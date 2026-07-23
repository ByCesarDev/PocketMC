# Auditoría y Diseño: Reestructuración de Contenido Vanilla

Este documento contiene el análisis técnico inicial (Fase 1) y el diseño propuesto (Fase 2) del sistema interno de contenido para PocketMC, según los requerimientos establecidos en el plan de reestructuración.

## 1. Análisis Técnico del Sistema Actual

La base de código actual es una recreación o adaptación de una versión antigua de Minecraft Pocket Edition (aproximadamente la v0.6.1). 
El estilo de programación utilizado mezcla directamente la lógica y los datos visuales, dependiendo de herencia profunda y de la creación de instancias mediante `new` en métodos estáticos de inicialización.

### Principales observaciones:
* **Acoplamiento Visual-Lógico**: Las definiciones de `Tile` (Bloques) e `Item` enlazan directamente texturas (`setIcon`) dentro del mismo archivo de inicialización lógica. 
* **Hardcoding**: Los IDs numéricos son hardcodeados. Se crean punteros estáticos globales para cada bloque e ítem (`Tile::rock`, `Item::apple`), haciéndolo altamente dependiente del estado global.
* **Clasificación Básica**: El motor no utiliza un Entity Component System (ECS). Se apoya en herencia tradicional para todo (`Tile -> LiquidTile -> LiquidTileDynamic` o `Item -> WeaponItem`). 

## 2. Registros Encontrados

Actualmente, no hay "registros" formales fuertemente tipados. Los objetos se instancian y almacenan en arreglos globales o se manejan por variables estáticas:
* **Tiles (Bloques)**: Arreglo `Tile::tiles[256]`. Inicializado en `Tile::initTiles()`.
* **Items**: Arreglo `Item::items[4096]`. Inicializado en `Item::initItems()`.
* **Entities**: No hay un registro estructurado, se inicializan con un `switch/case` hardcodeado en `EntityFactory::CreateEntity()` o `MobFactory::CreateMob()`.
* **Tile Entities (Block Entities)**: Se mapean estáticamente por tipos numéricos en `TileEntity::initTileEntities()`.
* **Materiales**: Inicializados estáticamente en `Material::initMaterials()`.
* **Biomas**: Arreglo `Biome::biomes[256]`.
* **Recetas**: `Recipes::initRecipes()` carga todo en instancias estáticas y listas.

## 3. Subsistemas de Contenido

* **Sistema de Mundo/Chunks**: Representación tradicional del terreno (probablemente usando nibble arrays para metadata y luz).
* **Sistema de Renderizado de Entidades**: Clases especializadas (ej. `GameRenderer`, `ItemRenderer`, `TileRenderer`) que contienen lógica visual. 
* **IA/Comportamiento**: Un sistema básico por clases, con herencia simple o jerarquía como `PathfinderMob`, `AgableMob`, `Mob`.
* **Redstone/Mecanismos**: Básicos (puertas, trampillas, redstone ore).

## 4. Mapa de Dependencias Problemático

* `NinecraftApp::init` inicializa lógica base.
* `Item` y `Tile` acoplan IDs de textura del cliente a los objetos lógicos.
* `EntityFactory` (lógica) incluye dependencias duras a clases individuales como `Arrow`, `Painting`, dificultando la mantenibilidad si se añaden muchas entidades. 
* Los "Singletons" (`Tile::grass`, `Item::stick`) asumen que las definiciones de juego son punteros globales modificables, los cuales podrían corromperse o estar mal inicializados.

## 5. Arquitectura Recomendada

Adoptar el patrón sugerido de separación estricta **Lógica vs Recursos**, pero manteniéndolo en C++ y evitando JSON para la lógica.

**Vanilla Behavior Side (Lógica):**
- Registros explícitos en tiempo de inicio (`RegistryManager`).
- Reemplazar herencia masiva con inicializaciones data-driven a través de _Builders_ en C++.
- Usar un sistema de Identificadores (Namespace + Path).

**Vanilla Resource Side (Renderizado):**
- Clases que resuelvan IDs de bloques, ítems o entidades hacia sus respectivas geometrías, materiales y texturas.
- Evitar que `ItemDefinition` sepa en qué sprite de la hoja de texturas se dibuja. Esto debe estar mapeado en el Resource Side.

## 6. Estructura de Carpetas Propuesta

```text
src/
├── behavior_packs/
│   └── vanilla/
│       ├── blocks/       # Definiciones de bloques (Builder, callbacks)
│       ├── items/        # Definiciones de items (Builder, callbacks)
│       ├── entities/     # Definiciones lógicas de entidades (Server-side)
│       ├── components/   # Sistemas modulares (en vez de herencia profunda)
│       ├── recipes/      # Recetas tipadas
│       └── VanillaBehaviorBootstrap.cpp  # Entry point de registro
│
└── resource_packs/
    └── vanilla/
        ├── models/       # Modelos importados / Parseados
        ├── textures/     # Resolución visual, mapeos de atlas
        ├── renderers/    # Despliegue visual
        └── VanillaResourceBootstrap.cpp  # Entry point de UI/Render
```

## 7. Interfaces Principales en C++ (Propuesta)

```cpp
// ResourceLocation (Identificadores)
struct ResourceLocation {
    std::string_view namespaceName;
    std::string_view path;
    
    // Comparadores para hash/map
};

// Builder para items
class ItemDefinition {
public:
    static ItemDefinitionBuilder builder(const ResourceLocation& id);
    // ...
};

// Registry
class GameRegistry {
public:
    BlockRegistry blocks;
    ItemRegistry items;
    EntityTypeRegistry entities;
    RecipeRegistry recipes;
};
```

## 8. Orden de Inicialización

1. **Creación del Registry**: Instanciación de un `GameRegistry` vacío.
2. **Behavior Bootstrap**: Se registran bloques, ítems y entidades puras (`VanillaBehaviorBootstrap::registerContent`).
3. **Validación Behavior**: Revisar cruces (ej. ítems referenciando recetas inválidas o referenciando bloques inexistentes).
4. **Client Resource Bootstrap**: Mapear los identificadores lógicos registrados con sus recursos visuales (Texturas, modelos).
5. **Freeze**: Se "congela" el registro para generar lookup-tables de alta velocidad (arrays de punteros u O(1) reads).
6. **Inicio del Juego**: Instanciación del `Level`, Carga del mundo.

## 9. Plan de Migración

1. **Infraestructura Core**: Crear `ResourceLocation`, y los Registros (`BlockRegistry`, `ItemRegistry`).
2. **Prueba Vertical (Shadowing)**: Migrar 1 bloque (ej. `stone`), 1 item (ej. `stick`) y 1 entidad (ej. `zombie`) al nuevo sistema, haciendo un "puente" automático hacia la estructura antigua (por compatibilidad temporal) o registrándolos nativamente en el nuevo sin borrar los viejos.
3. **Migración Completa de Items y Blocks**: Traducir todo `Tile::initTiles()` e `Item::initItems()` al formato builder, separando `.setIcon()` al Resource Bootstrap.
4. **Desacoplamiento de IDs numéricos**: Mantener compatibilidad temporal del guardado, pero internamente preferir acceso por `ResourceLocation`.
5. **Redirección Visual**: El renderer consulta al `ClientResourceRegistry` para obtener texturas o modelos basados en el string ID del bloque/ítem.

## 10. Riesgos Identificados

> [!WARNING]
> **Compatibilidad de Guardado**: Los mundos existentes guardan Nibbles y Bytes usando los IDs hardcodeados antiguos. Hay que garantizar que el nuevo sistema pueda mapear un `ResourceLocation` ("minecraft:stone") a su ID de runtime heredado (1) para cargar chunks antiguos correctamente.

> [!CAUTION]
> **Rendimiento Visual**: El `TileRenderer` asume que cada `Tile` le dirá cómo renderizarse. Separar la lógica puede requerir refactorizar partes del motor de teselado (`Tesselator.cpp`).

## 11. Elementos que Permanecen Sin Cambios (Por ahora)

- No tocaremos el formato NBT ni el I/O asíncrono de los chunks directamente.
- No instalaremos un ECS completo (Entity Component System) masivo si no es estrictamente necesario, aunque adaptaremos componentes específicos para no depender tanto de jerarquías.
- No se agregará soporte de modding ni APIs públicas todavía (sin loaders dinámicos).

## 12. Prueba Vertical (Próxima Fase - Ejecución)

**Objetivo:** Demostrar el flujo completo E2E en C++ tipado.
1. Implementar `ResourceLocation`.
2. Implementar `BlockRegistry` (Behavior) y `BlockResourceRegistry` (Client).
3. Migrar el bloque `stone` y un item como `stick` al nuevo sistema `VanillaBehaviorBootstrap`.
4. Enlazar el renderizado de `stone` en el mundo utilizando el `VanillaResourceBootstrap`.

## Próximos Pasos

> [!IMPORTANT]
> Se requiere aprobación del usuario para proceder.

Si apruebas este diseño y el enfoque de migración:
1. Me autorizas a modificar el código fuente para crear el registro básico y la infraestructura de identificadores (`ResourceLocation`).
2. Luego, crearé la carpeta `src/behavior_packs/vanilla` e implementaré la prueba vertical con el bloque de piedra (`stone`).
3. Te notificaré cuando la prueba de infraestructura esté lista para que intentes compilar.

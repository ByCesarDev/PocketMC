# Reestructuración del sistema interno de contenido vanilla en C++

Quiero que analices profundamente el proyecto actual antes de modificar cualquier archivo.

El objetivo general es investigar cómo funcionan actualmente el registro, almacenamiento, carga, inicialización, vinculación y uso interno de todo el contenido del juego, especialmente:

- Bloques.
- Ítems.
- Entidades.
- Tile Entities o Block Entities.
- Componentes.
- Estados de bloques.
- Propiedades de ítems.
- Comportamientos de entidades.
- Inteligencia artificial.
- Modelos.
- Geometrías.
- Huesos.
- Texturas.
- Materiales.
- Animaciones.
- Controladores de animación.
- Controladores de renderizado.
- Eventos.
- Recetas.
- Sonidos.
- Partículas.
- Loot tables.
- Inventarios.
- Contenedores.
- Tags.
- Spawn rules.
- Biomas y condiciones de aparición.
- Cualquier otro sistema relacionado con el contenido vanilla.

No quiero que comiences creando un sistema nuevo sin comprender el existente.

---

# 1. Objetivo principal

Quiero migrar progresivamente el contenido interno del juego hacia una arquitectura organizada en dos ramas principales:

```text
src/
├── behavior_packs/
│   └── vanilla/
│
└── resource_packs/
    └── vanilla/
````

Estas carpetas no representan packs externos cargados como en Minecraft Bedrock.

Representan la organización interna y nativa del contenido vanilla del juego.

La intención es separar claramente:

* La lógica, datos funcionales y comportamiento del contenido.
* Los recursos visuales, auditivos y de presentación.

Todo el contenido vanilla debe continuar formando parte del ejecutable o de los recursos oficiales del juego.

Por ahora, no debes implementar un sistema de mods.

Primero debe quedar correctamente diseñada, migrada y funcionando la arquitectura vanilla. El soporte para mods se estudiará en otra etapa reutilizando, cuando sea posible, las interfaces y registros creados para vanilla.

---

# 2. Restricción principal: no utilizar JSON para la lógica

No quiero copiar directamente el sistema data-driven de Minecraft Bedrock.

La lógica y las definiciones internas deben escribirse en C++.

Esto incluye, entre otros:

* Definiciones de bloques.
* Definiciones de ítems.
* Definiciones de entidades.
* Componentes.
* Propiedades.
* Estados.
* Eventos.
* Comportamientos.
* Objetivos de inteligencia artificial.
* Reglas de aparición.
* Recetas.
* Loot tables.
* Animaciones.
* Controladores de animación.
* Controladores de renderizado.
* Vinculación de texturas y materiales.
* Configuración de inventario creativo.
* Registro de Block Entities.
* Interacciones.
* Colisiones.
* Sonidos y partículas asociados.
* Cualquier configuración funcional del contenido.

No deben crearse archivos JSON para representar estos sistemas.

La arquitectura debe emplear:

* Clases de C++.
* Structs.
* Componentes.
* Builders.
* Factories.
* Registros tipados.
* Enumeraciones.
* Identificadores fuertes.
* Interfaces.
* Sistemas de eventos.
* Datos constantes compilados.
* Archivos `.hpp` y `.cpp`.

Evita crear un “JSON escrito en C++”, es decir, enormes estructuras genéricas de mapas de strings sin tipado.

Quiero aprovechar las ventajas reales de C++:

* Tipado estático.
* Validación durante compilación.
* Autocompletado.
* Referencias seguras.
* Menor cantidad de búsquedas mediante strings.
* Mejor rendimiento.
* Mejor trazabilidad.
* Código reutilizable.
* Errores detectables antes de ejecutar el juego.

---

# 3. Única excepción para JSON: modelos de Blockbench

La única excepción permitida inicialmente es el formato JSON de modelos o geometrías exportados por Blockbench.

Quiero mantener compatibilidad con los modelos vanilla de Blockbench.

El motor debe poder importar o cargar geometrías compatibles con el formato utilizado por modelos de Minecraft Bedrock o por el preset correspondiente de Blockbench.

Los archivos de modelo pueden contener información como:

* Identificador de la geometría.
* Texture width.
* Texture height.
* Visible bounds.
* Huesos.
* Jerarquía padre-hijo.
* Pivotes.
* Rotaciones.
* Cubos.
* Posición u origen.
* Tamaño.
* UV.
* Mirror.
* Inflate.
* Locators, cuando correspondan.

Debes analizar si el proyecto ya posee:

* Un parser de modelos.
* Una representación de geometría.
* Un sistema de huesos.
* Un cargador de texturas.
* Un sistema de UV.
* Soporte para jerarquías.
* Un sistema de animación esquelética.

No reemplaces un sistema existente que ya funcione sin justificar técnicamente la modificación.

Aunque los modelos se carguen desde JSON, después de leerlos deben convertirse a estructuras internas fuertemente tipadas en C++.

Por ejemplo:

```cpp
struct ModelGeometry;
struct ModelBone;
struct ModelCube;
struct ModelLocator;
struct ModelUV;
struct BoneTransform;
```

El JSON no debe permanecer como representación genérica durante el gameplay ni consultarse repetidamente durante el renderizado.

Debe analizarse, validarse y transformarse en recursos internos durante la etapa de carga.

---

# 4. Estructura conceptual deseada

Analiza si una organización semejante a la siguiente resulta adecuada para el proyecto. No la copies ciegamente: adáptala a la arquitectura real encontrada.

```text
src/
├── behavior_packs/
│   └── vanilla/
│       ├── blocks/
│       ├── items/
│       ├── entities/
│       ├── block_entities/
│       ├── components/
│       ├── events/
│       ├── recipes/
│       ├── loot_tables/
│       ├── spawn_rules/
│       ├── ai/
│       ├── tags/
│       ├── biomes/
│       ├── containers/
│       └── VanillaBehaviorBootstrap.cpp
│
└── resource_packs/
    └── vanilla/
        ├── models/
        │   ├── blocks/
        │   ├── items/
        │   └── entities/
        ├── textures/
        │   ├── blocks/
        │   ├── items/
        │   ├── entities/
        │   ├── gui/
        │   └── environment/
        ├── materials/
        ├── animations/
        ├── animation_controllers/
        ├── render_controllers/
        ├── sounds/
        ├── particles/
        ├── fonts/
        └── VanillaResourceBootstrap.cpp
```

No es obligatorio usar exactamente estos nombres.

Primero debes revisar:

* La estructura actual del repositorio.
* Las convenciones de nombres existentes.
* El sistema de compilación.
* Cómo se agregan archivos nuevos.
* Cómo se cargan los recursos.
* Qué subsistemas ya existen.
* Qué partes dependen directamente de rutas antiguas.
* Qué cambios romperían compatibilidad.

---

# 5. Fase obligatoria de investigación

Antes de implementar, realiza una auditoría completa del proyecto.

## 5.1 Registro actual de bloques

Investiga:

* Dónde se declaran los bloques.
* Dónde se crean sus instancias.
* Cómo se asignan sus identificadores.
* Si existen IDs numéricos, nombrespaced IDs o ambos.
* Cómo se relacionan los IDs persistentes con los IDs de runtime.
* Cómo se registran estados y propiedades.
* Cómo se calculan las variantes.
* Cómo se registra la colisión.
* Cómo se define la selección o hitbox.
* Cómo se configura la dureza.
* Cómo se configura la resistencia.
* Cómo se configura la luz emitida.
* Cómo se configura la filtración de luz.
* Cómo se determinan los sonidos.
* Cómo se determinan las herramientas adecuadas.
* Cómo se calculan los drops.
* Cómo se vincula un bloque con su ítem.
* Cómo se asigna su modelo.
* Cómo se asignan sus texturas.
* Cómo se renderizan bloques completos y modelos personalizados.
* Cómo se guardan y cargan en mundos existentes.
* Cómo se representan dentro de chunks.
* Cómo se sincronizan por red.
* Cómo se agregan al inventario creativo.
* Cómo se manejan bloques con orientación.
* Cómo se manejan bloques con múltiples estados.
* Cómo se manejan bloques transparentes o translúcidos.
* Cómo se manejan líquidos.
* Cómo se manejan bloques con Block Entity.

Identifica todas las clases, archivos y funciones implicadas.

## 5.2 Registro actual de ítems

Investiga:

* Registro de identificadores.
* IDs de runtime.
* Stack size.
* Durabilidad.
* Daño o metadata.
* Categoría creativa.
* Iconos.
* Modelos.
* Texturas.
* Uso principal y secundario.
* Cooldown.
* Herramientas.
* Armas.
* Armaduras.
* Comida.
* Ítems colocables.
* Ítems que generan entidades.
* Ítems con estados internos.
* Serialización dentro de inventarios.
* Sincronización por red.
* Enchantments.
* Tags.
* Recetas.
* Interacciones con bloques.
* Interacciones con entidades.
* Vinculación entre `Block` y `BlockItem`, si existe.

Determina si actualmente los bloques e ítems utilizan registros separados, un registro compartido o relaciones manuales.

## 5.3 Registro actual de entidades

Investiga:

* Clase base de entidad.
* Jerarquía de herencia.
* Factories.
* Identificadores persistentes.
* IDs de runtime.
* Spawn.
* Despawn.
* Serialización.
* Sincronización.
* Componentes.
* Atributos.
* Movimiento.
* Física.
* Colisiones.
* Salud.
* Daño.
* Efectos.
* Inventario.
* Equipamiento.
* IA.
* Goals.
* Navigation.
* Targeting.
* Eventos.
* Variantes.
* Taming.
* Breeding.
* Riding.
* Animaciones.
* Modelos.
* Texturas.
* Materiales.
* Sonidos.
* Partículas.
* Spawn eggs.
* Renderizado.
* Interpolación en el cliente.
* Diferencias entre representación lógica y visual.

Analiza si la arquitectura actual usa:

* Herencia tradicional.
* Entity Component System.
* Sistema híbrido.
* Componentes dinámicos.
* Componentes compilados.
* Máquinas de estados.
* Callbacks.
* Event buses.

No fuerces un ECS si el proyecto no lo necesita. Tampoco mantengas una jerarquía de herencia problemática solo por compatibilidad. Explica las ventajas y desventajas encontradas.

## 5.4 Tile Entities o Block Entities

Analiza:

* Cómo se asocian con un bloque.
* Cómo se crean.
* Cómo se destruyen.
* Cómo se guardan.
* Cómo se cargan.
* Cómo se actualizan.
* Si tienen tick.
* Cómo almacenan inventarios.
* Cómo abren interfaces.
* Cómo sincronizan datos.
* Cómo se vinculan con el renderer.
* Cómo se identifica su tipo.
* Cómo se valida que el bloque correspondiente siga existiendo.
* Qué ocurre al cambiar el estado del bloque.
* Qué ocurre al romper o mover el bloque.

Ejemplos que debes localizar, si existen:

* Cofres.
* Hornos.
* Tolvas.
* Carteles.
* Camas.
* Spawners.
* Mesas especiales.
* Bloques con inventario.
* Bloques animados.

## 5.5 Modelos y renderizado

Investiga por separado el flujo de:

```text
identificador lógico
→ definición visual
→ modelo
→ geometría
→ huesos
→ materiales
→ texturas
→ animaciones
→ render controller
→ renderer
```

Determina:

* Cómo se obtiene actualmente el modelo de un bloque, ítem o entidad.
* Si existen atlases.
* Si cada textura se almacena individualmente.
* Si se utilizan spritesheets globales.
* Si los ítems dependen de archivos como `gui_blocks.png`.
* Cómo se generan UV.
* Cómo se cargan texturas.
* Cómo se cachean modelos.
* Cómo se cachean materiales.
* Cómo se liberan recursos.
* Cómo se manejan recursos faltantes.
* Cómo se realiza hot reload, si existe.
* Cómo se elige una variante visual.
* Cómo se renderiza un ítem en GUI.
* Cómo se renderiza en primera persona.
* Cómo se renderiza en tercera persona.
* Cómo se renderiza como entidad tirada.
* Cómo se renderiza como bloque colocado.

Quiero que cada bloque, ítem o entidad pueda enlazarse explícitamente con sus recursos sin depender obligatoriamente de una textura global de inventario.

---

# 6. Sistema de registros propuesto

Después de estudiar el proyecto, diseña registros centrales fuertemente tipados.

Evalúa la creación de sistemas similares a:

```cpp
BlockRegistry
ItemRegistry
EntityTypeRegistry
BlockEntityTypeRegistry
ComponentRegistry
RecipeRegistry
LootTableRegistry
AnimationRegistry
AnimationControllerRegistry
RenderControllerRegistry
ModelRegistry
TextureRegistry
MaterialRegistry
SoundRegistry
ParticleRegistry
TagRegistry
```

No todos tienen que ser registros globales independientes.

Determina cuáles deberían:

* Existir como servicios.
* Pertenecer al contexto del juego.
* Pertenecer al cliente.
* Pertenecer al servidor.
* Compartirse.
* Inicializarse durante el bootstrap.
* Ser inmutables después de finalizar el registro.
* Permitir consultas durante runtime.
* Permitir recarga.
* Ser compilados directamente.

Evita singletons innecesarios y problemas de orden de inicialización estática.

Preferiblemente debe existir una fase explícita:

```text
crear registros
→ registrar definiciones vanilla
→ validar referencias
→ congelar registros
→ generar tablas de runtime
→ cargar recursos
→ iniciar mundo
```

Estudia si resulta apropiado utilizar una estructura como:

```cpp
class ContentRegistry {
public:
    BlockRegistry blocks;
    ItemRegistry items;
    EntityTypeRegistry entities;
    BlockEntityTypeRegistry blockEntities;
    RecipeRegistry recipes;
    TagRegistry tags;
};
```

Para el cliente podría existir:

```cpp
class ClientResourceRegistry {
public:
    ModelRegistry models;
    TextureRegistry textures;
    MaterialRegistry materials;
    AnimationRegistry animations;
    AnimationControllerRegistry animationControllers;
    RenderControllerRegistry renderControllers;
    SoundRegistry sounds;
    ParticleRegistry particles;
};
```

No implementes estas clases exactamente sin validar primero su encaje con el código actual.

---

# 7. Identificadores

Diseña un sistema consistente de identificadores.

Debe contemplar identificadores como:

```text
minecraft:stone
minecraft:diamond_sword
minecraft:zombie
minecraft:chest
minecraft:recipe/wooden_pickaxe
minecraft:animation/zombie_walk
minecraft:model/zombie
```

Evalúa una clase tipada como:

```cpp
class ResourceLocation {
public:
    std::string_view namespaceName() const;
    std::string_view path() const;
};
```

También puedes evaluar identificadores separados:

```cpp
BlockId
ItemId
EntityTypeId
BlockEntityTypeId
ModelId
TextureId
AnimationId
RecipeId
```

Los identificadores deben distinguir entre:

* Identificador estable y persistente.
* Identificador o índice de runtime.
* Identificador utilizado en archivos guardados.
* Identificador utilizado en paquetes de red.
* Handle interno.
* Ruta del recurso.

No reemplaces todos los identificadores con enteros sin considerar la compatibilidad de mundos guardados.

No uses strings repetidamente en operaciones críticas si pueden resolverse una vez durante la carga.

---

# 8. Definiciones de bloques en C++

Propón una API clara y tipada para registrar bloques vanilla.

Ejemplo conceptual:

```cpp
void registerVanillaBlocks(BlockRegistry& registry) {
    registry.registerBlock(
        BlockDefinition::builder(BlockId{"minecraft:stone"})
            .material(BlockMaterial::Stone)
            .hardness(1.5f)
            .blastResistance(6.0f)
            .soundGroup(SoundGroupId{"minecraft:stone"})
            .collision(BlockCollision::fullCube())
            .lightEmission(0)
            .lightFilter(15)
            .lootTable(LootTableId{"minecraft:blocks/stone"})
            .model(BlockModelId{"minecraft:block/stone"})
            .creativeCategory(CreativeCategory::Construction)
            .build()
    );
}
```

Esto es solamente un ejemplo conceptual.

La implementación final debe adaptarse al estilo real del motor.

Incluye soporte para:

* Bloques simples.
* Bloques con estados.
* Bloques orientables.
* Bloques con propiedades booleanas.
* Bloques con propiedades enumeradas.
* Bloques con propiedades enteras.
* Variantes de modelos.
* Colisiones personalizadas.
* Render layers.
* Transparencia.
* Luz.
* Interacciones.
* Ticks aleatorios.
* Ticks programados.
* Eventos.
* Block Entities.
* Drops.
* Herramientas apropiadas.
* Waterlogging, si existe.
* Redstone o sistema equivalente, si existe.

---

# 9. Definiciones de ítems en C++

Propón una API equivalente para ítems:

```cpp
void registerVanillaItems(ItemRegistry& registry) {
    registry.registerItem(
        ItemDefinition::builder(ItemId{"minecraft:diamond_sword"})
            .maxStackSize(1)
            .durability(1561)
            .creativeCategory(CreativeCategory::Equipment)
            .icon(TextureId{"minecraft:item/diamond_sword"})
            .component<MeleeWeaponComponent>(/* ... */)
            .component<ToolComponent>(/* ... */)
            .build()
    );
}
```

El sistema debe poder representar:

* Ítems básicos.
* Block items.
* Herramientas.
* Armas.
* Armaduras.
* Comida.
* Consumibles.
* Proyectiles.
* Ítems cargables.
* Ítems con cooldown.
* Ítems con durabilidad.
* Ítems con modelos personalizados.
* Ítems con comportamiento al usar.
* Ítems con comportamiento al utilizar sobre bloques.
* Ítems con comportamiento al utilizar sobre entidades.
* Ítems que colocan entidades.
* Ítems con estados o datos persistentes.

---

# 10. Definiciones de entidades en C++

Investiga si conviene registrar entidades mediante factories y descriptores:

```cpp
registry.registerEntityType(
    EntityTypeDefinition::builder(EntityTypeId{"minecraft:zombie"})
        .factory<Zombie>()
        .dimensions(0.6f, 1.95f)
        .trackingRange(64.0f)
        .component<HealthComponent>(20.0f)
        .component<MovementComponent>(0.23f)
        .component<HostileMobComponent>()
        .behaviorSet(BehaviorSetId{"minecraft:zombie"})
        .clientDefinition(ClientEntityId{"minecraft:zombie"})
        .build()
);
```

Debes determinar qué información pertenece a:

* El tipo de entidad.
* La instancia de entidad.
* Los componentes compartidos.
* Los componentes por instancia.
* El servidor.
* El cliente.
* El renderer.
* La IA.
* La serialización.

La lógica del servidor no debe depender directamente de texturas, modelos ni clases de renderizado.

La parte visual debe poder resolver el mismo identificador de entidad hacia una definición cliente.

---

# 11. Separación entre comportamiento y recursos

Quiero conservar conceptualmente la división de Bedrock, pero implementada internamente en C++.

## Behavior side

Debe contener o registrar:

* Bloques.
* Ítems.
* Entidades.
* Block Entities.
* Componentes funcionales.
* Atributos.
* IA.
* Eventos.
* Recetas.
* Loot.
* Spawn.
* Tags funcionales.
* Interacciones.
* Reglas del mundo.
* Serialización.
* Lógica de gameplay.

## Resource side

Debe contener o registrar:

* Modelos.
* Geometrías.
* Texturas.
* Materiales.
* Animaciones.
* Controladores de animación.
* Controladores de renderizado.
* Sonidos.
* Partículas.
* Recursos de GUI.
* Definiciones visuales.

Debe existir una interfaz clara entre ambos lados.

Por ejemplo:

```text
EntityTypeId minecraft:zombie
        │
        ├── servidor: comportamiento, atributos, IA y eventos
        │
        └── cliente: modelo, textura, material, animaciones y renderer
```

No permitas dependencias circulares entre gameplay y renderizado.

---

# 12. Sistema de componentes

Analiza los componentes actuales y determina si pueden normalizarse.

Posibles categorías:

## Componentes de bloques

* CollisionComponent.
* SelectionBoxComponent.
* LightComponent.
* FlammableComponent.
* PlacementComponent.
* InteractionComponent.
* TickComponent.
* LootComponent.
* BlockEntityComponent.
* CraftingTableComponent.

## Componentes de ítems

* DurabilityComponent.
* FoodComponent.
* ToolComponent.
* WeaponComponent.
* ArmorComponent.
* CooldownComponent.
* ChargeableComponent.
* BlockPlacerComponent.
* EntityPlacerComponent.
* UseComponent.
* EnchantableComponent.

## Componentes de entidades

* HealthComponent.
* MovementComponent.
* PhysicsComponent.
* CollisionComponent.
* InventoryComponent.
* EquipmentComponent.
* AgeableComponent.
* BreedableComponent.
* RideableComponent.
* TameableComponent.
* NavigationComponent.
* GoalSelectorComponent.
* TargetSelectorComponent.
* VariantComponent.
* ExperienceRewardComponent.

No crees componentes extremadamente pequeños sin una razón real.

Evita convertir cada propiedad escalar en una clase independiente.

Distingue entre:

* Datos de definición.
* Estado mutable de una instancia.
* Sistemas que procesan componentes.
* Callbacks de comportamiento.
* Eventos.

---

# 13. Animaciones en C++

Las animaciones y sus controladores también deben definirse en C++, no en JSON.

El sistema debe representar:

```text
Animation
└── BoneAnimation
    ├── PositionChannel
    │   └── Keyframes
    ├── RotationChannel
    │   └── Keyframes
    └── ScaleChannel
        └── Keyframes
```

Debe soportar:

* Posición.
* Rotación.
* Escala.
* Keyframes.
* Tiempo.
* Loop.
* Hold on last frame.
* Interpolación lineal.
* Interpolación Catmull-Rom, si el motor la soporta.
* Valores pre y post.
* Animaciones aditivas.
* Blend weights.
* Blend transitions.
* Eventos en timelines.
* Locators.
* Jerarquía de huesos.
* Animaciones simultáneas.
* Reinicio a la pose base.
* Animación por canales.
* Cacheo de bindings entre nombres de huesos e índices internos.

Ejemplo conceptual:

```cpp
AnimationDefinition zombieWalk {
    .id = AnimationId{"minecraft:zombie/walk"},
    .loopMode = AnimationLoopMode::Loop,
    .length = 1.0f,
    .bones = {
        BoneAnimation{
            .bone = BoneId{"right_leg"},
            .rotation = RotationChannel{
                /* keyframes */
            }
        }
    }
};
```

No es obligatorio utilizar inicializadores exactamente así.

Investiga el sistema actual de animación antes de diseñar la API definitiva.

---

# 14. Controladores de animación

Implementa conceptualmente una máquina de estados en C++.

Debe permitir:

* Estado inicial.
* Estados nombrados.
* Animaciones por estado.
* Animaciones anidadas.
* Peso de animación.
* Transiciones.
* Condiciones.
* Blend transition.
* Eventos de entrada.
* Eventos de salida.
* Variables temporales.
* Finalización de animaciones.
* Múltiples controladores activos.

Ejemplo conceptual:

```cpp
AnimationControllerDefinition controller {
    .id = AnimationControllerId{"minecraft:zombie/movement"},
    .initialState = "idle",
    .states = {
        AnimationState{
            .name = "idle",
            .animations = { AnimationId{"minecraft:zombie/idle"} },
            .transitions = {
                Transition{
                    .target = "walking",
                    .condition = Query::isMoving()
                }
            }
        }
    }
};
```

No quiero strings interpretados continuamente durante cada frame cuando la condición pueda representarse mediante una función, expresión compilada, handle o árbol de expresión preprocesado.

---

# 15. Sustitución de Molang

No quiero depender de Molang como lenguaje textual en archivos JSON.

Sin embargo, analiza los conceptos que Molang resuelve:

* Queries de solo lectura.
* Variables mutables.
* Variables temporales.
* Variables globales.
* Expresiones matemáticas.
* Condiciones.
* Acceso a propiedades de entidad.
* Acceso al tiempo de animación.
* Acceso al movimiento.
* Selección de recursos.
* Cálculos previos al render.
* Condiciones de transición.

Propón una alternativa en C++.

Puede incluir:

* Callbacks tipados.
* Lambdas.
* Expression trees.
* Functors.
* Query handles.
* Animation parameters.
* Variables indexadas.
* Expresiones compiladas.
* Un pequeño sistema interno de bytecode, solamente si está realmente justificado.

Ejemplo:

```cpp
AnimationCondition isWalking =
    [](const AnimationContext& context) {
        return context.entity().movementSpeed() > 0.01f;
    };
```

Para operaciones utilizadas en cada frame, evita:

* Búsquedas repetidas por strings.
* Parsing durante el gameplay.
* Allocations innecesarias.
* `std::function` en rutas críticas sin evaluar su costo.
* RTTI innecesario.
* Acceso inseguro a componentes.

Considera que las consultas representan valores de solo lectura del objeto actual, mientras las variables representan datos modificables utilizados por el sistema de animación.

---

# 16. Render Controllers en C++

Diseña una alternativa tipada para decidir:

* Qué geometría utilizar.
* Qué textura utilizar.
* Qué material utilizar.
* Qué variante renderizar.
* Qué render layer utilizar.
* Qué partes ocultar.
* Cómo renderizar armadura.
* Cómo renderizar objetos equipados.
* Qué recursos dependen del estado de la entidad.
* Cómo manejar variantes, bebés, entidades cargadas o estados especiales.

Ejemplo conceptual:

```cpp
struct EntityRenderDefinition {
    EntityTypeId entityType;
    ModelId defaultModel;
    MaterialId defaultMaterial;
    TextureSelector textureSelector;
    ModelSelector modelSelector;
    std::vector<AnimationControllerId> animationControllers;
};
```

El registro visual debe validar que todos los recursos referenciados existan.

---

# 17. Eventos

Diseña o reutiliza un sistema de eventos que permita manejar:

## Bloques

* OnPlaced.
* OnDestroyed.
* OnInteracted.
* OnSteppedOn.
* OnEntityInside.
* OnNeighborChanged.
* OnRandomTick.
* OnScheduledTick.

## Ítems

* OnUse.
* OnUseOnBlock.
* OnUseOnEntity.
* OnConsume.
* OnRelease.
* OnDurabilityChanged.
* OnBroken.

## Entidades

* OnSpawn.
* OnDespawn.
* OnDamage.
* OnDeath.
* OnTargetAcquired.
* OnInteract.
* OnTamed.
* OnBred.
* OnEnterState.
* OnExitState.

## Animaciones

* Timeline events.
* OnAnimationStart.
* OnAnimationFinished.
* OnControllerStateEnter.
* OnControllerStateExit.

Determina cuáles eventos deben:

* Ser callbacks directos.
* Publicarse en un event bus.
* Ser procesados por componentes.
* Ejecutarse exclusivamente en servidor.
* Ejecutarse exclusivamente en cliente.
* Replicarse por red.

Evita usar un event bus global para absolutamente todo.

---

# 18. Recetas

Las recetas deben registrarse en C++.

Debe existir soporte para:

* Shaped recipes.
* Shapeless recipes.
* Furnace recipes.
* Smelting.
* Smoking.
* Campfire.
* Stonecutting, si existe.
* Brewing, si existe.
* Recetas especiales.
* Tags como ingredientes.
* Cantidades.
* Variantes.
* Resultados con datos adicionales.

Ejemplo conceptual:

```cpp
recipes.registerShaped(
    RecipeId{"minecraft:wooden_pickaxe"},
    ShapedRecipe{
        .pattern = {
            "PPP",
            " S ",
            " S "
        },
        .keys = {
            {'P', Ingredient::tag("minecraft:planks")},
            {'S', Ingredient::item("minecraft:stick")}
        },
        .result = ItemStack{"minecraft:wooden_pickaxe", 1}
    }
);
```

Durante el bootstrap se deben validar ingredientes, tags y resultados.

---

# 19. Bootstrap vanilla

Quiero una inicialización explícita y ordenada.

Ejemplo:

```cpp
void registerVanillaContent(GameContent& content) {
    registerVanillaTags(content.tags);
    registerVanillaMaterials(content.materials);

    registerVanillaBlocks(content.blocks);
    registerVanillaItems(content.items);
    registerVanillaBlockEntities(content.blockEntities);
    registerVanillaEntityTypes(content.entities);

    registerVanillaRecipes(content.recipes);
    registerVanillaLootTables(content.lootTables);
    registerVanillaSpawnRules(content.spawnRules);
}

void registerVanillaResources(ClientResources& resources) {
    registerVanillaTextures(resources.textures);
    registerVanillaModels(resources.models);
    registerVanillaMaterials(resources.materials);
    registerVanillaAnimations(resources.animations);
    registerVanillaAnimationControllers(resources.animationControllers);
    registerVanillaRenderControllers(resources.renderControllers);
    registerVanillaSounds(resources.sounds);
    registerVanillaParticles(resources.particles);
}
```

Debes determinar el orden real necesario según las dependencias encontradas.

Los registros deben pasar por una fase de validación antes de iniciar el juego.

---

# 20. Validación

Agrega validaciones para detectar:

* Identificadores duplicados.
* Referencias inexistentes.
* Modelos faltantes.
* Texturas faltantes.
* Materiales faltantes.
* Animaciones faltantes.
* Controladores faltantes.
* Huesos referenciados que no existen.
* Estados de animación inválidos.
* Transiciones hacia estados inexistentes.
* Recetas con ingredientes inválidos.
* Bloques sin BlockItem cuando deberían tenerlo.
* Block Entities asociadas a bloques incompatibles.
* IDs persistentes duplicados.
* Colisiones inválidas.
* Rangos numéricos inválidos.
* Dependencias circulares.
* Orden incorrecto de carga.
* Recursos registrados en el lado equivocado.
* Contenido cliente usado en builds de servidor dedicado.

Los errores deben mostrar información útil:

```text
[Content Validation]
Entity minecraft:zombie references missing animation
minecraft:zombie/attack

Referenced from:
src/resource_packs/vanilla/entities/ZombieResources.cpp:42
```

Siempre que sea posible, aprovecha `std::source_location` para registrar el origen de una definición.

---

# 21. Compatibilidad con cliente y servidor dedicado

La arquitectura debe permitir separar:

```text
Game/Core
Server/Behavior
Client/Resources
Renderer
```

Un servidor dedicado no debe cargar:

* Texturas.
* Modelos.
* Materiales gráficos.
* Shaders.
* Animaciones visuales.
* Render controllers.
* Recursos de GUI.

Sin embargo, puede necesitar:

* Timelines de eventos de gameplay.
* Estados lógicos.
* Colisiones.
* Dimensiones.
* Spawn rules.
* IA.
* Recetas.
* Loot.
* Componentes.

Analiza cuidadosamente qué parte de una animación es puramente visual y qué parte puede disparar eventos de gameplay.

Los eventos autoritativos no deben depender exclusivamente de una animación ejecutada en el cliente.

---

# 22. Serialización y compatibilidad de mundos

Antes de cambiar registros, investiga cómo los mundos guardan:

* IDs de bloques.
* Estados de bloques.
* Ítems.
* Metadata.
* Entidades.
* Block Entities.
* Inventarios.
* Recetas desbloqueadas.
* Variantes.
* Componentes.

No rompas mundos existentes.

Si es necesario, crea:

* Tablas de migración.
* Aliases de identificadores.
* Versiones de esquema.
* Conversión de IDs anteriores.
* Fallbacks para contenido desconocido.
* Data fixers.

Explica detalladamente cualquier incompatibilidad encontrada.

---

# 23. Rendimiento

Evalúa:

* Tiempo de inicio.
* Uso de memoria.
* Número de allocations.
* Coste de búsquedas por identificador.
* Coste por frame de animaciones.
* Coste de consultas de componentes.
* Duplicación de definiciones.
* Cacheo de modelos.
* Cacheo de texturas.
* Cacheo de bindings de huesos.
* Tablas de runtime.
* Contención de locks.
* Datos compartidos inmutables.
* Localidad de memoria.

No realices microoptimizaciones prematuras, pero no diseñes rutas críticas basadas en mapas de strings, parsing repetido o asignaciones por frame.

---

# 24. Proceso de trabajo obligatorio

Trabaja por fases.

## Fase 1: auditoría

Entrega un informe con:

1. Estructura actual del proyecto.
2. Archivos responsables de cada registro.
3. Flujo de inicialización.
4. Flujo de carga de recursos.
5. Dependencias entre sistemas.
6. Problemas encontrados.
7. Código duplicado.
8. Acoplamientos problemáticos.
9. Riesgos de migración.
10. Sistemas que ya pueden reutilizarse.

No modifiques masivamente el proyecto durante esta fase.

## Fase 2: diseño

Presenta:

1. Arquitectura propuesta.
2. Diagrama de dependencias.
3. Estructura de carpetas.
4. Clases principales.
5. Interfaces.
6. Flujo de bootstrap.
7. Estrategia de identificadores.
8. Estrategia de serialización.
9. Estrategia cliente-servidor.
10. Plan de migración incremental.

Debes justificar cada decisión utilizando evidencia del código actual.

## Fase 3: infraestructura mínima

Implementa solamente:

* Identificadores.
* Registro base.
* Validación.
* Bootstrap.
* Un bloque vanilla de prueba.
* Su BlockItem.
* Un ítem independiente.
* Una entidad vanilla sencilla.
* Una Block Entity, si el sistema ya las soporta.
* Un modelo Blockbench.
* Una textura individual.
* Una animación sencilla en C++.
* Un controlador de animación sencillo en C++.

No migres todo el contenido todavía.

## Fase 4: prueba vertical

El contenido de prueba debe funcionar de extremo a extremo:

```text
registro
→ validación
→ creación
→ serialización
→ networking
→ gameplay
→ resolución visual
→ modelo
→ textura
→ animación
→ renderizado
```

## Fase 5: migración gradual

Migra sistemas por grupos y realiza pruebas después de cada grupo.

Orden sugerido:

1. Bloques simples.
2. BlockItems.
3. Ítems básicos.
4. Bloques con estados.
5. Block Entities.
6. Recetas.
7. Entidades simples.
8. Entidades con IA.
9. Modelos.
10. Animaciones.
11. Controladores.
12. Renderizado especializado.
13. Sonidos y partículas.
14. Contenido restante.

El orden definitivo debe ajustarse según las dependencias reales del proyecto.

---

# 25. Pruebas

Incluye pruebas para:

* Registros duplicados.
* Resolución de identificadores.
* Persistencia de IDs.
* Bloques y estados.
* Serialización de ItemStack.
* Creación de entidades.
* Creación de Block Entities.
* Carga de modelos Blockbench.
* Jerarquías de huesos.
* Resolución de texturas.
* Evaluación de animaciones.
* Transiciones de controladores.
* Validación de recetas.
* Recursos faltantes.
* Builds de cliente.
* Builds de servidor.
* Apertura de mundos anteriores.

Cuando sea posible, utiliza:

* Unit tests.
* Integration tests.
* Snapshot tests para estructuras.
* Pruebas de carga.
* Escenas visuales de prueba.
* Assertions de desarrollo.

---

# 26. Elementos que no debes hacer

No debes:

* Implementar todavía la carga de mods.
* Crear una carpeta `mods/`.
* Crear manifests de mods.
* Diseñar APIs públicas para modders.
* Crear compatibilidad binaria con plugins.
* Convertir todo el proyecto de una sola vez.
* Eliminar sistemas anteriores sin una migración funcional.
* Cambiar IDs persistentes sin analizar los mundos guardados.
* Usar JSON para bloques, ítems, entidades o lógica.
* Usar JSON para animaciones o controladores.
* Copiar la arquitectura de Bedrock literalmente.
* Crear un ECS completo sin justificarlo.
* Usar singletons globales para todos los registros.
* Realizar parsing durante cada frame.
* Vincular directamente el servidor con el renderer.
* Duplicar lógica entre contenido vanilla y registros generales.
* Simular una arquitectura data-driven mediante mapas genéricos de strings en C++.

---

# 27. Preparación futura sin implementar mods

Aunque no se implementarán mods ahora, evita decisiones que hagan imposible agregar contenido externo en el futuro.

La infraestructura general puede diferenciar entre:

```cpp
enum class ContentSource {
    Engine,
    Vanilla,
    External
};
```

Pero durante esta etapa solo deben existir y utilizarse:

```text
Engine
Vanilla
```

No agregues loaders externos, manifests ni interfaces públicas todavía.

El registro vanilla debe usar la misma API interna estable que podría reutilizarse más adelante, pero el alcance actual termina en el contenido oficial del juego.

---

# 28. Resultado esperado

Al finalizar la primera etapa quiero recibir:

1. Un análisis técnico completo del sistema actual.
2. Una lista de todos los registros encontrados.
3. Una lista de todos los subsistemas de contenido.
4. Un mapa de dependencias.
5. La arquitectura recomendada.
6. Una estructura de carpetas propuesta.
7. Las interfaces principales en C++.
8. El orden de inicialización.
9. El plan de migración.
10. Los riesgos identificados.
11. Los elementos que deben permanecer sin cambios.
12. Una prueba vertical pequeña.
13. Evidencia de que la prueba compila y funciona.
14. Una lista concreta de los próximos pasos.

Antes de modificar código de forma amplia, presenta primero la auditoría y el diseño.

No asumas que la arquitectura descrita en este documento es perfecta. Úsala como dirección conceptual, compárala con el código existente y propone cambios cuando exista una razón técnica clara.

La prioridad es:

1. Comprender el proyecto actual.
2. Mantener el juego funcionando.
3. Organizar correctamente el contenido vanilla.
4. Separar comportamiento y recursos.
5. Migrar la lógica a C++ fuertemente tipado.
6. Mantener JSON solamente para geometrías compatibles con Blockbench.
7. Preparar una base mantenible para el futuro.
8. Dejar el sistema de mods fuera del alcance actual.


Un detalle importante que reforcé es que **los eventos de gameplay no deben quedar ligados a animaciones visuales del cliente**. Bedrock permite timelines y eventos dentro de animaciones, incluso controladores con eventos de entrada y salida, pero en tu motor conviene separar la autoridad lógica del servidor de la presentación visual. :contentReference[oaicite:3]{index=3} :contentReference[oaicite:4]{index=4}

También dejé explícito que reemplazar Molang no significa ignorar sus conceptos. Molang está pensado para cálculos data-driven en runtime y ofrece consultas, variables y expresiones usadas por animaciones y render controllers; en tu caso, esas capacidades deberían transformarse en callbacks o expresiones tipadas en C++. :contentReference[oaicite:5]{index=5} :contentReference[oaicite:6]{index=6}
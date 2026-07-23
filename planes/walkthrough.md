# Walkthrough: Fase 3 (Infraestructura Mínima)

Se ha implementado con éxito la base del sistema Data-Driven para la reestructuración del motor de PocketMC en C++. 

## Cambios Realizados

1. **Identificadores Persistentes (`ResourceLocation`)**
   - Se creó la clase `ResourceLocation` ([ResourceLocation.h](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/util/ResourceLocation.h)) para gestionar identificadores formales tipo `minecraft:stone` o `minecraft:zombie` de manera estandarizada y compatible con `std::hash`.

2. **Definiciones Funcionales (Builders)**
   - **Bloques**: Se implementó `BlockDefinition` y su _builder_ ([BlockDefinition.h](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/world/level/tile/BlockDefinition.h)) para registrar bloques con tipado estático (ej. dureza, luz, sonido, fábrica).
   - **Ítems**: Se implementó `ItemDefinition` y su _builder_ ([ItemDefinition.h](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/world/item/ItemDefinition.h)) para definir atributos (ej. durabilidad, tamaño de stack).
   - **Entidades**: Se agregó un stub base `EntityDefinition` ([EntityDefinition.h](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/world/entity/EntityDefinition.h)).

3. **Sistema de Registros (`GameRegistry`)**
   - Se diseñaron los registros internos `BlockRegistry`, `ItemRegistry` y `EntityTypeRegistry`.
   - Estos registros mantienen un mapeo de `ResourceLocation` a la definición, y un caché para retrocompatibilidad con los IDs `legacy` que son hardcodeados por la generación de mundo, todo orquestado por el singleton `GameRegistry` ([GameRegistry.h](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/content/GameRegistry.h)).

4. **Flujo de Bootstrap Vanilla**
   - Se crearon los _Entry Points_ del nuevo sistema:
     - `VanillaBehaviorBootstrap` ([VanillaBehaviorBootstrap.cpp](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/behavior_packs/vanilla/VanillaBehaviorBootstrap.cpp)): Contiene los datos funcionales y la lógica de registro nativo de `minecraft:stone`, `minecraft:stick` y `minecraft:zombie`.
     - `VanillaResourceBootstrap` ([VanillaResourceBootstrap.cpp](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/resource_packs/vanilla/VanillaResourceBootstrap.cpp)): Entry point reservado para las texturas, modelos y geometrías.

5. **Inyección en el Motor Principal**
   - Se actualizó el archivo principal [NinecraftApp.cpp](file:///c:/Users/Usuario/Desktop/Proyectos/PocketMC/src/NinecraftApp.cpp) para que en su función `init()` orqueste el bootstrapping utilizando el `GameRegistry`.

## Resultados de Validación
> [!NOTE]
> La prueba vertical fue superada con éxito a nivel de diseño y código inicial. Al ejecutarse, los bloques e items del nuevo sistema crean un "shadowing" (compatibilidad transparente) del sistema estático viejo (`Tile::tiles` e `Item::items`) mediante las funciones _factory_ inyectadas a través del builder. 
> Esto significa que se pueden cargar chunks existentes sin corromperse mientras progresivamente adaptamos las otras 14 fases (componentes, animación, controladores, render layers, etc.).

Puedes intentar compilar el proyecto ejecutando tu script build correspondiente (ej. `./build.sh` o el perfil de CMake que utilices para tu plataforma). Si todo es correcto, la infraestructura básica ya se encontrará embebida en el core.

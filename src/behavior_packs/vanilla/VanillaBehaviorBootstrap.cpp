/**
 * VanillaBehaviorBootstrap.cpp
 * 
 * Manifiesto de comportamientos del behavior pack vanilla.
 * Este archivo es el punto de entrada que orquesta el registro de todo el 
 * contenido nativo del juego: bloques, ítems y entidades.
 * 
 * Estructura:
 *   - Los bloques se definen en behavior_packs/vanilla/blocks/
 *   - Los ítems se definirán en behavior_packs/vanilla/items/
 *   - Las entidades se definirán en behavior_packs/vanilla/entities/
 * 
 * Análogo conceptual: manifest.json de un Behavior Pack de Bedrock Edition,
 * pero tipado, compilado y sin JSON.
 */
#include "VanillaBehaviorBootstrap.h"

// --- Bloques ---
// Bloques naturales
#include "blocks/stone.h"
#include "blocks/grass.h"
#include "blocks/dirt.h"
#include "blocks/cobblestone.h"
#include "blocks/bedrock.h"
#include "blocks/sand.h"
#include "blocks/gravel.h"
#include "blocks/sandstone.h"
#include "blocks/brick_block.h"
#include "blocks/mossy_cobblestone.h"
#include "blocks/obsidian.h"
#include "blocks/snow_layer.h"
#include "blocks/ice.h"
#include "blocks/snow_block.h"
#include "blocks/clay.h"
#include "blocks/netherrack.h"
#include "blocks/invisible_bedrock.h"
#include "blocks/stonebrick.h"
#include "blocks/nether_brick.h"
#include "blocks/end_stone.h"
#include "blocks/glowing_obsidian.h"
#include "blocks/coal_ore.h"
#include "blocks/iron_ore.h"
#include "blocks/gold_ore.h"
#include "blocks/diamond_ore.h"
#include "blocks/lapis_ore.h"
#include "blocks/lapis_block.h"
#include "blocks/gold_block.h"
#include "blocks/iron_block.h"
#include "blocks/diamond_block.h"
#include "blocks/redstone_ore.h"
#include "blocks/lit_redstone_ore.h"
#include "blocks/quartz_ore.h"
#include "blocks/quartz_block.h"

// Bloques de madera y plantas
#include "blocks/planks.h"
#include "blocks/log.h"
#include "blocks/leaves.h"
#include "blocks/sapling.h"
#include "blocks/log_birch.h"
#include "blocks/log_spruce.h"
#include "blocks/glass.h"
#include "blocks/web.h"
#include "blocks/tallgrass.h"
#include "blocks/wool.h"
#include "blocks/brown_mushroom.h"
#include "blocks/red_mushroom.h"
#include "blocks/reeds.h"
#include "blocks/cactus.h"
#include "blocks/bookshelf.h"
#include "blocks/glass_pane.h"
#include "blocks/fence.h"
#include "blocks/fence_gate.h"
#include "blocks/yellow_flower.h"
#include "blocks/red_flower.h"
#include "blocks/grass_carried.h"
#include "blocks/leaves_carried.h"
#include "blocks/planks_spruce.h"
#include "blocks/planks_birch.h"
#include "blocks/birch_fence.h"
#include "blocks/spruce_fence.h"
#include "blocks/birch_fence_gate.h"
#include "blocks/spruce_fence_gate.h"

// Bloques funcionales
#include "blocks/bed.h"
#include "blocks/torch.h"
#include "blocks/chest.h"
#include "blocks/crafting_table.h"
#include "blocks/furnace.h"
#include "blocks/lit_furnace.h"
#include "blocks/standing_sign.h"
#include "blocks/wooden_door.h"
#include "blocks/ladder.h"
#include "blocks/wall_sign.h"
#include "blocks/iron_door.h"
#include "blocks/trapdoor.h"
#include "blocks/double_stone_slab.h"
#include "blocks/stone_slab.h"
#include "blocks/oak_stairs.h"
#include "blocks/stone_stairs.h"
#include "blocks/brick_stairs.h"
#include "blocks/stone_brick_stairs.h"
#include "blocks/nether_brick_stairs.h"
#include "blocks/sandstone_stairs.h"
#include "blocks/quartz_stairs.h"
#include "blocks/spruce_slab.h"
#include "blocks/spruce_slab_half.h"
#include "blocks/birch_slab.h"
#include "blocks/birch_slab_half.h"
#include "blocks/spruce_stairs.h"
#include "blocks/birch_stairs.h"

// Bloques especiales
#include "blocks/flowing_water.h"
#include "blocks/water.h"
#include "blocks/flowing_lava.h"
#include "blocks/lava.h"
#include "blocks/wheat.h"
#include "blocks/farmland.h"
#include "blocks/melon_block.h"
#include "blocks/melon_stem.h"
#include "blocks/tnt.h"
#include "blocks/fire.h"
#include "blocks/glowstone.h"
#include "blocks/portal.h"
#include "blocks/soul_sand.h"
#include "blocks/stonecutter.h"
#include "blocks/nether_reactor.h"
#include "blocks/info_update.h"
#include "blocks/info_update2.h"
#include "blocks/reserved6.h"
#include "blocks/deepslate.h"
#include "blocks/cobbled_deepslate.h"
#include "blocks/deepslate_coal_ore.h"
#include "blocks/deepslate_diamond_ore.h"
#include "blocks/deepslate_gold_ore.h"
#include "blocks/deepslate_iron_ore.h"
#include "blocks/deepslate_lapis_ore.h"
#include "blocks/deepslate_redstone_ore.h"
#include "blocks/lit_deepslate_redstone_ore.h"
#include "blocks/polished_deepslate.h"
#include "blocks/deepslate_tiles.h"
#include "blocks/deepslate_bricks.h"

// --- Ítems ---
#include "../../world/item/Item.h"

// --- Entidades ---
// #include "entities/VanillaEntities.h" // futuro

void VanillaBehaviorBootstrap::registerContent(GameRegistry& registry) {
    registerBlocks(registry.getBlocks());
    registerItems(registry.getItems());
    registerEntities(registry.getEntities());
}

void VanillaBehaviorBootstrap::registerBlocks(BlockRegistry& blocks) {
    // Bloques naturales
    register_stone(blocks);
    register_grass(blocks);
    register_dirt(blocks);
    register_cobblestone(blocks);
    register_bedrock(blocks);
    register_sand(blocks);
    register_gravel(blocks);
    register_sandstone(blocks);
    register_brick_block(blocks);
    register_mossy_cobblestone(blocks);
    register_obsidian(blocks);
    register_snow_layer(blocks);
    register_ice(blocks);
    register_snow_block(blocks);
    register_clay(blocks);
    register_netherrack(blocks);
    register_invisible_bedrock(blocks);
    register_stonebrick(blocks);
    register_nether_brick(blocks);
    register_end_stone(blocks);
    register_glowing_obsidian(blocks);
    
    // Menas
    register_coal_ore(blocks);
    register_iron_ore(blocks);
    register_gold_ore(blocks);
    register_diamond_ore(blocks);
    register_lapis_ore(blocks);
    register_lapis_block(blocks);
    register_gold_block(blocks);
    register_iron_block(blocks);
    register_diamond_block(blocks);
    register_redstone_ore(blocks);
    register_lit_redstone_ore(blocks);
    register_quartz_ore(blocks);
    register_quartz_block(blocks);

    // Bloques de madera y plantas
    register_planks(blocks);
    register_log(blocks);
    register_leaves(blocks);
    register_sapling(blocks);
    register_log_birch(blocks);
    register_log_spruce(blocks);
    register_glass(blocks);
    register_web(blocks);
    register_tallgrass(blocks);
    register_wool(blocks);
    register_brown_mushroom(blocks);
    register_red_mushroom(blocks);
    register_bookshelf(blocks);
    register_glass_pane(blocks);
    register_fence(blocks);
    register_fence_gate(blocks);
    register_yellow_flower(blocks);
    register_red_flower(blocks);
    register_grass_carried(blocks);
    register_leaves_carried(blocks);
    register_planks_spruce(blocks);
    register_planks_birch(blocks);
    register_birch_fence(blocks);
    register_spruce_fence(blocks);
    register_birch_fence_gate(blocks);
    register_spruce_fence_gate(blocks);

    // Bloques funcionales
    register_bed(blocks);
    register_torch(blocks);
    register_chest(blocks);
    register_crafting_table(blocks);
    register_furnace(blocks);
    register_lit_furnace(blocks);
    register_standing_sign(blocks);
    register_wooden_door(blocks);
    register_ladder(blocks);
    register_wall_sign(blocks);
    register_iron_door(blocks);
    register_trapdoor(blocks);
    register_double_stone_slab(blocks);
    register_stone_slab(blocks);
    register_oak_stairs(blocks);
    register_stone_stairs(blocks);
    register_brick_stairs(blocks);
    register_stone_brick_stairs(blocks);
    register_nether_brick_stairs(blocks);
    register_sandstone_stairs(blocks);
    register_quartz_stairs(blocks);
    register_spruce_slab(blocks);
    register_spruce_slab_half(blocks);
    register_birch_slab(blocks);
    register_birch_slab_half(blocks);
    register_spruce_stairs(blocks);
    register_birch_stairs(blocks);

    // Bloques especiales
    register_flowing_water(blocks);
    register_water(blocks);
    register_flowing_lava(blocks);
    register_lava(blocks);
    register_wheat(blocks);
    register_farmland(blocks);
    register_melon_block(blocks);
    register_melon_stem(blocks);
    register_tnt(blocks);
    register_fire(blocks);
    register_glowstone(blocks);
    register_portal(blocks);
    register_soul_sand(blocks);
    register_stonecutter(blocks);
    register_nether_reactor(blocks);
    register_info_update(blocks);
    register_info_update2(blocks);
    register_reserved6(blocks);
    
    // Deepslate
    register_deepslate(blocks);
    register_cobbled_deepslate(blocks);
    register_deepslate_coal_ore(blocks);
    register_deepslate_diamond_ore(blocks);
    register_deepslate_gold_ore(blocks);
    register_deepslate_iron_ore(blocks);
    register_deepslate_lapis_ore(blocks);
    register_deepslate_redstone_ore(blocks);
    register_lit_deepslate_redstone_ore(blocks);
    register_polished_deepslate(blocks);
    register_deepslate_tiles(blocks);
    register_deepslate_bricks(blocks);
}

void VanillaBehaviorBootstrap::registerItems(ItemRegistry& items) {
    // Los ítems del palo siguen siendo el ejemplo inicial.
    // La migración completa de ítems se realizará en una siguiente fase.
    items.registerItem(
        ItemDefinition::builder(ResourceLocation("minecraft:stick"))
            .legacyId(24)
            .descriptionId("stick")
            .handEquipped(true)
            .factory([](int id) {
                Item* item = new Item(id);
                item->setIcon(5, 3);
                return item;
            })
            .build()
    );
}

void VanillaBehaviorBootstrap::registerEntities(EntityTypeRegistry& entities) {
    entities.registerEntity(
        EntityDefinition::builder(ResourceLocation("minecraft:zombie"))
            .legacyId(32)
            .factory([](int id) { return nullptr; })
            .build()
    );
}

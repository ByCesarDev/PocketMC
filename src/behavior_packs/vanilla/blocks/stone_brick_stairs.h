#pragma once
#include "../../../world/level/tile/StairTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_stone_brick_stairs(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:stone_brick_stairs"))
            .legacyId(109).descriptionId("stairsStoneBrickSmooth")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StairTile(id, Tile::stoneBrickSmooth))->init(); })
            .build()
    );
}

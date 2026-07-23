#pragma once
#include "../../../world/level/tile/StairTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_birch_stairs(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:birch_stairs"))
            .legacyId(162).descriptionId("stairsBirch")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StairTile(id, Tile::birchPlanks))->init(); })
            .build()
    );
}

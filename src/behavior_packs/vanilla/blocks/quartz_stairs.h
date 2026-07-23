#pragma once
#include "../../../world/level/tile/StairTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_quartz_stairs(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:quartz_stairs"))
            .legacyId(156).descriptionId("stairsQuartz")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StairTile(id, Tile::quartzBlock))->init(); })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/StairTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_spruce_stairs(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:spruce_stairs"))
            .legacyId(161).descriptionId("stairsSpruce")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StairTile(id, Tile::sprucePlanks))->init(); })
            .build()
    );
}

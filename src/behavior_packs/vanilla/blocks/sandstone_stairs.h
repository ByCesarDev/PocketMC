#pragma once
#include "../../../world/level/tile/StairTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_sandstone_stairs(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:sandstone_stairs"))
            .legacyId(128).descriptionId("stairsSandStone")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StairTile(id, Tile::sandStone))->init(); })
            .build()
    );
}

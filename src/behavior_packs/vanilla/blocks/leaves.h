#pragma once
#include "../../../world/level/tile/LeafTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_leaves(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:leaves"))
            .legacyId(18).descriptionId("leaves")
            .destroyTime(0.2f).lightBlock(1)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new LeafTile(id, 4 + 3 * 16))->init(); })
            .build()
    );
}

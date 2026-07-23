#pragma once
#include "../../../world/level/tile/LeafTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_leaves_carried(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:leaves_carried"))
            .legacyId(254).descriptionId("leaves")
            .destroyTime(0.2f).lightBlock(1)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new LeafTile(id, 11 + 14 * 16))->init(); })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/FenceTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_birch_fence(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:birch_fence"))
            .legacyId(163).descriptionId("fenceBirch")
            .destroyTime(2.0f).explosionResistance(5)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new FenceTile(id, 5 | Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/FenceGateTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_birch_fence_gate(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:birch_fence_gate"))
            .legacyId(165).descriptionId("fenceGateBirch")
            .destroyTime(2.0f).explosionResistance(5)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new FenceGateTile(id, 5 | Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}

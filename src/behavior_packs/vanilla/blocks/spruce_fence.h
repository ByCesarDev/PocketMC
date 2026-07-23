#pragma once
#include "../../../world/level/tile/FenceTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_spruce_fence(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:spruce_fence"))
            .legacyId(164).descriptionId("fenceSpruce")
            .destroyTime(2.0f).explosionResistance(5)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new FenceTile(id, 4 | Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}

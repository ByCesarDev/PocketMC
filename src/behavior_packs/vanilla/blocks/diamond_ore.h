#pragma once
#include "../../../world/level/tile/OreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_diamond_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:diamond_ore"))
            .legacyId(56).descriptionId("oreDiamond")
            .destroyTime(3.0f).explosionResistance(5)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new OreTile(id, 16 * 3 + 2))->init(); })
            .build()
    );
}

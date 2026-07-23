#pragma once
#include "../../../world/level/tile/OreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_lapis_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:lapis_ore"))
            .legacyId(21).descriptionId("oreLapis")
            .destroyTime(3.0f).explosionResistance(5)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new OreTile(id, 10 * 16))->init(); })
            .build()
    );
}

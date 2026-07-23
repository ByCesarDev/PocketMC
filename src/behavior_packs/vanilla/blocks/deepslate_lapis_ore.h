#pragma once
#include "../../../world/level/tile/OreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_deepslate_lapis_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:deepslate_lapis_ore"))
            .legacyId(176).descriptionId("deepslateOreLapis")
            .destroyTime(3.0f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new OreTile(id, 12 | Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}

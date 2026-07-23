#pragma once
#include "../../../world/level/tile/RedStoneOreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_deepslate_redstone_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:deepslate_redstone_ore"))
            .legacyId(177).descriptionId("deepslateOreRedstone")
            .destroyTime(3.0f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Mechanisms)
            .factory([](int id) { return (new RedStoneOreTile(id, 13 | Tile::TEXTURE_ALT_FLAG, false))->init(); })
            .build()
    );
}

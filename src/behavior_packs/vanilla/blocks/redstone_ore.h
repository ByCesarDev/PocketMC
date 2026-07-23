#pragma once
#include "../../../world/level/tile/RedStoneOreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_redstone_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:redstone_ore"))
            .legacyId(73).descriptionId("oreRedstone")
            .destroyTime(3.0f).explosionResistance(5)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Mechanisms)
            .factory([](int id) { return (new RedStoneOreTile(id, 16 * 3 + 3, false))->init(); })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/OreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_iron_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:iron_ore"))
            .legacyId(15).descriptionId("oreIron")
            .destroyTime(3.0f).explosionResistance(5)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new OreTile(id, 33))->init(); })
            .build()
    );
}

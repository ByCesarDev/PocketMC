#pragma once
#include "../../../world/level/tile/OreTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_coal_ore(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:coal_ore"))
            .legacyId(16).descriptionId("oreCoal")
            .destroyTime(3.0f).explosionResistance(5)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new OreTile(id, 34))->init(); })
            .build()
    );
}

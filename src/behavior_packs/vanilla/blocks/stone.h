#pragma once
#include "../../../world/level/tile/StoneTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_stone(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:stone"))
            .legacyId(1).descriptionId("stone")
            .destroyTime(1.5f).explosionResistance(10)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StoneTile(id, 1))->init(); })
            .build()
    );
}

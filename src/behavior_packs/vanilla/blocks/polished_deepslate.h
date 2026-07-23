#pragma once
#include "../../../world/level/tile/DeepslateTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_polished_deepslate(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:polished_deepslate"))
            .legacyId(181).descriptionId("deepslatePolished")
            .destroyTime(1.5f).explosionResistance(6.0f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new PolishedDeepslateTile(id))->init(); })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/MetalTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_gold_block(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:gold_block"))
            .legacyId(41).descriptionId("blockGold")
            .destroyTime(3.0f).explosionResistance(10)
            .soundType(Tile::SOUND_METAL)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new MetalTile(id, 39 - 16))->init(); })
            .build()
    );
}

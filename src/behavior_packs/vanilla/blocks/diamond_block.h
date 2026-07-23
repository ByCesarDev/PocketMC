#pragma once
#include "../../../world/level/tile/MetalTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_diamond_block(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:diamond_block"))
            .legacyId(57).descriptionId("blockDiamond")
            .destroyTime(5.0f).explosionResistance(10)
            .soundType(Tile::SOUND_METAL)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new MetalTile(id, 40 - 16))->init(); })
            .build()
    );
}

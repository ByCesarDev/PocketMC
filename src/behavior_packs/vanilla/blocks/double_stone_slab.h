#pragma once
#include "../../../world/level/tile/StoneSlabTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_double_stone_slab(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:double_stone_slab"))
            .legacyId(43).descriptionId("stoneSlab")
            .destroyTime(2.0f).explosionResistance(10)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StoneSlabTile(id, true))->init(); })
            .build()
    );
}

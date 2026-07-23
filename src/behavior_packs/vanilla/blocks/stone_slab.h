#pragma once
#include "../../../world/level/tile/StoneSlabTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_stone_slab(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:stone_slab"))
            .legacyId(44).descriptionId("stoneSlab")
            .destroyTime(2.0f).explosionResistance(10)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StoneSlabTile(id, false))->init(); })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/ClothTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_wool(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:wool"))
            .legacyId(35).descriptionId("cloth")
            .destroyTime(0.8f)
            .soundType(Tile::SOUND_CLOTH)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new ClothTile(id))->init(); })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/CropTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_wheat(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:wheat"))
            .legacyId(59).descriptionId("crops")
            .destroyTime(0.0f)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new CropTile(id, 8 + 5 * 16))->init(); })
            .build()
    );
}

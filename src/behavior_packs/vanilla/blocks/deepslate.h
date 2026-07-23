#pragma once
#include "../../../world/level/tile/DeepslateTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_deepslate(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:deepslate"))
            .legacyId(170).descriptionId("deepslate")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new DeepslateTile(id, 6 | Tile::TEXTURE_ALT_FLAG, 171))->init(); })
            .build()
    );
}

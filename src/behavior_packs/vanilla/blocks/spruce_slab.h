#pragma once
#include "../../../world/level/tile/Tile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_spruce_slab(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:spruce_slab"))
            .legacyId(157).descriptionId("spruceSlab")
            .destroyTime(2.0f).explosionResistance(5.0f / 3.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new Tile(id, 4 | Tile::TEXTURE_ALT_FLAG, Material::wood))->init(); })
            .build()
    );
}

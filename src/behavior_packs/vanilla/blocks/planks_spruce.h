#pragma once
#include "../../../world/level/tile/Tile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_planks_spruce(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:planks_spruce"))
            .legacyId(150).descriptionId("planksSpruce")
            .destroyTime(2.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new Tile(id, 4 | Tile::TEXTURE_ALT_FLAG, Material::wood))->init(); })
            .build()
    );
}

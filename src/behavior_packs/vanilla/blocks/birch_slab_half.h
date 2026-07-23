#pragma once
#include "../../../world/level/tile/Tile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_birch_slab_half(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:birch_slab_half"))
            .legacyId(160).descriptionId("birchSlab")
            .destroyTime(2.0f).explosionResistance(5.0f / 3.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) {
                Tile* t = (new Tile(id, 5 | Tile::TEXTURE_ALT_FLAG, Material::wood))->init();
                t->setShape(0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f);
                return t;
            })
            .build()
    );
}

#pragma once
#include "../../../world/level/tile/MultiTextureTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

static const int STONE_BRICK_TEXTURES_ARR[] = { 6 + 16 * 3, 4 + 16 * 6, 5 + 16 * 6 };

inline void register_stonebrick(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:stonebrick"))
            .legacyId(98).descriptionId("stonebricksmooth")
            .destroyTime(1.5f).explosionResistance(10)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) {
                return (new MultiTextureTile(id, (const int*)&STONE_BRICK_TEXTURES_ARR, 3, Material::stone))->init();
            })
            .build()
    );
}

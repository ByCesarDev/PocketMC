#pragma once
#include "../../../world/level/tile/LightGemTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_glowstone(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:glowstone"))
            .legacyId(89).descriptionId("lightgem")
            .destroyTime(0.3f).lightEmission(16)
            .soundType(Tile::SOUND_GLASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new LightGemTile(id, 9 + 16 * 6, Material::glass))->init(); })
            .build()
    );
}

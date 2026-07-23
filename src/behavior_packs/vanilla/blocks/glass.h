#pragma once
#include "../../../world/level/tile/GlassTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_glass(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:glass"))
            .legacyId(20).descriptionId("glass")
            .destroyTime(0.3f)
            .soundType(Tile::SOUND_GLASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new GlassTile(id, 49, Material::glass, false))->init(); })
            .build()
    );
}

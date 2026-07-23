#pragma once
#include "../../../world/level/tile/ThinFenceTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_glass_pane(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:glass_pane"))
            .legacyId(102).descriptionId("thinGlass")
            .destroyTime(0.3f)
            .soundType(Tile::SOUND_GLASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new ThinFenceTile(id, 1 + 3 * 16, 4 + 9 * 16, Material::glass, false))->init(); })
            .build()
    );
}

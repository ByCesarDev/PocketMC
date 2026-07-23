#pragma once
#include "../../../world/level/tile/Tile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_info_update2(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:info_update2"))
            .legacyId(249).descriptionId("info_update")
            .destroyTime(1.0f)
            .soundType(Tile::SOUND_GRAVEL)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new Tile(id, 253, Material::dirt))->init(); })
            .build()
    );
}

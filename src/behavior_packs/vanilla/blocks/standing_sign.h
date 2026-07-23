#pragma once
#include "../../../world/level/tile/SignTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/tile/entity/TileEntity.h"
#include "../../../world/item/ItemCategory.h"

inline void register_standing_sign(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:standing_sign"))
            .legacyId(63).descriptionId("sign")
            .destroyTime(1.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new SignTile(id, TileEntityType::Sign, true))->init(); })
            .build()
    );
}

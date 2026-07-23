#pragma once
#include "../../../world/level/tile/CactusTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_cactus(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:cactus"))
            .legacyId(81).descriptionId("cactus")
            .destroyTime(0.4f)
            .soundType(Tile::SOUND_CLOTH)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new CactusTile(id, 16 * 4 + 6))->init(); })
            .build()
    );
}

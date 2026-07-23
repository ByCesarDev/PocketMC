#pragma once
#include "../../../world/level/tile/TorchTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_torch(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:torch"))
            .legacyId(50).descriptionId("torch")
            .destroyTime(0.0f).lightEmission(15)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Tools)
            .factory([](int id) { return (new TorchTile(id, 5 * 16))->init(); })
            .build()
    );
}

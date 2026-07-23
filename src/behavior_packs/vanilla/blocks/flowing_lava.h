#pragma once
#include "../../../world/level/tile/LiquidTileDynamic.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_flowing_lava(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:flowing_lava"))
            .legacyId(10).descriptionId("lava")
            .destroyTime(100.0f).lightEmission(16).lightBlock(255)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new LiquidTileDynamic(id, Material::lava))->init(); })
            .build()
    );
}

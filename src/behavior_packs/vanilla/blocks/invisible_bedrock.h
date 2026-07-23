#pragma once
#include "../../../world/level/tile/InvisibleTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"

inline void register_invisible_bedrock(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:invisible_bedrock"))
            .legacyId(95).descriptionId("bedrock")
            .destroyTime(-1).explosionResistance(6000000)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new InvisibleTile(id, 0, Material::stone))->init(); })
            .build()
    );
}

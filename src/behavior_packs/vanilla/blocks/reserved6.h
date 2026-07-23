#pragma once
#include "../../../world/level/tile/Tile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"

inline void register_reserved6(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:reserved6"))
            .legacyId(255).descriptionId("reserved6")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new Tile(id, Material::dirt))->init(); })
            .build()
    );
}

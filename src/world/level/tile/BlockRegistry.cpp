#include "BlockRegistry.h"
#include "Tile.h"
#include "../../../util/StringUtils.h" // Might not exist but assuming we have basic log

void BlockRegistry::registerBlock(const BlockDefinition& def) {
    blocks.push_back(def);
    size_t index = blocks.size() - 1;
    byId[def.id] = index;
    if (def.legacyId != -1) {
        byLegacyId[def.legacyId] = index;
    }

    if (def.factory && def.legacyId != -1) {
        // Instantiate the Tile and put it in Tile::tiles for backwards compatibility
        Tile* tile = def.factory(def.legacyId);
        tile->setDescriptionId(def.descriptionId)
            ->setDestroyTime(def.destroyTime)
            ->setExplodeable(def.explosionResistance)
            ->setSoundType(*def.soundType);
        
        // Setup light emission/block
        // Assuming Tile::lightBlock and Tile::lightEmission exist
        Tile::lightBlock[def.legacyId] = def.lightBlock;
        Tile::lightEmission[def.legacyId] = def.lightEmission;

        instantiatedTiles[def.legacyId] = tile;
        Tile::tiles[def.legacyId] = tile;
    }
}

const BlockDefinition* BlockRegistry::getBlock(const ResourceLocation& id) const {
    auto it = byId.find(id);
    if (it != byId.end()) {
        return &blocks[it->second];
    }
    return nullptr;
}

const BlockDefinition* BlockRegistry::getBlock(int legacyId) const {
    auto it = byLegacyId.find(legacyId);
    if (it != byLegacyId.end()) {
        return &blocks[it->second];
    }
    return nullptr;
}

Tile* BlockRegistry::getTile(const ResourceLocation& id) const {
    const BlockDefinition* def = getBlock(id);
    if (def && def->legacyId != -1) {
        return getTile(def->legacyId);
    }
    return nullptr;
}

Tile* BlockRegistry::getTile(int legacyId) const {
    auto it = instantiatedTiles.find(legacyId);
    if (it != instantiatedTiles.end()) {
        return it->second;
    }
    return nullptr;
}

#pragma once

#include "Tile.h"
#include "../../../util/ResourceLocation.h"
#include <string>
#include <memory>
#include <functional>

class BlockDefinitionBuilder;

class BlockDefinition {
public:
    ResourceLocation id;
    int legacyId;
    std::string descriptionId;
    float destroyTime = 0.0f;
    float explosionResistance = 0.0f;
    const Tile::SoundType* soundType = &Tile::SOUND_STONE;
    int creativeCategory = 0;
    int lightEmission = 0;
    int lightBlock = 0;
    std::function<Tile*(int)> factory;

    BlockDefinition(const ResourceLocation& id) : id(id), legacyId(-1) {}

    static BlockDefinitionBuilder builder(const ResourceLocation& id);
};

class BlockDefinitionBuilder {
    BlockDefinition def;
public:
    BlockDefinitionBuilder(const ResourceLocation& id) : def(id) {}

    BlockDefinitionBuilder& legacyId(int id) { def.legacyId = id; return *this; }
    BlockDefinitionBuilder& descriptionId(const std::string& descId) { def.descriptionId = descId; return *this; }
    BlockDefinitionBuilder& destroyTime(float time) { def.destroyTime = time; return *this; }
    BlockDefinitionBuilder& explosionResistance(float res) { def.explosionResistance = res; return *this; }
    BlockDefinitionBuilder& soundType(const Tile::SoundType& sound) { def.soundType = &sound; return *this; }
    BlockDefinitionBuilder& creativeCategory(int category) { def.creativeCategory = category; return *this; }
    BlockDefinitionBuilder& lightEmission(int emission) { def.lightEmission = emission; return *this; }
    BlockDefinitionBuilder& lightBlock(int block) { def.lightBlock = block; return *this; }
    
    BlockDefinitionBuilder& factory(std::function<Tile*(int)> f) { def.factory = f; return *this; }

    BlockDefinition build() const {
        return def;
    }
};

inline BlockDefinitionBuilder BlockDefinition::builder(const ResourceLocation& id) {
    return BlockDefinitionBuilder(id);
}

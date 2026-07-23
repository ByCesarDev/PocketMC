#pragma once

#include "Entity.h"
#include "../../util/ResourceLocation.h"
#include <string>
#include <memory>
#include <functional>

class EntityDefinitionBuilder;

class EntityDefinition {
public:
    ResourceLocation id;
    int legacyId;
    std::function<Entity*(int)> factory; // Temporary until full decoupling

    EntityDefinition(const ResourceLocation& id) : id(id), legacyId(-1) {}

    static EntityDefinitionBuilder builder(const ResourceLocation& id);
};

class EntityDefinitionBuilder {
    EntityDefinition def;
public:
    EntityDefinitionBuilder(const ResourceLocation& id) : def(id) {}

    EntityDefinitionBuilder& legacyId(int id) { def.legacyId = id; return *this; }
    EntityDefinitionBuilder& factory(std::function<Entity*(int)> f) { def.factory = f; return *this; }

    EntityDefinition build() const {
        return def;
    }
};

inline EntityDefinitionBuilder EntityDefinition::builder(const ResourceLocation& id) {
    return EntityDefinitionBuilder(id);
}

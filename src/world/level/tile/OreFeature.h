#ifndef NET_MINECRAFT_WORLD_LEVEL_LEVELGEN_FEATURE__OreFeature_H__
#define NET_MINECRAFT_WORLD_LEVEL_LEVELGEN_FEATURE__OreFeature_H__

#include "Feature.h"

class OreFeature : public Feature {
public:
    int oreTileId;
    int count;

    OreFeature(int oreTileId, int count) : oreTileId(oreTileId), count(count) {}

    virtual bool place(Level* level, Random* random, int x, int y, int z) override;
};

#endif /* NET_MINECRAFT_WORLD_LEVEL_LEVELGEN_FEATURE__OreFeature_H__ */
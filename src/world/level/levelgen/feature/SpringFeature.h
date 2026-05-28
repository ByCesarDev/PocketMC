#ifndef NET_MINECRAFT_WORLD_LEVEL_LEVELGEN_FEATURE__SpringFeature_H__
#define NET_MINECRAFT_WORLD_LEVEL_LEVELGEN_FEATURE__SpringFeature_H__

//package net.minecraft.world.level.levelgen.feature;

#include "Feature.h"
#include "../../Level.h"
#include "../../tile/Tile.h"
#include "../../material/Material.h"
#include "../../../../util/Random.h"

class SpringFeature: public Feature
{
    int tile;

public:
    SpringFeature(int tile) {
        this->tile = tile;
    }

    bool place(Level* level, Random* random, int x, int y, int z) {
        int tileAbove = level->getTile(x, y + 1, z);
        if (tileAbove != Tile::rock->id && tileAbove != Tile::deepslate->id) return false;
        
        int tileBelow = level->getTile(x, y - 1, z);
        if (tileBelow != Tile::rock->id && tileBelow != Tile::deepslate->id) return false;

        int currentTile = level->getTile(x, y, z);
        if (currentTile != 0 && currentTile != Tile::rock->id && currentTile != Tile::deepslate->id) return false;

        int rockCount = 0;
        int t;
        t = level->getTile(x - 1, y, z); if (t == Tile::rock->id || t == Tile::deepslate->id) rockCount++;
        t = level->getTile(x + 1, y, z); if (t == Tile::rock->id || t == Tile::deepslate->id) rockCount++;
        t = level->getTile(x, y, z - 1); if (t == Tile::rock->id || t == Tile::deepslate->id) rockCount++;
        t = level->getTile(x, y, z + 1); if (t == Tile::rock->id || t == Tile::deepslate->id) rockCount++;

        int holeCount = 0;
        if (level->isEmptyTile(x - 1, y, z)) holeCount++;
        if (level->isEmptyTile(x + 1, y, z)) holeCount++;
        if (level->isEmptyTile(x, y, z - 1)) holeCount++;
        if (level->isEmptyTile(x, y, z + 1)) holeCount++;

        if (rockCount == 3 && holeCount == 1) {
            level->setTile(x, y, z, tile);
            level->instaTick = true;
            Tile::tiles[tile]->tick(level, x, y, z, random);
            level->instaTick = false;
        }

        return true;
    }
};

#endif /*NET_MINECRAFT_WORLD_LEVEL_LEVELGEN_FEATURE__SpringFeature_H__*/

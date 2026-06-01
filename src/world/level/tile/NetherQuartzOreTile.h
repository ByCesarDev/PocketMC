#ifndef NET_MINECRAFT_WORLD_LEVEL_TILE__NetherQuartzOreTile_H__
#define NET_MINECRAFT_WORLD_LEVEL_TILE__NetherQuartzOreTile_H__

#include "Tile.h"
#include "../material/Material.h"
#include "../../item/Item.h"
#include "../../../util/Random.h"

class NetherQuartzOreTile : public Tile {
    typedef Tile super;
public:
    NetherQuartzOreTile(int id, int tex) : Tile(id, tex, Material::stone) {}

    int getResource(int data, Random* random) override {
        return Item::netherQuartz->id;
    }

    int getResourceCount(Random* random) override {
        return 1 + random->nextInt(3); // Drops 1-3 quartz
    }
};

#endif /*NET_MINECRAFT_WORLD_LEVEL_TILE__NetherQuartzOreTile_H__*/

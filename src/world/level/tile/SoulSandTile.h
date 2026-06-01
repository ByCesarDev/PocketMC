#ifndef NET_MINECRAFT_WORLD_LEVEL_TILE__SoulSandTile_H__
#define NET_MINECRAFT_WORLD_LEVEL_TILE__SoulSandTile_H__

#include "Tile.h"
#include "../material/Material.h"
#include "../../phys/AABB.h"

class SoulSandTile : public Tile {
    typedef Tile super;
public:
    SoulSandTile(int id, int tex) : Tile(id, tex, Material::sand) {
        friction = 0.55f;
    }

    AABB* getAABB(Level* level, int x, int y, int z) override {
        float r = 0.125f; // 2/16 of a block
        tmpBB.x0 = x;
        tmpBB.y0 = y;
        tmpBB.z0 = z;
        tmpBB.x1 = x + 1;
        tmpBB.y1 = y + 1 - r;
        tmpBB.z1 = z + 1;
        return &tmpBB;
    }
};

#endif /*NET_MINECRAFT_WORLD_LEVEL_TILE__SoulSandTile_H__*/

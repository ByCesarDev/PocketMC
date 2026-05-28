#pragma once

#include "StoneTile.h"

class DeepslateTile : public Tile {
public:
    DeepslateTile(int id, int tex) : Tile(id, tex, Material::stone) {
        
    }
};

class PolishedDeepslateTile : public StoneTile {
public:
    PolishedDeepslateTile(int id) : StoneTile(id, 18 | Tile::TEXTURE_ALT_FLAG) {
        setDescriptionId("polished_deepslate");
    }
};

class DeepslateTilesTile : public StoneTile {
public:
    DeepslateTilesTile(int id) : StoneTile(id, 19 | Tile::TEXTURE_ALT_FLAG) {
        setDescriptionId("deepslate_tiles");
    }
};

class DeepslateBricksTile : public StoneTile {
public:
    DeepslateBricksTile(int id) : StoneTile(id, 20 | Tile::TEXTURE_ALT_FLAG) {
        setDescriptionId("deepslate_bricks");
    }
};

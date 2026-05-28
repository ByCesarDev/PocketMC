#pragma once

#include "StoneTile.h"

class PolishedDeepslateTile : public StoneTile {
public:
    PolishedDeepslateTile(int id) : StoneTile(id) {
        tex = 2 * 16 + 1; // Texture from terrain2.png
        setNameId("polished_deepslate");
    }
};

class DeepslateTilesTile : public StoneTile {
public:
    DeepslateTilesTile(int id) : StoneTile(id) {
        tex = 3 * 16 + 1; // Texture from terrain2.png
        setNameId("deepslate_tiles");
    }
};

class DeepslateBricksTile : public StoneTile {
public:
    DeepslateBricksTile(int id) : StoneTile(id) {
        tex = 4 * 16 + 1; // Texture from terrain2.png
        setNameId("deepslate_bricks");
    }
};

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Serializable.hpp"

struct TileChange {
    int x, y;
    int newTileID;
};

struct Tile {
    int baseTileID;
    int currentTileID;
    bool discovered;
    bool occupied;

    Tile(int id = 0) : baseTileID(id), currentTileID(id), discovered(false), occupied(false) {}
};

class Map : public Serializable {
private:
    int width = 0;
    int height = 0;
    std::vector<std::vector<Tile>> tiles;
public:
    bool loadFromFile(const std::string& filename);
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    Tile& getTile(int x, int y);
    void setTile(int x, int y, int newTileID);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void exibirMapa() const;
};
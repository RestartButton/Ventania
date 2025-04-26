#include <iostream>
#include <fstream>
#include <sstream>
#include "Map.hpp"

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    tiles.clear();
    width = 0;
    height = 0;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<Tile> row;
        int tileID;
        while (ss >> tileID) {
            row.emplace_back(tileID);
        }
        if (row.size() > 0) {
            if (width == 0) {
                width = static_cast<int>(row.size());
            }
            tiles.push_back(row);
        }
    }

    height = static_cast<int>(tiles.size());
    file.close();
    return true;
}

Tile& Map::getTile(int x, int y) {
    if(x >= 0 && y >= 0) {
        if(x < width && y < height) {
            return tiles[y][x];
        }
    }
    throw "Out of Bounds";
}

void Map::setTile(int x, int y, int newTileID) {
    tiles[y][x].currentTileID = newTileID;
}

void Map::save(std::ostream& out) const {
    // Salvar width e height
    out.write(reinterpret_cast<const char*>(&width), sizeof(width));
    out.write(reinterpret_cast<const char*>(&height), sizeof(height));

    // Salvar todos os tiles
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            out.write(reinterpret_cast<const char*>(&tile.baseTileID), sizeof(tile.baseTileID));
            out.write(reinterpret_cast<const char*>(&tile.currentTileID), sizeof(tile.currentTileID));
            out.write(reinterpret_cast<const char*>(&tile.discovered), sizeof(tile.discovered));
            out.write(reinterpret_cast<const char*>(&tile.occupied), sizeof(tile.occupied));
        }
    }
}

void Map::load(std::istream& in) {
    // Ler width e height
    in.read(reinterpret_cast<char*>(&width), sizeof(width));
    in.read(reinterpret_cast<char*>(&height), sizeof(height));

    tiles.clear();
    tiles.resize(height, std::vector<Tile>(width));

    // Ler todos os tiles
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tile& tile = tiles[y][x];
            in.read(reinterpret_cast<char*>(&tile.baseTileID), sizeof(tile.baseTileID));
            in.read(reinterpret_cast<char*>(&tile.currentTileID), sizeof(tile.currentTileID));
            in.read(reinterpret_cast<char*>(&tile.discovered), sizeof(tile.discovered));
            in.read(reinterpret_cast<char*>(&tile.occupied), sizeof(tile.occupied));
        }
    }
}

void Map::exibirMapa() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << tiles[y][x].currentTileID << "\t";
        }
        std::cout << "\n";
    }
}
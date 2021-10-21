#pragma once

#include <vector>
#include <iostream>
#include <fstream>


namespace Cinder {
  enum class MapTypes {
    WORLD_MAP,
    LOCATION_MAP
  };

  struct Map {
    MapTypes mapType;
    uint32_t width;
    uint32_t height;
    std::vector<std::vector<uint8_t>> map;
    void save(std::string filePath) {
        using namespace std;
        ofstream outFile(filePath, ios::out|ios::binary);
        outFile.write((char*)&mapType, sizeof(MapTypes));
        outFile.write((char*)&width, sizeof(width));
        outFile.write((char*)&height, sizeof(height));

        for(auto & row : map) {
            outFile.write((char*)row.data(), width);
        }

        outFile.flush();
        outFile.close();

    }
  };

  enum class Biomes {
      WATER = 0,
      FIELD,
      FOREST,
      ROCK,
      HIGH_ROCK,
      GLACIER,
      SWAMP,
      DESERT,
      SAVANNA,
  };

  enum class TileBorder {
      NONE = 0,
      LEFT,
      RIGHT,
      TOP,
      BOTTOM
  };

  struct Biom {
      Biomes biomType;
      bool hasSnow;
      //uint8 hasRiver;
      TileBorder riverEntry;
      TileBorder riverExit;

      Biom(Biomes biomType){
          this->biomType = biomType;
      }
  };

  struct Village {
      float x;
      float y;
      uint8_t population;
  };
} // namespace Cinder


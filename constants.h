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

  enum class LocationTiles {
      WATER = 0,
      GRAVEL,
      GROUND,
      GRASS,
      SAND,
      ROCK,
      LAVA,
      ICE,
      SNOW,
      DIRT
  };

    enum class NaturalObjects {

        TREE_BEGIN = 0,
        OAK = TREE_BEGIN,
        MAPLE,
        SAKURA,
        PINE,
        MAHOGANY,
        PALM,
        COCOA,
        TREE_END,

        BUSH_BEGIN,
        HOPS = BUSH_BEGIN,
        GRAPE,
        LILAC,
        WEED,
        BUSH_END,

        VEGETABLES_BEGIN,
        POTATO = VEGETABLES_BEGIN,
        CARROT,
        CABBAGE,
        SUNFLOWER,
        VEGETABLES_END,

        MASHROOMS_BEGIN,
        BOLETUS = MASHROOMS_BEGIN,
        FLY_AGARIC,
        SHROOMS,
        MASHROOMS_END,

        ORES_BEGIN,
        STONE=ORES_BEGIN,
        COAL,
        DIAMOND,
        IRON,
        COPPER,
        COFFEE,
        SAND,
        GROUND,
        CINDER, //Something like Spice from Dune
        ORES_END
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


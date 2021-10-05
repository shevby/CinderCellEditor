#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>


namespace Cinder {
  enum class MapTypes {
    WORLD_MAP,
    CELL_MAP
  };

  struct Map {
    MapTypes mapType;
    uint32_t width;
    uint32_t height;
    uint8_t * map;
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



#endif // CONSTANTS_H

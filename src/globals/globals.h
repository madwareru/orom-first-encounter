#ifndef GLOBALS_H
#define GLOBALS_H

#include <cstdint>

#define MAX_ALTITUDE 255
#define STANDART_TILE_HEIGHT 32

#define MAX_COLUMN_HEIGHT (MAX_ALTITUDE + STANDART_TILE_HEIGHT)

/*
  MAX_COLUMN_HEIGHT times of repetitions for each pixel of a tile column
  in other words it looks like that:

  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00
  01 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00
  01 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 00  00 00 00 01
  ...
  01 00 01 00  01 00 01 00  01 00 01 00  01 00 01 00  01 00 01 00  01 00 01 00  01 00 01 00  01 00 00 01
  ...
  01 01 01 01  01 01 01 01  01 01 01 01  01 01 01 01  01 01 01 01  01 01 01 01  01 01 01 01  01 01 01 01
  ...
  08 08 08 08  08 08 08 08  08 08 08 08  08 08 08 08  08 08 08 08  08 08 08 08  08 08 08 08  08 08 08 08
  ...
  09 09 09 09  09 09 09 09  09 09 09 09  09 09 09 08  09 09 09 09  09 09 09 09  09 09 09 09  09 09 09 09
*/
extern uint8_t height_scaler_lookup[STANDART_TILE_HEIGHT * (MAX_COLUMN_HEIGHT + 1)];

void init_height_scaler_lookup();

#define ACQUIRE_HEIGHT_SCALER(x) &height_scaler_lookup[STANDART_TILE_HEIGHT * (x)]


#endif // GLOBALS_H

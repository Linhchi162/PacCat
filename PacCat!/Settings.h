#pragma once
#ifndef _SETTINGS_HEADER_INCLUDED_
#define _SETTINGS_HEADER_INCLUDED_
 // negative => the number of dots on map. Change this value to a positive int to 
// explicitly set the amount of score to be required for winning.

const unsigned COLLIDER_BOX_SIZE = 20; // these collider boxes are used for Pacman/Ghosts colliding logic

const int tilesCountX = 19, tilesCountY = 19;
const unsigned TILE_SIZE = 32;// Textures are 32x32p. Having higher tile size will decrease quality and might affect speeds.
const unsigned HALF_TILE_SIZE = TILE_SIZE / 2;
const unsigned WINDOW_WIDTH = tilesCountX * TILE_SIZE;
const unsigned WINDOW_HEIGHT = tilesCountY * TILE_SIZE;
const unsigned PACMAN_START_XPOS = 9 *TILE_SIZE;
const unsigned PACMAN_START_YPOS = 12 * TILE_SIZE;


const int pacmanSpeed = 2;



#endif


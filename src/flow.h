#pragma once
#include <stdbool.h>
#include <stdio.h>

struct point{
	char group; //Group 0 is reserved for empty space
	bool is_node; //If true, this makes the point a node 
};

struct grid{
	struct point **map;
	int height;
	int width;
};

struct grid load(FILE* f);

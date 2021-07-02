#pragma once

#include "rectangle.h"

Rec::Rec()
	: x{ 0 }, y{ 0 }, color{ BLACK }, outline_color{ BLACK } {}

Rec::Rec(int x, int y, Color color, Color outline_color) // Color color = BLACK, Color outline_color = BLACK
	: x{ x }, y{ y }, color{ color }, outline_color{ outline_color } {}

#include "figures.h"

const Figure Figures::o{ std::array<Rec, 4>{{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } }}, figure_enum::O, YELLOW };
const Figure Figures::i{ std::array<Rec, 4>{{ { 0,-2 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }}, figure_enum::I, SKYBLUE };
const Figure Figures::s{ std::array<Rec, 4>{{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1,-1 } }}, figure_enum::S, RED };
const Figure Figures::z{ std::array<Rec, 4>{{ {-1,-1 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }}, figure_enum::Z, GREEN };
const Figure Figures::l{ std::array<Rec, 4>{{ { 0,-1 }, { 0, 0 }, { 0, 1 }, { 1, 1 } }}, figure_enum::L, ORANGE };
const Figure Figures::j{ std::array<Rec, 4>{{ {-1, 1 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }}, figure_enum::J, PINK };
const Figure Figures::t{ std::array<Rec, 4>{{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }}, figure_enum::T, PURPLE };
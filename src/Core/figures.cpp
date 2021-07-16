#include "figures.h"

const Figure Figures::o{ std::array<Rec, 4>{{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } }}, FigureEnum::O, YELLOW };
const Figure Figures::i{ std::array<Rec, 4>{{ { 0,-2 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }}, FigureEnum::I, SKYBLUE };
const Figure Figures::s{ std::array<Rec, 4>{{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1,-1 } }}, FigureEnum::S, RED };
const Figure Figures::z{ std::array<Rec, 4>{{ {-1,-1 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }}, FigureEnum::Z, GREEN };
const Figure Figures::l{ std::array<Rec, 4>{{ { 0,-1 }, { 0, 0 }, { 0, 1 }, { 1, 1 } }}, FigureEnum::L, ORANGE };
const Figure Figures::j{ std::array<Rec, 4>{{ {-1, 1 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }}, FigureEnum::J, PINK };
const Figure Figures::t{ std::array<Rec, 4>{{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }}, FigureEnum::T, PURPLE };
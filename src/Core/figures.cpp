#include "figures.h"

Figure Figures::o{ std::vector<Rec>{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } }, FigureEnum::O, YELLOW };
Figure Figures::i{ std::vector<Rec>{ { 0,-2 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }, FigureEnum::I, SKYBLUE };
Figure Figures::s{ std::vector<Rec>{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1,-1 } }, FigureEnum::S, RED };
Figure Figures::z{ std::vector<Rec>{ {-1,-1 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }, FigureEnum::Z, GREEN };
Figure Figures::l{ std::vector<Rec>{ { 0,-1 }, { 0, 0 }, { 0, 1 }, { 1, 1 } }, FigureEnum::L, ORANGE };
Figure Figures::j{ std::vector<Rec>{ {-1, 1 }, { 0,-1 }, { 0, 0 }, { 0, 1 } }, FigureEnum::J, PINK };
Figure Figures::t{ std::vector<Rec>{ {-1, 0 }, { 0,-1 }, { 0, 0 }, { 1, 0 } }, FigureEnum::T, PURPLE };
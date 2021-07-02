#include "figures.h"

Figure Figures::o{ std::vector<Rec>{ { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } }, YELLOW };
Figure Figures::i{ std::vector<Rec>{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } }, SKYBLUE };
Figure Figures::s{ std::vector<Rec>{ { 0, 1 }, { 1, 0 }, { 1, 1 }, { 2, 0 } }, RED };
Figure Figures::z{ std::vector<Rec>{ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } }, GREEN };
Figure Figures::l{ std::vector<Rec>{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 2 } }, ORANGE };
Figure Figures::j{ std::vector<Rec>{ { 0, 2 }, { 1, 0 }, { 1, 1 }, { 1, 2 } }, PINK };
Figure Figures::t{ std::vector<Rec>{ { 0, 0 }, { 1, 0 }, { 2, 0},  { 1, 1 } }, PURPLE };
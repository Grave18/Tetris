#pragma once

#include <raylib.h>
#include "player.h"

//TODO: это скопище классов нужно переписать, разнести по файлам, либо сделать что-то еще
class Command
{
public:
	virtual ~Command() 
	{
	}

	virtual void Execute(Player &player) = 0;
};


class NoCommand : public Command
{
	void Execute(Player& player) override
	{
	}
};

class RotateCommand : public Command
{
public:
	void Execute (Player& player) override
	{
		player.rotate_figure();
	}
};

class MoveLeftCommand : public Command
{
	void Execute(Player& player)  override
	{
		player.move_left();
	}
};

class MoveRightCommand : public Command
{
	void Execute(Player& player) override
	{
		player.move_right();
	}
};


class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	Command* HandleInput();

private:
	Command* up_arrow_btn;
	Command* left_arrow_btn;
	Command* right_arrow_btn;
	Command* down_arrow_btn;
	Command* l_shift_btn;
};

inline InputHandler::InputHandler()
{
	up_arrow_btn = new RotateCommand();
	left_arrow_btn = new MoveLeftCommand();
	right_arrow_btn = new MoveRightCommand();
	down_arrow_btn = new NoCommand();
	l_shift_btn = new NoCommand();
}

inline InputHandler::~InputHandler()
{
	if(up_arrow_btn)
		delete up_arrow_btn;
	if(left_arrow_btn)
		delete left_arrow_btn;
	if(right_arrow_btn)
		delete right_arrow_btn;
	if (down_arrow_btn)
		delete down_arrow_btn;
	if (l_shift_btn)
		delete l_shift_btn;
}

Command* InputHandler::HandleInput()
{
	if (IsKeyPressed(KEY_UP))
		return up_arrow_btn;
	if (IsKeyPressed(KEY_DOWN))
		return down_arrow_btn;
	if (IsKeyPressed(KEY_LEFT))
		return left_arrow_btn;
	if (IsKeyPressed(KEY_RIGHT))
		return right_arrow_btn;
}
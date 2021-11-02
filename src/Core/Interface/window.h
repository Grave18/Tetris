#pragma once

#include <vector>
#include <functional>

#include <raylib.h>

#include "Interface/windowElementIntrface.h"

namespace Interface
{
	class Window
	{
	public:
		Window(int windowWidth,
			   int windowHeight,
			   std::function<Vector2(void)> getMousePosition,
			   std::function<bool(int)> isMouseButtonPressed);
		Window(Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&) = delete;
		Window& operator=(Window&&) = delete;

		void update();

	private:
		std::vector<WindowElementInterface*> elements_;

	};
}
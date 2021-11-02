#include "Interface/window.h"

namespace Interface
{
	Window::Window(int windowWidth,
				   int windowHeight,
				   std::function<Vector2(void)> getMousePosition,
				   std::function<bool(int)> isMouseButtonPressed)
	{

	}

	void Window::update()
	{
		for (const auto& element : elements_)
		{
			element->update();
		}
	}
}
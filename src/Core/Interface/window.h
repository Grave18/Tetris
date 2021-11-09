#pragma once

#include <vector>
#include <functional>

#include <raylib.h>

#include "Interface/windowElementIntrface.h"
#include "Interface/elementArgs.h"

namespace Interface
{
	class Window
	{
	public:
		Window();
		Window(Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&) = delete;
		Window& operator=(Window&&) = delete;

		void addElement(WindowElementInterface* element);
		void removeElement(WindowElementInterface* element);

		void update();

	private:
		void findMultiplier();

		std::vector<WindowElementInterface*> elements_;
		ElementArgs elemArgs_;
	};
}
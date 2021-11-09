#include "Interface/window.h"

namespace Interface
{
//public:
	Window::Window()
	{
		findMultiplier();
	}

	void Window::addElement(WindowElementInterface* element)
	{
		if (element && std::find(elements_.begin(), elements_.end(), element) == elements_.end())
		{
			elements_.push_back(element);
			TraceLog(LOG_INFO, "Element added");
		}
		else
			TraceLog(LOG_WARNING, "Element is allready added or null.");
	}

	void Window::removeElement(WindowElementInterface* element)
	{
		if (element)
		{
			auto elementToErase = std::find(elements_.begin(), elements_.end(), element);

			if (elementToErase != elements_.end())
			{
				elements_.erase(elementToErase);
				TraceLog(LOG_INFO, "Element removed");
			}
			else
				TraceLog(LOG_WARNING, "Element is not found.");

		}
		else
			TraceLog(LOG_WARNING, "Element is null.");
	}

	void Window::update()
	{
		for (const auto& element : elements_)
		{
			element->update(elemArgs_);
		}
	}

//private:
	void Window::findMultiplier()
	{
		elemArgs_.findMultiplier(GetScreenWidth());
	}
}
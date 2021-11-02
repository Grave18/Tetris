#pragma once

namespace Interface
{
	class WindowElementInterface
	{
	public:
		virtual ~WindowElementInterface() { }

		//TODO: pass button press and mouse pos
		virtual void update() = 0;
	};
}
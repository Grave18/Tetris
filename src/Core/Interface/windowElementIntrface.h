#pragma once

#include "elementArgs.h"
#include "alignment.h"

namespace Interface
{
	class WindowElementInterface
	{
	public:
		virtual ~WindowElementInterface() { }

		virtual void update(const ElementArgs& args) = 0;
	};
}
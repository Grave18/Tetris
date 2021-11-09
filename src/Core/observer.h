#pragma once

#include <raylib.h>
#include <vector>
#include <algorithm>
#include <any>

enum class Events
{
	PLAYER_FELL,
	ROW_CLEARED
};

class Observer
{
public:
	virtual void onNotify(const std::any& entity, Events event) = 0;
	virtual ~Observer() = default;
};

class Subject
{
public:
	void addObserver(Observer* observer)
	{
		if (observer && std::find(observers_.begin(), observers_.end(), observer) == observers_.end())
			observers_.push_back(observer);
		else
			TraceLog(LOG_WARNING, "Event allready registred or null.");
	}

	void removeObserver(Observer* observer)
	{
		if (observer)
		{
			auto observerToErase = std::find(observers_.begin(), observers_.end(), observer);

			if(observerToErase != observers_.end())
				observers_.erase(observerToErase);
			else
				TraceLog(LOG_WARNING, "Observer is not found.");
		}
		else
			TraceLog(LOG_WARNING, "Observer is null.");
	}

	void notify(const std::any& entity, Events event) const
	{
		for (const auto& observer : observers_)
		{
			observer->onNotify(entity, event);
		}
	}

private:
	std::vector<Observer*> observers_;
};
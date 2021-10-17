#pragma once

#include <raylib.h>
#include <vector>
#include <algorithm>

enum class Events
{
	PLAYER_FELL,
	ROW_CLEARED
};

class Observer
{
public:
	virtual void onNotify(void* entity, Events event) = 0;
	virtual ~Observer() = default;
};

class Subject
{
public:
	void addObserver(Observer* observer)
	{
		if (std::find(observers_.begin(), observers_.end(), observer) == observers_.end())
			observers_.push_back(observer);
		else
			TraceLog(LOG_WARNING, "Event allready registred.");
	}

	void removeObserver(Observer* observer)
	{
		observers_.erase(std::find(observers_.begin(), observers_.end(), observer));
	}

	void notify(void* entity, Events event) const
	{
		for (const auto& observer : observers_)
		{
			observer->onNotify(entity, event);
		}
	}

private:
	std::vector<Observer*> observers_;
};
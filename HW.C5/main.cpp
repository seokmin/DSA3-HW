#include <list>
#include <iostream>

int main(void)
{
	return 0;
}

struct Activity
{
	int startTime;
	int endTime;
};

int MaxActivityInTime(std::list<Activity>& activities, int endTime)
{
	activities.sort(
		[](Activity& act1, Activity&act2) {if (act1.endTime < act2.endTime) return true; });
	auto currentStartTime = 0;
	auto result = 0;
	for (auto& act : activities)
	{
		// 넣을 수 있으면 무조건 넣는다.
		if(act.startTime >= currentStartTime)
		{ 
			++result;
			currentStartTime = act.endTime;
		}
	}
	return result;
}
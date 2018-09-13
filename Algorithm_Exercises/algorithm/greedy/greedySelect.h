#pragma once
#include<vector>
#include<algorithm>
struct Activity {
	int startTime;
	int endTime;
};
std::vector<Activity> select(std::vector<Activity> activities) {
	std::vector<Activity> result;
	std::sort(activities.begin(), activities.end(), [](const Activity &a, const Activity &b)->bool {
		return a.endTime < b.endTime;
	});
	int thistime = 0;
	for (Activity activity : activities) {
		if (activity.startTime >= thistime && activity.endTime > thistime) {
			thistime = activity.endTime;
			result.push_back(activity);
		}
		else {
			continue;
		}
	}
	return result;
}
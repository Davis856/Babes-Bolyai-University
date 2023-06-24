#pragma once

#include "Observer.h"
#include "Star.h"

class RepoStars: public Observable
{
private:
	std::vector<Star> stars;
	void LoadData();

public:
	RepoStars();
	~RepoStars();

	void SaveData();
	std::vector<Star>& getStars();
	void addStar(Star s);
	void updateStar(Star s);
	int checkExistence(Star s);
};
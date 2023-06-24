#pragma once

#include "Astronomer.h"
#include "Observer.h"

class RepoAstronomer : public Observable
{
private:
	std::vector<Astronomer> astronomers;
	void LoadData();

public:
	RepoAstronomer();
	~RepoAstronomer() {};

	std::vector<Astronomer>& getAstronomers();
};
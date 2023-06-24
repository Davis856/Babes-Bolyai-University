#include "RepoStars.h"
#include <fstream>
#include <algorithm>

RepoStars::RepoStars()
{
	this->LoadData();
}

RepoStars::~RepoStars()
{
	this->SaveData();
}

std::vector<Star>& RepoStars::getStars()
{
	return this->stars;
}

void RepoStars::LoadData()
{
	std::ifstream inFile("stars.txt");
	Star currentElement;
	this->stars.clear();
	while (inFile >> currentElement)
	{
		this->stars.push_back(currentElement);
	}

	::std::sort(this->stars.begin(), this->stars.end(), [](Star s1, Star s2)
		{
			return s1.getCons() < s2.getCons();
		});
	inFile.close();
}

void RepoStars::addStar(Star s)
{
	int pos = this->checkExistence(s);
	if (pos == -1)
	{
		this->stars.push_back(s);
		::std::sort(this->stars.begin(), this->stars.end(), [](Star s1, Star s2)
			{
				return s1.getCons() < s2.getCons();
			});
		this->SaveData();
		this->notify();
	}
	else
	{
		throw std::exception();
	}
}

void RepoStars::updateStar(Star s)
{
	int pos = this->checkExistence(s);
	if (pos > 0)
	{
		this->stars[pos].setName(s.getName());
		this->stars[pos].setRA(s.getRA());
		this->stars[pos].setDec(s.getDec());
		this->stars[pos].setDiameter(s.getDiameter());
		this->SaveData();
		this->notify();
	}
	else
	{
		throw std::exception();
	}
}

int RepoStars::checkExistence(Star s)
{
	for (int i = 0; i < this->stars.size(); i++)
	{
		if (this->stars[i].getName() == s.getName())
			return i;
	}

	if (s.getName().empty())
		return 0;

	return -1;
}

void RepoStars::SaveData()
{
	std::ofstream outFile("stars.txt");
	::std::sort(this->stars.begin(), this->stars.end(), [](Star s1, Star s2)
		{
			return (s1.getCons() < s2.getCons()) && (s1.getDiameter() < s2.getDiameter());
		});
	for (auto& s : this->stars)
		outFile << s << '\n';
}
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Comparator
{
public:
	virtual bool compare(T elem1, T elem2) = 0;
};

template <typename T>
class ComparatorAscendingBySize : public Comparator<T>
{
public:
	bool compare(T elem1, T elem2) override;
};

template <typename T>
class ComparatorDescendingByQuantity : public Comparator<T>
{
public:
	bool compare(T elem1, T elem2) override;
};

template <typename T>
inline bool ComparatorAscendingBySize<T>::compare(T elem1, T elem2)
{
	return elem1.getSize() <= elem2.getSize();
}

template <typename T>
inline bool ComparatorDescendingByQuantity<T>::compare(T elem1, T elem2)
{
	return elem1.getQuantity() >= elem2.getQuantity();
}

template <typename T>
void genericSort(std::vector<T>& v, Comparator<T>* comp)
{
	bool sorted = true;

	do
	{
		sorted = true;
		
		for (int i = 0; i < v.size() - 1; i++)
		{
			if (!comp->compare(v[i], v[i + 1]))
			{
				std::swap(v[i], v[i + 1]);
				sorted = false;
			}
		}
	} while (!sorted);
}

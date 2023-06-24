#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
#include <math.h>

using namespace std;


Bag::Bag() {
	//TODO - Implementation
	this->m = 2;
	this->length = 0;
	this->elements = new TElem[this->m];
	for (int i = 0; i < this->m; i++)
		this->elements[i] = NULL_TELEM;
}
/*
BC: Theta(capacity)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: Theta(capacity)
*/

int Bag::hashFunction(TElem k) const
{
	return k % this->m;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/


int Bag::TFunction(TElem k, int i) const
{
	if (k < 0)
	{
		k = abs(k);
	}
	return (int)(hashFunction(k) + 0.5 * i + 0.5 * pow(i, 2)) % this->m;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void Bag::resizeAndRehash()
{
	int oldCapacity = this->m;
	this->m *= 2;
	
	TElem* newElements = new TElem[this->m];

	this->length = 0;
	for(int index = 0; index < this->m ; index++)
		newElements[index] = NULL_TELEM;

	//rehashing
	for (int index = 0; index < oldCapacity; index++)
	{
		if (this->elements[index] != -111111 && this->elements[index] != -111112)
		{
			int i = 0;
			int currentPosition = this->TFunction(this->elements[index], i);
			while (i < this->m && (newElements[currentPosition] != -111111))
			{
				i++;
				currentPosition = this->TFunction(this->elements[index], i);
			}
			newElements[currentPosition] = this->elements[index];
			this->length++;
		}
	}
	delete[] this->elements;
	this->elements = newElements;
}
/*
BC: Theta(newCapacity)
WC: Theta(newCapacity * oldCapacity)
AC: Theta(newCapacity * oldCapacity)
Total complexity: O(newCapacity * oldCapacity)
*/

void Bag::add(TElem elem) {
	//TODO - Implementation
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	while (i < this->m && (this->elements[currentPosition] != -111111 && this->elements[currentPosition] != -111112))
	{
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	if (i == this->m)
	{
		this->resizeAndRehash();
		this->add(elem);
	}
	else
	{
		this->elements[currentPosition] = elem;
		this->length++;
	}
}
/*
BC: Theta(1)
WC: Theta(newCapacity * oldCapacity)
AC: Theta(newCapacity * oldCapacity)
Total complexity: O(newCapacity * oldCapacity)
*/

bool Bag::remove(TElem elem) {
	//TODO - Implementation
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	while (i < this->m && (this->elements[currentPosition] != elem && this->elements[currentPosition] != -111111))
	{
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	if (i == this->m || this->elements[currentPosition] == -111111)
		return false;
	else
	{
		this->length--;
		this->elements[currentPosition] = DELETED;
		return true;
	}
	return false; 
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/


bool Bag::search(TElem elem) const {
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	if (this->length == 0)
		return false;
	while (i < this->m && (this->elements[currentPosition] != elem && this->elements[currentPosition] != -111111))
	{
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	if (i == this->m || this->elements[currentPosition] == -111111)
		return false;
	else
		return true;
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	int numberOccurences = 0;
	int i = 0;
	int currentPosition = this->TFunction(elem, i);
	while (i < this->m && this->elements[currentPosition] != -111111)
	{
		if (this->elements[currentPosition] == elem)
			numberOccurences++;
		i++;
		currentPosition = this->TFunction(elem, i);
	}
	return numberOccurences; 
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/

int Bag::size() const {
	//TODO - Implementation
	return this->length;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

bool Bag::isEmpty() const {
	//TODO - Implementation
	return this->length == 0;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
/*
BC: Theta(1)
WC: Theta(capacity)
AC: Theta(capacity)
Total complexity: O(capacity)
*/

Bag::~Bag() {
	//TODO - Implementation
	delete[] this->elements;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

int Bag::toSet()
{
	int counter = 0;
	BagIterator bi = this->iterator();
	while (this->nrOccurrences(bi.getCurrent()) > 1)
	{
		int current = bi.getCurrent();
		remove(bi.getCurrent());
		counter++;
		while (bi.getCurrent() != current)
		{
			bi.next();
		}
		if (bi.getCurrent() == current)
		{
			continue;
		}
		else
		{
			bi.first();
		}
		
	}
	std::cout << std::endl;
	return counter;
}
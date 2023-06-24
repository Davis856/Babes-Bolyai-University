#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
#include <iostream>

ListIterator::ListIterator(const IteratedList& l) : list(l) {
	this->current = l.head;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void ListIterator::first() {
	this->current = list.head;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void ListIterator::prev()
{
	if (!this->valid())
		throw std::exception();
	this->current = this->list.prev[this->current];
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void ListIterator::next() {
	if (!this->valid())
		throw std::exception();
	this->current = this->list.next[this->current];
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

bool ListIterator::valid() const {
	return this->current != -1;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

TElem ListIterator::getCurrent() const {
	if (!this->valid())
		throw std::exception();
	return this->list.elems[this->current];
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/



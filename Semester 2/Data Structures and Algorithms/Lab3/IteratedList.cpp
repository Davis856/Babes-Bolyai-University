#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
#include <iostream>

int IteratedList::allocate()
{
	int i = this->first_empty;
	this->first_empty = this->next[this->first_empty];
	return i;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void IteratedList::deallocate(int poz)
{
	this->next[poz] = this->first_empty;
	this->first_empty = poz;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void IteratedList::resize()
{
	TElem* new_elems = new TElem[2 * this->capacity];
	TElem* new_next = new int[2 * this->capacity];
	TElem* new_prev = new int[2 * this->capacity];

	for (int i = 0; i < this->capacity; i++)
	{
		new_elems[i] = this->elems[i];
		new_next[i] = this->next[i];
		new_prev[i] = this->prev[i];
	}
	for (int i = this->capacity; i < 2 * this->capacity; i++)
	{
		new_next[i] = i + 1;
		new_prev[i] = i - 1;
	}
	new_next[2 * this->capacity - 1] = -1; // NIL
	new_prev[0] = -1; // NIL

	delete[] this->elems;
	delete[] this->next;
	delete[] this->prev;

	this->elems = new_elems;
	this->next = new_next;
	this->prev = new_prev;
	this->first_empty = this->capacity;
	this->capacity = 2 * this->capacity;
}
/*
BC: O(capacity)
WC: O(capacity)
AC: O(capacity)
Total complexity: O(capacity)
*/

IteratedList::IteratedList() {
	this->capacity = 1;
	this->length = 0;
	this->first_empty = 0;
	this->head = -1;
	this->tail = -1;
	this->elems = new TElem[capacity];
	this->next = new int[capacity];
	this->prev = new int[capacity];

	for (int i = 0; i < this->capacity; i++)
	{
		this->next[i] = i + 1;
		this->prev[i] = i - 1;
	}

	this->next[capacity - 1] = -1;
	this->prev[0] = -1;
}
/*
BC: O(capacity)
WC: O(capacity)
AC: O(capacity)
Total complexity: O(capacity)
*/

int IteratedList::size() const {
	return this->length;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

bool IteratedList::isEmpty() const {
	return this->head == -1;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid())
		throw std::exception();
	return pos.getCurrent();
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

TElem IteratedList::remove(ListIterator& pos) {

	if (!pos.valid())
		throw std::exception();
	TElem e = pos.getCurrent();
	if (this->head == this->tail)
	{
		deallocate(this->head);
		this->head = this->tail = -1;
		this->length--;
		return e;
	}
	int current = pos.current;
	pos.next();
	if (this->prev[current] == -1)
	{
		int next_node = this->next[current];
		this->prev[next_node] = -1;
		deallocate(current);
		this->head = next_node;
		this->length--;
		return e;
	}
	if (this->next[current] == -1)
	{
		int prev_node = this->prev[current];
		this->next[prev_node] = -1;
		deallocate(current);
		this->tail = prev_node;
		this->length--;
		return e;
	}

	int prev_node = this->prev[current];
	int next_node = this->next[current];

	this->next[prev_node] = next_node;
	this->prev[next_node] = prev_node;

	deallocate(current);
	this->length--;
	return e;

	/*for (int i = 0; i < this->length; i++)
	{
		std::cout << this->elems[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->next[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->prev[i] << " ";
	}
	std::cout << std::endl;*/
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

ListIterator IteratedList::search(TElem e) const {
	ListIterator pos = ListIterator(*this);
	while (pos.valid())
	{
		if (pos.getCurrent() == e)
			return pos;
		pos.next();
	}
	return pos;
}
/*
BC: Theta(1)
WC: Theta(n)
AC: O(n)
Total complexity: O(n)
*/

TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid())
		throw std::exception();
	int poss = pos.current;
	TElem old_elem = pos.getCurrent();
	this->elems[poss] = e;
	return old_elem;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (this->first_empty == -1) resize();
	if (!pos.valid())
		throw std::exception();
	int nod = pos.current;

	if (this->next[nod] == -1)
	{
		addToEnd(e);
		return;
	}


	pos.next();
	int node_after = pos.current;
	pos.prev();
	int node_current = pos.current;

	int add_node = allocate();
	this->elems[add_node] = e;


	this->next[add_node] = node_after;
	this->prev[add_node] = node_current;
	this->next[node_current] = add_node;
	this->prev[node_after] = add_node;
	pos.next();

	this->length++;

	/*std::cout << "addToPosition: " << e << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->elems[i]<<" ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->next[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->prev[i] << " ";
	}
	std::cout << std::endl;*/
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void IteratedList::addToEnd(TElem e) {
	if (this->first_empty == -1) resize();
	if (isEmpty())
	{
		int q = allocate();
		this->elems[q] = e;
		this->head = this->tail = q;
		this->length++;
		/*std::cout << "addToEnd isEmpty: " << e << std::endl;
		for (int i = 0; i < this->length; i++)
		{
			std::cout << this->elems[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < this->length; i++)
		{
			std::cout << this->next[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < this->length; i++)
		{
			std::cout << this->prev[i] << " ";
		}
		std::cout << std::endl;*/
		return;
	}

	if (this->first_empty == -1) resize();
	int q = allocate();
	elems[q] = e;
	int previousTail = this->tail;
	this->next[this->tail] = q;
	this->tail = q;
	this->next[this->tail] = -1;
	this->prev[this->tail] = previousTail;
	this->length++;

	/*std::cout << "addToEnd: " << e << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->elems[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->next[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->prev[i] << " ";
	}
	std::cout << std::endl;*/
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

void IteratedList::addToBeginning(TElem e)
{
	if (this->first_empty == -1) resize();
	if (isEmpty())
	{
		int q = allocate();
		this->elems[q] = e;
		this->head = this->tail = q;
		this->length++;
		/*std::cout << "addToBeginning isEmpty: " << e << std::endl;
		for (int i = 0; i < this->length; i++)
		{
			std::cout << this->elems[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < this->length; i++)
		{
			std::cout << this->next[i] << " ";
		}
		std::cout << std::endl;
		for (int i = 0; i < this->length; i++)
		{
			std::cout << this->prev[i] << " ";
		}
		std::cout << std::endl;*/
		return;
	}
	if (this->first_empty == -1) resize();
	int q = allocate();
	int previousHead = this->head;

	this->elems[q] = e;
	this->prev[this->head] = q;

	this->head = q;
	this->next[this->head] = previousHead;
	this->length++;

	/*std::cout << "addToBeginning: " << e << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->elems[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->next[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->prev[i] << " ";
	}
	std::cout << std::endl;*/

}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

IteratedList::~IteratedList() {
	delete[] this->elems;
	delete[] this->next;
	delete[] this->prev;
}
/*
BC: Theta(1)
WC: Theta(1)
AC: Theta(1)
Total complexity: Theta(1)
*/

int IteratedList::removeAll(IteratedList& list)
{
	int counter = 0;
	ListIterator it = list.first();
	while (list.length > 0)
	{
		remove(it);
		it.next();
		counter++;
	}

	return counter;
}
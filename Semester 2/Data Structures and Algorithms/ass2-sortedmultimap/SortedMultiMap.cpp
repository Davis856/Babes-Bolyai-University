#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->r = r;
	this->head = NULL;
	this->tail = NULL;

	struct Node* node= new Node;
	node->next = NULL;
	node->prev = NULL;

	this->nrkeys = 0;
	this->nrvalues = 0;
}
//Theta(1)

void SortedMultiMap::add(TKey c, TValue v) {
	if (this->head == NULL)
	{
		struct Node* n_node = new Node;
		
		n_node->elem = new TNElem;
		n_node->elem->first = c;
		n_node->elem->second.value = new TValue;
		n_node->elem->second.prev = NULL;
		n_node->elem->second.next = NULL;
		n_node->next = NULL;
		n_node->prev = NULL;

		/*n_node->next = new Node;
		n_node->next->prev = n_node;*/

		//n_node->elem->second.next->prev = &(n_node->elem->second);
		n_node->elem->second.value[0] = v;

		this->nrvalues++;
		this->nrkeys++;
		this->head = n_node;
		this->tail = n_node;
		//cout << n_node->elem->second.value[0];
	}
	else {
		struct Node* other = this->head;
		int k = 0;
		int ok = 0;
		while (k<this->nrkeys && ok == 0)
		{
			if (other->elem->first == c)
			{
				ok = 1;
				break;
			}
			if (other->next != NULL)
				other = other->next;
			k++;
		}
		if (ok == 1)
		{
			struct NValue* othernode = &other->elem->second;
			while (othernode->next != NULL)
			{
				othernode = othernode->next;
			}

			struct NValue* n_on = new NValue;
			n_on->value = new TValue;
			n_on->value[0] = v;
			n_on->prev = othernode;
			n_on->next = NULL;
			othernode->next = n_on;

			this->nrvalues++;
		}
		else{//if (other->elem->first != c)
			other = this->head;

			if (this->nrkeys == 1 && r(c, other->elem->first))
			{
				//cout << "begining";
				struct Node* n_node = new Node;

				n_node->elem = new TNElem;
				n_node->elem->first = c;
				n_node->elem->second.value = new TValue;
				n_node->elem->second.value[0] = v;
				n_node->elem->second.prev = NULL;
				n_node->elem->second.next = NULL;
				this->head->prev = n_node;
				n_node->next = this->head;
				n_node->prev = NULL;

				this->nrvalues++;
				this->nrkeys++;
				this->head = n_node;
			}
			else if (this->nrkeys == 1 && r(other->elem->first, c))
			{
				//cout << "end";
				struct Node* n_node = new Node;

				n_node->elem = new TNElem;
				n_node->elem->first = c;
				n_node->elem->second.value = new TValue;
				n_node->elem->second.value[0] = v;
				n_node->elem->second.prev = NULL;
				n_node->elem->second.next = NULL;
				this->tail->next = n_node;
				n_node->next = NULL;
				n_node->prev = this->tail;

				this->nrvalues++;
				this->nrkeys++;
				this->tail = n_node;
			}
			else if (this->nrkeys > 1)
			{
				int k = 0;
				if (r(c, this->head->elem->first))
				{
					struct Node* n_node = new Node;

					n_node->elem = new TNElem;
					n_node->elem->first = c;
					n_node->elem->second.value = new TValue;
					n_node->elem->second.value[0] = v;
					n_node->elem->second.prev = NULL;
					n_node->elem->second.next = NULL;
					this->head->prev = n_node;
					n_node->next = this->head;
					n_node->prev = NULL;

					this->nrvalues++;
					this->nrkeys++;
					this->head = n_node;

					k = 1;
				}
				else if (r(this->tail->elem->first, c))
				{
					//cout << "end";
					struct Node* n_node = new Node;

					n_node->elem = new TNElem;
					n_node->elem->first = c;
					n_node->elem->second.value = new TValue;
					n_node->elem->second.value[0] = v;
					n_node->elem->second.prev = NULL;
					n_node->elem->second.next = NULL;
					this->tail->next = n_node;
					n_node->next = NULL;
					n_node->prev = this->tail;

					this->nrvalues++;
					this->nrkeys++;
					this->tail = n_node;
					k = 1;
				}
				if (k == 0)
				{
					other = this->head;
					k = 0;
					//cout << this->nrkeys;
					//TODO
					if (other->next == NULL)
					{ }//cout << "null next " << other->elem->first;
					else {
						while (k < this->nrkeys - 1 && !(r(other->elem->first, c) && r(c, other->next->elem->first)))
						{
							//cout << other->next<<" ";
							if (other->next != NULL)
								other = other->next;
							k++;
						}
					}
					//cout << other->elem->first;
					struct Node* n_node = new Node;

					n_node->elem = new TNElem;
					n_node->elem->first = c;
					n_node->elem->second.value = new TValue;
					n_node->elem->second.value[0] = v;
					n_node->elem->second.prev = NULL;
					n_node->elem->second.next = NULL;

					n_node->next = other->next;
					n_node->prev = other;

					//cout << n_node->prev->elem->first << " " << n_node->elem->first << " " << n_node->next->elem->first;

					
					other->next = n_node;
					//TODO
					if (other->next->next == NULL)
					{ }//cout << "null";
					else
						other->next->next->prev = n_node;

					this->nrvalues++;
					this->nrkeys++;
				}
			}
		}
	}
}
//Best case: Theta(1), Worst case: Theta(nrvalues) => Total complexiy: O(nrvalues)

vector<TValue> SortedMultiMap::search(TKey c) const {
	if (this->head != NULL)
	{
		struct Node* node = this->head;
		int is = 0;
		if (node->next == NULL && node->elem->first == c)
			is = 1;
		while (node->next != NULL)
		{
			if (node->elem->first == c)
			{
				is = 1;
				break;
			}
			node = node->next;
		}
		if (node->elem->first == c)
			is = 1;
		if (is == 1)
		{
			struct NValue* othernode = &node->elem->second;
			int k = 0;
			while (othernode->next != NULL)
			{
				othernode = othernode->next;
				k++;
			}
			if (k != 0)
			{
				vector<TValue>values(k);
				othernode = &node->elem->second;
				values.push_back(node->elem->second.value[0]);
				if (k > 1)
					while (othernode->next != NULL)
					{
						othernode = othernode->next;
						values.push_back(node->elem->second.value[0]);
					}
				return values;
			}
			else
				return vector<TValue>();
		}
		else
			return vector<TValue>();
	}
	else
		return vector<TValue>();
}
//Best case: Theta(nr of values for the first key), Worst case: Theta(nrkeys + nrvalues for that key) => Total complexiy: O(nrkeys + nrvalues for that key)


bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO organize better

	struct Node* other = this->head;
	int k = 0;
	int ok = 0;
	//looks for the value c;
	while (k < this->nrkeys && ok == 0)
	{
		if (other->elem->first == c)
		{
			ok = 1;
			break;
		}
		if (other->next != NULL)
			other = other->next;
		k++;
	}
	//cout << "ok " << ok<<" "<<c<<endl;
	if (ok == 1)
	{	
		//if last item
		if (this->nrvalues == 1 && other->elem->second.value[0] == v)
		{
			this->head = NULL;
			this->tail = NULL;
			this->nrkeys = 0;
			this->nrvalues = 0;
			return true;
		}
		//if last key, but multiple values
		if (this->nrkeys == 1)
		{
			if (other->elem->second.value[0] == v)
			{
				other->elem->second.next->prev = NULL;
				other->elem->second = *other->elem->second.next;
				this->nrvalues--;
				return true;
			}
			//just in case
		}
		else {
			struct NValue* othernode = &other->elem->second;
			//if the key has a unique value
			if (othernode->next == NULL)
			{
				if (other != this->head && other != this->tail && this->nrkeys != 1)
				{
					//std::cout << "keys" << this->nrkeys;
					//std::cout << "2";
					if (othernode->value[0] != v)
						return false;

					struct Node* node = other->prev;

					node->next = other->next;
					//cout << node->next->elem->first;
					other->next->prev = node;
					//cout << other->next->prev->elem->first;
					this->nrkeys--;
					this->nrvalues--;
					return true;
				}
				else if (other == this->head && this->nrkeys>1)
				{
					if (othernode->value[0] != v)
						return false;
					//std::cout << "3";
					other->next->prev = NULL;
					this->head = other->next;
					this->nrkeys--;
					this->nrvalues--;
					return true;
				}
				else if (other == this->tail && this->nrkeys > 1)
				{
					if (othernode->value[0] != v)
						return false;
					//std::cout << "4";
					other->prev->next = NULL;
					this->tail = other->prev;
					this->nrkeys--;
					this->nrvalues--;
					return true;
				}
				else
					return false;
			}
			//if the key has multiple values
			else {
				if (othernode->value[0] == v)
				{
					//if first
					othernode->next->prev = NULL;
					other->elem->second = *othernode->next;
					this->nrvalues--;
					return true;
				}
				else {
					//looking for the value
					int is = 0;
					while (othernode->next != NULL)
					{
						if (othernode->next != NULL)
							othernode = othernode->next;
						if (othernode->value[0] == v)
						{
							break;
							is = 1;
						}
					}
					if (othernode->next == NULL)
					{
						//if last
						if (othernode->value[0] == v)
						{
							othernode->prev->next = NULL;
							return true;
						}
						else
							return false;
					}
					else if (is == 1) {
						//else
						struct NValue* onode = othernode->prev;
						onode->next = othernode->next;
						othernode->next->prev = onode;
						this->nrvalues--;
						return true;
					}
					if (is == 0)
						return false;
				}
			}
		}
	}
	else
		return false;
	return false;
}
//Best case: Theta(1), Worst case: Theta(nrvalues) => Total complexiy: O(nrvalues)

int SortedMultiMap::size() const {
	return this->nrvalues;
}
//Theta(1)

bool SortedMultiMap::isEmpty() const {
	if (this->head == NULL)
		return true;
	else
		return false;
}
//Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
//Theta(1)

SortedMultiMap::~SortedMultiMap() {
	while (head != nullptr) {
		struct Node* p = this->head;

		//while (&this->head->elem->second != NULL) {
		//	struct NValue* c = &this->head->elem->second;
		//	this->head->elem->second = *this->head->elem->second.next;
		//	delete[] c;
		//}

		this->head = this->head->next;
		delete[] p;
	}
}
//Theta(nrkeys)
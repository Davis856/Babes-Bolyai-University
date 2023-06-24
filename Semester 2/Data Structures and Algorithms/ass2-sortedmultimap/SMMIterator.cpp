#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	if (map.head != NULL)
	{
		this->current_node = map.head;
		this->current_value = &map.head->elem->second;
	}
	else
	{
		this->current_node = NULL;
		this->current_value = NULL;
	}
}
//Theta(1)

void SMMIterator::first() {
	if (map.head != NULL)
	{
		this->current_node = map.head;
		this->current_value = &map.head->elem->second;
	}
	else
	{
		this->current_node = NULL;
		this->current_value = NULL;
	}
	//cout << this->current_value << " " << this->current_node << endl;
}
//Theta(1)

void SMMIterator::next(){
	//cout << this->current_value << " " << this->current_node << endl;
	if (this->current_value == NULL && this->current_node == NULL)
		throw exception();
	if (this->current_value != NULL && this->current_node != NULL)
	{
		if (this->current_value->next == NULL)
		{
			if (this->current_node->next == NULL)
			{
				
				this->current_node = NULL;
				this->current_value = NULL;
				//std::cout << "not"
			}
			else
			{
				this->current_node = this->current_node->next;
				this->current_value = &this->current_node->elem->second;
			}
		}
		else
		{
			this->current_value = this->current_value->next;
		}
	}

}
//Theta(1)

bool SMMIterator::valid() const{
	//cout << this->current_value << " " << this->current_node<<endl;
	return this->current_value != NULL && this->current_node != NULL;
}
//Theta(1)

TElem SMMIterator::getCurrent() const{
	if (this->current_value == NULL || this->current_node == NULL)
		throw exception();
	else
	{
		return TElem(this->current_node->elem->first, this->current_value->value[0]);
	}
}
//Theta(1)



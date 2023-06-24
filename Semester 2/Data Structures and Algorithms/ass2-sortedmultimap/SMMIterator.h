#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	struct SortedMultiMap::Node* current_node;
	struct SortedMultiMap::NValue* current_value;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};


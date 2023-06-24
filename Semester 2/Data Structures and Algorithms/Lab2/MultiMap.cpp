#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

Key* MultiMap::isKey(TKey key) const {
    Key* current = this->head;
    Key* sol = nullptr;

    while (current != nullptr) {
        if (current->info == key) {
            sol = current;
            return sol;
        }
        current = current->next;
    }

    return sol;
}
//Time complexity: BC:Theta(1), AC:Theta(keys), Total: O(keys)

void MultiMap::addKey(TKey k) {
    auto* node = new Key;

    node->info = k;
    node->v = nullptr;
    node->next = nullptr;

    if (this->head == nullptr) {
        this->head = node;
        this->tail = node;
        return;
    }

    this->tail->next = node;
    this->tail = this->tail->next;
}
//Time complexity: Theta(1)


void MultiMap::addValueToKey(TKey k, TValue v) {
    Key* currentKey = this->head;

    while (currentKey != nullptr && currentKey->info != k) {
        currentKey = currentKey->next;
    }

    auto* nodeVal = new Value;
    nodeVal->info = v;
    nodeVal->next = nullptr;

    if (currentKey->v == nullptr) {
        currentKey->v = nodeVal;
        return;
    }

    Value* currentValue = currentKey->v;

    while (currentValue->next != nullptr) {
        currentValue = currentValue->next;
    }

    currentValue->next = nodeVal;
}
//Time complexity: BC:Theta(1), AC:Theta(keys+values), Total: O(keys+values)

void MultiMap::freeValues(Value* head) {
    while (head != nullptr) {
        Value* tmp = head;
        head = head->next;
        delete tmp;
    }
}
//Time complexity: Theta(values)


MultiMap::MultiMap() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
//Time complexity: Theta(1)


void MultiMap::add(TKey c, TValue v) {
    Key* key = this->isKey(c);

    // if the key is not in the multimap
    if (key == nullptr) {
        this->addKey(c);
    }

    // add the value
    this->addValueToKey(c, v);

    this->length++;
}
//Time complexity: BC: Theta(1), AC/WC: Theta(2*keys+values), Total: O(2*keys+values)

bool MultiMap::remove(TKey c, TValue v) {
    auto currentElem = this->head;

    Key* prev = nullptr;
    Value* prev_value = nullptr;
    while (currentElem != nullptr and currentElem->info != c) {
        prev = currentElem;
        currentElem = currentElem->next;
    }
    if (currentElem == nullptr) {
        return false;
    }

    auto currentValue = currentElem->v;
    while (currentValue != nullptr and currentValue->info != v) {
        prev_value = currentValue;
        currentValue = currentValue->next;
    }

    if (currentValue == nullptr) {
        return false;
    }

    if (currentValue->info == v) {
        if (prev_value == nullptr) {
            currentElem->v = currentValue->next;
        }
        else {
            prev_value->next = currentValue->next;
        }
        this->length--;
        delete currentValue;


        if (currentElem->v == nullptr) {
            if (prev != nullptr) {
                prev->next = currentElem->next;
            }
            else {
                this->head = currentElem->next;
            }
            delete currentElem;
        }

        return true;
    }
    else {
        return false;
    }
    return false;
}
//Time complexity: BC:Theta(1), AC:Theta(keys+values), Total: O(keys+values)

vector<TValue> MultiMap::search(TKey c) const {
    vector<TValue> sol;

    Key* node = this->isKey(c);

    if (node == nullptr) {
        return sol;
    }

    Value* currentValue = node->v;

    while (currentValue != nullptr) {
        sol.push_back(currentValue->info);
        currentValue = currentValue->next;
    }

    return sol;
}
//Time complexity: BC: Theta(1), AC/WC: Theta(keys), Total: O(keys)

int MultiMap::size() const {
    return this->length;
}
//Time complexity: Theta(1)

bool MultiMap::isEmpty() const {
    return this->length == 0;
}
//Time complexity: Theta(1)

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
}
//Time complexity: Theta(1)

MultiMap::~MultiMap() {
    while (this->head != nullptr) {
        Key* tmp = this->head;
        this->freeValues(this->head->v);
        this->head = this->head->next;
        delete tmp;
    }
}
//Time complexity: Theta(keys+values)

TKey MultiMap::minKey() const
{
    TKey min_key = 100000;
    if (isEmpty())
        return NULL_TKEY;

    for (int i = 0; i < this->length; i++)
    {
        if (min_key > this->head->info)
            min_key = this->head->info;
        this->head->info = this->head->next->info;
    }
    return min_key;
}
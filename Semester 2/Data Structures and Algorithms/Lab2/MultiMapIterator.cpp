#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
    this->current_key = this->col.head;
    if (current_key == nullptr) {
        this->current_value = nullptr;
    }
    else {
        this->current_value = this->col.head->v;
    }
}
//Time complexity: Theta(1)

TElem MultiMapIterator::getCurrent() const {
    if (this->current_key == nullptr || this->current_value == nullptr) {
        throw exception();
    }
    TElem res = make_pair(this->current_key->info, this->current_value->info);
    return res;
}
//Time complexity: Theta(1)

bool MultiMapIterator::valid() const {
    if (this->current_key == nullptr) {
        return false;
    }
    return true;
}
//Time complexity: Theta(1)

void MultiMapIterator::next() {
    if (this->current_key == nullptr) {
        throw exception();
    }
    else {
        if (this->current_value == nullptr) {
            this->current_key = this->current_key->next;
            if (current_key == nullptr) {
                //throw exception();
            }
            else {
                this->current_value = this->current_key->v;
            }

        }
        else if (this->current_value->next == nullptr) {
            this->current_key = this->current_key->next;
            if (current_key == nullptr) {
                //throw exception();
            }
            else {
                this->current_value = this->current_key->v;
            }

        }
        else {
            this->current_value = this->current_value->next;
        }
    }
}
//Time complexity: Theta(1)


void MultiMapIterator::first() {
    this->current_key = this->col.head;
    if (current_key == nullptr) {
        this->current_value = nullptr;
    }
    else {
        this->current_value = this->col.head->v;
    }
}
//Time complexity: Theta(1)




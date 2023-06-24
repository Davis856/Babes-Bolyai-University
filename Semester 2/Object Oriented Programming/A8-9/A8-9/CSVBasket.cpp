#include <fstream>
#include "CSVBasket.h"

CSVBasket::CSVBasket(const std::vector<Coat> shoppingBasket, const std::string fileName)
{
	this->basket = shoppingBasket;
	this->filename = fileName;
}

std::vector<Coat> CSVBasket::getArray()
{
	return this->basket;
}

int CSVBasket::getSize()
{
	return this->basket.size();
}

void CSVBasket::writeToFile() {
    std::ofstream fout(this->filename);
    if (!this->basket.empty()) {
        for (const Coat& coat : this->basket) {
            fout << coat << "\n";
        }
    }
    fout.close();
}

CSVBasket::~CSVBasket() = default;
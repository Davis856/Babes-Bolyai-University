#pragma once

#include "Basket.h"

class CSVBasket : public Basket
{
public:
	CSVBasket(const std::vector<Coat> shoppingBasket, const std::string fileName);

	std::vector<Coat> getArray() override;

	std::string& getFilename() override;

	void writeToFile() override;

	int getSize() override;

	~CSVBasket();
};
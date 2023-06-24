#pragma once

#include "Basket.h"

class HTMLBasket : public Basket
{
public:
	HTMLBasket(const std::vector<Coat> shoppingBasket, const std::string fileName);

	std::vector<Coat> getArray() override;

	std::string& getFilename() override;

	void writeToFile() override;

	int getSize() override;

	~HTMLBasket();
};
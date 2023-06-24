#include "UI.h"
#include "Tests.h"
#include <stdio.h>
#include <assert.h>
#include <sstream>

void Tests::testCoat()
{
	Coat coat{ 1, "Magenta", 10, 50, "https://google.ro" };
	assert(coat.getSize() == 1);
	assert(coat.getColour() == "Magenta");
	assert(coat.getPrice() == 10);
	assert(coat.getQuantity() == 50);
	assert(coat.getPhotograph() == "https://google.ro");
}

void Tests::testDynamicVector()
{
	DynamicVector<int> v1{ 2 };
	v1.add(10);
	v1.add(20);
	assert(v1.getSize() == 2);
	assert(v1[1] == 20);
	v1[1] = 25;
	assert(v1[1] == 25);
	v1.add(30);
	assert(v1.getSize() == 3);

	DynamicVector<int> v2{ v1 };
	assert(v2.getSize() == 3);

	DynamicVector<int> v3;
	v3 = v1;
	assert(v3[0] == 10);
	assert(v3 == v1);
	assert(v3 == v2, false);
}

void Tests::testRepository()
{
	Repository repo(10);
	Repository repoCopy(10);
	Repository repoCopy2{};
	Coat coat{ 1, "Magenta", 10, 50, "https://google.ro" };
	Coat coat2{ 2, "Purple", 10, 30, "https://google.ro" };
	repo.addCoat(coat);
	repo.addCoat(coat2);
	repoCopy = repo;
	assert(repo.getArray()[0].getSize() == 1);
	assert(repo.getArray()[0].getColour() == "Magenta");
	assert(repo.getArray()[0].getPrice() == 10);
	assert(repo.getArray()[0].getQuantity() == 50);
	assert(repo.getArray()[0].getPhotograph() == "https://google.ro");
	assert(repo.getSize() == 2);
	size_t pos = repo.FindElemBySize(coat.getSize());
	repo.removeCoat(pos);
	assert(repo.getSize() == 1);
	assert(repo.FindElemBySize(2) == 0);
	std::ostringstream out;
	out << repo;
	_ASSERTE(out, "Size: 2 | Colour: Purple | Price: 10$ | Quantity: 30 | Photograph: https://google.ro");

}

void Tests::testBasket()
{
	Basket basket(10);
	Basket basketCopy{};
	Coat coat{ 1, "Magenta", 10, 50, "https://google.ro" };
	Coat coat2{ 2, "Purple", 10, 30, "https://google.ro" };
	basket.addCoatToBasket(coat);
	basket.addCoatToBasket(coat2);
	assert(basket.getArray()[0].getSize() == 1);
	assert(basket.getArray()[0].getColour() == "Magenta");
	assert(basket.getArray()[0].getPrice() == 10);
	assert(basket.getArray()[0].getQuantity() == 50);
	assert(basket.getArray()[0].getPhotograph() == "https://google.ro");
	assert(basket.getSize() == 2);
	assert(basket.FindElemBySize(1) == 0);
	assert(basket.FindElemBySize(5) == 0);
	std::ostringstream out;
	out << basket;
	_ASSERTE(out, "Size: 1 | Colour: Magenta | Price: 10$ | Quantity: 20 | Photograph: https://google.ro");
}

void Tests::testAdminService()
{
	Repository repo(10);
	AdminService serv{ repo };
	serv.addCoat(1, "Magenta", 10, 50, "https://google.ro");
	serv.updateCoatSize(serv.getRepo()[0].getSize(), 10);
	assert(serv.getRepo()[0].getSize() == 10);
	serv.updateCoatColour(serv.getRepo()[0].getSize(), "Black");
	assert(serv.getRepo()[0].getColour() == "Black");
	serv.updateCoatPrice(serv.getRepo()[0].getSize(), 30);
	assert(serv.getRepo()[0].getPrice() == 30);
	serv.updateCoatQuantity(serv.getRepo()[0].getSize(), 20);
	assert(serv.getRepo()[0].getQuantity() == 20);
	serv.updateCoatPhotograph(serv.getRepo()[0].getSize(), "https://google.com");
	assert(serv.getRepo()[0].getPhotograph() == "https://google.com");
	serv.removeCoat(serv.getRepo()[0].getSize());
}

void Tests::testUserService()
{
	Basket repo(10);
	UserService serv{ repo };
	serv.addCoatToBasket(1, "Magenta", 10, 50, "https://google.ro");
	serv.updateCoatQuantity(0, 20);
	assert(serv.getRepo().getArray()[0].getQuantity() == 20);
}

void Tests::testAll()
{
	testCoat();
	testDynamicVector();
	testRepository();
	testBasket();
	testAdminService();
	testUserService();
}
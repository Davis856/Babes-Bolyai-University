#include "UI.h"
#include "Tests.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <assert.h>
#include <sstream>
#include "Comparator.h"

void Tests::testCoat()
{
	Coat coat{ 1, "Magenta", 10, 50, "https://google.ro" };
	assert(coat.getSize() == 1);
	assert(coat.getColour() == "Magenta");
	assert(coat.getPrice() == 10);
	assert(coat.getQuantity() == 50);
	assert(coat.getPhotograph() == "https://google.ro");
}
void Tests::testRepository()
{
	std::string filename = "testrepo.txt";
	Repository repo(filename);
	Repository repoCopy(filename);
	Repository repoCopy2(filename);
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
}

void Tests::testBasket()
{
	std::string filename = "testbasket.txt";
	Basket basket(filename);
	Basket basketCopy(filename);
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
}

void Tests::testAdminService()
{
	std::string filename = "testadminserv.txt";
	Repository repo(filename);
	AdminService serv{ repo };
	serv.addCoat(1, "Magenta", 10, 50, "https://google.ro");
	serv.updateCoatSize(serv.getRepo().getArray()[0].getSize(), 10);
	assert(serv.getRepo().getArray()[0].getSize() == 10);
	serv.updateCoatColour(serv.getRepo().getArray()[0].getSize(), "Black");
	assert(serv.getRepo().getArray()[0].getColour() == "Black");
	serv.updateCoatPrice(serv.getRepo().getArray()[0].getSize(), 30);
	assert(serv.getRepo().getArray()[0].getPrice() == 30);
	serv.updateCoatQuantity(serv.getRepo().getArray()[0].getSize(), 20);
	assert(serv.getRepo().getArray()[0].getQuantity() == 20);
	serv.updateCoatPhotograph(serv.getRepo().getArray()[0].getSize(), "https://google.com");
	assert(serv.getRepo().getArray()[0].getPhotograph() == "https://google.com");
	serv.removeCoat(serv.getRepo().getArray()[0].getSize());
}

void Tests::testUserService()
{
	std::string filename = "testuserserv.txt";
	Basket repo(filename);
	UserService serv{ &repo };
	serv.addCoatToBasket(1, "Magenta", 10, 50, "https://google.ro");
	serv.updateCoatQuantity(0, 20);
	assert(serv.getRepo().getArray()[0].getQuantity() == 20);
}

void Tests::testSort()
{
	std::vector<Coat> coat;
	coat.push_back(Coat(1, "Blue", 50, 20, "https://google.ro"));
	coat.push_back(Coat(5, "Yellow", 30, 70, "https://google.ro"));
	coat.push_back(Coat(4, "Black", 50, 60, "https://google.ro"));
	coat.push_back(Coat(2, "White", 30, 20, "https://google.ro"));

	std::vector<Coat> size{ coat };
	std::vector<Coat> quantity{ coat };

	Comparator<Coat>* compSize = new ComparatorAscendingBySize<Coat>{};
	Comparator<Coat>* compQuantity = new ComparatorDescendingByQuantity<Coat>{};

	genericSort<Coat>(size, compSize);
	genericSort<Coat>(quantity, compQuantity);

	assert(size[0].getSize() == 1);
	assert(size[1].getSize() == 2);
	assert(size[2].getSize() == 4);
	assert(size[3].getSize() == 5);

	assert(quantity[0].getQuantity() == 70);
	assert(quantity[1].getQuantity() == 60);
	assert(quantity[2].getQuantity() == 20);
	assert(quantity[3].getQuantity() == 20);

	delete compSize;
	delete compQuantity;
}

void Tests::testAll()
{
	testCoat();
	testRepository();
	testBasket();
	testAdminService();
	testUserService();
	testSort();
}


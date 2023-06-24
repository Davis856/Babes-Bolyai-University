#include <fstream>
#include "HTMLBasket.h"

HTMLBasket::HTMLBasket(const std::vector<Coat> shoppingBasket, const std::string fileName)
{
    this->basket = shoppingBasket;
    this->filename = fileName;
}

std::string& HTMLBasket::getFilename()
{
    return this->filename;
}

std::vector<Coat> HTMLBasket::getArray()
{
    return this->basket;
}

int HTMLBasket::getSize()
{
    return this->basket.size();
}

void HTMLBasket::writeToFile() {
    std::ofstream fout(this->filename);
    fout << "<!DOCTYPE html>\n<html><head><title>Shopping Basket</title></head><body>\n";
    fout << "<table border=\"1\">\n";
    fout << "<tr><td>Size</td><td>Colour</td><td>Price</td><td>Quantity</td><td>Link</td></tr>\n";
    for (const Coat& coat : this->basket) {
        fout << "<tr><td>" << coat.getSize() << "</td>"
            << "<td>" << coat.getColour() << "</td>"
            << "<td>" << coat.getPrice() << "</td>"
            << "<td>" << coat.getQuantity() << "</td>"
            << "<td><a href=\"" << coat.getPhotograph() << "\">" << coat.getPhotograph() << "</a></td>" << '\n';
    }
    fout << "</table></body></html>";
    fout.close();
}

HTMLBasket::~HTMLBasket() = default;
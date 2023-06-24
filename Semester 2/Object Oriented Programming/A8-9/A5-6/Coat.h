#pragma once

#include <string>

using namespace std;

class Coat
{
private:
	size_t size;
	string colour;
	size_t price;
	size_t quantity;
	string photograph;

public:
	//constructor for Coats
	Coat() : size{ 0 }, colour{ "" }, price{ 0 }, quantity{ 0 }, photograph{ "" } {};

	/// <summary>
	/// Constructor for the coat class with initialization for all fields
	/// </summary>
	/// <param name="size">The size of the coat</param>
	/// <param name="colour">The colour of the coat</param>
	/// <param name="price">The price of the coat</param>
	/// <param name="quantity">The quantity of the coat</param>
	/// <param name="photograph">A link to the coat photo</param>
	Coat(size_t size, const string& colour, size_t price, size_t quantity, const string& photograph);


	/// <summary>
	/// Destructor for the coat
	/// </summary>
	~Coat();

	inline size_t getSize() const { return this->size; }
	inline string getColour() const { return this->colour; }
	inline size_t getPrice() const { return this->price; }
	inline size_t getQuantity() const { return this->quantity; }
	inline string getPhotograph() const { return this->photograph; }

	inline void setSize(size_t value) { this->size = value; }
	inline void setColour(string value) { this->colour = value; }
	inline void setPrice(size_t value) { this->price = value; }
	inline void setQuantity(size_t value) { this->quantity = value; }
	inline void setPhotograph(string value) { this->photograph = value; }

	/// <summary>
	/// Equality operator for the coat class
	/// </summary>
	/// <param name="other">The coat to compare the current obj with</param>
	/// <returns>True if the coats are identical, False otherwise</returns>
	bool operator==(const Coat& other) const;

	/// <summary>
	/// Insertion operator for the coat class
	/// </summary>
	/// <param name="os">The stream obj to write data of the coat to</param>
	/// <param name="coat">The coat whose fields will be written</param>
	/// <returns>A stream object which contains the data of the coat</returns>

	friend std::ostream& operator<<(std::ostream& os, const Coat& coat);

	void click();

};
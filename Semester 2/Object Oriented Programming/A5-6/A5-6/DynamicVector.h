#pragma once
#include <exception>
#include <algorithm>
#include <iostream>

template <typename T>
class DynamicVector
{
public:
	/// <summary>
	/// Default constructor for the dynamic vector class
	/// </summary>
	DynamicVector();

	/// <summary>
	/// Constructor which initializes the vector with a certain maximum size
	/// </summary>
	/// <param name="maxSize"></param>
	DynamicVector(size_t maxSize);

	/// <summary>
	/// Copy constructor for the dynamic vector
	/// </summary>
	/// <param name="other">The object to copy from</param>
	DynamicVector(const DynamicVector& other);

	/// <summary>
	/// Copy assignment operator for the dynamic vector
	/// </summary>
	/// <param name="other">The object to copy the data from</param>
	/// <returns>A dynamic vector with the same data as other</returns>
	DynamicVector& operator=(const DynamicVector& other);

	bool operator==(const DynamicVector& other);

	DynamicVector<T>& operator+(T elem);

	/// <summary>
	/// Insertion operator for the dynamic vector
	/// </summary>
	/// <typeparam name="T1">A generic type of the vector</typeparam>
	/// <param name="os">The stream object to write to</param>
	/// <param name="vector">The vector whose elements will be written</param>
	/// <returns>A stream object containing the elements of the vector</returns>
	template <typename T1>
	friend std::ostream& operator <<(std::ostream& os, const DynamicVector<T1>& vector);

	/// <summary>
	/// Destructor for the dynamic vector
	/// </summary>
	~DynamicVector();

	// Size getter
	size_t getSize();

	/// <summary>
	/// Subscript operator for the dynamic vector
	/// </summary>
	/// <param name="position">The position of the element</param>
	/// <returns>The element on the given position in the array</returns>
	T& operator[](size_t position) const;

	/// <summary>
	/// Adds a new element to the end of the array
	/// Doubles its capacity in case it's full
	/// </summary>
	/// <param name="newElement">The new element to be added</param>
	void add(const T& newElement);

	/// <summary>
	/// Removes an element from the array by its position
	/// </summary>
	/// <param name="position">The position of the element</param>
	void remove(size_t position);

private:
	void resize(size_t newSize);

	T* elements;
	size_t maxSize;
	size_t currentSize;
};

template<typename T>
std::ostream& operator <<(std::ostream& os, const DynamicVector<T>& vector)
{
	for (size_t i = 0; i < vector.currentSize; ++i)
		os << vector[i];

	os << '\n';
	return os;
}

template<typename T>
inline DynamicVector<T>::DynamicVector() :
	maxSize{ 0 }, currentSize{ 0 }, elements{ nullptr }
{
}

template<typename T>
inline DynamicVector<T>::DynamicVector(size_t maxSize) :
	maxSize{ maxSize }, currentSize{ 0 }, elements{ new T[maxSize] }
{
}

template<typename T>
inline DynamicVector<T>::DynamicVector(const DynamicVector& other) :
	maxSize{ other.maxSize }, currentSize{ other.currentSize }, elements{ new T[other.maxSize] }
{
	std::copy(other.elements, other.elements + other.currentSize, this->elements);
}

template<typename T>
inline DynamicVector<T>& DynamicVector<T>::operator+(T elem)
{
	this->add(elem);
	return *this;
}
template<typename T>
inline DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& other)
{
	if (*this == other) return *this;

	if (this->elements == nullptr) this->elements = new T[1];
	if (other.maxSize > this->maxSize) resize(other.maxSize);
	else
	{
		this->maxSize = other.maxSize;
		delete[] this->elements;
		this->elements = new T[this->maxSize];
	}

	this->currentSize = other.currentSize;

	std::copy(other.elements, other.elements + other.currentSize, this->elements);

	return *this;
}

template<typename T>
inline bool DynamicVector<T>::operator==(const DynamicVector& other)
{
	if (this->currentSize != other.currentSize)
		return false;
	for (size_t i = 0; i < this->currentSize; ++i)
		if (!(this->elements[i] == other.elements[i]))
			return false;

	return true;
}

template<typename T>
inline DynamicVector<T>::~DynamicVector()
{
	delete[] this->elements;
	this->elements = nullptr;
}

template<typename T>
inline size_t DynamicVector<T>::getSize()
{
	return this->currentSize;
}

template<typename T>
inline T& DynamicVector<T>::operator[](size_t position) const
{
	if (position > this->currentSize) throw std::exception();

	return this->elements[position];
}

template<typename T>
inline void DynamicVector<T>::add(const T& newElement)
{
	if (this->elements == nullptr) return;
	if (this->currentSize == this->maxSize) resize(2 * this->maxSize);
	this->elements[this->currentSize++] = newElement;
}

template<typename T>
inline void DynamicVector<T>::remove(size_t position)
{
	if (this->elements == nullptr) return;

	if (position > this->currentSize) return;

	for (size_t i = position; i < this->currentSize - 1; ++i)
		this->elements[i] = this->elements[i + 1];

	this->currentSize--;
}

template<typename T>
inline void DynamicVector<T>::resize(size_t newSize)
{
	T* newArray = new T[newSize];

	std::copy(this->elements, this->elements + this->currentSize, newArray);

	this->maxSize = newSize;
	delete[] this->elements;
	this->elements = newArray;
}

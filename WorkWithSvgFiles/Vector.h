#pragma once
#include<iostream>
/**
* @brief Class Vector.
*/
template <class T> //!< allows to increase the methods functionality, because they can be adapted to more than one type or class
class Vector //!< define template class Vector
{
private: //!< data fields
	T * data; //!< dynamic memory
	size_t size;

	void copy(const Vector& other); //!< canonical representation of BIG SIX
	void destroy();

public:
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	Vector<T>& push_back(const T& other); //!< adds element at the end of the vector
	Vector<T>& push(const T& other); //!< adds element at the beginning og the vector
	T popBack(); //!< returns the element at the end of the vector

	Vector<T>& operator+=(const Vector<T>& other); //!< operator += for two vectors
	Vector<T> operator+(const Vector<T>& other) const; //!< operator + for two vectors
	Vector<T>& operator+=(const T& other); //!< operator += for vector and element with the vector's type
	Vector<T> operator+(const T& other) const; //!< operator + for vector and element with the vector's type

	T& getElem(size_t index); //!< returns element with given index
	T& operator[](size_t index); //!< overloads operator[], loaded to return T reference
	T operator[](size_t index) const; //!< overloads operator[], loaded to return T
	
	T& returnFirst(); //!< returns T reference for the first element
	T& returnLast(); //!< returns T reference for the last element

	T removeFirst(); //!< returns T for the first element
	T removeLast(); //!< returns T for the last element

	size_t length(); //!< returns the size

	Vector<T>& deleteElementByIndex(size_t index); //!< deletes element from the vector by given index
	Vector<T>& deleteAll(); //!< deletes all vector elements

	friend std::ostream& operator<<(std::ostream& out, Vector<T>& other) //!< overloads operator <<
	{
		for (size_t i = 0; i < this->size; i++)
		{
			out << other.data[i] << std::endl;
		}
		return out;
	}
};

template<class T>
inline void Vector<T>::copy(const Vector & other) //!< copies all data from one vector to another
{
	this->data = new T[other.size];
	this->size = other.size;

	for (size_t i = 0; i < this->size; i++)
	{
		this->data[i] = other.data[i];
	}
}

template<class T>
inline void Vector<T>::destroy() //!< deletes vector data
{
	delete[] this->data;
}

template<class T>
inline Vector<T>::Vector() //!< default constructor
{
	this->data = nullptr;
	this->size = 0;
}

template<class T>
inline Vector<T>::Vector(const Vector & other) //!< copy constructor
{
	this->copy(other);
}

template<class T>
inline Vector<T> & Vector<T>::operator=(const Vector & other) //!< operator =
{
	if (this != &other)
	{
		this->destroy();
		this->copy(other);
	}

	return *this;
}

template<class T>
inline Vector<T>::~Vector() //!< destructor
{
	this->destroy();
}

template<class T>
inline Vector<T>& Vector<T>::push_back(const T & other) //!< adds element to the end of the vector by given T reference
{
	T *container = new T[this->size + 1];

	for (size_t i = 0; i < this->size; i++)
	{
		container[i] = this->data[i];
	}

	container[this->size] = other;

	this->destroy();
	this->data = container;
	this->size++;

	return *this;
}

template<class T>
inline Vector<T>& Vector<T>::push(const T & other) //!< adds element to the beginning of the vector by given T reference
{
	T *container = new T[this->size + 1];

	container[0] = other;
	for (size_t i = 0; i < this->size; i++)
	{
		container[i + 1] = this->data[i];
	}

	this->destroy();
	this->data = container;
	this->size++;

	return *this;
}

template<class T>
inline T Vector<T>::popBack() //!< returns vector's last element
{
	if (this->size == 0)
	{
		throw std::logic_error("The vector is already empty!");
	}
	return this->data[--index];
}

template<class T>
inline Vector<T>& Vector<T>::operator+=(const Vector<T>& other) //!< overloads operator += for two vector references
{
	T *container = new T[this->size + other.size];	

	for (size_t i = 0; i < this->size; i++)
	{
		container[i] = this->data[i];
	}
	for (size_t i = 0; i < other.size; i++)
	{
		container[this->size + i] = other.data[i];
	}

	this->destroy();
	this->data = container;
	this->size += other.size;

	return *this;
}

template<class T>
inline Vector<T> Vector<T>::operator+(const Vector<T>& other) const //!< overloads operator + for vector and vector referenc
{
	Vector<T> container;

	container.data = new T[this->size + other.size];
	container.size = this->size + other.size;

	for (size_t i = 0; i < this->size; i++)
	{
		container.data[i] = this->data[i];
	}
	for (size_t i = 0; i < other.size; i++)
	{
		container.data[this->size + i] = other.data[i];
	}

	return container;
}

template<class T>
inline Vector<T>& Vector<T>::operator+=(const T & other) //!< overloads operator += for vector reference and T reference
{
	this->push_back(other);
	return *this;
}

template<class T>
inline Vector<T> Vector<T>::operator+(const T & other) const //!< overloads operator + for vector and T
{
	Vector<T> container;
	container = *this + other;
	
	return container;
}

template<class T>
inline T & Vector<T>::getElem(size_t index) //!< returns element by given index
{
	if (this->size <= index)
	{              //!< throws exeption  to report out of range error                             
		throw std::out_of_range("There is no elem with such index!"); //!< case if the index is bigger than vector's size
	}
	return this->data[index];
}

template<class T>
inline T & Vector<T>::operator[](size_t index) //!< overloads operator[], loaded to return T reference
{
	if (this->size <= index)
	{
		throw std::out_of_range("There is no elem with such index!");
	}
	return this->data[index];
}

template<class T>
inline T Vector<T>::operator[](size_t index) const //!< overloads operator[], loaded to return T
{
	if (this->size <= index)
	{
		throw std::out_of_range("There is no elem with such index!");
	}
	return this->data[index];
}

template<class T>
inline T & Vector<T>::returnFirst() //!< returns reference to vector's first element
{
	return this->data[0];
}

template<class T>
inline T & Vector<T>::returnLast() //!< returns reference to vector's last element
{
	return this->data[this->size - 1];
}

template<class T>
inline T Vector<T>::removeFirst() //!< removes vector's first element
{
	T *container = new T[this->size - 1];
	
	for (size_t i = 0; i < this->size - 1; i++)
	{
		container[i] = this->data[i + 1];
	}

	this->destroy();
	this->data = container;
	this->size--;

	return *container;
}

template<class T>
inline T Vector<T>::removeLast() //!< removes vector's last element
{
	T *container = new T[this->size - 1];

	for (size_t i = 0; i < this->size - 1; i++)
	{
		container = this->data[i];
	}

	this->destroy();
	this->data = container;
	this->size--;

	return *this;
}

template<class T>
inline size_t Vector<T>::length() //!< returns vector's length
{
	return this->size;
}

template<class T>
inline Vector<T>& Vector<T>::deleteElementByIndex(size_t index) //!< deletes element by given index
{
	T *container = new T[this->size - 1];

	for (int i = 0; i < this->size - 1; i++)
	{
		if (i >= index && i != this->size - 2)
		{
			container[i] = this->data[i + 1];
		}
		else
		{
			container[i] = this->data[i];
		}
	}

	this->destroy();
	this->data = container;
	this->size--;

	return *this;
}

template<class T>
inline Vector<T>& Vector<T>::deleteAll() //!< deletes all vector elements
{
	this->destroy();
	this->data = nullptr;
	this->size = 0;

	return *this;
}

#pragma once
#include"Shape.h"
#include<iostream>
/**
* @brief Class that represents the properties of class Circle which inherits the abstract class Shape
*/
class Circle : public Shape //!< inherits base class
{
private: //!< data fields
	int cx;
	int cy;
	int r;
	char* colour; //!< dynamic memory

	void copy(const Circle& other); //!< canonical representation of BIG SIX
	void destroy();

public:
	Circle(); //!< default constructor
	Circle(const Circle& other); //!< copy constructor
	Circle& operator=(const Circle& other); //!< operator =
	~Circle(); //!< destructor

	Circle(int newCx, int newCy, int newR, const char* newColour); //!< general purpose constructor
																   //!< setters and getters
	void setCx(int newCx);
	int getX()const;

	void setCy(int newCy);
	int getY()const;

	void setR(int newR);
	int getR()const;

	void setColour(const char* newColour);
	const char* getColour()const;

	void save(std::ostream& out) override; //!< overrade save method
	void print() override; //!< overrade save method
};


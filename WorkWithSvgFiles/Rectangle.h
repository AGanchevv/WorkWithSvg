#pragma once
#include"Shape.h"
#include<iostream>
/**
* @brief Class that represents the properties of class Rectangle which inherits the abstract class Shape
*/
class Rectangle : public Shape //!< inherits base class
{
private: //!< data fields
	int x;
	int y;
	int width;
	int height;
	char* colour; //!< dynamic memory

	void copy(const Rectangle& other); //!< canonical representation of BIG SIX
	void destroy();

public:
	Rectangle(); //!< default constructor
	Rectangle(const Rectangle& other); //!< copy constructor
	Rectangle& operator=(const Rectangle& other); //!< operator =
	~Rectangle(); //!< destructor

	Rectangle(int newX, int newY, int newWidth, int newHeight, const char* newColour); //!< general purpose constructor
																					   //!< setters and getters
	void setX(int newX);
	int getX()const;

	void setY(int newY);
	int getY()const;

	void setWidth(int newWidth);
	int getWidth()const;

	void setHeight(int newHeight);
	int getHeight()const;

	void setColour(const char* newColour);
	const char* getColour()const;

	void save(std::ostream& out) override; //!< overrade save method
	void print() override; //!< overrade save method
};


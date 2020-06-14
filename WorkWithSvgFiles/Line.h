#pragma once
#include"Shape.h"
#include<iostream>
/**
* @brief Class that represents the properties of class Line which inherits the abstract class Shape
*/
class Line : public Shape //!< inherits base class
{
private: //!< data fields
	int x1;
	int y1;
	int x2;
	int y2;
	char* stroke; //!< dynamic memory

	void copy(const Line& other); //!< canonical representation of BIG SIX
	void destroy();

public:
	Line(); //!< default constructor
	Line(const Line& other); //!< copy constructor
	Line& operator=(const Line& other); //!< operator =
	~Line(); //!< destructor

	Line(int newX1, int newY1, int newX2, int newY2, const char* newStroke); //!< general purpose constructor
																			 //!< setters and getters
	void setX1(int newX1);
	int getX1()const;

	void setY1(int newY1);
	int getY1()const;

	void setX2(int newX2);
	int getX2()const;

	void setY2(int newY2);
	int getY2()const;

	void setStroke(const char* newStroke);
	const char* getStroke()const;

	void save(std::ostream& out) override; //!< overrade save method
	void print() override; //!< overrade save method
};
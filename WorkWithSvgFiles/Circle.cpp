#include "stdafx.h"
#include "Circle.h"

void Circle::copy(const Circle & other) //!< copies all data from one line to another
{
	setCx(other.cx);
	setCy(other.cy);
	setR(other.r);
	setColour(other.colour);
}

void Circle::destroy() //!< deletes data to prevent memory leak from happening
{
	delete[] this->colour;
}

Circle::Circle() :colour(nullptr) //!< default constructor and colour points nullptr to prevent memory leak
{
	setCx(0);
	setCy(0);
	setR(0);
	setColour("Default colour");
}

Circle::Circle(const Circle & other) //!< copy constructor
{
	this->copy(other);
}

Circle & Circle::operator=(const Circle & other) //!< operator =
{
	if (this != &other)
	{
		this->copy(other);
	}

	return *this;
}

Circle::~Circle() //!< destructor
{
	this->destroy();
}

Circle::Circle(int newCx, int newCy, int newR, const char * newColour) //!< constructor will all necessary data given
	:colour(nullptr) //!< again colour points nullptr to rpevent memory leak
{
	setCx(newCx);
	setCy(newCy);
	setR(newR);
	setColour(newColour);
}

void Circle::setCx(int newCx) //!< setters and getters
{
	this->cx = newCx;
}

int Circle::getX() const
{
	return this->cx;
}

void Circle::setCy(int newCy)
{
	this->cy = newCy;
}

int Circle::getY() const
{
	return this->cy;
}

void Circle::setR(int newR)
{
	this->r = newR;
}

int Circle::getR() const
{
	return this->r;
}

void Circle::setColour(const char * newColour)
{
	if (newColour != NULL)
	{
		this->destroy();
		this->colour = new char[strlen(newColour) + 1];
		strcpy_s(this->colour, strlen(newColour) + 1, newColour);
	}
}

const char * Circle::getColour() const
{
	return this->colour;
}

void Circle::save(std::ostream& out) //!< this method writes in the file and saves the rectangle information in it
{                                    //!< there are specific standarts that must be met in order to create svg file successfully
	out << "  <circle cx=\"" << getX() << "\" cy=\"" << getY() << "\" r=\"" << getR() << "\" fill=\"" << getColour() << "\" />" << std::endl;
}

void Circle::print() //!< shows circle information on the console
{
	std::cout << "circle " << getX() << " " << getY() << " " << getR() << " " << getColour() << std::endl;
}
#include "stdafx.h"
#include "Rectangle.h"

void Rectangle::copy(const Rectangle & other) //!< copies all data from one line to another
{
	setX(other.x);
	setY(other.y);
	setWidth(other.width);
	setHeight(other.height);
	setColour(other.colour);
}

void Rectangle::destroy() //!< deletes data to prevent memory leak from happening
{
	delete[] this->colour;
}

Rectangle::Rectangle() :colour(nullptr) //!< default constructor and colour points nullptr to prevent memory leak
{
	setX(0);
	setY(0);
	setWidth(0);
	setHeight(0);
	setColour("Default colour");
}

Rectangle::Rectangle(const Rectangle & other) :colour(nullptr) //!< copy constructor
{
	this->copy(other);
}

Rectangle & Rectangle::operator=(const Rectangle & other) //!< operator =
{
	if (this != &other)
	{
		this->copy(other);
	}

	return *this;
}

Rectangle::~Rectangle() //!< destructor
{
	this->destroy();
}

Rectangle::Rectangle(int newX, int newY, int newWidth, int newHeight, const char * newColour) //!< constructor will all necessary data given
	:colour(nullptr) //!< again colour points nullptr to rpevent memory leak
{
	setX(newX);
	setY(newY);
	setWidth(newWidth);
	setHeight(newHeight);
	setColour(newColour);
}

void Rectangle::setX(int newX) //!< setters and getters
{
	this->x = newX;
}

int Rectangle::getX() const
{
	return this->x;
}

void Rectangle::setY(int newY)
{
	this->y = newY;
}

int Rectangle::getY() const
{
	return this->y;
}

void Rectangle::setWidth(int newWidth)
{
	this->width = newWidth;
}

int Rectangle::getWidth() const
{
	return this->width;
}

void Rectangle::setHeight(int newHeight)
{
	this->height = newHeight;
}

int Rectangle::getHeight() const
{
	return this->height;
}

void Rectangle::setColour(const char * newColour)
{
	if (newColour != NULL)
	{
		this->destroy();
		this->colour = new char[strlen(newColour) + 1];
		strcpy_s(this->colour, strlen(newColour) + 1, newColour);
	}
}

const char * Rectangle::getColour() const
{
	return this->colour;
}

void Rectangle::save(std::ostream & out) //!< this method writes in the file and saves the rectangle information in it
{                                        //!< there are specific standarts that must be met in order to create svg file successfully
	out << "  <rect x=\"" << getX()
		<< "\" y=\"" << getY()
		<< "\" width=\"" << getWidth()
		<< "\" height=\"" << getHeight()
		<< "\" fill=\"" << getColour()
		<< "\" />" << std::endl;
}

void Rectangle::print() //!< shows rectangle information on the console
{
	std::cout << "rectangle " << getX()
		<< " " << getY()
		<< " " << getWidth()
		<< " " << getHeight()
		<< " " << getColour()
		<< std::endl;
}

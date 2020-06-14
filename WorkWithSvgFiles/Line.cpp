#include "stdafx.h"
#include "Line.h"

void Line::copy(const Line & other) //!< copies all data from one line to another
{
	setX1(other.x1);
	setY1(other.y1);
	setX2(other.x2);
	setY2(other.y2);
	setStroke(other.stroke);
}

void Line::destroy() //!< deletes data to prevent memory leak from happening
{
	delete[] this->stroke;
}

Line::Line() :stroke(nullptr) //!< default constructor and stroke points nullptr to prevent memory leak
{
	setX1(0);
	setY1(0);
	setX2(0);
	setY2(0);
	setStroke("Default colour");
}

Line::Line(const Line & other) //!< copy constructor
{
	this->copy(other);
}

Line & Line::operator=(const Line & other) //!< operator =
{
	if (this != &other) //!< otherwise there will be no point of rewriting the data
	{
		this->copy(other);
	}

	return *this;
}

Line::~Line() //!< destructor
{
	this->destroy();
}

Line::Line(int newX1, int newY1, int newX2, int newY2, const char * newStroke) //!< constructor will all necessary data given
	:stroke(nullptr) //!< again stroke points nullptr to rpevent memory leak
{
	setX1(newX1);
	setY1(newY1);
	setX2(newX2);
	setY2(newY2);
	setStroke(newStroke);
}

void Line::setX1(int newX1) //!< setters and getters
{
	this->x1 = newX1;
}

int Line::getX1() const
{
	return this->x1;
}

void Line::setY1(int newY1)
{
	this->y1 = newY1;
}

int Line::getY1() const
{
	return this->y1;
}

void Line::setX2(int newX2)
{
	this->x2 = newX2;
}

int Line::getX2() const
{
	return this->x2;
}

void Line::setY2(int newY2)
{
	this->y2 = newY2;
}

int Line::getY2() const
{
	return this->y2;
}

void Line::setStroke(const char * newStroke) 
{
	if (newStroke != NULL)
	{
		this->destroy(); //!< deleting old memory to prevent memory leak
		this->stroke = new char[strlen(newStroke) + 1];
		strcpy_s(this->stroke, strlen(newStroke) + 1, newStroke);
	}
}

const char * Line::getStroke() const
{
	return this->stroke;
}

void Line::save(std::ostream & out) //!< this method writes in the file and saves the line information in it
{                                   //!< there are specific standarts that must be met in order to create svg file successfully
	out << "  <line x1=\"" << getX1()
		<< "\" y1=\"" << getY1() //!< for the quotation marks is used the symbol \ before them, because otherwise
		<< "\" x2=\"" << getX2()                 //!< it won't be read by as elemnt of the text by the program
		<< "\" y2=\"" << getY2()
		<< "\" stroke=\"" << getStroke()
		<< "\" />" << std::endl;
}

void Line::print() //!< shows line information on the console
{
	std::cout << "line " << getX1() << " " << getY1() << " " << getX2() << " " << getY2() << " " << getStroke() << std::endl;
}

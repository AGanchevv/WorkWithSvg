#pragma once
#include"Vector.h"
#include"Circle.h"
#include"Rectangle.h"
#include"Line.h"
#include"Shape.h"
#include"TextManipulating.h"
#include<fstream>
#include<iostream>
/**
* @brief In this header are located all of the methods that can be performed by the user through the console.
*/
Vector<Shape*> getCircle(Vector<char*> info, Vector<Shape*> shapes) //!< reads circle data from the file
{
	int cx, cy, r; //!< variables for the coordinates and radius
	char* colour; //!< colour

	for (int i = 1; i < 5; i++)
	{
		info[i] = getValue(info[i]);
	}

	cx = charToInt(info[1]); //!< saves the values
	cy = charToInt(info[2]);
	r = charToInt(info[3]);

	colour = new char[strlen(info[4]) + 1]; //!< sets aside memory for the colour
	strcpy_s(colour, strlen(info[4]) + 1, info[4]);

	shapes.push_back(new Circle(cx, cy, r, colour)); //!< adds a circle at the last position of the Shapes vector

	return shapes; //!< returns the vector of shapes
}

Vector<Shape*> getRect(Vector<char*> info, Vector<Shape*> shapes) //!< reds rectangle data from the file
{
	int x, y, width, height; //!< variables for the coordinates , width and height
	char* colour;

	for (int i = 1; i < 6; i++)
	{
		info[i] = getValue(info[i]);
	}

	x = charToInt(info[1]);
	y = charToInt(info[2]);
	width = charToInt(info[3]);
	height = charToInt(info[4]);

	colour = new char[strlen(info[5]) + 1];
	strcpy_s(colour, strlen(info[5]) + 1, info[5]);

	shapes.push_back(new Rectangle(x, y, width, height, colour)); //!< adds a recnagle at the last position of the vector

	return shapes; //!< returns vector
}

Vector<Shape*> getLine(Vector<char*> info, Vector<Shape*> shapes) //!< reads line info from file
{
	int x1, y1, x2, y2;
	char* stroke;

	for (int i = 1; i < 6; i++)
	{
		info[i] = getValue(info[i]);
	}

	x1 = charToInt(info[1]);
	y1 = charToInt(info[2]);
	x2 = charToInt(info[3]);
	y2 = charToInt(info[4]);

	stroke = new char[strlen(info[5]) + 1];
	strcpy_s(stroke, strlen(info[5]) + 1, info[5]);

	shapes.push_back(new Line(x1, y1, x2, y2, stroke)); //!< adds line at the last position to the vector type Shape

	return shapes; //!< returns vector
}

Vector<Shape*> open(const char* other) //!< opens file
{
	Vector<Shape*> shapes; //!< creates a vector to save data for all shapes that the program supports
	Vector<char*> info; //!< creates a vector type info

	std::ifstream in; //!< in is member constant that stands for input
	in.open(other); //!< opens the file

	if (!in.is_open() && !in.good()) //!< case if the file is not opened and the data feed is bad
	{
		std::fstream out(other, std::ios::app); //!< creates a new file if it doesn't already exist

		out << "<svg version = \"1.1\" xmlns = \"http://www.w3.org/2000/svg\">" << std::endl; 
		out << "</svg>" << std::endl; //!< there are specific standarts that must be met in order to create svg file successfully

		out.close(); //!< closes the file
	}
	else
	{
		while (!in.eof()) //!< the loop goes on until the end of the file
		{
			char information[128]; //!< static variable to save the row information

			in.get();
			in.getline(information, 128);

			if (strcmp(information, "") == 0) //!< if the row is empty the file closes and returns the vector of shapes
			{
				in.close();
				return shapes;
			}

			info = splitBySpace(information); //!< splitting the row information by space

			if (strcmp(info[0], " <circle") == 0) //!< different casses for each shape that the program supports
			{
				shapes = getCircle(info, shapes);
			}
			if (strcmp(info[0], " <rect") == 0)
			{
				shapes = getRect(info, shapes);
			}
			if (strcmp(info[0], " <line") == 0)
			{
				shapes = getLine(info, shapes);
			}
		}
	}
	in.close(); //!< closes the file

	return shapes; //!< returns vector of shapes
}

bool close(bool isFileOpen, Vector<Shape*> shapes, const char* currentFile) //!< closes file 
{
	if (isFileOpen == true) //!< case if the file is opened
	{
		shapes.deleteAll(); //!< deletes all data in the vector
		std::cout << "Successfully closed " << currentFile << std::endl; //!< shows a message

		return false;
	}
	else
	{
		std::cout << "There is no file opened!" << std::endl; //!< shows a message

		return false;
	}
}

void save(const char* other, Vector<Shape*>& shapes) //!< saves vector data in file
{
	std::ofstream out; //!< member constant for output
	out.open(other); //!< opens file

	out << "<svg version = \"1.1\" xmlns = \"http://www.w3.org/2000/svg\">" << std::endl; //!< specific row for svg files

	for (int i = 0; i < shapes.length(); i++)
	{
		shapes[i]->save(out); //!< saves each shape
	}

	out << "</svg>" << std::endl; //!< specific row for svg files
	out.close(); //!< closes the file
}

void saveFile(bool isFileOpen, Vector<Shape*> shapes, const char* currentFile) //!< saves data in File IF it is already opened
{
	if (isFileOpen == true) //!< case if the file is open
	{
		save(currentFile, shapes); //!< saves the vector data in the file
		std::cout << "Successfully saved!" << std::endl;
	}
	else
	{
		std::cout << "There is no file opened!" << std::endl;
	}
}

void help() //!< shows all of the supported commands
{
	std::cout << "     The following commands are supported: " << std::endl
		<< "open <file>        opens <file> " << std::endl
		<< "close              closes currently open file " << std::endl
		<< "save               saves the currently open file" << std::endl
		<< "saveas <file>      saves the currently open file in <file>" << std::endl
		<< "help               prints this information" << std::endl
		<< "exit               exits the program" << std::endl
		<< "print              prints all shapes that are supported" << std::endl
		<< "create             creates new shape" << std::endl
		<< "erase <n>          erases shape with serial number <n>" << std::endl
		<< "translate <n>      translates shape with serial number <n> or all if there is no <n>" << std::endl
		<< "within <option>    shows all figures contained in this area option can be circle or rectangle" << std::endl
		<< "clear              clears console" << std::endl;
}

bool exitProgram() //!< exits the program 
{
	std::cout << "Exiting the program..." << std::endl;
	return true;
}

void print(Vector<Shape*>& shapes) //!< prints all figures from the vector
{
	if (shapes.length() == 0) //!< case if there aren't any shapes
	{
		std::cout << "There are no figures supported by the program!" << std::endl;
	}
	else
	{
		for (int i = 0; i < shapes.length(); i++)
		{
			std::cout << i + 1 << ".";
			shapes[i]->print(); //!< shows each shape
		}
	}
}

void printFile(bool isFileOpen, Vector<Shape*> shapes) //!< prints all shapes in a file if it is already opened
{
	if (isFileOpen == true)
	{
		print(shapes);
	}
	else
	{
		std::cout << "There is no file opened!" << std::endl;
	}
}

Vector<Shape*> createCircle(Vector<char*>& other, Vector<Shape*> shapes) //!< creates a circle and adds it to the given vector
{
	int cx, cy, r;
	char* colour;

	cx = charToInt(other[2]);
	cy = charToInt(other[3]);
	r = charToInt(other[4]);

	colour = new char[strlen(other[5]) + 1];
	strcpy_s(colour, strlen(other[5]) + 1, other[5]);

	shapes.push_back(new Circle(cx, cy, r, colour));

	return shapes;
}

Vector<Shape*> createRect(Vector<char*>& other, Vector<Shape*> shapes) //!< creates a rectangle and adds it to the given vector
{
	int x, y, width, height;
	char* colour;

	x = charToInt(other[2]);
	y = charToInt(other[3]);
	width = charToInt(other[4]);
	height = charToInt(other[5]);

	colour = new char[strlen(other[6]) + 1];
	strcpy_s(colour, strlen(other[6]) + 1, other[6]);

	shapes.push_back(new Rectangle(x, y, width, height, colour));

	return shapes;
}

Vector<Shape*> createLine(Vector<char*>& other, Vector<Shape*> shapes)//!< creates a line and adds it to the given vector
{
	int x1, y1, x2, y2;
	char* stroke;

	x1 = charToInt(other[2]);
	y1 = charToInt(other[3]);
	x2 = charToInt(other[4]);
	y2 = charToInt(other[5]);

	stroke = new char[strlen(other[6]) + 1];
	strcpy_s(stroke, strlen(other[6]) + 1, other[6]);

	shapes.push_back(new Line(x1, y1, x2, y2, stroke));

	return shapes;
}

void create(Vector<char*>& other, Vector<Shape*>& shapes) //!< creates a figure
{
	if (strcmp(other[1], "circle") == 0) //!< different cases for each shape that the program supports
	{
		shapes = createCircle(other, shapes); //!< adds a shape to the vector
		std::cout << "Successfully created file!" << std::endl;
	}
	else if (strcmp(other[1], "rectangle") == 0)
	{
		shapes = createRect(other, shapes);
		std::cout << "Successfully created file!" << std::endl;
	}
	else if (strcmp(other[1], "line") == 0)
	{
		shapes = createLine(other, shapes);
		std::cout << "Successfully created file!" << std::endl;
	}
	else
	{
		std::cout << "This figure is not supported by the program!" << std::endl;
	}
}

void createFile(bool isFileOpen, Vector<char*> userChoice, Vector<Shape*>& shapes) //!< creates a shape from the shapes in the file
{
	if (isFileOpen == true)
	{
		create(userChoice, shapes); //!< creates a shape
	}
	else
	{
		std::cout << "There is no file opened!" << std::endl;
	}
}

void erase(size_t index, Vector<Shape*>& shapes) //!< erases shape from the given vector by index
{
	shapes.deleteElementByIndex(index);
}

Vector<Shape*> eraseShape(bool isFileOpen, Vector<Shape*> shapes, Vector<char*> userChoice) //!< erases shape if the file is opened
{
	if (isFileOpen == true)
	{
		int index = charToInt(userChoice[1]); //!< takes the index and transformes it to int

		if (index <= shapes.length() && index >= 1) //!< verification if this a shape with this index exists
		{
			erase(index - 1, shapes); //!< erases shape
			std::cout << "Successfully erased!" << std::endl;
		}
		else
		{
			std::cout << "No figure with serial number " << index << " was found!" << std::endl;
		}
	}
	else
	{
		std::cout << "There is no file opened!" << std::endl;
	}

	return shapes;
}

Vector<Shape*> translateCircle(Vector<char*> info, Vector<Shape*> shapes, int vertical, int horizontal) //!< translates circle with given values
{                                                                 //!< this method works as getCircle
	int cx, cy, r;
	char* colour;

	for (int i = 1; i < 5; i++)
	{
		info[i] = getValue(info[i]);
	}

	cx = charToInt(info[1]) + horizontal; //!< adds horizonatal and vertical values to the coordinates
	cy = charToInt(info[2]) + vertical;
	r = charToInt(info[3]);

	colour = new char[strlen(info[4]) + 1];
	strcpy_s(colour, strlen(info[4]) + 1, info[4]);

	shapes.push_back(new Circle(cx, cy, r, colour));

	return shapes;
}

Vector<Shape*> translateRect(Vector<char*> info, Vector<Shape*> shapes, int vertical, int horizontal) //!< translates rectangle with given values
{                                                    //!< this method works as getRect
	int x, y, width, height;
	char* colour;

	for (int i = 1; i < 6; i++)
	{
		info[i] = getValue(info[i]);
	}

	x = charToInt(info[1]) + horizontal;
	y = charToInt(info[2]) + vertical;
	width = charToInt(info[3]);
	height = charToInt(info[4]);

	colour = new char[strlen(info[5]) + 1];
	strcpy_s(colour, strlen(info[5]) + 1, info[5]);

	shapes.push_back(new Rectangle(x, y, width, height, colour));

	return shapes;
}

Vector<Shape*> translateLine(Vector<char*> info, Vector<Shape*> shapes, int vertical, int horizontal) //!< translates line with given values
{                                                    //!< this method works as getLine
	int x1, y1, x2, y2;
	char* stroke;

	for (int i = 1; i < 6; i++)
	{
		info[i] = getValue(info[i]);
	}

	x1 = charToInt(info[1]) + horizontal; //!< in this case horizontal and vertical should be add twice
	y1 = charToInt(info[2]) + vertical;
	x2 = charToInt(info[3]) + horizontal;
	y2 = charToInt(info[4]) + vertical;

	stroke = new char[strlen(info[5]) + 1];
	strcpy_s(stroke, strlen(info[5]) + 1, info[5]);

	shapes.push_back(new Line(x1, y1, x2, y2, stroke));

	return shapes;
}

Vector<Shape*> translate(int vertical, int horizontal, const char* other) //!< translates all shapes
{
	Vector<Shape*> shapes; //!< creates vector type Shapes
	Vector<char*> info; //!< creates vector type char* to save file data

	std::ifstream in;
	in.open(other);

	while (!in.eof())
	{
		char information[128];

		in.get();
		in.getline(information, 128);

		if (strcmp(information, "") == 0)
		{
			in.close();
			return shapes;
		}

		info = splitBySpace(information);

		if (strcmp(info[0], " <circle") == 0) //!< different cases for each shape supported by the program
		{
			shapes = translateCircle(info, shapes, vertical, horizontal);
		}
		if (strcmp(info[0], " <rect") == 0)
		{
			shapes = translateRect(info, shapes, vertical, horizontal);
		}
		if (strcmp(info[0], " <line") == 0)
		{
			shapes = translateLine(info, shapes, vertical, horizontal);
		}
	}
	in.close();

	return shapes;
}

Vector<Shape*> translateByIndex(int index, int vertical, int horizontal, const char* other) //!< translates a specific shape by given index
{
	Vector<Shape*> shapes;
	Vector<char*> info;
	int br = 0; //!< variable that increases with each shape in order to change only the shape with the given index

	std::ifstream in;
	in.open(other);

	while (!in.eof())
	{
		char information[128];

		in.get();
		in.getline(information, 128);

		if (strcmp(information, "") == 0)
		{
			in.close();
			return shapes;
		}

		info = splitBySpace(information);

		if (strcmp(info[0], " <circle") == 0)
		{
			br++; //!< the counter increases
			if (br == index) //!< case if the counter matches index
			{
				shapes = translateCircle(info, shapes, vertical, horizontal);
			}
			else
			{
				shapes = getCircle(info, shapes);
			}

		}
		if (strcmp(info[0], " <rect") == 0)
		{
			br++;
			if (br == index)
			{
				shapes = translateRect(info, shapes, vertical, horizontal);
			}
			else
			{
				shapes = getRect(info, shapes);
			}
		}
		if (strcmp(info[0], " <line") == 0)
		{
			br++;
			if (br == index)
			{
				shapes = translateLine(info, shapes, vertical, horizontal);
			}
			else
			{
				shapes = getLine(info, shapes);
			}
		}
	}
	in.close();

	return shapes;
}

Vector<Shape*> translateFile(bool isFileOpen, Vector<char*> userChoice, Vector<Shape*> shapes, const char* currentFile)
{                                 //!< translate a shape or all of the shapes in the currently opened file
	if (isFileOpen == true)
	{
		Vector<Shape*> other; //!< creates a vector 
		int vertical, horizontal, index;

		if (userChoice.length() == 4) //!< if the legth is four that means the user has entered index too
		{
			index = charToInt(userChoice[1]);

			if (index > shapes.length()) //!< verification if the a shape with this index exists in the file
			{
				std::cout << "There is not a figure with such index!" << std::endl;
			}
			else
			{
				vertical = charToInt(getVertical(userChoice[2]));
				horizontal = charToInt(getHorizontal(userChoice[3]));

				shapes = translateByIndex(index, vertical, horizontal, currentFile); //!< translates by index

				std::cout << "Translated figure number " << index << " !" << std::endl;
			}
		}
		else if (userChoice.length() == 3) //!< if the length is 3 that means the user wants to translate all shapes
		{
			vertical = charToInt(getVertical(userChoice[1]));
			horizontal = charToInt(getHorizontal(userChoice[2]));

			shapes = translate(vertical, horizontal, currentFile); //!< translates all shapes

			std::cout << "Translated all figures" << std::endl;
		}
		else
		{
			std::cout << "Incorrect input!" << std::endl;
		}
	}
	else
	{
		std::cout << "There is no file opened!" << std::endl;
	}

	return shapes;
}

Vector<Shape*> circleWithinCircle(Vector<char*> info, Vector<Shape*> shapes, int circleX, int circleY, int circleR)
{                   //!< functions that checks if a circle is within another circle and adds it to the vector
	int cx, cy, r;
	char* colour;

	for (int i = 1; i < 5; i++)
	{
		info[i] = getValue(info[i]);
	}

	cx = charToInt(info[1]);
	cy = charToInt(info[2]);
	r = charToInt(info[3]);

	int distance = sqrt((circleX - cx) * (circleX - cx) - (circleY - cy) *(circleY - cy)); //!< distance between the circle's centers

	if ((cx == circleX && cy == circleY && r == circleR) || distance + r < circleR) //!< verificaion if the data matches or
	{                                                                //!< the distance plus the radius of the circle from the file is less
		if (cx + r <= circleX + circleR && cx - r >= circleX - circleR                  //!< than the other circles radius
			&& cy + r <= circleY + circleR && cy - r >= circleY - circleR) //!< verifications if the circle's(from the file) coordinates
		{                                                       //!< with the radius obtained and substracked meet the conditions
			colour = new char[strlen(info[4]) + 1];
			strcpy_s(colour, strlen(info[4]) + 1, info[4]);

			shapes.push_back(new Circle(cx, cy, r, colour));
		}
	}

	return shapes;
}

Vector<Shape*> rectWithinCircle(Vector<char*> info, Vector<Shape*> shapes, int circleX, int circleY, int circleR)
{                //!< functions that checks if a rectangle is within circle and adds it to the vector
	int x, y, width, height;
	char* colour;

	for (int i = 1; i < 6; i++)
	{
		info[i] = getValue(info[i]);
	}

	x = charToInt(info[1]);
	y = charToInt(info[2]);
	width = charToInt(info[3]);
	height = charToInt(info[4]);

	int topLeftX = x, topLeftY = y; //!< in the svg format the given coordinates are the topLeft coordinates 
	int bottomeRightX = x + width, bottomeRightY = y + height; //!< because of the coordinate system in svg file
													   //!< the downLeft coordinates are obstained by adding the width and height
	if (topLeftX >= circleX - circleR && topLeftY >= circleY - circleR //!< verification if the two opposite edges of the rectangle
		&& bottomeRightX <= circleX + circleR && bottomeRightY <= circleY + circleR) //!< are in the circle area, because the ractangle is symmetrical
	{
		colour = new char[strlen(info[5]) + 1];
		strcpy_s(colour, strlen(info[5]) + 1, info[5]);

		shapes.push_back(new Rectangle(x, y, width, height, colour));
	}

	return shapes;
}

Vector<Shape*> lineWithinCircle(Vector<char*> info, Vector<Shape*> shapes, int circleX, int circleY, int circleR)
{                           //!< functions that checks if a line is within circle and adds it to the vector                        
	int x1, y1, x2, y2;
	char* stroke;

	for (int i = 1; i < 5; i++)
	{
		info[i] = getValue(info[i]);
	}

	x1 = charToInt(info[1]);
	y1 = charToInt(info[2]);
	x2 = charToInt(info[3]);
	y2 = charToInt(info[4]);

	if (((double)x1 - circleX) * ((double)x1 - circleX) + ((double)y1 - circleY) * ((double)y1 - circleY) <= circleR * circleR
		&& ((double)x2 - circleX) * ((double)x2 - circleX) + ((double)y2 - circleY) * ((double)y2 - circleY) <= circleR * circleR)
	{                  //!< verification if the distance between the circle center and the ends of the line
		stroke = new char[strlen(info[4]) + 1];             //!< is smaller than the circle's radius ^ 2
		strcpy_s(stroke, strlen(info[4]) + 1, info[4]);

		shapes.push_back(new Line(x1, y1, x2, y2, stroke));
	}

	return shapes;
}

Vector<Shape*> withinCircle(const char* other, int circleX, int circleY, int circleR)
{                                 //!< goes through the shapes in the file and returns only the ones
	Vector<Shape*> shapes;        //!< that are within the circle
	Vector<char*> info;

	std::ifstream in;
	in.open(other);

	while (!in.eof())
	{
		char information[128];

		in.get();
		in.getline(information, 128);

		if (strcmp(information, "") == 0)
		{
			in.close();
			return shapes;
		}

		info = splitBySpace(information);

		if (strcmp(info[0], " <circle") == 0) //!< different cases for each shape
		{
			shapes = circleWithinCircle(info, shapes, circleX, circleY, circleR);
		}
		if (strcmp(info[0], " <rect") == 0)
		{
			shapes = rectWithinCircle(info, shapes, circleX, circleY, circleR);
		}
		if (strcmp(info[0], " <line") == 0)
		{
			shapes = lineWithinCircle(info, shapes, circleX, circleY, circleR);
		}
	}
	in.close();

	return shapes;
}

Vector<Shape*> circleWithinRectangle(Vector<char*> info, Vector<Shape*> shapes, double topLeftX, double topLeftY, double bottomeRightX, double bottomeRightY)
{                          //!< functions that checks if a circle is within rectangle and adds it to the vector
	int cx, cy, r;
	char* colour;

	for (int i = 1; i < 5; i++)
	{
		info[i] = getValue(info[i]);
	}

	cx = charToInt(info[1]);
	cy = charToInt(info[2]);
	r = charToInt(info[3]);

	if (cx > topLeftX && cx < bottomeRightX && cy > topLeftY && cy < bottomeRightY
		&& cx + r >= topLeftX && cx - r <= bottomeRightX //!< checks if the coordinates are between the two opposite rectangle edges
		&& cy + r >= topLeftY && cy - r <= bottomeRightY) //!< and if the maximum and minimum circle values are still within the circle
	{
		colour = new char[strlen(info[4]) + 1];
		strcpy_s(colour, strlen(info[4]) + 1, info[4]);

		shapes.push_back(new Circle(cx, cy, r, colour));
	}

	return shapes;
}

Vector<Shape*> rectWithinRectangle(Vector<char*> info, Vector<Shape*> shapes, double topLeftX, double topLeftY, double bottomeRightX, double bottomeRightY)
{                       //!< functions that checks if a rectangle is within rectangle and adds it to the vector
	int x, y, width, height;
	char* colour;

	for (int i = 1; i < 6; i++)
	{
		info[i] = getValue(info[i]);
	}

	x = charToInt(info[1]);
	y = charToInt(info[2]);
	width = charToInt(info[3]);
	height = charToInt(info[4]);

	if (x >= topLeftX && x <= bottomeRightX && y >= topLeftY && y <= bottomeRightY
		&& x + width >= topLeftX && x - width <= bottomeRightX //!< checks if the two opposite circle(circle from the file) edges are IN
		&& y + height >= topLeftY && y - height <= bottomeRightY) //!< the space between the  two opposite edges of the other circle
	{
		colour = new char[strlen(info[5]) + 1];
		strcpy_s(colour, strlen(info[5]) + 1, info[5]);

		shapes.push_back(new Rectangle(x, y, width, height, colour));
	}

	return shapes;
}

Vector<Shape*> lineWithinRectangle(Vector<char*> info, Vector<Shape*> shapes, double topLeftX, double topLeftY, double bottomeRightX, double bottomeRightY)
{                          //!< functions that checks if a line is within rectangle and adds it to the vector
	int x1, y1, x2, y2;
	char* stroke;

	for (int i = 1; i < 5; i++)
	{
		info[i] = getValue(info[i]);
	}

	x1 = charToInt(info[1]);
	y1 = charToInt(info[2]);
	x2 = charToInt(info[3]);
	y2 = charToInt(info[4]);

	if (x1 >= topLeftX && y1 >= topLeftY //!< checks if the end of the line are between the two opposite edges
		&& x1 <= bottomeRightX && y1 <= bottomeRightY //!< of the rectangle
		&& x2 >= topLeftX && y2 >= topLeftY
		&& x2 <= bottomeRightX && y2 <= bottomeRightY)
	{
		stroke = new char[strlen(info[4]) + 1];
		strcpy_s(stroke, strlen(info[4]) + 1, info[4]);

		shapes.push_back(new Line(x1, y1, x2, y2, stroke));
	}

	return shapes;
}

Vector<Shape*> withinRectangle(const char* other, int rectangleX, int rectangleY, int rectangleWidth, int rectangleHeight)
{                                    //!< goes through the shapes in the file and returns only the ones
	Vector<Shape*> shapes;           //!< that are within the rectangle
	Vector<char*> info;

	int topLeftX, topLeftY, bottomeRightX, bottomeRightY;

	topLeftX = rectangleX;
	topLeftY = rectangleY;
	bottomeRightX = rectangleX + rectangleWidth;
	bottomeRightY = rectangleY + rectangleHeight;

	std::ifstream in;
	in.open(other);

	while (!in.eof())
	{
		char information[128];

		in.get();
		in.getline(information, 128);

		if (strcmp(information, "") == 0)
		{
			in.close();
			return shapes;
		}

		info = splitBySpace(information);

		if (strcmp(info[0], " <circle") == 0)
		{
			shapes = circleWithinRectangle(info, shapes, topLeftX, topLeftY, bottomeRightX, bottomeRightY);
		}
		if (strcmp(info[0], " <rect") == 0)
		{
			shapes = rectWithinRectangle(info, shapes, topLeftX, topLeftY, bottomeRightX, bottomeRightY);
		}
		if (strcmp(info[0], " <line") == 0)
		{
			shapes = lineWithinRectangle(info, shapes, topLeftX, topLeftY, bottomeRightX, bottomeRightY);
		}
	}
	in.close();

	return shapes;
}

void withinFile(bool isFileOpen, Vector<char*> userChoice, Vector<Shape*> shapes, const char* currentFile)
{                              //!< checks all the shapes within a circle or ractangle is the file is opened
	if (isFileOpen == true)
	{
		if (strcmp(userChoice[1], "circle") == 0)
		{
			Vector<Shape*> other; //!< creates vector
			int cx, cy, r;

			cx = charToInt(userChoice[2]);
			cy = charToInt(userChoice[3]);
			r = charToInt(userChoice[4]);

			other = withinCircle(currentFile, cx, cy, r); //!< saves all the shapes that meet the condition

			if (other.length() == 0)
			{
				std::cout << "No figures are located within " << userChoice[1] << " " << cx << " " << cy << " " << r << std::endl;
			}
			else
			{
				print(other);
			}
		}
		else if (strcmp(userChoice[1], "rectangle") == 0)
		{
			Vector<Shape*> other;
			int x, y, width, height;

			x = charToInt(userChoice[2]);
			y = charToInt(userChoice[3]);
			width = charToInt(userChoice[4]);
			height = charToInt(userChoice[5]);

			other = withinRectangle(currentFile, x, y, width, height); //!< saves all the shapes that meet the condition

			if (other.length() == 0)
			{
				std::cout << "No figures are located within " << userChoice[1] << " " << x << " " << y << " " << width << " " << height << std::endl;
			}
			else
			{
				print(other);
			}

		}

	}
	else
	{
		std::cout << "There is no file opened!" << std::endl;
	}
}
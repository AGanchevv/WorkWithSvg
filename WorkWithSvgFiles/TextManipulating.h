#pragma once
#include"Vector.h"
#include"Circle.h"
#include"Rectangle.h"
#include"Line.h"
#include"Shape.h"
#include<iostream>
/**
* @brief In this header are located all the methods that process text.
*/
Vector<char*> splitBySpace(char* other) //!< splits a sentance by space and returns the data as vector of type char*
{
	Vector<char*> separetedWords;  //!< defines vector
	int capacity = strlen(other), br = 0; //!< variables that will be used in the algorithm

	for (int i = 0; i < capacity; i++)
	{
		br++;

		if (other[i] == ' ' && i != 0) //!< case when the element is space and it is not in the start of the string
		{
			//int varBr = br; //!< saves the current br value
			char* container = new char[br - 1]; //!< sets aside enough memory to save the first word
			container[br - 1] = 0; //!< saves determinating zero

			for (int j = 0; br > 1; j++)
			{
				br--; //!< reduces br by one
				container[j] = other[i - br]; //!< saves character 
			}

			br = 0; //!< sets br to zero to be ables to save the size of the next word
			separetedWords.push_back(container);
		}
		if (i == capacity - 1) //!< case for the last word in string
		{
			char* container = new char[br]; //!< sets aside memory
			container[br] = 0; //!< determinating zero 

			for (int j = 0; br > 0; j++)
			{
				br--; //!< reduce br by one

				if (other[i - br] == ' ') //!< case if there is
				{
					i++; //!< adds one to the i in order not to save the space
				}
				container[j] = other[i - br]; //!< saves character
			}
			separetedWords.push_back(container); //!< sets the word at the end of the vector
		}
	}
	return separetedWords; //!< returns the vector of words
}

char* getValue(char* other) //!< returns the value between to quotation marks as char*
{
	int firstPosition = 0, secondPosition = 0; //!< variables to save the first quotation mark and the last one

	for (size_t i = 0; i < strlen(other); i++)
	{
		if (firstPosition == 0 && other[i] == '\"')
		{
			firstPosition = i + 1; //!< saves position plus one, because that will be the position of the first number 
		}
		if (firstPosition != 0 && other[i] == '\"')
		{
			secondPosition = i; //!< saves position
		}
	}

	char* container = new char[secondPosition - firstPosition]; //!< sets aside memory for the value

	for (int i = 0; i < secondPosition - firstPosition; i++)
	{
		container[i] = other[i + firstPosition];
	}
	container[secondPosition - firstPosition] = 0;

	return container;
}

int charToInt(const char* other) //!< returns char type number in int
{
	int converted = 0; //!< variable for saving the new number
	bool isNegative = false; //!< flag

	for (int i = 0; i < strlen(other); i++)
	{
		if (other[i] == '-' && i == 0) //!< case for negative numbers
		{
			isNegative = true;
		}
		else
		{
			converted = converted * 10 + (other[i] - '0'); //!< algorithm for converting to int
		}
	}

	if (isNegative == true) //!< case if the flag is true
	{
		converted = -converted;
	}

	return converted;
}

int charToAsciiSum(char* other) //!< method for transforming a word in a int number
{                               //!< that represents the asci sum of each character
	int sum = 0; //!< variable for the sum

	for (size_t i = 0; i < strlen(other); i++)
	{
		sum += (int)other[i]; //!< taking asci value of a character and adding it to the sum
	}

	return sum;
}

size_t recognizeCommand(char * other) //!< checks if the string matches one of the commands that
{                                      //!< the program supports
	int sum = 0;
	sum = charToAsciiSum(other); //!< transforming each word into its ascii sum, because
								 //!< each of the supported commands has a different one 
	switch (sum)      //!< switch for the sum             
	{
	case 434: return 1;
	case 534: return 2;
	case 431: return 3;
	case 643: return 4;
	case 425: return 5;
	case 442: return 6;
	case 557: return 7;
	case 628: return 8;
	case 528: return 9;
	case 974: return 10;
	case 659: return 11;
	case 519: return 12;
	default: return 0;
	}
}

char* getVertical(const char* other) //!< returns the number in char* after "vertical="
{
	int br = 0; //!< variable for container size
	char* container; //!< container to save the data

	for (int i = 0; i < strlen(other); i++)
	{
		if (other[i - 1] == '=')
		{
			br = strlen(other) - i; //!< length of the container that has to be saved
		}
	}

	container = new char[br]; //!< sets aside data
	container[br] = 0; //!< determinating zero

	for (int i = 0; i < br; i++)
	{
		container[i] = other[9 + i]; //!< 9 is the position ot the first number
	}

	return container;
}

char* getHorizontal(const char* other) //!< returns the number in type char* after "horizontal="
{                                       //!< similar as getVertical
	int br = 0;
	char* container;

	for (int i = 0; i < strlen(other); i++)
	{
		if (other[i - 1] == '=')
		{
			br = strlen(other) - i;
		}
	}

	container = new char[br];
	container[br] = 0;

	for (int i = 0; i < br; i++)
	{
		container[i] = other[11 + i];
	}

	return container;
}

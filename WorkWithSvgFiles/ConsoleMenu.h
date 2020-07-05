#pragma once
#include"Vector.h"
#include"Circle.h"
#include"Rectangle.h"
#include"Line.h"
#include"Shape.h"
#include"TextManipulating.h"
#include"ConsoleCommands.h"
#include<stdlib.h> //!<library used for clearing the console data
#include<fstream>
#include<iostream>
/**
* @brief In this header is located only one method which controls every other method that can be performed.
*/
void consoleMenu() //!< combines all the methods that can be performed by the user
{
	Vector<Shape*> shapes; //!< creates a vector type Shape

	char* currentFile = new char[300]; 
	bool isFileOpen = false, exit = false; //!< flags

	help(); //!< shows all of the supported commands

	while (exit == false)
	{
		Vector<char*> userChoice; //!< the vector in which the input is saved after splitted to words
		char input[128]; //!< static variable for the input

		std::cout << "> ";
		std::cin.getline(input, 256);
		userChoice = splitBySpace(input); //!< splits the input and saves the result

		switch (recognizeCommand(userChoice[0])) //!< recognizes the command and performes it
		{
		case 1: //!< open <file>
		{
			if (isFileOpen == false) //!< check if there is already opened file
			{
				isFileOpen = true; //!< sets the flag to true

				currentFile = new char[strlen(userChoice[1]) + 1];
				strcpy_s(currentFile, strlen(userChoice[1]) + 1, userChoice[1]);

				shapes = open(currentFile); //!< openes the file

				std::cout << "Successfully opened " << currentFile << std::endl;
			}
			else
			{
				std::cout << "Another file is already open!" << std::endl;
			}

			break;
		}
		case 2: //!< close 
		{
			isFileOpen = close(isFileOpen, shapes, currentFile);
			break;
		}
		case 3: //!< save 
		{
			saveFile(isFileOpen, shapes, currentFile);
			break;
		}
		case 4: //!< saveas <file>
		{
			saveFile(isFileOpen, shapes, userChoice[1]);
			break;
		}
		case 5: //!< help 
		{
			help();
			break;
		}
		case 6: //!< exit
		{
			exit = exitProgram();
			break;
		}
		case 7: //!< print
		{
			printFile(isFileOpen, shapes);
			break;
		}
		case 8: //!< create
		{
			createFile(isFileOpen, userChoice, shapes);
			break;
		}
		case 9: //!< erase <n>
		{
			shapes = eraseShape(isFileOpen, shapes, userChoice);
			break;
		}
		case 10: //!<translate <n>
		{
			shapes = translateFile(isFileOpen, userChoice, shapes, currentFile);
			break;
		}
		case 11: //!< within <option>
		{
			withinFile(isFileOpen, userChoice, shapes, currentFile);
			break;
		}
		case 12: //!< clear 
		{
			system("cls");
			help();
			break;
		}
		default:
		{
			std::cout << "This command is not supported by the program!" << std::endl;
			break;
		}
		}
	}
	delete[] currentFile;
}
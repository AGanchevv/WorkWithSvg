#pragma once
#include<iostream>
/**
* @brief Abstract class Shape which is inherited by other classes
*/
class Shape //!< defines acstract class Shape
{
public:                                       //!< methodes are PURE virtual, because " = 0 "
	virtual void save(std::ostream& out) = 0; //!< pure virtual methodes and the classes that inheritate this class 
	virtual void print() = 0; //!< need to override these methodes, because otherwise they will become abstract too
};//!< the pure virtual functions define the class as abstract. 


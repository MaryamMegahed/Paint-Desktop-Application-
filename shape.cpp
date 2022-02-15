/**************************************************
 * File Name :shape.cpp
 *Description:
 *source file of class shapes
 *Author:team 7
 **************************************************/

#include "shape.h"

/**************************************************
 *        Function Definitions                    *
**************************************************/
/*
 * Describtion:
 *the Default constructor of shapes class
 */
Shape::Shape()
{
}
/*
 * Describtion:
 * the getter function for rectangle
 */
bool Shape::getIsRectangle() const
{
    return isRectangle;
}
/*
 * Describtion:
 * the setter function for rectangle
 */
void Shape::setIsRectangle(bool value)
{
    isRectangle = value;
}
/*
 * Describtion:
 * the getter function for circle
 */
bool Shape::getIsCircle() const
{
    return isCircle;
}
/*
 * Describtion:
 * the setter function for circle
 */
void Shape::setIsCircle(bool value)
{
    isCircle = value;
}
/*
 * Describtion:
 * the getter function for line
 */
bool Shape::getIsLine() const
{
    return isLine;
}
/*
 * Describtion:
 * the setter function for line
 */
void Shape::setIsLine(bool value)
{
    isLine = value;
}
/*
 * Describtion:
 * the getter function for diameter of circle
 */
double  Shape::getDiameter()const
{
  return diameter;
}
/*
 * Describtion:
 * the setter function for diameter of circle
 */
void  Shape::setDiameter(double d)
{
    diameter=d;
}
/*
 * Describtion:
 * the getter function for shape name
 */
QString Shape::getShapeName()const{
    return shapeName;
}
/*
 * Describtion:
 * the setter function for shape name
 */
void Shape::setShapeName(QString s)
{
    shapeName=s;
}
/*
 * Describtion:
 * the getter function for mouse first action point
 */
double Shape::getX()const
{
    return X;
}
/*
 * Describtion:
 * the setter function for mouse first action point
 */
void Shape::setX(double x)
{
    X=x;
}
/*
 * Describtion:
 * the getter function for mouse last action point of mouse
 */
double Shape::getY()const
{
    return Y;
}
/*
 * Describtion:
 * the setter function for mouse last action point of mouse
 */
void Shape::setY(double y)
{
    Y=y;
}
/*
 * Describtion:
 * the getter function for radius of mouse action
 */
double Shape::getRadius()const
{
    return radius;
}
/*
 * Describtion:
 * the setter function for radius of mouse action
 */
void Shape::setRadius(double rr)
{
    radius=rr;
}
/*
 * Describtion:
 * the setter function for X location
 */
void Shape::setXLocation(double XLocation)
{
    this->XLocation=XLocation;
}
/*
 * Describtion:
 * the getter function for X location
 */
double Shape::getXLocation()
{
    return XLocation;
}
/*
 * Describtion:
 * the setter function for y location
 */
void Shape::setYLocation(double YLocation)
{
     this->YLocation=YLocation;
}
/*
 * Describtion:
 * the getter function for y location
 */
double Shape::getYLocation()
{
     return YLocation;
}






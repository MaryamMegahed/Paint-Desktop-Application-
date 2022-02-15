/**************************************************
 * File Name : shape.h
 * Description :
 * header file of shape class
 * Author:team 7
 **************************************************/
#ifndef SHAPE_H
#define SHAPE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include<QPainterPath>
#include <QInputDialog>
/***************************************************
 *        Function prototypes                     *
***************************************************/
class Shape
{
public:
    /*
     * Describtion:
     *the Default constructor of shapes class
     */
    Shape();

    void setColor(QColor setColor);
    QColor getColor();
    /*
     * Describtion:
     * the getter function for rectangle
     */
    bool getIsRectangle() const;
    /*
     * Describtion:
     * the setter function for rectangle
     */
    void setIsRectangle(bool value);
    /*
     * Describtion:
     * the getter function for circle
     */
    bool getIsCircle() const;
    /*
     * Describtion:
     * the setter function for circle
     */
    void setIsCircle(bool value);
    /*
     * Describtion:
     * the getter function for line
     */
    bool getIsLine() const;
    /*
     * Describtion:
     * the setter function for line
     */
    void setIsLine(bool value);
    /*
     * Describtion:
     * the getter function for diameter of circle
     */
    double getDiameter()const;
    /*
     * Describtion:
     * the setter function for diameter of circle
     */
    void setDiameter(double d);
    /*
     * Describtion:
     * the getter function for shape name
     */
    QString getShapeName()const;
    /*
     * Describtion:
     * the setter function for shape name
     */
    void setShapeName(QString s);
    /*
     * Describtion:
     * the getter function for mouse first action point
     */
    double getX()const;
    /*
     * Describtion:
     * the setter function for mouse first action point
     */
    void setX(double x);
    /*
     * Describtion:
     * the getter function for mouse last action point of mouse
     */
    double getY()const;
    /*
     * Describtion:
     * the setter function for mouse last action point of mouse
     */
    void setY(double y);
    /*
     * Describtion:
     * the getter function for radius of mouse action
     */
    double getRadius()const;
    /*
     * Describtion:
     * the setter function for radius of mouse action
     */
    void setRadius(double rr);
    /*
     * Describtion:
     * the setter function for x location
     */
    void setXLocation(double XLocation);
    /*
     * Describtion:
     * the getter function for x location
     */
    double getXLocation();
    /*
         * Describtion:
         * the setter function for y location
         */
    void setYLocation(double YLocation);
    /*
         * Describtion:
         * the getter function for y location
         */
    double getYLocation();

private:

    QString shapeName;
    double diameter;
    double radius;
    double X,Y;
    int brushWidth;
    bool isLine;
    bool isRectangle;
    bool isCircle;
    double XLocation ,YLocation;
};

#endif // SHAPE_H

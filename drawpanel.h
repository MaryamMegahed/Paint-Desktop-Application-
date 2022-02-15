/******************
 * File Name : drawpanel.h
 * Description :
 * header file of dsrawpanel class
 * Author:team 7
 ******************/
#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include<QPainterPath>
#include <QInputDialog>
#include "shape.h"
#include <QDebug>
#include <QUndoStack>
#include <vector>
#include <QStack>
#include<stack>
/**********************************************
 *        Function prototypes                 *
**********************************************/
class DrawPanel : public QWidget
{
    Q_OBJECT
public:
    /*
     * Describtion:
     *the constructor responsible for starting the program
     */
    explicit DrawPanel(QWidget *parent = nullptr);
    /*
     * Describtion:
     *the default constructor for drawpanel class
     */
    ~DrawPanel() override;
    /*
     * Describtion:
     * it is the function responsible for setting the main programm window
     */
    void start();
    /*
     * Describtion:
     *function responsible for activating mouse function
     */
    virtual void mousePressEvent(QMouseEvent *event) override;
    /*
     * Describtion:
     *function responsible for allowing action during mouse pressing period
     */
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    /*
     * Describtion:
     *function responsible for getting the required action done when mouse is pressed
     */
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    /*
     * Describtion:
     * it is the function responsible for drawing shapes in the programm window
     */
    virtual void paintEvent(QPaintEvent *event) override;
    //virtual void resizeEvent(QResizeEvent *event) override;
    /*
     * Describtion:
     * function responsible for undo action of the program
     */
    QImage undo();
    /*
     * Describtion:
     * function responsible for redo action of the program
     */
    QImage redo();

    /*
     * Describtion:
     *function responsible for opening image on the program
     */
    bool openImage();
    QVector <Shape*>myVector;
    QVector <Shape*>Vector;
    QStack <Shape*>  undo_shape;
    QStack <Shape*>  redo_shape;
    QStack <QImage>  undo_image;
    QStack <QImage>  redo_image;
    QImage getImage();
    void setImage(QImage image);



    void clear();

    void setBrushWidth (int setBrushWidth);
    /*
     * Describtion:
     * it is the function responsible for setting choosen color
     */
    void setColor(QColor setColor);
    /*
     * Describtion:
     * it is the function responsible for getting choosen color
     */
    QColor getColor();

    QColor getPrevColor() const;
    void setPrevColor(const QColor &value);
    /*
     * Describtion:
     * it is the function responsible for getting choosen pen style
     */
    Qt::PenStyle getPenStyle() const;
    /*
     * Describtion:
     * it is the function responsible for setting choosen pen style
     */
    void setPenStyle(const Qt::PenStyle &value);
    Qt::PenCapStyle getCapStyle() const;
    void setCapStyle(const Qt::PenCapStyle &value);

    Qt::PenJoinStyle getJoinStyle() const;
    void setJoinStyle(const Qt::PenJoinStyle &value);
    /*
     * Describtion:
     * the setter function for rectangle
     */
    void setIsRectangle(bool value);
    /*
     * Describtion:
     * the getter function for rectangle
     */
    bool getIsRectangle() const;
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
    * it is the function responsible for getting erasing command
    */
    bool getErase() const;
    /*
    * Describtion:
    * it is the function responsible for setting erasing command
    */
    void setErase(bool value);
    /*
     * Describtion:
     * the setter function for line
     */
    void setIsLine(bool value);

    /*
     * Describtion:
     * the getter function for line
     */
    bool getIsLine() const;

    bool getIsFilling() const;
    void setIsFilling(bool value);

    QColor getFillColor() const;
    void setFillColor(const QColor &value);

    QImage getCopyDrawing() const;
    void setCopyDrawing(const QImage &value);
    /*
     * Describtion:
     * the getter function for diameter
     */
    double getDiameter()const;
    /*
     * Describtion:
     * the setter function for diameter
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
     * the getter function for radius of the mouse movement
     */
    double getRadius()const;
    /*
     * Describtion:
     * the setter function for radius of the mouse movement
     */
    void setRadius(double rr);
    /*
     * Describtion:
     * the setter function for y location of the shape
     */
    void setXLocation(double XLocation);
    /*
     * Describtion:
     * the geetter function for y location of the shape
     */
    double getXLocation();
    void setYLocation(double YLocation);
    double getYLocation();
private:
    QImage draw;
    QImage oldimage;
    QImage change_image;
    QImage copyDrawing;
    QPoint lastPoint;
    QPoint firstPoint;
    QColor currentColor;
    QColor prevColor;
    QColor fillColor;
    Qt::PenStyle penStyle;
    Qt::PenCapStyle capStyle;
    Qt::PenJoinStyle joinStyle;
    QString shapeName;
    double diameter;
    double radius;
    double X,Y;
    int brushWidth;
    bool isDrawing;
    bool isRectangle;
    bool isCircle;
    bool eraser;
    bool isLine;
    bool isFilling;
    Shape *shape;
    Shape *shape2;
    Shape *shape3;
    bool mousePressed;
    double XLocation,YLocation;
};

#endif // DRAWPANEL_H

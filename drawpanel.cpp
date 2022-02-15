/******************
 * File Name :drawpanel.cpp
 *Description:
 *source file of class draw panel that activate the actions required
 *Author:team 7
 ******************/

#include "drawpanel.h"
#include <QImage>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>

/************************************
*        Function Definitions       *
*************************************/
/*
 * Describtion:
 *the constructor responsible for starting the program
 */
DrawPanel::DrawPanel(QWidget *parent) : QWidget(parent)
{
    start();
}

/*
 * Describtion:
 *the default constructor for drawpanel class
 */
DrawPanel::~DrawPanel() {}

/*
 * Describtion:
 * it is the function responsible for setting the main programm window
 */
void DrawPanel::start()
{
    draw = QImage(this->size(), QImage::Format_RGB32);
    // start the programm with emty white page
    draw.fill(Qt::white);
    undo_image.push(draw);
    // defalt shape colour is black
    setColor(Qt::black);
    // defalt fill colour is black
    setFillColor(Qt::black);
    // defalt pen size is 1mm
    setBrushWidth(1);
    // defalt programm style
    setPenStyle(Qt::SolidLine);
    setCapStyle(Qt::RoundCap);
    setJoinStyle(Qt::RoundJoin);
    // defalt program shapes is line
    setIsLine(true);
    // set all other shapes to zero untill action on the buttons takes place
    setIsCircle(false);
    setIsRectangle(false);
    setIsFilling(false);
    // prevent the mouse action on the buttons until get pressed
    mousePressed = false;
}

/*
 * Describtion:
 *function responsible for opening image on the program
 */
bool DrawPanel::openImage()
{
    // pass the image location to the var and change it to Qt code
    QString openImageLocation = QFileDialog::getOpenFileName(this, tr("Open image"), "", tr("PNG (.png);;JPEG (.jpg .jpeg);;BMP (.bmp)" ));
    // after coverting the image location, open it on the window
    if(!openImageLocation.isEmpty())
    {
        draw.load(openImageLocation);
        return true;
    }
    else
    {
        // no image will appear if no image is selected
        return false;
    }
}

/*
 * Describtion:
 *function responsible for activating mouse action
 */
void DrawPanel::mousePressEvent(QMouseEvent *event)
{
    // if the left button of mouse get pressed, change the mousepressed var to true and
    if (event->button() == Qt::LeftButton)
    {
        //the start of pressing mouse left button
        firstPoint = event->pos();
        //the end of pressing mouse left button
        lastPoint = event->pos();
        isDrawing = true;
        mousePressed = true;
    }
    update();
}

/*
 * Describtion:
 *function responsible for allowing action during mouse pressing period
 */
void DrawPanel::mouseMoveEvent(QMouseEvent *event)
{
    // condition checks that left mouse button is pressed, so that required action is done
    if ((event->buttons() & Qt::LeftButton) && isDrawing)
    {
        lastPoint = event->pos();
    }
    update();
}

/*
 * Describtion:
 *function responsible for getting the required action done when mouse is pressed
 */
void DrawPanel::mouseReleaseEvent(QMouseEvent *event)
{
    double D;
    double x,y;
    // check that the mouse is pressed and drawing a shape
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        shape=new Shape();
        bool ok;
        QString text = QInputDialog::getText(this, tr("Get Shape Name"),
                                             tr("Your Shape Name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !text.isEmpty())
        {
            // set the entered text to the shape name
            this->shapeName=text;
            // set the mouse first and last points to the 2 variables to be used as dimensions
            x=qFabs(lastPoint.x()-firstPoint.x());
            y=qFabs(lastPoint.y()-firstPoint.y());
            // D is the parameter refrence to each shape dimension
            D=qSqrt((x*x)+(y*y));
            // D represent the Diameter of circle
            this->radius=D;
            this->X=x;
            this->Y=y;
            if(this->getIsCircle())
                // the of circle is drawn through its circumference (dimensions of circle)
                shape->setDiameter(3.14*D);
            if(this->getIsLine())
                // the line dimensions are the first and last point
                shape->setDiameter(D);
            if(this->getIsRectangle())
                // the rectangle is drawn through it primeter
                shape->setDiameter(2*x+2*y);
            shape->setIsCircle(this->getIsCircle());
            shape->setIsRectangle(this->getIsRectangle());
            shape->setIsLine(this->getIsLine());
            shape->setShapeName(this->getShapeName());
            shape->setX(this->getX());
            shape->setY(this->getY());
            // get the location of the shape
            shape->setXLocation(firstPoint.x());
            shape->setYLocation(firstPoint.y());
            // add the drawn shape to the shapes vector
            myVector.push_back(shape);
            // add the drawn shape to the undo stack
            undo_shape.push(shape);
            // add the drawn shape to the redo stack
            redo_shape.push(shape);
        }
        // stop the mouse drawing action after realing the button
        isDrawing = false;
        // set it to false to show that the button is released
        mousePressed = false;
    }
    update();
}
/*
 * Describtion:
 * the setter function for x location of the shape
 */
void DrawPanel::setXLocation(double XLocation)
{
    this->XLocation=XLocation;
}
/*
 * Describtion:
 * the getter function for x location of the shape
 */
double DrawPanel::getXLocation()
{
    return XLocation;
}
/*
 * Describtion:
 * the setter function for y location of the shape
 */
void DrawPanel::setYLocation(double YLocation)
{
     this->YLocation=YLocation;
}
/*
 * Describtion:
 * the getter function for y location of the shape
 */
double DrawPanel::getYLocation()
{
     return YLocation;
}

/*
 * Describtion:
 * it is the function responsible for drawing shapes in the programm window
 */
void DrawPanel::paintEvent(QPaintEvent *event)
{
    // mouse var is set false at the beginning to prevent any action from taking place
    static bool wasMousePressed = false;
    QRect draw_Rect = event->rect();
    QPainter painter(this);
    painter.drawImage(draw_Rect,draw, draw_Rect);

    if(mousePressed)
    {
        // change the condition of mouse var to true when there is action on the shapes buttons
        wasMousePressed = true;
        // in case the pressed shape is circle
        if (getIsCircle())
        {
            // for a circle to be drawn, it is required 2 points to specify the diameter
            QRect circle = QRect(firstPoint, lastPoint);
            QPainter circlePainter(this);
            // set the pen width and colour of the circle
            circlePainter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));
            circlePainter.drawEllipse(circle);
            if(isFilling)
            {
                // in case the user want the circle to be completely coloured
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addEllipse(circle);
                painter.fillPath(path, fillbrush);
            }
        }
        // in case the pressed shape is rectangle
        else if (getIsRectangle())
        {
            // for a rectangle to be drawn, it is required 2 points to specify the width and lenght
            QRect rect = QRect(firstPoint, lastPoint);
            QPainter rectanglePainter(this);
            // set the pen width and colour of the rectangle
            rectanglePainter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));
            rectanglePainter.drawRect(rect);
            if (isFilling)
            {
                 // in case the user want the rectangle to be completely coloured
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addRoundedRect(rect,brushWidth, brushWidth);
                painter.fillPath(path,fillbrush);
            }
        }
        else if(getIsLine())
        {
            // for a line to be drawn, it is required 2 points to specify the end and start point
            QPainter painter(this);
            painter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));
            QLine line=QLine(firstPoint, lastPoint);
            painter.drawLine(line);
        }else{
            QPainter pencilPainter(&draw);
                      pencilPainter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));
                      pencilPainter.drawLine(lastPoint, firstPoint);
                      firstPoint = lastPoint;
        }
    }
    else if(wasMousePressed)
    {
        //the program will start collecting the data from the previous conditions to start drawing the required shape on the programm window and appear on the screen
        QPainter painter(&draw);
        painter.setPen(QPen(currentColor,brushWidth,penStyle,capStyle,joinStyle));
        if (getIsCircle())
        {
            QRect circle = QRect(firstPoint, lastPoint);
            painter.drawEllipse(circle);
            if(isFilling)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addEllipse(circle);
                painter.fillPath(path, fillbrush);
            }
        }
        else if (getIsRectangle())
        {
            QRect rect = QRect(firstPoint, lastPoint);
            painter.drawRect(rect);
            if (isFilling)
            {
                QBrush fillbrush(fillColor);
                QPainterPath path;
                path.addRoundedRect(rect,brushWidth, brushWidth);
                painter.fillPath(path,fillbrush);
            }
        }
        else if(getIsLine())
        {
            QLine line=QLine(firstPoint, lastPoint);
            painter.drawLine(line);
        }else{
           painter.drawImage(draw_Rect, draw, draw_Rect);
        }
        wasMousePressed = false;
        undo_image.push( draw);
    }
    update();
}


/*
 * Describtion:
 * it is the function responsible for clearing the programm window
 */
void DrawPanel::clear()
{
    // fill the window with white empty page
    draw.fill(Qt::white);
    update();
}
/*
 * Describtion:
 * it is the function responsible for setting choosen color
 */
void DrawPanel::setPrevColor(const QColor &value)
{
    prevColor = value;
}
/*
 * Describtion:
 * it is the function responsible for getting choosen color
 */
QColor DrawPanel::getPrevColor() const
{
    return prevColor;
}
/*
 * Describtion:
 * it is the function responsible for setting choosen pen style
 */
void DrawPanel::setPenStyle(const Qt::PenStyle &value)
{
    penStyle = value;
}
/*
 * Describtion:
 * it is the function responsible for getting choosen pen style
 */
Qt::PenStyle DrawPanel::getPenStyle() const
{
    // to adjust the pen
    return penStyle;
}


Qt::PenCapStyle DrawPanel::getCapStyle() const
{
    return capStyle;
}

void DrawPanel::setCapStyle(const Qt::PenCapStyle &value)
{
    capStyle = value;
}

Qt::PenJoinStyle DrawPanel::getJoinStyle() const
{
    return joinStyle;
}

void DrawPanel::setJoinStyle(const Qt::PenJoinStyle &value)
{
    joinStyle = value;
}

/*
 * Describtion:
 * the setter function for rectangle
 */
void DrawPanel::setIsRectangle(bool value)
{
    isRectangle = value;
}
/*
 * Describtion:
 * the getter function for rectangle
 */
bool DrawPanel::getIsRectangle() const
{
    return isRectangle;
}
/*
 * Describtion:
 * the setter function for circle
 */
void DrawPanel::setIsCircle(bool value)
{
    isCircle = value;
}
/*
 * Describtion:
 * the getter function for circle
 */
bool DrawPanel::getIsCircle() const
{
    return isCircle;
}
/*
* Describtion:
* it is the function responsible for getting erasing command
*/
bool DrawPanel::getErase() const
{
    return eraser;
}
/*
* Describtion:
* it is the function responsible for setting erasing command
*/
void DrawPanel::setErase(bool value)
{
    eraser = value;
}
/*
 * Describtion:
 * the setter function for line
 */
void DrawPanel::setIsLine(bool value)
{
    isLine = value;
}
/*
 * Describtion:
 * the getter function for line
 */
bool DrawPanel::getIsLine() const
{
    return isLine;
}
/*
 * Describtion:
 * the getter function for diameter
 */
double  DrawPanel::getDiameter()const
{
    return diameter;
}
/*
 * Describtion:
 * the setter function for diameter
 */
void  DrawPanel::setDiameter(double d)
{
    diameter=d;
}
/*
 * Describtion:
 * the getter function for shape name
 */
QString DrawPanel::getShapeName()const{
    return shapeName;
}
/*
 * Describtion:
 * the setter function for shape name
 */
void DrawPanel::setShapeName(QString s)
{
    shapeName=s;
}
/*
 * Describtion:
 * the getter function for mouse first action point
 */
double DrawPanel::getX()const
{
    return X;
}
/*
 * Describtion:
 * the setter function for mouse first action point
 */
void DrawPanel::setX(double x)
{
    X=x;
}
/*
 * Describtion:
 * the getter function for mouse last action point of mouse
 */
double DrawPanel::getY()const
{
    return Y;
}
/*
 * Describtion:
 * the setter function for mouse last action point of mouse
 */
void DrawPanel::setY(double y)
{
    Y=y;
}
/*
 * Describtion:
 * the getter function for radius
 */
double DrawPanel::getRadius()const
{
    return radius;
}
/*
 * Describtion:
 * the getter function for radius
 */
void DrawPanel::setRadius(double rr)
{
    radius=rr;
}
bool DrawPanel::getIsFilling() const
{
    return isFilling;
}

void DrawPanel::setIsFilling(bool value)
{
    isFilling = value;
}

QColor DrawPanel::getFillColor() const
{
    return fillColor;
}

void DrawPanel::setFillColor(const QColor &value)
{
    fillColor = value;
}
/*
 * Describtion:
 * the getter function for image of the shape
 */
QImage DrawPanel::getImage()
{
    return  draw;
}
/*
 * Describtion:
 * the setter function for image of the shape
 */
void DrawPanel::setImage(QImage image)
{
    draw = image;
}
QImage DrawPanel::getCopyDrawing() const
{
    return copyDrawing;
}

void DrawPanel::setCopyDrawing(const QImage &value)
{
    copyDrawing = value;
}
/*
 * Describtion:
 * it is the function responsible for setting choosen color
 */
void DrawPanel::setColor(QColor setColor)
{
    currentColor = setColor;
}
/*
 * Describtion:
 * it is the function responsible for getting choosen color
 */
QColor DrawPanel::getColor()
{
    return currentColor;
}
void DrawPanel::setBrushWidth(int setBrushWidth)
{
    brushWidth = setBrushWidth;
}
/*
 * Describtion:
 * function responsible for undo action of the program
 */
QImage   DrawPanel::undo()
{
    // when undo button is pressed, move the last shape image (the top element) in undo stack to the redo stack
    // then remove it from the undo stack, and set the new top element to appear on the window (show the previous shape)
    redo_image.push(undo_image.top());
    undo_image.pop();
    oldimage =undo_image.top();
    // when undo button is pressed, move the last shape info (the top element) in undo stack to the redo stack
    // then remove it from the undo stack, and set the new top element info to appear on the window (show the previous shape)
    redo_shape.push( undo_shape.top());
    myVector.removeAll(undo_shape.top());
    undo_shape.pop();
    return oldimage;
}
/*
 * Describtion:
 * function responsible for redo action of the program
 */
QImage DrawPanel::redo(){
    // when redo button is pressed, move the last shape image (the top element) in redo stack to the undo stack
    // then remove it from redo stack, and set the new top element to appear on the window (show the previous shape)
    undo_shape.push(redo_shape.top());
    myVector.push_back(redo_shape.top());
    redo_shape.pop();
    undo_image.push(redo_image.top());
    change_image =redo_image.pop();
    return change_image;

}

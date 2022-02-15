/**************************************************
 * File Name :mainwindow.cpp
 *Description:
 *   source file of class mainwindow,cenetral class around  which applications can be built.
 *Author:team 7
 **************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include <QColorDialog>
#include <QScrollArea>
#include <QBoxLayout>
#include <QVector>
#include <QHBoxLayout>
#include <QtMath>
#include <algorithm>
#include <QtAlgorithms>
#include "drawpanel.h"
#include <QMessageBox>
#include <QStatusBar>
/**************************************************
 *           Function Definitions                 *
**************************************************/
/*
 * Description:
 * constractor a Qmainwindow with given parent.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      drawpanel(new DrawPanel)
{
    ui->setupUi(this);

    drawpanel->show();

}
/*
 * Description:
 *  constractor that destroys the main window.
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete drawpanel;
}
/*
 * Description:
 *the dialog that apper when we press open to check if i want to save the last iamge i draw or not
 *if i pressed save -> save the image.
 *if i pressed no ->open my pc to open new image.
 */
int MainWindow::openDialog()
{
    QMessageBox dialog(QMessageBox::Question, tr("PaintQT"), tr("Do you want to save changes?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, this);
    dialog.setButtonText(QMessageBox::Yes, tr("Yes"));
    dialog.setButtonText(QMessageBox::No, tr("No"));
    dialog.setButtonText(QMessageBox::Cancel, tr("Cancel"));
    dialog.setDefaultButton(QMessageBox::Yes);

    return dialog.exec();
}
/*
 * Description:
 * when press on save button the function running out and save the image that drawen as (png).
 */
void MainWindow::on_actionSave_triggered()
{
    QImage saveDrawing = drawpanel->getImage();
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG (.png);;JPEG (.jpg .jpeg);;BMP (.bmp)");
    saveDrawing.save(filePath);
}

/*
 * Description:
 * when press on open button
 * first:call openDialog function and check if i want to save last image
 * second : open my pc to open picture from it to display on the program
 */
void MainWindow::on_actionOpen_triggered()
{
    //calling openDialog function to ask if i want to save the last image drawn or not/
    int dialog = openDialog();
    /*if pressed yes so go to save the last Qimage firstly and then open picture */
    if(dialog == QMessageBox::Yes)
    {
        on_actionSave_triggered();
        drawpanel->openImage();
    }
    //if pressed no so don't save the last Qimage and open picture that i choose from the pc/
    else if(dialog == QMessageBox::No)
    {
        drawpanel->openImage();
    }
    /*if pressed cancel so return to the mainwindow */
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}
/*
 * Description:
 * when press on the new button
 * first : call openDialog function and check if i want to save last Qimage that i drawn
 * second : open new image to draw new shapes
 */
void MainWindow::on_actionNew_triggered()
{
    //calling openDialog function to ask if i want to save the last Qimage drawn or not/
    int dialog = openDialog();
    /*if pressed yes so go to save the last Qimage firstly and then open new Qimage */
    if(dialog == QMessageBox::Yes)
    {
        on_actionSave_triggered();
        drawpanel->start();
        update();
    }
    /*if pressed no so don't save the last Qimage and open new Qimage to draw */
    else if(dialog == QMessageBox::No)
    {
        drawpanel->start();
        update();
    }
    /*if pressed cancel so return to the mainwindow */
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}
/*
 * Description:
 * when press on close button
 * first : call openDialog function and check if i want to save last Qimage that i drawn
 * second : close all the program
 */
void MainWindow::on_actionClose_triggered()
{
    //calling openDialog function to ask if i want to save the last Qimage drawn or not/
    int dialog = openDialog();
    /*if pressed yes so go to save the last Qimage firstly and then close the program */
    if(dialog == QMessageBox::Yes)
    {
        on_actionSave_triggered();
        QApplication::quit();
    }
    /*if pressed no so don't save the last Qimage and close the program */
    else if(dialog == QMessageBox::No)
    {
        QApplication::quit();
    }
    /*if pressed cancel so return to the mainwindow */
    else if(dialog == QMessageBox::Cancel)
    {
        return;
    }
}
/*
 * Description:
 * button to re-size the image
 */
void MainWindow::on_actionResize_triggered()
{
    Resize resize;
    resize.setWidth(drawpanel->getImage().width());
    resize.setHeight(drawpanel->getImage().height());
    if(resize.exec() == QDialog::Accepted)
    {
        int nWidth = resize.getWidth();
        int nHeight = resize.getHeight();

        drawpanel->resize(nWidth, nHeight);
    }

}
/*
 * Description:
 *  when press cut button
 *  first: copy the shape that wanted to cut
 *  second: clear the shape
 *  third :when clicked on paste button i paste the shape
 */
void MainWindow::on_actionCut_triggered()
{
    /*copy the shape */
    drawpanel->setCopyDrawing(drawpanel->getImage());
    /*clear the shape */
    drawpanel->clear();
    /*when clicked paste ,paste the shape */
    ui->actionPaste->setEnabled(true);
}
/*
 * Description:
 *  when press paste button
 *  paste the shape at position
 */
void MainWindow::on_actionPaste_triggered()
{
    /*get the image the drwan from getCopyDrawing function */
    drawpanel->setImage(drawpanel->getCopyDrawing());
    QPainter painter;
    /*then paste the image */
    painter.drawImage(0,0, drawpanel->getImage());
}
/*
 * Description:
 *  when press on about menu
 *  then clicked on about button
 *  then go to the about that is the description about the program
 *  that include all information about the program
 */
void MainWindow::on_actionAbout_PaintQT_triggered()
{
    About aboutDialog;
    aboutDialog.exec();
}
/*
 * Description:
 *  when press on zoom button it make zoom on the image
 */
void MainWindow::on_actionZoom_2_triggered()
{
    Zoom zoomDialog;
    if(zoomDialog.exec() == QDialog::Accepted)
    {
        int zoom = zoomDialog.getZoom();

        int newW = drawpanel->getImage().width() * zoom / 100;
        int newH = drawpanel->getImage().height() * zoom / 100;

        QImage zoomedImage = drawpanel->getImage();

        drawpanel->clear();
        drawpanel->resize(newW, newH);

        drawpanel->setImage(zoomedImage.scaled(newW, newH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}
/*
 * Description:
 * when press on sort menu
 * then press Ascneding
 * so it sort the shapes ascneding depends on it's diameter
 */
void MainWindow::on_actionAscneding_triggered()
{

    Shape *toSwap;
    //the first loop on the size of vector/
    for(int i=0; i<drawpanel->myVector.size(); i++)
    {
        /*the second loop on the size-1 of the vector */
        for(int j=0; j<drawpanel->myVector.size()-1; j++)
        {
            /*check the diamter of each shape to sort */
            if(drawpanel->myVector[j+1]->getDiameter()<drawpanel->myVector[j]->getDiameter())
            {
                toSwap=drawpanel->myVector[j];
                drawpanel->myVector[j]=drawpanel->myVector[j+1];
                drawpanel->myVector[j+1]=toSwap;
            }

        }
    }
    /* message box to display the sorted shapes by their names */
    QString name="";
    name="Shapes   Name    preimeter    X-Axis    Y-Axis\n";
    for(int i=0; i<drawpanel->myVector.length(); i++)
    {
        QString diameterString =QString::number(drawpanel->myVector[i]->getDiameter());
        QString num =QString::number(i+1);
        /*  Responsible  for getting the location of the shapes on pressing ascending*/
        QString numX =QString::number(drawpanel->myVector[i]->getXLocation());
        QString numY =QString::number(drawpanel->myVector[i]->getYLocation());
        name+="Shape "+num+" : "+drawpanel->myVector[i]->getShapeName()+"      "+ diameterString+"        "+numX+"        "+numY+"\n";
    }
    QMessageBox::information(this,"sorted", name);
}
/*
 * Description:
 * when press on sort menu
 * then press Descneding
 * so it sort the shapes descneding depends on it's diameter
 */
void MainWindow::on_actionDescneding_triggered()
{
    Shape *toSwap;
    /*the first loop on the size of vector to sort */
    for(int i=0; i<drawpanel->myVector.size(); i++)
    {
        /*the second loop on the size-1 of the vector */
        for(int j=0; j<drawpanel->myVector.size()-1; j++)
        {
            /*check the diamter of each shape to sort */
            if(drawpanel->myVector[j+1]->getDiameter()>drawpanel->myVector[j]->getDiameter())
            {
                toSwap=drawpanel->myVector[j];
                drawpanel->myVector[j]=drawpanel->myVector[j+1];
                drawpanel->myVector[j+1]=toSwap;
            }

        }
    }
    /* message box to display the sorted shapes by their names */
    QString name="";
    name="Shapes   Name    preimeter    X-Axis    Y-Axis\n";
    for(int i=0; i<drawpanel->myVector.length(); i++)
    {
        QString diameterString =QString::number(drawpanel->myVector[i]->getDiameter());
        QString num =QString::number(i+1);
        /*  Responsible  for getting the location of the shapes on pressing descending*/
        QString numX =QString::number(drawpanel->myVector[i]->getXLocation());
        QString numY =QString::number(drawpanel->myVector[i]->getYLocation());
        name+="Shape "+num+" : "+drawpanel->myVector[i]->getShapeName()+"      "+ diameterString+"        "+numX+"        "+numY+"\n";
    }
    QMessageBox::information(this,"sorted", name);
}
/*
 * Description :
 *  when press on search button
 *  i can search for certain shape by it's name
 *  and if found the shape it display it's name and information about the shape
 *  and if didn't found display message
 */
void MainWindow::on_actionSearch_triggered()
{
    bool ok,done=false;

    /*make text box to take the name of shape that the user want to search about it */
    QString text = QInputDialog::getText(this, tr("Searching"),
                                         tr("Shape_Name:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    /*if enter the name of shape and clicked ok */
    if (ok && !text.isEmpty())
    {
        /*looping on the vector that stored the shapes */
        for(int i=0; i<drawpanel->myVector.size(); i++)
        {
            /*if the entered name of shape matched with name in the vector so the shape founded and display it's name */
            if(text==drawpanel->myVector[i]->getShapeName())
            {
                done=true;
                /*display message box that conatine the name of the shape */
                QString name="";
                QString diameterString =QString::number(drawpanel->myVector[i]->getDiameter());
                /*  Responsible  for getting the location of the shapes on pressing on search */
                QString numX =QString::number(drawpanel->myVector[i]->getXLocation());
                QString numY =QString::number(drawpanel->myVector[i]->getYLocation());
                name+="ShapeName : "+drawpanel->myVector[i]->getShapeName()+"\n"+"Preimeter : "+diameterString+"\nX_Axis : "+numX+"\nY-Axis : "+numY;
                QMessageBox::information(this,"Search", name);

                break;
            }
            /*if didn't found the shape name display a message */
        }if(!done)
        {
            QMessageBox msgBox;
            msgBox.setText("Sorry:Shape is not found.");
            msgBox.exec();
        }
    }
}
/*
 * Description:
 * function that draw with the pen
 */
void MainWindow::on_draw_Button_clicked()
{
    bool correct = false;
    //set the pen size
    int size = QInputDialog::getInt(this, "Set pen size", "Pen size", 1, 1, 50, 1, &correct);

    if (correct)
    {
        drawpanel->setBrushWidth(size);
    }
}
/*
 *Description:
 *when press on circle button so activate the function of draw circle
 *and get the circumference of a circle
 */
void MainWindow::on_circle_Button_clicked()
{
    /*set the pen to draw circe or ellipse */
    drawpanel->setIsCircle(true);
    drawpanel->setIsRectangle(false);
    drawpanel->setIsLine(false);
    drawpanel->setErase(false);
    /*if the user draw circle or ellipse so here we can calculate the circumference of a circle or ellipse */
    if(!drawpanel->getShapeName().isEmpty())
    {
        drawpanel->setDiameter(3.14*2*drawpanel->getRadius());
    }
}
/*
 *Description:
 * when press on line button so activate the function of draw line
 * and calculate the length of line
 */
void MainWindow::on_lineButton_clicked()
{

    drawpanel->setIsCircle(false);
    drawpanel->setIsRectangle(false);
    /*set the pen to draw lines */
    drawpanel->setIsLine(true);
    drawpanel->setErase(false);
    //if the user draw line so here we can calculate the length of the line/
    if(!drawpanel->getShapeName().isEmpty())
    {
        drawpanel->setDiameter(drawpanel->getRadius());
    }
}

/*
 *Description:
 * when press on square button so activate the function of draw square
 * and calculate perimeter of rectangle
 */
void MainWindow::on_square_Button_clicked()
{
    /*set the pen to draw rectangle or square */
    drawpanel->setIsRectangle(true);
    drawpanel->setIsCircle(false);
    drawpanel->setIsLine(false);
    drawpanel->setErase(false);
    //if the user draw square or rectangle so here we can calculate the perimeter of the square or rectangle/
    if(!drawpanel->getShapeName().isEmpty())
    {
        drawpanel->setDiameter(2*(drawpanel->getX()+drawpanel->getY()));
    }
}
/*
 * Description:
 * when press on erase button it change the pen color to white
 */
void MainWindow::on_Erase_Button_clicked()
{
    drawpanel->setPrevColor(drawpanel->getColor());
    /* set the pen color white to clear */
    drawpanel->setColor(Qt::white);
    /* set to erase */
    drawpanel->setErase(true);
    drawpanel->setIsLine(false);
    drawpanel->setIsCircle(false);
    drawpanel->setIsRectangle(false);

}
/*
 * Description:
 *  when press on fill button it fill inside the shape with specific color
 */
void MainWindow::on_Fill_Button_clicked()
{
    QColor customColor = QColorDialog::getColor(Qt::white, this, QString("Pick a fill color"), QColorDialog::ShowAlphaChannel);
    drawpanel->setFillColor(customColor);
    drawpanel->setIsFilling(true);
}

/*
 * Description:
 * choose the pen color to draw with the pen
 */
void MainWindow::on_Pencolor_Button_clicked()
{
    QColor customColor = QColorDialog::getColor(Qt::white, this, QString("Pick a color"), QColorDialog::ShowAlphaChannel);
    drawpanel->setColor(customColor);
}
/*
 * Description:
 * when press on undo button it clear the last action
*/
void MainWindow::on_Undo_Button_clicked()
{
    /*calling function of undo */
    drawpanel->setImage(drawpanel->undo());
    QPainter painter;
    painter.drawImage(0,0, drawpanel->getImage());

}
/*
 * Description:
 *  when press on redo button it come back the last action that
 */
void MainWindow::on_Redo_Button_clicked()
{
    //calling function of redo/
    drawpanel->setImage(drawpanel->redo());
    QPainter painter;
    painter.drawImage(0,0, drawpanel->getImage());

}

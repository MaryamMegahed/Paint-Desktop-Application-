/**************************************************
 * File Name : minwindow.h
 * Description :
 * header file of class mainwindow
 * Author:team 7
 **************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <drawpanel.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QVector>
#include <QMessageBox>
#include <resize.h>
#include <about.h>
#include <zoom.h>
#include "shape.h"
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
/***************************************************
 * Function prototypes                           *
***************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*
     * Description:
     * constractor a Qmainwindow with given parent.
     */
    MainWindow(QWidget *parent = nullptr);
    /*
     * Description:
     *  constractor that destroys the main window.
     */
    ~MainWindow();
    /*
     * Description:
     *the dialog that apper when we press open to check if i want to save the last iamge i draw or not
     *if i pressed save -> save the image.
     *if i pressed no ->open my pc to open new image.
     */
    int openDialog();

private:

    Ui::MainWindow *ui;
    DrawPanel *drawpanel;


private slots:
    /*
     * Description:
     * when press on save button the function running out and save the image that drawen as (png).
     */
    void on_actionSave_triggered();
    /*
     * Description:
     * when press on open button
     * first:call openDialog function and check if i want to save last image
     * second : open my pc to open picture from it to display on the program
     */
    void on_actionOpen_triggered();
    /*
     * Description:
     * when press on the new button
     * first : call openDialog function and check if i want to save last Qimage that i drawn
     * second : open new image to draw new shapes
     */
    void on_actionNew_triggered();
    /*
     * Description:
     * when press on close button
     * first : call openDialog function and check if i want to save last Qimage that i drawn
     * second : close all the program
     */
    void on_actionClose_triggered();
    /*
     * Description:
     * button to re-size the shape after i drawn
     */
    void on_actionResize_triggered();
    /*
     * Description:
     *  when press cut button
     *  first: copy the shape that wanted to cut
     *  second: clear the shape
     *  third :when clicked on paste button i paste the shape
     */
    void on_actionCut_triggered();
    /*
     * Description:
     * when press on sort menu
     * then press Ascneding
     * so it sort the shapes ascneding depends on it's diameter
     */
    void on_actionAscneding_triggered();
    /*
     * Description:
     * when press on sort menu
     * then press Descneding
     * so it sort the shapes descneding depends on it's diameter
     */
    void on_actionDescneding_triggered();
    /*
     * Description :
     *  when press on search button
     *  i can search for certain shape by it's name
     *  and if found the shape it display it's name and information about the shape
     *  and if didn't found display message
     */
    void on_actionSearch_triggered();
    /*
     * Description:
     *  when press paste button
     *  paste the shape at position
     */
    void on_actionPaste_triggered();
    /*
     * Description:
     *  when press on about menu
     *  then clicked on about button
     *  then go to the about that is the description about the program
     *  that include all information about the program
     */
    void on_actionAbout_PaintQT_triggered();
    /*
     * Description:
     *  when press on zoom button it make zoom on the image
     */
    void on_actionZoom_2_triggered();
    /*
     * Description:
     * function that draw with the pen
     */
    void on_draw_Button_clicked();
    /*
     *Description:
     *when press on circle button so activate the function of draw circle
     *and get the circumference of a circle
     */
    void on_circle_Button_clicked();
    /*
     *Description:
     * when press on line button so activate the function of draw line
     * and calculate the length of line
     */
    void on_lineButton_clicked();
    /*
     *Description:
     * when press on square button so activate the function of draw square
     * and calculate perimeter of rectangle
     */
    void on_square_Button_clicked();
    /*
     * Description:
     * when press on erase button it change the pen color to white
     */
    void on_Erase_Button_clicked();
    /*
     * Description:
     *  when press on fill button it fill inside the shape with specific color
     */
    void on_Fill_Button_clicked();
    /*
     * Description:
     * choose the pen color to draw with the pen
     */
    void on_Pencolor_Button_clicked();
    /*
     * Description:
     * when press on undo button it clear the last action
     */
    void on_Undo_Button_clicked();
    /*
     * Description:
     *  when press on redo button it come back the last action that
     */
    void on_Redo_Button_clicked();
};
#endif // MAINWINDOW_H

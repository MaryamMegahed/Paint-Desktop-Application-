/***************************************************
 * File Name : zoom.cpp
 * Description:
 * Source file of class zoom that is responsible for zooming the image
 * Author: team 7
 **************************************************/
#include "zoom.h"
#include "ui_zoom.h"
/**************************************************
 *        Function Definitions                    *
**************************************************/
/*
 * Description:
 * function responsible for zooming action window in the program
 */
Zoom::Zoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Zoom)
{
    ui->setupUi(this);
    // the defualt window size is 200
    ui->lineEdit->setText(QString::number(200));
    ui->lineEdit->setValidator( new QIntValidator(100, 200, this) );
}
/*
 * Description:
 * the defualt constructor of zoom class
 */
Zoom::~Zoom()
{
    delete ui;
}
/*
 * Description:
 * function responsible for zooming the program main window
 */
int Zoom::getZoom() const
{
    return ui->lineEdit->text().toInt();
}

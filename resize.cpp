
/**************************************************
 * File Name :resize.cpp
 * source file of resize class
 *Author:team 7
 **************************************************/
#include "resize.h"
#include "ui_resize.h"


Resize::Resize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resize)
{
    ui->setupUi(this);
    ui->height->setValidator( new QIntValidator(1, 5000, this) );
    ui->width->setValidator( new QIntValidator(1, 5000, this) );
}
/*
 * Description:
 *  defualt constractor a of resize responsinble for destroying it
 */
Resize::~Resize()
{
    delete ui;
}
/*
 * Description:
 *  function responsible for specifying thr required height
 */
void Resize::setHeight(int value)
{
    ui->height->setText(QString::number(value));
}
/*
 * Description:
 *  function responsible for specifying thr required width
 */
void Resize::setWidth(int value)
{
    ui->width->setText(QString::number(value));
}
/*
 * Description:
 *  getter function of required height
 */
int Resize::getHeight() const
{
    return ui->height->text().toInt();
}
/*
 * Description:
 *  getter function of required width
 */
int Resize::getWidth() const
{
    return ui->width->text().toInt();
}


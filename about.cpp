/***************************************************
 * File Name : about.cpp
 * Description:
 * Source file of class about that have the main information about the program
 * Author: team 7
 **************************************************/
#include "about.h"
#include "ui_about.h"
/*
 * Description:
 * when press on button about that will open plain text that include the main information about the program
 */
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    ui->plainTextEdit->document()->setPlainText("PaintQT\n"
                                                "Application written in C++, using QT.\nOriginally made for passing 'Multiplatform programming in QT' subject at studies.\n"
                                                "version 2021 \n"
                                                "the program include functions : Undo,Redo,search,sort(descneding,ascneding),shapes\n"
                                                "made by team 7");
}

About::~About()
{
    delete ui;
}

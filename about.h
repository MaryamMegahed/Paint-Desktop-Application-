/**************************************************
 * File Name : about.h
 * Description:
 * header file of about class
 * Author :team7
 **************************************************/
#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
/**************************************************
 *          Functions Prototypes                  *
 **************************************************/
namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H

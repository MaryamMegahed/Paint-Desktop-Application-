/**************************************************
 * File Name : zoom.h
 * Description :
 * header file of class zoom
 * Author:team 7
 **************************************************/
#ifndef ZOOM_H
#define ZOOM_H

#include <QDialog>
#include <QIntValidator>
/***************************************************
 *      Function prototypes                        *
***************************************************/
namespace Ui {
class Zoom;
}

class Zoom : public QDialog
{
    Q_OBJECT

public:
    /*
     * Description:
     * function responsible for zooming action window in the program
     */
    explicit Zoom(QWidget *parent = nullptr);
    /*
     * Description:
     * the defualt constructor of zoom class
     */
    ~Zoom();
    /*
     * Description:
     * function responsible for zooming the program main window
     */
    int getZoom() const;

private:
    Ui::Zoom *ui;

    int zoom;
};

#endif // ZOOM_H

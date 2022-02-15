/**************************************************
 * File Name : resize.h
 * Description:class responsible for resizing the main window
 * header file of resize class
 * Author :team7
 **************************************************/
#ifndef RESIZEDIALOG_H
#define RESIZEDIALOG_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class Resize;
}

class Resize : public QDialog
{
    Q_OBJECT

public:
    explicit Resize(QWidget *parent = nullptr);
    /*
     * Description:
     *  defualt constractor a of resize.
     */
    ~Resize();
    /*
     * Description:
     *  getter function of required width
     */
    int getWidth() const;
    /*
     * Description:
     *  getter function of required height
     */
    int getHeight() const;
    /*
     * Description:
     *  function responsible for specifying thr required width
     */
    void setWidth(int value);
    /*
     * Description:
     *  function responsible for specifying thr required height
     */
    void setHeight(int value);

private slots:

private:
    Ui::Resize *ui;
    int width;
    int height;
};

#endif // RESIZEDIALOG_H

#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <ui_interface.h>
#include <glwidget.h>

namespace Ui
{
    class Interface;
}

class Interface : public QWidget, private Ui::Interface
{
    Q_OBJECT

public:
    explicit Interface(QWidget *parent = 0);

//signals:
//    void valueChanged(int value);


private slots:
    //void on_satID_valueChanged(int value);
    void on_timeSpeed_valueChanged();
    void on_simulate_clicked();
    void slotTimer();


private:
    QTimer timer;
    GLWidget *widget;
    int max;
    int min;
public:
     void setGLWidget(GLWidget*);
};

#endif // INTERFACE_H

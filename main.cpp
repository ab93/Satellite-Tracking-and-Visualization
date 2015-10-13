#include <QGLWidget>
#include <QtDebug>
#include <window.h>
#include <qt4/QtGui/QApplication>
//#include <QtGui/QApplication>
#include "interface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(QGLFormat::hasOpenGL ())
        qDebug()<<"has opengl";

    if(QGLFormat::hasOpenGLOverlays ())
        qDebug()<<"has opengl overlay";

    qDebug()<<QGLFormat::openGLVersionFlags ();

    Window window;
    window.show();

    Interface I;
    I.setGLWidget(window.glWidget);
    I.show();

    return a.exec();
}

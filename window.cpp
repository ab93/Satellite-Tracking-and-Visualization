#include <QtGui>
#include<qt4/QtGui/qlayout.h>
#include "glwidget.h"
#include "window.h"


Window::Window(int index)
{
    glWidget = new GLWidget(index);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(glWidget);
    setLayout(mainLayout);



    setWindowTitle(tr("Satellite Tracking"));

}


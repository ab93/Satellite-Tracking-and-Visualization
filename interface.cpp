#include <QGLWidget>
#include "interface.h"
#include "ui_interface.h"
#include "window.h"
#include "satellite.h"
#include <iostream>
using namespace std;


Interface::Interface(QWidget *parent) :QWidget(parent)
{
    setupUi(this);
    timer.start(100);
    //connect(&timer,SIGNAL(timeout()),this,SLOT(slotTimer()),Qt::AutoConnection);
    connect(&timer,SIGNAL(timeout()),this,SLOT(slotTimer()));

    min = 1;
    max = 20;
    timeSpeed->setFocusPolicy(Qt::StrongFocus);
    timeSpeed->setTickPosition(QSlider::TicksBothSides);
    timeSpeed->setTickInterval(20);
    timeSpeed->setMaximum(max);
    timeSpeed->setMinimum(min);
}

void Interface::on_timeSpeed_valueChanged()
{
    int val = timeSpeed->value();
    widget->SetUserInput(val);

}

void Interface::on_simulate_clicked()
{
    if(satID->value() > 23)
        exit(0);
    else
    {
        Window window(satID->value());
        window.show();
        //startProcess();
        ResetCOUNT();
    }
}


void Interface::slotTimer()
{
   SatelliteParam sat_par;
   widget->GetSatelliteInfo(sat_par);
   altitude->setText(QString::number(sat_par.altitude));
   velocity->setText(QString::number(sat_par.velocity));
   footprint->setText((QString::number((sat_par.footprint))));
   latitude->setText(QString::number(sat_par.latitude));
   longitude->setText(QString::number(sat_par.longitude));
   satName->setText(sat_par.name);
   date->setText(sat_par.date);

}

void Interface::setGLWidget(GLWidget* glwidget)
{
    widget = glwidget;
}


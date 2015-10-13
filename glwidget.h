#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include<QTimer>
#include "dataTypes.h"
#include <vector>
#include <glm/glm.hpp>
#include <iterator>
#include <vector>
#include <GL/glu.h>
using namespace std;

static int COUNT_temp;
static vector<double> x_coord;
static vector<double> y_coord;
static vector<double> z_coord;
static vector<double>::iterator itr_x;
static vector<double>::iterator itr_y;
static vector<double>::iterator itr_z;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(int index = 0,QWidget *parent = 0);
    ~GLWidget();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    float scalingParam;
    //void getSatelliteParam(double &x, double &y, double &z, double &velocity);
    void GetSatelliteInfo(SatelliteParam &sat_par);
    void SetUserInput(int &value);


//    vector<glm::vec4> sat_vertices;
//    vector<glm::vec3> sat_normals;
//    vector<GLushort> sat_elements;

public slots:
    void rotate();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void wheelEvent( QWheelEvent *event );
    void scalePlus();
    void scaleMinus();


private:
    GLuint makeObject();
    GLuint object;
    QPoint lastPos;
    QColor trolltechGreen;
    QColor trolltechPurple;

    GLsizei g_width ;   // width and height of the window
    GLsizei g_height;

    GLboolean g_rotate;    // whether to animate

    GLUquadricObj * g_sphere;  // texture and glu data

    GLUquadricObj *g_cube;

    GLuint g_img;
    GLuint g_img_moon;

    GLfloat g_angle_x;
    GLfloat g_inc;
    char g_filename[128];
    GLfloat scale;
    GLfloat g_light_position[4];   // light position
    GLfloat roty;
    GLfloat rotx;
    GLfloat rotz;
    QTimer timer;

    SatelliteParam sat_info;




};

#endif

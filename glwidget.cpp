#include <QtGui>
#include <QtOpenGL>
#include <math.h>
#include "glwidget.h"
#include "satellite.h"
#include "loadobj.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

int satID;

GLWidget::GLWidget(int index,QWidget *parent) : QGLWidget(parent)
{
    object = 0;

    g_width = 320;          // width and height of the window
    g_height = 320;

    g_rotate = GL_TRUE;     // whether to animate

    g_sphere = NULL;        // texture and glu data
    g_img = 0;

    g_img_moon = 0;

    g_angle_x = 27.0f;
    g_inc = 0.0f;

    g_light_position[0] = -4.0f;    // light position
    g_light_position[1] = -2.2f;
    g_light_position[2] = -8.0f;
    g_light_position[3] = 0.0f;

    scalingParam = 5.3333E-4;

    satID = index;

    printf("\nsatID(cons): %d\n",satID);

    COUNT_temp = 0;

    setFocusPolicy(Qt::StrongFocus);
    scale = 1.0;
    roty = 0;
    rotx = 0;
    rotz = 0;
    timer.start(10);

    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));


}

GLWidget::~GLWidget()
{
    makeCurrent();
    glDeleteLists(object, 1);
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::initializeGL()
{

    //GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
    //GLfloat mat_shininess[] = {50.0};

    GLfloat light_position[] = {-100.0,0.0,0.0,0.0};
    GLfloat light_ambient[] = {10.0,10.0,10.0,1};
    GLfloat light_diffuse[] = {200.0,200.0,200.0,1.0};

    glClearColor( 0.0f, 0.0f,0.0f, 0 );

    glShadeModel( GL_SMOOTH );   // SET THE SHADING MODEL TO SMOOTH

    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_diffuse);
    glLightfv(GL_LIGHT1,GL_AMBIENT,light_ambient);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS,mat_shininess);
    //glLightfv(GL_LIGHT0, GL_POSITION, g_light_position);

    glEnable( GL_DEPTH_TEST );   // ENABLE DEPTH

    glFrontFace( GL_CCW );   // SET THE FRONT FACES OF THE POLYGONS

    glEnable( GL_CULL_FACE );    // CULL FACES

    glLineWidth( 1.0f );  // SET THE INITIAL LINE WIDTH

    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );   // MATERIAL HAVE DIFFUSE AND AMBIENT LIGHTING

    glEnable( GL_LIGHTING );  // ENABLE LIGHTING

    glLightModeli( GL_FRONT, GL_TRUE );   // ENABLE LIGHTING FOR FRONT

    //glEnable( GL_COLOR_MATERIAL );  // ENABLE COLOR

    glEnable( GL_LIGHT0 );   // ENABLE LIGHT0
    glEnable( GL_LIGHT1 );

    g_sphere = gluNewQuadric( );                            // INITIALIZE OUR SPHERE
    gluQuadricNormals( g_sphere, ( GLenum )GLU_SMOOTH );
    gluQuadricTexture( g_sphere, GL_TRUE );


//    g_cube = gluNewQuadric( );                            // INITIALIZE OUR SPHERE
//    gluQuadricNormals( g_cube, ( GLenum )GLU_SMOOTH );
//    gluQuadricTexture( g_cube, GL_TRUE );


    glPixelStorei( GL_UNPACK_ALIGNMENT, 3 );                           // SET TEXTURE STATE
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    // READ THE TEXTURE

    glGenTextures( 1, &g_img );    // GENERATE OPENGL TEXTURE
    QImage image("earth.jpg");
    QImage image_moon("moon.tif");

    g_img = bindTexture (image);
    g_img_moon = bindTexture(image_moon);

    glTexImage2D(GL_TEXTURE_2D,image.width(),GL_RGBA,image.height(),0,0, GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image.bits()
                 );

    glTexImage2D(GL_TEXTURE_2D,image_moon.width(),GL_RGBA,image_moon.height(),0,0,GL_RGBA, GL_UNSIGNED_BYTE,image_moon.bits());

    startProcess();


}

void GLWidget::paintGL()
{
    static GLfloat x = 0.0f;
    double x_temp, y_temp, z_temp;


    //load_obj("satellite.obj",sat_vertices,sat_normals,sat_elements);



    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  // CLEAR THE COLOR AND DEPTH BUFFERS

    if( g_img )
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, g_img );
    }


    glPushMatrix( );    // SAVE THE CURRENT MATRIX


    // glRotatef( g_angle_x, 1.0f, 0.0f, 0.0f );      // ROTATE THE VIEW POINT
    // g_angle_x += g_inc;
    glTranslatef(0.0,0.0,-4.0);
    glRotatef(15.0,1.0,0.0,0.0);


    glRotatef( -90.0f, 1.0f, 0.0f, 0.0f );             // ROTATE THE PLANET
    glRotatef( roty, 1.0f, 0.0f, 0.0f );
    glRotatef( g_angle_x * 2, 0.0f, 0.0f, 1.0f );

    //glRotatef(rotx * 3,1.0f, 0.0f, 0.0f);
    //glRotatef(rotz * 3,0.0f, 0.0f, 1.0f);

    glScalef(scale,scale,scale);
    x += .4f;


    glColor3f( 1.0f, 1.0f, 1.0f );                     // DRAW THE EARTH
    //gluSphere( g_sphere, 1.28f, 60, 60 );
    gluSphere( g_sphere, 6378 * scalingParam, 60, 60 );
    //glTranslatef(3.5,0,0);


    //vector_t coord;

    //coord = getSatelliteCoordinates(satID);

    GetSatelliteInfo(sat_info);

    printf("satID: %d\n",satID);


    x_coord.push_back(sat_info.coord.x * scalingParam);
    y_coord.push_back(sat_info.coord.y * scalingParam);
    z_coord.push_back(sat_info.coord.z * scalingParam);

    //cout<<x_coord.size()<<" "<<x_coord[0];
    //exit(0);


    COUNT_temp++;

    if(COUNT_temp==1)
    {
        x_temp = x_coord[0];
        y_temp = y_coord[0];
        z_temp = z_coord[0];

    }

    if(x_coord[COUNT_temp - 1] == x_temp && y_coord[COUNT_temp - 1] == y_temp && COUNT_temp != 1)
    {
        exit(0);
    }
    //if(COUNT_temp>100)
    //else
    //{
        glBegin(GL_LINE_LOOP);
        //while(itr_x != x_coord.end())

        for(int i=0; i<x_coord.size(); i++)
        {
            glVertex3f(x_coord[i],y_coord[i],z_coord[i]);
        }
        //cout<<endl<<x_coord[COUNT_temp - 1]<<" "<<x_temp<<endl;
        glEnd();
        glFlush();
    //}


    // glPushMatrix();

            glRotatef(23.5,0.0,0.0,1.0);   //USE THIS FOR AXIS INCLINATION
            //glRotatef(15,0.0,1.0,0.0);

    // glPopMatrix();

    //qglColor(Qt::red);
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);

    glVertex3d(sat_info.coord.x * scalingParam,sat_info.coord.y * scalingParam,sat_info.coord.z * scalingParam);

    glEnd();

    //glEnd();

    glPopMatrix( );


    if( g_img )
        glDisable( GL_TEXTURE_2D );

    glFlush( );
 }

void GLWidget::resizeGL(int w, int h)
{    
    g_width = w; g_height = h;     // SAVE THE NEW WINDOW SIZE

    glViewport(0, 0, w, h);     // MAP THE VIEWPORT TO THE CLIENT AREA

    glMatrixMode(GL_PROJECTION);    // SET THE MATRIX MODE TO PROJECT

    glLoadIdentity();      // LOAD THE IDENTITY MATRIX

    gluPerspective(45.0, (GLfloat) w / (GLfloat) h, 1.0, 300.0);      // CREATE THE VIEWING FRUSTUM

    glMatrixMode(GL_MODELVIEW);     // SET THE MATRIX TO MODELVIEW

    glLoadIdentity();    // LOAD THE IDENTITY MATRIX

    glTranslatef(0.0, 0.0, -10.0f );     // TRANSLATE SO WE CAN HAVE A BETTER VIEW

    //glLightfv( GL_LIGHT0, GL_POSITION, g_light_position );   // SET THE POSITION OF LIGHT
    //glLightfv( GL_LIGHT1, GL_POSITION, g_light_position );
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
   int dx = event->x() - lastPos.x();
   int dy = event->y() - lastPos.y();

   if(event->buttons() & Qt::LeftButton)
   {
        roty += 0.05f * dy;
        g_angle_x += 0.05f * dx;
   }

//    rotx += 180/scale * (float)(event->y()/lastPos.y()) / height();
//    rotz += 180/scale * (float)(event->x()/lastPos.x()) / width();

//    lastPos = event->pos();

//    if(rotx >= 360)
//        rotx = 0;

//    if(rotz >= 360)
//        rotz = 0;

//    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        scalePlus();
    else if(event->delta() < 0)
        scaleMinus();

    updateGL();
}

void GLWidget::scalePlus()
{
    scale *= 1.15;
}

void GLWidget::scaleMinus()
{
    scale /= 1.15;
}

GLuint GLWidget::makeObject()
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    glEndList();
    return list;
}
void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key() )
    {

    case Qt::Key_Q:
        exit(1);
        break;
    case Qt::Key_Up:
        // scale *= 1.2f;
        roty += 5.0f;
        break;
    case Qt::Key_Down:
        //scale /= 1.2f;
        roty -= 5.0f;
        break;
    case Qt::Key_Left:
        g_angle_x -= 5.0f;
        break;
    case Qt::Key_Right:
        g_angle_x += 5.0f;
        break;
    case Qt::Key_PageDown:
        scale *= 1.2f;
        // roty += 1.6f;
        break;
    case Qt::Key_PageUp:
        scale /= 1.2f;
        //roty -= 1.6f;
        break;
    }
 updateGL();
}

void GLWidget::rotate()
{
    g_angle_x += .36f;
    updateGL();
}


 void GLWidget::GetSatelliteInfo(SatelliteParam &sat_par)
 {
     SatelliteParam temp;
     temp = GetSatelliteParam(satID);
     sat_par = temp;
 }

 void GLWidget::SetUserInput(int &value)
 {
     SetCountSpeed(value);
 }




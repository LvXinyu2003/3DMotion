#include "glwidget.h"
#include <QDebug>
#include <QPoint>
#include <QVector3D>
#include <glut.h>
#include <qmath.h>

//hcy*********************************************************************
GLWidget::GLWidget(QWidget* parent)
    : QGLWidget(parent)
{

    /*初始化成员*/
    eyex = 0.1;
    eyey = 0.1;
    eyez = 0.1;

    upx = 0;
    upy = 0.1;
    upz = 0;

    CurrentAngleZ = 0;
    CurrentAngleY = 0;
    LastAngleZ = M_PI / 4;
    LastAngleY = M_PI / 4;
}

void GLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    //glClearColor(0.757,0.973,0.694,0.0);//淡绿色背景
    // glClearColor(0.741,0.745,0.957,0.0);//淡蓝色背景
    glClearColor(0.93,0.93,0.957,0.0);//淡蓝色背景2
    //glClearColor(0.894, 0.949, 0.996, 0.0); //淡蓝色背景3
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void GLWidget::paintGL()
{

    // if(clear==0){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear=1;}

    glMatrixMode(GL_MODELVIEW); //定义哪一个矩阵是当前矩阵
    glLoadIdentity(); //用恒等矩阵替换当前矩阵

    //设定一个变换视点
    gluLookAt(eyex * 0.1, eyey * 0.1, eyez * 0.1, 0, 0, 0, upx * 0.1, upy * 0.1, upz * 0.1);
    drawCoordinate();
    glColor3f(1, 0, 1);

    glPushMatrix(); //glPushMatrix()和glPopMatrix()的配对使用可以消除上一次的变换对本次变换的影响。使本次变换是以世界坐标系的原点为参考点进行
    //平移、旋转、缩放变换
    //glTranslated(m_xTranslation,m_yTranslation,0.0f);平移
    //glRotatef(m_xRotation,1.0f,0.0f,0.0f); 旋转
    //glRotatef(m_yRotation,0.0f,1.0f,0.0f);
    glScalef(m_xScaling, m_yScaling, m_zScaling); //缩放

    DrawShape(); //根据Id选择画出什么样得图形
    //qDebug()<<"画图结束";

    glPopMatrix();
}

void GLWidget::drawCoordinate()
{
    /*红色轴是X轴，绿色是Y轴，蓝色是Z轴*/
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.5, 0.0f, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    // glutWireCone(0.027,0.09,10,10);
    glPopMatrix();

    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.5f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    //glutWireCone(0.027,0.09,10,10);
    glPopMatrix();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    glPushMatrix();
    glTranslatef(0.0, 0.0f, 0.5f);
    //glutWireCone(0.027,0.09,10,10);
    glPopMatrix();
}

void GLWidget::RotateViewPoint()
{
    float avAnale = M_PI / 180 * 0.6; //把每次移动的角度单位化

    /*把每次移动点跟开始按下鼠标记录的点作差，然后乘以avAngle,最后把上一次释放鼠标后时记录的
      角度相加起来*/
    CurrentAngleZ = (EndPoint.x() - StartPoint.x()) * avAnale;
    CurrentAngleZ += LastAngleZ;
    CurrentAngleY = (EndPoint.y() - StartPoint.y()) * avAnale;
    CurrentAngleY += LastAngleY;

    QVector3D vector1(sin(CurrentAngleY) * sin(CurrentAngleZ), cos(CurrentAngleY), sin(CurrentAngleY) * cos(CurrentAngleZ));
    vector1 = vector1.normalized(); //将坐标单位化
    eyex = vector1.x();
    eyey = vector1.y();
    eyez = vector1.z();

    /*主要计算第三组坐标*/
    QVector3D vectorA(0, sin(CurrentAngleY), 0);
    QVector3D vectorB = QVector3D(0, 0, 0) - QVector3D(sin(CurrentAngleY) * sin(CurrentAngleZ), 0, sin(CurrentAngleY) * cos(CurrentAngleZ));
    QVector3D vectorAB = QVector3D::crossProduct(vectorA, vectorB);

    QVector3D vectorC = QVector3D(0, 0, 0) - vector1;
    QVector3D vector2 = QVector3D::crossProduct(vectorC, vectorAB);
    vector2 = vector2.normalized();
    upx = vector2.x();
    upy = vector2.y();
    upz = vector2.z();
}

void GLWidget::mousePressEvent(QMouseEvent* e)
{

    QPoint st(e->pos());
    StartPoint = st;
}

void GLWidget::mouseReleaseEvent(QMouseEvent* e)
{
    /*记录上一次的角度*/
    LastAngleZ = CurrentAngleZ;
    LastAngleY = CurrentAngleY;
}

void GLWidget::mouseMoveEvent(QMouseEvent* e)
{
    QPoint ed(e->pos());
    EndPoint = ed;
    RotateViewPoint();
    this->updateGL();
    // paintGL();
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    // QRect tmp=this->geometry();//获取窗口的位置以及大小并保存在tmp中。
    if (event->delta() > 0) { //如果滚轮往上滚
        //       tmp.setWidth(tmp.width()+25);//设置宽度为原有基础上+25
        //       tmp.setHeight(tmp.height()+15);//设置窗口高度为原有基础上+20
        //       this->setGeometry(tmp);//然后设置窗口大小。
        m_xScaling += 0.1f;
        m_yScaling += 0.1f;
        m_zScaling += 0.1f;

    } else { //同样的
        //       tmp.setWidth(tmp.width()-25);
        //       tmp.setHeight(tmp.height()-15);
        //如果缩小之后的窗口不小于设置的最小窗口尺寸，则执行缩放。
        //if(this->minimumSize().height()<tmp.height()&&this->minimumSize().width()<tmp.width())
        // this->setGeometry(tmp);
        if (m_xScaling > 0.2) {
            m_xScaling -= 0.1f;
            m_yScaling -= 0.1f;
            m_zScaling -= 0.1f;
        }
    }
    this->updateGL();
}

void GLWidget::getId(int id)
{
    Id = id;
    i++;
    qDebug() << "点击按键";
    //    points_x.push_back(i/100.0);
    //    points_y.push_back(i/100.0);
    //    points_z.push_back(i/100.0);
    updateGL();
    //paintGL();
}

void GLWidget::DrawShape()
{

    //画一个点

    for (int m = 0; m < points_x.size(); m++) {
        if (m <= 0) {
            glPointSize(3.0f);
            glColor4f(0.9, 0.5, 0.7, 0.5);
            glBegin(GL_POINTS);
            //glVertex3f(points_x[m],points_y[m],points_z[m]);//应该按照笛卡尔坐标系，即先y再x再z
            glVertex3f(points_y[m], points_z[m], points_x[m]);
            glEnd();
        } else {
            //

            glLineWidth(0.5); //  宽度
            glColor4f(0.5, 0.5, 0.5, 0.5);
            if ((xyz_mode[m] == 1) && (xyz_mode[m - 1] == 1)) //8.31
            {
                glBegin(GL_LINES);

                //glVertex3f(points_x[m-1],points_y[m-1],points_z[m-1]);
                //glVertex3f(points_x[m],points_y[m],points_z[m]);
                glVertex3f(points_y[m - 1], points_z[m - 1], points_x[m - 1]); //应该按照笛卡尔坐标系，即先y再x再z
                glVertex3f(points_y[m], points_z[m], points_x[m]);
                glEnd();

            } else if ((xyz_mode[m] == 1) && (xyz_mode[m - 1] == 0)) //8.31
            {
                glBegin(GL_LINES);

                //glVertex3f(points_x[m-1],points_y[m-1],points_z[m-1]);
                //glVertex3f(points_x[m],points_y[m],points_z[m]);
                glVertex3f(points_y[m - 1], points_z[m - 1], points_x[m - 1]); //应该按照笛卡尔坐标系，即先y再z再x
                glVertex3f(points_y[m], points_z[m], points_x[m]);
                glEnd();
            }

            //                   else if((xyz_mode[m]==1)&&(xyz_mode[m-1]==0))//8.31
            //                   {
            //                   glBegin(GL_LINES);

            //                   glVertex3f(points_x[m-1],points_y[m-1],points_z[m-1]);
            //                   glVertex3f(points_x[m],points_y[m],points_z[m]);
            //                   glEnd();

            //                   }

            //qDebug()<<xyz_mode[m]<<xyz_mode[m-1];
            //画出当前点，用大点表示
            glPointSize(4.0f);
            glColor4f(0.9, 0.5, 0.7, 0.5);
            glBegin(GL_POINTS);
            glVertex3f(points_y.back(), points_z.back(), points_x.back()); //先画红再绿再蓝
            glEnd();
            //
        }
    }

    //glVertex3f((i/10.0), 0.8f,0.1f);//x红,z绿,y蓝
    //qDebug()<<"画点线";

    //  i++;qDebug()<<i;
}
//hcy*****************************************************************************************************************

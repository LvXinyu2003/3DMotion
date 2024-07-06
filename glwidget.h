#ifndef GLWIDGET_H
#define GLWIDGET_H
#include<QGLWidget>
#include<QMouseEvent>
#include <vector>
#include <iostream>
#include <QDebug>
using namespace std;
class QVector3D;
class GLWidget:public QGLWidget
{
    Q_OBJECT

public:
    int i =0;
    bool clear=0;
    GLWidget(QWidget *parent=0);

    void DrawShape();
    int get() {return Id;} //把ID给配置对象
    vector<float> points_x;
    vector<float> points_y;
    vector<float> points_z;
    vector<int> xyz_mode;
    int g_mode00or01=0;//默认G00快速移动模式

    void paintGL();

private:
    int Id;//选择画什么图
    QPoint StartPoint;     //记录鼠标按下的点
    QPoint EndPoint;       //鼠标移动过程中的点

    /*gluLookAt函数中第一组坐标跟第三组坐标*/
    GLdouble eyex;
    GLdouble eyey;
    GLdouble eyez;

    GLdouble upx;
    GLdouble upy;
    GLdouble upz;


    float CurrentAngleZ;     //当前与Z轴的夹角
    float CurrentAngleY;     //当前与Y轴的夹角

    float LastAngleZ;        //上一次与Z轴的夹角
    float LastAngleY;        //上一次与Y轴的夹角



   float m_xScaling=5.0;
   float m_yScaling=5.0;
   float m_zScaling=5.0;
//

protected:
    void initializeGL();
    void resizeGL(int w, int h);


    void drawCoordinate();   //画坐标轴
    void RotateViewPoint();  //用鼠标旋转视点

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent*event);//滚轮

public slots:
    void getId(int id);
};

#endif // GLWIDGET_H

#include "dialog.h"
#include "ui_dialog.h"
#include "LogHandler.h"
#include <QDebug>
//调用WIN API需要用到的头文件与库
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif
static Joy_Thread *joy_thread;
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    joy_thread = new Joy_Thread();
    qRegisterMetaType<joyinfoex_tag>("joyinfoex_tag");//注册一种信号的参数类型
    connect(joy_thread, SIGNAL(JoySignal_row(joyinfoex_tag)), this, SLOT(display_slot_row(joyinfoex_tag)));
    joy_thread->start();
    initForm();         //框
    m_timerid=-1;
    m_timerid_3D=-1;
    g_handle=nullptr;
    /**************设置窗口**********/
    this->setWindowTitle("未连接");//窗口标题
    ui->labTitle->setText(QString("运动控制器上位机（%1） 手柄（%2）").arg("未连接","已连接"));

    /**************设置弹窗**********/
    QPixmap p(":/image/msg_error.png");
    p=p.scaled(30,30);
    messagebox_warning.setIconPixmap(p);
    messagebox_warning.setWindowTitle("提示");


    /***********设置连接功能box***********/

    groupbox_link=new QGroupBox(widget_canshu);
    groupbox_link->setTitle("连接");

    combobox_ip=new QComboBox(groupbox_link);//ip下拉列表
    QStringList ip;
    ip<<"127.0.0.1"<<"192.168.0.11";
    combobox_ip->addItems(ip);//添加项目
    combobox_ip->setEditable(true);
    combobox_ip->setMaxCount(5);

    pushbutton_lianjie=new QPushButton(groupbox_link);//连接按钮
    pushbutton_lianjie->setText("连接");
    QIcon button_iconl(":/image/connect.png");
    pushbutton_lianjie->setIcon(button_iconl);
    pushbutton_lianjie->setIconSize(QSize(24,24));
    //pushbutton_lianjie->setEnabled(false);
    pushbutton_lianjie->setMaximumWidth(100);
    connect(pushbutton_lianjie, SIGNAL(clicked()), this, SLOT(lianjie()));


    pushbutton_duankai=new QPushButton(groupbox_link);//断开按钮
    pushbutton_duankai->setText("断开");
    QIcon button_icond(":/image/disconnect.png");
    pushbutton_duankai->setIcon(button_icond);
    pushbutton_duankai->setIconSize(QSize(24,24));
    pushbutton_duankai->setEnabled(false);
    pushbutton_duankai->setMaximumWidth(100);
    pushbutton_duankai->setEnabled(false);
    connect(pushbutton_duankai, SIGNAL(clicked()), this, SLOT(duankai()));
    //groupbox_link->setFont(font);
    //groupbox_link->setStyleSheet("QGroupBox{font-size:9pt}");
    groupbox_link->setMaximumHeight(60);


    QHBoxLayout* hboxlayout_link=new QHBoxLayout(groupbox_link);//布局
    QFormLayout* formlayout_ip=new QFormLayout();
    formlayout_ip->addRow("IP:",combobox_ip);
    hboxlayout_link->addLayout(formlayout_ip,0);
    hboxlayout_link->addWidget(pushbutton_lianjie,1);
    hboxlayout_link->addWidget(pushbutton_duankai,2);
    hboxlayout_link->setAlignment(Qt::AlignCenter);//居中

    /*******设置状态box***********/
    QFormLayout* formlayout_axis[3];
    for(int i=0;i<3;i++)//三个轴的状态 x(0) y(1) z(2)
    {
        groupbox_axis[i]=new QGroupBox(ui->widget_status);
        formlayout_axis[i]=new QFormLayout(groupbox_axis[i]);
        for (int j=0;j<3;j++)
        {
            label_status[i][j]=new QLabel(widget_canshu);
        }
        formlayout_axis[i]->addRow("状态:",label_status[i][0]);
        formlayout_axis[i]->addRow("位置:",label_status[i][1]);
        formlayout_axis[i]->addRow("速度:",label_status[i][2]);
        formlayout_axis[i]->setAlignment(Qt::AlignCenter);//居中
    }
    groupbox_axis[0]->setTitle("X轴");
    groupbox_axis[0]->setStyleSheet("color:rgb(0,0,255)");
    groupbox_axis[1]->setTitle("Y轴");
    groupbox_axis[1]->setStyleSheet("color:rgb(255,0,0)");
    groupbox_axis[2]->setTitle("Z轴");
    groupbox_axis[2]->setStyleSheet("color:rgb(0,255,0)");


    /************参数设置***************/
    groupbox_setspeed=new QGroupBox(widget_canshu);
    groupbox_setspeed->setTitle("参数设置");

    QFormLayout* formlayout_set=new QFormLayout(groupbox_setspeed);
    for(int i=0;i<6;i++)
    {
        lineedit_setspeed[i]=new QLineEdit(groupbox_setspeed);
    }
    formlayout_set->addRow("加工速度(mm/s):",lineedit_setspeed[0]);
    formlayout_set->addRow("最大速度(mm/s):",lineedit_setspeed[1]);
    formlayout_set->addRow("加速度(mm/s/s):",lineedit_setspeed[2]);
    formlayout_set->addRow("减速度(mm/s/s):",lineedit_setspeed[3]);
    formlayout_set->addRow("过渡时间(ms):",lineedit_setspeed[4]);
    formlayout_set->addRow("爬行速度(mm/s):",lineedit_setspeed[5]);
    lineedit_setspeed[0]->setText("10");//默认值
    lineedit_setspeed[1]->setText("25");
    lineedit_setspeed[2]->setText("10");
    lineedit_setspeed[3]->setText("10");
    lineedit_setspeed[4]->setText("10");
    lineedit_setspeed[5]->setText("2");
    groupbox_setspeed->setMaximumHeight(190);

    lineedit_jiting=new QLineEdit(widget_canshu);// /////wgy
    lineedit_jiting->setText("-1");
    formlayout_set->addRow("急停IO:",lineedit_jiting);


    groupbox_pid=new QGroupBox(widget_canshu);
    QFormLayout* formlayout_pid[3];
    QGridLayout* gridlayout_pid=new QGridLayout(groupbox_pid);
    for (int i=0;i<3;i++) {
        formlayout_pid[i]=new QFormLayout();
        lineedit_pid[i]=new QLineEdit(groupbox_pid);
        gridlayout_pid->addLayout(formlayout_pid[i],0,i);
    }
    gridlayout_pid->setAlignment(Qt::AlignCenter);//居中
    formlayout_pid[0]->addRow("P:",lineedit_pid[0]);
    formlayout_pid[1]->addRow("I:",lineedit_pid[1]);
    formlayout_pid[2]->addRow("D:",lineedit_pid[2]);
    lineedit_pid[0]->setText("40");//默认pid参数
    lineedit_pid[1]->setText("20");
    lineedit_pid[2]->setText("1");
    groupbox_pid->setTitle("PID");
    //groupbox_pid->setFont(font);
    //groupbox_pid->setStyleSheet("QGroupBox{font-size:9pt}");
    groupbox_pid->setMaximumHeight(60);

    /************脉冲当量与限位设置***************/
    QFormLayout* formlayout_mcdl[3];
    for(int i=0;i<3;i++)//三个轴的状态 x(0) y(1) z(2)
    {
        groupbox_limit[i]=new QGroupBox(widget_canshu);
        formlayout_mcdl[i]=new QFormLayout(groupbox_limit[i]);
        for (int j=0;j<6;j++)
        {
            lineedit_limit[i][j]=new QLineEdit(groupbox_limit[i]);
        }
        formlayout_mcdl[i]->addRow("脉冲当量(p/mm):",lineedit_limit[i][0]);
        formlayout_mcdl[i]->addRow("正限位(mm):+",lineedit_limit[i][1]);
        formlayout_mcdl[i]->addRow("负限位(mm):-",lineedit_limit[i][2]);
        formlayout_mcdl[i]->addRow("正限位IO:",lineedit_limit[i][3]);
        formlayout_mcdl[i]->addRow("负限位IO:",lineedit_limit[i][4]);
        formlayout_mcdl[i]->addRow("回零IO:",lineedit_limit[i][5]);
        lineedit_limit[i][0]->setText("26214.4");
        lineedit_limit[i][1]->setText("200");
        lineedit_limit[i][2]->setText("200");
        lineedit_limit[i][3]->setText("-1");
        lineedit_limit[i][4]->setText("-1");
        lineedit_limit[i][5]->setText(QString::number(i));
        groupbox_limit[i]->setMaximumHeight(180);
    }
    groupbox_limit[0]->setTitle("X轴");
    //groupbox_limit[0]->setStyleSheet("color:rgb(255,0,0)");
    groupbox_limit[1]->setTitle("Y轴");
    //groupbox_limit[1]->setStyleSheet("color:rgb(0,255,0)");
    groupbox_limit[2]->setTitle("Z轴");
    //groupbox_limit[2]->setStyleSheet("color:rgb(0,0,255)");


    /***********保存设置按钮****************/
    pushbutton_saveset=new QPushButton(widget_canshu);
    pushbutton_saveset->setText("保存设置");
    QIcon button_icon3(":/image/save.png");
    pushbutton_saveset->setIcon(button_icon3);
    pushbutton_saveset->setIconSize(QSize(24,24));
    pushbutton_saveset->setEnabled(false);
    connect(pushbutton_saveset, SIGNAL(clicked()), this, SLOT(setstatus()));

    /***************是否有输入检测*************/
    QList<QLineEdit *> alledit = widget_canshu->findChildren<QLineEdit *>();
    foreach (QLineEdit * edit, alledit)
    {
        connect(edit, SIGNAL(textChanged(QString)), this, SLOT(editchange()));
    }

    /**************布局***********************/
    QGridLayout* middle[2]={new QGridLayout(),new QGridLayout()};
    middle[0]->addWidget(groupbox_limit[0],0,0);//X轴
    middle[0]->addWidget(groupbox_limit[1],0,1);//Y轴
    middle[1]->addWidget(groupbox_limit[2],0,0);//Z轴
    middle[1]->addWidget(groupbox_setspeed,0,1);//速度设置

    QVBoxLayout* vboxlayout_canshu=new QVBoxLayout(widget_canshu);
    vboxlayout_canshu->addWidget(groupbox_link,0);
    vboxlayout_canshu->addWidget(groupbox_pid,1);
    vboxlayout_canshu->addLayout(middle[0],2);
    vboxlayout_canshu->addLayout(middle[1],3);
    vboxlayout_canshu->addWidget(pushbutton_saveset,4);

    QGridLayout* gridlayout_status=new QGridLayout(ui->widget_status);

    gridlayout_status->addWidget(groupbox_axis[0],0,1);
    gridlayout_status->addWidget(groupbox_axis[1],0,2);
    gridlayout_status->addWidget(groupbox_axis[2],0,3);




    /************吴炼***************/

    // 创建字体
    QFont ifont;
    ifont.setFamily("FontAwesome");
    ifont.setPointSize(20);

    /************Message***************/
    groupbox_message=new QGroupBox(widget_shoudong);
    groupbox_message->setTitle("Message");
    QGridLayout* gridlayout_message=new QGridLayout(groupbox_message);
    textedit_message=new QTextEdit(groupbox_message);
    textedit_message->append("报警记录");
    textedit_message->setReadOnly(true);
    gridlayout_message->addWidget(textedit_message);

    /************变频器参数***************/
    groupbox_bpqcanshu=new QGroupBox(widget_shoudong);
    groupbox_bpqcanshu->setTitle("变频器参数");
    groupbox_bpqcanshu->setMaximumHeight(80);
    //groupbox_bpqcanshu->setFont(font);
    label_pinlv=new QLabel(groupbox_bpqcanshu);
    //label_pinlv->setText("频率");
    label_pinlv->setMinimumWidth(15);
    QPixmap button_pix(":/image/freq.png");
    label_pinlv->setPixmap(button_pix);

    lineedit_pinlv=new QLineEdit(groupbox_bpqcanshu);
    lineedit_pinlv->setMinimumWidth(320);
    pushbutton_yunxing=new QPushButton(groupbox_bpqcanshu);
    pushbutton_yunxing->setText("运行");
    QIcon button_icony(":/image/startprocess.png");
    pushbutton_yunxing->setIcon(button_icony);
    pushbutton_yunxing->setIconSize(QSize(18,18));
    pushbutton_yunxing->setFlat(true);
    pushbutton_yunxing->setMaximumHeight(40);
    pushbutton_yunxing->setMaximumWidth(70);
    pushbutton_tingzhi=new QPushButton(groupbox_bpqcanshu);
    pushbutton_tingzhi->setText("停止");
    QIcon button_icont(":/image/stopprocess.png");
    pushbutton_tingzhi->setIcon(button_icont);
    pushbutton_tingzhi->setIconSize(QSize(18,18));
    pushbutton_tingzhi->setFlat(true);
    pushbutton_yunxing->setMaximumHeight(40);
    pushbutton_tingzhi->setMaximumWidth(70);
    radiobutton_zhengxiang=new QRadioButton(groupbox_bpqcanshu);
    radiobutton_zhengxiang->setText("正向");
    radiobutton_fanxiang=new QRadioButton(groupbox_bpqcanshu);
    radiobutton_fanxiang->setText("反向");
    buttongroup_zhengfan=new QButtonGroup(groupbox_bpqcanshu);
    buttongroup_zhengfan->setId(radiobutton_zhengxiang,0);
    buttongroup_zhengfan->setId(radiobutton_fanxiang,1);
    buttongroup_zhengfan->addButton(radiobutton_zhengxiang);
    buttongroup_zhengfan->addButton(radiobutton_fanxiang);

    connect(pushbutton_yunxing, SIGNAL(clicked()), this, SLOT(bpqyunxing()));
    connect(pushbutton_tingzhi, SIGNAL(clicked()), this, SLOT(bpqtingzhi()));

    QGridLayout* gridlayout_plzf=new QGridLayout;
    gridlayout_plzf->addWidget(label_pinlv,0,0);
    gridlayout_plzf->addWidget(lineedit_pinlv,0,1,1,2);
    gridlayout_plzf->addWidget(radiobutton_zhengxiang,0,3);
    gridlayout_plzf->addWidget(radiobutton_fanxiang,0,4);
    QGridLayout* gridlayout_yxtz=new QGridLayout;
    gridlayout_yxtz->addWidget(pushbutton_yunxing,0,0);
    gridlayout_yxtz->addWidget(pushbutton_tingzhi,0,1);
    QGridLayout* gridlayout_bpqcanshu=new QGridLayout(groupbox_bpqcanshu);
    gridlayout_bpqcanshu->addLayout(gridlayout_plzf,0,0);
    gridlayout_bpqcanshu->addLayout(gridlayout_yxtz,1,0);


    /************轴限位状态***************/
    groupbox_zhouxianwei=new QGroupBox(widget_shoudong);
    groupbox_zhouxianwei->setTitle("轴限位状态");
    for(int i=0;i<8;i++)
    {
        label_led_zxw[i]=new QLabel(groupbox_zhouxianwei);
        label_led_name[i]=new QLabel(groupbox_zhouxianwei);
        label_led_zxw[i]->setFont(ifont);
        label_led_zxw[i]->setStyleSheet("color:rgb(90,240,170)");
        label_led_zxw[i]->setAlignment(Qt::AlignCenter);
        label_led_name[i]->setAlignment(Qt::AlignCenter);
        label_led_zxw[i]->setProperty("round","true");
        QPixmap pic(":/image/state.png");
        label_led_zxw[i]->setPixmap(pic);
    }
    label_led_zxw[1]->setStyleSheet("color:rgb(240,120,160)");

    label_led_name[0]->setText("紧急制动");
    label_led_name[1]->setText("门限位");
    label_led_name[2]->setText("X+");
    label_led_name[3]->setText("X-");
    label_led_name[4]->setText("Y+");
    label_led_name[5]->setText("Y-");
    label_led_name[6]->setText("Z+");
    label_led_name[7]->setText("Z-");
    checkbox_zhidongfanzhuan=new QCheckBox(widget_shoudong);
    checkbox_xianweifanzhuan=new QCheckBox(widget_shoudong);
    checkbox_zhidongfanzhuan->setText("制动电平反转");
    checkbox_xianweifanzhuan->setText("限位电平反转");

    connect(checkbox_zhidongfanzhuan, SIGNAL(clicked()), this, SLOT(handcontrol_zhidongfanzhuan()));
    connect(checkbox_xianweifanzhuan, SIGNAL(clicked()), this, SLOT(handcontrol_xianweifanzhuan()));



    QGridLayout* gridlayout_zhouxianwei=new QGridLayout(groupbox_zhouxianwei);
    QVBoxLayout* vboxlayout_led[8];
    for(int i=0;i<8;i++){
        vboxlayout_led[i]=new QVBoxLayout;
        vboxlayout_led[i]->addWidget(label_led_zxw[i],0);
        vboxlayout_led[i]->addWidget(label_led_name[i],1);
    }
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_jinjizhidong],0,0,2,1);
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_menxianwei],0,1,2,1);
    gridlayout_zhouxianwei->addWidget(checkbox_zhidongfanzhuan,0,2,2,2);
    gridlayout_zhouxianwei->addWidget(checkbox_xianweifanzhuan,0,4,2,2);
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_xplus],2,0,2,1);
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_xsub],2,1,2,1);
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_yplus],2,2,2,1);
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_ysub],2,3,2,1);
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_zplus],2,4,2,1);
    gridlayout_zhouxianwei->addLayout(vboxlayout_led[label_led_zsub],2,5,2,1);




    /************三维手动控制***************/
    groupbox_handcontrol=new QGroupBox(widget_shoudong);
    groupbox_handcontrol->setTitle("三维手动控制(已支持手柄)");
    QGridLayout* gridlayout_handcontrol=new QGridLayout(widget_shoudong);
    pushbutton_xzhouhuiling=new QPushButton(groupbox_handcontrol);
    pushbutton_xzhouhuiling->setText("X轴回零");
    pushbutton_yzhouhuiling=new QPushButton(groupbox_handcontrol);
    pushbutton_yzhouhuiling->setText("Y轴回零");
    pushbutton_zzhouhuiling=new QPushButton(groupbox_handcontrol);
    pushbutton_zzhouhuiling->setText("Z轴回零");
    pushbutton_xzhouhuiling->setEnabled(false);
    pushbutton_yzhouhuiling->setEnabled(false);
    pushbutton_zzhouhuiling->setEnabled(false);
    pushbutton_shoudongjiting=new QPushButton(groupbox_handcontrol);
    QIcon button_ico(":/image/zero.png");
    pushbutton_shoudongjiting->setIcon(button_ico);
    pushbutton_shoudongjiting->setIconSize(QSize(20,20));
    pushbutton_shoudongjiting->setFlat(true);
    pushbutton_shoudongjiting->setText("坐标回零");
    for(int i=0;i<6;i++){
        pushbutton_handcontrol[i]=new QPushButton(groupbox_handcontrol);
        pushbutton_handcontrol[i]->setFont(ifont);
        pushbutton_handcontrol[i]->setStyleSheet("color: rgb(150, 240, 240);"); //矢量图颜色
        pushbutton_handcontrol[i]->setProperty("round","true");
    }
    gridlayout_handcontrol->addWidget(pushbutton_handcontrol[0],1,1);
    gridlayout_handcontrol->addWidget(pushbutton_handcontrol[1],2,1);
    gridlayout_handcontrol->addWidget(pushbutton_handcontrol[2],2,0);
    gridlayout_handcontrol->addWidget(pushbutton_handcontrol[3],2,2);
    gridlayout_handcontrol->addWidget(pushbutton_handcontrol[4],1,3);
    gridlayout_handcontrol->addWidget(pushbutton_handcontrol[5],2,3);
    gridlayout_handcontrol->addWidget(pushbutton_xzhouhuiling,0,0);
    gridlayout_handcontrol->addWidget(pushbutton_yzhouhuiling,0,1);
    gridlayout_handcontrol->addWidget(pushbutton_zzhouhuiling,0,2);
    gridlayout_handcontrol->addWidget(pushbutton_shoudongjiting,0,3);
    groupbox_handcontrol->setLayout(gridlayout_handcontrol);
    QIcon button_ico0(":/image/up.png");
    pushbutton_handcontrol[0]->setIcon(button_ico0);
    pushbutton_handcontrol[0]->setIconSize(QSize(24,24));
    pushbutton_handcontrol[0]->setFlat(true);
    QIcon button_ico1(":/image/down.png");
    pushbutton_handcontrol[1]->setIcon(button_ico1);
    pushbutton_handcontrol[1]->setIconSize(QSize(24,24));
    pushbutton_handcontrol[1]->setFlat(true);
    QIcon button_ico2(":/image/left.png");
    pushbutton_handcontrol[2]->setIcon(button_ico2);
    pushbutton_handcontrol[2]->setIconSize(QSize(24,24));
    pushbutton_handcontrol[2]->setFlat(true);
    QIcon button_ico3(":/image/right.png");
    pushbutton_handcontrol[3]->setIcon(button_ico3);
    pushbutton_handcontrol[3]->setIconSize(QSize(24,24));
    pushbutton_handcontrol[3]->setFlat(true);
    QIcon button_ico4(":/image/lift.png");
    pushbutton_handcontrol[4]->setIcon(button_ico4);
    pushbutton_handcontrol[4]->setIconSize(QSize(24,24));
    pushbutton_handcontrol[4]->setFlat(true);
    QIcon button_ico5(":/image/decrease.png");
    pushbutton_handcontrol[5]->setIcon(button_ico5);
    pushbutton_handcontrol[5]->setIconSize(QSize(24,24));
    pushbutton_handcontrol[5]->setFlat(true);
    connect(pushbutton_handcontrol[0], SIGNAL(pressed()), this, SLOT(handcontrol_yplus()));
    connect(pushbutton_handcontrol[0], SIGNAL(released()), this, SLOT(handcontrol_yplus_cancel()));
    connect(pushbutton_handcontrol[1], SIGNAL(pressed()), this, SLOT(handcontrol_ysub()));
    connect(pushbutton_handcontrol[1], SIGNAL(released()), this, SLOT(handcontrol_ysub_cancel()));
    connect(pushbutton_handcontrol[2], SIGNAL(pressed()), this, SLOT(handcontrol_xsub()));
    connect(pushbutton_handcontrol[2], SIGNAL(released()), this, SLOT(handcontrol_xsub_cancel()));
    connect(pushbutton_handcontrol[3], SIGNAL(pressed()), this, SLOT(handcontrol_xplus()));
    connect(pushbutton_handcontrol[3], SIGNAL(released()), this, SLOT(handcontrol_xplus_cancel()));
    connect(pushbutton_handcontrol[4], SIGNAL(pressed()), this, SLOT(handcontrol_zplus()));
    connect(pushbutton_handcontrol[4], SIGNAL(released()), this, SLOT(handcontrol_zplus_cancel()));
    connect(pushbutton_handcontrol[5], SIGNAL(pressed()), this, SLOT(handcontrol_zsub()));
    connect(pushbutton_handcontrol[5], SIGNAL(released()), this, SLOT(handcontrol_zsub_cancel()));
    connect(pushbutton_xzhouhuiling, SIGNAL(clicked()), this, SLOT(handcontrol_xzhouhuiling()));
    connect(pushbutton_yzhouhuiling, SIGNAL(clicked()), this, SLOT(handcontrol_yzhouhuiling()));
    connect(pushbutton_zzhouhuiling, SIGNAL(clicked()), this, SLOT(handcontrol_zzhouhuiling()));
    connect(pushbutton_shoudongjiting, SIGNAL(clicked()), this, SLOT(handcontrol_shoudongjiting()));

    QVBoxLayout* vboxlayout_shoudong=new QVBoxLayout(widget_shoudong);
    vboxlayout_shoudong->addWidget(groupbox_handcontrol,0);
    vboxlayout_shoudong->addWidget(groupbox_zhouxianwei,1);
    vboxlayout_shoudong->addWidget(groupbox_bpqcanshu,2);
    vboxlayout_shoudong->addWidget(groupbox_message,3);


    //hcy********************************************************************************************************************************开始
    /***********自动模式***********/
    zhongduan_biaozhi=0;
    groupbox_file=new QGroupBox(widget_zidong);
    groupbox_file->setTitle("文件导入");
    /***********导入文件***********/
    pushbutton_daoruwenjian=new QPushButton(groupbox_file);//导入文件按钮
    pushbutton_daoruwenjian->setText("导入文件");
    QIcon button_icondis(":/image/load.png");
    pushbutton_daoruwenjian->setIcon(button_icondis);
    pushbutton_daoruwenjian->setIconSize(QSize(20,20));
    pushbutton_daoruwenjian->setFlat(true);
    pushbutton_daoruwenjian->setEnabled(false);
    connect(pushbutton_daoruwenjian, SIGNAL(clicked()), this, SLOT(daoruwenjian()));

    /***********启动***********/
    pushbutton_qidong=new QPushButton(groupbox_file);//qidong
    pushbutton_qidong->setText("启动");
    QIcon button_iconq(":/image/begin.png");
    pushbutton_qidong->setIcon(button_iconq);
    pushbutton_qidong->setIconSize(QSize(20,20));
    pushbutton_qidong->setFlat(true);
    pushbutton_qidong->setEnabled(false);
    connect(pushbutton_qidong, SIGNAL(clicked()), this, SLOT(qidong()));

    /***********继续***********/
    pushbutton_jixu=new QPushButton(groupbox_file);//
    pushbutton_jixu->setText("继续");
    QIcon button_iconj(":/image/continue.png");
    pushbutton_jixu->setIcon(button_iconj);
    pushbutton_jixu->setIconSize(QSize(20,20));
    pushbutton_jixu->setFlat(true);
    pushbutton_jixu->setEnabled(false);
    pushbutton_jixu->setEnabled(false);
    connect(pushbutton_jixu, SIGNAL(clicked()), this, SLOT(Continue()));

    /***********坐标清零+清屏***********/
    pushbutton_zuobiaoqingling=new QPushButton(groupbox_file);//
    pushbutton_zuobiaoqingling->setText("坐标清零+清屏");
    connect(pushbutton_zuobiaoqingling, SIGNAL(clicked()), this, SLOT(zuobiaoqingling()));
    //pushbutton_zuobiaoqingling->setGeometry(140,70,100,40);

    /***********暂停***********/
    pushbutton_zanting=new QPushButton(groupbox_file);//
    pushbutton_zanting->setText("暂停");
    QIcon button_iconz(":/image/stop.png");
    pushbutton_zanting->setIcon(button_iconz);
    pushbutton_zanting->setIconSize(QSize(20,20));
    pushbutton_zanting->setFlat(true);
    pushbutton_zanting->setEnabled(false);
    connect(pushbutton_zanting, SIGNAL(clicked()), this, SLOT(Pause()));

    /***********对刀点记忆***********/
    pushbutton_duidaodianjiyi=new QPushButton(groupbox_file);//
    pushbutton_duidaodianjiyi->setText("对刀点记忆");
    //pushbutton_duidaodianjiyi->setGeometry(250,70,100,40);
    connect(pushbutton_duidaodianjiyi, SIGNAL(clicked()), this, SLOT(duidaodianjiyi()));

    /***********对刀点恢复***********/
    pushbutton_duidaodianhuifu=new QPushButton(groupbox_file);//
    pushbutton_duidaodianhuifu->setText("对刀点恢复");
    //pushbutton_duidaodianhuifu->setGeometry(250,120,100,40);
    connect(pushbutton_duidaodianhuifu, SIGNAL(clicked()), this, SLOT(duidaodianhuifu()));

    /***********选择文件***********/
    lineedit_file=new QLineEdit(groupbox_file);
    //lineedit_file->setFont(font);
    //lineedit_file->setGeometry(110,30,380,30);



    /***********设置G代码box***********/
    groupbox_G=new QGroupBox(widget_zidong);
    groupbox_G->setTitle("G代码");
    //groupbox_G->setGeometry(10,160,470,400);

    /***********文件内容***********/
    textedit_file=new QTextEdit(groupbox_G);
    //textedit_file->setFont(font);
    //textedit_file->setGeometry(30,120,380,260);


    Gdaimazongshu=new QLabel(groupbox_G);
    Gdaimazongshu->setText("G代码总数:");
    //Gdaimazongshu->setGeometry(10,10,80,40);
    num_Gdaimazongshu=new QLabel(groupbox_G);

    num_Gdaimazongshu->setText(QString::number(hangshu));
    //num_Gdaimazongshu->setGeometry(100,10,80,40);

    jindu=new QLabel(groupbox_G);
    jindu->setText("进度:");
    //jindu->setGeometry(10,40,80,40);

    yiyongshijian=new QLabel(groupbox_G);
    yiyongshijian->setText("已用时间:");
    //yiyongshijian->setGeometry(10,80,80,40);
    num_yiyongshijian=new QLabel(groupbox_G);

    //num_yiyongshijian->setGeometry(90,80,80,40);

    shengyushijian=new QLabel(groupbox_G);
    shengyushijian->setText("剩余时间:");
    //shengyushijian->setGeometry(300,80,80,40);
    num_shengyushijian=new QLabel(groupbox_G);

    //num_shengyushijian->setGeometry(380,80,80,40);

    /***********进度条x***********/
    jindutiao = new QProgressBar(widget_zidong);
    jindutiao->setRange(0,100); //设置进度条最小值和最大值(取值范围)
    //jindutiao->setGeometry(80,210,400,30);

    QGridLayout* gridlayout_file=new QGridLayout(groupbox_file);
    gridlayout_file->addWidget(pushbutton_daoruwenjian,0,0);
    gridlayout_file->addWidget(lineedit_file,0,1,1,2);
    gridlayout_file->addWidget(pushbutton_qidong,1,0);
    gridlayout_file->addWidget(pushbutton_zuobiaoqingling,1,1);
    gridlayout_file->addWidget(pushbutton_duidaodianjiyi,1,2);
    gridlayout_file->addWidget(pushbutton_jixu,2,0);
    gridlayout_file->addWidget(pushbutton_zanting,2,1);
    gridlayout_file->addWidget(pushbutton_duidaodianhuifu,2,2);

    QGridLayout* gridlayout_G=new QGridLayout(groupbox_G);
    gridlayout_G->addWidget(Gdaimazongshu,0,0);
    gridlayout_G->addWidget(num_Gdaimazongshu,0,1);
    gridlayout_G->addWidget(jindu,1,0);
    gridlayout_G->addWidget(jindutiao,1,1,1,5);
    gridlayout_G->addWidget(yiyongshijian,2,0);
    gridlayout_G->addWidget(num_yiyongshijian,2,1);
    gridlayout_G->addWidget(shengyushijian,2,5);
    gridlayout_G->addWidget(num_shengyushijian,2,6);
    gridlayout_G->addWidget(textedit_file,3,0,1,7);

    QVBoxLayout* VBox_zidong=new QVBoxLayout(widget_zidong);
    VBox_zidong->addWidget(groupbox_file,0);
    VBox_zidong->addWidget(groupbox_G,1);
    //3D图放置
    //          groupbox_3D=new QGroupBox(this);
    //          groupbox_3D->setTitle("3D图");
    //          groupbox_3D->setGeometry(100,160,470,400);
    glwidget=new GLWidget(ui->widget_3D);

    //glwidget->setGeometry(0,0,300,300);

    QGridLayout* gridlayout_3D=new QGridLayout(ui->widget_3D);
    gridlayout_3D->addWidget(glwidget,0,0);


    // VBox_zidong->addWidget(groupbox_3D,2);

    //制作人员名单
    QVBoxLayout* vboxlayout_staff=new QVBoxLayout(widget_staff);
    QGroupBox* staff[6];
    QHBoxLayout* layout_staff[6];
    QLabel* label_staff[6];
    for(int i=0;i<6;i++){
        staff[i]=new QGroupBox(widget_staff);
        label_staff[i]=new QLabel(staff[i]);
        layout_staff[i]=new QHBoxLayout(staff[i]);
        layout_staff[i]->addWidget(label_staff[i]);
        layout_staff[i]->setAlignment(Qt::AlignCenter);
        vboxlayout_staff->addWidget(staff[i]);
        staff[i]->setMaximumHeight(50);
        //staff[i]->setAlignment(Qt::AlignHCenter);
        staff[i]->setProperty("tt","true");
    }
    staff[0]->setTitle("制作人员");
    staff[1]->setTitle("制作人员");
    staff[2]->setTitle("制作人员");
    staff[3]->setTitle("制作人员");
    staff[4]->setTitle("制作人员");
    staff[5]->setTitle("开发版本");
    label_staff[0]->setText("刘江宇");
    label_staff[1]->setText("吕昕宇");
    label_staff[2]->setText("付文斌");
    label_staff[3]->setText("许瑞奇");
    label_staff[4]->setText("吴涛");
    label_staff[5]->setText("Qt5.12");


    status_in();//读取本地数据

    //大模型相关
    // 创建TCP套接字
    m_socket = new QTcpSocket(this);

    // 连接到服务器
    connect(m_socket, &QTcpSocket::connected, this, &Dialog::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &Dialog::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Dialog::onReadyRead);
    m_socket->connectToHost("127.0.0.1", 12345); // 连接到本地服务器

    // 初始化讯飞API
    m_appId = "d790db02";
    m_apiKey = "f43f78b7d6b02cf53ef9231bf351aac8";
    m_apiSecret = "MThlOGZiMmJmNWUzNDI0OWQzMzJhZGU0";
    m_accessToken = "";
    m_expireTime = QDateTime();

    // 获取访问令牌
    getAccessToken();

    // 发送聊天信息
    connect(m_sendButton, &QPushButton::clicked, this, &Dialog::sendMessage);

    // 处理@机器人事件
    connect(m_textEdit, &QTextEdit::textChanged, this, &Dialog::onTextChange);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::status_out()
{
    QFile file("Data.dat");
    file.open(QIODevice::WriteOnly|QIODevice::Text);
    QDataStream out(&file);
    QList<QLineEdit*> lines = widget_canshu->findChildren<QLineEdit*>();
    foreach (QLineEdit *line, lines) {//遍历的每个元素
        out<<line->text();
    }
    out<<combobox_ip->currentText();
    file.close();

}

void Dialog::status_in()
{
    QString a;
    QFile file("Data.dat");
    if(!file.open(QIODevice::ReadOnly))
        return;
    QDataStream in(&file);
    QList<QLineEdit*> lines = widget_canshu->findChildren<QLineEdit*>();
    foreach (QLineEdit *line, lines) {//遍历的每个元素
        in>>a;
        line->setText(a);
    }
    in>>a;
    if(a!=combobox_ip->currentText()){
        combobox_ip->insertItem(0,a);
        combobox_ip->setCurrentText(a);
    }
    file.close();

}
void Dialog::initForm()
{
    widget_canshu=new QWidget(this);
    widget_zidong=new QWidget(this);
    widget_shoudong=new QWidget(this);
    widget_staff=new QWidget(this);
    widget_canshu->setObjectName("widget_canshu");
    widget_zidong->setObjectName("widget_zidong");
    widget_shoudong->setObjectName("widget_shoudong");
    widget_staff->setObjectName("widget_staff");

    ui->stackedWidget->addWidget(widget_canshu);
    ui->stackedWidget->addWidget(widget_zidong);
    ui->stackedWidget->addWidget(widget_shoudong);
    ui->stackedWidget->addWidget(widget_staff);

    connect(ui->btnMenu_Min, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(ui->btnMenu_Max, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(ui->btnMenu_Close, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    setWindowFlags(Qt::FramelessWindowHint);//隐藏原标题栏

    //添加自定义属性,用于切换ico用
    ui->btn_canshu->setProperty("icoName", "para");
    ui->btn_zidong->setProperty("icoName", "auto");
    ui->btn_shoudong->setProperty("icoName", "manual");
    ui->btn_staff->setProperty("icoName", "staff");

    //获取所有的btn
    QList<QToolButton *> btns = ui->widgetLeft->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {//遍历btns的每个元素
        btn->setMaximumHeight(80);
        btn->setCheckable(true);//可选中
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClick()));
    }

    ui->btn_canshu->click();
    //double dpi=QGuiApplication::primaryScreen()->logicalDotsPerInch()/96;
}

void Dialog::buttonClick()
{
    QToolButton *b = qobject_cast<QToolButton *>(sender());
    //QToolButton *b = (QToolButton *)sender();
    QString text = b->text();

    //widgetLeft的所有子控件
    QList<QToolButton *> btns = ui->widgetLeft->findChildren<QToolButton *>();
    foreach (QToolButton *btn, btns) {
        QString icoName = btn->property("icoName").toString();
        if (btn != b) {     //点下切换图标
            btn->setChecked(false);
            btn->setIcon(QIcon(QString(":/image/%1.png").arg(icoName)));
        } else {
            btn->setChecked(true);
            btn->setIcon(QIcon(QString(":/image/%1_focus.png").arg(icoName)));
        }
    }
    if(b==ui->btn_canshu)
        ui->stackedWidget->setCurrentIndex(0);
    else if(b==ui->btn_zidong)
        ui->stackedWidget->setCurrentIndex(1);
    else if(b==ui->btn_shoudong)
        ui->stackedWidget->setCurrentIndex(2);
    else if(b==ui->btn_staff)
        ui->stackedWidget->setCurrentIndex(3);
    //ui->label->setText(text);
}



void Dialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    QPoint p=event->pos();;
    if(p.y()>50) return;//只在title响应
    emit ui->btnMenu_Max->clicked();
}

//进行界面的拖动 界面随着标题栏的移动而移动,windows起作用,其他未定义
void Dialog::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    QPoint p=event->pos();;
    if(p.y()>50) return;//只在title响应
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
    //event->ignore();
#else
#endif
}

//使用事件过滤器监听标题栏所在的窗体，所以当窗体标题、图标等信息发生改变时，标题栏也应该随之改变
bool Dialog::eventFilter(QObject *obj, QEvent *event)
{
    switch ( event->type() ) //判断发生事件的类型
    {
    case QEvent::WindowTitleChange: //窗口标题改变事件
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj); //获得发生事件的窗口对象
        if (pWidget)
        {
            //窗体标题改变，则标题栏标题也随之改变
            ui->labTitle->setText(pWidget->windowTitle());
            return true;
        }
    }
        break;

    default:
        return QWidget::eventFilter(obj, event);
    }

    return QWidget::eventFilter(obj, event);
}


//进行最小化、最大化/还原、关闭操作
void Dialog::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window(); //获得标题栏所在的窗口
    if (pWindow->isTopLevel())
    {
        //判断发送信号的对象使哪个按钮
        if (pButton == ui->btnMenu_Min)
        {
            pWindow->showMinimized(); //窗口最小化显示
        }
        else if (pButton == ui->btnMenu_Max)
        {
            if(pWindow->isMaximized()){
                pWindow->showNormal();//还原显示
                ui->btnMenu_Max->setIcon(QIcon(":/image/title_max.png"));
            }
            else{
                pWindow->showMaximized();  //窗口最大化
                ui->btnMenu_Max->setIcon(QIcon(":/image/title_reset.png"));
            }
        }
        else if (pButton == ui->btnMenu_Close)
        {
            pWindow->close(); //窗口关闭
        }
    }
}

void Dialog::timerEvent(QTimerEvent *event)
{
    if(m_timerid == event->timerId())
    {
        int idle[3]={1,1,1};
        float fdpos(0);
        float fvspeed(0);
        static bool biaozhi1[3];
        static bool biaozhi2[3];
        for(int i=0;i<3;i++)//x(0) y(1) z(2)
        {
            ZAux_Direct_GetIfIdle(g_handle,i,&idle[i]);//获得轴状态
            if(idle[i])
            {
                label_status[i][0]->setText("停止");
                label_status[i][0]->setStyleSheet("color:rgb(240,120,160)");
            }
            else
            {
                label_status[i][0]->setText("运行");
                label_status[i][0]->setStyleSheet("color:rgb(150, 240, 240)");
            }
            ZAux_Direct_GetDpos(g_handle,i,&fdpos);//获得轴位置
            label_status[i][1]->setText(QString("%1mm").arg(fdpos));
            //label_status[i][1]->setText(QString::number(fdpos));



            //保存点位置，用来画3D
            switch(i)
            {
            case 0:glwidget->points_x.push_back(fdpos/1000);break;
            case 1:glwidget->points_y.push_back(fdpos/1000);break;
            case 2:glwidget->points_z.push_back(fdpos/1000);
                //xyz坐标采集结束，判断其在快速移动还是直线插补
                switch( glwidget->g_mode00or01)
                {
                case 0:glwidget->xyz_mode.push_back(0); qDebug()<<0;break;

                case 1:glwidget->xyz_mode.push_back(1); qDebug()<<1;break;

                default:break;
                }
                break;
            }

            //hcy*********************************************************************************************开始
            ZAux_Direct_GetMspeed(g_handle,i,&fvspeed);
            //label_status[i][2]->setText(QString::number(fvspeed));
            label_status[i][2]->setText(QString("%1mm/s").arg(fvspeed));
            // [[1]] 安装消息处理函数
            LogHandler::Get().installMessageHandler();
            switch(i){
              case 0:
                qInfo()<<"X轴"<<"当前位置"<<fdpos<<"当前速度"<<fvspeed;
              case 1:
                qInfo()<<"Y轴"<<"当前位置"<<fdpos<<"当前速度"<<fvspeed;
              case 2:
                qInfo()<<"Z轴"<<"当前位置"<<fdpos<<"当前速度"<<fvspeed;
              default: break;
            }

            float zhengxianwei;
            float fuxianwei;

            ZAux_Direct_GetFsLimit(g_handle,i,&zhengxianwei);
            ZAux_Direct_GetRsLimit(g_handle,i,&fuxianwei);
            if(fdpos>zhengxianwei){
                label_led_zxw[2*i+2]->setStyleSheet("color:rgb(240,120,160)");

                if(biaozhi1[i]==0){
                    textedit_message->append("@轴正向限位警告");
                    biaozhi1[i]=1;
                }
            }
            else{
                label_led_zxw[2*i+2]->setStyleSheet("color:rgb(90,240,170)");
                biaozhi1[i]=0;
            }
            if(fdpos<fuxianwei){
                label_led_zxw[2*i+3]->setStyleSheet("color:rgb(240,120,160)");
                if(biaozhi2[i]==0){
                    textedit_message->append("@轴负向限位警告");
                    biaozhi2[i]=1;
                }
            }
            else{
                label_led_zxw[2*i+3]->setStyleSheet("color:rgb(90,240,170)");
                biaozhi2[i]=0;
            }

        }




        if(zhongduan_biaozhi==1&&idle[0]&&idle[1]&&idle[2])
        {
            if(fileFull=="No file"){textedit_file->setPlainText("No file");}
            else
            {
                QTextCodec *codec = QTextCodec::codecForName("GBK");//指定为GBK,因为file.readLine()无法读取中文

                static char* fileat;//用来指向每行的某个字符
                static QString str;


                if(iiiii<=hangshu)
                {
                    textedit_file->setTextColor("black");
                    fmt.setForeground(QColor(Qt::green));
                    //移动光标到某行行首
                    QTextBlock block = textedit_file->document()->findBlockByNumber(iiiii-1);
                    textedit_file->setTextCursor(QTextCursor(block));
                    //上色
                    cursor = textedit_file->textCursor();
                    cursor.select(QTextCursor::LineUnderCursor);   //选中要着色的内容
                    cursor.mergeCharFormat(fmt);    //设置文本格式
                    cursor.clearSelection(); //撤销选中
                    //获取光标所在行列
                    row=cursor.blockNumber();
                    lie=cursor.columnNumber();
                    //qDebug()<<row<<lie;
                    //读取一行文本数据
                    QByteArray lineread = fileread->readLine();
                    //将读取到的行数据转换为Unicode
                    str = codec->toUnicode(lineread);       //文件每一行内容
                    //qDebug()<<str;
                    QByteArray ba = str.toUtf8();
                    fileat = ba.data();
                    //qDebug()<<fileat;
                    for(;*fileat;fileat++)//依次对各个字符进行解析
                    {
                        switch(*fileat)
                        {
                        case 'G':
                            if(g_0full==0)
                            {   g_command[0] = atoi(fileat+1);g_0full=1;}
                            else if(g_1full==0)
                            {   g_command[1]= atoi(fileat+1); g_1full=1;}
                            break;
                        case 'F':
                            m_aspeed  = atof(fileat+1);
                            break;
                        case 'X':
                            xyz_pos[0] = atof(fileat+1);
                            break;
                        case 'Y':
                            xyz_pos[1] = atof(fileat+1);
                            break;
                        case 'Z':
                            xyz_pos[2] = atof(fileat+1);
                            break;
                        case'M':
                            Modbus=atoi(fileat+1);//command_M();//开刀或关刀
                        default: break;

                        }
                    }

                    num_yiyongshijian->setText(QString::number(iiiii));//已用时间
                    num_shengyushijian->setText(QString::number(hangshu-iiiii));//剩余时间
                    //qDebug()<<g_command;
                    //qDebug()<<m_aspeed;
                    //qDebug()<<xyz_pos[0]<<xyz_pos[1]<<xyz_pos[2];

                    jindutiao->setValue((iiiii/hangshu)*100);
                    iiiii++;

                    command_G();//运行对应运动函数

                    g_0full=0;
                    g_1full=0;
                }
                textedit_file->setTextColor("black");

            }

        }

    }
    //定时刷新画布
    else if(m_timerid_3D == event->timerId())
    {
        glwidget->update();
    }
}

void Dialog::command_G()
{
    int iiii=3; float poslist[3];
    if(g_1full==0)
    {
        switch(g_command[0])
        {
        case 0:
            //hcy*********************************************************************************开始
            while(iiii){
                poslist[iiii-1]=xyz_pos[iiii-1] ;
                float s(lineedit_setspeed[1]->text().toFloat()) ;
                if(m_aspeed>s)
                   { m_aspeed=s;}

                ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度

                iiii--;
            }
            switch(g_mode)
            {
            case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
            case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
            default:break;
            }
            //qDebug()<<poslist;
            //qDebug()<<g_mode;
            glwidget->g_mode00or01=0;
            break;

        case 1:
            while(iiii){
                poslist[iiii-1]=xyz_pos[iiii-1] ;
                float s(lineedit_setspeed[0]->text().toFloat()) ;
                if(m_aspeed>s)
                   { m_aspeed=s;}
                ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度


                iiii--;
            }
            switch(g_mode)
            {
            case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
            case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
            default:break;
            }
            //qDebug()<<poslist;
            //qDebug()<<g_mode;
            glwidget->g_mode00or01=1;
            break;

        default:break;
            //hcy*********************************************************************************结束
        }
    }
    else if(g_1full==1)
    {
        switch(g_command[0])
        {
        case 90:
            g_mode=90;
            switch(g_command[1])
            {
            case 0:
                //hcy*********************************************************************************开始
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[1]->text().toFloat()) ;
                    if(m_aspeed>s)
                       { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度
                    //if(m_aspeed)

                    iiii--;
                }
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                //qDebug()<<g_mode;
                glwidget->g_mode00or01=0;
                break;

            case 1:
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[0]->text().toFloat()) ;
                    if(m_aspeed>s)
                       { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度


                    iiii--;
                }
                //qDebug()<<poslist;
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                //qDebug()<<g_mode;
                glwidget->g_mode00or01=1;
                break;

            default:break;
                //hcy*********************************************************************************结束
            }
            break;

        case 91:
            g_mode=91;
            switch(g_command[1])
            {
            case 0:
                //hcy*********************************************************************************开始
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[1]->text().toFloat()) ;
                    if(m_aspeed>s)
                       { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度

                    iiii--;
                }
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                // qDebug()<<g_mode;
                glwidget->g_mode00or01=0;
                break;

            case 1:
                while(iiii){
                    poslist[iiii-1]=xyz_pos[iiii-1] ;
                    float s(lineedit_setspeed[0]->text().toFloat()) ;
                    if(m_aspeed>s)
                       { m_aspeed=s;}

                    ZAux_Direct_SetSpeed(g_handle,iiii-1,m_aspeed);//设置速度


                    iiii--;
                }
                switch(g_mode)
                {
                case 90:ZAux_Direct_MoveAbs(g_handle,3,poslist);break;
                case 91:ZAux_Direct_Move(g_handle,3,poslist);break;
                default:break;
                }
                //qDebug()<<poslist;
                //qDebug()<<g_mode;
                glwidget->g_mode00or01=1;
                break;

            default:break;
                //hcy*********************************************************************************结束
            }
            break;

        default:break;
        }
    }
}

void Dialog::command_M()
{
    int m_freq=500;
    uint8 m_bit=1;
    switch(Modbus)
    {
    case 2:
        ZAux_Modbus_Set4x_Long(g_handle,111,2,&m_freq);//频率寄存器111
        ZAux_Modbus_Set0x(g_handle,25,1,&m_bit);//暂停寄存器25，写1激活
        break;
    case 3:
        ZAux_Modbus_Set4x_Long(g_handle,111,1,&m_freq);//频率寄存器111
        ZAux_Modbus_Set0x(g_handle,23,1,&m_bit);//正向寄存器23，写1激活
        break;
    case 4://主轴反转
        ZAux_Modbus_Set4x_Long(g_handle,111,1,&m_freq);//频率寄存器111
        ZAux_Modbus_Set0x(g_handle,24,1,&m_bit);//反向寄存器24，写1激活
        break;
    case 5://主轴停止
        ZMC_Execute(g_handle,"MODBUSM_REGSET(99,1,1)" , 10,NULL,0);//频率寄存器111
        break;
    default:break;
    }
}

void Dialog::lianjie()
{

    char*  buffer;
    int32 iresult;
    if(nullptr != g_handle)
    {
        ZMC_Close(g_handle);
        g_handle = nullptr;
        killTimer(m_timerid);//停止计时
        killTimer(m_timerid_3D);//停止计时
    }
    QString currentIP(combobox_ip->currentText());
    QByteArray ba = currentIP.toUtf8();  //借助bytearray将Qstring转char*
    buffer=ba.data();
    iresult = ZMC_OpenEth(buffer, &g_handle);
    if(ERR_SUCCESS != iresult)
    {
        g_handle = nullptr;
        messagebox_warning.setText("连接失败");
        messagebox_warning.exec();
        setWindowTitle("未连接");
        ui->labTitle->setText(QString("三维运动系统（%1） 手柄（%2）").arg("未连接","已连接"));

        return;
    }
    m_timerid=startTimer(9);//开始计时
    m_timerid_3D=startTimer(8);//开始计时
    setWindowTitle("已连接:"+currentIP);
    ui->labTitle->setText(QString("三维运动系统（%1）").arg("已连接:"+currentIP));
    emit checkbox_xianweifanzhuan->click();//8.11

    pushbutton_duankai->setEnabled(true);
    pushbutton_lianjie->setEnabled(false);
    pushbutton_saveset->setEnabled(true);
    pushbutton_daoruwenjian->setEnabled(true);
    lianjie_ok=1;
}


void Dialog::duankai()
{
    if(nullptr != g_handle)
    {
        ZMC_Close(g_handle);
        g_handle = nullptr;
        setWindowTitle("未连接");
        ui->labTitle->setText(QString("运动控制器上位机（%1）").arg("未连接"));

        pushbutton_duankai->setEnabled(false);
        pushbutton_lianjie->setEnabled(true);
        pushbutton_saveset->setEnabled(false);
        killTimer(m_timerid);//停止计时
        killTimer(m_timerid_3D);//停止计时
        m_timerid=-1;
        m_timerid_3D=-1;
        lianjie_ok=0;
    }
}


void Dialog::setstatus()
{
    float inttemp;
    QString strtemp;
    if(windowTitle()=="未连接")
    {
        messagebox_warning.setText("请先连接控制器");
        messagebox_warning.exec();
        return;
    }
    for(int i=0;i<3;i++){

        if(combobox_ip->currentText()=="127.0.0.1")//仿真
        {
           ZAux_Direct_SetAtype(g_handle,i,0);//设置类型为脉冲方向
           ZAux_Direct_SetInvertStep(g_handle,i,1);//设置类型为脉冲方向
        }
        else
            ZAux_Direct_SetAtype(g_handle,i,65);//设置类型为脉冲方向

        strtemp=lineedit_setspeed[edit_set_lspeed]->text();
        inttemp=strtemp.toFloat();
        ZAux_Direct_SetSpeed(g_handle,i,inttemp);//设置加工速度

        ZAux_Direct_SetLspeed(g_handle,i,0);//初始速度为0

        //        strtemp=lineedit_setspeed[edit_set_speed]->text();
        //        inttemp=strtemp.toFloat();
        //        ZAux_Direct_SetSpeed(g_handle,i,inttemp);//设置最大速度

        strtemp=lineedit_setspeed[edit_set_acc]->text();
        inttemp=strtemp.toFloat();
        ZAux_Direct_SetAccel(g_handle,i,inttemp);//设置加速度

        strtemp=lineedit_setspeed[edit_set_dacc]->text();
        inttemp=strtemp.toFloat();
        ZAux_Direct_SetDecel(g_handle,i,inttemp);//设置减速度

        ZAux_Direct_SetSramp(g_handle,i,20);//梯形速度

        strtemp=lineedit_limit[i][edit_mcdl]->text();
        inttemp=strtemp.toFloat();
        ZAux_Direct_SetUnits(g_handle,i,inttemp);//设置脉冲当量

        strtemp=lineedit_limit[i][edit_zxw]->text();
        inttemp=strtemp.toFloat();
        ZAux_Direct_SetFsLimit(g_handle,i,inttemp);//设置正向软限位

        strtemp=lineedit_limit[i][edit_fxw]->text();
        inttemp=strtemp.toFloat();
        ZAux_Direct_SetRsLimit(g_handle,i,-inttemp);//设置负向软限位


        strtemp=lineedit_limit[i][edit_zxwio]->text();
        inttemp=strtemp.toInt();
        ZAux_Direct_SetFwdIn(g_handle,i,inttemp);//设置正限位io

        strtemp=lineedit_limit[i][edit_fxwio]->text();
        inttemp=strtemp.toInt();
        ZAux_Direct_SetRevIn(g_handle,i,inttemp);//设置负限位io

        strtemp=lineedit_limit[i][edit_zeroio]->text();
        inttemp=strtemp.toInt();
        ZAux_Direct_SetDatumIn(g_handle,i,inttemp);//设置回零开关io

        strtemp=lineedit_jiting->text();//急停io
        inttemp=strtemp.toInt();
        ZAux_Direct_SetAlmIn(g_handle, i, inttemp);
        /***PID设置****/
//        strtemp=lineedit_pid[i]->text();
//        inttemp=strtemp.toFloat();
//        QString sdo;
//        sdo=QString("SDO_WRITE(0,%1,$%2,0,3,%3)").arg(i).arg(2005+i).arg(inttemp);
//        //参数分别为（槽号：EtherCat总线，轴号，数据字典，子编号，数据类型：int16，数据值）
//        QByteArray ba = sdo.toUtf8();
//        char* pchar;
//        pchar = ba.data();
//        ZMC_Execute(g_handle,pchar,10,nullptr,0);


        pushbutton_saveset->setEnabled(false);

    }
    status_out();//保存数据到本地
}

void Dialog::editchange()
{
    pushbutton_saveset->setEnabled(true);
}


void Dialog::handcontrol_xplus(){
    ZAux_Direct_Singl_Vmove(g_handle,0,1);
    glwidget->g_mode00or01=0;//手动不画点
}

void Dialog::handcontrol_xzhouhuiling(){

    float zhengfu=(label_status[0][1]->text()).toFloat();

    if(zhengfu>0)
        ZAux_Direct_Singl_Datum(g_handle,0,19);

    else
        ZAux_Direct_Singl_Datum(g_handle,0,18);// ///////////////7.29
}

void Dialog::handcontrol_xplus_cancel(){
    ZAux_Direct_Singl_Cancel(g_handle,0,2);
}

void Dialog::handcontrol_xsub(){
    ZAux_Direct_Singl_Vmove(g_handle,0,-1);
    glwidget->g_mode00or01=0;//手动不画点
}

void Dialog::handcontrol_xsub_cancel(){
    ZAux_Direct_Singl_Cancel(g_handle,0,2);
}

void Dialog::handcontrol_yplus(){
    ZAux_Direct_Singl_Vmove(g_handle,1,1);
    glwidget->g_mode00or01=0;//手动不画点
}

void Dialog::handcontrol_yzhouhuiling(){
    float zhengfu=(label_status[1][1]->text()).toFloat();

    if(zhengfu>0)
        ZAux_Direct_Singl_Datum(g_handle,1,19);

    else
        ZAux_Direct_Singl_Datum(g_handle,1,18);// ///////////////7.29
}

void Dialog::handcontrol_yplus_cancel(){
    ZAux_Direct_Singl_Cancel(g_handle,1,2);
}

void Dialog::handcontrol_ysub(){
    ZAux_Direct_Singl_Vmove(g_handle,1,-1);
    glwidget->g_mode00or01=0;//手动不画点
}

void Dialog::handcontrol_ysub_cancel(){
    ZAux_Direct_Singl_Cancel(g_handle,1,2);
}

void Dialog::handcontrol_zplus(){
    ZAux_Direct_Singl_Vmove(g_handle,2,1);
    glwidget->g_mode00or01=0;//手动不画点
}

void Dialog::handcontrol_zzhouhuiling(){
    float zhengfu=(label_status[2][1]->text()).toFloat();

    if(zhengfu>0)
        ZAux_Direct_Singl_Datum(g_handle,2,19);

    else
        ZAux_Direct_Singl_Datum(g_handle,2,18);// ///////////////7.29
}


void Dialog::handcontrol_zplus_cancel(){
    ZAux_Direct_Singl_Cancel(g_handle,2,2);
}

void Dialog::handcontrol_zsub(){
    ZAux_Direct_Singl_Vmove(g_handle,2,-1);
    glwidget->g_mode00or01=0;//手动不画点
}

void Dialog::handcontrol_zsub_cancel(){
    ZAux_Direct_Singl_Cancel(g_handle,2,2);
}



void Dialog::handcontrol_shoudongjiting(){
    ZMC_Execute(g_handle,"MPOS=0,0,0",10,nullptr,0);
    ZMC_Execute(g_handle,"DPOS=0,0,0",10,nullptr,0);
}


void Dialog::handcontrol_zhidongfanzhuan(){
    if(checkbox_zhidongfanzhuan->isChecked()==1){
        label_led_zxw[0]->setStyleSheet("color:rgb(240,120,160)");
        int ionum;
        ionum=lineedit_jiting->text().toInt();
        ZAux_Direct_SetInvertIn(g_handle,ionum,1);
    }
    else if(checkbox_zhidongfanzhuan->isChecked()==0){
        label_led_zxw[0]->setStyleSheet("color:rgb(90,240,170)");
        int ionum;
        ionum=lineedit_jiting->text().toInt();
        ZAux_Direct_SetInvertIn(g_handle,ionum,0);
    }
}

void Dialog::handcontrol_xianweifanzhuan(){
    int ionum[6];
    ionum[0]=lineedit_limit[0][3]->text().toInt();
    ionum[1]=lineedit_limit[0][4]->text().toInt();
    ionum[2]=lineedit_limit[1][3]->text().toInt();
    ionum[3]=lineedit_limit[1][4]->text().toInt();
    ionum[4]=lineedit_limit[2][3]->text().toInt();
    ionum[5]=lineedit_limit[2][4]->text().toInt();
    if(checkbox_xianweifanzhuan->isChecked()==1){
        label_led_zxw[1]->setStyleSheet("color:rgb(240,120,160)");
        for(int i=0;i<=5;i++){
            ZAux_Direct_SetInvertIn(g_handle,ionum[i],1);
        }
    }
    else if(checkbox_xianweifanzhuan->isChecked()==0){
        label_led_zxw[1]->setStyleSheet("color:rgb(90,240,170)");
        for(int i=0;i<=5;i++){
            ZAux_Direct_SetInvertIn(g_handle,ionum[i],0);
        }
    }
}





/*void Dialog::bpqyunxing(){
    uint8 m_bit=1;
    int m_freq=0;
    QString pinlv;
    pinlv=lineedit_pinlv->text();
    m_freq=pinlv.toInt();
    ZAux_Modbus_Set4x_Long(g_handle,111,1,&m_freq);
    if(radiobutton_zhengxiang->isChecked()==1){
        ZAux_Modbus_Set0x(g_handle,23,1,&m_bit);
    }
    else if(radiobutton_fanxiang->isChecked()==1){
        ZAux_Modbus_Set0x(g_handle,24,1,&m_bit);
    }
}*/


/*void Dialog::bpqtingzhi(){
    uint8 m_bit=1;
    int m_freq=0;
    QString pinlv;
    pinlv=lineedit_pinlv->text();
    m_freq=pinlv.toInt();
    ZAux_Modbus_Set4x_Long(g_handle,111,2,&m_freq);
    ZAux_Modbus_Set0x(g_handle,25,1,&m_bit);
}*/
void Dialog::bpqyunxing()
{
    QString pinlv(lineedit_pinlv->text());
    int m_freq(pinlv.toInt());

    ZAux_Modbus_Set4x_Long(g_handle,3,1,&m_freq);//频率寄存器111
    ZMC_Execute(g_handle, "MODBUSM_REGSET(100,1,3)",10,  NULL, 0);
    Sleep(150);
    if(radiobutton_zhengxiang->isChecked()==1)//正向
    {
        ZMC_Execute( g_handle, "MODBUSM_REGSET(99,1,0)",10,  NULL, 0);
    }
    else if(radiobutton_fanxiang->isChecked()==1)//反向
    {
        ZMC_Execute( g_handle, "MODBUSM_REGSET(99,1,2)", 10, NULL, 0);
    }
}
void Dialog::bpqtingzhi()
{
    ZMC_Execute( g_handle, "MODBUSM_REGSET(99,1,1)", 10, NULL, 0);
}



void Dialog::daoruwenjian()
{
    ZAux_Direct_Rapidstop(g_handle,0);
//默认值
    g_command[0]=0;
    g_command[1]=0;//8.3默认G00
    g_0full=0; g_1full=0; g_mode=90;//默认没有出现G90/G91,默认坐标移动为绝对值



    m_aspeed=100.0;
    xyz_pos[0]=0.0;//目标点
    xyz_pos[1]=0.0;
    xyz_pos[2]=0.0;

    zhongduan_biaozhi=0;
    hangshu=0;
    jindutiao->setValue(0);
    num_yiyongshijian->setText(QString::number(0));//已用时间
    num_shengyushijian->setText(QString::number(0));//剩余时间
    num_Gdaimazongshu->setText(QString::number(0));//显示当前文件行数

    textedit_file->clear();
    QString fileName, filePath,fileSuffix;
    QFileInfo fileinfo;
    fileFull = QFileDialog::getOpenFileName(this,tr("file"),"/",tr("text(*.tap)"));  //获取整个文件名，打开tap文件
    //fileFull = E:\QtCode\newExample\myTry\新建文本文档.txt

    //获取文件信息
    fileinfo = QFileInfo(fileFull);

    //获取文件名字
    fileName = fileinfo.fileName();

    //获取文件后缀
    fileSuffix = fileinfo.suffix();

    //获取文件绝对路径
    filePath = fileinfo.absolutePath();
    if(!fileFull.isNull())
    {
        pushbutton_qidong->setEnabled(true);
        pushbutton_zanting->setEnabled(true);
        pushbutton_jixu->setEnabled(true);
        pushbutton_zuobiaoqingling->setEnabled(true);
        pushbutton_duidaodianhuifu->setEnabled(true);
        QFile file(fileFull);//通过文件路径，来获取文件
        if(!file.open(QFile::ReadOnly ))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);

        lineedit_file->setText(fileFull);

        //逐行读取文件并放入wen'ben'kuan文本框
        QTextCodec *codec = QTextCodec::codecForName("GBK");//指定为GBK,因为file.readLine()无法读取中文
        while (!file.atEnd())
        {

            //读取一行文本数据
            QByteArray line = file.readLine();
            //将读取到的行数据转换为Unicode
            QString str = codec->toUnicode(line);       //文件每一行内容
            //qDebug() << str;

            textedit_file->insertPlainText(str);//追加放入文本框②

            hangshu++;
        }
        file.close();
        num_Gdaimazongshu->setText(QString::number(hangshu));//显示当前文件行数

    }
    else
    {
        qDebug()<<"cancel";
        fileFull="No file";
    }

}

void Dialog::qidong()
{
    //三维图清空，（之后从当前点开始走）没有回零功能
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear=1;}
    glwidget->points_x.clear();
    glwidget->points_y.clear();
    glwidget->points_z.clear();
    glwidget->xyz_mode.clear();

    zhongduan_biaozhi=1;
    iiiii=1;
    textedit_file->moveCursor(QTextCursor::Start);//进度条滚到顶

    //通过文件路径，来获取文件
    fileread=new QFile(fileFull);
    if(!fileread->open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(fileread->errorString()));
        return;
    }
    //显示初始化
    hangshu=0;
    jindutiao->setValue(0);
    num_yiyongshijian->setText(QString::number(0));//已用时间
    num_shengyushijian->setText(QString::number(0));//剩余时间
    num_Gdaimazongshu->setText(QString::number(0));//显示当前文件行数
    textedit_file->clear();
    textedit_file->setTextColor("black");

    if(!fileFull.isNull())
    {

        QFile file(fileFull);//通过文件路径，来获取文件
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);

        lineedit_file->setText(fileFull);



        //逐行读取文件并放入wen'ben'kuan文本框
        QTextCodec *codec = QTextCodec::codecForName("GBK");//指定为GBK,因为file.readLine()无法读取中文
        while (!file.atEnd())
        {

            //读取一行文本数据
            QByteArray line = file.readLine();
            //将读取到的行数据转换为Unicode
            QString str = codec->toUnicode(line);       //文件每一行内容
            textedit_file->insertPlainText(str);//追加放入文本框②
            hangshu++;
        }
        //  file.close();
        num_Gdaimazongshu->setText(QString::number(hangshu));//显示当前文件行数

    }
    else
    {
        fileFull="No file";
    }

}


void Dialog::Readcode_G()  //带未选择文件检测
{
    if(fileFull=="No file"){textedit_file->setPlainText("No file");}
    else
    {
        textedit_file->moveCursor(QTextCursor::Start);//进度条滚到顶
        QTextCodec *codec = QTextCodec::codecForName("GBK");//指定为GBK,因为file.readLine()无法读取中文

        //通过文件路径，来获取文件
        QFile fileread(fileFull);
        if(!fileread.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this,tr("Error"),tr("read file error:&1").arg(fileread.errorString()));
            return;
        }


        char* fileat;//用来指向每行的某个字符
        QString str;
        float i=1;int row=0;int lie=0;
        QTextCursor cursor;
        while(i<=hangshu)
        {
            //while(pause);

            //字体的颜色
            textedit_file->setTextColor("black");

            //设置选中行的颜色
            fmt.setForeground(QColor(Qt::green));

            //移动光标到某行行首
            QTextBlock block = textedit_file->document()->findBlockByNumber(i-1);
            textedit_file->setTextCursor(QTextCursor(block));

            //上色
            cursor = textedit_file->textCursor();
            cursor.select(QTextCursor::LineUnderCursor);   //选中要着色的内容
            cursor.mergeCharFormat(fmt);    //设置文本格式
            cursor.clearSelection(); //撤销选中

            //获取光标所在行列
            row=cursor.blockNumber();
            lie=cursor.columnNumber();
            qDebug()<<row<<lie;


            //读取一行文本数据
            QByteArray lineread = fileread.readLine();
            //将读取到的行数据转换为Unicode
            str = codec->toUnicode(lineread);       //文件每一行内容
            qDebug()<<str;
            //   strcpy(str_char, str);
            QByteArray ba = str.toUtf8();
            fileat = ba.data();
            qDebug()<<fileat;
            for(;*fileat;fileat++)//依次对各个字符进行解析
            {
                switch(*fileat)
                {
                case 'G':
                    if(g_0full==0)
                    {   g_command[0] = atoi(fileat+1);g_0full=1;}
                    else
                    {   g_command[1]= atoi(fileat+1); g_1full=1;}
                    break;
                case 'F':
                    m_aspeed  = atof(fileat+1);
                    break;
                case 'X':
                    xyz_pos[0] = atof(fileat+1);
                    break;
                case 'Y':
                    xyz_pos[1] = atof(fileat+1);
                    break;
                case 'Z':
                    xyz_pos[2] = atof(fileat+1);
                    break;
                default: break;

                }
            }

            num_yiyongshijian->setText(QString::number(iiiii));//已用时间
            num_shengyushijian->setText(QString::number(hangshu-iiiii));//剩余时间
            qDebug()<<g_command;
            qDebug()<<m_aspeed;
            qDebug()<<xyz_pos[0]<<xyz_pos[1]<<xyz_pos[2];

            jindutiao->setValue((iiiii/hangshu)*100);
            iiiii++;

            command_G();//运行对应运动函数
            g_0full=0;
            g_1full=0;
        }
        textedit_file->setTextColor("black");

    }

}
void Dialog::Pause()
{
    zhongduan_biaozhi=0;
    ZAux_Direct_MovePause(g_handle,0);
    pushbutton_qidong->setEnabled(false);
    pushbutton_zuobiaoqingling->setEnabled(false);
    pushbutton_duidaodianhuifu->setEnabled(false);//8.11
}

void Dialog::Continue()
{
    zhongduan_biaozhi=1;
    ZAux_Direct_MoveResume(g_handle);
    pushbutton_qidong->setEnabled(true);
    pushbutton_zuobiaoqingling->setEnabled(true);
    pushbutton_duidaodianhuifu->setEnabled(true);
}

void Dialog::zuobiaoqingling()
{
    float poslist[3]={0,0,0};
    ZAux_Direct_MoveAbs(g_handle,3,poslist);

    //三维图清空，（之后从当前点开始走）
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear=1;}
    glwidget->points_x.clear();
    glwidget->points_y.clear();
    glwidget->points_z.clear();
    glwidget->xyz_mode.clear();
}

void Dialog::duidaodianjiyi()
{
    float fdpos(0);
    for(int i=0;i<3;i++)
    {
        ZAux_Direct_GetDpos(g_handle,i,&fdpos);//获得轴位置
        daodianjiyi[i]=fdpos ;
    }
}
void Dialog::duidaodianhuifu()
{
    ZAux_Direct_MoveAbs(g_handle,3,daodianjiyi);
}

//语言识别1
void Dialog::on_pushButton_voice_recog_pressed()
{
    ui->pushButton_voice_recog->setText("松开识别");
    //开始录音
    audio = new Audio;
    audio->startAudio("D:\\audio.pcm");
}

//语音识别2
void Dialog::on_pushButton_voice_recog_released()
{
    //停止录音
    audio->stopAudio();
    //修改按钮文字
    ui->pushButton_voice_recog->setText("开始识别");
    //开始识别
    Speech m_speech;
    QString text =  m_speech.speechIdentify("D:\\audio.pcm");
    ui->lineEdit_voice->setText(text);

    ui->pushButton_voice_recog->setText("按住说话");
}

//清除
void Dialog::on_pushButton_clear_clicked()
{
    ui->lineEdit_voice->clear();
}

//语音指令解析与执行
void Dialog::on_pushButton_act_clicked()
{
    QString tem_text = ui->lineEdit_voice->text();
    qDebug()<<tem_text;
    int direction = 0;
    int polar = 0;
    int length = 0;
    //语音指令解析与执行
    QStringList keywords = {"x", "y", "z", "正", "负"};
    QString keywordPattern = "(?:" + keywords.join("|") + ")";
    QRegularExpression keywordRegex(keywordPattern, QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatchIterator keywordMatches = keywordRegex.globalMatch(tem_text);

    while (keywordMatches.hasNext()) {
        QRegularExpressionMatch match = keywordMatches.next();
        qDebug() << "Keyword: " << match.captured(0);
        QString tem_str = match.captured(0);
        if(tem_str == 'x' || tem_str == 'X')
        {
            direction = 1;
        }
        else if(tem_str == 'y' || tem_str == 'Y')
        {
            direction = 2;
        }
        else if(tem_str == 'z' || tem_str == 'Z')
        {
            direction = 3;
        }

        if(tem_str == "正")
        {
            polar = 1;
        }
        else if(tem_str == "负")
        {
            polar = 2;
        }
    }

    // Find numbers using regular expression
    QRegularExpression numberRegex("-?\\b\\d+\\b");
    QRegularExpressionMatchIterator numberMatches = numberRegex.globalMatch(tem_text);

    while (numberMatches.hasNext()) {
        QRegularExpressionMatch match = numberMatches.next();
        qDebug() << "Number: " << match.captured(0);
        length = match.captured(0).toInt();
    }
    qDebug()<<"Direction:"<<direction;
    qDebug()<<"Polar:"<<polar;
    qDebug()<<"Length:"<<length;

    ZAux_Direct_Singl_Move(g_handle,direction, length);
    qDebug() << "success";
}

void Dialog::receiveshow()
{
    this->show();
}

void Dialog::display_slot_row(joyinfoex_tag state_row)
{
//     if(state_row.dwButtons & 0x01 << 0) {
//         bpqyunxing();
//         qInfo()<<"变频器运行";
//     }

//     else if(state_row.dwButtons & 0x01 << 1) {
//         bpqtingzhi();
//         qInfo()<<"变频器停止";
//     }

//     else if(state_row.dwButtons & 0x01 << 2) {
//         handcontrol_shoudongjiting();
//         qInfo()<<"手动急停";
//     }

//     else if(state_row.dwButtons & 0x01 << 4) {
//         handcontrol_zplus();
//         qInfo()<<"z轴正向";
//     }

//     else if(state_row.dwButtons & 0x01 << 5) {
//         handcontrol_zsub();
//         qInfo()<<"z轴负向";
//     }
//     else
//     {
//         handcontrol_zsub_cancel();
//         handcontrol_zplus_cancel();
//        // qInfo()<<"z轴取消运动";
//     }

//     if(state_row.dwPOV == 0) {
//         handcontrol_yplus();
//         qInfo()<<"y轴正向";
//         if(state_row.dwPOV == 65535)
//             handcontrol_yplus_cancel();
//             qInfo()<<"y轴正向取消运动";
//     } else if(state_row.dwPOV == 9000) {
//         handcontrol_xplus();
//         qInfo()<<"x轴正向";
//     } else if(state_row.dwPOV == 18000) {
//         handcontrol_ysub();
//         qInfo()<<"y轴负向";
//     } else if(state_row.dwPOV == 27000) {
//         handcontrol_xsub();
//         qInfo()<<"x轴负向";
//     } else if(state_row.dwPOV == 4500) {
//         handcontrol_yplus();
//         handcontrol_xplus();
//         qInfo()<<"x，y轴正向";
//     } else if(state_row.dwPOV == 31500) {
//         handcontrol_xsub();
//         handcontrol_yplus();
//         qInfo()<<"x轴负向，y轴正向";
//     } else if(state_row.dwPOV == 13500) {
//         handcontrol_xplus();
//         handcontrol_ysub();
//         qInfo()<<"x轴正向，y轴负向";
//     } else if(state_row.dwPOV == 22500) {
//         handcontrol_ysub();
//         handcontrol_xsub();
//         qInfo()<<"x轴负向，y轴负向";
//     }
//     else
//     {
//         handcontrol_xplus_cancel();
//         handcontrol_yplus_cancel();
//         handcontrol_xsub_cancel();
//         handcontrol_ysub_cancel();
//         //qInfo()<<"x轴，y轴，运动取消";
//     }
}

void Dialog::keyPressEvent(QKeyEvent* event) {
    int key = event->key();
    qInfo()<<key;
    switch (key) {
    case Qt::Key_W:
        //handcontrol_yplus();
        ZAux_Direct_Singl_Move(g_handle,1, 1000);
        break;
    case Qt::Key_S:
         ZAux_Direct_Singl_Move(g_handle,1, -1000);
        break;
    case Qt::Key_A:
         ZAux_Direct_Singl_Move(g_handle,0, 1000);
        break;
    case Qt::Key_D:
         ZAux_Direct_Singl_Move(g_handle,0, -1000);
        break;
    case Qt::Key_N:
         ZAux_Direct_Singl_Move(g_handle,2, 1000);
        break;
    case Qt::Key_M:
         ZAux_Direct_Singl_Move(g_handle,2, -1000);
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void Dialog::keyReleaseEvent(QKeyEvent *event) {
    int key = event->key();
    qInfo()<<key;
    switch (key) {
    case Qt::Key_W:
        ZAux_Direct_Singl_Move(g_handle,1, 0);
        break;
    case Qt::Key_S:
        ZAux_Direct_Singl_Move(g_handle,1, 0);
        break;
    case Qt::Key_A:
        ZAux_Direct_Singl_Move(g_handle,0, 0);
        break;
    case Qt::Key_D:
        ZAux_Direct_Singl_Move(g_handle,0, 0);
        break;
    case Qt::Key_N:
        ZAux_Direct_Singl_Move(g_handle,2, 0);
        break;
    case Qt::Key_M:
        ZAux_Direct_Singl_Move(g_handle,2, 0);
        break;
    default:
        QWidget::keyReleaseEvent(event);
        break;
    }
}

void Dialog::on_pushButton_generate_clicked()
{
    // 提取问题
    QString tem_text = ui->lineEdit_voice->text();

    // 发送请求接收结果
    QString tem_answer = getAnswer(tem_text);

    // 添加刀具参数
    QString daoju_papameters = "T1M6\nG17\nG0Z10.000\nG0X0.000Y0.000S20000M3\nG0X-21.167Y-37.667Z10.000";
    textedit_file->insertPlainText(daoju_papameters);
    // 合成G代码并显示
    textedit_file->insertPlainText(tem_answer);//追加放入文本框

}

void Dialog::onConnected()
{
    qDebug() << "Connected to server";
}

void Dialog::onDisconnected()
{
    qDebug() << "Disconnected from server";
}

void Dialog::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    QString message = QString::fromUtf8(data);
    m_textEdit->append(message);
}

void Dialog::getAccessToken()
{
    // 构造HTTP请求
    QUrl url("https://spark-api-open.xf-yun.com/v1/chat/completions");
    QNetworkRequest request(url);

    // 设置请求头部为JSON格式
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 从成员变量获取API密钥和秘密
    QString apiKey = m_apiKey;
    QString apiSecret = m_apiSecret;

    // 构建Bearer认证的头部，将API密钥和秘密以冒号分隔
    QString bearerToken = QString("Bearer %1:%2").arg(apiKey).arg(apiSecret);

    // 将Bearer Token设置为请求的Authorization头部
    request.setRawHeader("Authorization", bearerToken.toUtf8());

    // 发送HTTP请求
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.post(request, QString("grant_type=client_credentials&client_id=%1&client_secret=%2").arg(m_appId).arg(m_apiSecret).toUtf8());
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 解析HTTP响应
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        m_accessToken = jsonDocument.object().value("access_token").toString();
        int expiresIn = jsonDocument.object().value("expires_in").toInt();
        m_expireTime = QDateTime::currentDateTime().addSecs(expiresIn);
    }
    else
    {
        qDebug() << "Failed to get access token: " << reply->errorString();
    }

    // 释放HTTP响应
    reply->deleteLater();
}

QString Dialog::getAnswer(const QString& question)
{
    // 检查访问令牌是否过期
    if (QDateTime::currentDateTime() >= m_expireTime)
    {
        getAccessToken();
    }

    // 构造HTTP请求
    QUrl url("https://spark-api-open.xf-yun.com/v1/chat/completions");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_accessToken).toUtf8());

    QJsonObject json;
    json.insert("scene", "main");
    json.insert("userid", "123456");
    json.insert("auth_id", "123456");
    json.insert("text", question);
    QJsonDocument jsonDocument(json);
    QByteArray postData = jsonDocument.toJson(QJsonDocument::Compact);

    // 发送HTTP请求
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.post(request, postData);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 解析HTTP响应
    QString answer;
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = jsonDocument.object();
        if (jsonObject.contains("data"))
        {
            QJsonObject data = jsonObject.value("data").toObject();
            QJsonArray answerArray = data.value("answer").toArray();
            for (int i = 0; i < answerArray.size(); i++)
            {
                QJsonObject answerObject = answerArray.at(i).toObject();
                if (answerObject.contains("text"))
                {
                    answer += answerObject.value("text").toString() + " ";
                }
            }
        }
    }
    else
    {
        qDebug() << "Failed to get answer: " << reply->errorString();
    }

    // 释放HTTP响应
    reply->deleteLater();

    return answer.trimmed();
}

void Dialog::onTextChange()
{
    QString text = m_textEdit->toPlainText();
    int index = text.lastIndexOf("@机器人");

}

void Dialog::sendMessage()
{
    QString message = m_lineEdit->text();
    if (!message.isEmpty())
    {
        m_socket->write(message.toUtf8());
        m_lineEdit->clear();
    }
}



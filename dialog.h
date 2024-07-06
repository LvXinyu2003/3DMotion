#ifndef DIALOG_H
#define DIALOG_H
#include"zaux.h"
#include "glwidget.h"
#include<QtWidgets>
#include <QDialog>
#include<QMouseEvent>
#include<QScreen>
#include<QFontDatabase>
#include<glwidget.h>
#include <audio.h>
#include <speech.h>
#include "joy_thread.h"
#include <QTest>

enum LABEL_LED_ZWX{
    label_led_jinjizhidong,//紧急制动
    label_led_menxianwei,
    label_led_xplus,
    label_led_xsub,
    label_led_yplus,
    label_led_ysub,
    label_led_zplus,
    label_led_zsub,
};
enum EDIT_SET{//文本框
    edit_set_lspeed,//初速度
    edit_set_speed,//速度
    edit_set_acc,//加速度
    edit_set_dacc//减速度
};
enum EDIT_MCDL{
    edit_mcdl,//脉冲当量
    edit_zxw,//软正限位
    edit_fxw,//软负限位
    edit_zxwio,//硬正限位io
    edit_fxwio,//硬负限位io
    edit_zeroio//回零开关
};

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    Audio *audio;
    QWidget* widget_canshu;//参数界面
    QWidget* widget_zidong;//自动
    QWidget* widget_shoudong;//手动
    QWidget* widget_staff;//制作人员
    //QWidget* widget_3D;//3d图形界面

    //双击标题栏进行界面的最大化/还原
    void mouseDoubleClickEvent(QMouseEvent *event);

    //进行界面的拖动
    void mousePressEvent(QMouseEvent *event);

    //事件过滤器，关联标题栏与原标题栏
    bool eventFilter(QObject *obj, QEvent *event);
    void initForm();//自定义样式窗口初始化
    void status_in();//读取数据文件
    void status_out();//写入数据文件




private slots:

    void buttonClick();
    void onClicked();
    void display_slot_row(joyinfoex_tag state_row);
    void receiveshow();

private:
    int m_timerid;//定时器返回值
    int m_timerid_3D;//定时器返回值
    ZMC_HANDLE g_handle;//zmc句柄

    //QWidget* centralwiget;//主窗口
    QMessageBox messagebox_warning;//弹窗
    //QTabWidget* tabwidget;//界面切换


    QGroupBox* groupbox_link;//连接模块
    QComboBox* combobox_ip;//设置ip
    QPushButton* pushbutton_lianjie;//连接
    QPushButton* pushbutton_duankai;//断开

    QGroupBox* groupbox_axis[3];//3个轴
    QLabel* label_status[3][3];//3三个轴 每个轴3个标签

    QGroupBox* groupbox_pid;//pid模块
    QLineEdit* lineedit_pid[3];

    QGroupBox* groupbox_setspeed;//速度设置块
    QLineEdit* lineedit_setspeed[6];

    QGroupBox* groupbox_limit[3];//脉冲当量
    QLineEdit* lineedit_limit[3][6];//脉冲当量与限位 1(脉冲当量） 2（正限位） 3（负限位）4(正限位io） 5（负限位io） 6（回零io）

    QPushButton* pushbutton_saveset;//保存设置

    QLineEdit* lineedit_jiting;

    /************吴炼***************/
    QGroupBox* groupbox_message;//Message
    QTextEdit* textedit_message;//message文本

    QGroupBox* groupbox_bpqcanshu;//变频器参数
    QLabel* label_pinlv;
    QPushButton* pushbutton_yunxing;//运行按钮
    QPushButton* pushbutton_tingzhi;//停止按钮
    QLineEdit* lineedit_pinlv;//频率
    QRadioButton* radiobutton_zhengxiang;//正向
    QRadioButton* radiobutton_fanxiang;//反向
    QButtonGroup* buttongroup_zhengfan;

    QGroupBox* groupbox_zhouxianwei;//轴限位状态
    QCheckBox* checkbox_zhidongfanzhuan;//制动反转
    QCheckBox* checkbox_xianweifanzhuan;//限位反转
    QLabel* label_led_zxw[8];
    QLabel* label_led_name[8];

    QGroupBox* groupbox_handcontrol;//三维手动控制
    QPushButton* pushbutton_xzhouhuiling;//x轴回零
    QPushButton* pushbutton_yzhouhuiling;//y轴回零
    QPushButton* pushbutton_zzhouhuiling;//z轴回零
    QPushButton* pushbutton_shoudongjiting;//急停
    QPushButton* pushbutton_handcontrol[6];//手动控制按钮

    //hcy********************************************************************************************************************************开始
    //int m_timerid;//定时器返回值
    bool  zhongduan_biaozhi;
    QPushButton* pushbutton_daoruwenjian;//导入文件
    QPushButton* pushbutton_qidong;//启动
    QPushButton* pushbutton_jixu;//继续
    QPushButton* pushbutton_zuobiaoqingling;//坐标清零
    QPushButton* pushbutton_zanting;//暂停
    QPushButton* pushbutton_duidaodianjiyi;//对刀点记忆
    QPushButton* pushbutton_duidaodianhuifu;//对刀点恢复
    QLineEdit* lineedit_file;
    QTextEdit* textedit_file;
    QTextEdit* textedit_file1;
    QLabel* Gdaimazongshu;
    QLabel* jindu;
    QLabel* yiyongshijian;
    QLabel* shengyushijian;
    QLabel* num_Gdaimazongshu;
    QLabel* num_jindu;
    QLabel* num_yiyongshijian;
    QLabel* num_shengyushijian;
    float hangshu=0;
    QString fileFull="No file";
    int g_command[2]={0,0};//8.3默认G00，默认没有出现G90/G91
    int g_0full=0;int g_1full=0;int g_mode=90;//默认坐标移动为绝对值
    int Modbus=2;
    float m_aspeed=100.0;
    float xyz_pos[3]={0.0,0.0,0.0};//目标点
    float daodianjiyi[3];
    QTextCharFormat fmt;
    //Thread *myThread;
    float iiiii=1; int row=0, lie=0;
    bool fileread_biaozhi=0;
    QFile* fileread;
    QTextCursor cursor;

    QGroupBox* groupbox_G;//G代码模块
    QGroupBox* groupbox_file;
    QProgressBar* jindutiao;
    //3D 画图控件glwidget
    GLWidget *glwidget;
    QGroupBox* groupbox_3D;

    bool lianjie_ok=0;



private:
    void timerEvent(QTimerEvent *event);
    //void timerEvent_3D(QTimerEvent *event);

private slots:

    void lianjie();//连接按钮
    void duankai();//断开按钮
    void setstatus();//保存设置
    void editchange();//输入有变化



    /************吴炼***************/
    void handcontrol_xplus();//手动x轴正方向运动
    void handcontrol_xzhouhuiling();//手动x轴回零
    void handcontrol_xplus_cancel();//手动x轴正方向暂停
    void handcontrol_xsub();//手动x轴负方向运动
    void handcontrol_xsub_cancel();//手动x轴负方向暂停
    void handcontrol_yplus();//手动y轴正方向运动
    void handcontrol_yzhouhuiling();//手动y轴回零
    void handcontrol_yplus_cancel();//手动y轴正方向暂停
    void handcontrol_ysub();//手动y轴负方向运动
    void handcontrol_ysub_cancel();//手动y轴负方向暂停
    void handcontrol_zplus();//手动z轴正方向运动
    void handcontrol_zzhouhuiling();//手动z轴回零
    void handcontrol_zplus_cancel();//手动z轴正方向暂停
    void handcontrol_zsub();//手动z轴负方向运动
    void handcontrol_zsub_cancel();//手动z轴负方向暂停
    void handcontrol_shoudongjiting();//手动模式急停
    void handcontrol_zhidongfanzhuan();//手动制动反转
    void handcontrol_xianweifanzhuan();//手动限位反转

    void bpqyunxing();//变频器运行
    void bpqtingzhi();//变频器停止

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent *event);

    //hcy********************************************************************************************************************************开始
    //void timerEvent(QTimerEvent *event);
    void daoruwenjian();//打开文件
    void Readcode_G();//解码G代码
    void qidong();//启动
    void Pause();
    void Continue();

    void command_G();
    void command_M();//hcy.7.24
    void zuobiaoqingling();//hcy7.29
    void duidaodianjiyi();//hcy8.3
    void duidaodianhuifu();

    void on_pushButton_voice_recog_pressed();
    void on_pushButton_voice_recog_released();
    void on_pushButton_clear_clicked();
    void on_pushButton_act_clicked();
    void on_pushButton_generate_clicked();
};
#endif // DIALOG_H

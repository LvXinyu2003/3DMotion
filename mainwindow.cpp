#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QPushButton>

bool MainWindow::myconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("student.db");
    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
                              QObject::tr("Unable to establish a database connection.\n"
                                          "This example needs SQLite support. Please read "
                                          "the Qt SQL driver documentation for information how "
                                          "to build it.\n\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }
    return true;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("登陆界面");//窗口标题


    ui->stackedWidget->setCurrentIndex(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    ui->pushButton_login->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_queren_login_clicked()//学生登录
{
    QString a1=ui->lineEdit->text();
    QString a2=ui->lineEdit_2->text();
    int flag = 0;

    myconnect();
    QSqlQuery que("select * from sin ");

    while(que.next()){
        QString q1=que.value(0).toString();
        QString q2=que.value(1).toString();
        if(a1==q1&&a2==q2){
            flag=1;

        }

    }//判断学生输入账号密码是否匹配
    flag=1;
    if(flag){

        int flag1=0;

        myconnect();
        QSqlQuery que1("select sno from sc ");

        while(que1.next()){
            QString q3=que1.value(0).toString();

            if(a1==q3){
                flag1=1;

            }

        }//判断sc表中是否有该学生信息

        QMessageBox::StandardButton result = QMessageBox::information(this, "提示","登录成功");
        studentqrModel=new QSqlQueryModel(this);
        myconnect();
        QSqlQuery qr;
        if(flag1)
        {
            qr.prepare("select student.*,cno,grade from student,sc where student.sno=sc.sno and student.sno=? ");
        }
        else
        {
            qr.prepare("select * from student where sno=? ");
        }
        qr.addBindValue(a1);
        qr.exec();
        studentqrModel->setQuery(qr);
        this->hide();
        emit testshow();

    }
    else{
        QMessageBox::StandardButton result = QMessageBox::information(this, "提示","用户名或密码错误");
    }
}


void MainWindow::on_pushButton_Sdel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_login->setEnabled(true);
}


void MainWindow::on_pushButton_queren_clicked()//注册
{
    QString z1=ui->lineEdit_3->text();
    QString z2=ui->lineEdit_8->text();
    QString z3=ui->lineEdit_4->text();
    QString z4=ui->lineEdit_5->text();
    QString z5=ui->lineEdit_6->text();
    QString z6=ui->lineEdit_7->text();

    myconnect();
    QSqlQuery que("select * from student");
    int flag = 0;
    while(que.next()){
        QString q1=que.value(0).toString();

        if(z1==q1)
        {
            flag = 1;
        }
    }//判断注册信息在数据库中是否存在


    if(z1!=""&&z2!=""&&z3!=""&&z4!=""&&z5!=""&&z6!=""&&!flag){//不能注册空数据和重复数据
        studentqrModel=new QSqlQueryModel(this);

        myconnect();
        QSqlQuery qr,qq;
        qr.prepare("insert into student values(?,?,?,?,?) ");//注册student

        qr.addBindValue(z1);
        qr.addBindValue(z3);
        qr.addBindValue(z4);
        qr.addBindValue(z5);
        qr.addBindValue(z6);
        qr.exec();

        studentqrModel->setQuery(qr);

        qq.prepare("insert into sin values(?,?) ");//注册账号密码
        qq.addBindValue(z1);
        qq.addBindValue(z2);
        qq.exec();

        QMessageBox::StandardButton result = QMessageBox::information(this, "提示","注册成功");
        ui->stackedWidget->setCurrentIndex(1);
    }

    else
    {QMessageBox::StandardButton result = QMessageBox::information(this, "提示","注册失败");}

}

void MainWindow::on_pushButton_register_clicked()//跳转至注册界面
{
    ui->stackedWidget->setCurrentIndex(2);
}
void MainWindow::receivelogin()
{
    this->show();
}

void MainWindow::on_pushButton_clicked()
{
    exit(0);
}


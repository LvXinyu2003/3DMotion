#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<dialog.h>
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlTableModel>
#include<QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlRelationalTableModel>
#include<QtSql>
#include"dialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    bool myconnect();
private:
    QSqlTableModel*homeModel;//查询数据放入模型，按模型结构显示
    QSqlRelationalTableModel*studentModel;
    QSqlQueryModel* studentqrModel;
    //QSqlQuery *que;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void testshow();


private slots:
    void receivelogin();

    void on_pushButton_login_clicked();

    void on_pushButton_queren_login_clicked();

    void on_pushButton_Sdel_clicked();

    void on_pushButton_queren_clicked();

    void on_pushButton_register_clicked();

    //Dialog w;

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


#include "zaux.h"
#include "zmotion.h"
#include <QDebug>
#include <QString>

typedef signed int int32; /* defined for signed 32-bits integer variable         有符号32位整型变量 */

//int32 __stdcall ZMC_DirectCommand(ZMC_HANDLE handle, const char* pszCommand, char* psResponse, uint32 uiResponseLength);
//ZAUX支持的最大轴数宏
#define MAX_AXIS_AUX 32
#define MAX_CARD_AUX 16

/*************************************************************
Description:    //读取轴是否运动结束
Input:          //卡链接handlea
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetIfIdle(ZMC_HANDLE handle, int iaxis, int* piValue)
{
    int32 iresult;
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("?IDLE(%1)").arg(iaxis);
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    iresult = ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);

    if (ERR_OK != iresult) {
        return iresult;
    }

    //
    if (0 == strlen(cmdbuffAck)) {
        return ERR_NOACK;
    }

    //
    sscanf(cmdbuffAck, "%d", piValue);

    return ERR_OK;
}

int32 __stdcall ZAux_Direct_SetUnits(ZMC_HANDLE handle, int iaxis, float fValue)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("units(%1) = %2").arg(iaxis).arg(fValue);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //设置轴速度，单位为units/s，当多轴运动时，作为插补运动的速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetSpeed(ZMC_HANDLE handle, int iaxis, float fValue)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("speed(%1) = %2").arg(iaxis).arg(fValue);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //设置加速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetAccel(ZMC_HANDLE handle, int iaxis, float fValue)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("ACCEL(%1) = %2").arg(iaxis).arg(fValue);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //设置减速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetDecel(ZMC_HANDLE handle, int iaxis, float fValue)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("DECEL(%1) = %2").arg(iaxis).arg(fValue);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //设置轴起始速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetLspeed(ZMC_HANDLE handle, int iaxis, float fValue)
{

    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("LSPEED(%1) = %2").arg(iaxis).arg(fValue);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //设置 S曲线设置。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetSramp(ZMC_HANDLE handle, int iaxis, float fValue)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("SRAMP(%1) = %2").arg(iaxis).arg(fValue);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //单轴运动
Input:          //卡链接handle  轴号， 距离
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Move(ZMC_HANDLE handle, int iaxis, float fdistance)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("MOVE(%2)  axis(%1)").arg(iaxis).arg(fdistance);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //连续运动
Input:          //卡链接handle  轴号， 方向
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Vmove(ZMC_HANDLE handle, int iaxis, int idir)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("VMOVE(%2) AXIS(%1)").arg(iaxis).arg(idir);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //单轴运动停止
Input:          //卡链接handle  轴号， 模式
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Cancel(ZMC_HANDLE handle, int iaxis, int imode)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("CANCEL(%2) AXIS(%1)").arg(iaxis).arg(imode);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //设置轴位置
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetDpos(ZMC_HANDLE handle, int iaxis, float fValue)
{
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("DPOS(%1)=%2").arg(iaxis).arg(fValue);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //读取轴位置
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetDpos(ZMC_HANDLE handle, int iaxis, float* pfValue)
{
    int32 iresult;
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("?DPOS(%1)").arg(iaxis);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    iresult = ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);

    if (ERR_OK != iresult) {
        return iresult;
    }

    //
    if (0 == strlen(cmdbuffAck)) {
        return ERR_NOACK;
    }

    //
    sscanf(cmdbuffAck, "%f", pfValue);

    return ERR_OK;
}
/*************************************************************
Description:    //参数
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetVpSpeed(ZMC_HANDLE handle, int iaxis, float* pfValue)
{
    int32 iresult;
    char cmdbuffAck[2048];
    QString tmp_str;
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    tmp_str = QString("?VP_SPEED(%1)").arg(iaxis);
    //qDebug()<<"tmp_str"<<tmp_str;
    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    iresult = ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
    if (ERR_OK != iresult) {
        return iresult;
    }

    //
    if (0 == strlen(cmdbuffAck)) {
        return ERR_NOACK;
    }

    sscanf(cmdbuffAck, "%f", pfValue);

    return ERR_OK;
}
/////////////////////////////////////////////////////wgy
/*************************************************************
Description:    //设置轴类型
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetAtype(ZMC_HANDLE handle, int iaxis, int iValue)
{
    char cmdbuff[2048];
    char cmdbuffAck[2048];
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "ATYPE(%d)=%d", iaxis, iValue);
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //设置脉冲输出模式
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetInvertStep(ZMC_HANDLE handle, int iaxis, int iValue)
{

    char cmdbuff[2048];
    char cmdbuffAck[2048];
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }
    //生成命令
    sprintf(cmdbuff, "INVERT_STEP(%d)=%d", iaxis, iValue);
    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //设置正向硬限位输入
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetFwdIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    char cmdbuff[2048];
    char cmdbuffAck[2048];
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "FWD_IN(%d)=%d", iaxis, iValue);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //设置负向硬件限位开关对应的输入点编号，-1无效。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetRevIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    char cmdbuff[2048];
    char cmdbuffAck[2048];
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "Rev_In(%d)=%d", iaxis, iValue);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //设置正向软限位
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetFsLimit(ZMC_HANDLE handle, int iaxis, float fValue)
{

    char cmdbuff[2048];
    char cmdbuffAck[2048];
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "FS_LIMIT(%d)=%f", iaxis, fValue);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //设置负向软限位位置。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetRsLimit(ZMC_HANDLE handle, int iaxis, float fValue)
{

    char cmdbuff[2048];
    char cmdbuffAck[2048];
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "RS_LIMIT(%d)=%f", iaxis, fValue);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/****************设置P参数**********/
int32 __stdcall ZAux_Direct_SetP(ZMC_HANDLE handle, int iaxis, int Value)
{
    char cmdbuffAck[2048];
    QString tmp_str;

    tmp_str = QString("SDO_WRITE(0,%1,$2005,0,3,%2)").arg(iaxis).arg(Value);

    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    return ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
}

/****************读取P参数**********/
int32 __stdcall ZAux_Direct_GetP(ZMC_HANDLE handle, int iaxis, int& Value)
{
    char cmdbuffAck[2048];
    QString tmp_str;

    tmp_str = QString("SDO_READ(0,%1,$2005,0,3,0)").arg(iaxis);

    QByteArray ba = tmp_str.toLatin1();
    char* pchar;
    pchar = ba.data();
    //调用命令执行函数
    ZMC_DirectCommand(handle, pchar, cmdbuffAck, 2048);
    char temp[15];
    strncpy(temp, cmdbuffAck, 15);
    tmp_str = QString(temp);
    qDebug() << tmp_str;
    //Value=cmdbuffAck[1];
    return 0;
}

/*************************************************************
Description:    //设置原点信号
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetDatumIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    char cmdbuff[2048];
    char cmdbuffAck[2048];
    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "DATUM_IN(%d)=%d", iaxis, iValue);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/************吴炼***************/
/*************************************************************
Description:    //回零
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Datum(ZMC_HANDLE handle, int iaxis, int imode)
{

    char cmdbuff[2048];
    char cmdbuffAck[2048];

    if (0 > iaxis || iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "DATUM(%d) AXIS(%d)", imode, iaxis);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

/*************************************************************
Description:    //所有轴立即停止
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Rapidstop(ZMC_HANDLE handle, int imode)
{

    char cmdbuff[2048];

    //生成命令
    sprintf(cmdbuff, "RAPIDSTOP(%d)", imode);

    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
Description:    //读取正向软限位
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetFsLimit(ZMC_HANDLE handle, int iaxis, float* pfValue)
{

    int32 iresult;

    char cmdbuff[2048];
    char cmdbuffAck[2048];

    if (NULL == pfValue || iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "?FS_LIMIT(%d)", iaxis);

    //调用命令执行函数
    //iresult = ZAux_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if (ERR_OK != iresult) {
        return iresult;
    }

    //
    if (0 == strlen(cmdbuffAck)) {
        return ERR_NOACK;
    }

    //
    sscanf(cmdbuffAck, "%f", pfValue);

    return ERR_OK;
}

/*************************************************************
Description:    //读取负向软限位位置。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetRsLimit(ZMC_HANDLE handle, int iaxis, float* pfValue)
{

    int32 iresult;

    char cmdbuff[2048];
    char cmdbuffAck[2048];

    if (NULL == pfValue || iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "?RS_LIMIT(%d)", iaxis);

    //调用命令执行函数
    //iresult = ZAux_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if (ERR_OK != iresult) {
        return iresult;
    }

    //
    if (0 == strlen(cmdbuffAck)) {
        return ERR_NOACK;
    }

    //
    sscanf(cmdbuffAck, "%f", pfValue);

    return ERR_OK;
}

//hcy********************************************************************************************************************************开始
/*************************************************************
Description:    //相对插补 直接调用运动函数 20130901 以后的控制器版本支持
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Move(ZMC_HANDLE handle, int imaxaxises, float* pfDisancelist)
{
    int i;

    char cmdbuff[2048];
    char tempbuff[2048];

    //
    if (0 > imaxaxises || imaxaxises > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    strcpy(cmdbuff, "MOVE(");

    for (i = 0; i < imaxaxises - 1; i++) {
        //
        sprintf(tempbuff, "%f,", pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }

    //
    sprintf(tempbuff, "%f)", pfDisancelist[imaxaxises - 1]);
    strcat(cmdbuff, tempbuff);

    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}

/*************************************************************
Description:    //运动暂停
Input:          //卡链接handle

  0（缺省） 暂停当前运动。
  1 在当前运动完成后正准备执行下一条运动指令时暂停。
  2 在当前运动完成后正准备执行下一条运动指令时，并且两条指令的MARK标识不一样时暂停。这个模式可以用于一个动作由多个指令来实现时，可以在一整个动作完成后暂停。

    Output:         //
    Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MovePause(ZMC_HANDLE handle, int imode)
{

    char cmdbuff[2048];

    //生成命令
    sprintf(cmdbuff, "MOVE_PAUSE(%d)", imode);

    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}
/*************************************************************
Description:    //运动暂停
Input:          //卡链接handle

  0（缺省） 暂停当前运动。
  1 在当前运动完成后正准备执行下一条运动指令时暂停。
  2 在当前运动完成后正准备执行下一条运动指令时，并且两条指令的MARK标识不一样时暂停。这个模式可以用于一个动作由多个指令来实现时，可以在一整个动作完成后暂停。

    Output:         //
    Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MoveResume(ZMC_HANDLE handle)
{

    char cmdbuff[2048];

    //生成命令
    sprintf(cmdbuff, "MOVE_RESUME");

    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}
/*************************************************************
Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MoveAbsSp(ZMC_HANDLE handle, int imaxaxises, float* pfDisancelist)
{
    int i;

    char cmdbuff[2048];
    char tempbuff[2048];

    if (0 > imaxaxises || imaxaxises > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    strcpy(cmdbuff, "MOVEABSSP(");

    for (i = 0; i < imaxaxises - 1; i++) {
        //
        sprintf(tempbuff, "%f,", pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }

    //
    sprintf(tempbuff, "%f)", pfDisancelist[imaxaxises - 1]);
    strcat(cmdbuff, tempbuff);

    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}
/*************************************************************
Description:    //单轴运动
Input:          //卡链接handle  轴号， 距离
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_MoveAbs(ZMC_HANDLE handle, int iaxis, float fdistance)
{

    char cmdbuff[2048];

    if (0 > iaxis || iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "MOVEABS(%f) AXIS(%d)", fdistance, iaxis);

    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}
//hcy********************************************************************************************************************************结束
//hcy********************************************************************************************************************************开始
/*************************************************************
Description:    //读取反馈速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetMspeed(ZMC_HANDLE handle, int iaxis, float* pfValue)
{
    int i;
    float ftemp;
    int32 iresult;

    char cmdbuff[2048];
    char cmdbuffAck[2048];

    if (NULL == pfValue || iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "?MSPEED(%d)", iaxis);

    //调用命令执行函数
    //iresult = ZAux_Execute(handle, cmdbuff, cmdbuffAck,2048);
    iresult = ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    if (ERR_OK != iresult) {
        return iresult;
    }

    //
    if (0 == strlen(cmdbuffAck)) {
        return ERR_NOACK;
    }

    //
    sscanf(cmdbuffAck, "%f", pfValue);

    return ERR_OK;
}
/*************************************************************
Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MoveAbs(ZMC_HANDLE handle, int imaxaxises, float* pfDisancelist)
{
    int i;
    int32 iresult;

    char cmdbuff[2048];
    char tempbuff[2048];

    //
    if (0 > imaxaxises || imaxaxises > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    strcpy(cmdbuff, "MOVEABS(");

    for (i = 0; i < imaxaxises - 1; i++) {
        //
        sprintf(tempbuff, "%f,", pfDisancelist[i]);
        strcat(cmdbuff, tempbuff);
    }

    //
    sprintf(tempbuff, "%f)", pfDisancelist[imaxaxises - 1]);
    strcat(cmdbuff, tempbuff);

    //调用命令执行函数
    //return ZMC_ExecuteNoAck(handle, cmdbuff, g_ZMC_MaxExcuteWaitms);
    return ZMC_DirectCommand(handle, cmdbuff, NULL, 0);
}
/*************************************************************
Description:    //modbus_long
Input:          //
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Modbus_Set4x_Long(ZMC_HANDLE handle, uint16 start, uint16 inum, int32* pidata)
{
    int i, j;
    int32 iresult;
    void* pitemp;
    uint16* pi;
    uint16 tempdata[2048];

    if (NULL == pidata || inum < 0) {
        return ERR_AUX_PARAERR;
    }

    pi = tempdata;
    pitemp = pidata;

    for (i = 1; i < inum + 1; i++) {
        for (j = 0; j < 2; j++) {
            *(pi + j) = *((uint16*)pitemp + j);
        }
        pitemp = pidata + i;
        pi = pi + 2;
    }
    iresult = ZMC_Modbus_Set4x(handle, start, inum * 2, tempdata);
    return iresult;
}
/*************************************************************
Description:    //modbus寄存器操作
Input:          //卡链接handle 寄存器地址
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Modbus_Set0x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint8* pdata)
{
    int32 iresult;
    iresult = ZMC_Modbus_Set0x(handle, start, inum, pdata);

    return iresult;
}
//hcy********************************************************************************************************************************结束
/*************************************************************
Description:    //设置轴告警信号
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetAlmIn(ZMC_HANDLE handle, int iaxis, int iValue)
{
    int i;
    int32 iresult;

    char cmdbuff[2048];
    char cmdbuffAck[2048];

    if (iaxis > MAX_AXIS_AUX) {
        return ERR_AUX_PARAERR;
    }

    //生成命令
    sprintf(cmdbuff, "ALM_IN(%d)=%d", iaxis, iValue);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}
/*************************************************************
Description:    //设置输入口反转
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetInvertIn(ZMC_HANDLE handle, int ionum, int bifInvert)
{
    int i;
    int32 iresult;

    char cmdbuff[2048];
    char cmdbuffAck[2048];

    //生成命令
    sprintf(cmdbuff, "INVERT_IN(%d,%d)", ionum, bifInvert);

    //调用命令执行函数
    return ZMC_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
    //return ZAux_DirectCommand(handle, cmdbuff, cmdbuffAck, 2048);
}

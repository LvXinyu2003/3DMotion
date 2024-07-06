#ifndef ZAUX_H
#define ZAUX_H

#include "zmotion.h"
//#define __stdcall

#define ERR_AUX_OFFSET       30000

#define ERR_NOACK               ERR_AUX_OFFSET      //无应答
#define ERR_ACKERROR            (ERR_AUX_OFFSET+1)  //应答错误
#define ERR_AUX_PARAERR         (ERR_AUX_OFFSET+2)  //参数错误
#define ERR_AUX_NOTSUPPORT      (ERR_AUX_OFFSET+3)  //不支持

#define ERR_AUX_FILE_ERROR      (ERR_AUX_OFFSET+4)  //参数错误
#define ERR_AUX_OS_ERR      (ERR_AUX_OFFSET+5)  //


/*************************************************************
Description:    //读取轴是否运动结束
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetIfIdle(ZMC_HANDLE handle, int iaxis, int *piValue);
/*************************************************************
Description:    //设置 脉冲当量
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetUnits(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //设置轴速度，单位为units/s，当多轴运动时，作为插补运动的速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetSpeed(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //设置加速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetAccel(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //设置减速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetDecel(ZMC_HANDLE handle, int iaxis, float fValue);
/*************************************************************
Description:    //设置轴起始速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetLspeed(ZMC_HANDLE handle, int iaxis, float fValue);
/*************************************************************
Description:    //设置 S曲线设置。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetSramp(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //单轴运动
Input:          //卡链接handle  轴号， 距离
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Move(ZMC_HANDLE handle, int iaxis, float fdistance);

/*************************************************************
Description:    //连续运动
Input:          //卡链接handle  轴号， 方向
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Vmove(ZMC_HANDLE handle, int iaxis, int idir);
/*************************************************************
Description:    //单轴运动停止
Input:          //卡链接handle  轴号， 模式
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Cancel(ZMC_HANDLE handle, int iaxis, int imode);

/*************************************************************
Description:    //设置轴位置
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetDpos(ZMC_HANDLE handle, int iaxis, float fValue);
/*************************************************************
Description:    //读取轴位置
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetDpos(ZMC_HANDLE handle, int iaxis, float *pfValue);
/*************************************************************
Description:    //参数
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetVpSpeed(ZMC_HANDLE handle, int iaxis, float *pfValue);
//////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************
Description:    //设置轴类型
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetAtype(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //设置脉冲输出模式
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetInvertStep(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //设置正向硬限位输入
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetFwdIn(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //设置负向硬件限位开关对应的输入点编号，-1无效。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetRevIn(ZMC_HANDLE handle, int iaxis, int iValue);

/*************************************************************
Description:    //设置正向软限位
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetFsLimit(ZMC_HANDLE handle, int iaxis, float fValue);

/*************************************************************
Description:    //设置负向软限位位置。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetRsLimit(ZMC_HANDLE handle, int iaxis, float fValue);

/****************设置P参数**********/
int32 __stdcall ZAux_Direct_SetP(ZMC_HANDLE handle, int iaxis, int Value);
/****************读取P参数**********/
int32 __stdcall ZAux_Direct_GetP(ZMC_HANDLE handle, int iaxis, int& Value);

/*************************************************************
Description:    //设置原点信号
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetDatumIn(ZMC_HANDLE handle, int iaxis, int iValue);


/************吴炼***************/
/*************************************************************
Description:    //回零
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_Datum(ZMC_HANDLE handle, int iaxis, int imode);



/*************************************************************
Description:    //所有轴立即停止
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Rapidstop(ZMC_HANDLE handle, int imode);

/*************************************************************
Description:    //读取正向软限位
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetFsLimit(ZMC_HANDLE handle, int iaxis, float *pfValue);


/*************************************************************
Description:    //读取负向软限位位置。
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetRsLimit(ZMC_HANDLE handle, int iaxis, float *pfValue);


//hcy********************************************************************************************************************************开始
/*************************************************************
Description:    //相对插补 直接调用运动函数 20130901 以后的控制器版本支持
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Move(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist);

/*************************************************************
Description:    //运动暂停
Input:          //卡链接handle

  0（缺省） 暂停当前运动。
  1 在当前运动完成后正准备执行下一条运动指令时暂停。
  2 在当前运动完成后正准备执行下一条运动指令时，并且两条指令的MARK标识不一样时暂停。这个模式可以用于一个动作由多个指令来实现时，可以在一整个动作完成后暂停。

    Output:         //
    Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MovePause(ZMC_HANDLE handle, int imode);
/*************************************************************
Description:    //运动暂停
Input:          //卡链接handle

  0（缺省） 暂停当前运动。
  1 在当前运动完成后正准备执行下一条运动指令时暂停。
  2 在当前运动完成后正准备执行下一条运动指令时，并且两条指令的MARK标识不一样时暂停。这个模式可以用于一个动作由多个指令来实现时，可以在一整个动作完成后暂停。

    Output:         //
    Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MoveResume(ZMC_HANDLE handle);
/*************************************************************
Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MoveAbsSp(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist);
/*************************************************************
Description:    //单轴运动
Input:          //卡链接handle  轴号， 距离
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_Singl_MoveAbs(ZMC_HANDLE handle, int iaxis, float fdistance);
//hcy********************************************************************************************************************************结束

//hcy********************************************************************************************************************************开始
/*************************************************************
Description:    //读取反馈速度
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_GetMspeed(ZMC_HANDLE handle, int iaxis, float *pfValue);
/*************************************************************
Description:    //插补 直接调用运动函数 20130901 以后的控制器版本支持
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_MoveAbs(ZMC_HANDLE handle, int imaxaxises, float *pfDisancelist);
/*************************************************************
Description:    //modbus_long
Input:          //
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Modbus_Set4x_Long(ZMC_HANDLE handle, uint16 start, uint16 inum, int32 * pidata);
/*************************************************************
Description:    //modbus寄存器操作
Input:          //卡链接handle 寄存器地址
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Modbus_Set0x(ZMC_HANDLE handle, uint16 start, uint16 inum, uint8* pdata);
//hcy********************************************************************************************************************************结束
/*************************************************************
Description:    //设置轴告警信号
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetAlmIn(ZMC_HANDLE handle, int iaxis, int iValue);
/*************************************************************
Description:    //设置输入口反转
Input:          //卡链接handle
Output:         //
Return:         //错误码
*************************************************************/
int32 __stdcall ZAux_Direct_SetInvertIn(ZMC_HANDLE handle, int ionum, int bifInvert);
#endif // ZAUX_H


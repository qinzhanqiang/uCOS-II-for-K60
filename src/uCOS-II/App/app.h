/******************** (C) COPYRIGHT 2011 武汉理工大学秦战强 ********************
 * 文件名       ：app.c
 * 描述         ：uC/OS的用户任务函数头文件
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：武汉理工大学秦战强
**********************************************************************************/

#ifndef _APP_H_
#define _APP_H_

/**************** 用户任务声明 *******************/
void Task_LED(void *p_arg);
void Task_Start(void *p_arg);




#endif    //_APP_H_

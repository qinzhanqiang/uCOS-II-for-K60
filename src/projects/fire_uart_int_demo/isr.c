/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名       ：isr.c
 * 描述         ：中断处理例程
 *
 * 实验平台     ：野火kinetis开发板
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：野火嵌入式开发工作室
 * 淘宝店       ：http://firestm32.taobao.com
 * 技术支持论坛 ：http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/



#include "common.h"
#include "include.h"



/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：USART1_IRQHandler
*  功能说明：串口1 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*  备    注：
*************************************************************************/
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //关总中断

    //接收一个字节数据并回发
    ch = uart_getchar (UART1);              //接收到一个数据
    printf("\n你发送的数据为：%c", ch);     //发送出去


    EnableInterrupts;		    //开总中断
}




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
    ch = uart_getchar (UART1);      //接收到一个数据
    uart_sendStr  (UART1, "\n你发送的数据为：");
    uart_putchar (UART1, ch);       //就发送出去

    EnableInterrupts;		    //开总中断
}

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：PIT0_IRQHandler
*  功能说明：PIT0 定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：
*************************************************************************/
#if 1
void PIT0_IRQHandler(void)
{
    LED_turn(LED1);             //LED1反转
    PIT_Flag_Clear(PIT0);       //清中断标志位
}
#else
extern u32 test_time;
void PIT0_IRQHandler(void)
{
    test_time++;
    PIT_Flag_Clear(PIT0);       //清中断标志位
}
#endif


/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：SysTick_Handler
*  功能说明：系统滴答定时器中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：ucos里用得到
*************************************************************************/
void SysTick_Handler(void)
{
        OSIntEnter();                                   //进入中断服务程序，记录中断嵌套层数
        
        OSTimeTick();                                   //调用节拍处理函数
        
        OSIntExit();                                    //退出中断服务程序，中断嵌套层数减一
}


/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-4    已测试
*  备    注：可以用LED闪烁来指示发生了硬件上访
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****硬件上访错误!!!*****\r\n\n");
    }
}

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：PendSV_Handler
*  功能说明：PendSV（可悬起系统调用）中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-15    已测试
*  备    注：uC/OS用来切换任务
*************************************************************************/
void PendSV_Handler(void)
{
}


/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：PORTA_IRQHandler
*  功能说明：PORTA端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要自己初始化来清除
*************************************************************************/
void PORTA_IRQHandler()
{
    u8  n = 0;    //引脚号

    n = 0;
    if(PORTA_ISFR & (1 << n))         //PTA0触发中断
    {
        PORTA_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */

    }

    n = 26;
    if(PORTA_ISFR & (1 << n))         //PTA16触发中断
    {
        PORTA_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */
        LED_turn(LED1);                 //LED1反转
    }
}

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：PORTB_IRQHandler
*  功能说明：PORTB端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/
void PORTB_IRQHandler()
{
    u8  n = 0;    //引脚号

    n = 0;
    if(PORTB_ISFR & (1 << n))         //PTB0触发中断
    {
        PORTB_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */
        LED_turn(LED1);                 //LED1反转
    }

    n = 10;
    if(PORTB_ISFR & (1 << n))         //PTB10触发中断
    {
        PORTB_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */

    }
}

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：FTM0_IRQHandler
*  功能说明：FTM0输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM0_IRQHandler()
{


}

/*************************************************************************
*                             野火嵌入式开发工作室
*
*  函数名称：FTM1_IRQHandler
*  功能说明：FTM1输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM1_IRQHandler()
{
    u8 s = FTM1_STATUS;             //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
    u8 n;
    FTM1_STATUS = 0x00;               //清中断标志位

    n = 0;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */
        LED_turn(LED1);                             //翻转LED1
        printf("\nFTM1发送中断\n");

        /*********************/
        //不建议在这里开启输入捕捉中断，而是在main函数里根据需要来开启
        //通道 CH0、CH1、Ch2、Ch3 有滤波器
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
        //delayms(10);        //因为输入的信号跳变过程不稳定，容易触发多次输入捕捉，所以添加延时
        //但考虑到中断不应该过长延时，所以开输入捕捉中断就放在main函数里，根据需要来开启
    }

    n = 1;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
    }

}




/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.c
 * ����         ���жϴ�������
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/



#include "common.h"
#include "include.h"

volatile u8  pit_flag = 0;
volatile u32 dma_int_count = 0;


/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�DMA_CH4_Handler
*  ����˵����DMAͨ��4���жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-3-18    �Ѳ���
*  ��    ע��
*************************************************************************/
void DMA_CH4_Handler(void)
{
    //DMAͨ��4
    DMA_IRQ_CLEAN(DMA_CH4);                             //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
    DMA_EN(DMA_CH4);                                    //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����)

    dma_int_count++;
}

void PIT0_IRQHandler()
{
    printf("PIT0_IRQHandler\n");
    pit_flag = 1;               //��ǽ���PIT�ж�
    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
    PIT_MCR = 0;  // add for correcting PIT bug
}

void DMA_CH0_Handler(void)
{

    //DMAͨ��0
    printf("DMA_CH0_Handler\n");
    DMA_IRQ_CLEAN(DMA_CH0);                             //���ͨ�������жϱ�־λ    (���������ٴν����ж�)
    DMA_EN(DMA_CH0);                                    //ʹ��ͨ��CHn Ӳ������      (�������ܼ�������DMA����)

}

extern u8 BUFF[];
void PIT1_IRQHandler()
{
    u8 i;
    printf("PIT1_IRQHandler\n");
    printf("\nBUFF[10]={");
    for(i = 0; i < 9; i++)
        printf("%d,", BUFF[i]);
    printf("%d}\n", BUFF[10]);
    //printf("\n")

    PIT_Flag_Clear(PIT1);       //���жϱ�־λ
    PIT_MCR = 0;  // add for correcting PIT bug
}
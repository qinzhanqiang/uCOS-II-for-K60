/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��main.c
 * ����         ��DMA����ʵ��
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

#if 0

u8 BUFF[11];

/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*                             DMA����GPIO����ʵ��
*
*  ʵ��˵����DMA����GPIO����ʵ�飬���ô���������������� PTA26 �������岨��
*            ���̽�PTA26��PTA27����PTA27��ȡ�������أ��Ӷ�����DMA���䡣
*
*  ʵ��������̽�PTA26��PTA27 ���ڴ�����������㷢��һ���ַ��Ϳ���ʹPTA26����
*            ���岨���ϵ������ڵ���uart_getchar ���� DELAY_MS ���������
*            BUFF ����watch������ÿ�δ�������watch����Կ��� BUFF ������Ԫ
*            �ص�ֵ�ı��ˡ�
*
*  ʵ��Ч����ÿ�δ��ڽ��յ�һ���ֽڣ��ͻᴥ��DMA�жϣ��Ӷ��������ݵ� BUFF����
*            ���DEBUG�����watch���ڣ����Կ���BUFF�����Ԫ�ط��ͱ仯��
*
*  ʵ��Ŀ�ģ�ѧ��ʹ�� DMA_PORTx2BUFF_Init �������ﵽ DMA ����Ŀ��
*
*  �޸�ʱ�䣺2012-3-24     �Ѳ���
*
*  ��    ע����������ܽţ���Ϊ DMA_PORTx2BUFF_Init ����ԴIO�ܽ��ڲ�������
*            ����ֻ���ȡ�� 0
*************************************************************************/
void  main(void)
{
    char command;

    gpio_init  (PORTA, 26, GPO, LOW);         //��ʼ�� PTA26 Ϊ����͵�ƽ

    DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN, BUFF, PTA27, DMA_BYTE1, 3, DMA_rising);
    //DMAͨ��4��ʼ����PTA27�����ش���DMA���䣬Դ��ַΪPTD_BYTE0_IN��Ŀ�ĵ�ַΪ��BUFF ��ÿ�δ���1Byte������3�κ�ֹͣ���䣬�ָ�Ŀ�ĵ�ַ

    while(1)
    {
        command = uart_getchar(FIRE_PORT);  //ͨ������������PTA26���������PTA27������
                                            //�Ӷ����ƴ���DMA����

        if(command)                         //���յ����ݾͷ�תPTA26���Σ�����һ�����岨��DMA�ʹ���һ��
        {
            PTA26_OUT = ~PTA26_OUT;         //ȡ��
            PTA26_OUT = ~PTA26_OUT;         //ȡ��
        }

        DELAY_MS(50);                       //��ʱһ�£��ⲽ�����ɾ��
    }
}


#elif  0

void  main(void)
{
    char command;

    gpio_init  (PORTA, 26, GPO, LOW);         //��ʼ�� PTA26 Ϊ����͵�ƽ

    DMA_count_Init(DMA_CH4, PTA27 , 0x4, DMA_rising);

    while(1)
    {
        command = uart_getchar(FIRE_PORT);  //ͨ������������PTA26���������PTA27������
                                            //�Ӷ����ƴ���DMA����

        if(command)                         //���յ����ݾͷ�תPTA26���Σ�����һ�����岨��DMA�ʹ���һ��
        {
            PTA26_OUT = ~PTA26_OUT;         //ȡ��
            PTA26_OUT = ~PTA26_OUT;         //ȡ��
        }
        /*      //
                if(DMA_count_get(DMA_CH4)==2)
                {
                    DMA_count_reset(DMA_CH4);
                }
        */
        DELAY_MS(50);                       //��ʱһ�£��ⲽ�����ɾ��
    }
}

#else
extern volatile u8  pit_flag ;
extern volatile u32 dma_int_count;
#define INT_COUNT  100
void main()
{
    u16 count;

    DisableInterrupts;                                                              //��ֹ���ж�

    FTM_PWM_init(FTM1, CH0, 30000, 50);                                               //FTMģ�����PWM���� FTM1_CH0 ���� PTA8 ��Ƶ��Ϊ 200

    //lptmr_counter_init(LPT0_ALT2,INT_COUNT,2,LPT_Rising);                         //��ʼ���������������LPT0_ALT2����PTC5���룬ÿ��INT_COUNT�����жϣ���ʱ2��ʱ���˲��������ش���
    DMA_count_Init(DMA_CH4, PTC5 , 0x7FFF, DMA_rising);

    pit_init_ms(PIT0, 1000);                                                        //��ʱ 1�� �ж�

    EnableInterrupts;                                                               //�����ж�

    while(1)
    {
        if( pit_flag > 0 )                                                          /*   1 ���ж���  */
        {
            //count=LPTMR0_CNR;                                                       //�����������������ֵ
            //lptmr_counter_clean();                                                  //����������������ֵ��������գ��������ܱ�֤����ֵ׼ȷ��
            count = DMA_count_get(DMA_CH4);
            DMA_count_reset(DMA_CH4);
            //printf("1����LPT��ȡ����:%d��\n",LPT_INT_count*INT_COUNT +  count);     //��ȡ���1����������
            printf("1����LPT��ȡ����:%d��\n", count);     //��ȡ���1����������
            //LPT_INT_count=0;                                                        //���LPT�жϴ���
            dma_int_count = 0;
            pit_flag = 0;                                                           //���pit�жϱ�־λ
        }
    }
}


#endif
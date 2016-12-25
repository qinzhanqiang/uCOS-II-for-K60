/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��main.c
 * ����         ��DSP����ʵ��
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

#include "arm_math.h"



/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*                            CMSIS��cos��sin����ʵ��
*
*  ʵ��˵����Ұ��CMSIS��cos��sin����ʵ��
*
*  ʵ���������
*
*  ʵ��Ч�������Գɹ�����LED��ˮ��
*
*  ʵ��Ŀ�ģ���ϤCMSIS�⺯���ĵ���
*
*  �޸�ʱ�䣺2012-3-26     �Ѳ���
*
*  ��    ע��
*************************************************************************/
#define DELTA           (0.000001f)             //����������

float32_t a = 0.45454;                          //����������
float32_t cosa, sina, cos2a, sin2a;             //a ������ֵ������ֵ������ֵƽ��������ֵƽ����
float32_t test;                                 //���Խ��


void main(void)
{
    //float32_t b=1,c=2,d;
    q7_t b = 2, c = 2, d;
    float32_t diff;                             //��ֵ

    //arm_mult_f32(&b,&c,&d,1);
    arm_mult_q7(&b, &c, &d, 1);

    LED_init();                                 //��ʼ��LED

    cosa = arm_cos_f32(a);                      //��cosֵ��cosa = cos(a);
    sina = arm_sin_f32(a);                      //��sinֵ��sina = sin(a);

    arm_mult_f32(&cosa, &cosa, &cos2a, 1);      //�˷���cos2a = cosa * cosa ����ƽ��
    arm_mult_f32(&sina, &sina, &sin2a, 1);      //�˷���sin2a = sina * sina ����ƽ��

    arm_add_f32(&cos2a, &sin2a, &test, 1);      //�ӷ���test = cos2a + sin2a = cosa * cosa  + sina * sina = 1

    diff = fabsf( 1.000000000 - test);          //�����ֵ

    if( diff <= DELTA)                          //������Խ���ھ��ȷ�Χ֮��
    {
        while(1)
        {
            water_lights();                     //��ˮ�Ʊ�ʾ�ɹ�
        }
    }
}


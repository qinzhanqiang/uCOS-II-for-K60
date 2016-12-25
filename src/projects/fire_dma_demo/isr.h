/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��isr.h
 * ����         �����º궨���жϺţ���ӳ���ж�����������жϺ�����ַ��
 *                ʹ��ָ��������������жϷ������������жϷ�����
 *                ���棺ֻ����"vectors.c"���������ұ�����"vectors.h"�����ĺ��棡����
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/



#ifndef __ISR_H
#define __ISR_H 1

#include  "include.h"

/*                          ���¶����ж�������
 *  ��ȡ��Ĭ�ϵ��ж�����Ԫ�غ궨��       #undef  VECTOR_xxx
 *  �����¶��嵽�Լ���д���жϺ���       #define VECTOR_xxx    xxx_IRQHandler
 *  ���磺
 *       #undef  VECTOR_003
 *       #define VECTOR_003    HardFault_Handler    ���¶���Ӳ���Ϸ��жϷ�����
 *
 *       extren void  HardFault_Handler(void);      ����������Ȼ����isr.c�ﶨ��
 */

#undef  VECTOR_016
#define VECTOR_016    DMA_CH0_Handler

#undef  VECTOR_020
#define VECTOR_020    DMA_CH4_Handler

#undef  VECTOR_084
#define VECTOR_084    PIT0_IRQHandler     //���¶���84���ж�ΪPIT0_IRQHandler�ж�

#undef  VECTOR_085
#define VECTOR_085    PIT1_IRQHandler     //���¶���84���ж�ΪPIT0_IRQHandler�ж�

extern void DMA_CH0_Handler(void);
extern void DMA_CH4_Handler(void);              //DMAͨ��4���жϷ�����
extern void PIT0_IRQHandler();            //PIT0 ��ʱ�жϷ�����
extern void PIT1_IRQHandler();            //PIT0 ��ʱ�жϷ�����

#endif  //__ISR_H

/* End of "isr.h" */

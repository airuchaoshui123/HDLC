/*********************************************
@ author : Bai Jiaqi �׼��� 
@ ID : 161720328
@ class: 1617203
@ date : 2020/5/11
@ instructor :Teacher Ye Haibo Ҷ������ʦ 
**********************************************/

#ifndef _INITFIELD_H
#define _INITFIELD_H

#include "frame.h"
 

//#define I 0				//�����ֶ���Ϣ֡��� 
//#define S 2				//�����ֶμ��֡��� 
//#define U 3				//�����ֶ��ޱ��֡��� 

//bool IF_INFO_EXIST = 1;			//ȫ�ֱ��� ����֡�����и�֪�Ƿ���ڼ��֡

int init_control_fld(char *Control,char control_type); 			//�����ֶ����� ���ؿ����ֶ�֡���ͱ�� 
int init_info_fld(char *Info, int info_type,char *Info_temp);	//���ݿ����ֶ�֡���ͱ�� ��������ֶ� ���������ֶγ��� 

#endif

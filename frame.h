/*********************************************
@ author : Bai Jiaqi �׼��� 
@ ID : 161720328
@ class: 1617203
@ date :2020/5/11
@ instructor :Teacher Ye Haibo Ҷ������ʦ 
**********************************************/
#ifndef _FRAME_H
#define _FRAME_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//#define I 0				//�����ֶ���Ϣ֡��� 
//#define S 2				//�����ֶμ��֡��� 
//#define U 3				//�����ֶ��ޱ��֡��� 

//bool IF_INFO_EXIST = 1;			//ȫ�ֱ��� ����֡�����и�֪�Ƿ���ڼ��֡

#define BYTE 8								//1�ֽ� 
#define MAX_FRAME 12000 					//������·�����֡��Ϊ1500 byte �� 12000bit 
#define MAX_INFO  11952						/*���֡�� 1500 byte - ֡ͷ֡β 2 byte - ��ַ�ֶ� 1 byte - �����ֶ� 1 byte - FCS�ֶ� 2 byte = 1494 byte 
												�� 11952bit */
												
// �˴�������Ϊ��֡�����ڲ����ú���********************************************************************************												
int _2_x(int x);										//2��x�η�
void char_to_bit(char letter, char *bit);				//��������ĸת��Ϊ���ش�
int info_to_bit(char *Info, int Info_len, char *Info_temp);			//����������ת��Ϊ���ش� 
void print_info_bit(char *Info,int Info_len);						//��ӡ���ݱ��ش�												
void flag_fld_header(char *frame);						//��ʼ����֡֡ͷ 
void addr_fld(char *frame, char *Address);				//��ʼ����֡��ַ�ֶ� 												
void control_fld(char *frame, char *Control);			//��ʼ����֡�����ֶ�
//int bit_stf(char *Info, int Info_len);					//�����ֶ��ֽ�����
int info_fld(char *frame, char *Info, int Info_len);	//��ʼ����֡�����ֶ� 
int fcs_fld(char *frame,char *FCS,int frame_length);	//��ʼ����֡FCS�ֶ�
int bit_stf(char *frame, int frame_length);				//0bit����
int flag_fld_end(char *frame, int frame_length);		//��ʼ����֡֡β 
void print_frame(char *frame, int frame_length);		//��ӡ��֡

void Frameing(char *Address, char *Control, char *Info, int Info_len, char *FCS, char *frame);		//��֡����
// ******************************************************************************************************************
/*
int init_control_fld(char *Control,char control_type); 			//�����ֶ����� ���ؿ����ֶ�֡���ͱ�� 
int init_info_fld(char *Info, int info_type,char *Info_temp);	//���ݿ����ֶ�֡���ͱ�� ��������ֶ� ���������ֶγ��� 
*/				
#endif

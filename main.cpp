/*********************************************
@ author : Bai Jiaqi �׼��� 
@ ID : 161720328
@ class: 1617203
@ date : 2020/5/11
@ instructor :Teacher Ye Haibo Ҷ������ʦ 
**********************************************/

#include "frame.h"
#include "initfield.h"

										
char Address[BYTE+1];						//��ַ�ֶ�A
char Control[BYTE+1];						//�����ֶ�C(ֻ���ǵ��ֽ�)
char Info[MAX_INFO];				
		//�����ֶ�S 
char Info_temp[MAX_INFO];					//ת���ɱ��ش��������ֶθ������� 
int Info_len;								//�����ֶγ��� 
char FCS[BYTE * 2 + 1];						//֡У�������ֶ�FCS 
char frame[MAX_FRAME];						//�洢������֡

int main(){
	char control_type;
	printf("����ҪHDLC֡����(I or S or U):\n");
	scanf("%c",&control_type);
	int info_type = init_control_fld(Control,control_type);
	Info_len = init_info_fld(Info,info_type,Info_temp);
	printf("Ҫ����ĵ�ַ(8bit):\n");
	scanf("%s",Address);
//	printf("�����ֶ�(8bit):\n");
//	scanf("%s",Control);
	printf("FCS�ֶ�(16bit):\n");
	scanf("%s",FCS);
	Frameing(Address,Control,Info,Info_len,FCS,frame);
	return 0;
}
 

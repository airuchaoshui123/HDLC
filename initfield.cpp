/*********************************************
@ author : Bai Jiaqi �׼��� 
@ ID : 161720328
@ class: 1617203
@ date : 2020/5/11
@ instructor :Teacher Ye Haibo Ҷ������ʦ 
**********************************************/
#include "initfield.h"
 
int init_control_fld(char *Control,char control_type){						//�����ֶ����� ���ؿ����ֶ�֡���ͱ�� 
	switch(control_type){
		case 'I':			//��Ϣ֡ 
		case 'i':
			Control[0] = '0';
			//Ĭ��N(s) = 1, N(r) = 1, P/F bit = 1 
				Control[1] = '0';	//N(s) = Control[1,2,3] 
				Control[2] = '0';
				Control[3] = '1';
				
				Control[4] = '1'; 	//P/F bit = Control[4]
				
				Control[5] = '0';	//N(r) = Control[5,6,7] 
				Control[6] = '0';
				Control[7] = '1';	
			return 0;		//��Ϣ֡���Ϊ0 
		case 'S':			//���֡ 
		case 's':
			Control[0] = '1';
			Control[1] = '0';
			//Ĭ�� bit2 bit3 Ϊ 00(RR), P/F bit = 1, N(r) = 1
				Control[2] = '0';
				Control[3] = '0';
					
				Control[4] = '1'; 	//P/F bit = Control[4]
				
				Control[5] = '0';	//N(r) = Control[5,6,7] 
				Control[6] = '0';
				Control[7] = '1';	
			 return 2;		//���֡���Ϊ2 
		case 'U':			//�ޱ��֡ 
		case 'u':
			Control[0] = '1';
			Control[1] = '1';
			//Ĭ����������ӦģʽSNRM(M1 = 00, M2 = 001), P/F bit = 1
				Control[2] = '0';	//M1
				Control[3] = '0';
					
				Control[4] = '1'; 	//P/F bit = Control[4]
				
				Control[5] = '0';	//M2
				Control[6] = '0';
				Control[7] = '1';
			return 3;		//�ޱ��֡���Ϊ3 
		default:
			printf("HDLC֡������������!\n");
			exit(0);
	}
}

int init_info_fld(char *Info, int info_type, char *Info_temp){								//���ݿ����ֶ�֡���ͱ�� ��������ֶ�
	int info_len;
	switch(info_type){
		case 0:			//��Ϣ֡ д����Ϣ��ת��Ϊ���ش� 
			printf("Ҫ���������:\n");
			scanf("%s",Info);
			info_len = strlen(Info);
			printf("ת��Ϊ���ش�:\n");
			info_len = info_to_bit(Info,info_len,Info_temp);
			print_info_bit(Info,info_len);
			return info_len;
		case 2:			//���֡ ��Ϣ�ֶβ�����
			Info[0] = '#';			//#��ʾ�����ֶβ����� 
//			IF_INFO_EXIST = 0;		//ȫ�ֱ��� ����֡�����и�֪�Ƿ���ڼ��֡
			return 0;
		case 3:			//�ޱ��֡ Ĭ����Ϣ�ֶ�ȫΪ0 
			for(int i = 0; i < BYTE; i++){
				Info[i] = '0';
			}
			info_len = BYTE;
			return info_len;
	}
}	

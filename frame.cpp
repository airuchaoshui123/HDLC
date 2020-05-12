/*********************************************
@ author : Bai Jiaqi �׼��� 
@ ID : 161720328
@ class: 1617203
@ date : 2020/5/11
@ instructor :Teacher Ye Haibo Ҷ������ʦ 
**********************************************/
#include "frame.h"

int _2_x(int x){		//2��x�η�
	int num = 1;
	for(int i = 0; i < x; i++){
		num *= 2;
	}
	return num;
}


void char_to_bit(char letter, char *bit){		//��������ĸת��Ϊ���ش�	
	char temp = letter;
	for(int i = 0; i < 8; i++)
	{
		if(temp / _2_x(7 - i) != 0){
			bit[i] = '1';
			temp = temp - _2_x(7 - i);
		}
		else
			bit[i] = '0';
	}
}

int info_to_bit(char *Info, int Info_len, char *Info_temp){		//����������ת��Ϊ���ش� 
	char bit[8];
	for(int i = 0; i < Info_len; i++){
		char_to_bit(Info[i],bit);
		for(int j = 0; j < 8; j++){
			Info_temp[i*8+j] = bit[j];			
		}
	}
	strcpy(Info,Info_temp);
	return strlen(Info);
}

void print_info_bit(char *Info,int Info_len){			//��ӡ���ݱ��ش�
	for(int i = 0; i < Info_len; i++){
		printf("%c",Info[i]);
	}
	printf("\n");
}

void flag_fld_header(char *frame){						//��ʼ����֡֡ͷ 
	frame[0] = '0';
	for(int i = 1; i < 7; i++){
		frame[i] = '1';
	}
	frame[7] = '0';
}

void addr_fld(char *frame, char *Address){				//��ʼ����֡��ַ�ֶ� 
	int j = 0;
	for(int i = 8; i <= 15; i++){
		frame[i] = Address[j++];
	}
}

void control_fld(char *frame, char *Control){			//��ʼ����֡�����ֶ� 
	int j = 0;
	for(int i = 16; i <= 23; i++){
		frame[i] = Control[j++];
	}
}


int info_fld(char *frame, char *Info, int Info_len){	//��ʼ����֡�����ֶ� 
	int frame_length = 24 + Info_len;
	int j = 0;
	for(int i = 24; i < 24 + Info_len; i++){
		frame[i] = Info[j++];
	}
	return frame_length;
}

int fcs_fld(char *frame,char *FCS,int frame_length){	//��ʼ����֡FCS�ֶ� 
	int j = 0;
	for(int i = frame_length; i < frame_length + 16; i++){
		frame[i] = FCS[j++];
	}
	frame_length = frame_length + 16;
	return frame_length;
}

int bit_stf(char *frame, int frame_length){					//0bit���� 
	int cnt_1 = 0;
	for(int i = 8; i < frame_length; i++){
		if(frame[i] == '1') cnt_1++;
		else cnt_1 = 0;
		if(cnt_1 == 5){
			int temp1 = frame[i+1];
			frame[i+1] = '0';
			frame_length++;
			int temp2;
			for(int j = i + 2; j < frame_length; j++){
				temp2 = frame[j];
				frame[j] = temp1;
				temp1 = temp2;
			}
		}
	}
	return frame_length;
}

int flag_fld_end(char *frame, int frame_length){		//��ʼ����֡֡β 
	frame[frame_length] = '0';
	for(int i = frame_length + 1; i < frame_length + 7; i++){
		frame[i] = '1';
	}
	frame_length = frame_length + 7;
	frame[frame_length++] = '0';
	return frame_length;
}

void print_frame(char *frame, int frame_length){		//��ӡ��֡ 
	printf("��֡: \n");
	for(int i = 0; i < frame_length; i++){
		printf("%c",frame[i]);
	}
	printf("\n֡��: %d(bit)\n",frame_length);
}

void Frameing(char *Address, char *Control, char *Info, int Info_len, char *FCS, char *frame){		//��֡���� 
//            address,		 control,	  	information,infobytelength, FCS,		Frame
	int frame_length;							//��֡���� 
//Flag field 
	flag_fld_header(frame);
//Address field 
	addr_fld(frame,Address);		
//Control field
	control_fld(frame,Control);
//Information field
	frame_length = info_fld(frame,Info,Info_len);
//FCS filed
	frame_length = fcs_fld(frame,FCS,frame_length);
//Bit stuffing
	frame_length = bit_stf(frame,frame_length);
//Flag field
	frame_length = flag_fld_end(frame,frame_length);
//Print Frame
	print_frame(frame,frame_length);
}

/*
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
	*/

/*********************************************
@ author : Bai Jiaqi �׼��� 
@ ID : 161720328
@ class: 1617203
@ date : 2020/5/11
@ instructor :Teacher Ye Haibo Ҷ������ʦ 
**********************************************/

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
												�� 11952bit */					/*���֡�� 1500 byte - ֡ͷ֡β 2 byte - ��ַ�ֶ� 1 byte - �����ֶ� 1 byte - FCS�ֶ� 2 byte = 1494 byte 
												�� 11952bit */
												
// frame.h�˴�������Ϊ��֡�����ڲ����ú���********************************************************************************												
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

// initfield.h**********************************************************************************
int init_control_fld(char *Control,char control_type); 			//�����ֶ����� ���ؿ����ֶ�֡���ͱ�� 
int init_info_fld(char *Info, int info_type,char *Info_temp);	//���ݿ����ֶ�֡���ͱ�� ��������ֶ� ���������ֶγ��� 
void init_fcs_fld(char *Info, char *FCS,int info_type);			//������������CRCУ���� 
void bin_div(char *inStr,char *outStr);
void checkCRC(char *inStr, char *outStr);
//***********************************************************************************************


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

void init_fcs_fld(char *Info,char *FCS,int info_type){			//��ʼ��FCS�ֶ� 
	switch(info_type){
		case 2:			//��Ϊ���֡ FCS�ֶ���Ϊȫ0
			for(int i = 0; i < 2*BYTE; i++){
				FCS[i] = '0';
			}
			printf("CRCУ����:\n");
			for(int i = 0; i < 2*BYTE; i++){
				printf("%c",FCS[i]);
			}
			printf("\n");
			break;
		case 0:			//��Ϊ����֡���ޱ��֡��������CRC����У���� 
		case 3:
			checkCRC(Info,FCS);
			printf("CRCУ����:\n");
			for(int i = 0; i < 2*BYTE; i++){
				printf("%c",FCS[i]);
			}
			printf("\n");
			break; 
			
	}
}

void bin_div(char *inStr,char *outStr){
	int ii = 0;
	int flag = 0;
	int ff = 0;
	int len = 0;
	int maxlen = MAX_INFO;
	int div_n = 0;
	int n = 16;						//����ʽ���� 
	char p[]="10001000000100001";	//��ʽ��CRC�еĶ���ʽ�� 
	char temp[maxlen];
	char temp2[maxlen];
	for(int i = 0; (inStr[i] == '0' || inStr[i] == '1') && i < maxlen; i++, len++){
		temp[i]=inStr[i];	
	}
	ii=0;
	for(int i = 0; i < len; i++){
		if(temp[i] == '1'){		//�������ĵ�һ��1
			div_n = i;
			break;
		}
	}
	ii=0;
	ff=0;
	if(len-div_n>=16){	//����������ĵ�һ��1�������������һλ֮��ĳ��ȴ��ڵ���16��ʵ����ѧ�����Ǳ��������ڳ�����
		//�ӱ������ĵ�һ��1��ʼ��11000000 00000011 ���������õ�����������ʱ����temp[]��
		for(int i = div_n; i < len; i++){
			if(i < div_n + 16){
				if(temp[i] != p[i-div_n]) temp2[i-div_n] = '1';
				else temp2[i-div_n] = '0';
			}
			else temp2[i-div_n] = temp[i];
		} 
		
	}
	else{//�������ĵ�һ��1�������������һλ֮��ĳ���С�ڵ���16��ʵ����ѧ���屻�����ȳ���С��ֱ����Ϊ������
		for(int i = 0; i < 16; i++){
			temp2[i] = temp[len-16+i];
		}
	}
	//ɾ����ǰ׺
	for(int i = 0; i < len && (temp2[i] == '1' || temp2[i] == '0'); i++){
		if(ff == 0 && temp2[i] == '1') ff=1;		
		if(ff==1){
			outStr[ii] = temp2[i];
			ii++;
		}
	}		
}

void checkCRC(char *inStr, char *outStr){
	int i;
	int maxlen = MAX_INFO;
	int len;
	char temp[MAX_INFO];
	char tempRx[MAX_INFO];

	for(i = 0; (inStr[i] == '0' || inStr[i] == '1') && i < maxlen ; i++){		//Ϊf(x)�����15��0��ʱ�����temp[]
		temp[i]=inStr[i];		
	}
	len = i;
	for(i = len; i < len + 15 ; i++){
			temp[i]='0';
	}
	len = i;
	bin_div(temp,tempRx);
	for(i = 0, len = i; i < maxlen && (tempRx[i] == '0' || tempRx[i] == '1'); i++);
	len = i;
	while(len > 15){
		for(i = 0; i < maxlen; i++){
			temp[i] = tempRx[i];
			tempRx[i] = 0;
		}
		
		bin_div(temp,tempRx);
		
		for(i = 0; i < maxlen && (tempRx[i] == '0' || tempRx[i] == '1'); i++);
		len = i;
	}
	for(i = 0; i < 16 - len; i++){
		outStr[i] = '0';		
	}
	for(i = 16 - len; i < 16; i++){
		outStr[i] = tempRx[len + i - 16];		
	}
}

char Address[BYTE+1];						//��ַ�ֶ�A
char Control[BYTE+1];						//�����ֶ�C(ֻ���ǵ��ֽ�)
char Info[MAX_INFO];						//�����ֶ�S 
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
	init_fcs_fld(Info,FCS,info_type);
//	printf("FCS�ֶ�(16bit):\n");
//	scanf("%s",FCS);
	Frameing(Address,Control,Info,Info_len,FCS,frame);
	return 0;
}
 

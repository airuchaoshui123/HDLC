/*********************************************
@ author : Bai Jiaqi �׼��� 
@ ID : 161720328
@ class: 1617203
@ date : 2020/5/11
@ instructor :Teacher Ye Haibo Ҷ������ʦ 
**********************************************/

/*********************************************
@ �����HDLC�������Э������,����:
@ 1. ��֡ ��֡ ��֡���з���
@ 2. ���ӵĽ�������
@ 3. ʵ��ͣ��Э���ģ����ʾ
@ 4. CRCУ�� 
@ Attention: ����Dev-C++ ���������ļ�����ʱ
@            �����Ҳ���ͷ�ļ����� �ʰ�����
@			 ����������main.cpp�У�����Ķ�
@			 ���� �����½�! ^_^
**********************************************/

 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define I 0				//�����ֶ���Ϣ֡��� 
#define S 2				//�����ֶμ��֡��� 
#define U 3				//�����ֶ��ޱ��֡��� 
#define SNRM 30 		//�ޱ��֡��SARM��������֡
#define UA 31			//�ޱ��֡��UAȷ��֡
#define DISC 32			//�ޱ��֡��DISC����֡ 
#define RR 20			//���֡��ȷ���յ���N(r)֡ 
#define SREJ 21			//���֡�з����յ���N(r)֡ 

bool IF_INFO_EXIST = 1;			//ȫ�ֱ��� ����֡�����и�֪�Ƿ���ڼ��֡

#define BYTE 8								//1�ֽ� 
#define MAX_FRAME 12000 					//������·�����֡��Ϊ1500 byte �� 12000bit 
#define MAX_INFO 11952						/*���֡�� 1500 byte - ֡ͷ֡β 2 byte - ��ַ�ֶ� 1 byte - �����ֶ� 1 byte - FCS�ֶ� 2 byte = 1494 byte 
												�� 11952bit */	
#define MAX_STR 1449
												
// frame.h�˴�������Ϊ��֡�����ڲ����ú���***************************************************************************											
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

int Frameing(char *Address, char *Control, char *Info, int Info_len, char *FCS, char *frame);		//��֡���� ����֡�� 
// ******************************************************************************************************************

// initfield.h ��ʼ���ֶ�**********************************************************************************
int init_control_fld(char *Control,int control_type); 			//�����ֶ����� ���ؿ����ֶ�֡���ͱ�� 
int init_info_fld(char *Info, int info_type,char *Info_temp);	//���ݿ����ֶ�֡���ͱ�� ��������ֶ� ���������ֶγ��� 
void init_fcs_fld(char *Info, char *FCS,int info_type);			//������������CRCУ���� 
void bin_div(char *inStr,char *outStr);							//bit���� 
void checkCRC(char *inStr, char *outStr);						//CRCУ�������� 
//*********************************************************************************************************

//���ӽ���������غ���************************************************************************* 
int build_SNRM_frame(char *Address);					//����Ҫ�������ӵ�SARM����֡  
int build_UA_frame(char *Address);						//����ȷ��UA����֡ 
int build_DISC_frame(char *Address);					//�������������DISC֡ 
int connect_to_addr(char * Address);					//��Ŀ�ĵ�ַ�������� 	
//void receive(char *frame);							//����֡	
//**************************************************************************************************************** 

// ���ݷ�����غ���*********************************************************************************************** 
int send(int flag);										//����֡ ���ط��͵�֡���� 
int frame_parsing(char *frame, int frame_len, int info_len);				//֡�������� ����unframe���� Ȼ���֡���н���
void unframe(char *frame, int frame_len, int info_len, char *addr, char *cont, char *info, char *fcs);								//��֡		
int bit_del(char *frame, int len, char *frame1);					//0bitɾ��	
// ***************************************************************************************************************
 
//֡�ṹ��ʼ������ *********************************************************************************************** 
void  init_frame();   			//���ȫ�ֱ���Address,Control,Info,Info_temp,Info_len,FCS,frame�Ա���һ֡����ʹ�� 
// *************************************************************************************************************** 

//*֡������غ���*************************************************************************************************
int control_parsing(char *recv_cont);				//���������ֶ� ����֡���� 
void info_parsing(int fcs_flag, int con_type, char *recv_info, int info_len);		//���������ֶ�  
int fcs_parsing(int con_type, char *recv_info, char *recv_fcs);		//����CRCУ�� �ɹ�����1 ���򷵻�0
void bit_to_info(char *recv_info, int info_len);		//bit��ת�ַ��� 
//****************************************************************************************************************

//ͣ��Э��������غ���********************************************************************************************
void num_to_str(int info_num, char *info_num_str);		//�����תΪ�����ƴ�� 
int build_RR_frame(char *Address);						//����RRȷ��֡ 
int build_SREJ_frame(char *Address);					//����SREJ�����ط�֡  
//****************************************************************************************************************

//ȫ�ֱ���(�ظ�ʹ�� ��ʡ�ռ�)*************************************************************************************
char Address[BYTE+1];						//��ַ�ֶ�A
char Control[BYTE+1];						//�����ֶ�C(ֻ���ǵ��ֽ�)
char Info[MAX_INFO];						//�����ֶ�S 
char Info_temp[MAX_INFO];					//ת���ɱ��ش��������ֶθ������� 
int Info_len;								//�����ֶγ��� 
char FCS[BYTE*2+1];							//֡У�������ֶ�FCS 
char CRC[BYTE*2+1];							//���CRC������ ��У��ʱ��FCS�Ƚ� 
char frame[MAX_FRAME];						//�洢������֡
int Info_num = 0;							//�洢���͵����ݴ��� ��������N(s) N(r) 
char Info_num_str[BYTE/2];					//�����תΪ�����ƴ���������� 
int RR_flag;								//����RR֡��־
//*****************************************************************************************************************


// frame.h�˴�������Ϊ��֡�����ڲ����ú���************************************************
 
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

int Frameing(char *Address, char *Control, char *Info, int Info_len, char *FCS, char *frame){		//��֡���� 
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
	return frame_length;
}

//***************************************************************************

// initfield.h ��ʼ���ֶ�**********************************************************************************
int init_control_fld(char *Control,int control_type){						//�����ֶ����� ���ؿ����ֶ�֡���ͱ�� 
	switch(control_type){
		case I:			//��Ϣ֡ 
			Control[0] = '0';
			//Ĭ��N(s) N(r)ÿ��+1, P/F bit = 1 
				num_to_str(Info_num, Info_num_str);
				Control[1] = Info_num_str[0];
				Control[2] = Info_num_str[1];
				Control[3] = Info_num_str[2];
//				Control[1] = '0';	//N(s) = Control[1,2,3] 
//				Control[2] = '0';
//				Control[3] = '1';
				
				Control[4] = '1'; 	//P/F bit = Control[4]
				
				Control[5] = Info_num_str[0];	
				Control[6] = Info_num_str[1];
				Control[7] = Info_num_str[2];
//				Control[5] = '0';	//N(r) = Control[5,6,7] 
//				Control[6] = '0';
//				Control[7] = '1';	
				if(Info_num > 7) Info_num = 0;		//�����͵���Ϣ֡��������7 �ʹ�0��ʼ���±�� 
			return I;		//��Ϣ֡���ΪI 
		case RR:			//���֡ RR
			Control[0] = '1';
			Control[1] = '0';
			// bit2 bit3 Ϊ 00(RR), P/F bit = 1, N(r) = 1
				Control[2] = '0';
				Control[3] = '0';
					
				Control[4] = '1'; 	//P/F bit = Control[4]
				
				Control[5] = '0';	//N(r) = Control[5,6,7] 
				Control[6] = '0';
				Control[7] = '1';	
			 return RR;		//���֡���ΪRR
		case SREJ:			//���֡ SREJ
			Control[0] = '1';
			Control[1] = '0';
			// bit2 bit3 Ϊ 11(SREJ), P/F bit = 1, N(r) = 1
				Control[2] = '1';
				Control[3] = '1';
					
				Control[4] = '1'; 	//P/F bit = Control[4]
				
				Control[5] = '0';	//N(r) = Control[5,6,7] 
				Control[6] = '0';
				Control[7] = '1';	
			 return SREJ;		//���֡���ΪRR
		case 'U':			//�ޱ��֡ 
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
		case I:			//��Ϣ֡ д����Ϣ��ת��Ϊ���ش� 
			printf("Ҫ���������:\n");
			gets(Info);
			info_len = strlen(Info);
			printf("ת��Ϊ���ش�:\n");
			info_len = info_to_bit(Info,info_len,Info_temp);
			print_info_bit(Info,info_len);
			return info_len;
		case S:			//���֡ ��Ϣ�ֶβ�����
//			Info[0] = '#';			//#��ʾ�����ֶβ����� 
			IF_INFO_EXIST = 0;		//ȫ�ֱ��� ����֡�����и�֪�Ƿ���ڼ��֡
			return 0;
		case U:			//�ޱ��֡ Ĭ����Ϣ�ֶ�ȫΪ0 
			for(int i = 0; i < BYTE; i++){
				Info[i] = '0';
			}
			info_len = BYTE;
			return info_len;
	}
}	

void init_fcs_fld(char *Info,char *FCS,int info_type){			//��ʼ��FCS�ֶ� 
	switch(info_type){
		case S:			//��Ϊ���֡ FCS�ֶ���Ϊȫ0
			for(int i = 0; i < 2*BYTE; i++){
				FCS[i] = '0';
			}
			printf("CRCУ����:\n");
			for(int i = 0; i < 2*BYTE; i++){
				printf("%c",FCS[i]);
			}
			printf("\n");
			break;
		case I:			//��Ϊ����֡���ޱ��֡��������CRC����У���� 
		case U:
			checkCRC(Info,FCS);
			printf("CRCУ����:\n");
			for(int i = 0; i < 2*BYTE; i++){
				printf("%c",FCS[i]);
			}
			printf("\n");
			break; 
			
	}
}

void bin_div(char *inStr,char *outStr){				//bit���� 
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

void checkCRC(char *inStr, char *outStr){			//CRCУ�������� 
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
//****************************************************************************************

//���ӽ���������غ���************************************************************************* 

int build_SNRM_frame(char *Address){					//�������ӵ�Address������֡ 
	//char linframe[MAX_FRAME];
	char lincontrol[BYTE+1] = "11001001";
	char lininfo[BYTE+1] = "00000000";
	int lininfo_len = BYTE;
	char linfcs[BYTE*2+1] = "0000000000000000";
	strcpy(Control,lincontrol);
	strcpy(Info,lininfo);
	Info_len = lininfo_len;
	strcpy(FCS,linfcs);
	int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
	return frame_len;
} 

int build_UA_frame(char *Address){					//����ȷ��UA����֡ 
	char linframe[MAX_FRAME];
	char lincontrol[BYTE+1] = "11001110";
	char lininfo[BYTE+1] = "00000000";
	int lininfo_len = BYTE;
	char linfcs[BYTE*2+1] = "0000000000000000";
	strcpy(Control,lincontrol);
	strcpy(Info,lininfo);
	Info_len = lininfo_len;
	strcpy(FCS,linfcs);
	int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
	return frame_len;
} 

int build_DISC_frame(char *Address){					//�������������DISC֡ 
	char linframe[MAX_FRAME];
	char lincontrol[BYTE+1] = "11001010";
	char lininfo[BYTE+1] = "00000000";
	int lininfo_len = BYTE;
	char linfcs[BYTE*2+1] = "0000000000000000";
	strcpy(Control,lincontrol);
	strcpy(Info,lininfo);
	Info_len = lininfo_len;
	strcpy(FCS,linfcs);
	int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
	return frame_len;
}

int connect_to_addr(char *Address){
	if(strlen(Address) != 8){
		printf("�Ҳ����˵�ַ(����ԭ��:�����ַλ������ ӦΪ8λ!)\n");
		exit(0);
	} 
	char flag = Address[0];							//������ַ�ֶ�flag �鿴��ַ����Ч��ַ����ȫ0���ǹ㲥��ַ 
	for(int i = 0; i < BYTE; i++){
		if(Address[i] != flag){
			flag = '2';
			break;	
		}
	}
	switch(flag){
		case '0':
			printf("����������·״̬�ɹ�!\n");
			return 0;
		case '1':
			printf("�㲥ģʽ!\n");
			return 1;
		case '2':
			printf("���ڽ�������!\n");
			return -1;
	}
}

//******************************************************************************************

 
// ���ݷ�����غ���*************************************************************************
int send(int flag){					//����֡ 
	if(flag == 0){
		int frame_len = build_SNRM_frame(Address);
//		int info_type = init_control_fld(Control,'U');
//		Info_len = init_info_fld(Info,info_type,Info_temp);
//		init_fcs_fld(Info,FCS,info_type);
//		int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
		int con_type = frame_parsing(frame,frame_len,Info_len);
		return con_type;
	}
	else if(flag == 1){
		int frame_len = build_UA_frame(Address);
//		int info_type = init_control_fld(Control,'U');
//		Info_len = init_info_fld(Info,info_type,Info_temp);
//		init_fcs_fld(Info,FCS,info_type);
//		int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
		int con_type = frame_parsing(frame,frame_len,Info_len);
		return con_type;
	}
	else{
		while(1){
			printf("\n������������(����1),����Զ�̵�ַ�Ͽ�����(����2):\n");
			int choice;
			scanf("%d",&choice);
			getchar();
			if(choice == 1){
				int info_type = init_control_fld(Control,I);
				Info_len = init_info_fld(Info,info_type,Info_temp);
				init_fcs_fld(Info,FCS,info_type);
				int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
				printf("������֡!\n");
				system("pause");
				printf("����֡����:\n");
				int con_type = frame_parsing(frame,frame_len,Info_len);
//				if(con_type == I){		//������������֡ 
//					printf("��У�������Ƿ�һ��(һ������1,��һ������2),��һ�·���RR֡ȷ��,����һ�·���SREJ֡�����ط�!\n");
//					int choice2;
//					scanf("%d",&choice2);
//					send_Sframe(choice2);
//				}
				return con_type;
			}
			else if(choice == 2){
				int frame_len = build_DISC_frame(Address);
				int con_type = frame_parsing(frame,frame_len,Info_len);
				return con_type;
			}
			else{
				printf("��������ȷ���!\n");
			}	
		}
	}
}

int frame_parsing(char *frame, int frame_len, int info_len){
	char recv_cont[BYTE+1] = {'\0'};
	char recv_addr[BYTE+1] = {'\0'};				//void unframe(char *frame, int frame_len, int info_len, char *addr, char *cont, char *info, char *fcs)
	char recv_info[MAX_INFO] = {'\0'};
	char recv_fcs[BYTE*2+1] = {'\0'};
	unframe(frame,frame_len,Info_len,recv_addr,recv_cont,recv_info,recv_fcs);
	printf("���յ�֡:%s ��%dbit\n",frame,frame_len);
	printf("����:\n"); 
	printf("��ַ�ֶ�:%s\n",recv_addr);
	printf("�����ֶ�:%s\n",recv_cont);
	printf("�����ֶ�:%s,֡��:%d\n",recv_info,info_len);
	printf("FCS�ֶ�:%s\n",recv_fcs);
	int con_type = control_parsing(recv_cont);
	int fcs_flag = fcs_parsing(con_type,recv_info,recv_fcs);
	info_parsing(fcs_flag,con_type,recv_info,info_len);
	return con_type; 
}

void unframe(char *frame, int frame_len, int info_len, char *addr, char *cont, char *info, char *fcs){		//��֡ 
	char frame1[MAX_FRAME];
	int i = 0;
	int j = 0;
	int len = 0;
	for(i = 8; i < frame_len - 8; i++){
		frame1[j++] = frame[i];
		len++;
	}
	char frame2[MAX_FRAME];
	int len2 = bit_del(frame1,len,frame2);
	for(i = 0; i < BYTE; i++){
		addr[i] = frame2[i];
	}
	addr[i] = '\0';
	j = i;
	int k = 0;
	for(; i < j + BYTE; i++){
		cont[k++] = frame2[i];
	}
	cont[k] = '\0';
	j = i;
	k = 0;
	for(; i < j + info_len; i++){
		info[k++] = frame2[i];
	}
	info[k] = '\0';
	j = i;
	k = 0;
	for(; i < j + BYTE * 2; i++){
		fcs[k++] = frame2[i];
	}
	fcs[k] = '\0';
} 

int bit_del(char *frame, int len, char *frame1){		//0bitɾ�� 
	int cnt = 0;
	int j = 0;
	for(int i = 0 ; i < len ; i++){
		if(frame[i] == '1') cnt++;
		else cnt = 0; 
		if(cnt != 5){
			frame1[j] = frame[i];	
			j++;
		}
		else if(cnt == 5){
			frame1[j] = frame[i];	
			j++;
			if(frame[i+1] == '0'){
				i++;
				cnt = 0;
			}
			else if(frame[i+1] == 1 && frame[i+2] == 1){
				printf("�����ֶ�����!\n");
				exit(0);
			}
		}
	}
	return j;
}

//***************************************************************************

//֡�ṹ��ʼ������ ***********************************************************************************************

void init_frame(){
	for(int i = 0; i < BYTE; i++){
//		Address[i] = '\0';
		Control[i] = '\0';
	}
	for(int i = 0; i < BYTE * 2; i++){
		FCS[i] = '\0';
		CRC[i] = '\0'; 
	}
	for(int i = 0; i < MAX_INFO; i++){
		Info[i] = '\0';
		Info_temp[i] = '\0';
	}
	for(int i = 0; i < MAX_FRAME; i++){
		frame[i] = '\0';
	}
	Info_len = 0;
} 

//****************************************************************************************************

//*֡������غ���*************************************************************************************************

int control_parsing(char *recv_cont){				//���������ֶ� ����֡���� 
	if(recv_cont[0] == '0'){		//�ж�Ϊ��Ϣ֡ 
		printf("��Ϣ֡���:%c%c%c\n",recv_cont[1],recv_cont[2],recv_cont[3]);
		return I;
	}
	else if(recv_cont[0] == '1'){		 
//		if(recv_cont[1] == '0') return S;		//�ж�Ϊ���֡ 
		if(recv_cont[1] == '0'){		//�ж�Ϊ���֡ 
			char bit2 = recv_cont[2];
			char bit3 = recv_cont[3];
			if(bit2 == '0' && bit3 == '0'){		//RR֡ 
				return RR;
			} 
			else if(bit2 == '1' && bit3 == '1'){		//SREJ֡ 
				return SREJ;
			} 
		} 
		else{		//�ж�Ϊ�ޱ��֡ 
			char bit3 = recv_cont[2];
			char bit4 = recv_cont[3];
			char bit6 = recv_cont[5];
			char bit7 = recv_cont[6];
			char bit8 = recv_cont[7];
			if(bit3 == '0' && bit4 == '0' && bit6 == '0'
				&& bit7 == '0' && bit8 == '1'){
					return SNRM;
				}
			else if(bit3 == '0' && bit4 == '0' && bit6 == '1'
					&& bit7 == '1' && bit8 == '0'){
						return UA;
					}
			else if(bit3 == '0' && bit4 == '0' && bit6 == '0'
					&& bit7 == '1' && bit8 == '0'){
						return DISC;
					}
		}
	}
	printf("����֡��������!\n");
	exit(0);
}

//void bit_to_info(char *inStr_bit, char *outStr_char){		//bit��ת���ַ� 
//	int i, j;
//	int n = 0;
//	int maxlen = MAX_INFO;
//	char temp[MAX_INFO];
//	char bin[8];
//	char sumchar;
//	for(i = 0; i < maxlen  && (inStr_bit[i] == '0' || inStr_bit[i] == '1'); i++){			//��ȡ���봮����
//		temp[i]=inStr_bit[i];
//	}
//	n = i;
//	for(i = 0; i < n % 8 && i + n < maxlen; i++){			//������8�ı������ش������0
//		temp[i+n] = '0';
//	}
//	for(i = 0; i < maxlen && (temp[i] == '0' || temp[i] == '1'); i = i + 8){			//ת����ASCII��ֵ
//		sumchar = 0;
//		for(j = 0; j < 8; j++){		//��8λ����ת����ʮ���Ƶ�ASCII��ֵ
//			sumchar = (temp[i+j] - '0') * _2_x(7 - j);
//			outStr_char[i/8] = outStr_char[i/8] + sumchar;	
//		}
//	}
//}

void info_parsing(int fcs_flag, int con_type, char *recv_info, int info_len){			//���������ֶ� 
	if(!fcs_flag){
		printf("CRCУ����У��ʧ��!�����·���!\n"); 
	}
	else{
		switch(con_type){
			case I:
				printf("���ڽ��������ֶ�!\n");
				printf("��������Ϊ:%s\n",recv_info);
//				for(int i = 0; i < info_len; i++){
//					printf("%c",recv_info[i]);
//				}
//				char str[MAX_STR]; 
				printf("������ԭ����Ϊ:");
				bit_to_info(recv_info,info_len);
//				printf("�ַ�������Ϊ:%s\n",str);
				break;
			case S:
			case RR:
			case SREJ: 
				printf("��֡Ϊ���֡,�����������ֶ�!\n");
				break;
			case SNRM:
				printf("��֡ΪSNRM֡!\n");
				break; 
			case UA:
				printf("��֡ΪUA֡!\n");
				break;
			case DISC:
				printf("��֡ΪDISC֡!����������Զ�̵�ַ�Ͽ�����!\n"); 
				break;
		}	
	}
}

int fcs_parsing(int con_type, char *recv_info, char *recv_fcs){		//����CRCУ�� �ɹ�����1 ���򷵻�0
	switch(con_type){
		case I:
			printf("���ڽ���CRCУ��!\n");
			checkCRC(recv_info,CRC);
			strcpy(CRC,recv_fcs);
			printf("FCS:%s\n",recv_fcs);
			printf("CRC:%s\n",CRC);
			system("pause");
			if(strcmp(CRC,recv_fcs) == 0){
				printf("CRCУ��ɹ�!\n");
				return 1;
			}
			else {
				printf("CRCУ��ʧ��!\n");
				return 0;
			}
		case S:
		case RR:
		case SREJ:
		case U:
		case SNRM:
		case DISC:
		case UA:
			return 1;
	}
}

void bit_to_info(char *recv_info, int info_len){			//bit��ת�ַ��� 
	char str[BYTE+1];
	int k, sum;
	for(int i = 0; i < info_len; i = i + 8){
		int i1 = 0;
		for(int j = i; j < i + 8; j++){
			str[i1++] = recv_info[j];
		}
		str[i1] = '\0';
    	for(sum = k = 0; str[k] ; (sum *= 2) += str[k++] - '0');
    	printf("%c",sum);
	}
	printf("\n");
}

//************************************************************************************* 

//*ͣ��Э��������غ���***************************************************************** 
void num_to_str(int info_num, char *info_num_str){
	switch(info_num){
		case 0:
			info_num_str[0] = '0';
			info_num_str[1] = '0';
			info_num_str[2] = '0';
			info_num_str[3] = '\0';
			break;
		case 1:
			info_num_str[0] = '0';
			info_num_str[1] = '0';
			info_num_str[2] = '1';
			info_num_str[3] = '\0';
			break;
		case 2:
			info_num_str[0] = '0';
			info_num_str[1] = '1';
			info_num_str[2] = '0';
			info_num_str[3] = '\0';
			break;
		case 3:
			info_num_str[0] = '0';
			info_num_str[1] = '1';
			info_num_str[2] = '1';
			info_num_str[3] = '\0';
			break;
		case 4:
			info_num_str[0] = '1';
			info_num_str[1] = '0';
			info_num_str[2] = '0';
			info_num_str[3] = '\0';
			break;
		case 5:
			info_num_str[0] = '1';
			info_num_str[1] = '0';
			info_num_str[2] = '1';
			info_num_str[3] = '\0';
			break;
		case 6:
			info_num_str[0] = '1';
			info_num_str[1] = '1';
			info_num_str[2] = '0';
			info_num_str[3] = '\0';
			break;
		case 7:
			info_num_str[0] = '1';
			info_num_str[1] = '1';
			info_num_str[2] = '1';
			info_num_str[3] = '\0';
			break;
	}
} 

int build_RR_frame(char *Address){					//����RRȷ��֡ 
	//char linframe[MAX_FRAME];
	char lincontrol[BYTE+1] = "10001001";
	char lininfo[BYTE+1] = "00000000";
	int lininfo_len = 0;		//���֡����Ϣ�ֶ� 
	char linfcs[BYTE*2+1] = "0000000000000000";
	strcpy(Control,lincontrol);
	strcpy(Info,lininfo);
	Info_len = lininfo_len;
	strcpy(FCS,linfcs);
	int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
//	RR_flag = 1; 
	return frame_len;
}

int build_SREJ_frame(char *Address){					//����SREJ�����ط�֡ 
	//char linframe[MAX_FRAME];
	char lincontrol[BYTE+1] = "10111001";
	char lininfo[BYTE+1] = "00000000";
	int lininfo_len = 0;		//���֡����Ϣ�ֶ� 
	char linfcs[BYTE*2+1] = "0000000000000000";
	strcpy(Control,lincontrol);
	strcpy(Info,lininfo);
	Info_len = lininfo_len;
	strcpy(FCS,linfcs);
	int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
//	RR_flag = 0;
	return frame_len;
}

//********************************************************************************* 

int main(){
	char control_type;
//	printf("����HDLC֡����(I or S or U):\n");
//	scanf("%c",&control_type);
//	int info_type = init_control_fld(Control,control_type);
//	Info_len = init_info_fld(Info,info_type,Info_temp);
	printf("Ҫ����ĵ�ַ(8bit):\n");
	scanf("%s",Address);
	getchar();
	int cta = connect_to_addr(Address); 
	if(cta == -1){
		printf("����SNRM֡��Ŀ���ַ��������:\n");
//		build_SARM_frame(Address);
//		printf("���ӳɹ���\n");
		int end_flag = 0;			//֡��� 
		int con_type;
		init_frame();
		while(1){
			if(end_flag == 0){
				con_type = send(end_flag++);
				system("pause");
			}
			else if(end_flag == 1){
				printf("�յ�SNRM֡,��������UA֡ȷ��:\n");
				con_type = send(end_flag++);
				printf("��Զ�̵�ַ�������ӳɹ�!\n");
				system("pause");
			}
			else{
				con_type = send(end_flag++);
				if(con_type == I){
					printf("��У�������Ƿ�һ��(һ������1,��һ������2),��һ�·���RR֡ȷ��,����һ�·���SREJ֡�����ط�!\n");
					int choice2;
					scanf("%d",&choice2);
					while(1){
						if(choice2 == 1){		//RR֡ 
							Info_num++;
							int frame_len = build_RR_frame(Address);
							int con_type = frame_parsing(frame,frame_len,Info_len);
							printf("�յ�RR֡,�����ѳɹ�������Զ�̵�ַ!\n");
							break;
						}
						else if(choice2 == 2){
							int frame_len = build_SREJ_frame(Address);
							int con_type = frame_parsing(frame,frame_len,Info_len);
							printf("�յ�SREJ֡,�������ݷ���ʧ��,�����·���!\n");
							break; 
						}
					}
					 
				}
				if(con_type == DISC){
					printf("�յ�DISC֡,����UA֡ȷ�ϲ���!\n");
					system("pause");
			//		build_UA_frame(frame);
					int frame_len = build_UA_frame(Address);
					int con_type = frame_parsing(frame,frame_len,Info_len);
					if(con_type == UA){
						printf("�ѶϿ�����,�ٻ�! ^-^\n");
					} 
					break;
				}
			}
			init_frame(); 
//			printf("�����%d֡��\n",end_flag);
//			printf("HDLC֡����(I or S or U):");
//			scanf("%c",&control_type);
//			printf("%d",control_type);
//			int info_type = init_control_fld(Control,control_type);
//			Info_len = init_info_fld(Info,info_type,Info_temp);
//			init_fcs_fld(Info,FCS,info_type);
//			int frame_len = Frameing(Address,Control,Info,Info_len,FCS,frame);
//			frame_parsing(frame,frame_len,Info_len);
//			end_flag++;
//			init_frame();
		}		
	}
//	printf("�����ֶ�(8bit):\n");
//	scanf("%s",Control);
//	init_fcs_fld(Info,FCS,info_type);
//	printf("FCS�ֶ�(16bit):\n");
//	scanf("%s",FCS);
//	Frameing(Address,Control,Info,Info_len,FCS,frame);
	return 0;
}
 

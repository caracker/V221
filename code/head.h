#ifndef __HEAD_H
#define __HEAD_H	

//*************************************************//
//�����Ķ��壬�޸ı�������ͬ���޸�head_extern.h
//***********************************************//

BYTE	Sys_Flag;
BIT		f_work		:	Sys_Flag.0;		//���ػ�
BIT		f_low		:	Sys_Flag.1;			//
bit     f_key_scan	:	Sys_Flag.2;		//����ɨ��
bit     f_charging_full:Sys_Flag.3;		//����
bit     f_charging	:	Sys_Flag.4;	
bit 	f_heating 	:   Sys_Flag.5;	
byte motor_state,motor_state_temp;		//��﹤��ģʽ0~7
byte count;//T16����
byte S1_count,S2_count;//��������
word motor_time;
WORD sleep_time;
word led_time,led_time2;
byte s1_lastime;
byte hot_mode;
byte motor_delcnt;
word hot_ad;
byte check_cnt;
bit  f_low35;
byte low_ledtime;
byte Suck_mode;
byte led_flashtime;
#endif
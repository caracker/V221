
#include	"motor.h"
#include "../../head_extern.h"
#include	"../key/key.h"
/************************************************************************
*	PWM���Ƶ��= FIHRC �� [ CB +1 ]
*	PWM���ռ�ձȣ�ʵʱ�� = (1/FIHRC) * [ DB10_1 + DB0 * 0.5 + 0.5]
*	���� Duty_Bound[10:1] = {pwmgxdth[7:0],pwmgxdtl[7:6]} = DB10_1; ��ռ�ձ�
*	Duty_Bound[0] = pwmgxdtl[5] = DB0
*	Counter_Bound[10:1] = {pwmgcubh[7:0], pwmgcubl[7:6]} = CB; �Ǽ���������
**************************************************************************/
byte motor_temp;

//M1 PB5
void motor_init(void)
{ 
	tm3ct=0;
	tm3b = 127;			 //���޼Ĵ���    k=127
	tm3c = 0b_0010_00_0_0;   // 16m, ��� = PA3, ����ģʽ
	tm3s = 0b_0_10_01001; 
	motor_off;


	tm2ct=0;
	tm2b = 127;			 //���޼Ĵ���    k=127
	tm2c = 0b_0010_00_1_0;   // 16m, ��� = PA3, ����ģʽ
	tm2s = 0b_0_00_10100; 
	motor2_off;
//	while(1)
	{
//		motor2_on;
		nop;
	}
}

void motor_mode1(void)
{
	if(motor_state_temp !=motor_temp)
	{
		motor_state_temp=motor_temp;
		tm3b =102;
		motor_on;
	}
}
void motor_mode2(void)
{
	if(motor_state_temp !=motor_temp )
	{
		motor_state_temp=motor_temp;
		motor_time=0;
		tm3b =153;
		motor_on;
	}

}
void motor_mode3(void)
{
	if(motor_state_temp !=motor_temp)
	{
		motor_state_temp=motor_temp;
		motor_time=0;
		tm3b =204;
		motor_on;
	}
}
void motor_mode4(void)
{
	if(motor_state_temp !=motor_temp)
	{
		motor_state_temp=motor_temp;
		motor_time=0;
		tm3b =255;
		motor_on;
	}
}
void motor_mode5(void)
{
	if(motor_state_temp !=motor_temp )
	{
		motor_state_temp=motor_temp;
		motor_time=0;
		tm3b =255;
		motor_on;
	}
	if(motor_time<15)
	{
		motor_on;
	}
	else if(motor_time<30)
	{
		motor_off;
	}
	else
	{
		motor_time=0;
	}
}
//������ģʽ ��800mS-ͣ200mS-��200mS-ͣ150mS-��200mS-ͣ150mS-��200mS-ͣ150mS ѭ��
void motor_mode6(void)
{
	if(motor_state_temp !=motor_temp )
	{
		motor_state_temp=motor_temp;
		motor_time=0;
		tm3b =255;
		motor_on;
	}
	if(motor_time<80)
	{
		motor_on;
	}
	else if(motor_time<100)
	{
		motor_off;
	}
	else if(motor_time<120)
	{
		motor_on;
	}
	else if(motor_time<135)
	{
		motor_off;
	}
	else if(motor_time<155)
	{
		motor_on;
	}
	else if(motor_time<170)
	{
		motor_off;
	}else if(motor_time<190)
	{
		motor_on;
	}
	else if(motor_time<205)
	{
		motor_off;
	}
	else
	{
		motor_time=0;
	}
}
//������ģʽ ռ�ձ�30%��50Hz����1S- ռ�ձ�50%��50Hz����1S-100%��1S ѭ��
void motor_mode7(void)
{
	if(motor_state_temp !=motor_temp )
	{
		motor_state_temp=motor_temp;
		motor_time=0;
		tm3b =76;
		motor_on;
	}
	if(motor_time<100)
	{
		tm3b =76;
		motor_on;
	}
	else if(motor_time<200)
	{
		tm3b =127;
		motor_on;
	}
	else if(motor_time<300)
	{
		tm3b =255;
		motor_on;
	}
	else
	{
		motor_time=0;
	}
}

byte motor_state_temp2;
void motor2_mode1(void)
{
	if(Suck_mode != motor_state_temp2)
	{
		motor_state_temp2=Suck_mode;
		/*
		pwmgclk=0B_1_000_000_0;		//ϵͳʱ�ӣ�pwmg���ã�32��Ƶ
		//CB=631
		pwmgcubl=(666&0x6)<<6;	//�������޵�λ�Ĵ���
		pwmgcubh=(666>>2);			//�������޸�λ�Ĵ��� 
		//DB=1023   ռ�ձ�50%
		pwmg1dtl=(566&0x6)<<6;	
		pwmg1dth=(566>>2);	
		*/
		tm2b =216;
		motor2_on;
	
	}
}

void motor2_mode2(void)
{
	if(Suck_mode != motor_state_temp2)
	{
		motor_state_temp2=Suck_mode;
		/*
		pwmgclk=0B_1_000_000_0;		//ϵͳʱ�ӣ�pwmg���ã�32��Ƶ
		//CB=631
		pwmgcubl=(666&0x6)<<6;	//�������޵�λ�Ĵ���
		pwmgcubh=(666>>2);			//�������޸�λ�Ĵ��� 
		//DB=1023   ռ�ձ�50%
		pwmg1dtl=(612&0x6)<<6;	
		pwmg1dth=(612>>2);	
		*/	
		tm2b =234;
		motor2_on;
	}
}
void motor2_mode3(void)
{
	if(Suck_mode != motor_state_temp2)
	{
		motor_state_temp2=Suck_mode;
		/*
		pwmgclk=0B_1_000_000_0;		//ϵͳʱ�ӣ�pwmg���ã�32��Ƶ
		//CB=631
		pwmgcubl=(666&0x6)<<6;	//�������޵�λ�Ĵ���
		pwmgcubh=(666>>2);			//�������޸�λ�Ĵ��� 
		//DB=1023   ռ�ձ�50%
		pwmg1dtl=(660&0x6)<<6;	
		pwmg1dth=(660>>2);	
		*/
		tm2b =253;
		motor2_on;
	}
}

void motor_even(void)
{
	if(f_work && (!f_charging))
	{
	//	if(motor_delcnt>30)
		{
			motor_temp=motor_state;
		}
		switch(motor_temp)
		{
			case 0:
				motor_off;
				break;
			case 1:
				motor_mode1();
				break;
			case 2:
				motor_mode2();
				break;
			case 3:
				motor_mode3();
				break;
			case 4:
				motor_mode4();
				break;
			case 5:
				motor_mode5();
				break;
			case 6:
				motor_mode6();
				break;
			case 7:
				motor_mode7();
				break;
			default:
				break;
		}

		switch(Suck_mode)
		{
			case 0:
				motor2_off;
				break;
			case 1:
				motor2_mode1();
				break;
			case 2:
				motor2_mode2();
				break;
			case 3:
				motor2_mode3();
				break;
			default :
				Suck_mode=0;
				break;
		}
	}
	else
	{
		motor_off;
		motor2_off;
	}
}
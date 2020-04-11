#include	"KEY.h"
#include "../../head_extern.h"
#include	"../led/led.h"
#include	"../motor/motor.h"
#include	"../comparator/comparator.h"
#include	"../hot/hot.h"
extern byte motor_state_temp,motor_state_temp2;
extern byte hot_mode_temp;
void key_init(void)
{
	$ s1 IN,pull;
	$ s2 IN,pull;
	$ power_full IN,pull;
	$ power_in   in,nopull;						
	
}
byte check_cnt2;
dword char_time;
word sec30;
void check_charging(void)
{
 	if(power_in)
	{
		f_low=0;
		f_charging=1;
		motor_state=0;
		f_work=0;
		f_heating=0;
		hot_mode=0;
		sleep_time=0;
		Suck_mode=0;
 		sec30=0;
		char_time++;
		if(char_time>150*60*100)
		{
			char_time=0;
			f_charging_full=1;
		}
		if(power_full)
		{
			check_cnt2++;
			if(check_cnt2>100)
			{
				check_cnt2=0;
				f_charging_full=1;
			}
			
		}
		else
		{
		//	f_charging_full=0;
		}
	}
	else
	{
		f_charging_full=0;
		f_charging=0;
		check_cnt2=0;
		char_time=0;
	}
	
}
word hot_time2;

void key_scan(void)
{
	
	if(f_key_scan)
	{
		f_key_scan=0;
		check_charging();

	//	f_charging=1;
		if(!f_charging)
		{
			check_low();
			s1_even();
			s2_even();
			if(f_heating ||Suck_mode||motor_state)
			{
				if(f_work==0)
				{
					$ gpcs  VDD*9/24;  
					if(gpcc.6 )  //VDD大2.9
					{
						nop;
		
					}
					else
					{
						f_heating=0;
					}
					f_work=1;
					$ gpcs   VDD*13/32;//低于2.9v  
					if(gpcc.6 ==0) //低于2.9v 
					{
						f_work=0;
						motor2_off;
						motor_off;
						hot_pin=0;
						red_led=led_off;
						white_led =led_off;
						white_led2 =led_off;
						motor_state=5;
						while(motor_state--)
						{
							white_led=led_on;
							white_led2=led_on;
							.delay 2000*500;
							white_led=led_off;
							white_led2=led_off;
							.delay 2000*500;
						}
						white_led=led_off;
						white_led2=led_off;
						sleep_time=0;
						motor_state=0;
						f_work=0;
						f_low=1;	
						f_heating=0;
						hot_mode=0;
						f_low35=0;
						Suck_mode=0;	
					}
					$ gpcs  VDD*9/24;  
					check_cnt=0;
					f_low35=0;
				}
			
			}
			else
			{
				f_work=0;
			}
			if(f_heating && !Suck_mode)
			{
				hot_time2++;
				if(hot_time2>5*60*100)
				{
					f_heating=0;
				}
			}
			else
			{
				hot_time2=0;
			}
			if(f_work)
			{
				if(!f_heating && !Suck_mode && !motor_state)
				{
					sec30++;
					if(sec30>30*100)
					{
						f_work=0;	
					}
				}
				else
				{
					sec30=0;
				}
				/*
				：电压低于3.3V时发热丝没有关闭或低于3.3V时还能开启发热丝
  					 如电压低于3.3V后不能开启发热丝
 					 如单独开启发热丝，3.3V低电后就关闭，30秒自动关机
 				  如发热丝和吸吮同时开启，3.3V低电发热丝就关闭，吸吮继续工作，直到3V自动关机
				  */
				if(f_low35)//低于3.3
				{
					if(f_heating)
					{
						f_heating=0;	
					}
				}
			}
			else
			{
				sec30=0;
			}
		}

	}
}

byte s1_cnt;
bit s1_open;
bit f_click;
byte s1_time;
extern byte motor_state_temp2;
void s1_even(void)
{
	if(s1==0)
	{
		if(S1_count<250)	S1_count++;
		if(S1_count>100&&S1_count<210) //长按
		{
			S1_count=220;
			if(Suck_mode==0)
			{
				Suck_mode=1;
				motor_state_temp2=99;
			}
			else
			{
				Suck_mode=0;
			}
			/*
			if(!f_work)
			{
				f_work=1;
				motor_state=0;
				f_heating=0;
				Suck_mode=0;
				motor_state_temp=99;
				motor_state_temp2=99;
				s1_open=0;
				f_click=0;
				hot_time2=0;
			}
			else
			{
				if(s1_open)
				{
					//打开吸允关闭马达
					if(Suck_mode==0)
					{
						Suck_mode=1;
						motor_state=0;	
						motor_state_temp2=99;
					}
					else
					{
						Suck_mode=0;
					}
					led_flashtime=35;
				}
			}
			*/

		}
	}
	else
	{	
		if(S1_count>2&&S1_count<100)
		{
//			if(f_work)
			{
				if(f_click && s1_time<30)
				{
					//双击
					if(f_heating==0)
					{
						f_heating=1;
					}
					else
					{
						f_heating=0;
					}
					s1_time=250;
					f_click=0;
					if(!Suck_mode)led_flashtime=35;	
				}
				else
				{
					//单击
					f_click=1;
					s1_time=0;
					if(Suck_mode) led_flashtime=35;		
				}
			}
		}
		S1_count=0;	
		s1_open=1;
		if(s1_time<250)s1_time++;
		if(s1_time>30)
		{
			if(f_click && f_work)  //按下延迟300ms
			{
				if(Suck_mode)
				{
					Suck_mode++;
					if(Suck_mode>3)Suck_mode=1;
					motor_state_temp2=99;
				}
			}
			f_click=0;
		}
	}
}
byte s2_cnt;
bit s2_open;
bit f_click2;
byte s2_time;

void s2_even(void)
{
	if(s2==0)
	{
		if(S2_count<250)	S2_count++;
		if(S2_count>100&&S2_count<210) //长按
		{
			S2_count=220;
			if(motor_state==0)
			{
				motor_state=1;
				motor_state_temp=99;
			}
			else
			{
				motor_state=0;
			}
		}
	}
	else
	{	
		if(S2_count>2&&S2_count<100)
		{
//			if(f_work)
			{
				if(f_click2 && s2_time<30)
				{
					//双击
					if(f_heating==0)
					{
						f_heating=1;	
					}
					else
					{
						f_heating=0;
					}
					s2_time=250;
					f_click2=0;
				}
				else
				{
					//单击
					f_click2=1;
					s2_time=0;		
				}
			}
		}
		S2_count=0;	
		s2_open=1;
		if(s2_time<250)s2_time++;
		if(s2_time>30)
		{
			if(f_click2 && f_work)  //按下延迟300ms
			{
				if(motor_state)
				{
					motor_state++;
					if(motor_state>7)motor_state=1;
					motor_state_temp=99;
				}
			}
			f_click2=0;
		}
	}
}
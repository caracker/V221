#include	"led.h"
#include "../../head_extern.h"
#include	"../key/key.h"
#include	"../motor/motor.h"

void led_init(void)
{ 
	$ red_led out,low;
	$ white_led out,low;
	$ white_led2 out,low;
	red_led=led_off;
	white_led=led_off;
	white_led2=led_off;
}


byte led_cnt,led_cnt2;
bit pwm_flag,pwm_flag2;
extern bit s1_open;
void led_even(void)
{
	if(f_charging)
	{
		red_led=led_off;
		if(f_charging_full)
		{
			white_led=led_on;
			white_led2=led_on;
			led_time=0;
			led_cnt=0;
			led_time2=0;
			pwm_flag=0;
		}
		else
		{
			if(led_time2>=5)
			{
				led_time2=0;
				if(pwm_flag)
				{
					if(led_cnt) led_cnt--;
					else
					{
						pwm_flag=0;
					}
				}
				else
				{
					led_cnt++;
					if(led_cnt>42) pwm_flag=1;
				}
				
			}
			if(led_time<led_cnt)
			{
				white_led=led_on;
				white_led2=led_on;
			}
			else if(led_time<42)
			{
				white_led=led_off;
				white_led2=led_off;
			}
			else
			{
				led_time=0;
			}	
		}
	}
	else
	{
		led_cnt=0;
		pwm_flag=0;
		if(f_low35)
		{
			if(f_work)
			{
				if(low_ledtime<100)
				{
					white_led=led_on;
					white_led2=led_on;
				}
				else if(low_ledtime<200)
				{
					white_led=led_off;
					white_led2=led_off;
				}
				else
				{
					low_ledtime=0;	
				}
				if(f_heating)
				{
					red_led=led_on;
				}
				else
				{
					red_led=led_off;
				}
			}
		}
		else
		{
			if(f_work)
			{
				/*
				if(s1_open)
				{
					if(s1 &&s2)
					{
						white_led=led_on;
						white_led2=led_on;
					}
					else
					{
						white_led=led_off;
						white_led2=led_off;
					}
					
				}
				else
				{
					white_led=led_on;
					white_led2=led_on;
				}*/
				if(motor_state||Suck_mode)
				{
					white_led=led_on;
					white_led2=led_on;
				}
				else
				{
					white_led=led_off;
					white_led2=led_off;
				}
				if(f_heating)
				{
					red_led=led_on;
				}
				else
				{
					red_led=led_off;
				}
			}
			else
			{
				white_led=led_off;
				white_led2=led_off;
				red_led=led_off;
			}
		}
	
	}
}




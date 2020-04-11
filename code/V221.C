#include	"extern.h"
#include	"./user/TIM16/TIM16.h"
#include	"./user/key/key.h"
#include	"./user/led/led.h"
#include	"./user/motor/motor.h"
#include	"./user/STOPSYS/STOPSYS.h"
#include	"./user/adc/adc.h"
#include	"./user/hot/hot.h"
#include	"./user/comparator/comparator.h"
#include 	"head.h"
//.Writer     Limit   $ + 5
extern byte motor_state_temp;
extern byte motor_state_temp2;
extern byte check_cnt2;
extern dword char_time;
void data_init(void)
{
	f_work=0;
	f_charging=0;
	f_key_scan=0;
	count=39;
	s1_lastime=250;
	motor_state_temp=0;
	motor_state=0;
	f_heating=0;
	hot_mode=0;
	motor_delcnt=250;
	sleep_time=0;
	check_cnt=0;
	led_time2=0;
	f_low35=0;
	low_ledtime=0;
	f_charging_full=0;
	led_flashtime=0;
	check_cnt2=0;
	char_time=0;
}
void	FPPA0 (void)
{

	.ADJUST_IC	SYSCLK=IHRC/8, IHRC=16MHz, VDD=3.7V;
	.delay 2000*200;
	T16_init();
	key_init();
	motor_init();
	ADC_init();
	hot_init();
	led_init();
	comparator_init();	
	stopsys_init();
	data_init();
	f_low=0;
	while (1)
	{
		key_scan();
		motor_even();
		adc_even();
		hot_even();
		led_even();
		stopsys_even();
 	}
}
void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	
		Intrq.T16	=	0;
		if(led_time<50000)led_time++;
		if (--count == 0)					
		{
			count= 39;          // 256 uS * 39 = 9,984 uS ¨P 10 mS
	 		f_key_scan=1;
			if(motor_time<10000) motor_time++;
			if(motor_delcnt<250) motor_delcnt++;
			if(led_time2<250)led_time2++;
			if(low_ledtime<250)low_ledtime++;
			if(led_flashtime)led_flashtime--;
			if(!f_work)
			{
				sleep_time++;
			}
			else
			{
				sleep_time=0;
			}
		}
	}

	popaf;
}







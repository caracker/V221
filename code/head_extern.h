#ifndef __head_extern_H
#define __head_extern_H	

extern BYTE	Sys_Flag;
extern BYTE	Sys_Flag;
extern BIT		f_work		:	Sys_Flag.0;		//开关机
extern BIT		f_low		:	Sys_Flag.1;			//
extern bit     f_key_scan	:	Sys_Flag.2;		//按键扫描
extern bit     f_charging_full:Sys_Flag.3;		//充满
extern bit     f_charging	:	Sys_Flag.4;	
extern bit 		f_heating 	:   Sys_Flag.5;	
extern byte motor_state,motor_state_temp;		//马达工作模式0~7
extern byte motor_state2;
extern byte count;//T16计数
extern byte S1_count,s2_count,s3_count;//按键计数
extern word  motor_time;
extern word motor_time2;
extern byte pwm_num;
extern word pwm_num2;
extern WORD sleep_time;
extern bit pwm_bit;
extern byte rate;
extern byte pwm_duty,pwm_cnt;
extern byte pwm_speed;   
extern byte  pwm_hz; 
extern word led_time,led_time2,pwm_time;
extern byte led_mode,led_mode_temp;
extern byte pir_mode;
extern word pir_time,pir_time2;
extern byte ad_cnt,pwm_time2,pwm_time3;
extern byte s1_lastime;
extern byte hot_mode;
extern byte motor_delcnt;
extern word hot_ad;
extern byte check_cnt;
extern bit  f_low35;
extern byte low_ledtime;
extern byte Suck_mode;
extern byte led_flashtime;
#endif
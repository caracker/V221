void led_init(void);
void led_even(void);
void red_even(void);
void blue_even(void);
void led_breathing(void);
void led_blue_pwm(void);
void led_data_init(void);
 


red_led	equ pb.2
white_led equ pb.1
white_led2 equ pa.6

#define led_on	1
#define led_off 0
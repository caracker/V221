void motor_init(void);
void motor_even(void);

#define motor_on 	tm3c = 0b_0001_01_1_0;	 // ϵͳʱ��, ��� = Pb5, PWM ģʽ
#define motor_off 	tm3c = 0b_0010_00_1_0;	 // ϵͳʱ��, ��� = Pb5, PWM ģʽ



#define motor2_on 	tm2c = 0b_0010_10_1_0;	 // ϵͳʱ��, ��� = Pb5, PWM ģʽ
#define motor2_off 	tm2c = 0b_0010_00_1_0;	 // ϵͳʱ��, ��� = Pb5, PWM ģʽ
#include	"ADC.h"
#include "../../head_extern.h"
static	void	Shifter_K (void);
static	void	Get_AD_By_K (void);
extern byte motor_state_temp;
//ADC
void ADC_init(void)
{
	//io
	$ pb.6 IN,nopull;//PB0没上拉输入
	$ ADCC Enable, pb6; // 设定PB0 当ADC 输入
	$ ADCM 8BIT, /4; // 建议 /16 @系统时钟=8MHz
	ADCRGC=0b_000_0_00_00; //参考vcc

	$ pb.0 out,low;
//	while(1)
	{
//		adc_even();
	}
}
/***************************************************************************/
/*
/*						滑动滤波器
/*
/*
/*
******************************************************************************/
#define	K	3	//	1 ~ 4
static	WORD	AD_Shift, AD_Filter;
static	void	Shifter_K (void)
{
	AD_Shift	=	AD_Filter;
	A			=	K;
	do
	{
		AD_Shift >>= 1;
	} while (--A);
}



DWORD	mul_t4;
WORD	mul_x2;
WORD	mul_y2;
void	Word_Mul_Word (void)
{	//	mul_t4[D]	=	mul_x2[W] * mul_y2[W]
	mul_t4$3	=	0;
	mul_t4$2	=	0;

	BYTE	cnt;
	cnt	=	16;

	do
	{
		mul_x2	>>=	1;
		if (CF)
		{
			mul_t4	+=	(mul_y2 << 16);
		}
		mul_t4	>>>=	1;
	} while (--cnt);
}


DWORD	div_src4;
WORD	div_val2, div_res2;
void	DWord_Div_Word (void)
{	//	div_src4[D] / div_val2[W]	=	div_src4[D] * div_val2[W] + div_res2[W]
	BYTE	div_cnt, div_tmp;
	div_cnt		=	0;
	div_res2	=	0;

	do
	{
		div_src4	<<=		1;
		div_res2	<<<=	1;
		div_tmp		<<<=	1;
		div_cnt++;
		A	=	(div_res2 - div_val2) >> 8;

		if (div_tmp.0 || ! CF)
		{
			div_res2$1	=	A;
			div_res2$0	-=	div_val2$0;
			div_src4.0	=	1;
		}
	} while (! div_cnt.5);
}


WORD Data;
void GET_ADC(void)
{
	AD_START = 1;				 // 开始ADC 转换
	do
	{
		Nop;
	}while (!AD_DONE) ; 		// 等待ADC 转换结果				// 2 字节结果: ADCRH 和ADCRL
//	Data = (ADCRH << 4) | (ADCRL & 0xf0) >> 4;  //12位的AD 转换的结果
	DATA=ADCR;
}

void adc_even(void)
{
	GET_ADC();
	hot_ad=DATA;
}





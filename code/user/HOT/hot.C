#include	"hot.h"
#include "../../head_extern.h"

void hot_init(void)
{
	$ hot_pin out,low;
	$ pb.0 out,low;
}

void hot_even(void)
{
	if(f_heating && !f_charging && f_work)
	{
		if(hot_ad>20 && hot_ad<220)
		{
			/*
			switch(hot_mode)
			{
				case 0:
					hot_pin=0;
					break;
				case 1:
					if(hot_ad<47)  hot_pin=0;
					if(hot_ad>51)  hot_pin=1;
					break;
				case 2:
					if(hot_ad<35)  hot_pin=0;
					if(hot_ad>37)  hot_pin=1;
					break;
				default:
					hot_mode=0;
					break;
			}
			*/
			if(hot_ad<59)  hot_pin=0;
			if(hot_ad>63)  hot_pin=1;
		}
		else
		{
			hot_pin=0;
		}
	}
	else
	{
		hot_pin=0;
	
	}

}
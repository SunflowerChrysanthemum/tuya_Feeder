#include "stm32f10x.h"                  // Device header
#include "sys.h"
#include "Delay.H"
#include "usart.h"
#include "usart3.h"
#include "string.h"
#include "HX711.h"
#include "timer.h"
#include "key.h"

#include "mcu_api.h"
#include "protocol.h"
#include "wifi.h"


//int main()
//{
//	timer3_Init();
//	
//	Rotate_value(3);
//	while(1)
//	{
//		
//	}
//}



int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	usart_init(115200);
	usart3_init(9600);
	wifi_protocol_init();
	KEY_Init();
	LCD_Init();
	timer3_Init();
	
	HX711_Init();
	HX711_Maoqi();
	DelayMs(800);
	HX711_Maoqi();
	
	timer2_Init();
	
	printf("init succeed\r\n");
	while(1)
	{
		wifi_uart_service();
		DelayMs(10);
		
		if(flag_small)
		{
			flag_small = !flag_small;
			LCD_Change();
		}
		if(flag_middle)
		{
			flag_middle = !flag_middle;
			LCD_Change();
		}
		if(flag_big)
		{
			flag_big = !flag_big;
			LCD_Change();
		}
		
		if(KEY1 == RESET)
		{
			DelayMs(20);
			if(KEY1 == RESET)
			{
				mcu_reset_wifi();
				DelayMs(50);
				mcu_set_wifi_mode(SMART_CONFIG);
				printf("SMART_CONFIG\r\n");
			}
			while(!KEY1);
		}
	}
}



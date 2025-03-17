#include "HX711.h"

u32 Weight_Maopi;


uint8_t medleng = 0;         // 当前缓存的数量
uint8_t bufferIndex = 0;
float buffer[MEDIAN_LEN];

void HX711_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


u32 HX711_Read(void)
{
	u32 count;
	uint8_t i;
	HX711_DT_SET;
	DelayUs(1);
	HX711_CLK_CLR;
	count = 0;
	while(HX711_DT_CHECK);
	for(i = 0; i < 24; i++)
	{
		HX711_CLK_SET;
		count = count<<1;
		DelayUs(1);
		HX711_CLK_CLR;
		if(HX711_DT_CHECK)
			count++;
		DelayUs(1);
	}
	HX711_CLK_SET;
	count=count^0x800000;
	DelayUs(1);
	HX711_CLK_CLR;
	return (count);
}

void HX711_Maoqi(void)
{
	Weight_Maopi = HX711_Read();
}


float Get_Weight(void)
{
	float result;
	u32 weight = HX711_Read();
	if(weight <= Weight_Maopi)
	{
		return 0;
	}
	else{
		weight = weight - Weight_Maopi;
		result = (float)(weight / GapValue);
		result = MedianFilter(result);
	}
	
	return result;
}



//卡尔曼滤波
float KalmanFilter(float inData)
{
		static float prevData = 0;                                 //先前数值
		static float p = 10, q = 0.001, r = 0.001, kGain = 0;      // q控制误差  r控制响应速度 
	
		p = p + q;
		kGain = p / ( p + r );                                     //计算卡尔曼增益
		inData = prevData + ( kGain * ( inData - prevData ) );     //计算本次滤波估计值
		p = ( 1 - kGain ) * p;                                     //更新测量方差
		prevData = inData;
		return inData;                                             //返回滤波值
}





void bubbleSort(float *arr, uint8_t len)
{
    for (uint8_t i = 0; i < len - 1; i++) {
        for (uint8_t j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


// 中值滤波函数
float MedianFilter(float newData)
{
    // 将新数据插入到缓冲区
    if (medleng < MEDIAN_LEN) {
        buffer[medleng] = newData;  // 插入数据
        medleng++;
    } else {
        // 覆盖最旧的数据
        buffer[bufferIndex] = newData;
        bufferIndex = (bufferIndex + 1) % MEDIAN_LEN;
    }

    // 排序并返回中位数
    bubbleSort(buffer, MEDIAN_LEN);
    return buffer[MEDIAN];  // 返回排序后的中位数
}



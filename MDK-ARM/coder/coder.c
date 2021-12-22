#include "coder.h"
#include <math.h>
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
uint8_t data[15];
//储存每一个角度的字符串
uint8_t RD;
 int i;
 int cnt = 0;
//储存接收到的单个字符
float angle;
float	readstring (uint8_t *rxbuffer);
//定义一个解包函数
__weak void coder(void const * argument)
{   
    HAL_UART_Receive_DMA(&huart1,&RD,1);
//进入回调函数
  while(1)
   {
   }
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin);

 
    if (cnt == 1)
    {
      data[i] = RD;
      i++;
    }
    if (RD == 0x0A)
    {
      data[0] = RD; 
      i = 1;
      cnt = 1;
    }
    //逐个读取字符储存在data数组中
		if (RD == 0x0D)
    {
      data[i] = RD;
      angle = readstring(data);
    //通过readstring()函数解包data中的数据
    cnt=0;
    }
   //cnt = (int)((1500/360)*angle);
  // __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 500+(cnt));
   
    HAL_UART_Receive_DMA(&huart1,&RD,1);
   //再次使用DMA进入回调函数
}


float	readstring (uint8_t *rxbuffer)
{
  float str = 0;//返回的变量
	int cnt = -1;
	int flag = 0;//做标记位，判断有无小数点
	for(int i = 7;i<15;i++)//15是因为创建了一个15的数组来存放数据，可根据自己情况改变
	{
    if (rxbuffer[i] == 0x0D)
    {
        break;
    }
    //如果为 0x0D 则数据段结束，退出转换

		if(rxbuffer[i]== 0x2E)//记录小数点位置
		{
			flag =1;
			i++;
      //记录此时的位置
		}

    if (flag == 0)
    {
      str = str*10+(rxbuffer[i]-'0');
    }
     //如果flag为0则为整数部分
    if (flag == 1)
    {
      str = str+(rxbuffer[i]-'0')*pow(10,cnt) ;
      cnt--;
    }
     //如果flag为1则为
	}
	return str;
}



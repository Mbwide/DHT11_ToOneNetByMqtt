
/*-----------------------------------------------------*/
/*                                                     */
/*         		  	  延时函数                         */
/*                                                     */
/*-----------------------------------------------------*/

#include "delay.h"

static u8  fac_us = 0;						//us延时倍乘数			   
static u16 fac_ms = 0;						//ms延时倍乘数

/*-------------------------------------------------*/
/*函数名：延时初始化                    	           */
/*参  数：无                                        */
/*返回值：无                                        */
/*-------------------------------------------------*/
void Delay_Init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	fac_us = SystemCoreClock/8000000;				 
	fac_ms = (u16)fac_us*1000;					
}	 

/*-------------------------------------------------*/
/*函数名：us延时                    			    */
/*参  数  us                                       */
/*返回值：无                                        */
/*-------------------------------------------------*/
void DelayUs(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD = nus*fac_us; 			   //时间加载	  		 
	SysTick->VAL = 0x00;        			   //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ; //开始倒数	  
	
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));	   //等待时间到达 
	
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //关闭计数器
	SysTick->VAL = 0X00;      				   //清空计数器	 
}

/*-------------------------------------------------*/
/*函数名：ms延时                    			    */
/*参  数  ms                                       */
/*返回值：无                                        */
/*-------------------------------------------------*/
void DelayMs(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD = (u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL = 0x00;						//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	
	do
	{
		temp = SysTick->CTRL;
	}while((temp&0x01) && !(temp&(1<<16)));		//等待时间到达 
	
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL = 0X00;       					//清空计数器	  	    
} 










































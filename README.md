# DHT11_ToOneNetByMqtt

**简介：** ESP8266通过MQTT协议将温湿度数据传输至OnenNet云平台

**具体功能：**

1.  DHT11采集环境温湿度数据，ESP8266模块通过MQTT协议将温湿度数据传输至OnenNet云平台
2.  OneNET可以通过云平台远程控制LED灯的亮灭
3.  串口显示相关数据信息

**硬件环境：**

1. 正点原子STM32F103RCT6（正点原子MiniSTM32）
2. DHT11温湿度传感器
3. ESP8266-01S无线模块

**接线：**

1. ESP8266-01S（5根线）

   - PA2     RX
   - PA3     TX
   - PA4     复位
   - 3V3     VCC
   - GND   GND

2. DHT11（3根线）

   - PA6    DATA

   - 3V3     VCC

   - GND   GND

3. LED
   - PD2    LED1

**要修改的的地方：**

1. 

​     

​     
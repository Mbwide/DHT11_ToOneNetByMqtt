# DHT11_ToOneNetByMqtt

**简介：** ESP8266通过MQTT协议将温湿度数据传输至OnenNet云平台

#### 1. 相关连接：

1. github（源码）： https://github.com/Mbwide/DHT11_ToOneNetByMqtt
2. CSDN：（图文解析）：https://blog.csdn.net/ssssadw/article/details/111584510
3. Bilibili（视频解析）：https://www.bilibili.com/video/BV1Vi4y1w7U1

#### 2. 具体功能：

1.  DHT11采集环境温湿度数据，ESP8266模块通过MQTT协议将温湿度数据传输至OnenNet云平台
2.  OneNET可以通过云平台远程控制LED灯的亮灭
3.  串口显示相关数据信息

#### 3. 硬件环境：

1. 正点原子STM32F103RCT6（正点原子MiniSTM32）
2. DHT11温湿度传感器
3. ESP8266-01S无线模块

#### 4. 云平台环境配置：

1. **云平台配置：**
- OneNET控制台—全部产品服务（多协议接入，选MQTT旧版）—添加产品—进入产品（记住产品ID）—设备列表—添加设备（记住鉴权信息）—创建完成（记住设备ID）
  
2. **云平台应用设置：**
- 添加应用—编辑应用—组件库中添加折线图和开关
  
- 折线图（数据上传成功后进行配置）: 选择数据流 — 选择设备—数据流选择要显示的数据（这里选择温度，temperature）
   - 开关（数据上传成功后进行配置）: 选择数据流 — 选择设备—数据流选择要显示的数据（这里选择温度，ledFlag）—开关开值（LEDON）—开关关值（LEDOFF）——EDP不填

#### 5. 接线：

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

#### 6. 功能展示：

1. **数据流**![image-20201223113457360](./images/data.png)

2. **APP应用管理**

   ![image-20201223113558021](./images/APP.png)

3. **串口数据**

   ![image-20201223113700277](./images/serial.png)

4. **源码简要解析**

   ![image-20201223113912384](./images/code.png)

   - stm32f10x_it.c：中断处理函数
   - usart1.c：与上位机通信
   - usart2.c：与ESP8266通信，串口2接收中断处理上位机发送来的数据
   - timer2.c：定时器2中断用来发送温湿度数据，10S
   - timer3.c：定时器3中断用来发送心跳包（ping，用于保持和服务器连接，长时间没给服务器发送数据会被踢下线），2s和30s两种模式
   - timer4.c：将串口2接收到的服务器数据依次存放在MQTT接收缓存数组中，50ms
   - control.c：控制LED灯，并且发送LED灯开关信号

#### 7. 要修改的的地方：

1. mqtt.h ：

   ```c
   #define  PRODUCTID      "393773"          //自己的产品ID
   #define  DEVICEID       "660024974"       //自己的设备ID 
   #define  AUTHENTICATION  "123456"         //自己的鉴权信息（创建设备的时候设置）
   ```
   
   ![./image-20201223112140673](./images/__MQTT_H.png)
   
2. wifi.h

   ```c
    #define SSID   "PPP"                     //路由器SSID名称
    #define PASS   "qaz123qaz"               //路由器密码
   ```

   ![__WIFI_H](./images/__WIFI_H.png)

3. mqtt.c

   ```c
   sprintf(ServerIP,"%s","183.230.40.39");              //构建服务器域名（ONENET的）
   ServerPort = 6002;                                   //服务器端口号6002
   ```

   根据平台地址列表填写，这里是mqtt协议

   ![image-20201223113142935](./images/address.png)

   ![image-20201223112902671](./images/__MQTT_C.png)

   


#ifndef ct511__h
#define ct511__h
#include "string.h"
#include "stdio.h"
#include "usart.h"

//设置ATCONFIG的连接参数 分别对应 设备名称(随意)  设备账号  设备密码
void setATCONFIG(char *clientId,char *account ,char* password);

//设置连接的mqtt网址以及端口好
void setUrlAndPort(char *url,unsigned int port);

//发送at命令到传感器 需要先设置参数
void init_ct511(void);

void quickUsart(UART_HandleTypeDef* h,char*message);

//连接后 设置订阅命令
void setATSUB( char *topic) ;

//发送数据至Mqtt服务器
void sendMqtt(char *topic,char *message);

extern char ct511Data[];
#endif

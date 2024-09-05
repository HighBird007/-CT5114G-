#ifndef ct511__h
#define ct511__h
#include "string.h"
#include "stdio.h"
#include "usart.h"

//发送at命令到传感器
void init_ct511(void);
//发送数据到对应的mqtt服务器
void sendMqtt(char *topic,char *message);
//设置ATCONFIG的连接参数 分别对应 设备名称(随意)  设备账号  设备密码
void setATCONFIG(char *clientId,char *account ,char* password);
extern char ct511Data[];

#endif

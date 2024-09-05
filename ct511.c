#include "ct511.h"
#include "stdlib.h"
char ct511Data[100];
char senddata[50];
char atApnCommand[] = "AT+QICSGP=1,1,\"\",\"\",\"\"\r\n";
char atNetOpenCommand[] = "AT+NETOPEN\r\n";
char atConfigCommand[200];  
char atStartCommand[200];
char atConnectCommand[] = "AT+MCONNECT=1,60\r\n";
char atSubCommand[50]; 
char atPubCommand[300];

void quickUsart(UART_HandleTypeDef* h,char*message){
	HAL_UART_Transmit(h,(uint8_t*)message,strlen(message),1000);
}

// 设置配置命令
void setATCONFIG( char *clientId,  char *account,  char *password) {
    sprintf(atConfigCommand, "AT+MCONFIG=\"%s\",\"%s\",\"%s\"\r\n", clientId, account, password);
}
//设置连接的mqtt网址以及端口好
void setUrlAndPort(char *url,unsigned int port){
	sprintf(atStartCommand, "AT+MIPSTART=\"%s\",%d\r\n",url,port);
}
//流程  1.发送apn 2.发送netopen 3.发送给config也就是设备的id 以及登录的账号密码  4.发送startcommand  里面是连接的网址以及端口好 不支持ssl tls连接 5.开启连接
void init_ct511(void) {
	
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t*)ct511Data, 100);
	//1.发送apn
    quickUsart(&huart3, atApnCommand);
    HAL_Delay(2000);
	//2.发送netopen
    quickUsart(&huart3, atNetOpenCommand);
    HAL_Delay(4000);
	//3.发送给config也就是设备的id 以及登录的账号密码
    quickUsart(&huart3, atConfigCommand); 
	HAL_Delay(2000);
	//4.发送startcommand 里面是连接的网址以及端口好 不支持ssl tls连接
    quickUsart(&huart3, atStartCommand); 
	HAL_Delay(2000);
	//5.开启连接
    quickUsart(&huart3, atConnectCommand); 
	HAL_Delay(100);
}

// 设置订阅命令
void setATSUB( char *topic) {
    sprintf(atSubCommand, "AT+MSUB=\"%s\",0\r\n", topic);
}
//发送数据至Mqtt服务器
void sendMqtt(char *topic,char *message){
	 sprintf(atPubCommand, "AT+MPUB=\"%s\",0,0,\"%s\"\r\n", topic, message);
	quickUsart(&huart3,atPubCommand);
}


#ifndef DEF_CONST
#define DEF_CONST
#include <stdio.h>
#include <QDebug>
#define DEBUG
#define J_userName "userName"
#define J_password "password"
#define J_phoneNumber "phoneNumber"
#define J_userToken "userToken"
#define J_stateCode "stateCode"
#define J_temperature "temperature"
#define J_humidity "humidity"
#define J_light "light"
#define J_deviceNumber "deviceNumber"
#define J_deviceCode "deviceCode"
#define J_deviceState deviceState
#define APP_TO_A9 0xaa
#define A9_TO_APP ~(0x00)
#define LOGIN 0x01
#define CTLDOOR 0x0a
#define CTLFAN 0x09
#define CTLLED 0x08
#define CTLTEMP 0x04
#define CTLHUM 0x05
#define CTLLUX 0x06

#define PACKETLEN 1024

#define MSGTYPESITE 0
#define MSGNUMSITE 1
#define MSGLENSITE0 2
#define MSGLENSITE1 3
#define MSGJSONSITE 4
#ifdef DEBUG
#define DBUG_OUT qDebug("[%s,%s,%d]",__FILE__,__FUNCTION__,__LINE__)

#endif

extern QString userToken;

#endif // DEF_CONST


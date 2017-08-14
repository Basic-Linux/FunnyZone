#ifndef BC_SERIALPORT_H
#define BC_SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>
#include "selfdef.h"
class bc_serialPort : public QObject
{
    Q_OBJECT
public:
    explicit bc_serialPort(QObject *parent = 0);
    ~bc_serialPort();

    QByteArray readPort();
    void writePort(QByteArray array);

    //自动获取当前设备上的串口
    void setPort(int baudRate,
                 QSerialPort::DataBits dataBits = QSerialPort::Data8,
                 QSerialPort::StopBits stopBits = QSerialPort::OneStop,
                 QSerialPort::Parity parity = QSerialPort::NoParity,
                 QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl);

    void startCheckClock();

    void stopCheckClock();

public slots:
    void slotTimeOut();

signals:

private:
    QSerialPort *serial;
    //设置一个时钟计时器 用来检测端口是否断开，如果断开则弹出提示框
    QTimer *timer;
};


#endif // BC_SERIALPORT_H

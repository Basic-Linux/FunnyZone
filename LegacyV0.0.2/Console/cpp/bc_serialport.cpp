#include "bc_serialport.h"

bc_serialPort::bc_serialPort(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(parent);
    timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
}

bc_serialPort::~bc_serialPort()
{
    delete timer;
    delete serial;
}

QByteArray bc_serialPort::readPort()
{
    QByteArray array = serial->readAll();
    if(array.isEmpty())
        qDebug() << "empty serial";
    return array;
}

void bc_serialPort::writePort(QByteArray array)
{
    if(-1 == serial->write(array))
    {
        QMessageBox::warning(0,"serial error",serial->errorString());
        //QCoreApplication::instance()->exit(-1);
    }
}

void bc_serialPort::setPort(int baudRate,
                            QSerialPort::DataBits dataBits,
                            QSerialPort::StopBits stopBits,
                            QSerialPort::Parity parity,
                            QSerialPort::FlowControl flowControl)
{
    QString portName;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        portName = info.portName();

    serial->close();

    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(dataBits);
    serial->setStopBits(stopBits);
    serial->setParity(parity);
    serial->setFlowControl(flowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(0,"serial open error",serial->errorString());
    }
    qDebug() << "serial name = " << serial->portName() << "is open!";
}



void bc_serialPort::startCheckClock()
{
    timer->start(INTERVER_Port);
}

void bc_serialPort::stopCheckClock()
{
    timer->stop();
}

void bc_serialPort::slotTimeOut()
{
    QSerialPortInfo info(serial->portName());
    QString result = info.description();
    if(result.isEmpty())
    {
        QMessageBox::warning(0,"serial error","serial is not work,we are changing port!");
        setPort(Baudrate);
    }
}



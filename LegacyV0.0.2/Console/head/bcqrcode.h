#ifndef QRCODE_H
#define QRCODE_H

#include <QString>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "qrencode_inner.h"
#include "qrspec.h"
#include "mqrspec.h"
#include "qrinput.h"
#include "mask.h"
#include "rscode.h"
#include "split.h"
#include "tests/decoder.h"
#include <QImage>
#include <QPainter>
class MQRcode
{
public:
    static QImage GenerateQRcodeImage(QString tempstr,QSize PixSize)
    {
        QRcode *qrcode = QRcode_encodeString(tempstr.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 0);
        qint32 temp_width=PixSize.width(); //二维码图片的大小
        qint32 temp_height=PixSize.height();
        qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
        double scale_x = (double)temp_width / (double)qrcode_width; //二维码图片的缩放比例
        double scale_y =(double) temp_height /(double) qrcode_width;
        QImage mainimg=QImage(temp_width,temp_height,QImage::Format_ARGB32);
        QPainter painter(&mainimg);
        QColor background(Qt::white);
        painter.setBrush(background);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, temp_width, temp_height);
        QColor foreground(Qt::black);
        painter.setBrush(foreground);
        for( qint32 y = 0; y < qrcode_width; y ++)
        {
            for(qint32 x = 0; x < qrcode_width; x++)
            {
                unsigned char b = qrcode->data[y * qrcode_width + x];
                if(b & 0x01)
                {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
                }
            }
        }
        return mainimg;
    }
};

#endif // QRCODE_H

﻿#ifndef FUNCTOTEXT_H
#define FUNCTOTEXT_H

#include "globaldefine.h"

QString spiToText(uchar ch);
QString dpiToText(uchar ch);
QString scsToText(uchar ch);
QString dcsToText(uchar ch);
QString blToText(uchar ch);
QString sbToText(uchar ch);
QString ntToText(uchar ch);
QString ivToText(uchar ch);
QString ovToText(uchar ch);
QString qoiToText(uchar ch);
QString coiToText(uchar ch);
QString rqtToText(uchar ch);
QString frzToText(uchar ch);
QString suToText(uchar ch);
QString quToText(uchar ch);
QString seToText(uchar ch);
QString caToText(uchar ch);
QString cyToText(uchar ch);
QString vtiToText(uchar ch);
QString qosToText(uchar ch);
QString timeToText(char *time, int timelen);
QString timeToText(uchar *time ,int timelen);

#endif // FUNCTOTEXT_H
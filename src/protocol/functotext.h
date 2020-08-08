#ifndef FUNCTOTEXT_H
#define FUNCTOTEXT_H

#include "globaldefine.h"

QString prmToText(uchar ch);
QString fcbToText(uchar ch);
QString fcvToText(uchar ch);
QString acdToText(uchar ch);
QString dfcToText(uchar ch);
QString cw1ToText(uchar ch);
QString cw2ToText(uchar ch);

QString spiToText(uchar ch);
QString dpiToText(uchar ch);
QString dpiteToText(uchar ch);
QString scsToText(uchar ch);
QString dcsToText(uchar ch);
QString blToText(uchar ch);
QString sbToText(uchar ch);
QString ntToText(uchar ch);
QString ivToText(uchar ch);
QString ovToText(uchar ch);
QString erToText(uchar ch);
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
QString timeToText(const char *time, int timelen);
QString timeToText(uchar *time ,int timelen);

QString ngdToText(uchar ch);
QString nogToText(uchar ch);
QString kodToText(uchar ch);
QString gdd1ToText(uchar ch);
QString gdd3ToText(uchar ch);
QString grcToText(uchar ch);
#endif // FUNCTOTEXT_H

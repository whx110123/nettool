#include "myhighlighter.h"
#include <QString>

myhighlighter::myhighlighter(QTextDocument *parent):QSyntaxHighlighter(parent)
{

}

void myhighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myformat1;
    myformat1.setFontWeight(QFont::Bold);
    myformat1.setForeground(Qt::red);
    QTextCharFormat myformat2;
    myformat2.setFontWeight(QFont::Bold);
    myformat2.setForeground(Qt::blue);
    myformat2.setFontPointSize(14);
    QStringList patlis1;
    patlis1  <<"OV(bit1):1 溢出"
           <<"BL(bit5):1 被闭锁"
          <<"SB(bit6):1 被取代"
         <<"NT(bit7):1 非当前值"
        <<"IV(bit8):1 无效"
       <<"否定确认"
      <<"试验状态"
     <<"未知，无法识别当前的传送原因"
    <<"未完成此ASDU剩余报文的解析"
    <<"出错！"
    <<"CA(bit7):1 上次读数后计数器被调整"
    <<"CY(bit6):1 在相应的累加周期内计数器溢出"
    <<"ER(bit2):1 被测值无效";

    QStringList patlis2;
    for (int i = 1;i<20;i++)
    {
        patlis2  <<QString("####第%1帧####").arg(i);
    }


    for (int i = 0;i <patlis1.size();i++)
    {
        QString pattern = patlis1.at(i);
        int length = pattern.length();
        int index = text.indexOf(pattern);
        while (index >=0)
        {
            setFormat(index,length,myformat1);
            index = text.indexOf(pattern,index+length);

        }
    }
    for (int i = 0;i <patlis2.size();i++)
    {
        QString pattern = patlis2.at(i);
        int length = pattern.length();
        int index = text.indexOf(pattern);
        while (index >=0)
        {
            setFormat(index,length,myformat2);
            index = text.indexOf(pattern,index+length);

        }
    }
}

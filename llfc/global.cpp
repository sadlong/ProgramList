#include "global.h"

QString gate_url_prefix = "";

std::function<void(QWidget*)> repolish = [](QWidget* w) {
    w->style()->unpolish(w);
    w->style()->polish(w);
};

std::function<QString(QString)> xorString = [](QString input) {
    //复制原始字符串 以便进行修改
    QString result = input;
    //获取字符串的长度
    int length = input.length();
    length = length%255;    //char是一个字节 2^8=256
    for(int i = 0; i < length; i++) {
        result[i] = QChar(static_cast<ushort>(input[i].unicode() ^ static_cast<ushort>(length)));
    }
    return result;
};

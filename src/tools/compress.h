#ifndef COMPRESS_H
#define COMPRESS_H

#include <QByteArray>

class Compress
{
public:
    static QByteArray gunzip(const QByteArray &data);
};

#endif // COMPRESS_H

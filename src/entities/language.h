#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>


struct Language {
    QString color;
    QString name;

    Language &operator=(const Language &) = default;
};

#endif // LANGUAGE_H

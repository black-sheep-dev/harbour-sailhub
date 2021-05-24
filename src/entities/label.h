#ifndef LABEL_H
#define LABEL_H

#include <QObject>

#include <QDateTime>

struct LabelListItem {
    LabelListItem() = default;
    LabelListItem(const QJsonObject &obj);

    QString color;
    QDateTime createdAt;
    QString name;
};

class Label : public QObject
{
    Q_OBJECT

public:
    enum LabelType {
        Undefined,
        Issue,
        PullRequest,
        Repository
    };
    Q_ENUM(LabelType)

    explicit Label(QObject *parent = nullptr);
};

#endif // LABEL_H

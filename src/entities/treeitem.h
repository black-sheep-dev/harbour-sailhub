#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>

struct TreeItemListItem {
    QString name;
    QString path;
    quint8 type{0};
};

class TreeItem : public QObject
{
    Q_OBJECT
public:
    enum Type {
        Undefined,
        Blob,
        Tree
    };
    Q_ENUM(Type)

    explicit TreeItem(QObject *parent = nullptr);

signals:

};

#endif // TREEITEM_H

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>

struct TreeItemListItem {
    QString extension;
    quint8 fileType{0};
    QString name;
    QString path;
    quint8 type{0};
};

class TreeItem : public QObject
{
    Q_GADGET

public:    
    enum Type {
        Undefined,
        Blob,
        Tree
    };
    Q_ENUM(Type)
};

#endif // TREEITEM_H

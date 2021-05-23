#include "label.h"

#include <QJsonObject>

#include "src/api/keys.h"

// List Item
LabelListItem::LabelListItem(const QJsonObject &obj)
{
    color = obj.value(ApiKey::COLOR).toString();
    createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    name = obj.value(ApiKey::NAME).toString();
}

// Object
Label::Label(QObject *parent) :
    QObject(parent)
{

}



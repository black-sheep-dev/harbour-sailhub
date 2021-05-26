#include "label.h"

#include <QJsonObject>

#include "src/api/keys.h"

// List Item
LabelListItem::LabelListItem(const QJsonObject &data)
{
    color = data.value(ApiKey::COLOR).toString();
    createdAt = QDateTime::fromString(data.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    name = data.value(ApiKey::NAME).toString();
}

// Object
Label::Label(QObject *parent) :
    QObject(parent)
{

}



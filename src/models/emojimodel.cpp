#include "emojimodel.h"

//#include <QDebug>
#include <QFile>
#include <QTextStream>

EmojiModel::EmojiModel(QObject *parent) :
    QAbstractListModel(parent)
{
   loadEmoji();
}

void EmojiModel::loadEmoji()
{
    beginResetModel();

    QFile file("/usr/share/harbour-sailhub/data/emoji.def");

    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        m_emoji << in.readLine().simplified();
    }

    file.close();


    endResetModel();
}

int EmojiModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_emoji.count();
}

QVariant EmojiModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto &emoji = m_emoji[index.row()];

    switch (role) {
    case NameRole:
        return emoji;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> EmojiModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[NameRole]     = "name";

    return roles;
}

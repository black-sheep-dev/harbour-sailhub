#include "emojimodel.h"

//#include <QDebug>
#include <QDir>
#include <QFileInfo>

EmojiModel::EmojiModel(QObject *parent) :
    QAbstractListModel(parent)
{
   loadEmoji();
}

void EmojiModel::loadEmoji()
{
    beginResetModel();

    QDir dir(QStringLiteral("/usr/share/harbour-sailhub/twemoji/svg"));

    for (const auto &file : dir.entryList(QDir::Files, QDir::Name) ) {
        QFileInfo info(file);

        if (info.baseName().isEmpty())
            continue;

        m_emoji.append(info.baseName());
    }

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

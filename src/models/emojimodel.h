#ifndef EMOJIMODEL_H
#define EMOJIMODEL_H

#include <QAbstractListModel>

class EmojiModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum EmojiRoles {
        NameRole    = Qt::UserRole + 1
    };
    Q_ENUM(EmojiRoles)

    explicit EmojiModel(QObject *parent = nullptr);

private:
    void loadEmoji();

    QStringList m_emoji;


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // EMOJIMODEL_H

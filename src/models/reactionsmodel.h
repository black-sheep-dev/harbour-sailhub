#ifndef REACTIONSMODEL_H
#define REACTIONSMODEL_H

#include <QAbstractListModel>

#include "src/entities/reaction.h"

class ReactionsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(quint8 viewerReactions READ viewerReactions WRITE setViewerReactions NOTIFY viewerReactionsChanged)

public:
    enum ReactionRoles {
        CountRole           = Qt::UserRole + 1,
        TypeRole,
        ViewerReactedRole
    };
    Q_ENUM(ReactionRoles)

    explicit ReactionsModel(QObject *parent = nullptr);

    void setReactions(const QList<ReactionListItem> &reactions);

    // properties
    quint8 viewerReactions() const;

signals:
    // properties
    void viewerReactionsChanged(quint8 reactions);

public slots:
    // properties
    void setViewerReactions(quint8 reactions);

private:
    QList<ReactionListItem> m_reactions;

    // properties
    quint8 m_viewerReactions{Reaction::None};

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // REACTIONSMODEL_H

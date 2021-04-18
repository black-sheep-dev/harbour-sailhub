#include "reactionsmodel.h"

ReactionsModel::ReactionsModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

void ReactionsModel::setReactions(const QList<ReactionListItem> &reactions)
{
    beginResetModel();
    m_reactions.clear();
    m_reactions = reactions;
    endResetModel();

    quint8 viewerReactions{Reaction::None};
    for (const auto &reaction : reactions) {
        if (!reaction.viewerReacted)
            continue;

        viewerReactions |= reaction.type;
    }

    setViewerReactions(viewerReactions);
}

quint8 ReactionsModel::viewerReactions() const
{
    return m_viewerReactions;
}

void ReactionsModel::setViewerReactions(quint8 reactions)
{
    if (m_viewerReactions == reactions)
        return;

    m_viewerReactions = reactions;
    emit viewerReactionsChanged(m_viewerReactions);
}

int ReactionsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_reactions.count();
}

QVariant ReactionsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto reaction = m_reactions.at(index.row());

    switch (role) {
    case CountRole:
        return reaction.count;

    case TypeRole:
        return reaction.type;

    case ViewerReactedRole:
        return reaction.viewerReacted;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReactionsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CountRole]            = "count";
    roles[TypeRole]             = "type";
    roles[ViewerReactedRole]    = "viewerReacted";

    return roles;
}

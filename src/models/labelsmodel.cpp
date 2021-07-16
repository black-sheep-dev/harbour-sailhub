#include "labelsmodel.h"

#include <QJsonArray>

#include "src/api/datautils.h"
#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/api/query_items.h"

// GET NODE LABELS
static const QString SAILHUB_QUERY_GET_NODE_LABELS =
        QStringLiteral("query("
                       "        $nodeId: ID!, "
                       "        $orderField: LabelOrderField = NAME, "
                       "        $orderDirection: OrderDirection = ASC, "
                       "        $itemCount: Int = 20, "
                       "        $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on %3 {"
                       "            id"
                       "            labels("
                       "                    first: $itemCount, "
                       "                    after: $itemCursor, "
                       "                    orderBy: { "
                       "                        direction: $orderDirection, "
                       "                        field: $orderField"
                       "                    } ) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_LABEL_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

LabelsModel::LabelsModel(QObject *parent) :
    PaginationModel(parent)
{
    setSortRole(NameRole);
    setSortOrder(Qt::AscendingOrder);
}

LabelsModel::~LabelsModel()
{
    m_labels.clear();
}

void LabelsModel::addLabels(const QList<LabelListItem> &labels)
{
    beginInsertRows(QModelIndex(), m_labels.count(), m_labels.count() + labels.count() - 1);
    m_labels.append(labels);
    endInsertRows();
}

void LabelsModel::setLabels(const QList<LabelListItem> &labels)
{
    beginResetModel();
    m_labels.clear();
    m_labels = labels;
    endResetModel();
}

int LabelsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_labels.count();
}

QVariant LabelsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto label = m_labels.at(index.row());

    switch (role) {
    case ColorRole:
        return label.color;

    case CreatedAtRole:
        return label.createdAt;

    case NameRole:
        return label.name;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LabelsModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ColorRole]        = "color";
    roles[CreatedAtRole]    = "createdAt";
    roles[NameRole]         = "name";

    return roles;
}

void LabelsModel::clear()
{
    beginResetModel();
    m_labels.clear();
    endResetModel();
}

void LabelsModel::parseQueryResult(const QJsonObject &data)
{
    const QJsonObject labels = data.value(ApiKey::NODE).toObject()
                                  .value(ApiKey::LABELS).toObject();
    const QJsonValue count = labels.value(ApiKey::TOTAL_COUNT);

    setPageInfo(DataUtils::pageInfoFromJson(labels, count));

    // read label items
    QList<LabelListItem> items;

    const QJsonArray nodes = labels.value(ApiKey::NODES).toArray();

    for (const auto &node : nodes) {
        const QJsonObject label = node.toObject();
        if (label.isEmpty())
            continue;

        items.append(LabelListItem(label));
    }

    addLabels(items);

    setLoading(false);
}

GraphQLQuery LabelsModel::query() const
{
    GraphQLQuery query;

    // query
    switch (modelType()) {
    case Label::Issue:
        query.query = SAILHUB_QUERY_GET_NODE_LABELS.arg(QStringLiteral("Issue"));
        break;

    case Label::PullRequest:
        query.query = SAILHUB_QUERY_GET_NODE_LABELS.arg(QStringLiteral("PullRequest"));
        break;

    case Label::Repository:
        query.query = SAILHUB_QUERY_GET_NODE_LABELS.arg(QStringLiteral("Repository"));
        break;

    default:
        break;
    }

    // variables
    query.variables = defaultQueryVariables();

    return query;
}

QString LabelsModel::sortField() const
{
    switch (sortRole()) {
    case LabelsModel::CreatedAtRole:
        return QStringLiteral("CREATED_AT");

    default:
        return QStringLiteral("NAME");
    }
}

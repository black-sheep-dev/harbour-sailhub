#include "treemodel.h"

#include "src/api/datautils.h"
#include "src/api/queryvars.h"

// GET REPOSITORY FILES
static const QString SAILHUB_QUERY_GET_REPOSITORY_FILES =
        QStringLiteral("query($nodeId: ID!, $branch: String!, $path: String!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            ref(qualifiedName: $branch) {"
                       "                target {"
                       "                    ... on Commit {"
                       "                        file(path: $path) {"
                       "                            object {"
                       "                                ... on Tree {"
                       "                                    entries {"
                       "                                        extension"
                       "                                        name"
                       "                                        path"
                       "                                        type"
                       "                                        object {"
                       "                                            ... on Blob {"
                       "                                                isBinary"
                       "                                            }"
                       "                                        }"
                       "                                    }"
                       "                                }"
                       "                            }"
                       "                        }"
                       "                    }"
                       "                }"
                       "            }"
                       "        }"
                       "    }"
                       "}").simplified();

TreeModel::TreeModel(QObject *parent) :
    BaseModel(parent)
{

}

void TreeModel::setItems(const QList<TreeItemListItem> &items)
{
    beginResetModel();
    m_items.clear();
    m_items = items;
    endResetModel();

    setLoading(false);
}

QString TreeModel::branch() const
{
    return m_branch;
}

QString TreeModel::path() const
{
    return m_path;
}

void TreeModel::setBranch(const QString &branch)
{
    if (m_branch == branch)
        return;

    m_branch = branch;
    emit branchChanged(m_branch);
}

void TreeModel::setPath(const QString &path)
{
    if (m_path == path)
        return;

    m_path = path;
    emit pathChanged(m_path);
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = m_items.at(index.row());

    switch (role) {
    case NameRole:
        return item.name;

    case PathRole:
        return item.path;

    case TypeRole:
        return item.type;

    case ExtensionRole:
        return item.extension;

    case FileTypeRole:
        return item.fileType;

    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ExtensionRole]        = "extension";
    roles[FileTypeRole]         = "fileType";
    roles[NameRole]             = "name";
    roles[PathRole]             = "path";
    roles[TypeRole]             = "type";

    return roles;
}

void TreeModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}

void TreeModel::parseQueryResult(const QJsonObject &data)
{
    setItems(DataUtils::treeListItemsFromJson(data));
}

GraphQLQuery TreeModel::query() const
{
    GraphQLQuery query;
    query.variables.insert(QueryVar::NODE_ID, identifier());
    query.variables.insert(QueryVar::BRANCH, m_branch);
    query.variables.insert(QueryVar::PATH, m_path);

    query.query = SAILHUB_QUERY_GET_REPOSITORY_FILES;

    return query;
}

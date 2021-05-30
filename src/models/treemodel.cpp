#include "treemodel.h"

#include <QJsonArray>

#include "src/api/keys.h"
#include "src/api/queryvars.h"
#include "src/entities/file.h"

// GET COMMIT FILES
static const QString SAILHUB_QUERY_GET_COMMIT_FILES =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Commit {"
                       "            id"
                       "            tree {"
                       "                entries {"
                       "                    extension"
                       "                    name"
                       "                    path"
                       "                    type"
                       "                    object {"
                       "                        ... on Blob {"
                       "                            isBinary"
                       "                        }"
                       "                    }"
                       "                }"
                       "            }"
                       "        }"
                       "    }"
                       "}").simplified();

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
    QJsonArray entries;

    switch (modelType()) {
    case Commit:
        entries = data.value(ApiKey::NODE).toObject()
                .value(ApiKey::TREE).toObject()
                .value(ApiKey::ENTRIES).toArray();
        break;

    default:
        entries = data.value(ApiKey::NODE).toObject()
                .value(ApiKey::REF).toObject()
                .value(ApiKey::TARGET).toObject()
                .value(ApiKey::FILE).toObject()
                .value(ApiKey::OBJECT).toObject()
                .value(ApiKey::ENTRIES).toArray();
        break;
    }

    QList<TreeItemListItem> items;

    for (const auto &entry : entries) {
        const QJsonObject obj = entry.toObject();

        TreeItemListItem item;

        item.name = obj.value(ApiKey::NAME).toString();
        item.path = obj.value(ApiKey::PATH).toString();
        item.extension = obj.value(ApiKey::EXTENSION).toString();

        const QString type = obj.value(ApiKey::TYPE).toString();

        if (type == QLatin1String("tree")) {
            item.type = TreeItem::Tree;
            items.append(item);
            continue;
        }

        if (type == QLatin1String("blob")) {
            item.type = TreeItem::Blob;

            if (obj.value(ApiKey::OBJECT).toObject().value(ApiKey::IS_BINARY).toBool()) {

                // image files
                QRegExp regex;
                regex.setPattern(".(jpg|png|gif|jpeg|ico|bmp)");

                if (regex.exactMatch(item.extension)) {
                    item.fileType = File::Image;
                    items.append(item);
                    continue;
                }

                // else binary
                item.fileType = File::Binary;
                items.append(item);
                continue;
            }

            // SVG file
            QRegExp regex;
            regex.setPattern(".(svg)");

            if (regex.exactMatch(item.extension)) {
                item.fileType = File::Image;
                items.append(item);
                continue;
            }

            // Markdown
            regex.setPattern(".(md)");

            if (regex.exactMatch(item.extension)) {
                item.fileType = File::Markdown;
                items.append(item);
                continue;
            }

            item.fileType = File::Text;
        }

        items.append(item);
    }

    setItems(items);
}

GraphQLQuery TreeModel::query() const
{
    GraphQLQuery query;

    switch (modelType()) {
    case Commit:
        query.query = SAILHUB_QUERY_GET_COMMIT_FILES;
        break;

    default:
        query.query = SAILHUB_QUERY_GET_REPOSITORY_FILES;
        query.variables.insert(QueryVar::BRANCH, m_branch);
        query.variables.insert(QueryVar::PATH, m_path);
        break;
    }

    query.variables.insert(QueryVar::NODE_ID, identifier());

    return query;
}

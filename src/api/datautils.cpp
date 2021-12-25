#include "datautils.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>
#include <QTextStream>

#include "keys.h"

QList<NotificationListItem> DataUtils::notificationsFromJson(const QJsonArray &array)
{
    QList<NotificationListItem> items;

    for (const auto &value : array) {
        const QJsonObject obj = value.toObject();

        NotificationListItem item;

        item.id = obj.value(ApiKey::ID).toString();
        item.lastReadAt = QDateTime::fromString(obj.value(RestApiKey::LAST_READ_AT).toString(), Qt::ISODate);

        // reason
        const QString reason = obj.value(RestApiKey::REASON).toString();

        if (reason == QLatin1String("assign")) {
            item.reason = NotificationObject::Assign;
        } else if (reason == QLatin1String("author")) {
            item.reason = NotificationObject::Author;
        } else if (reason == QLatin1String("comment")) {
            item.reason = NotificationObject::Comment;
        } else if (reason == QLatin1String("invitation")) {
            item.reason = NotificationObject::Invitation;
        } else if (reason == QLatin1String("manual")) {
            item.reason = NotificationObject::Manual;
        } else if (reason == QLatin1String("mention")) {
            item.reason = NotificationObject::Mention;
        } else if (reason == QLatin1String("review_request")) {
            item.reason = NotificationObject::ReviewRequest;
        } else if (reason == QLatin1String("security_alert")) {
            item.reason = NotificationObject::SecurityAlert;
        } else if (reason == QLatin1String("state_change")) {
            item.reason = NotificationObject::StateChange;
        } else if (reason == QLatin1String("subscribed")) {
            item.reason = NotificationObject::Subscribed;
        } else if (reason == QLatin1String("team_mention")) {
            item.reason = NotificationObject::TeamMention;
        }

        // repo
        const QJsonObject repo = obj.value(ApiKey::REPOSITORY).toObject();
        item.repoId = repo.value(RestApiKey::NODE_ID).toString();
        item.repoName = repo.value(RestApiKey::FULL_NAME).toString();

        // subject title
        const QJsonObject subject = obj.value(RestApiKey::SUBJECT).toObject();
        item.title = subject.value(ApiKey::TITLE).toString();

        // number
        const QStringList urlItems = subject.value(ApiKey::URL).toString().split('/');
        if (urlItems.count() > 1)
            item.number = urlItems.last().toInt();

        // type
        const QString type = subject.value(ApiKey::TYPE).toString();

        if (type == QLatin1String("Issue")) {
            item.type = NotificationObject::Issue;
        } else if (type == QLatin1String("PullRequest")) {
            item.type = NotificationObject::PullRequest;
        } else if (type == QLatin1String("RepositoryVulnerabilityAlert")) {
            item.type = NotificationObject::RepositoryVulnerabilityAlert;
        }

        // unread
        item.unread = obj.value(RestApiKey::UNREAD).toBool();

        // updated at
        item.updatedAt = QDateTime::fromString(obj.value(RestApiKey::UPDATED_AT).toString(), Qt::ISODate);
        item.updatedAtTimeSpan = timeSpanText(item.updatedAt, true);

        //

        items.append(item);
    }

    return items;
}

Owner *DataUtils::ownerFromJson(const QJsonObject &obj)
{
    auto owner = new Owner;
    owner->setNodeId(obj.value(ApiKey::ID).toString());
    owner->setLogin(obj.value(ApiKey::LOGIN).toString());
    owner->setAvatarUrl(obj.value(ApiKey::AVATAR_URL).toString());

    return owner;
}

Owner *DataUtils::ownerFromGitActorJson(const QJsonObject &obj)
{
    auto owner = new Owner;

    const QJsonObject user = obj.value(ApiKey::USER).toObject();

    owner->setNodeId(user.value(ApiKey::ID).toString());
    owner->setLogin(user.value(ApiKey::LOGIN).toString());
    owner->setAvatarUrl(obj.value(ApiKey::AVATAR_URL).toString());

    return owner;
}

PageInfo DataUtils::pageInfoFromJson(const QJsonObject &obj, const QJsonValue &count)
{
    PageInfo info;

    const QJsonObject item = obj.value(ApiKey::PAGE_INFO).toObject();
    if (item.isEmpty())
        return info;

    info.hasNextPage = item.value(ApiKey::HAS_NEXT_PAGE).toBool();
    info.totalCount = count.toInt();
    info.lastItemCursor = item.value(ApiKey::END_CURSOR).toString();

    return info;
}

QList<TreeItemListItem> DataUtils::treeListItemsFromJson(const QJsonObject &obj)
{
    QList<TreeItemListItem> items;

    const QJsonArray entries = obj.value(ApiKey::NODE).toObject()
            .value(ApiKey::REF).toObject()
            .value(ApiKey::TARGET).toObject()
            .value(ApiKey::FILE).toObject()
            .value(ApiKey::OBJECT).toObject()
            .value(ApiKey::ENTRIES).toArray();

    for (const auto &entry : entries) {
        items.append(treeListItemFromJson(entry.toObject()));
    }


    return items;
}

TreeItemListItem DataUtils::treeListItemFromJson(const QJsonObject &obj)
{
    TreeItemListItem item;

    item.name = obj.value(ApiKey::NAME).toString();
    item.path = obj.value(ApiKey::PATH).toString();
    item.extension = obj.value(ApiKey::EXTENSION).toString();

    const QString type = obj.value(ApiKey::TYPE).toString();

    if (type == QLatin1String("tree")) {
        item.type = TreeItem::Tree;
        return item;
    }

    if (type == QLatin1String("blob")) {
        item.type = TreeItem::Blob;

        if (obj.value(ApiKey::OBJECT).toObject().value(ApiKey::IS_BINARY).toBool()) {

            // image files
            QRegExp regex;
            regex.setPattern(".(jpg|png|gif|jpeg|ico|bmp)");

            if (regex.exactMatch(item.extension)) {
                item.fileType = File::Image;
                return item;
            }

            // else binary
            item.fileType = File::Binary;
            return item;
        }

        // SVG file
        QRegExp regex;
        regex.setPattern(".(svg)");

        if (regex.exactMatch(item.extension)) {
            item.fileType = File::Image;
            return item;
        }

        // Markdown
        regex.setPattern(".(md)");

        if (regex.exactMatch(item.extension)) {
            item.fileType = File::Markdown;
            return item;
        }

        item.fileType = File::Text;
    }

    return item;
}

QString DataUtils::getEmoji(const QString &string)
{
    QRegularExpression re(QStringLiteral("(?<=unicode\\/)(.*)(?=\">)"));
    QRegularExpressionMatch match = re.match(string);

    if (!match.hasMatch())
        return QString();



    QFile file(QStringLiteral("/usr/share/harbour-sailhub/twemoji/svg/") + match.captured(0));

    return QString();
}

QString DataUtils::getEmojiLinkFromString(const QString &string)
{
    QRegularExpression re(QStringLiteral("(?<=unicode\\/)(.*)(?=\">)"));
    QRegularExpressionMatch match = re.match(string);

    if (!match.hasMatch())
        return QString();

    auto result = match.captured(0);
    auto test = result.remove(".png").append(".svg");

    return QStringLiteral("/usr/share/harbour-sailhub/twemoji/svg/") + match.captured(0).remove(".png").append(".svg");
}


QString DataUtils::getLinkFromString(const QString &string)
{
    QRegularExpression re(QStringLiteral("(https):\\/\\/([\\w_-]+(?:(?:\\.[\\w_-]+)+))([\\w.,@?^=%&:\\/~+#-]*[\\w@?^=%&\\/~+#-])?"));
    QRegularExpressionMatch match = re.match(string);

    if (!match.hasMatch())
        return QString();

    return match.captured(0);
}

quint16 DataUtils::getRepoFlags(const QJsonObject &obj)
{
    quint16 flags{0};

    if (obj.value(ApiKey::IS_ARCHIVED).toBool())
        flags |= Repo::IsArchived;

    if (obj.value(ApiKey::IS_BLANK_ISSUES_ENABLED).toBool())
        flags |= Repo::IsBlankIssuesEnabled;

    if (obj.value(ApiKey::IS_DISABLED).toBool())
        flags |= Repo::IsDisabled;

    if (obj.value(ApiKey::IS_EMPTY).toBool())
        flags |= Repo::IsEmpty;

    if (obj.value(ApiKey::IS_FORK).toBool())
        flags |= Repo::IsFork;

    if (obj.value(ApiKey::IS_IN_ORGANIZATION).toBool())
        flags |= Repo::IsInOrganization;

    if (obj.value(ApiKey::IS_LOCKED).toBool())
        flags |= Repo::IsLocked;

    if (obj.value(ApiKey::IS_MIRROR).toBool())
        flags |= Repo::IsMirror;

    if (obj.value(ApiKey::IS_PRIVATE).toBool())
        flags |= Repo::IsPrivate;

    if (obj.value(ApiKey::IS_SECURITY_POLICY_ENABLED).toBool())
        flags |= Repo::IsSecurityPolicyEnabled;

    if (obj.value(ApiKey::IS_TEMPLATE).toBool())
        flags |= Repo::IsTemplate;

    if (obj.value(ApiKey::IS_USER_CONFIGURATION_REPOSITORY).toBool())
        flags |= Repo::IsUserConfigurationRepository;

    return flags;
}

quint32 DataUtils::getTotalCount(const QJsonObject &obj)
{
    return quint32(obj.value(ApiKey::TOTAL_COUNT).toInt());
}

quint32 DataUtils::getViewerAbilities(const QJsonObject &obj)
{
    quint32 abilities{0};

    if (obj.value(ApiKey::VIEWER_CAN_ADMINISTER).toBool())
        abilities |= Viewer::CanAdminister;

    if (obj.value(ApiKey::VIEWER_CAN_APPLY_SUGGESTION).toBool())
        abilities |= Viewer::CanApplySuggestion;

    if (obj.value(ApiKey::VIEWER_CAN_CREATE_PROJECTS).toBool())
        abilities |= Viewer::CanCreateProjects;

    if (obj.value(ApiKey::VIEWER_CAN_DELETE).toBool())
        abilities |= Viewer::CanDelete;

    if (obj.value(ApiKey::VIEWER_CAN_DELETE_HEAD_REF).toBool())
        abilities |= Viewer::CanDeleteHeadRef;

    if (obj.value(ApiKey::VIEWER_CAN_DISABLE_AUTO_MERGE).toBool())
        abilities |= Viewer::CanDisableAutoMerge;

    if (obj.value(ApiKey::VIEWER_CAN_ENABLE_AUTO_MERGE).toBool())
        abilities |= Viewer::CanEnableAutoMerge;

    if (obj.value(ApiKey::VIEWER_CAN_REACT).toBool())
        abilities |= Viewer::CanReact;

    if (obj.value(ApiKey::VIEWER_CAN_SUBSCRIBE).toBool())
        abilities |= Viewer::CanSubscribe;

    if (obj.value(ApiKey::VIEWER_CAN_UPDATE).toBool())
        abilities |= Viewer::CanUpdate;

    if (obj.value(ApiKey::VIEWER_CAN_UPDATE_TOPICS).toBool())
        abilities |= Viewer::CanUpdateTopics;

    if (obj.value(ApiKey::VIEWER_CAN_MARK_AS_ANSWER).toBool())
        abilities |= Viewer::CanMarkAsAnswer;

    if (obj.value(ApiKey::VIEWER_CAN_MINIMIZE).toBool())
        abilities |= Viewer::CanMinimize;

    if (obj.value(ApiKey::VIEWER_CAN_UNMARK_AS_ANSWER).toBool())
        abilities |= Viewer::CanUnmarkAsAnswer;

    return abilities;
}

QString DataUtils::removeEmojiTags(const QString &text)
{
    QString out = text;

    QRegularExpression re(QStringLiteral("<g-emoji(.*)\">"));

    out.remove(re);
    out.remove(QStringLiteral("</g-emoji>"));

    return out;
}

QString DataUtils::timeSpanText(const QDateTime &start, bool shortText)
{
    const QDateTime now = QDateTime::currentDateTimeUtc();

    if (start.addSecs(3600) > now) {
        const quint64 minutes = start.secsTo(now) / 60;
        return shortText ? QStringLiteral("%1m").arg(minutes) : QObject::tr("%n minute(s) ago", "", minutes);
    }

    if (start.addSecs(86400) > now) {
        const quint64 hours = start.secsTo(now) / 3600;
        return shortText ? QStringLiteral("%1h").arg(hours) : QObject::tr("%n hour(s) ago", "", hours);
    }

    if (start.addMonths(1) > now) {
        const quint64 days = start.daysTo(now);
        return shortText ? QStringLiteral("%1d").arg(days) : QObject::tr("%n day(s) ago", "", days);
    }

    if (start.addMonths(12) > now ) {
        const quint64 months = start.daysTo(now) / 30;
        return shortText ? QStringLiteral("%1mo").arg(months) : QObject::tr("%n month(s) ago", "", months);
    }

    const quint64 years = start.daysTo(now) / 365;
    return shortText ? QStringLiteral("%1y").arg(years) : QObject::tr("%n year(s) ago", "", years);
}

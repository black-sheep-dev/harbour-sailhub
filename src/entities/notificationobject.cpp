#include "notificationobject.h"

#include "src/api/datautils.h"
#include "src/api/keys.h"

// List Item
NotificationListItem::NotificationListItem(const QJsonObject &data)
{
    id = data.value(ApiKey::ID).toString();
    lastReadAt = QDateTime::fromString(data.value(RestApiKey::LAST_READ_AT).toString(), Qt::ISODate);

    // reason
    const QString r = data.value(RestApiKey::REASON).toString();

    if (r == QLatin1String("assign")) {
        reason = NotificationObject::Assign;
    } else if (r == QLatin1String("author")) {
        reason = NotificationObject::Author;
    } else if (r == QLatin1String("comment")) {
        reason = NotificationObject::Comment;
    } else if (r == QLatin1String("invitation")) {
        reason = NotificationObject::Invitation;
    } else if (r == QLatin1String("manual")) {
        reason = NotificationObject::Manual;
    } else if (r == QLatin1String("mention")) {
        reason = NotificationObject::Mention;
    } else if (r == QLatin1String("review_request")) {
        reason = NotificationObject::ReviewRequest;
    } else if (r == QLatin1String("security_alert")) {
        reason = NotificationObject::SecurityAlert;
    } else if (r == QLatin1String("state_change")) {
        reason = NotificationObject::StateChange;
    } else if (r == QLatin1String("subscribed")) {
        reason = NotificationObject::Subscribed;
    } else if (r == QLatin1String("team_mention")) {
        reason = NotificationObject::TeamMention;
    }

    // repo
    const QJsonObject repo = data.value(ApiKey::REPOSITORY).toObject();
    repoId = repo.value(RestApiKey::NODE_ID).toString();
    repoName = repo.value(RestApiKey::FULL_NAME).toString();

    // subject title
    const QJsonObject subject = data.value(RestApiKey::SUBJECT).toObject();
    title = subject.value(ApiKey::TITLE).toString();

    // number
    const QStringList urlItems = subject.value(ApiKey::URL).toString().split('/');
    if (urlItems.count() > 1)
        number = urlItems.last().toInt();

    // type
    const QString t = subject.value(ApiKey::TYPE).toString();

    if (t == QLatin1String("Issue")) {
        type = NotificationObject::Issue;
    } else if (t == QLatin1String("PullRequest")) {
        type = NotificationObject::PullRequest;
    } else if (t == QLatin1String("RepositoryVulnerabilityAlert")) {
        type = NotificationObject::RepositoryVulnerabilityAlert;
    }

    // unread
    unread = data.value(RestApiKey::UNREAD).toBool();

    // updated at
    updatedAt = QDateTime::fromString(data.value(RestApiKey::UPDATED_AT).toString(), Qt::ISODate);
    updatedAtTimeSpan = DataUtils::timeSpanText(updatedAt, true);

}

// Object
NotificationObject::NotificationObject(QObject *parent) :
    QObject(parent)
{

}



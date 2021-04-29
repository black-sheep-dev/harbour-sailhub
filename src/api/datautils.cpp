#include "datautils.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

#include <QJsonArray>
#include <QJsonObject>
#include <QRegularExpression>

#include "keys.h"

#include "src/enums/lockreason.h"
#include "src/enums/subscriptionstate.h"

#include "src/entities/reaction.h"

Comment *DataUtils::commentFromJson(const QJsonObject &obj)
{
    Comment *comment = new Comment;

    comment->setNodeId(obj.value(ApiKey::ID).toString());

    constexpr int max = 160;
    const QString body = obj.value(ApiKey::BODY_TEXT).toString();

    if (body.length() <= max) {
        comment->setBodyExcerpt(body);
    } else {
        const QString excerpt = body.mid(0, max);
        comment->setBodyExcerpt(
                    excerpt.mid(0, excerpt.lastIndexOf(' '))
                    .simplified()
                    .append(QStringLiteral("...")));
    }

    comment->setViewerAbilities(getViewerAbilities(obj));

    // reactions
    getInteractable(obj, comment);

    return comment;
}

QList<Comment *> DataUtils::commentsFromJson(const QJsonObject &obj)
{
    QList<Comment *> comments;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject comment = node.toObject();
        if (comment.isEmpty())
            continue;

        comments.append(commentFromJson(comment));
    }

    return comments;
}

Discussion *DataUtils::discussionFromJson(const QJsonObject &obj, Discussion *discussion)
{
    if (discussion == nullptr)
        discussion = new Discussion;

    discussion->setNodeId(obj.value(ApiKey::ID).toString());

    discussion->setActiveLockReason(LockReason::fromString(obj.value(ApiKey::ACTIVE_LOCK_REASON).toString()));
    discussion->setAnswerChosenAt(QDateTime::fromString(obj.value(ApiKey::ANSWER_CHOSEN_AT).toString(), Qt::ISODate));
    discussion->setAnswerChosenBy(ownerFromJson(obj.value(ApiKey::ANSWER_CHOSEN_BY).toObject()));

    const QJsonObject category = obj.value(ApiKey::CATEGORY).toObject();
    discussion->setCategory(category.value(ApiKey::NAME).toString());
    discussion->setCategoryId(category.value(ApiKey::ID).toString());
    discussion->setCategoryEmoji(getEmojiLinkFromString(category.value(ApiKey::EMOJI_HTML).toString()));

    discussion->setCommentCount(getTotalCount(obj.value(ApiKey::COMMENTS).toObject()));
    discussion->setCreatedViaEmail(obj.value(ApiKey::CREATED_VIA_EMAIL).toBool());
    discussion->setEditor(ownerFromJson(obj.value(ApiKey::EDITOR).toObject()));
    discussion->setLocked(obj.value(ApiKey::LOCKED).toBool());
    discussion->setNumber(obj.value(ApiKey::NUMBER).toInt());
    discussion->setPublishedAt(QDateTime::fromString(obj.value(ApiKey::PUBLISHED_AT).toString(), Qt::ISODate));

    const QJsonObject repo = obj.value(ApiKey::REPOSITORY).toObject();
    discussion->setRepository(repo.value(ApiKey::NAME_WITH_OWNER).toString());
    discussion->setRepositoryId(repo.value(ApiKey::ID).toString());
    discussion->setTitle(obj.value(ApiKey::TITLE).toString());
    discussion->setViewerSubscription(SubscriptionState::fromString(obj.value(ApiKey::VIEWER_SUBSCRIPTION).toString()));

    discussion->setViewerAbilities(getViewerAbilities(obj));

    // reactions
    getInteractable(obj, discussion);

    return discussion;
}

DiscussionListItem DataUtils::discussionListItemFromJson(const QJsonObject &obj)
{
    DiscussionListItem item;

    item.nodeId = obj.value(ApiKey::ID).toString();

    const QJsonObject category = obj.value(ApiKey::CATEGORY).toObject();
    item.category = category.value(ApiKey::NAME).toString();
    item.emoji = getEmojiLinkFromString(category.value(ApiKey::EMOJI_HTML).toString());

    item.commentCount = getTotalCount(obj.value(ApiKey::COMMENTS).toObject());
    item.title = obj.value(ApiKey::TITLE).toString();

    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.createdAtTimeSpan = timeSpanText(item.createdAt, true);
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    item.updatedAtTimeSpan = timeSpanText(item.updatedAt, true);
    item.viewerCanDelete = obj.value(ApiKey::VIEWER_CAN_DELETE).toBool();

    const QJsonObject author = obj.value(ApiKey::AUTHOR).toObject();

    item.authorLogin = author.value(ApiKey::LOGIN).toString();
    item.authorAvatar = author.value(ApiKey::AVATAR_URL).toString();

    return item;
}

QList<DiscussionListItem> DataUtils::discussionsFromJson(const QJsonObject &obj)
{
    QList<DiscussionListItem> discussions;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject discussion = node.toObject();
        if (discussion.isEmpty())
            continue;

        discussions.append(discussionListItemFromJson(discussion));
    }

    return discussions;
}

DiscussionCategoryListItem DataUtils::discussionCategoryListItemFromJson(const QJsonObject &obj)
{
    DiscussionCategoryListItem item;

    item.nodeId = obj.value(ApiKey::ID).toString();
    item.emoji = getEmojiLinkFromString(obj.value(ApiKey::EMOJI_HTML).toString());
    item.description = obj.value(ApiKey::DESCRIPTION).toString();
    item.name = obj.value(ApiKey::NAME).toString();

    return item;
}

QList<DiscussionCategoryListItem> DataUtils::discussionCategoriesFromJson(const QJsonObject &obj)
{
    QList<DiscussionCategoryListItem> categories;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject category = node.toObject();
        if (category.isEmpty())
            continue;

        categories.append(discussionCategoryListItemFromJson(category));
    }

    return categories;
}

DiscussionComment *DataUtils::discussionCommentFromJson(const QJsonObject &obj)
{
    DiscussionComment *comment = new DiscussionComment;

    comment->setNodeId(obj.value(ApiKey::ID).toString());

    comment->setCreatedViaEmail(obj.value(ApiKey::CREATED_VIA_EMAIL).toBool());
    comment->setDeletedAt(QDateTime::fromString(obj.value(ApiKey::DELETED_AT).toString(), Qt::ISODate));
    comment->setDiscussionId(obj.value(ApiKey::DISCUSSION).toObject().value(ApiKey::ID).toString());
    comment->setEditor(ownerFromJson(obj.value(ApiKey::EDITOR).toObject()));
    comment->setIncludesCreatedEdit(obj.value(ApiKey::INCLUDES_CREATED_EDIT).toBool());
    comment->setIsAnswer(obj.value(ApiKey::IS_ANSWER).toBool());
    comment->setIsMinimized(obj.value(ApiKey::IS_MINIMIZED).toBool());
    comment->setMinimizedReason(obj.value(ApiKey::MINIMIZED_REASON).toString());
    comment->setReplyCount(getTotalCount(obj.value(ApiKey::REPLIES).toObject()));
    comment->setReplyToId(obj.value(ApiKey::REPLY_TO).toObject().value(ApiKey::ID).toString());


    // reactions
    getInteractable(obj, comment);

    comment->setViewerAbilities(getViewerAbilities(obj));

    return comment;
}

QList<DiscussionComment *> DataUtils::discussionCommentsFromJson(const QJsonObject &obj)
{
    QList<DiscussionComment *> comments;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject comment = node.toObject();
        if (comment.isEmpty())
            continue;

        comments.append(discussionCommentFromJson(comment));
    }

    return comments;
}

Gist *DataUtils::gistFromJson(const QJsonObject &obj, Gist *gist)
{
    if (gist == nullptr)
        gist = new Gist;

    gist->setNodeId(obj.value(ApiKey::ID).toString());
    gist->setName(obj.value(ApiKey::NAME).toString());

    gist->setCommetCount(getTotalCount(obj.value(ApiKey::COMMENTS).toObject()));
    gist->setCreatedAt(QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    gist->setDescription(obj.value(ApiKey::DESCRIPTION).toString());
    gist->setForkCount(getTotalCount(obj.value(ApiKey::FORKS).toObject()));
    gist->setIsFork(obj.value(ApiKey::IS_FORK).toBool());
    gist->setIsPublic(obj.value(ApiKey::IS_PUBLIC).toBool());
    gist->setOwner(ownerFromJson(obj.value(ApiKey::OWNER).toObject()));
    gist->setPushedAt(QDateTime::fromString(obj.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate));
    gist->setStargazerCount(obj.value(ApiKey::STARGAZER_COUNT).toInt());
    gist->setUpdatedAt(QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate));
    gist->setViewerHasStarred(obj.value(ApiKey::VIEWER_HAS_STARRED).toBool());

    return gist;
}

GistListItem DataUtils::gistListItemFromJson(const QJsonObject &obj)
{
    GistListItem item;

    item.nodeId = obj.value(ApiKey::ID).toString();

    item.description = obj.value(ApiKey::DESCRIPTION).toString();
    item.isPublic = obj.value(ApiKey::IS_PUBLIC).toBool();
    item.commentCount = getTotalCount(obj.value(ApiKey::COMMENTS).toObject());
    item.fileCount = getTotalCount(obj.value(ApiKey::FILES).toObject());
    item.forkCount = getTotalCount(obj.value(ApiKey::FORKS).toObject());
    item.stargazerCount = obj.value(ApiKey::STARGAZER_COUNT).toInt();
    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.pushedAt = QDateTime::fromString(obj.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate);
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);

    const QJsonObject owner = obj.value(ApiKey::OWNER).toObject();

    item.ownerLogin = owner.value(ApiKey::LOGIN).toString();
    item.ownerAvatar = owner.value(ApiKey::AVATAR_URL).toString();

    return item;
}

QList<GistListItem> DataUtils::gistsFromJson(const QJsonObject &obj)
{
    QList<GistListItem> gists;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject gist = node.toObject();
        if (gist.isEmpty())
            continue;

        gists.append(gistListItemFromJson(gist));
    }

    return gists;
}

Issue *DataUtils::issueFromJson(const QJsonObject &obj, Issue *issue)
{
    if (issue == nullptr)
        issue = new Issue;

    issue->setNodeId(obj.value(ApiKey::ID).toString());

    issue->setAssigneeCount(getTotalCount(obj.value(ApiKey::ASSIGNEES).toObject()));
    issue->setTitle(obj.value(ApiKey::TITLE).toString());
    issue->setNumber(obj.value(ApiKey::NUMBER).toInt());

    const QJsonObject repo = obj.value(ApiKey::REPOSITORY).toObject();
    issue->setRepository(repo.value(ApiKey::NAME_WITH_OWNER).toString());
    issue->setRepositoryId(repo.value(ApiKey::ID).toString());
    issue->setRepositoryPermission(getViewerPermission(repo.value(ApiKey::VIEWER_PERMISSION).toString()));

    issue->setStates(obj.value(ApiKey::STATE).toInt());
    issue->setCommentCount(getTotalCount(obj.value(ApiKey::COMMENTS).toObject()));
    issue->setEdited(issue->updatedAt() > issue->createdAt());
    issue->setLabelCount(getTotalCount(obj.value(ApiKey::LABELS).toObject()));
    issue->setParticipantCount(getTotalCount(obj.value(ApiKey::PARTICIPANTS).toObject()));

    issue->setViewerAbilities(getViewerAbilities(obj));

    getInteractable(obj, issue);

    return issue;
}

IssueListItem DataUtils::issueListItemFromJson(const QJsonObject &obj)
{
    IssueListItem item;

    item.nodeId = obj.value(ApiKey::ID).toString();
    item.closed = obj.value(ApiKey::CLOSED).toBool();
    item.commentCount = getTotalCount(obj.value(ApiKey::COMMENTS).toObject());
    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.createdAtTimeSpan = timeSpanText(item.createdAt, true);
    item.number = obj.value(ApiKey::NUMBER).toInt();
    item.repository = obj.value(ApiKey::REPOSITORY).toObject()
                         .value(ApiKey::NAME_WITH_OWNER).toString();

    const QString state = obj.value(ApiKey::STATE).toString();
    if (state == QLatin1Literal("OPEN"))
        item.state = Issue::StateOpen;
    else if (state == QLatin1Literal("CLOSED"))
        item.state = Issue::StateClosed;

    item.title = obj.value(ApiKey::TITLE).toString();
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    item.updatedAtTimeSpan = timeSpanText(item.updatedAt, true);

    return item;
}

QList<IssueListItem> DataUtils::issuesFromJson(const QJsonObject &obj)
{
    QList<IssueListItem> issues;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject issue = node.toObject();
        if (issue.isEmpty())
            continue;

        issues.append(issueListItemFromJson(issue));
    }

    return issues;
}

LabelListItem DataUtils::labelListItemFromJson(const QJsonObject &obj)
{
    LabelListItem item;

    item.color = obj.value(ApiKey::COLOR).toString();
    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.name = obj.value(ApiKey::NAME).toString();

    return item;
}

QList<LabelListItem> DataUtils::labelsFromJson(const QJsonObject &obj)
{
    QList<LabelListItem> items;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject label = node.toObject();
        if (label.isEmpty())
            continue;

        items.append(labelListItemFromJson(label));
    }

    return items;
}

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

Organization *DataUtils::organizationFromJson(const QJsonObject &obj, Organization *organization)
{
    if (organization == nullptr)
        organization = new Organization;

    organization->setAvatarUrl(obj.value(ApiKey::AVATAR_URL).toString());
    organization->setDescription(obj.value(ApiKey::DESCRIPTION).toString());
    organization->setEmail(obj.value(ApiKey::EMAIL).toString());
    organization->setLocation(obj.value(ApiKey::LOCATION).toString());
    organization->setLogin(obj.value(ApiKey::LOGIN).toString());
    organization->setMembers(getTotalCount(obj.value(ApiKey::MEMBERS_WITH_ROLE).toObject()));
    organization->setName(obj.value(ApiKey::NAME).toString());
    organization->setNodeId(obj.value(ApiKey::ID).toString());
    organization->setProjects(getTotalCount(obj.value(ApiKey::PROJECTS).toObject()));
    organization->setRepositories(getTotalCount(obj.value(ApiKey::REPOSITORIES).toObject()));
    organization->setTeams(getTotalCount(obj.value(ApiKey::TEAMS).toObject()));
    organization->setTwitterUsername(obj.value(ApiKey::TWITTER_USERNAME).toString());
    organization->setViewerIsMember(obj.value(ApiKey::VIEWER_IS_MEMBER).toBool());
    organization->setViewerIsSponsoring(obj.value(ApiKey::VIEWER_IS_SPONSORING).toBool());
    organization->setWebsiteUrl(obj.value(ApiKey::WEBSITE_URL).toString());

    return organization;
}

OrganizationListItem DataUtils::organizationListItemFromJson(const QJsonObject &obj)
{
    OrganizationListItem item;

    item.avatarUrl = obj.value(ApiKey::AVATAR_URL).toString();
    item.description = obj.value(ApiKey::DESCRIPTION).toString();
    item.login = obj.value(ApiKey::LOGIN).toString();
    item.name = obj.value(ApiKey::NAME).toString();
    item.nodeId = obj.value(ApiKey::ID).toString();

    return item;
}

QList<OrganizationListItem> DataUtils::organizationsFromJson(const QJsonObject &obj)
{
    QList<OrganizationListItem>  organizations;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject organization = node.toObject();
        if (organization.isEmpty())
            continue;

        organizations.append(organizationListItemFromJson(organization));
    }

    return organizations;
}

Owner *DataUtils::ownerFromJson(const QJsonObject &obj)
{
    Owner *owner = new Owner;
    owner->setNodeId(obj.value(ApiKey::ID).toString());
    owner->setLogin(obj.value(ApiKey::LOGIN).toString());
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

PullRequest *DataUtils::pullRequestFromJson(const QJsonObject &obj)
{
    PullRequest *request = new PullRequest();

    issueFromJson(obj, request);

    return request;
}

QList<PullRequestListItem> DataUtils::pullRequestsFromJson(const QJsonObject &obj)
{
    QList<PullRequestListItem>  prs;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject pr = node.toObject();
        if (pr.isEmpty())
            continue;

        prs.append(pullRequestListItemFromJson(pr));
    }

    return prs;
}

PullRequestListItem DataUtils::pullRequestListItemFromJson(const QJsonObject &obj)
{
    PullRequestListItem item;

    item.nodeId = obj.value(ApiKey::ID).toString();
    item.commentCount = getTotalCount(obj.value(ApiKey::COMMENTS).toObject());
    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.createdAtTimeSpan = timeSpanText(item.createdAt, true);
    item.number = quint32(obj.value(ApiKey::NUMBER).toInt());
    item.repository = obj.value(ApiKey::REPOSITORY).toObject()
            .value(ApiKey::NAME_WITH_OWNER).toString();

    const QString state = obj.value(ApiKey::STATE).toString();
    if (state == QLatin1Literal("OPEN"))
        item.state = PullRequest::StateOpen;
    else if (state == QLatin1Literal("CLOSED"))
        item.state = PullRequest::StateClosed;
    else if (state == QLatin1Literal("MERGED"))
        item.state = PullRequest::StateMerged;

    item.timeSpan = timeSpanText(item.createdAt, true);
    item.title = obj.value(ApiKey::TITLE).toString();
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);
    item.updatedAtTimeSpan = timeSpanText(item.updatedAt, true);

    return item;
}

Release *DataUtils::releaseFromJson(const QJsonObject &obj)
{
    if (obj.isEmpty())
        return nullptr;

    Release *release = new Release;

    // author
    auto author = ownerFromJson(obj.value(ApiKey::AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(release);
        release->setAuthor(author);
    }

    release->setNodeId(obj.value(ApiKey::ID).toString());

    release->setAssetCount(getTotalCount(obj.value(ApiKey::RELEASE_ASSETS).toObject()));
    release->setCreatedAt(QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    release->setDescription(obj.value(ApiKey::DESCRIPTION).toString());
    release->setName(obj.value(ApiKey::NAME).toString());
    release->setIsDraft(obj.value(ApiKey::IS_DRAFT).toBool());
    release->setIsLatest(obj.value(ApiKey::IS_LATEST).toBool());
    release->setIsPrerelease(obj.value(ApiKey::IS_PRERELEASE).toBool());
    release->setPublishedAt(QDateTime::fromString(obj.value(ApiKey::PUBLISHED_AT).toString(), Qt::ISODate));
    release->setRepository(obj.value(ApiKey::REPOSITORY).toObject()
                           .value(ApiKey::NAME_WITH_OWNER).toString());
    release->setTagCommit(obj.value(ApiKey::TAG_COMMIT).toObject()
                          .value(ApiKey::ABBREVIATED_OID).toString());
    release->setTagName(obj.value(ApiKey::TAG_NAME).toString());


    return release;
}

ReleaseListItem DataUtils::releaseListItemFromJson(const QJsonObject &obj)
{
    ReleaseListItem item;

    item.nodeId = obj.value(ApiKey::ID).toString();
    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.createdAtTimeSpan = timeSpanText(item.createdAt, true);
    item.name = obj.value(ApiKey::NAME).toString();
    item.isDraft = obj.value(ApiKey::IS_DRAFT).toBool();
    item.isLatest = obj.value(ApiKey::IS_LATEST).toBool();
    item.isPrerelease = obj.value(ApiKey::IS_PRERELEASE).toBool();

    return item;
}

QList<ReleaseListItem> DataUtils::releasesFromJson(const QJsonObject &obj)
{
    QList<ReleaseListItem>  releases;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject release = node.toObject();
        if (release.isEmpty())
            continue;

        releases.append(releaseListItemFromJson(release));
    }

    return releases;
}

QList<ReleaseAssetListItem> DataUtils::releaseAssetsFromJson(const QJsonObject &obj)
{
    QList<ReleaseAssetListItem>  assets;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject asset = node.toObject();
        if (asset.isEmpty())
            continue;

        ReleaseAssetListItem item;

        item.contentType = asset.value(ApiKey::CONTENT_TYPE).toString();
        item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
        item.downloadCount = asset.value(ApiKey::DOWNLOAD_COUNT).toInt();
        item.downloadUrl = asset.value(ApiKey::DOWNLOAD_URL).toString();
        item.name = asset.value(ApiKey::NAME).toString();
        item.size = asset.value(ApiKey::SIZE).toInt();
        item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);

        assets.append(item);
    }

    return assets;
}

Repo *DataUtils::repoFromJson(const QJsonObject &obj)
{
    if (obj.isEmpty())
        return nullptr;

    Repo *repo = new Repo;

    QStringList branches;

    const QJsonArray nodes = getNodes(obj.value(ApiKey::REFS).toObject());

    for (const auto &node : nodes) {
        branches.append(node.toObject().value(ApiKey::NAME).toString());
    }
    repo->setBranches(branches);

    repo->setContributorCount(getTotalCount(obj.value(ApiKey::MENTIONABLE_USERS).toObject()));
    repo->setDefaultBranch(obj.value(ApiKey::DEFAULT_BRANCH_REF).toObject()
                           .value(ApiKey::NAME).toString());
    repo->setDescription(obj.value(ApiKey::DESCRIPTION).toString());
    repo->setDiscussionCount(getTotalCount(obj.value(ApiKey::DISCUSSIONS).toObject()));
    repo->setForkCount(obj.value(ApiKey::FORK_COUNT).toInt());
    repo->setHomepageUrl(obj.value(ApiKey::HOMEPAGE_URL).toString());
    repo->setIsPrivate(obj.value(ApiKey::IS_PRIVATE).toBool());
    repo->setIssuesCount(getTotalCount(obj.value(ApiKey::ISSUES).toObject()));
    repo->setName(obj.value(ApiKey::NAME).toString());
    repo->setNodeId(obj.value(ApiKey::ID).toString());
    repo->setProjects(getTotalCount(obj.value(ApiKey::PROJECTS).toObject()));
    repo->setReleaseCount(getTotalCount(obj.value(ApiKey::RELEASES).toObject()));
    repo->setPullRequestsCount(getTotalCount(obj.value(ApiKey::PULL_REQUESTS).toObject()));
    //repo->setReadme(obj.value(ApiKey::OBJECT).toObject().value(ApiKey::TEXT).toString());
    repo->setReleaseCount(getTotalCount(obj.value(ApiKey::RELEASES).toObject()));
    repo->setStargazerCount(obj.value(ApiKey::STARGAZER_COUNT).toInt());
    repo->setViewerCanSubscribe(obj.value(ApiKey::VIEWER_CAN_SUBSCRIBE).toBool());
    repo->setViewerHasStarred(obj.value(ApiKey::VIEWER_HAS_STARRED).toBool());
    repo->setViewerSubscription(obj.value(ApiKey::VIEWER_SUBSCRIPTION).toInt());
    repo->setWatcherCount(getTotalCount(obj.value(ApiKey::WATCHERS).toObject()));

    const QJsonObject lic = obj.value(ApiKey::LICENSE_INFO).toObject();
    License *license = new License(repo);
    license->setName(lic.value(ApiKey::SPDX_ID).toString());
    license->setUrl(lic.value(ApiKey::URL).toString());
    repo->setLicense(license);


    Owner *owner = ownerFromJson(obj.value(ApiKey::OWNER).toObject());
    if (owner != nullptr) {
        owner->setParent(repo);
        repo->setOwner(owner);
    }

    // features
    quint8 features{Repo::FeatureNone};

    if (obj.value(ApiKey::HAS_ISSUES_ENABLED).toBool())
        features |= Repo::FeatureIssues;

    if (obj.value(ApiKey::HAS_PROJECTS_ENABLED).toBool())
        features |= Repo::FeatureProjects;

    if (obj.value(ApiKey::HAS_WIKI_ENABLED).toBool())
        features |= Repo::FeatureWiki;

    repo->setFeatures(features);

    // permisson
    repo->setViewerPermission(getViewerPermission(obj.value(ApiKey::VIEWER_PERMISSION).toString()));

    // subscription
    repo->setViewerSubscription(SubscriptionState::fromString(obj.value(ApiKey::VIEWER_SUBSCRIPTION).toString()));

    return repo;
}

QList<RepoListItem> DataUtils::reposFromJson(const QJsonObject &obj)
{
    QList<RepoListItem>  repos;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject repo = node.toObject();
        if (repo.isEmpty())
            continue;

        repos.append(repoListItemFromJson(repo));
    }

    return repos;
}


RepoListItem DataUtils::repoListItemFromJson(const QJsonObject &obj)
{
    RepoListItem item;

    item.createdAt = QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate);
    item.description = obj.value(ApiKey::SHORT_DESCRIPTION_HTML).toString();
    item.isPrivate = obj.value(ApiKey::IS_PRIVATE).toBool();
    item.name = obj.value(ApiKey::NAME).toString();
    item.nodeId = obj.value(ApiKey::ID).toString();
    item.owner = obj.value(ApiKey::OWNER).toObject()
                 .value(ApiKey::LOGIN).toString();
    item.pushedAt = QDateTime::fromString(obj.value(ApiKey::PUSHED_AT).toString(), Qt::ISODate);
    item.stargazerCount = quint32(obj.value(ApiKey::STARGAZER_COUNT).toInt());

    const QJsonObject lang = obj.value(ApiKey::PRIMARY_LANGUAGE).toObject();
    item.language.name = lang.value(ApiKey::NAME).toString();
    item.language.color = lang.value(ApiKey::COLOR).toString();
    item.updatedAt = QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate);

    return item;
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

User *DataUtils::userFromJson(const QJsonObject &obj, User *user)
{
    if (user == nullptr)
        user = new User;

    user->setAvatarUrl(obj.value(ApiKey::AVATAR_URL).toString());
    user->setBio(obj.value(ApiKey::BIO).toString());
    user->setCompany(obj.value(ApiKey::COMPANY).toString());
    user->setFollowers(getTotalCount(obj.value(ApiKey::FOLLOWERS).toObject()));
    user->setFollowing(getTotalCount(obj.value(ApiKey::FOLLOWING).toObject()));
    user->setGistCount(getTotalCount(obj.value(ApiKey::GISTS).toObject()));
    user->setLocation(obj.value(ApiKey::LOCATION).toString());
    user->setLogin(obj.value(ApiKey::LOGIN).toString());
    user->setIsViewer(obj.value(ApiKey::IS_VIEWER).toBool());
    user->setName(obj.value(ApiKey::NAME).toString());
    user->setNodeId(obj.value(ApiKey::ID).toString());
    user->setOrganizations(getTotalCount(obj.value(ApiKey::ORGANIZATIONS).toObject()));
    user->setRepositories(getTotalCount(obj.value(ApiKey::REPOSITORIES).toObject()));
    user->setStarredRepositories(getTotalCount(obj.value(ApiKey::STARRED_REPOSITORIES).toObject()));
    user->setTwitterUsername(obj.value(ApiKey::TWITTER_USERNAME).toString());
    user->setViewerIsFollowing(obj.value(ApiKey::VIEWER_IS_FOLLOWING).toBool());
    user->setWebsiteUrl(obj.value(ApiKey::WEBSITE_URL).toString());

    // user status
    const QJsonObject status = obj.value(ApiKey::STATUS).toObject();

    UserStatus sta;
    sta.emoji = status.value(ApiKey::EMOJI).toString();
    sta.message = status.value(ApiKey::MESSAGE).toString();

    user ->setStatus(sta);

    return user;
}

UserListItem DataUtils::userListItemFromJson(const QJsonObject &obj)
{
    UserListItem item;

    item.avatarUrl = obj.value(ApiKey::AVATAR_URL).toString();
    item.login = obj.value(ApiKey::LOGIN).toString();
    item.name = obj.value(ApiKey::NAME).toString();
    item.nodeId = obj.value(ApiKey::ID).toString();

    return item;
}

QList<UserListItem> DataUtils::usersFromJson(const QJsonObject &obj)
{
    QList<UserListItem>  users;

    const QJsonArray nodes = getNodes(obj);

    for (const auto &node : nodes) {
        const QJsonObject user = node.toObject();
        if (user.isEmpty())
            continue;

        users.append(userListItemFromJson(user));
    }

    return users;
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

QString DataUtils::getEmojiLinkFromString(const QString &string)
{
    QRegularExpression re(QStringLiteral("(?<=unicode\\/)(.*)(?=\">)"));
    QRegularExpressionMatch match = re.match(string);

    if (!match.hasMatch())
        return QString();

    return QStringLiteral("/usr/share/harbour-twemoji/72x72/") + match.captured(0);
}

QString DataUtils::getLinkFromString(const QString &string)
{
    QRegularExpression re(QStringLiteral("(https):\\/\\/([\\w_-]+(?:(?:\\.[\\w_-]+)+))([\\w.,@?^=%&:\\/~+#-]*[\\w@?^=%&\\/~+#-])?"));
    QRegularExpressionMatch match = re.match(string);

    if (!match.hasMatch())
        return QString();

    return match.captured(0);
}

quint8 DataUtils::getViewerPermission(const QString &permission)
{
    if (permission == QLatin1String("ADMIN"))
        return Repo::PermissionAdmin;

    if (permission == QLatin1String("MAINTAIN"))
        return Repo::PermissionMaintain;

    if (permission == QLatin1String("READ"))
        return Repo::PermissionRead;

    if (permission == QLatin1String("TRIAGE"))
        return Repo::PermissionTriage;

    if (permission == QLatin1String("WRITE"))
        return Repo::PermissionWrite;


    return Repo::PermissionNone;
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

QJsonArray DataUtils::getNodes(const QJsonObject &obj)
{
    return obj.value(ApiKey::NODES).toArray();
}

void DataUtils::getInteractable(const QJsonObject &obj, Interactable *node)
{
    // author
    auto author = ownerFromJson(obj.value(ApiKey::AUTHOR).toObject());
    if (author != nullptr) {
        author->setParent(node);
        node->setAuthor(author);
    }

    node->setViewerDidAuthor(obj.value(ApiKey::VIEWER_DID_AUTHOR).toBool());

    // body
    //node->setBody(obj.value(ApiKey::BODY_HTML).toString());
    node->setBody(obj.value(ApiKey::BODY).toString());
    //qDebug() << "BODY: " << node->body();

    // reactions
    const QJsonArray reactionGroups = obj.value(ApiKey::REACTION_GROUPS).toArray();

    if (reactionGroups.isEmpty())
        return;

    quint8 viewerReactions{Reaction::None};

    for (const auto &item : reactionGroups) {
        const QJsonObject group = item.toObject();
        const QString content = group.value(ApiKey::CONTENT).toString();
        const bool viewerReacted = group.value(ApiKey::VIEWER_HAS_REACTED).toBool();
        const quint32 count = getTotalCount(group.value(ApiKey::USERS).toObject());

        if (content == QLatin1String("CONFUSED")) {
            node->setReactionConfusedCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Confused;

        } else if (content == QLatin1String("EYES")) {
            node->setReactionEyesCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Eyes;

        } else if (content == QLatin1String("HEART")) {
            node->setReactionHeartCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Heart;

        } else if (content == QLatin1String("HOORAY")) {
            node->setReactionHoorayCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Hooray;

        } else if (content == QLatin1String("LAUGH")) {
            node->setReactionLaughCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Laugh;

        } else if (content == QLatin1String("ROCKET")) {
            node->setReactionRocketCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::Rocket;

        } else if (content == QLatin1String("THUMBS_DOWN")) {
            node->setReactionThumbsDownCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::ThumbsDown;

        } else if (content == QLatin1String("THUMBS_UP")) {
            node->setReactionThumbsUpCount(count);
            if (viewerReacted)
                viewerReactions |= Reaction::ThumbsUp;

        }
    }

    node->setViewerReactions(viewerReactions);

    // timespamps
    node->setCreatedAt(QDateTime::fromString(obj.value(ApiKey::CREATED_AT).toString(), Qt::ISODate));
    node->setCreatedAtTimeSpan(timeSpanText(node->createdAt(), true));
    node->setLastEditedAt(QDateTime::fromString(obj.value(ApiKey::LAST_EDITED_AT).toString(), Qt::ISODate));
    node->setUpdatedAt(QDateTime::fromString(obj.value(ApiKey::UPDATED_AT).toString(), Qt::ISODate));
    node->setUpdatedAtTimeSpan(timeSpanText(node->updatedAt()));
    node->setEdited(node->createdAt() < node->lastEditedAt());
}

quint32 DataUtils::getTotalCount(const QJsonObject &obj)
{
    return quint32(obj.value(ApiKey::TOTAL_COUNT).toInt());
}

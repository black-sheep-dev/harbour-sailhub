#ifndef QUERY_ITEMS_H
#define QUERY_ITEMS_H

#include <QString>

// ------------------------------------------------------------------------------------------------------------------
// QUERY ITEMS
// ------------------------------------------------------------------------------------------------------------------
static const QString SAILHUB_QUERY_ITEM_COMMIT_LIST_ITEM =
        QStringLiteral("    id"
                       "    author {"
                       "        date"
                       "        user {"
                       "            avatarUrl"
                       "            login"
                       "        }"
                       "    }"
                       "    committer {"
                       "        date"
                       "        user {"
                       "            avatarUrl"
                       "            login"
                       "        }"
                       "    }"
                       "    messageHeadline").simplified();

static const QString SAILHUB_QUERY_ITEM_DISCUSSION_LIST_ITEM =
        QStringLiteral("    id"
                       "    activeLockReason"
                       "    author {"
                       "        avatarUrl"
                       "        login"
                       "    }"
                       "    category {"
                       "        emoji"
                       "        emojiHTML"
                       "        name"
                       "    }"
                       "    comments {"
                       "        totalCount"
                       "    }"
                       "    createdAt"
                       "    locked"
                       "    title"
                       "    updatedAt"
                       "    viewerCanDelete").simplified();

static const QString SAILHUB_QUERY_ITEM_DISCUSSION_COMMENT =
        QStringLiteral("    id"
                       "    author {"
                       "        avatarUrl"
                       "        login"
                       "    }"
                       "    body"
                       "    createdAt"
                       "    createdViaEmail"
                       "    deletedAt"
                       "    discussion {"
                       "        id"
                       "    }"
                       "    editor {"
                       "        avatarUrl"
                       "        login"
                       "    }"
                       "    includesCreatedEdit"
                       "    isAnswer"
                       "    isMinimized"
                       "    lastEditedAt"
                       "    minimizedReason"
                       "    publishedAt"
                       "    reactionGroups {"
                       "        ... on ReactionGroup {"
                       "            content"
                       "            users {"
                       "                totalCount"
                       "            }"
                       "            viewerHasReacted"
                       "        }"
                       "    }"
                       "    replies {"
                       "        totalCount"
                       "    }"
                       "    replyTo {"
                       "        id"
                       "    }"
                       "    updatedAt"
                       "    viewerCanDelete"
                       "    viewerCanMarkAsAnswer"
                       "    viewerCanMinimize"
                       "    viewerCanReact"
                       "    viewerCanUnmarkAsAnswer"
                       "    viewerCanUpdate"
                       "    viewerDidAuthor").simplified();

static const QString SAILHUB_QUERY_ITEM_DISCUSSION_CATEGORY_LIST_ITEM =
        QStringLiteral("    id"
                       "    description"
                       "    emojiHTML"
                       "    name").simplified();

static const QString SAILHUB_QUERY_ITEM_GIST_LIST_ITEM =
        QStringLiteral("    id"
                       "    comments {"
                       "        totalCount"
                       "    }"
                       "    createdAt"
                       "    description"
                       "    forks {"
                       "        totalCount"
                       "    }"
                       "    isPublic"
                       "    owner {"
                       "        avatarUrl"
                       "        login"
                       "    }"
                       "    pushedAt"
                       "    stargazerCount"
                       "    updatedAt").simplified();

static const QString SAILHUB_QUERY_ITEM_COMMENT =
        QStringLiteral("    id"
                       "    author {"
                       "        avatarUrl"
                       "        login"
                       "    }"
                       "    body"
                       "    bodyText"
                       "    createdAt"
                       "    lastEditedAt"
                       "    reactionGroups {"
                       "        ... on ReactionGroup {"
                       "            content"
                       "            users {"
                       "                totalCount"
                       "            }"
                       "            viewerHasReacted"
                       "        }"
                       "    }"
                       "    viewerCanDelete"
                       "    viewerCanReact"
                       "    viewerCanUpdate"
                       "    viewerDidAuthor").simplified();

static const QString SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM =
        QStringLiteral("    id"
                       "    closed"
                       "    comments {"
                       "        totalCount"
                       "    }"
                       "    createdAt"
                       "    number"
                       "    repository {"
                       "        nameWithOwner"
                       "    }"
                       "    state"
                       "    title"
                       "    updatedAt").simplified();

static const QString SAILHUB_QUERY_ITEM_LABEL_LIST_ITEM =
        QStringLiteral("    color"
                       "    createdAt"
                       "    name").simplified();

static const QString SAILHUB_QUERY_ITEM_ORGANIZATION =
        QStringLiteral("    id"
                       "    avatarUrl"
                       "    description"
                       "    email"
                       "    location"
                       "    login"
                       "    membersWithRole {"
                       "        totalCount"
                       "    }"
                       "    name"
                       "    projects {"
                       "        totalCount"
                       "    }"
                       "    repositories {"
                       "        totalCount"
                       "    }"
                       "    teams {"
                       "        totalCount"
                       "    }"
                       "    twitterUsername"
                       "    viewerIsAMember"
                       "    viewerIsSponsoring"
                       "    websiteUrl").simplified();

static const QString SAILHUB_QUERY_ITEM_ORGANIZATION_LIST_ITEM =
        QStringLiteral("    id"
                       "    avatarUrl"
                       "    description"
                       "    login"
                       "    name").simplified();

static const QString SAILHUB_QUERY_ITEM_PAGE_INFO =
        QStringLiteral("    pageInfo {"
                       "        hasNextPage"
                       "        endCursor"
                       "    }").simplified();

static const QString SAILHUB_QUERY_ITEM_PULL_REQUEST_LIST_ITEM =
        QStringLiteral("    id"
                       "    comments {"
                       "        totalCount"
                       "    }"
                       "    createdAt"
                       "    number"
                       "    repository {"
                       "        nameWithOwner"
                       "    }"
                       "    state"
                       "    title"
                       "    updatedAt").simplified();

static const QString SAILHUB_QUERY_ITEM_RELEASE_ASSET_LIST_ITEM =
        QStringLiteral("    id"
                       "    contentType"
                       "    createdAt"
                       "    downloadCount"
                       "    downloadUrl"
                       "    name"
                       "    size"
                       "    updatedAt").simplified();

static const QString SAILHUB_QUERY_ITEM_RELEASE_LIST_ITEM =
        QStringLiteral("    id"
                       "    createdAt"
                       "    isDraft"
                       "    isLatest"
                       "    isPrerelease"
                       "    name").simplified();

static const QString SAILHUB_QUERY_ITEM_REPO_LIST_ITEM =
        QStringLiteral("    id"
                       "    createdAt"
                       "    isArchived"
                       "    isDisabled"
                       "    isFork"
                       "    isLocked"
                       "    isPrivate"
                       "    lockReason"
                       "    shortDescriptionHTML"
                       "    primaryLanguage {"
                       "        color"
                       "        name"
                       "    }"
                       "    pushedAt"
                       "    name"
                       "    owner {"
                       "        avatarUrl"
                       "        login"
                       "    }"
                       "    stargazerCount"
                       "    updatedAt").simplified();

static const QString SAILHUB_QUERY_ITEM_USER =
        QStringLiteral("    id"
                       "    avatarUrl"
                       "    bio"
                       "    company"
                       "    email"
                       "    followers {"
                       "        totalCount"
                       "    }"
                       "    following {"
                       "        totalCount"
                       "    }"
                       "    gists ( privacy: ALL ) {"
                       "        totalCount"
                       "    }"
                       "    location"
                       "    login"
                       "    isViewer"
                       "    name"
                       "    organizations {"
                       "        totalCount"
                       "    }"
                       "    projects {"
                       "        totalCount"
                       "    }"
                       "    repositories {"
                       "        totalCount"
                       "    }"
                       "    starredRepositories {"
                       "        totalCount"
                       "    }"
                       "    status {"
                       "        emojiHTML"
                       "        message"
                       "    }"
                       "    twitterUsername"
                       "    viewerIsFollowing"
                       "    websiteUrl").simplified();

static const QString SAILHUB_QUERY_ITEM_USER_LIST_ITEM =
        QStringLiteral("    id"
                       "    avatarUrl"
                       "    login"
                       "    name").simplified();




#endif // QUERY_ITEMS_H

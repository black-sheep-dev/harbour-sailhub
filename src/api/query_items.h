#ifndef QUERY_ITEMS_H
#define QUERY_ITEMS_H

#include <QString>

// ------------------------------------------------------------------------------------------------------------------
// QUERY ITEMS
// ------------------------------------------------------------------------------------------------------------------
static const QString SAILHUB_QUERY_ITEM_COMMMENT =
        QStringLiteral("    id"
                       "    author {"
                       "        avatarUrl"
                       "        login"
                       "    }"
                       "    bodyHTML"
                       "    createdAt"
                       "    lastEditedAt"
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

static const QString SAILHUB_QUERY_ITEM_REPO_LIST_ITEM =
        QStringLiteral("    id"
                       "    isPrivate"
                       "    shortDescriptionHTML"
                       "    primaryLanguage {"
                       "        color"
                       "        name"
                       "    }"
                       "    name"
                       "    owner {"
                       "        login"
                       "    }"
                       "    stargazerCount").simplified();

static const QString SAILHUB_QUERY_ITEM_USER =
        QStringLiteral("    id"
                       "    avatarUrl"
                       "    bio"
                       "    company"
                       "    followers {"
                       "        totalCount"
                       "    }"
                       "    following {"
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
                       "    totalCount"
                       "    }"
                       "    status {"
                       "        emoji"
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

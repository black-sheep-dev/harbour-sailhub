#ifndef QUERIES_H
#define QUERIES_H

#include <QString>

// ------------------------------------------------------------------------------------------------------------------
// VARS
// ------------------------------------------------------------------------------------------------------------------
static const QString SAILHUB_QUERY_VAR_ITEM_COUNT               = QStringLiteral("itemCount");
static const QString SAILHUB_QUERY_VAR_ITEM_CURSOR              = QStringLiteral("itemCursor");
static const QString SAILHUB_QUERY_VAR_REPO_NAME                = QStringLiteral("repoName");
static const QString SAILHUB_QUERY_VAR_NODE_ID                  = QStringLiteral("nodeId");
static const QString SAILHUB_QUERY_VAR_USER_LOGIN               = QStringLiteral("userLogin");

// ------------------------------------------------------------------------------------------------------------------
// QUERY PARTS
// ------------------------------------------------------------------------------------------------------------------
static const QString SAILHUB_QUERY_PART_REPO_LIST_ITEM =
        QStringLiteral("    totalCount"
                       "    pageInfo {"
                       "        endCursor"
                       "        hasNextPage"
                       "    }"
                       "    nodes {"
                       "        id"
                       "        shortDescriptionHTML"
                       "        primaryLanguage {"
                       "            color"
                       "         name"
                       "        }"
                       "        name"
                       "        owner {"
                       "            login"
                       "        }"
                       "        stargazerCount"
                       "    }").simplified();

static const QString SAILHUB_QUERY_PART_USER =
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
                       "    name"
                       "    organizations {"
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
                       "    websiteUrl").simplified();

static const QString SAILHUB_QUERY_PART_USER_LIST_ITEM =
        QStringLiteral("    totalCount"
                       "    nodes {"
                       "        id"
                       "        avatarUrl"
                       "        login"
                       "        name"
                       "    }"
                       "    pageInfo {"
                       "        hasNextPage"
                       "        endCursor"
                       "    }").simplified();



// ------------------------------------------------------------------------------------------------------------------
// QUERIES
// ------------------------------------------------------------------------------------------------------------------

// GET LOGIN INFO OF AUTHENTICATED USER
static const QString SAILHUB_QUERY_GET_LOGIN =
        QStringLiteral("query {"
                       "    viewer {"
                       "        id"
                       "        login"
                       "    }"
                       "}").simplified();

// GET REPOSITORY
static const QString SAILHUB_QUERY_GET_REPOSITORY =
        QStringLiteral("query($nodeId: ID!) {"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            description"
                       "            forkCount"
                       "            homepageUrl"
                       "            isPrivate"
                       "            issues(states: [OPEN]) {"
                       "                totalCount"
                       "            }"
                       "            licenseInfo {"
                       "                spdxId"
                       "                url"
                       "            }"
                       "            mentionableUsers {"
                       "                totalCount"
                       "            }"
                       "            name"
                       "            owner {"
                       "                id"
                       "                login"
                       "                avatarUrl"
                       "            }"
                       "            pullRequests(states: [OPEN]) {"
                       "                totalCount"
                       "            }"
                       "            stargazerCount"
                       "            watchers {"
                       "                totalCount"
                       "            }"
//                       "        object(expression: \"master:README.md\") {"
//                       "            ... on Blob {"
//                       "                text"
//                       "            }"
//                       "        }
                       "        }"
                       "    }"
                       "}").simplified();

// GET REPOSITORY FORKS
static const QString SAILHUB_QUERY_GET_REPOSITORY_FORKS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String) {"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            forks(first: $itemCount, after: $itemCursor) {"
                       "                %1"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_REPO_LIST_ITEM).simplified();

// GET REPOSITORY CONTRIBUTORS
static const QString SAILHUB_QUERY_GET_REPOSITORY_CONTRIBUTORS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String) {"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            mentionableUsers(first: $itemCount, after: $itemCursor) {"
                       "                %1"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET REPOSITORY STARGAZERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_STARGAZERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String) {"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            stargazers(first: $itemCount, after: $itemCursor) {"
                       "                %1"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET REPOSITORY WATCHERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_WATCHERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String) {"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            watchers(first: $itemCount, after: $itemCursor) {"
                       "                %1"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET USER PROFILE
static const QString SAILHUB_QUERY_GET_USER_BY_LOGIN =
        QStringLiteral("query($userLogin: String!) {"
                       "    user(login: $userLogin) {"
                       "        %1"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER).simplified();

static const QString SAILHUB_QUERY_GET_USER =
        QStringLiteral("query($nodeId: ID!) {"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER).simplified();

// GET USER FOLLOWERS
static const QString SAILHUB_QUERY_GET_USER_FOLLOWERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String) {"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            followers(first: $itemCount, after: $itemCursor) {"
                       "                %1"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET USER FOLLOWERS
static const QString SAILHUB_QUERY_GET_USER_FOLLOWING =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String) {"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            following(first: $itemCount, after: $itemCursor) {"
                       "                %1"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET USER REPOSITORIES
static const QString SAILHUB_QUERY_GET_USER_REPOSITORIES =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            login"
                       "            repositories(first: $itemCount, after: $itemCursor) {"
                       "                %1"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_REPO_LIST_ITEM).simplified();


#endif // QUERIES_H

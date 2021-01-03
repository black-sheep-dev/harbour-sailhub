#ifndef QUERIES_H
#define QUERIES_H

#include <QString>

#include "query_items.h"

// ------------------------------------------------------------------------------------------------------------------
// VARS
// ------------------------------------------------------------------------------------------------------------------
static const QString SAILHUB_QUERY_VAR_ITEM_COUNT               = QStringLiteral("itemCount");
static const QString SAILHUB_QUERY_VAR_ITEM_CURSOR              = QStringLiteral("itemCursor");
static const QString SAILHUB_QUERY_VAR_NODE_ID                  = QStringLiteral("nodeId");
static const QString SAILHUB_QUERY_VAR_QUERY_STRING             = QStringLiteral("queryString");
static const QString SAILHUB_QUERY_VAR_REPO_NAME                = QStringLiteral("repoName");
static const QString SAILHUB_QUERY_VAR_USER_LOGIN               = QStringLiteral("userLogin");
static const QString SAILHUB_QUERY_VAR_STATES                   = QStringLiteral("states");


// ------------------------------------------------------------------------------------------------------------------
// QUERIES
// ------------------------------------------------------------------------------------------------------------------

// GET ISSUE
static const QString SAILHUB_QUERY_GET_ISSUE =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Issue {"
                       "            id"
                       "            author {"
                       "                avatarUrl"
                       "                login"
                       "            }"
                       "            comments {"
                       "                totalCount"
                       "            }"
                       "            title"
                       "            state"
                       "        }"
                       "    }"
                       "    "
                       "}").simplified();

static const QString SAILHUB_QUERY_GET_ISSUE_COMMENTS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Issue {"
                       "            id"
                       "            comments(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "    "
                       "}").arg(SAILHUB_QUERY_ITEM_COMMMENT, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET LOGIN INFO OF AUTHENTICATED USER
static const QString SAILHUB_QUERY_GET_VIEWER_PROFILE =
        QStringLiteral("query {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    viewer {"
                       "        %1"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER).simplified();

// GET REPOSITORY
static const QString SAILHUB_QUERY_GET_REPOSITORY =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
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
                       "            viewerCanSubscribe"
                       "            viewerHasStarred"
                       "            viewerSubscription"
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

// GET REPOSITORY ISSUES
static const QString SAILHUB_QUERY_GET_REPOSITORY_ISSUES =
        QStringLiteral("query($nodeId: ID!, $states: [IssueState!]!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            issues(first: $itemCount, after: $itemCursor, states: $states) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY FORKS
static const QString SAILHUB_QUERY_GET_REPOSITORY_FORKS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            forks(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_REPO_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY CONTRIBUTORS
static const QString SAILHUB_QUERY_GET_REPOSITORY_CONTRIBUTORS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            mentionableUsers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY STARGAZERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_STARGAZERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            stargazers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET REPOSITORY WATCHERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_WATCHERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on Repository {"
                       "            id"
                       "            watchers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER PROFILE
static const QString SAILHUB_QUERY_GET_USER =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER).simplified();

// GET USER FOLLOWERS
static const QString SAILHUB_QUERY_GET_USER_FOLLOWERS =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            followers(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER FOLLOWERS
static const QString SAILHUB_QUERY_GET_USER_FOLLOWING =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId,) {"
                       "        ... on User {"
                       "            id"
                       "            login"
                       "            following(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER REPOSITORIES
static const QString SAILHUB_QUERY_GET_USER_REPOSITORIES =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            login"
                       "            repositories(first: $itemCount, after: $itemCursor, orderBy: {"
                       "                    direction: ASC"
                       "                    field: NAME"
                       "                }) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_REPO_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// GET USER STARRED REPOSITORIES
static const QString SAILHUB_QUERY_GET_USER_REPOSITORIES_STARRED =
        QStringLiteral("query($nodeId: ID!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on User {"
                       "            login"
                       "            starredRepositories(first: $itemCount, after: $itemCursor) {"
                       "                nodes {"
                       "                    %1"
                       "                }"
                       "                totalCount"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_REPO_LIST_ITEM, SAILHUB_QUERY_ITEM_PAGE_INFO).simplified();

// ------------------------------------------------------------------------------------------------------------------
// QUERIES SEARCH
// ------------------------------------------------------------------------------------------------------------------

static const QString SAILHUB_QUERY_SEARCH_REPOSITORY =
        QStringLiteral("query searchRepos($queryString: String!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    search(query: $queryString, type: REPOSITORY, first: $itemCount, after: $itemCursor) {"
                       "        %1"
                       "        repositoryCount"
                       "        nodes {"
                       "            ... on Repository {"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_PAGE_INFO, SAILHUB_QUERY_ITEM_REPO_LIST_ITEM).simplified();

static const QString SAILHUB_QUERY_SEARCH_USER =
        QStringLiteral("query searchUsers($queryString: String!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    search(query: $queryString, type: USER, first: $itemCount, after: $itemCursor) {"
                       "        %1"
                       "        userCount"
                       "        nodes {"
                       "            ... on User {"
                       "                %2"
                       "            }"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_PAGE_INFO, SAILHUB_QUERY_ITEM_USER_LIST_ITEM).simplified();



#endif // QUERIES_H

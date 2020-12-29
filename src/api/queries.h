#ifndef QUERIES_H
#define QUERIES_H

#include <QString>

// ------------------------------------------------------------------------------------------------------------------
// VARS
// ------------------------------------------------------------------------------------------------------------------
static const QString SAILHUB_QUERY_VAR_ITEM_COUNT               = QStringLiteral("itemCount");
static const QString SAILHUB_QUERY_VAR_ITEM_CURSOR              = QStringLiteral("itemCursor");
static const QString SAILHUB_QUERY_VAR_REPO_NAME                = QStringLiteral("repoName");
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
                       "    }");

static const QString SAILHUB_QUERY_PART_USER_LIST_ITEM =
        QStringLiteral("    totalCount"
                       "    nodes {"
                       "        avatarUrl"
                       "        login"
                       "        name"
                       "    }"
                       "    pageInfo {"
                       "        hasNextPage"
                       "        endCursor"
                       "    }");

// ------------------------------------------------------------------------------------------------------------------
// QUERIES
// ------------------------------------------------------------------------------------------------------------------

// GET LOGIN INFO OF AUTHENTICATED USER
static const QString SAILHUB_QUERY_GET_LOGIN =
        QStringLiteral("query {"
                       "    viewer {"
                       "        login"
                       "    }"
                       "}");

// GET REPOSITORY
static const QString SAILHUB_QUERY_GET_REPOSITORY =
        QStringLiteral("query($userLogin: String!, $repoName: String!) {"
                       "    repository(owner: $userLogin, name: $repoName) {"
                       "        description"
                       "        forkCount"
                       "        homepageUrl"
                       "        isPrivate"
                       "        issues(states: [OPEN]) {"
                       "            totalCount"
                       "        }"
                       "        licenseInfo {"
                       "            spdxId"
                       "            url"
                       "        }"
                       "        mentionableUsers {"
                       "            totalCount"
                       "        }"
                       "        name"
                       "        owner {"
                       "            login"
                       "            avatarUrl"
                       "        }"
                       "        pullRequests(states: [OPEN]) {"
                       "            totalCount"
                       "        }"
                       "        stargazerCount"
                       "        watchers {"
                       "            totalCount"
                       "        }"
//                       "        object(expression: \"master:README.md\") {"
//                       "            ... on Blob {"
//                       "                text"
//                       "            }"
//                       "        }"
                       "    }"
                       "}");

// GET REPOSITORY FORKS
static const QString SAILHUB_QUERY_GET_REPOSITORY_FORKS =
        QStringLiteral("query($userLogin: String!, $repoName: String! , $itemCount: Int = 20, $itemCursor: String) {"
                       "    repository(owner: $userLogin, name: $repoName) {"
                       "        nameWithOwner"
                       "        forks(first: $itemCount, after: $itemCursor) {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_REPO_LIST_ITEM).simplified();

// GET REPOSITORY CONTRIBUTORS
static const QString SAILHUB_QUERY_GET_REPOSITORY_CONTRIBUTORS =
        QStringLiteral("query($userLogin: String!, $repoName: String! , $itemCount: Int = 20, $itemCursor: String) {"
                       "    repository(owner: $userLogin, name: $repoName) {"
                       "        nameWithOwner"
                       "        mentionableUsers(first: $itemCount, after: $itemCursor) {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET REPOSITORY STARGAZERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_STARGAZERS =
        QStringLiteral("query($userLogin: String!, $repoName: String! , $itemCount: Int = 20, $itemCursor: String) {"
                       "    repository(owner: $userLogin, name: $repoName) {"
                       "        nameWithOwner"
                       "        stargazers(first: $itemCount, after: $itemCursor) {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET REPOSITORY WATCHERS
static const QString SAILHUB_QUERY_GET_REPOSITORY_WATCHERS =
        QStringLiteral("query($userLogin: String!, $repoName: String! , $itemCount: Int = 20, $itemCursor: String) {"
                       "    repository(owner: $userLogin, name: $repoName) {"
                       "        nameWithOwner"
                       "        watchers(first: $itemCount, after: $itemCursor) {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET USER PROFILE
static const QString SAILHUB_QUERY_GET_USER =
        QStringLiteral("query($userLogin: String!) {"
                       "    user(login: $userLogin) {"
                       "        avatarUrl"
                       "        bio"
                       "        company"
                       "        followers {"
                       "            totalCount"
                       "        }"
                       "        following {"
                       "            totalCount"
                       "        }"
                       "        location"
                       "        login"
                       "        name"
                       "        organizations {"
                       "            totalCount"
                       "        }"
                       "        repositories {"
                       "            totalCount"
                       "        }"
                       "        starredRepositories {"
                       "            totalCount"
                       "        }"
                       "        status {"
                       "            emoji"
                       "            message"
                       "        }"
                       "        twitterUsername"
                       "        websiteUrl"
                       "    }"
                       "}");

// GET USER FOLLOWERS
static const QString SAILHUB_QUERY_GET_USER_FOLLOWERS =
        QStringLiteral("query($userLogin: String!,$itemCount: Int = 20, $itemCursor: String = null) {"
                       "    user(login: $userLogin) {"
                       "        login"
                       "        followers(first: $itemCount, after: $itemCursor) {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET USER FOLLOWERS
static const QString SAILHUB_QUERY_GET_USER_FOLLOWING =
        QStringLiteral("query($userLogin: String!,$itemCount: Int = 20, $itemCursor: String = null) {"
                       "    user(login: $userLogin) {"
                       "        login"
                       "        following(first: $itemCount, after: $itemCursor) {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_USER_LIST_ITEM).simplified();

// GET USER REPOSITORIES
static const QString SAILHUB_QUERY_GET_USER_REPOSITORIES =
        QStringLiteral("query($userLogin: String!, $itemCount: Int = 20, $itemCursor: String = null) {"
                       "    user(login: $userLogin) {"
                       "       login"
                       "       repositories(first: $itemCount, after: $itemCursor) {"
                       "           %1"
                       "       }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_PART_REPO_LIST_ITEM).simplified();


#endif // QUERIES_H

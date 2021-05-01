#ifndef QUERIES_H
#define QUERIES_H

#include <QString>

#include "query_items.h"

// ------------------------------------------------------------------------------------------------------------------
// QUERIES
// ------------------------------------------------------------------------------------------------------------------

// GET GIST
static const QString SAILHUB_QUERY_GET_DISCUSSION =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Discussion {"
                       "            id"
                       "            activeLockReason"
                       "            answerChosenAt"
                       "            answerChosenBy {"
                       "                login"
                       "                avatarUrl"
                       "            }"
                       "            author {"
                       "                login"
                       "                avatarUrl"
                       "            }"
                       "            body"
                       "            category {"
                       "                id"
                       "                name"
                       "                emojiHTML"
                       "            }"
                       "            comments {"
                       "                totalCount"
                       "            }"
                       "            createdAt"
                       "            createdViaEmail"
                       "            editor {"
                       "                login"
                       "                avatarUrl"
                       "            }"
                       "            lastEditedAt"
                       "            locked"
                       "            number"
                       "            publishedAt"
                       "            reactionGroups {"
                       "                ... on ReactionGroup {"
                       "                    content"
                       "                    users {"
                       "                        totalCount"
                       "                    }"
                       "                    viewerHasReacted"
                       "                }"
                       "            }"
                       "            repository {"
                       "                id"
                       "                nameWithOwner"
                       "            }"
                       "            title"
                       "            updatedAt"
                       "            viewerCanDelete"
                       "            viewerCanReact"
                       "            viewerCanSubscribe"
                       "            viewerCanUpdate"
                       "            viewerDidAuthor"
                       "            viewerSubscription"
                       "        }"
                       "    }"
                       "    "
                       "}").simplified();

// GET GIST
static const QString SAILHUB_QUERY_GET_GIST =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Gist {"
                       "            id"
                       "            comments {"
                       "                totalCount"
                       "            }"
                       "            createdAt"
                       "            description"
                       "            forks {"
                       "                totalCount"
                       "            }"
                       "            isFork"
                       "            isPublic"
                       "            name"
                       "            owner {"
                       "                id"
                       "                avatarUrl"
                       "                login"
                       "            }"
                       "            pushedAt"
                       "            stargazerCount"
                       "            updatedAt"
                       "            viewerHasStarred"
                       "        }"
                       "    }"
                       "    "
                       "}").simplified();

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
                       "            assignees {"
                       "                totalCount"
                       "            }"
                       "            author {"
                       "                avatarUrl"
                       "                login"
                       "            }"
                       "            body"
                       "            comments {"
                       "                totalCount"
                       "            }"
                       "            createdAt"
                       "            labels {"
                       "                totalCount"
                       "            }"
                       "            number"
                       "            participants {"
                       "                totalCount"
                       "            }"
                       "            reactionGroups {"
                       "                ... on ReactionGroup {"
                       "                    content"
                       "                    users {"
                       "                        totalCount"
                       "                    }"
                       "                    viewerHasReacted"
                       "                }"
                       "            }"
                       "            repository {"
                       "                id"
                       "                nameWithOwner"
                       "                viewerPermission"
                       "            }"
                       "            title"
                       "            state"
                       "            updatedAt"
                       "            viewerCanReact"
                       "            viewerCanSubscribe"
                       "            viewerCanUpdate"
                       "            viewerDidAuthor"
                       "        }"
                       "    }"
                       "    "
                       "}").simplified();


// GET ORGANIZATION PROFILE
static const QString SAILHUB_QUERY_GET_ORGANIZATION =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Organization {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ORGANIZATION).simplified();

// GET ISSUE
static const QString SAILHUB_QUERY_GET_PULL_REQUEST =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on PullRequest {"
                       "            id"
                       "            assignees {"
                       "                totalCount"
                       "            }"
                       "            author {"
                       "                avatarUrl"
                       "                login"
                       "            }"
                       "            body"
                       "            comments {"
                       "                totalCount"
                       "            }"
                       "            createdAt"
                       "            labels {"
                       "                totalCount"
                       "            }"
                       "            number"
                       "            participants {"
                       "                totalCount"
                       "            }"
                       "            reactionGroups {"
                       "                ... on ReactionGroup {"
                       "                    content"
                       "                    users {"
                       "                        totalCount"
                       "                    }"
                       "                    viewerHasReacted"
                       "                }"
                       "            }"
                       "            repository {"
                       "                id"
                       "                nameWithOwner"
                       "                viewerPermission"
                       "            }"
                       "            title"
                       "            state"
                       "            updatedAt"
                       "            viewerCanApplySuggestion"
                       "            viewerCanDeleteHeadRef"
                       "            viewerCanDisableAutoMerge"
                       "            viewerCanEnableAutoMerge"
                       "            viewerCanReact"
                       "            viewerCanSubscribe"
                       "            viewerCanUpdate"
                       "            viewerDidAuthor"
                       "        }"
                       "    }"
                       "    "
                       "}").simplified();


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

// GET RELEASE
static const QString SAILHUB_QUERY_GET_RELEASE =
        QStringLiteral("query($nodeId: ID!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Release {"
                       "            id"
                       "            author {"
                       "                avatarUrl"
                       "                login"
                       "            }"
                       "            createdAt"
                       "            description"
                       "            isDraft"
                       "            isLatest"
                       "            isPrerelease"
                       "            name"
                       "            publishedAt"
                       "            releaseAssets {"
                       "                totalCount"
                       "            }"
                       "            repository {"
                       "                nameWithOwner"
                       "            }"
                       "            tagCommit {"
                       "                abbreviatedOid"
                       "            }"
                       "            tagName"
                       "        }"
                       "    }"
                       "}").simplified();

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
                       "            defaultBranchRef {"
                       "                id"
                       "                name"
                       "            }"
                       "            description"
                       "            discussions {"
                       "                totalCount"
                       "            }"
                       "            forkCount"
                       "            fundingLinks {"
                       "                platform"
                       "            }"
                       "            hasIssuesEnabled"
                       "            hasProjectsEnabled"
                       "            hasWikiEnabled"
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
                       "            projects {"
                       "                totalCount"
                       "            }"
                       "            pullRequests(states: [OPEN]) {"
                       "                totalCount"
                       "            }"
                       "            refs(first: 100, refPrefix: \"refs/heads/\") {"
                       "                totalCount"
                       "                nodes {"
                       "                    id"
                       "                    name"
                       "                }"
                       "            }"
                       "            releases {"
                       "                totalCount"
                       "            }"
                       "            stargazerCount"
                       "            viewerCanSubscribe"
                       "            viewerHasStarred"
                       "            viewerPermission"
                       "            viewerSubscription"
                       "            watchers {"
                       "                totalCount"
                       "            }"
//                       "            object(expression: \"master:README.md\") {"
//                       "                ... on Blob {"
//                       "                    text"
//                       "                }"
//                       "            }"
                       "        }"
                       "    }"
                       "}").simplified();



// GET REPOSITORY PULL REQUESTS
static const QString SAILHUB_QUERY_GET_REPOSITORY_FILE_CONTENT =
        QStringLiteral("query($nodeId: ID!, $branch: String!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    node(id: $nodeId) {"
                       "        ... on Repository {"
                       "            id"
                       "            object(expression: $branch) {"
                       "                ... on Blob {"
                       "                    byteSize"
                       "                    isBinary"
                       "                    text"
                       "                }"
                       "            }"
                       "        }"
                       "    }"
                       "}").simplified();


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

// GET USER PROFILE BY LOGIN
static const QString SAILHUB_QUERY_GET_USER_BY_LOGIN =
        QStringLiteral("query($userLogin: String!) {"
                       "    rateLimit {"
                       "        remaining"
                       "        resetAt"
                       "    }"
                       "    user(login: $userLogin) {"
                       "        ... on User {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_USER).simplified();


#endif // QUERIES_H

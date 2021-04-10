#ifndef MUTATIONS_H
#define MUTATIONS_H

#include <QString>

#include "query_items.h"

// ------------------------------------------------------------------------------------------------------------------
// VARS
// ------------------------------------------------------------------------------------------------------------------
static const QString SAILHUB_MUTATION_VAR_INPUT               = QStringLiteral("input");

// ------------------------------------------------------------------------------------------------------------------
// MUTATIONS
// ------------------------------------------------------------------------------------------------------------------

// ADD COMMENT
static const QString SAILHUB_MUTATION_ADD_COMMENT =
        QStringLiteral("mutation($input: AddCommentInput!) {"
                       "    addComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// ADD ISSUE
static const QString SAILHUB_MUTATION_CREATE_ISSUE =
        QStringLiteral("mutation($input: CreateIssueInput!) {"
                       "    createIssue(input: $input) {"
                       "        clientMutationId"
                       "        issue {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM).simplified();

// CLOSE ISSUE
static const QString SAILHUB_MUTATION_CLOSE_ISSUE =
        QStringLiteral("mutation($input: CloseIssueInput!) {"
                       "    closeIssue(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// DELETE COMMENT
static const QString SAILHUB_MUTATION_DELETE_COMMENT =
        QStringLiteral("mutation($input: DeleteIssueCommentInput!) {"
                       "    deleteIssueComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// DELETE ISSUE
static const QString SAILHUB_MUTATION_DELETE_ISSUE =
        QStringLiteral("mutation($input: DeleteIssueInput!) {"
                       "    deleteIssue(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// FOLLOW USER
static const QString SAILHUB_MUTATION_FOLLOW_USER =
        QStringLiteral("mutation($input: FollowUserInput!) {"
                       "    followUser(input: $input) {"
                       "        clientMutationId"
                       "        user {"
                       "            id"
                       "            login"
                       "        }"
                       "    }"
                       "}").simplified();
// UNFOLLOW USER
static const QString SAILHUB_MUTATION_UNFOLLOW_USER =
        QStringLiteral("mutation($input: UnfollowUserInput!) {"
                       "    unfollowUser(input: $input) {"
                       "        clientMutationId"
                       "        user {"
                       "            id"
                       "            login"
                       "        }"
                       "    }"
                       "}").simplified();

// STAR REPO
static const QString SAILHUB_MUTATION_REPO_ADD_STAR =
        QStringLiteral("mutation($input: AddStarInput!) {"
                       "    addStar(input: $input) {"
                       "        clientMutationId"
                       "        starrable {"
                       "            id"
                       "        }"
                       "    }"
                       "}").simplified();

// UPDATE COMMENT
static const QString SAILHUB_MUTATION_UPDATE_COMMENT =
        QStringLiteral("mutation($input: UpdateIssueCommentInput!) {"
                       "    updateIssueComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// UPDATE ISSUE
static const QString SAILHUB_MUTATION_UPDATE_ISSUE =
        QStringLiteral("mutation($input: UpdateIssueInput!) {"
                       "    updateIssue(input: $input) {"
                       "        clientMutationId"
                       "        issue {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM).simplified();

// UNSTAR REPO
static const QString SAILHUB_MUTATION_REPO_REMOVE_STAR =
        QStringLiteral("mutation($input: RemoveStarInput!) {"
                       "    removeStar(input: $input) {"
                       "        clientMutationId"
                       "        starrable {"
                       "            id"
                       "        }"
                       "    }"
                       "}").simplified();

// UPDATE REPO SUBSCRIPTION
static const QString SAILHUB_MUTATION_REPO_UPATE_SUBSCRIPTION =
        QStringLiteral("mutation($input: UpdateSubscriptionInput!) {"
                       "    updateSubscription(input: $input) {"
                       "        clientMutationId"
                       "        subscribable {"
                       "            id"
                       "            viewerSubscription"
                       "        }"
                       "    }"
                       "}").simplified();


#endif // MUTATIONS_H

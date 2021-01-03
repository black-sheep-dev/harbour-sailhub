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

// ADD ISSUE
static const QString SAILHUB_MUTATION_ADD_ISSUE =
        QStringLiteral("mutation($input: CreateIssueInput!) {"
                       "    createIssue(input: $input) {"
                       "        clientMutationId"
                       "        issue {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM).simplified();

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

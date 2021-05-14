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

// ASSIGN USERS TO ASSIGNABLE
static const QString SAILHUB_MUTATION_ASSIGN_USERS_TO_ASSIGNABLE =
        QStringLiteral("mutation($input: AddAssigneesToAssignableInput!) {"
                       "    addAssigneesToAssignable(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// UNASSIGN USERS FROM ASSIGNABLE
static const QString SAILHUB_MUTATION_UNASSIGN_USERS_FROM_ASSIGNABLE =
        QStringLiteral("mutation($input: RemoveAssigneesFromAssignableInput!) {"
                       "    removeAssigneesFromAssignable(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// ADD COMMENT
static const QString SAILHUB_MUTATION_ADD_COMMENT =
        QStringLiteral("mutation($input: AddCommentInput!) {"
                       "    addComment(input: $input) {"
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

// CREATE DISCUSSION
static const QString SAILHUB_MUTATION_CREATE_DISCUSSION =
        QStringLiteral("mutation($input: CreateDiscussionInput!) {"
                       "    createDiscussion(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// DELETE DISCUSSION
static const QString SAILHUB_MUTATION_DELETE_DISCUSSION =
        QStringLiteral("mutation($input: DeleteDiscussionInput!) {"
                       "    deleteDiscussion(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// UPDATE DISCUSSION
static const QString SAILHUB_MUTATION_UPDATE_DISCUSSION =
        QStringLiteral("mutation($input: UpdateDiscussionInput!) {"
                       "    updateDiscussion(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// ADD DISCUSSION COMMENT
static const QString SAILHUB_MUTATION_ADD_DISCUSSION_COMMENT =
        QStringLiteral("mutation($input: AddDiscussionCommentInput!) {"
                       "    addDiscussionComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// DELETE DISCUSSION COMMENT
static const QString SAILHUB_MUTATION_DELETE_DISCUSSION_COMMENT =
        QStringLiteral("mutation($input: DeleteDiscussionCommentInput!) {"
                       "    deleteDiscussionComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// UPDATE DISCUSSION COMMENT
static const QString SAILHUB_MUTATION_UPDATE_DISCUSSION_COMMENT =
        QStringLiteral("mutation($input: UpdateDiscussionCommentInput!) {"
                       "    updateDiscussionComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// MARK DISCUSSION COMMENT AS ANSWER
static const QString SAILHUB_MUTATION_MARK_DISCUSSION_COMMENT_AS_ANSWER =
        QStringLiteral("mutation($input: MarkDiscussionCommentAsAnswerInput!) {"
                       "    markDiscussionCommentAsAnswer(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// UNMARK DISCUSSION COMMENT AS ANSWER
static const QString SAILHUB_MUTATION_UNMARK_DISCUSSION_COMMENT_AS_ANSWER =
        QStringLiteral("mutation($input: UnmarkDiscussionCommentAsAnswerInput!) {"
                       "    unmarkDiscussionCommentAsAnswer(input: $input) {"
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

// DELETE ISSUE
static const QString SAILHUB_MUTATION_DELETE_ISSUE =
        QStringLiteral("mutation($input: DeleteIssueInput!) {"
                       "    deleteIssue(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// REACTION ADD
static const QString SAILHUB_MUTATION_ADD_REACTION =
        QStringLiteral("mutation($input: AddReactionInput!) {"
                       "    addReaction(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// REACTION REMOVE
static const QString SAILHUB_MUTATION_REMOVE_REACTION =
        QStringLiteral("mutation($input: RemoveReactionInput!) {"
                       "    removeReaction(input: $input) {"
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

// UPDATE REPO SUBSCRIPTION
static const QString SAILHUB_MUTATION_CHANGE_PROFILE_STATUS =
        QStringLiteral("mutation($input: ChangeUserStatusInput!) {"
                       "    changeUserStatus(input: $input) {"
                       "        clientMutationId"
                       "        status {"
                       "            createdAt"
                       "            emoji"
                       "            emojiHTML"
                       "            expiresAt"
                       "            id"
                       "            indicatesLimitedAvailability"
                       "            message"
                       "            organization {"
                       "                avatarUrl"
                       "                id"
                       "                login"
                       "            }"
                       "            updatedAt"
                       "        }"
                       "    }"
                       "}").simplified();


#endif // MUTATIONS_H

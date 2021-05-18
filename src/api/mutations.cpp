#include "mutations.h"

// ----------------------------------------------------------------------------------------------------------------------
// assignable
// ----------------------------------------------------------------------------------------------------------------------

const QString Mutation::ASSIGN_USERS_TO_ASSIGNABLE =
        QStringLiteral("mutation($input: AddAssigneesToAssignableInput!) {"
                       "    addAssigneesToAssignable(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();


const QString Mutation::UNASSIGN_USERS_FROM_ASSIGNABLE =
        QStringLiteral("mutation($input: RemoveAssigneesFromAssignableInput!) {"
                       "    removeAssigneesFromAssignable(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();


// ----------------------------------------------------------------------------------------------------------------------
// comments
// ----------------------------------------------------------------------------------------------------------------------
const QString Mutation::ADD_COMMENT =
        QStringLiteral("mutation($input: AddCommentInput!) {"
                       "    addComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::DELETE_COMMENT =
        QStringLiteral("mutation($input: DeleteIssueCommentInput!) {"
                       "    deleteIssueComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::UPDATE_COMMENT =
        QStringLiteral("mutation($input: UpdateIssueCommentInput!) {"
                       "    updateIssueComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// ----------------------------------------------------------------------------------------------------------------------
// discussion
// ----------------------------------------------------------------------------------------------------------------------
const QString Mutation::CREATE_DISCUSSION =
        QStringLiteral("mutation($input: CreateDiscussionInput!) {"
                       "    createDiscussion(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::DELETE_DISCUSSION =
        QStringLiteral("mutation($input: DeleteDiscussionInput!) {"
                       "    deleteDiscussion(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::UPDATE_DISCUSSION =
        QStringLiteral("mutation($input: UpdateDiscussionInput!) {"
                       "    updateDiscussion(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();


// ----------------------------------------------------------------------------------------------------------------------
// discussion comment
// ----------------------------------------------------------------------------------------------------------------------
const QString Mutation::ADD_DISCUSSION_COMMENT =
        QStringLiteral("mutation($input: AddDiscussionCommentInput!) {"
                       "    addDiscussionComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::DELETE_DISCUSSION_COMMENT =
        QStringLiteral("mutation($input: DeleteDiscussionCommentInput!) {"
                       "    deleteDiscussionComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::MARK_DISCUSSION_COMMENT_AS_ANSWER =
        QStringLiteral("mutation($input: MarkDiscussionCommentAsAnswerInput!) {"
                       "    markDiscussionCommentAsAnswer(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::UNMARK_DISCUSSION_COMMENT_AS_ANSWER =
        QStringLiteral("mutation($input: UnmarkDiscussionCommentAsAnswerInput!) {"
                       "    unmarkDiscussionCommentAsAnswer(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::UPDATE_DISCUSSION_COMMENT =
        QStringLiteral("mutation($input: UpdateDiscussionCommentInput!) {"
                       "    updateDiscussionComment(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// ----------------------------------------------------------------------------------------------------------------------
// issue
// ----------------------------------------------------------------------------------------------------------------------

const QString Mutation::CREATE_ISSUE =
        QStringLiteral("mutation($input: CreateIssueInput!) {"
                       "    createIssue(input: $input) {"
                       "        clientMutationId"
                       "        issue {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM).simplified();

const QString Mutation::CLOSE_ISSUE =
        QStringLiteral("mutation($input: CloseIssueInput!) {"
                       "    closeIssue(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();


const QString Mutation::DELETE_ISSUE =
        QStringLiteral("mutation($input: DeleteIssueInput!) {"
                       "    deleteIssue(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();


const QString Mutation::REOPEN_ISSUE =
        QStringLiteral("mutation($input: ReopenIssueInput!) {"
                       "    reopenIssue(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::UPDATE_ISSUE =
        QStringLiteral("mutation($input: UpdateIssueInput!) {"
                       "    updateIssue(input: $input) {"
                       "        clientMutationId"
                       "        issue {"
                       "            %1"
                       "        }"
                       "    }"
                       "}").arg(SAILHUB_QUERY_ITEM_ISSUE_LIST_ITEM).simplified();

// ----------------------------------------------------------------------------------------------------------------------
// pull request
// ----------------------------------------------------------------------------------------------------------------------

const QString Mutation::CLOSE_PULL_REQUEST =
        QStringLiteral("mutation($input: ClosePullRequestInput!) {"
                       "    closePullRequest(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::MERGE_PULL_REQUEST =
        QStringLiteral("mutation($input: MergePullRequestInput!) {"
                       "    mergePullRequest(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::REOPEN_PULL_REQUEST =
        QStringLiteral("mutation($input: ReopenPullRequestInput!) {"
                       "    reopenPullRequest(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

const QString Mutation::UPDATE_PULL_REQUEST =
        QStringLiteral("mutation($input: UpdatePullRequestInput!) {"
                       "    updatePullRequest(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// ----------------------------------------------------------------------------------------------------------------------
// status
// ----------------------------------------------------------------------------------------------------------------------

const QString Mutation::CHANGE_PROFILE_STATUS =
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

// ----------------------------------------------------------------------------------------------------------------------
// subscribeable
// ----------------------------------------------------------------------------------------------------------------------

const QString Mutation::UPATE_SUBSCRIPTION =
        QStringLiteral("mutation($input: UpdateSubscriptionInput!) {"
                       "    updateSubscription(input: $input) {"
                       "        clientMutationId"
                       "        subscribable {"
                       "            id"
                       "            viewerSubscription"
                       "        }"
                       "    }"
                       "}").simplified();

// ----------------------------------------------------------------------------------------------------------------------
// reactable
// ----------------------------------------------------------------------------------------------------------------------

const QString Mutation::ADD_REACTION =
        QStringLiteral("mutation($input: AddReactionInput!) {"
                       "    addReaction(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// REACTION REMOVE
const QString Mutation::REMOVE_REACTION =
        QStringLiteral("mutation($input: RemoveReactionInput!) {"
                       "    removeReaction(input: $input) {"
                       "        clientMutationId"
                       "    }"
                       "}").simplified();

// ----------------------------------------------------------------------------------------------------------------------
// starabel
// ----------------------------------------------------------------------------------------------------------------------

// STAR REPO
const QString Mutation::ADD_STAR =
        QStringLiteral("mutation($input: AddStarInput!) {"
                       "    addStar(input: $input) {"
                       "        clientMutationId"
                       "        starrable {"
                       "            id"
                       "        }"
                       "    }"
                       "}").simplified();

// UNSTAR REPO
const QString Mutation::REMOVE_STAR =
        QStringLiteral("mutation($input: RemoveStarInput!) {"
                       "    removeStar(input: $input) {"
                       "        clientMutationId"
                       "        starrable {"
                       "            id"
                       "        }"
                       "    }"
                       "}").simplified();

// ----------------------------------------------------------------------------------------------------------------------
// user
// ----------------------------------------------------------------------------------------------------------------------

const QString Mutation::FOLLOW_USER =
        QStringLiteral("mutation($input: FollowUserInput!) {"
                       "    followUser(input: $input) {"
                       "        clientMutationId"
                       "        user {"
                       "            id"
                       "            login"
                       "        }"
                       "    }"
                       "}").simplified();

const QString Mutation::UNFOLLOW_USER =
        QStringLiteral("mutation($input: UnfollowUserInput!) {"
                       "    unfollowUser(input: $input) {"
                       "        clientMutationId"
                       "        user {"
                       "            id"
                       "            login"
                       "        }"
                       "    }"
                       "}").simplified();

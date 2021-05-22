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

struct Mutation {
    // assignable
    static const QString ASSIGN_USERS_TO_ASSIGNABLE;
    static const QString UNASSIGN_USERS_FROM_ASSIGNABLE;

    // comment
    static const QString ADD_COMMENT;
    static const QString DELETE_COMMENT;
    static const QString UPDATE_COMMENT;

    // discussion
    static const QString CREATE_DISCUSSION;
    static const QString DELETE_DISCUSSION;
    static const QString UPDATE_DISCUSSION;

    // discussion comment
    static const QString ADD_DISCUSSION_COMMENT;
    static const QString DELETE_DISCUSSION_COMMENT;
    static const QString MARK_DISCUSSION_COMMENT_AS_ANSWER;
    static const QString UNMARK_DISCUSSION_COMMENT_AS_ANSWER;
    static const QString UPDATE_DISCUSSION_COMMENT;

    // issue
    static const QString CREATE_ISSUE;
    static const QString CLOSE_ISSUE;
    static const QString DELETE_ISSUE;
    static const QString REOPEN_ISSUE;
    static const QString UPDATE_ISSUE;

    // lockable
    static const QString LOCK_LOCKABLE;
    static const QString UNLOCK_LOCKABLE;

    // pull request
    static const QString CLOSE_PULL_REQUEST;
    static const QString MERGE_PULL_REQUEST;
    static const QString REOPEN_PULL_REQUEST;
    static const QString UPDATE_PULL_REQUEST;

    // reactable
    static const QString ADD_REACTION;
    static const QString REMOVE_REACTION;

    // starable
    static const QString ADD_STAR;
    static const QString REMOVE_STAR;

    // status
    static const QString CHANGE_PROFILE_STATUS;

    // subscribeable
    static const QString UPATE_SUBSCRIPTION;

    // user
    static const QString FOLLOW_USER;
    static const QString UNFOLLOW_USER;
};


#endif // MUTATIONS_H

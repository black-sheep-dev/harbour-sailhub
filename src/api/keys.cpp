#include "keys.h"

// ApiKey
const QString ApiKey::ABBREVIATED_OID                   = QStringLiteral("abbreviatedOid");
const QString ApiKey::ACTIVE_LOCK_REASON                = QStringLiteral("activeLockReason");
const QString ApiKey::ADD_STAR                          = QStringLiteral("addStar");
const QString ApiKey::ADDITIONS                         = QStringLiteral("additions");
const QString ApiKey::ANSWER_CHOSEN_AT                  = QStringLiteral("answerChosenAt");
const QString ApiKey::ANSWER_CHOSEN_BY                  = QStringLiteral("answerChosenBy");
const QString ApiKey::ASSIGNABLE_ID                     = QStringLiteral("assignableId");
const QString ApiKey::ASSIGNABLE_USERS                  = QStringLiteral("assignableUsers");
const QString ApiKey::ASSIGNEE_IDS                      = QStringLiteral("assigneeIds");
const QString ApiKey::ASSIGNEES                         = QStringLiteral("assignees");
const QString ApiKey::AUTHOR                            = QStringLiteral("author");
const QString ApiKey::AUTHORS                           = QStringLiteral("authors");
const QString ApiKey::AUTHORED_BY_COMMITTER             = QStringLiteral("authoredByCommitter");
const QString ApiKey::AVATAR_URL                        = QStringLiteral("avatarUrl");
const QString ApiKey::BASE_REF_NAME                     = QStringLiteral("baseRefName");
const QString ApiKey::BIO                               = QStringLiteral("bio");
const QString ApiKey::BODY                              = QStringLiteral("body");
const QString ApiKey::BODY_HTML                         = QStringLiteral("bodyHTML");
const QString ApiKey::BODY_TEXT                         = QStringLiteral("bodyText");
const QString ApiKey::CAN_BE_REBASED                    = QStringLiteral("canBeRebased");
const QString ApiKey::CATEGORY                          = QStringLiteral("category");
const QString ApiKey::CATEGORY_ID                       = QStringLiteral("categoryId");
const QString ApiKey::CHANGE_USER_STATUS                = QStringLiteral("changeUserStatus");
const QString ApiKey::CHANGED_FILES                     = QStringLiteral("changedFiles");
const QString ApiKey::CLIENT_MUTATION_ID                = QStringLiteral("clientMutationId");
const QString ApiKey::CLOSED                            = QStringLiteral("closed");
const QString ApiKey::COLLABORATORS                     = QStringLiteral("collaborators");
const QString ApiKey::COLOR                             = QStringLiteral("color");
const QString ApiKey::COMMENT_ID                        = QStringLiteral("commentId");
const QString ApiKey::COMMENTS                          = QStringLiteral("comments");
const QString ApiKey::COMMIT                            = QStringLiteral("commit");
const QString ApiKey::COMMITS                           = QStringLiteral("commits");
const QString ApiKey::COMMITTED_DATE                    = QStringLiteral("committedDate");
const QString ApiKey::COMMITTER                         = QStringLiteral("committer");
const QString ApiKey::COMPANY                           = QStringLiteral("company");
const QString ApiKey::CONTENT                           = QStringLiteral("content");
const QString ApiKey::CONTENT_TYPE                      = QStringLiteral("contentType");
const QString ApiKey::CREATED_AT                        = QStringLiteral("createdAt");
const QString ApiKey::CREATED_VIA_EMAIL                 = QStringLiteral("createdViaEmail");
const QString ApiKey::DATA                              = QStringLiteral("data");
const QString ApiKey::DATE                              = QStringLiteral("date");
const QString ApiKey::DEFAULT_BRANCH_REF                = QStringLiteral("defaultBranchRef");
const QString ApiKey::DELETED_AT                        = QStringLiteral("deletedAt");
const QString ApiKey::DELETIONS                         = QStringLiteral("deletions");
const QString ApiKey::DESCRIPTION                       = QStringLiteral("description");
const QString ApiKey::DISCUSSION                        = QStringLiteral("discussion");
const QString ApiKey::DISCUSSION_CATEGORIES             = QStringLiteral("discussionCategories");
const QString ApiKey::DISCUSSION_ID                     = QStringLiteral("discussionId");
const QString ApiKey::DISCUSSIONS                       = QStringLiteral("discussions");
const QString ApiKey::DOWNLOAD_COUNT                    = QStringLiteral("downloadCount");
const QString ApiKey::DOWNLOAD_URL                      = QStringLiteral("downloadUrl");
const QString ApiKey::EDGES                             = QStringLiteral("edges");
const QString ApiKey::EDITOR                            = QStringLiteral("editor");
const QString ApiKey::EMAIL                             = QStringLiteral("email");
const QString ApiKey::EMOJI                             = QStringLiteral("emoji");
const QString ApiKey::EMOJI_HTML                        = QStringLiteral("emojiHTML");
const QString ApiKey::END_CURSOR                        = QStringLiteral("endCursor");
const QString ApiKey::ENTRIES                           = QStringLiteral("entries");
const QString ApiKey::EXPIRES_AT                        = QStringLiteral("expiresAt");
const QString ApiKey::EXTENSION                         = QStringLiteral("extension");
const QString ApiKey::FILE                              = QStringLiteral("file");
const QString ApiKey::FILES                             = QStringLiteral("files");
const QString ApiKey::FOLLOWER_USER                     = QStringLiteral("followUser");
const QString ApiKey::FOLLOWERS                         = QStringLiteral("followers");
const QString ApiKey::FOLLOWING                         = QStringLiteral("following");
const QString ApiKey::FORK_COUNT                        = QStringLiteral("forkCount");
const QString ApiKey::FORKS                             = QStringLiteral("forks");
const QString ApiKey::FUNDING_LINKS                     = QStringLiteral("fundingLinks");
const QString ApiKey::GISTS                             = QStringLiteral("gists");
const QString ApiKey::HAS_ISSUES_ENABLED                = QStringLiteral("hasIssuesEnabled");
const QString ApiKey::HAS_NEXT_PAGE                     = QStringLiteral("hasNextPage");
const QString ApiKey::HAS_PROJECTS_ENABLED              = QStringLiteral("hasProjectsEnabled");
const QString ApiKey::HAS_WIKI_ENABLED                  = QStringLiteral("hasWikiEnabled");
const QString ApiKey::HEAD_REF_NAME                     = QStringLiteral("headRefName");
const QString ApiKey::HOMEPAGE_URL                      = QStringLiteral("homepageUrl");
const QString ApiKey::ID                                = QStringLiteral("id");
const QString ApiKey::INCLUDES_CREATED_EDIT             = QStringLiteral("includesCreatedEdit");
const QString ApiKey::INDICATES_LIMITED_AVAILABILITY    = QStringLiteral("indicatesLimitedAvailability");
const QString ApiKey::IS_ANSWER                         = QStringLiteral("isAnswer");
const QString ApiKey::IS_ARCHIVED                       = QStringLiteral("isArchived");
const QString ApiKey::IS_BINARY                         = QStringLiteral("isBinary");
const QString ApiKey::IS_BLANK_ISSUES_ENABLED           = QStringLiteral("isBlankIssuesEnabled");
const QString ApiKey::IS_CROSS_REPOSITORY               = QStringLiteral("isCrossRepository");
const QString ApiKey::IS_DISABLED                       = QStringLiteral("isDisabled");
const QString ApiKey::IS_DRAFT                          = QStringLiteral("isDraft");
const QString ApiKey::IS_EMPTY                          = QStringLiteral("isEmpty");
const QString ApiKey::IS_FORK                           = QStringLiteral("isFork");
const QString ApiKey::IS_IN_ORGANIZATION                = QStringLiteral("isInOrganization");
const QString ApiKey::IS_LATEST                         = QStringLiteral("isLatest");
const QString ApiKey::IS_LOCKED                         = QStringLiteral("isLocked");
const QString ApiKey::IS_MINIMIZED                      = QStringLiteral("isMinimized");
const QString ApiKey::IS_MIRROR                         = QStringLiteral("isMirror");
const QString ApiKey::IS_PRERELEASE                     = QStringLiteral("isPrerelease");
const QString ApiKey::IS_PRIVATE                        = QStringLiteral("isPrivate");
const QString ApiKey::IS_PUBLIC                         = QStringLiteral("isPublic");
const QString ApiKey::IS_SECURITY_POLICY_ENABLED        = QStringLiteral("isSecurityPolicyEnabled");
const QString ApiKey::IS_TEMPLATE                       = QStringLiteral("isTemplate");
const QString ApiKey::IS_USER_CONFIGURATION_REPOSITORY  = QStringLiteral("isUserConfigurationRepository ");
const QString ApiKey::IS_VALID                          = QStringLiteral("isValid");
const QString ApiKey::IS_VIEWER                         = QStringLiteral("isViewer");
const QString ApiKey::ISSUE_ID                          = QStringLiteral("issueId");
const QString ApiKey::ISSUE                             = QStringLiteral("issue");
const QString ApiKey::ISSUES                            = QStringLiteral("issues");
const QString ApiKey::LABELS                            = QStringLiteral("labels");
const QString ApiKey::LANGUAGES                         = QStringLiteral("languages");
const QString ApiKey::LAST_EDITED_AT                    = QStringLiteral("lastEditedAt");
const QString ApiKey::LICENSE_INFO                      = QStringLiteral("licenseInfo");
const QString ApiKey::LIMITED_AVAILABILITY              = QStringLiteral("limitedAvailability");
const QString ApiKey::LOCATION                          = QStringLiteral("location");
const QString ApiKey::LOCK_LOCKABLE                     = QStringLiteral("lockLockable");
const QString ApiKey::LOCKABLE_ID                       = QStringLiteral("lockableId");
const QString ApiKey::LOCKED                            = QStringLiteral("locked");
const QString ApiKey::LOCKED_RECORD                     = QStringLiteral("lockedRecord");
const QString ApiKey::LOCK_REASON                       = QStringLiteral("lockReason");
const QString ApiKey::LOGIN                             = QStringLiteral("login");
const QString ApiKey::MAINTAINER_CAN_MODIFY             = QStringLiteral("maintainerCanModify");
const QString ApiKey::MEMBERS_WITH_ROLE                 = QStringLiteral("membersWithRole");
const QString ApiKey::MENTIONABLE_USERS                 = QStringLiteral("mentionableUsers");
const QString ApiKey::MERGE_STATE_STATUS                = QStringLiteral("mergeStateStatus");
const QString ApiKey::MERGEABLE                         = QStringLiteral("mergeable");
const QString ApiKey::MERGED                            = QStringLiteral("merged");
const QString ApiKey::MERGED_AT                         = QStringLiteral("mergedAt");
const QString ApiKey::MERGEG_BY                         = QStringLiteral("mergedBy");
const QString ApiKey::MESSAGE                           = QStringLiteral("message");
const QString ApiKey::MESSAGE_HEADLINE                  = QStringLiteral("messageHeadline");
const QString ApiKey::MINIMIZED_REASON                  = QStringLiteral("minimizedReason");
const QString ApiKey::NAME                              = QStringLiteral("name");
const QString ApiKey::NAME_WITH_OWNER                   = QStringLiteral("nameWithOwner");
const QString ApiKey::NODE                              = QStringLiteral("node");
const QString ApiKey::NODES                             = QStringLiteral("nodes");
const QString ApiKey::NUMBER                            = QStringLiteral("number");
const QString ApiKey::OBJECT                            = QStringLiteral("object");
const QString ApiKey::ORGANIZATION                      = QStringLiteral("organization");
const QString ApiKey::ORGANIZATION_ID                   = QStringLiteral("organizationId");
const QString ApiKey::ORGANIZATIONS                     = QStringLiteral("organizations");
const QString ApiKey::OWNER                             = QStringLiteral("owner");
const QString ApiKey::PAGE_INFO                         = QStringLiteral("pageInfo");
const QString ApiKey::PARENT                            = QStringLiteral("parent");
const QString ApiKey::PARENTS                           = QStringLiteral("parents");
const QString ApiKey::PARTICIPANTS                      = QStringLiteral("participants");
const QString ApiKey::PATH                              = QStringLiteral("path");
const QString ApiKey::PLATFORM                          = QStringLiteral("platform");
const QString ApiKey::PRIMARY_LANGUAGE                  = QStringLiteral("primaryLanguage");
const QString ApiKey::PROJECTS                          = QStringLiteral("projects");
const QString ApiKey::PUBLISHED_AT                      = QStringLiteral("publishedAt");
const QString ApiKey::PULL_REQUEST                      = QStringLiteral("pullRequest");
const QString ApiKey::PULL_REQUEST_ID                   = QStringLiteral("pullRequestId");
const QString ApiKey::PULL_REQUESTS                     = QStringLiteral("pullRequests");
const QString ApiKey::PUSHED_AT                         = QStringLiteral("pushedAt");
const QString ApiKey::PUSHED_DATE                       = QStringLiteral("pushedDate");
const QString ApiKey::RATE_LIMIT                        = QStringLiteral("rateLimit");
const QString ApiKey::REACTION_GROUPS                   = QStringLiteral("reactionGroups");
const QString ApiKey::REF                               = QStringLiteral("ref");
const QString ApiKey::REFS                              = QStringLiteral("refs");
const QString ApiKey::RELEASE_ASSETS                    = QStringLiteral("releaseAssets");
const QString ApiKey::RELEASES                          = QStringLiteral("releases");
const QString ApiKey::REMAINING                         = QStringLiteral("remaining");
const QString ApiKey::REMOVE_STAR                       = QStringLiteral("removeStar");
const QString ApiKey::REPLIES                           = QStringLiteral("replies");
const QString ApiKey::REPLY_TO                          = QStringLiteral("replyTo");
const QString ApiKey::REPLY_TO_ID                       = QStringLiteral("replyToId");
const QString ApiKey::REPOSITORIES                      = QStringLiteral("repositories");
const QString ApiKey::REPOSITORY_COUNT                  = QStringLiteral("repositoryCount");
const QString ApiKey::REPOSITORY                        = QStringLiteral("repository");
const QString ApiKey::REPOSITORY_ID                     = QStringLiteral("repositoryId");
const QString ApiKey::RESET_AT                          = QStringLiteral("resetAt");
const QString ApiKey::SEARCH                            = QStringLiteral("search");
const QString ApiKey::SHORT_DESCRIPTION_HTML            = QStringLiteral("shortDescriptionHTML");
const QString ApiKey::SIGNATURE                         = QStringLiteral("signature");
const QString ApiKey::SIZE                              = QStringLiteral("size");
const QString ApiKey::SPDX_ID                           = QStringLiteral("spdxId");
const QString ApiKey::STARGAZER_COUNT                   = QStringLiteral("stargazerCount");
const QString ApiKey::STARGAZERS                        = QStringLiteral("stargazers");
const QString ApiKey::STARRABLE                         = QStringLiteral("starrable");
const QString ApiKey::STARRABLE_ID                      = QStringLiteral("starrableId");
const QString ApiKey::STARRED_REPOSITORIES              = QStringLiteral("starredRepositories");
const QString ApiKey::STATE                             = QStringLiteral("state");
const QString ApiKey::STATUS                            = QStringLiteral("status");
const QString ApiKey::SUBJECT_ID                        = QStringLiteral("subjectId");
const QString ApiKey::SUBSCRIBABLE                      = QStringLiteral("subscribable");
const QString ApiKey::SUBSCRIBABLE_ID                   = QStringLiteral("subscribableId");
const QString ApiKey::TAG_COMMIT                        = QStringLiteral("tagCommit");
const QString ApiKey::TAG_NAME                          = QStringLiteral("tagName");
const QString ApiKey::TARGET                            = QStringLiteral("target");
const QString ApiKey::TEAMS                             = QStringLiteral("teams");
const QString ApiKey::TEXT                              = QStringLiteral("text");
const QString ApiKey::TITLE                             = QStringLiteral("title");
const QString ApiKey::TOTAL_COUNT                       = QStringLiteral("totalCount");
const QString ApiKey::TREE                              = QStringLiteral("tree");
const QString ApiKey::TWITTER_USERNAME                  = QStringLiteral("twitterUsername");
const QString ApiKey::TYPE                              = QStringLiteral("type");
const QString ApiKey::UNFOLLOW_USER                     = QStringLiteral("unfolloweUser");
const QString ApiKey::UNLOCK_LOCKABLE                   = QStringLiteral("unlockLockable");
const QString ApiKey::UPDATED_AT                        = QStringLiteral("updatedAt");
const QString ApiKey::UPDATE_SUBSCRIPTION               = QStringLiteral("updateSubscription");
const QString ApiKey::URL                               = QStringLiteral("url");
const QString ApiKey::USER                              = QStringLiteral("user");
const QString ApiKey::USERS                             = QStringLiteral("users");
const QString ApiKey::USER_COUNT                        = QStringLiteral("userCount");
const QString ApiKey::USER_ID                           = QStringLiteral("userId");
const QString ApiKey::VIEWER                            = QStringLiteral("viewer");
const QString ApiKey::VIEWER_CAN_ADMINISTER             = QStringLiteral("viewerCanAdminister");
const QString ApiKey::VIEWER_CAN_APPLY_SUGGESTION       = QStringLiteral("viewerCanApplySuggestion");
const QString ApiKey::VIEWER_CAN_CREATE_PROJECTS        = QStringLiteral("viewerCanCreateProjects");
const QString ApiKey::VIEWER_CAN_DELETE                 = QStringLiteral("viewerCanDelete");
const QString ApiKey::VIEWER_CAN_DELETE_HEAD_REF        = QStringLiteral("viewerCanDeleteHeadRef");
const QString ApiKey::VIEWER_CAN_DISABLE_AUTO_MERGE     = QStringLiteral("viewerCanDisableAutoMerge");
const QString ApiKey::VIEWER_CAN_ENABLE_AUTO_MERGE      = QStringLiteral("viewerCanEnableAutoMerge");
const QString ApiKey::VIEWER_CAN_MARK_AS_ANSWER         = QStringLiteral("viewerCanMarkAsAnswer");
const QString ApiKey::VIEWER_CAN_MINIMIZE               = QStringLiteral("viewerCanMinimize");
const QString ApiKey::VIEWER_CAN_REACT                  = QStringLiteral("viewerCanReact");
const QString ApiKey::VIEWER_CAN_SUBSCRIBE              = QStringLiteral("viewerCanSubscribe");
const QString ApiKey::VIEWER_CAN_UNMARK_AS_ANSWER       = QStringLiteral("viewerCanUnmarkAsAnswer");
const QString ApiKey::VIEWER_CAN_UPDATE                 = QStringLiteral("viewerCanUpdate");
const QString ApiKey::VIEWER_CAN_UPDATE_TOPICS          = QStringLiteral("viewerCanTopics");
const QString ApiKey::VIEWER_DID_AUTHOR                 = QStringLiteral("viewerDidAuthor");
const QString ApiKey::VIEWER_IS_MEMBER                  = QStringLiteral("viewerIsAMember");
const QString ApiKey::VIEWER_IS_FOLLOWING               = QStringLiteral("viewerIsFollowing");
const QString ApiKey::VIEWER_IS_SPONSORING              = QStringLiteral("viewerIsSponsoring");
const QString ApiKey::VIEWER_HAS_REACTED                = QStringLiteral("viewerHasReacted");
const QString ApiKey::VIEWER_HAS_STARRED                = QStringLiteral("viewerHasStarred");
const QString ApiKey::VIEWER_PERMISSION                 = QStringLiteral("viewerPermission");
const QString ApiKey::VIEWER_SUBSCRIPTION               = QStringLiteral("viewerSubscription");
const QString ApiKey::VULNERABILITY_ALERTS              = QStringLiteral("vulnerabilityAlerts");
const QString ApiKey::WATCHERS                          = QStringLiteral("watchers");
const QString ApiKey::WEBSITE_URL                       = QStringLiteral("websiteUrl");


// RestApiKey
const QString RestApiKey::FULL_NAME                     = QStringLiteral("full_name");
const QString RestApiKey::LAST_READ_AT                  = QStringLiteral("last_read_at");
const QString RestApiKey::NODE_ID                       = QStringLiteral("node_id");
const QString RestApiKey::REASON                        = QStringLiteral("reason");
const QString RestApiKey::SUBJECT                       = QStringLiteral("subject");;
const QString RestApiKey::UNREAD                        = QStringLiteral("unread");;
const QString RestApiKey::UPDATED_AT                    = QStringLiteral("updated_at");;

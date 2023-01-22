TARGET = harbour-sailhub

CONFIG += sailfishapp_qml
PKGCONFIG += nemonotifications-qt5 keepalive

DISTFILES += qml/harbour-sailhub.qml \
    qml/components/AuthorItem.qml \
    qml/components/CircleImage.qml \
    qml/components/CommentItem.qml \
    qml/components/CommitInfoItem.qml \
    qml/components/CounterItem.qml \
    qml/components/FilesChangedItem.qml \
    qml/components/IconLabel.qml \
    qml/components/IconRelatedItem.qml \
    qml/components/LanguageItem.qml \
    qml/components/MarkdownLabel.qml \
    qml/components/ReactionsInteractiveItem.qml \
    qml/components/TimelineAssignedItem.qml \
    qml/components/TimelineChangedTitleItem.qml \
    qml/components/TimelineCommentItem.qml \
    qml/components/TimelineConnectedItem.qml \
    qml/components/TimelineCrossReferencedItem.qml \
    qml/components/TimelineLabelItem.qml \
    qml/components/TimelinePullRequestCommitItem.qml \
    qml/components/TimelineRequestedReviewItem.qml \
    qml/components/TimelineStandardItem.qml \
    qml/components/TimelineUserItem.qml \
    qml/components/menu/LockableMenuItem.qml \
    qml/components/menu/StartMenuItem.qml \
    qml/components/menu/SubscriptionMenuItem.qml \
    qml/components/Pill.qml \
    qml/components/ProfileStatusItem.qml \
    qml/components/ReactionGridItem.qml \
    qml/components/ReactionLabel.qml \
    qml/components/ReactionsItem.qml \
    qml/components/RelatedItem.qml \
    qml/components/RelatedValueItem.qml \
    qml/components/RepoFlagsItem.qml \
    qml/components/StargazerItem.qml \
    qml/cover/CoverPage.qml \
    qml/delegates/AssetListDelegate.qml \
    qml/delegates/DiscussionListDelegate.qml \
    qml/delegates/GistFileDelegate.qml \
    qml/delegates/GistListDelegate.qml \
    qml/delegates/IssueListDelegate.qml \
    qml/delegates/LabelListDelegate.qml \
    qml/delegates/NotificationListDelegate.qml \
    qml/delegates/OrganizationListDelegate.qml \
    qml/delegates/PullRequestListDelegate.qml \
    qml/delegates/ReleaseListDelegate.qml \
    qml/delegates/RepoListDelegate.qml \
    qml/delegates/TreeListDelegate.qml \
    qml/delegates/UserListDelegate.qml \
    qml/dialogs/AssingLabelsToLabelableDialog.qml \
    qml/dialogs/CloseIssueDialog.qml \
    qml/dialogs/EditCommentDialog.qml \
    qml/dialogs/EditIssueDialog.qml \
    qml/dialogs/EditPullRequestDialog.qml \
    qml/dialogs/SearchDialog.qml \
    qml/dialogs/SelectBranchDialog.qml \
    qml/dialogs/SelectEmojiDialog.qml \
    qml/dialogs/SelectEmojiDialog.qml \
    qml/dialogs/SelectLockReasonDialog.qml \
    qml/dialogs/SelectSubscriptionDialog.qml \
    qml/dialogs/SortSelectionDialog.qml \
    qml/models/NotificationsModel.qml \
    qml/objects/ViewerProfile.qml \
    qml/pages/AboutPage.qml \
    qml/pages/DiscussionsListPage.qml \
    qml/pages/FundingLinksListPage.qml \
    qml/pages/GistPage.qml \
    qml/pages/GistsListPage.qml \
    qml/pages/ImageViewerPage.qml \
    qml/pages/IssuePage.qml \
    qml/pages/IssueSelectionPage.qml \
    qml/pages/IssuesListPage.qml \
    qml/pages/LabelPage.qml \
    qml/pages/LabelsListPage.qml \
    qml/pages/MarkdownViewerPage.qml \
    qml/pages/NitificationsListPage.qml \
    qml/pages/OrganizationPage.qml \
    qml/pages/OrganizationsListPage.qml \
    qml/pages/OverviewPage.qml \
    qml/pages/ProfileStatusPage.qml \
    qml/pages/PullRequestPage.qml \
    qml/pages/PullRequestsListPage.qml \
    qml/pages/PullRequestsSelectionPage.qml \
    qml/pages/ReleaseAssetListPage.qml \
    qml/pages/ReleasePage.qml \
    qml/pages/ReleasesListPage.qml \
    qml/pages/RepoPage.qml \
    qml/pages/ReposListsPage.qml \
    qml/pages/SearchPage.qml \
    qml/pages/SearchRepositioryPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/settings/SettingsNotificartionPage.qml \
    qml/pages/TextFileViewerPage.qml \
    qml/pages/TreeListPage.qml \
    qml/pages/UserPage.qml \
    qml/pages/UsersListPage.qml \
    qml/pages/wizard/WizardIntroPage.qml \
    qml/pages/wizard/WizardTokenPage.qml \
    qml/queries/AddLabelsToLabelableMutation.qml \
    qml/queries/RemoveLabelsFromLabelableMutation.qml \
    qml/queries/assignee/AddAssigneesMutation.qml \
    qml/queries/assignee/RemoveAssigneesMutation.qml \
    qml/queries/AddReactionMutation.qml \
    qml/queries/AddStarMutation.qml \
    qml/queries/BaseQuery.qml \
    qml/queries/comment/AddCommentMutation.qml \
    qml/queries/comment/DeleteCommentMutation.qml \
    qml/queries/comment/UpdateCommentMutation.qml \
    qml/queries/FollowOrganizationMutation.qml \
    qml/queries/FollowUserMutation.qml \
    qml/queries/discussion/AddDiscussionCommentMutation.qml \
    qml/queries/discussion/CreateDiscussionMutation.qml \
    qml/queries/discussion/DeleteDiscussionCommentMutation.qml \
    qml/queries/discussion/DeleteDiscussionMutation.qml \
    qml/queries/discussion/UpdateDiscussionCommentMutation.qml \
    qml/queries/discussion/UpdateDiscussionMutation.qml \
    qml/queries/issue/CloseIssueMutation.qml \
    qml/queries/issue/CreateIssueMutation.qml \
    qml/queries/issue/DeleteIssueMutation.qml \
    qml/queries/issue/ReopenIssueMutation.qml \
    qml/queries/issue/UpdateIssueMutation.qml \
    qml/queries/LockLockableMutation.qml \
    qml/queries/RemoveReactionMutation.qml \
    qml/queries/RemoveStarMutation.qml \
    qml/queries/UnfollowOrganizationMutation.qml \
    qml/queries/UnfollowUserMutation.qml \
    qml/queries/UnlockLockableMutation.qml \
    qml/queries/UpdateSubscription.qml \
    qml/js/datautils.js \
    qml/js/showdown.min.js \
    qml/js/twemoji.min.js \
    qml/queries/pullRequest/ClosePullRequestMutation.qml \
    qml/queries/pullRequest/MergePullRequestMutation.qml \
    qml/queries/pullRequest/ReopenPullRequestMutation.qml \
    qml/queries/pullRequest/UpdatePullRequestMutation.qml \
    qml/tools/DataHelper.qml \
    qml/tools/MarkdownParser.qml \
    qml/views/ListPage.qml \
    qml/api.qml \
    qml/global.qml \
    qml/SailHubStyles.qml \
    qml/qmldir \
    qml/views/TimelinePage.qml \
    rpm/harbour-sailhub.changes \
    rpm/harbour-sailhub.changes.run.in \
    rpm/harbour-sailhub.spec \
    rpm/harbour-sailhub.yaml \
    translations/*.ts \
    harbour-sailhub.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

include(translations/translations.pri)

emoji.files = icons/emoji/*.svg
emoji.path = $$INSTALL_ROOT/usr/share/harbour-sailhub/emoji

icons.files = icons/*.svg
icons.path = $$INSTALL_ROOT/usr/share/harbour-sailhub/icons

images.files = images/*.svg
images.path = $$INSTALL_ROOT/usr/share/harbour-sailhub/images

scaleable.files = icons/scaleable/*.svg
scaleable.path = $$INSTALL_ROOT/usr/share/harbour-sailhub/icons

INSTALLS += emoji icons images scaleable

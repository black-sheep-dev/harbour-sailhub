import QtQuick 2.0

import org.nubecula.harbour.sailhub 1.0

import ".."

QueryObject {
    property string nodeId
    property string content

    query: 'mutation($input: RemoveReactionInput!) {
                removeReaction(input: $input) {
                    subject {
                        reactionGroups {
                            ... on ReactionGroup {
                                content
                                users {
                                    totalCount
                                }
                                viewerHasReacted
                            }
                        }
                    }
                }
            }'

    variables: {
        "input": {
            "clientMutationId": viewerProfile.nodeId,
            "subjectId": nodeId,
            "content": content
        }
    }

    onErrorChanged: notification.showErrorMessage(error)
}

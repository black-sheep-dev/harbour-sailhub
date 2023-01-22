import QtQuick 2.0

import "../."
import "."

BaseQuery {
    property string nodeId
    property string content

    function execute() {
        loading = true
        Api.request({
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
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                subjectId: nodeId,
                                content: content
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to remove reaction"
                            notify.show(qsTrId("id-failed-to-remove-reaction"))
                            return
                        }

                        result = data
                    })
    }
}

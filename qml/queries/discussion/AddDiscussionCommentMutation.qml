import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string body
    property string replyToId

    function getQueryVars() {
        const vars = {}
        vars.input = {}
        vars.input.clientMutationId = viewerProfile.nodeId
        vars.input.discussionId = nodeId
        if (replyToId.length > 0) vars.input.replyToId = replyToId

        return vars
    }

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: AddDiscussionCommentInput!) {
                                    addDiscussionComment(input: $input) {
                                        clientMutationId
                                    }
                                }',
                        variables: getQueryVars()
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to add comment"
                            notify.show(qsTrId("id-failed-to-add-comment"))
                            return
                        }

                        result = data.addDiscussionComment
                    })
    }
}

import QtQuick 2.0

import "../."
import "../../."

BaseQuery {
    property string nodeId
    property string authorEmail
    property string body
    property string headline
    property string mergeMethod: "MERGE"

    function execute() {
        loading = true
        Api.request({
                        query: 'mutation($input: MergePullRequestInput!) {
                                    mergePullRequest(input: $input) {
                                        pullRequest {
                                            state
                                        }
                                    }
                                }',
                        variables: {
                            input: {
                                clientMutationId: viewerProfile.nodeId,
                                pullRequestId: nodeId,
                                authorEmail: authorEmail,
                                commitBody: body,
                                commitHeadline: headline,
                                mergeMethod: mergeMethod
                            }
                        }
                    },
                    function(data, status) {
                        loading = false

                        if (status !== 200) {
                            console.log(JSON.stringify(data))
                            //% "Failed to merge pull request"
                            notify.show(qsTrId("id-failed-to-merge-pull-request"))
                            return
                        }

                        result = data
                    })
    }
}

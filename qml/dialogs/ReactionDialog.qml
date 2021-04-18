import QtQuick 2.0
import Sailfish.Silica 1.0


import org.nubecula.harbour.sailhub 1.0

import "../components/"

Dialog {
    property int reactions: 0

    id: dialog

    DialogHeader {
        id: header
        acceptText: qsTr("Save")
    }

    Grid {
        anchors.top: header.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        ReactionGridItem {
            icon: "qrc:///emoji/thumbs_up"
            selected: reactions & Reaction.ThumbsUp

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.ThumbsUp
                else
                    reactions &= ~Reaction.ThumbsUp
            }
        }
        ReactionGridItem {
            icon: "qrc:///emoji/thumbs_down"
            selected: reactions & Reaction.ThumbsDown

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.ThumbsDown
                else
                    reactions &= ~Reaction.ThumbsDown
            }
        }
        ReactionGridItem {
            icon: "qrc:///emoji/laugh"
            selected: reactions & Reaction.Laugh

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.Laugh
                else
                    reactions &= ~Reaction.Laugh
            }
        }
        ReactionGridItem {
            icon: "qrc:///emoji/hooray"
            selected: reactions & Reaction.Hooray

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.Hooray
                else
                    reactions &= ~Reaction.Hooray
            }
        }
        ReactionGridItem {
            icon: "qrc:///emoji/confused"
            selected: reactions & Reaction.Confused

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.Confused
                else
                    reactions &= ~Reaction.Confused
            }
        }
        ReactionGridItem {
            icon: "qrc:///emoji/heart"
            selected: reactions & Reaction.Heart

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.Heart
                else
                    reactions &= ~Reaction.Heart
            }
        }
        ReactionGridItem {
            icon: "qrc:///emoji/rocket"
            selected: reactions & Reaction.Rocket

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.Rocket
                else
                    reactions &= ~Reaction.Rocket
            }
        }
        ReactionGridItem {
            icon: "qrc:///emoji/eyes"
            selected: reactions & Reaction.Eyes

            onSelectedChanged: {
                if (selected)
                    reactions |= Reaction.Eyes
                else
                    reactions &= ~Reaction.Eyes
            }
        }
    }

    onReactionsChanged: console.log(reactions)
}


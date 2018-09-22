import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: pippo
    width: 300
    height: 300

TableView {
     id: tableView

     frameVisible: false
     sortIndicatorVisible: true

     anchors.fill: parent

//     Layout.minimumWidth: 400
//     Layout.minimumHeight: 240
//     Layout.preferredWidth: 600
//     Layout.preferredHeight: 400

     TableViewColumn {
         id: titleColumn
         title: "Title"
         role: "title"
         movable: false
         resizable: false
         width: tableView.viewport.width - authorColumn.width
     }

     TableViewColumn {
         id: authorColumn
         title: "Author"
         role: "author"
         movable: false
         resizable: false
         width: tableView.viewport.width / 3
     }

     model: SortFilterProxyModel {
         id: proxyModel
         source: sourceModel.count > 0 ? sourceModel : null

         sortOrder: tableView.sortIndicatorOrder
         sortCaseSensitivity: Qt.CaseInsensitive
         sortRole: sourceModel.count > 0 ? tableView.getColumn(tableView.sortIndicatorColumn).role : ""

         filterString: "*" + searchBox.text + "*"
         filterSyntax: SortFilterProxyModel.Wildcard
         filterCaseSensitivity: Qt.CaseInsensitive
     }

     ListModel {
         id: sourceModel
         ListElement {
             title: "Moby-Dick"
             author: "Herman Melville"
         }
         ListElement {
             title: "The Adventures of Tom Sawyer"
             author: "Mark Twain"
         }
         ListElement {
             title: "Cat’s Cradle"
             author: "Kurt Vonnegut"
         }
         ListElement {
             title: "Farenheit 451"
             author: "Ray Bradbury"
         }
         ListElement {
             title: "It"
             author: "Stephen King"
         }
         ListElement {
             title: "On the Road"
             author: "Jack Kerouac"
         }
         ListElement {
             title: "Of Mice and Men"
             author: "John Steinbeck"
         }
         ListElement {
             title: "Do Androids Dream of Electric Sheep?"
             author: "Philip K. Dick"
         }
         ListElement {
             title: "Uncle Tom’s Cabin"
             author: "Harriet Beecher Stowe"
         }
         ListElement {
             title: "The Call of the Wild"
             author: "Jack London"
         }
         ListElement {
             title: "The Old Man and the Sea"
             author: "Ernest Hemingway"
         }
         ListElement {
             title: "A Streetcar Named Desire"
             author: "Tennessee Williams"
         }
         ListElement {
             title: "Catch-22"
             author: "Joseph Heller"
         }
         ListElement {
             title: "One Flew Over the Cuckoo’s Nest"
             author: "Ken Kesey"
         }
         ListElement {
             title: "The Murders in the Rue Morgue"
             author: "Edgar Allan Poe"
         }
         ListElement {
             title: "Breakfast at Tiffany’s"
             author: "Truman Capote"
         }
         ListElement {
             title: "Death of a Salesman"
             author: "Arthur Miller"
         }
         ListElement {
             title: "Post Office"
             author: "Charles Bukowski"
         }
         ListElement {
             title: "Herbert West—Reanimator"
             author: "H. P. Lovecraft"
         }
     }
}
}

//Item {
//    id: item
//    state: "labelMode"

//    Text {
//        id: textLabel
//        text: "PIPPO"; //styleData.value
//        anchors.fill: parent
//        renderType: Text.NativeRendering
//    }

//    TextField {
//        id: textField
//        text: "PUPPA"; //styleData.value
//        anchors.fill: parent

//        Keys.onEnterPressed: commit()
//        Keys.onReturnPressed: commit()
//        Keys.onEscapePressed: rollback()

//        function commit() {
//            item.state = "labelMode"
//        }

//        function rollback() {
//            item.state = "labelMode"
//        }
//    }

//    MouseArea {
//        id: mouseArea
//        anchors.fill: parent
//        onDoubleClicked: item.state = "editMode"
//    }

//    states: [
//        State {
//            name: "labelMode"
//            PropertyChanges {
//                target: textLabel
//                visible: true
//            }
//            PropertyChanges {
//                target: mouseArea
//                visible: true
//            }
//            PropertyChanges {
//                target: textField
//                visible: false
//            }
//        },

//        State {
//            name: "editMode"
//            PropertyChanges {
//                target: textLabel
//                visible: false
//            }
//            PropertyChanges {
//                target: mouseArea
//                visible: false
//            }
//            PropertyChanges {
//                target: textField
//                visible: true
//                focus: true
//            }
//        }
//    ]
//}

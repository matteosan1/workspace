import QtQuick 2.5

Rectangle {

    id: mainArea
    width: 1080
    height: 1920

    property alias buttonRoster: buttonRoster
    property alias buttonLineup: buttonLineup

    MyButton {
        id: buttonRoster
        x: 233
        y: 459
        width: 615
        height: 297
        text: "Modifica Rosa"
        fontSize: 50
    }

    MyButton {
        id: buttonLineup
        x: 232
        y: 1152
        width: 616
        height: 297
        text: qsTr("Consegna Formazione")
        fontSize: 50
    }
}

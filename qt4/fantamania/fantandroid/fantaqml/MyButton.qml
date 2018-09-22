import QtQuick 2.0

Item {
    id: buttonItem
    property string text: ""
    property int fontSize: 10

    signal clicked
    width: 200
    height: 100

    BorderImage {
        id: borderImage1
        anchors.fill: parent
        visible: !mouseArea1.pressed
        source: "button_up.png"
    }

    BorderImage {
        id: borderImage2
        anchors.fill: parent
        visible: mouseArea1.pressed
        source: "button_down.png"
    }

    Text {
        id: text1
        x: 29
        y: 24
        color: "#020b9d"
        text: parent.text
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: parent.fontSize
        scale: if (!mouseArea1.pressed) { 1 } else { 0.95 }
    }

    MouseArea {
        id: mouseArea1
        anchors.fill: parent
    }

    Connections {
        target: mouseArea1
        onClicked: buttonItem.clicked()
    }
}

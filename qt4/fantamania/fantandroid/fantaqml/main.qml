import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Window {
    id: root
    visible: true
    width: 1080
    height: 1920
    title: qsTr("FantAndroid")

    //property variant win; // you can hold this as a reference...
    Rectangle {
    id: mainWindow
    width: 360
    height: 360

    Rectangle {
        id: myButton
            x: 125
            y: 84
            width: 100
            height: 30
            color: "#000000"
            Text {
                anchors.centerIn: parent
                color: "#FFFFFF"
                text: "dialog"
            }
            // This mouse area fills the complete myButton
            // when clicked it will create Dialog.qml dynamically
            // adding it to the rectangle with the id=mainWindow
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    // now we create a dialog QML object dynamically
                    // we do not pass any properties to the dialog so we use {}
                    Qt.createComponent("qrc:/Roster.qml").createObject(root, {});
                }
            }
    }
    }

//    MainForm {
//        anchors.fill: parent

//        buttonLineup.onClicked: messageDialog.open();

//        buttonRoster.onClicked: {
//             Qt.createComponent("Roster.qml").createObject(MainForm, {});
//            //var component = Qt.createComponent("Roster.qml");
//            //win = component.createObject(root);
//            //win.open();
//        }

//    }

//    MessageDialog {
//        id: messageDialog
//        title: "May I have your attention please"
//        text: "It's so cool that you are using Qt Quick."
//        onAccepted: {
//            console.log("And of course you could only agree.")
//            Qt.quit()
//        }
//        Component.onCompleted: visible = false
//    }
}

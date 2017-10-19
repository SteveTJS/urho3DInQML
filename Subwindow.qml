import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id: _windowItem
    property int index
    property int leftOffset
    property alias window: _window
    property int urho_width : 640
    property int urho_height : 480

    signal mySignalToMainWindow(int inIndex)

    Window {
        id: _window
        objectName: "Urho3DWindow"
        visible: true
        title: "QML window with Urho3D"

        Component.onCompleted: {
            x = 200 + leftOffset * index
            y = 40 * (index + 1)
            width = urho_width;
            height = urho_height;
        }

        Rectangle{
            id: dockRectangleLeft
            anchors.fill: parent
            x: 0

            Urho3DComponent{
                id: urho3DComponent;
                x: 0
                y: 0
                width: 640
                height: 480
            }

            Column{
                x: 10
                y: 10
                Text {
                    id: windowText
                    text: qsTr("SubWindowText")
                    color: 'red'
                }

                Button {
                    id: buttonToMainWindow
                    text: "SubWindow " + index
                    onClicked: _windowItem.mySignalToMainWindow(index);
                    z:2;
                }
            }
        }
    }

    function windowFunction()
    {
        if( windowText.text == "Hello" )
            windowText.text = "Bye!"
        else windowText.text = "Hello";
    }

}

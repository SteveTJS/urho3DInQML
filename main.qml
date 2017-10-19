import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtMultimedia 5.4

Window {
    id: _component
    objectName: "myMainWindow"
    title: "MainWindow"

    property int instances: 1 //number of windows to create in addition to the main window

    width: 300
    height: 500;
    visible: true

    property bool mOpticalFlow:false;
    property bool mHarrisPoints:false;


    Component.onCompleted: {
        x = 40
        y = 40
    }

    //one window
    Subwindow {
        id: myUrho3DView
        objectName : "MyUrho3DView"
        index: 1
        leftOffset: _component.width
        onMySignalToMainWindow: testConnection(inIndex);
        visible: false
    }
    Column {
        Button {
            text: "Delete Urho3DApplication"
            onClicked:{
                mUrho3DManager.deleteUrho3D();
            }
        }
        Button {
            text: "Window 1"
            onClicked:{
                myUrho3DView.windowFunction();
            }
        }
        Text{
            id: mainWindowText
            text: qsTr("MainWindowText")
        }

    }

    Urho3DComponent{
        id: urho3DComponent0;
        x: 0
        y: 100
        width: 160
        height: 120
    }

    function testConnection(inIndex)
    {
        mainWindowText.text = "Signal from Subwindow "+inIndex;
    }
}

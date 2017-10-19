import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item{

    property bool urho3DFill;

    Image {
        id: textureUrho3d
        source: "image://Urho3DTextureProvider/texture" //mUrho3DManager.getUrl(1)//
        x: parent.x
        y: parent.y
        width: parent.width
        height: parent.height
    }

    Connections {
        target: mUrho3DManager
        onSceneTextureUpdated:{
            textureUrho3d.source = "image://Urho3DTextureProvider/texture?" + Math.random()//mUrho3DManager.getUrl(2) //
        }
    }

}

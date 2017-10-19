# urho3DInQML
Simple application to show how to use Urho3D in a QML application

Briefly, the Urho3D scene is rendered to texture and this texture is sent to QML which displays it via QQuickImagePorvider. 

- Urho3DManager : makes the link between Urho3D (Urho3DApplication class) and the QML part of the application,
- Urho3DApplication : the Urho3D class which inherits from QObject and Urho3D::Object : contains the Urho3D part of the application,
- TextureProvider : get Urho3D scene' texture and displays it in QML

- main.qml : main qml file,
- Urho3DComponent : qml itemcontaining the Urho3D scene in a qml Image (rendered to texture from Urho3DApplication),
- Subwindow : qml window containing qml items and Urho3DComponent.

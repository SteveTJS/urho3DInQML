#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQuickWindow>
#include <QtQuickWidgets/QQuickWidget>
#include <QQmlContext>
#include <QWindow>
#include <QWidget>

#include "Urho3DManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

    Urho3DManager* urho3DManager = new Urho3DManager(&engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    //run after qml loading
    urho3DManager->startUrho3D();


    return app.exec();
}

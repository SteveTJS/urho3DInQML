#ifndef URHO3DMANAGER_H
#define URHO3DMANAGER_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QUrl>
#include <QTimer>

#include "Urho3DApplication.h"

class TextureProvider;

class Urho3DManager : public QObject
{
    Q_OBJECT

private:
    QTimer *mTimer;
    int mUrho3DWidth;
    int mUrho3DHeight;

    //to provide QML part the Urho3D texture
    TextureProvider *mTextureProvider;

    unsigned char* mRenderTextureData;
    
    //Urho3D application (exec engine, create Urho3D window, scene, ...)
    Urho3D::SharedPtr<Urho3DApplication> mUrho3DApplication;
    Urho3D::SharedPtr<Urho3D::Context> mUrho3DContext;
    bool mIsUrho3DCreated;

public:
    explicit Urho3DManager(QQmlApplicationEngine *inEngine=0, QObject *parent = 0);
    void startUrho3D();
    unsigned char* renderTextureData();

signals:
    void sceneTextureUpdated();

public slots:
    void refreshUrho3D();
    void deleteUrho3D();
    void updateSceneTexture(unsigned char* inRenderTextureData, int inWidth, int inHeight);
};

#endif // URHO3DMANAGER_H

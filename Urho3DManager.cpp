#include "Urho3DManager.h"
#include "TextureProvider.h"

#define URHO_WIDTH 640
#define URHO_HEIGHT 480

Urho3DManager::Urho3DManager(QQmlApplicationEngine *inEngine, QObject *parent) : QObject(parent)
{
    (inEngine->rootContext())->setContextProperty("mUrho3DManager",this);
    mRenderTextureData=0;

    //TextureProvider
    mTextureProvider = new TextureProvider(this);
    inEngine->addImageProvider("Urho3DTextureProvider",mTextureProvider);

    //Urho3D application
    mUrho3DContext = new Urho3D::Context();
    mUrho3DApplication = new Urho3DApplication(mUrho3DContext);
    QObject::connect(mUrho3DApplication,SIGNAL(updateSceneTexture(unsigned char*,int,int)),this,SLOT(updateSceneTexture(unsigned char*,int,int)));

    //timer to refresh Urho3D frame
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(refreshUrho3D()));
}

void Urho3DManager::startUrho3D()
{
    mUrho3DApplication->Start();
    mTimer->start();
}

void Urho3DManager::deleteUrho3D()
{
    //test to delete Urho3D part and close the second window
    mTimer->stop();
    //delete mUrho3DApplication;//crash
}

void Urho3DManager::refreshUrho3D()
{
  mUrho3DApplication->refreshUrho3D();
}

void Urho3DManager::updateSceneTexture(unsigned char* inRenderTextureData, int inWidth, int inHeight)
{
    mRenderTextureData = inRenderTextureData;
    emit sceneTextureUpdated();
}

unsigned char* Urho3DManager::renderTextureData()
{
    return mRenderTextureData;
}

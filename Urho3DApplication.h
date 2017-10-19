#ifndef URHO3DAPPLICATION_H
#define URHO3DAPPLICATION_H

#include "Windows.h"

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Core/Context.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Texture2D.h>
using namespace Urho3D;

#include <QObject>

class Urho3DApplication : public QObject, public Object
{
    Q_OBJECT

private:
    int mUrho3DWidth;
    int mUrho3DHeight;

    HWND mHWnd;
    SharedPtr<Engine> mEngine;

    SharedPtr<Scene> mScene;
    Viewport* mViewport;
    SharedPtr<Node> mCameraNode;
    Camera* mCamera;
    SharedPtr<Node> mBoxNode;

    unsigned char* mRenderTextureData;
    unsigned char* mRenderTextureWholeSceneData;
    SharedPtr<Texture2D> renderTexture;
    SharedPtr<Texture2D> renderTextureWholeScene;

public:
    Urho3DApplication(Context * context);
    virtual void Setup();
    virtual void Start();
    void HandleUpdate(StringHash eventType,VariantMap& eventData);
    void HandleRenderUpdate(StringHash eventType, VariantMap & eventData);

    //functions to implement as this clas inherits from Object from Urho3D
    virtual StringHash GetType() const { return StringHash(""); };
    const String stra = "a";
    const String& GetTypeName() const { return stra; };
    virtual const TypeInfo* GetTypeInfo() const { return new TypeInfo("", 0); };

    unsigned char* getRenderTextureData();    

signals:
    void updateSceneTexture(unsigned char* inRenderTextureData, int inWidth, int inHeight);

public slots:
    void refreshUrho3D();
};

#endif // URHO3DAPPLICATION_H

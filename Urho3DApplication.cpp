#include "Urho3DApplication.h"

#define URHO_WIDTH 640
#define URHO_HEIGHT 480

Urho3DApplication::Urho3DApplication(Context * context) :
    Object(context),
    mEngine(new Engine(context))
{
    mUrho3DWidth = URHO_WIDTH;
    mUrho3DHeight = URHO_HEIGHT;

    //create a native window used as external window by Urho3D
    mHWnd = CreateWindow(L"STATIC", L"Native window", 0, 0, 0, URHO_WIDTH, URHO_HEIGHT, 0, 0, 0, 0);
}

void Urho3DApplication::Setup()
{
    VariantMap engineParameters;
    engineParameters["WindowWidth"]=mUrho3DWidth;
    engineParameters["WindowHeight"]=mUrho3DHeight;
    engineParameters["ResourcePaths"]="Urho3DResources/Data;Urho3DResources/CoreData";
    engineParameters["ExternalWindow"] = mHWnd;

    if (!mEngine->Initialize(engineParameters))
      return;
}

void Urho3DApplication::refreshUrho3D()
{
  if (mEngine && !mEngine->IsExiting())
    mEngine->RunFrame();
}

void Urho3DApplication::Start()
{
    Setup();

    // We will be needing to load resources.
    ResourceCache* cache=GetSubsystem<ResourceCache>();

    // Let's setup a scene to render.
    mScene=new Scene(context_);
    // Let the scene have an Octree component!
    mScene->CreateComponent<Octree>();

    // We need a camera from which the viewport can render.
    mCameraNode=mScene->CreateChild("Camera");
    mCamera=mCameraNode->CreateComponent<Camera>();

    // Let's put a box in there.
    mBoxNode=mScene->CreateChild("Box");
    mBoxNode->SetScale(Vector3(2,2,2));
    mBoxNode->SetPosition(Vector3(0,0,10));
    StaticModel* boxObject=mBoxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/Stone.xml"));
    boxObject->SetCastShadows(true);

    // Create a red directional light (sun)
    {
       Urho3D::Node* lightNode=mScene->CreateChild();
       lightNode->SetDirection(Vector3::FORWARD);
       lightNode->Yaw(50);
       lightNode->Pitch(10);
       Light* light=lightNode->CreateComponent<Light>();
       light->SetLightType(LIGHT_DIRECTIONAL);
       light->SetBrightness(1.0f);
       light->SetColor(Color(1.0f,.6f,0.3f,1.f));
       light->SetCastShadows(true);
    }

    // Now we setup the viewport. Of course, you can have more than one!
    mViewport = new Viewport(context_,mScene,mCameraNode->GetComponent<Camera>());

    // render all Urho3D scene to texture
    renderTextureWholeScene = new Texture2D(context_);
    renderTextureWholeScene->SetSize(mUrho3DWidth, mUrho3DHeight, Graphics::GetRGBAFormat(), TEXTURE_RENDERTARGET);
    renderTextureWholeScene->SetFilterMode(FILTER_BILINEAR);
    mRenderTextureWholeSceneData = new unsigned char[renderTextureWholeScene->GetDataSize(mUrho3DWidth, mUrho3DHeight)];

    RenderSurface* surfaceWholeScene = renderTextureWholeScene->GetRenderSurface();
    surfaceWholeScene->SetNumViewports(1);
    surfaceWholeScene->SetViewport(0,mViewport);
    surfaceWholeScene->SetUpdateMode(SURFACE_UPDATEALWAYS );
    renderTextureWholeScene->GetData(0, mRenderTextureWholeSceneData);
    emit updateSceneTexture(mRenderTextureWholeSceneData, mUrho3DWidth, mUrho3DHeight);

    // We subscribe to the events we'd like to handle.
    SubscribeToEvent(E_UPDATE,URHO3D_HANDLER(Urho3DApplication,HandleUpdate));
    SubscribeToEvent(E_RENDERUPDATE,URHO3D_HANDLER(Urho3DApplication,HandleRenderUpdate));
}

void Urho3DApplication::HandleUpdate(StringHash eventType,VariantMap& eventData)
{
    float timeStep=eventData[Update::P_TIMESTEP].GetFloat();
    mBoxNode->Rotate(Quaternion(8*timeStep,16*timeStep,0));
}

void Urho3DApplication::HandleRenderUpdate(StringHash eventType, VariantMap & eventData)
{
    //whole scene's texture sent to QML
    renderTextureWholeScene->GetData(0, mRenderTextureWholeSceneData);
    emit updateSceneTexture(mRenderTextureWholeSceneData, mUrho3DWidth, mUrho3DHeight);
}

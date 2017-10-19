#include "TextureProvider.h"

#define URHO_WIDTH 640
#define URHO_HEIGHT 480

TextureProvider::TextureProvider(Urho3DManager *inUrho3DManager) : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    mUrho3DManager = inUrho3DManager;
    mUrho3DWidth = URHO_WIDTH;
    mUrho3DHeight = URHO_HEIGHT;
}

QPixmap TextureProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap img = QPixmap();

    if(mUrho3DManager->renderTextureData() != 0){

        unsigned char* textureData = mUrho3DManager->renderTextureData();
        //if( textureData[0] != '\0')
        {
            QImage img0 = QImage(textureData,mUrho3DWidth, mUrho3DHeight,QImage::Format_RGBA8888);// ARGB32);
            img = QPixmap::fromImage(img0);
        }
    }

    return img;
}


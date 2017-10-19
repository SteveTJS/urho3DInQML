#ifndef TEXTUREPROVIDER_H
#define TEXTUREPROVIDER_H

#include <QQuickImageProvider>

#include "Urho3DManager.h"

class TextureProvider : public QQuickImageProvider
{
private:
    Urho3DManager *mUrho3DManager;
    int mUrho3DWidth;
    int mUrho3DHeight;

public:
    TextureProvider(Urho3DManager *inUrho3DManager);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

};

#endif // TEXTUREPROVIDER_H

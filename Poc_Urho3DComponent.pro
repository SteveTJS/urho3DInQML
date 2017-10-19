TEMPLATE = app

QT += qml quick widgets webview
CONFIG += c++11

SOURCES += main.cpp \
    Urho3DManager.cpp \
    Urho3DApplication.cpp \
    TextureProvider.cpp

RESOURCES += qml.qrc

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Urho3DManager.h \
    Urho3DApplication.h \
    TextureProvider.h

#For Urho3D
URHO_HOME = C:/Urho3D/Urho3D-msvc2015 #REBUILDER LE .SLN!!!

# $(URHO_HOME) should point to your Urho3D installation folder
INCLUDEPATH += $${URHO_HOME}/include $${URHO_HOME}/include/Urho3D/ThirdParty

LIBS+= -L$${URHO_HOME}/lib -lUrho3D_d
LIBS+= "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3d9.lib" "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/d3dcompiler.lib"

#Then these guys, every single one of them seems to be needed on Windows
LIBS += kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib
LIBS += dbghelp.lib imm32.lib version.lib winmm.lib ws2_32.lib

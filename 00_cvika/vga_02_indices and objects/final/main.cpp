#include <QtGui/QGuiApplication>
#include "scenewindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    /// Nastavime format, ktery popisuje verzi OpenGL a dalsi drobnosti
    QSurfaceFormat format;
    format.setDepthBufferSize( 24 );
    format.setMajorVersion( 3 );
    format.setMinorVersion( 1 );
    format.setSamples(4);
    format.setProfile( QSurfaceFormat::CoreProfile );

    /// Vytvorime zakladni okno aplikace, kteremu predame nastaveni
    SceneWindow window;
    window.setFormat(format);
    window.resize(800, 800);
    window.show();

    return app.exec();
}

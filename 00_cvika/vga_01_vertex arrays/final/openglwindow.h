#include <QWindow>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QOpenGLFunctions>
#include <QtDebug>

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();

public slots:
    void renderNow();

protected:
    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);

private:
    bool m_update_pending;
    QOpenGLContext *m_context;

protected:
    QOpenGLFunctions* m_functions;
};


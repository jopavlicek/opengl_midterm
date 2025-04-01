/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "OpenGLScene.h"

OpenGLScene::OpenGLScene()
    : m_t(0), m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &OpenGLScene::handleWindowChanged);
}

void OpenGLScene::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void OpenGLScene::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeSynchronizing, this, &OpenGLScene::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &OpenGLScene::cleanup, Qt::DirectConnection);
        // Ensure we start with cleared to black. The squircle's blend mode relies on this.
        win->setColor(Qt::black);
    }
}

void OpenGLScene::cleanup()
{
    delete m_renderer;
    m_renderer = nullptr;
}

class CleanupJob : public QRunnable
{
public:
    CleanupJob(OpenGLSceneRenderer *renderer) : m_renderer(renderer) { }
    void run() override { delete m_renderer; }
private:
    OpenGLSceneRenderer *m_renderer;
};

void OpenGLScene::releaseResources()
{
    window()->scheduleRenderJob(new CleanupJob(m_renderer), QQuickWindow::BeforeSynchronizingStage);
    m_renderer = nullptr;
}

OpenGLSceneRenderer::~OpenGLSceneRenderer()
{
    delete m_invertShader;
}

void OpenGLScene::sync()
{
    if (!m_renderer) {
        m_renderer = new OpenGLSceneRenderer();
        connect(window(), &QQuickWindow::beforeRendering, m_renderer, &OpenGLSceneRenderer::init, Qt::DirectConnection);
        connect(window(), &QQuickWindow::beforeRenderPassRecording, m_renderer, &OpenGLSceneRenderer::paint, Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
    m_renderer->setWindow(window());
}


// -----------------------------------------------------------------------------------
// Scene Renderer
// -----------------------------------------------------------------------------------
void OpenGLSceneRenderer::init()
{
    if (!m_invertShader) {
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);

        initializeOpenGLFunctions();

        // ------------------------------------------------------------
        // Shader
        // ------------------------------------------------------------

        m_invertShader = new ShaderProgram(":/invert.vert", ":/invert.frag", "posAttr", "colAttr");
        m_grayscaleShader = new ShaderProgram(":/grayscale.vert", ":/grayscale.frag", "position", "color");

        // ------------------------------------------------------------
        // VBO
        // ------------------------------------------------------------

        Vertex triangle[] = {
            { { 0.0,-1.0}, {1.0, 0.0, 0.0} },
            { {-1.0,-1.0}, {0.0, 1.0, 0.0} },
            { {-1.0, 0.0}, {1.0, 0.0, 1.0} }
        };
        m_triangleBuffer = new VertexBuffer(triangle, 3);

        Vertex square[] = {
            { {1.0,0.0}, {1.0, 0.0, 0.0}},
            { {1.0,1.0}, {0.0, 1.0, 0.0}},
            { {0.0,0.0}, {1.0, 0.0, 1.0}},
            { {0.0,1.0}, {1.0, 0.0, 1.0}}
        };
        m_squareBuffer = new VertexBuffer(square, 4);

        m_go1 = new GraphicalObject(m_invertShader, m_triangleBuffer);
        m_go1->addDrawMethod(new DrawMethod(GL_TRIANGLES, 0, 3));

        m_go2 = new GraphicalObject(m_invertShader, m_squareBuffer);
        m_go2->addDrawMethod(new DrawMethod(GL_TRIANGLE_STRIP, 0, 4));
    }
}

void OpenGLSceneRenderer::clear(){
    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}


void OpenGLSceneRenderer::paint(){
    // Play nice with the RHI. Not strictly needed when the scenegraph uses
    // OpenGL directly.
    m_window->beginExternalCommands();

    clear();

    m_go1->render();
    m_go2->render();

    m_window->endExternalCommands();

    qDebug() << "m_t: " << m_t;
}

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
    for (auto shader : m_shaders) {
        delete shader;
    }

    for (auto buffer : m_buffers) {
        delete buffer;
    }

    for (auto object : m_objects) {
        delete object;
    }
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
    if (m_shaders.empty()) {
        QSGRendererInterface *rif = m_window->rendererInterface();
        Q_ASSERT(rif->graphicsApi() == QSGRendererInterface::OpenGL);

        initializeOpenGLFunctions();


        //m_uniformDamage = m_programGrayscale->uniformLocation("damage");

        Vertex triangle[] = {
            { { 0.0,-1.0, 2.0}, {1.0, 0.0, 0.0}},
            { {-1.0,-1.0, 2.0}, {0.0, 1.0, 0.0}},
            { {-1.0, 0.0, 2.0}, {1.0, 0.0, 1.0}}
        };
        m_buffers.push_back( new VertexBuffer(triangle, 3) );

        // --------------------------------------
        Vertex square[] = {
            { {1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}},
            { {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}},
            { {0.0, 0.0, 0.0}, {1.0, 0.0, 1.0}},
            { {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}},
            { {0.0, 0.0, 0.0}, {1.0, 0.0, 1.0}},
            { {0.0, 1.0, 0.0}, {1.0, 0.0, 1.0}}
        };
        m_buffers.push_back( new VertexBuffer(square, 6) );

        Vertex tree[] = {
            { { 0.0, 2.0, 0.0}, {0.0, 1.0, 0.0}},
            { { 1.0, 0.0, 1.0}, {0.0, 1.0, 0.0}},
            { { 1.0, 0.0,-1.0}, {0.0, 1.0, 0.0}},
            { { 0.0, 2.0, 0.0}, {0.3, 1.0, 0.3}},
            { { 1.0, 0.0,-1.0}, {0.3, 1.0, 0.3}},
            { {-1.0, 0.0,-1.0}, {0.3, 1.0, 0.3}},
            { { 0.0, 2.0, 0.0}, {0.0, 1.0, 0.0}},
            { {-1.0, 0.0,-1.0}, {0.0, 1.0, 0.0}},
            { {-1.0, 0.0, 1.0}, {0.0, 1.0, 0.0}},
            { { 0.0, 2.0, 0.0}, {0.3, 1.0, 0.3}},
            { {-1.0, 0.0, 1.0}, {0.3, 1.0, 0.3}},
            { { 1.0, 0.0, 1.0}, {0.3, 1.0, 0.3}}
        };

        m_buffers.push_back( new VertexBuffer(tree, 12) );

        m_shaders.push_back( new ShaderProgram(":/invert.vert", ":/invert.frag", "posAttr", "colAttr", "matrix") );

        m_objects.push_back( new GraphicalObject( m_shaders.at(0), m_buffers.at(2),
                                                Position{2,0,2}, Rotation{0,0,1,0} ) );
        m_objects.push_back( new GraphicalObject( m_shaders.at(0), m_buffers.at(2),
                                                Position{0,0,0}, Rotation{45,0,1,0}) );
        m_objects.push_back( new GraphicalObject( m_shaders.at(0), m_buffers.at(2),
                                                Position{-2,0,-2}, Rotation{0,0,1,0}) );

    }
}

void OpenGLSceneRenderer::clear(){
    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
}


void OpenGLSceneRenderer::paint(){
    // Play nice with the RHI. Not strictly needed when the scenegraph uses
    // OpenGL directly.
    m_window->beginExternalCommands();

    clear();

    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(90, 4.0f/3.0f, 0.1f, 100.f);
    //projectionMatrix.ortho(-5, 5, -5, 5, 0, 100);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.lookAt(
        {0.0, 5.0,-5.0},
        {0.0, 0.0, 0.0},
        {0.0, 1.0, 0.0}
        );

    modelViewMatrix.rotate(m_t, 0, 1, 0);

    QMatrix4x4 startMatrix = modelViewMatrix;

    for (auto object : m_objects) {
        Position pos = object->getPosition();
        Rotation rot = object->getRotation();
        modelViewMatrix.translate(pos.x, pos.y, pos.z);
        modelViewMatrix.rotate(rot.angle, rot.x, rot.y, rot.z);

        object->render(projectionMatrix*modelViewMatrix);
        modelViewMatrix = startMatrix;
    }

    m_window->endExternalCommands();

    qDebug() << "m_t: " << m_t;
}

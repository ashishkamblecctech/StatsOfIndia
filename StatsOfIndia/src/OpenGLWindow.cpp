#include "stdafx.h"
#include "OpenGLWindow.h"
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include "StatsOfIndia.h"

OpenGLWindow::OpenGLWindow(const QColor& background, QWidget* parent) : mBackground(background)
{
    setParent(parent);
    setMinimumSize(300, 250);
}

OpenGLWindow::~OpenGLWindow()
{
    reset();
}

void OpenGLWindow::reset()
{
    makeCurrent();
    delete mProgram;
    mProgram = nullptr;
    delete mVshader;
    mVshader = nullptr;
    delete mFshader;
    mFshader = nullptr;
    mVbo.destroy();
    doneCurrent();

    QObject::disconnect(mContextWatchConnection);
}

void OpenGLWindow::initializeGL()
{
    static const char* vertexShaderSource =
        "attribute highp vec4 posAttr;\n"
        "attribute lowp vec4 colAttr;\n"
        "varying lowp vec4 col;\n"
        "uniform highp mat4 matrix;\n"
        "void main() {\n"
        "   col = colAttr;\n"
        "   gl_Position = matrix * posAttr;\n"
        "}\n";

    static const char* fragmentShaderSource =
        "varying lowp vec4 col;\n"
        "void main() {\n"
        "   gl_FragColor = col;\n"
        "}\n";

    initializeOpenGLFunctions();

    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();

    m_posAttr = mProgram->attributeLocation("posAttr");
    Q_ASSERT(m_posAttr != -1);
    m_colAttr = mProgram->attributeLocation("colAttr");
    Q_ASSERT(m_colAttr != -1);
    m_matrixUniform = mProgram->uniformLocation("matrix");
    Q_ASSERT(m_matrixUniform != -1);
}

void OpenGLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mProgram->bind();

    QMatrix4x4 matrix;
    matrix.ortho(0.0f, 80.0f, 0.0f, 80.0f, 0.1f, 100.0f);
    matrix.translate(-35, 15, -1);
    matrix.rotate(rotationAngle);
    matrix.scale(scaleFactor);
    mProgram->setUniformValue(m_matrixUniform, matrix);
 
    drawRegions();
    update();
}

void OpenGLWindow::addFilePoints(QString filepath, float r, float g, float b, float stateValue) {
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    QTextStream in(&file);

    Region region;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList coordinates = line.split(' ');

        if (coordinates.size() == 2)
        {
            // Add coordinates to mVertices and mColors
            float x = coordinates[0].toFloat();
            float y = coordinates[1].toFloat();
            float z = stateValue;
            region.vertices << x << y << 0;
            region.vertices << x << y << -z;
            region.colors << r << g << b;
            region.colors << r << g << b;
            
        }
    }
    
    regionsToDraw.append(region);

    file.close();
}

void OpenGLWindow::updateShape(QVector<GLfloat>& vertices, QVector<GLfloat>& colors)
{
    mVertices = vertices;
    mColors = colors;
    emit shapesUpdated();
}

void OpenGLWindow::drawRegions() {
    // Iterate through each region and draw its vertices
    for (const Region& region : regionsToDraw) {
        glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, region.vertices.data());
        glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, region.colors.data());

        glEnableVertexAttribArray(m_posAttr);
        glEnableVertexAttribArray(m_colAttr);

        glDrawArrays(GL_POLYGON, 0, region.vertices.size() / 3);

        glDisableVertexAttribArray(m_colAttr);
        glDisableVertexAttribArray(m_posAttr);
    }
}

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.1f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.1f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() > 0) {
        zoomIn();
    }
    else {
       zoomOut();

    }
}

void OpenGLWindow::zoomIn()

{
    // Here we are taking zoomIn factor 1.1
    scaleFactor *= 1.1f;

    update(); // Trigger repaint
}

void OpenGLWindow::zoomOut()

{
    // Here we are taking zoomOut factor 1.1
    scaleFactor /= 1.1f;

    update(); // Trigger repaint
}
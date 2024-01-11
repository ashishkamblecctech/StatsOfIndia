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
    const QStringList list = { "vertexShader.glsl", "fragmentShader.glsl" };
    mShaderWatcher = new QFileSystemWatcher(list, this);
    connect(mShaderWatcher, &QFileSystemWatcher::fileChanged, this, &OpenGLWindow::shaderWatcher);
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
    QString vertexShaderSource = readShader("vertexShader.glsl");
    QString fragmentShaderSource = readShader("fragmentShader.glsl");

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
    matrix.ortho(50, 110, 00, 40, -300.0f, 300.0f);
    matrix.translate(0,0,-20);
    matrix.rotate(rotationAngle);
    matrix.scale(scaleFactor);
    mProgram->setUniformValue(m_matrixUniform, matrix);
 
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
    update();
}

void OpenGLWindow::addFilePoints(std::string filepath, float r, float g, float b, float stateValue) {

    QString qFilePath = QString::fromStdString(filepath);
    QFile file(qFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }
    QTextStream in(&file);
    Region region;
    while (!in.atEnd())
    {
        QString line = in.readLine();//It reads the 1st line
        QString line1 = in.readLine();//It skips the 2nd point line to make operation fast
        QString line2 = in.readLine();//It skips the 3rd point line to make operation fast
        
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

void OpenGLWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton && !lastPos.isNull())
    {
        int dx = event->x() - lastPos.x();
        int dy = event->y() - lastPos.y();

        QQuaternion rotX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.05f * dx);
        QQuaternion rotY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, 0.05f * dy);

        rotationAngle = rotX * rotY * rotationAngle;
        update();
    }
    lastPos = event->pos();
}


void OpenGLWindow::clearRegions()
{
    regionsToDraw.clear();
    update(); // Trigger repaint to clear the window
}

void OpenGLWindow::shaderWatcher() {
    QString fragmentShaderSource = readShader("fragmentShader.glsl");
    QString vertexShaderSource = readShader("vertexShader.glsl");

    mProgram->release();
    mProgram->removeAllShaders();
    mProgram = new QOpenGLShaderProgram(this);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->link();
}

QString OpenGLWindow::readShader(QString filepath) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "Invalid Path";

    QTextStream stream(&file);
    QString line = stream.readLine();
    while (!stream.atEnd()) {
        line.append(stream.readLine());
    }
    file.close();
    return line;
}

void OpenGLWindow::wheelEvent(QWheelEvent* event)
{
    //This will all zoomIn() and and zoomOut event
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

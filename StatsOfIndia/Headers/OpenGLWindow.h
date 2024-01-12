#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QList>
#include <QVector3D>

class QOpenGLShader;
class QOpenGLShaderProgram;

struct Region {
    QVector<GLfloat> mVertices;
    QVector<GLfloat> mNormals; //Vertices for lighting effects
    QVector<GLfloat> mColors;
};

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

signals:
    void shapesUpdated();

public:
    OpenGLWindow(const QColor& background, QWidget* parent);
    ~OpenGLWindow();
    void mouseMoveEvent(QMouseEvent* event);
    void addFilePoints(std::string filepath, float r, float g, float b, float stateValue);
    void clearRegions();
    void shaderWatcher();
    QString readShader(QString filepath);

protected:
    void paintGL() override;
    void initializeGL() override;
    void wheelEvent(QWheelEvent* event) override;


private:
    void reset();
   
    void zoomOut();
    void zoomIn();

private:
    bool mAnimating = false;
    QOpenGLContext* mContext = nullptr;
    QOpenGLShader* mVshader = nullptr;
    QOpenGLShader* mFshader = nullptr;
    QOpenGLShaderProgram* mProgram = nullptr;
    QOpenGLBuffer mVbo;
    int mVertexAttr;
    int mNormalAttr;
    int mMatrixUniform;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    GLint m_normalAttr;          
    GLint m_lightPositionUniform; 
    GLint m_lightDirectionUniform;

    QColor mBackground;
    QQuaternion rotationAngle;
    QPoint lastPos;
    QMetaObject::Connection mContextWatchConnection;

    float scaleFactor=1;
    
    QVector <Region> regionsToDraw;
    QFileSystemWatcher* mShaderWatcher;
};

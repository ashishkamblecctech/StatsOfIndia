#pragma once

#include "OpenGLWindow.h"

#include <QtCore/QVariant>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

struct RegionInfo {
    QString filePath;
    float r, g, b, statePopulation, stateEducation, stateArea;
};

class StatsOfIndia : public QMainWindow
{
    Q_OBJECT

public:
    StatsOfIndia(QWidget *parent = nullptr);
    ~StatsOfIndia();

private:
    void setupUi();
    void setupTableModel(const QStringList& stateNames, const QList<int>& stateValues);
    void handleComboBoxChange(int index);

private:
    QWidget* mCentralWidget;
    QWidget* mGridLayoutWidget;
    QGridLayout* mGridLayout;
    QVBoxLayout* mVerticalLayout;
    QHBoxLayout* mHorizontalLayout;
    QHBoxLayout* mHorizontalLayout1;
    QLabel* mLabel;
    QDateEdit* mDateEdit;
    OpenGLWindow* mOpenGLWidget;
    QTableView* mTableView;
    QPushButton* mPushButton;
    QComboBox* mComboBox;

    QVector<GLfloat> mVertices;
    QVector<GLfloat> mColors;

    /*QStringList stateNames;
    QList<int> stateValues;*/
};

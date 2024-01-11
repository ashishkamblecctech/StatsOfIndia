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
#include "StatsDataReader.h"

class StatsOfIndia : public QMainWindow
{
    Q_OBJECT

public:
    StatsOfIndia(QWidget *parent = nullptr);
    ~StatsOfIndia();

private:
    void setupUi();
    void setupTableModel(const QStringList& stateNames, const QList<long>& stateValues);
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

    std::vector<std::string> stateNames;
    std::vector<long> statePopulation;
    std::vector<float> stateEducation;
    std::vector<float> stateArea;

    std::vector<long> stateActualPopulation;
    std::vector<float> stateActualEducation;
    std::vector<float> stateActualArea;

    std::vector <RegionInfo1> regions1;

    QStringList stateNames1;
    QList<long> stateValues1;
};

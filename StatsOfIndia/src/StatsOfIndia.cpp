#include "stdafx.h"
#include "StatsOfIndia.h"

StatsOfIndia::StatsOfIndia(QWidget *parent) 
    : QMainWindow(parent)
{
    setupUi();

    //Connection to handle combo box UI
    connect(mComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &StatsOfIndia::handleComboBoxChange);
}

StatsOfIndia::~StatsOfIndia()
{}

void StatsOfIndia::setupUi()
{
    // Set a minimum and maximum size for the main window
    this->setMinimumSize(800, 600);
    this->setMaximumSize(1900, 1000);

    // UI part can be added in the code below
    resize(1900, 1000);
    mCentralWidget = new QWidget(this);

    mGridLayoutWidget = new QWidget(mCentralWidget);
    mGridLayoutWidget->setGeometry(QRect(0, 0, 1900, 1000));
    mGridLayout = new QGridLayout(mGridLayoutWidget);

    mVerticalLayout = new QVBoxLayout();

    mHorizontalLayout = new QHBoxLayout();

    mComboBox = new QComboBox(mGridLayoutWidget);
    mComboBox->addItem("Select Parameter:");
    mComboBox->addItem("Population");
    mComboBox->addItem("Education");
    mComboBox->addItem("Area");
    mComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents); // To make page responsive
    
    mVerticalLayout->addWidget(mComboBox);

    mTableView = new QTableView(mGridLayoutWidget);
    mTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // To make page responsive
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    mTableView->setSizePolicy(sizePolicy);
    mVerticalLayout->addWidget(mTableView);

    mGridLayout->addLayout(mVerticalLayout, 0, 1, 1, 1);

    // Set the size policy for making the page responsive
    mCentralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set the layout for making the page responsive
    mCentralWidget->setLayout(mGridLayout);

    setCentralWidget(mCentralWidget);

    // No need for additional layout, just add mOpenGLWidget directly
    mOpenGLWidget = new OpenGLWindow(QColor(0, 0, 0), mCentralWidget);
    mGridLayout->addWidget(mOpenGLWidget, 0, 0, 2, 1); // Spanning two rows
}






void StatsOfIndia::setupTableModel(const QStringList& stateNames, const QList<long>& stateValues)
{
    // Create a standard item model
    QStandardItemModel* model = new QStandardItemModel(this);

    // Set the column headers
    model->setHorizontalHeaderLabels(QStringList() << "State Names" << "Values");

    for (int i = 0; i < stateNames.size(); i++) {
        QList<QStandardItem*> row;

        // Add state name to the first column
        row << new QStandardItem(stateNames[i]);

        // Add the corresponding value for the second column
        row << new QStandardItem(QString::number(stateValues[i]));

        model->appendRow(row);
    }

    // Set the model for the table view
    mTableView->setModel(model);
}

void StatsOfIndia::handleComboBoxChange(int index) {

    // Fix the size of array to 31
    stateNames.resize(31); 
    statePopulation.resize(31);
    stateEducation.resize(31);
    stateArea.resize(31);
    stateActualPopulation.resize(31);
    stateActualEducation.resize(31);
    stateActualArea.resize(31);

    //Calling the reader and gathering all the data from the reader
    StatsDataReader reader;
    reader.dataReader(stateNames, statePopulation, stateEducation, stateArea, stateActualPopulation, stateActualEducation, stateActualArea, regions1);

    mOpenGLWidget->clearRegions();//clear the data first from the variables

    switch (index) {
    case 1: // Handle Population selection
    {        
        // Pass the data to setupTableModel
        for (int i = 0; i < stateActualPopulation.size(); i++) {
            stateNames1 << QString::fromStdString(stateNames[i]);
            stateValues1 << stateActualPopulation[i];
        }
        setupTableModel(stateNames1, stateValues1);

        // Loop through the array and call addFilePoints for each region
        for (RegionInfo1& region : regions1) {
            mOpenGLWidget->addFilePoints(region.filePath, region.r, region.g, region.b, region.statePopulation);
        }
        update();
        break;
    }
    case 2: // Handle Education selection
    { 
        // Pass the data to setupTableModel
        for (int i = 0; i < stateActualEducation.size(); i++) {
            stateNames1 << QString::fromStdString(stateNames[i]);
            stateValues1 << stateActualEducation[i];
        }
        setupTableModel(stateNames1, stateValues1);

        // Loop through the array and call addFilePoints for each region
        for (RegionInfo1& region : regions1) {
            mOpenGLWidget->addFilePoints(region.filePath, region.r, region.g, region.b, region.stateEducation);
        }
        update();
        break;
    }
        
    case 3: // Handle Area selection
    {
        // Pass the data to setupTableModel
        for (int i = 0; i < stateActualArea.size(); i++) {
            stateNames1 << QString::fromStdString(stateNames[i]);
            stateValues1 << stateActualArea[i];
        }
        setupTableModel(stateNames1, stateValues1);

        // Loop through the array and call addFilePoints for each region
        for (RegionInfo1& region : regions1) {
            mOpenGLWidget->addFilePoints(region.filePath, region.r, region.g, region.b, region.stateArea);
        }
        update();
        break;
    }
        
        // We can add more cases as needed
    }
}
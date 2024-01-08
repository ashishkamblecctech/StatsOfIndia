#include "stdafx.h"
#include "StatsOfIndia.h"

StatsOfIndia::StatsOfIndia(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(mComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &StatsOfIndia::handleComboBoxChange);//Connection to handle combo box UI
}

StatsOfIndia::~StatsOfIndia()
{}

//Array of state names of India
std::string stateNames[] = {"ladakh","JK","HP","odisha","bihar","meghalay","tripura","mizoram","manipur","nagaland","AP","assam","sikkim",
                                "UP","uttarakhand","gujarat","rajastan","punjab","goa","andraPradesh","telangana","chattisgarh","tamilnadu","MH","MP",
                                    "kerala","karnatak","jharkhand","haryana","delhi","state1","bengal"};

//Input for population, education and area are given dummy values manually
float statePopulation[] = { 1, 2, 3, 1+1, 2+1, 3+1, 1+2, 2+2, 3+2, 1+1 , 2+1, 3+1, 1, 2, 3, 1+1, 2+1, 3+1, 1, 2, 3, 1+1, 2+1, 3+1, 1, 2, 3, 1+1, 2+1, 3+1, 1};
float stateEducation[] = { 3, 1, 2,  3+1, 1+1, 2+1, 3+2, 1+2, 2+2, 3+1, 1+1, 2+1, 3, 1, 2, 3+1, 1+1, 2+1, 3, 1, 2, 3+1, 1+1, 2+1, 3, 1, 2, 3+1, 1+1, 2+1, 3};
float stateArea[] = { 3, 2, 1, 3+1, 2+1, 1+1, 3+2, 2+2, 1+2, 3+1, 2+1, 1+1, 3, 2, 1, 3+1, 2+1, 1+1, 3, 2, 1, 3+1, 2+1, 1+1, 3, 2, 1, 3+1, 2+1, 1+1, 3};


//Creating array of states of India
RegionInfo regions1[] = {
            {"Resources/ladakh.txt", 0.0, 0.0, 1.0, statePopulation[0], stateEducation[0], stateArea[0]},
            {"Resources/JK.txt", 0.0, 1.0, 1.0, statePopulation[1], stateEducation[1], stateArea[1]},
            {"Resources/HP.txt", 1.0, 0.0, 0.0, statePopulation[2], stateEducation[2], stateArea[2]},
            {"Resources/odisha.txt", 1.0, 1.0, 1.0, statePopulation[3], stateEducation[3], stateArea[3]},
            {"Resources/bihar.txt", 1.0, 1.0, 0.0, statePopulation[4], stateEducation[4], stateArea[4]},
            {"Resources/meghalay.txt", 0.0, 1.0, 0.0, statePopulation[5], stateEducation[5], stateArea[5]},
            {"Resources/tripura.txt", 1.0, 0.0, 0.0, statePopulation[6], stateEducation[6], stateArea[6]},
            {"Resources/mizoram.txt", 0.0, 0.0, 1.0, statePopulation[7], stateEducation[7], stateArea[7]},
            {"Resources/manipur.txt", 0.0, 1.0, 1.0, statePopulation[8], stateEducation[8], stateArea[8]},
            {"Resources/nagaland.txt", 1.0, 1.0, 1.0, statePopulation[9], stateEducation[9], stateArea[9]},
            {"Resources/AP.txt", 1.0, 0.5, 0.5, statePopulation[10], stateEducation[10], stateArea[10]},
            {"Resources/assam.txt", 0.0, 0.5, 0.5, statePopulation[11], stateEducation[11], stateArea[11]},
            {"Resources/sikkim.txt", 0.0, 1.0, 0.5, statePopulation[12], stateEducation[12], stateArea[12]},
            {"Resources/UP.txt", 0.0, 1.0, 0.5, statePopulation[13], stateEducation[13], stateArea[13]},
            {"Resources/uttarakhand.txt", 0.5, 1.0, 1.0, statePopulation[14], stateEducation[14], stateArea[14]},
            {"Resources/gujarat.txt", 1.0, 0.5, 0.5, statePopulation[15], stateEducation[15], stateArea[15]},
            {"Resources/rajastan.txt", 1.0, 0.5, 1.0, statePopulation[16], stateEducation[16], stateArea[16]},
            {"Resources/punjab.txt",1.0, 1.0, 0.0, statePopulation[17], stateEducation[17], stateArea[17]},
            {"Resources/goa.txt",1.0, 0.0, 0.0, statePopulation[18], stateEducation[18], stateArea[18]},
            {"Resources/andraPradesh.txt",1.0, 0.5, 1.0, statePopulation[19], stateEducation[19], stateArea[19]},
            {"Resources/telangana.txt",0.5, 0.5, 0.5, statePopulation[20], stateEducation[20], stateArea[20]},
            {"Resources/chattisgarh.txt",1.0, 0.5, 0.5, statePopulation[21], stateEducation[21], stateArea[21]},
            {"Resources/tamilnadu.txt",0.0, 1.0, 0.5, statePopulation[22], stateEducation[22], stateArea[22]},
            {"Resources/MH.txt",0.5, 0.5, 1.0, statePopulation[23], stateEducation[23], stateArea[23]},
            {"Resources/MP.txt",1.0, 1.0, 1.0, statePopulation[24], stateEducation[24], stateArea[24]},
            {"Resources/kerala.txt",1.0, 0.5, 0.5, statePopulation[25], stateEducation[25], stateArea[25]},
            {"Resources/karnatak.txt",0.0, 1.0, 1.0, statePopulation[26], stateEducation[26], stateArea[26]},
            {"Resources/jharkhand.txt",1.0, 0.0, 0.0, statePopulation[27], stateEducation[27], stateArea[27]},
            {"Resources/haryana.txt",0.0, 0.5, 0.5, statePopulation[28], stateEducation[28], stateArea[28]},
            {"Resources/delhi.txt",1.0, 1.0, 1.0, statePopulation[29], stateEducation[29], stateArea[29]},
            {"Resources/bengal.txt",0.5, 0.5, 1.0, statePopulation[30], stateEducation[30], stateArea[30]}
};



void StatsOfIndia::setupUi()
{
    //UI part can be added in the code below 
    resize(830, 625);
    mCentralWidget = new QWidget(this);

    mGridLayoutWidget = new QWidget(mCentralWidget);
    mGridLayoutWidget->setGeometry(QRect(0, 0, 830, 625));
    mGridLayout = new QGridLayout(mGridLayoutWidget);

    mVerticalLayout = new QVBoxLayout();

    mHorizontalLayout = new QHBoxLayout();

    mComboBox = new QComboBox(mGridLayoutWidget);
    mComboBox->addItem("Select Parameter:");
    mComboBox->addItem("Population");
    mComboBox->addItem("Education");
    mComboBox->addItem("Area");
    mHorizontalLayout->addWidget(mComboBox);

    mHorizontalLayout1 = new QHBoxLayout();

    mOpenGLWidget = new OpenGLWindow(QColor(0, 0, 0), mCentralWidget);
    mHorizontalLayout1->addWidget(mOpenGLWidget);

    mTableView = new QTableView(mGridLayoutWidget);
    QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
    mTableView->setSizePolicy(sizePolicy);
    mHorizontalLayout1->addWidget(mTableView);
    mGridLayout->addLayout(mHorizontalLayout1, 0, 0, 1, 1);

    mVerticalLayout->addLayout(mHorizontalLayout);
    mGridLayout->addLayout(mVerticalLayout, 1, 0, 1, 1);

    setCentralWidget(mCentralWidget);
    
}

void StatsOfIndia::setupTableModel(const QStringList& stateNames, const QList<int>& stateValues)
{
    // Create a standard item model
    QStandardItemModel* model = new QStandardItemModel(this);

    // Set the column headers
    model->setHorizontalHeaderLabels(QStringList() << "State Names" << "Values");

    // Add data for each state
    for (int i = 0; i < stateNames.size(); i++) {
        QList<QStandardItem*> row;

        // Add state name to the first column
        row << new QStandardItem(stateNames[i]);

        // Add the corresponding value for the second column
        row << new QStandardItem(QString::number(stateValues[i]));

        // Append the row to the model
        model->appendRow(row);
    }

    // Set the model for the table view
    mTableView->setModel(model);

}

void StatsOfIndia::handleComboBoxChange(int index) {
    int size = sizeof(statePopulation) / sizeof(statePopulation[0]);
    switch (index) {
    case 1: // Handle Population selection
    {        
        // Pass the data to setupTableModel
        QStringList stateNames1;
        QList<int> stateValues1;
        for (int i = 0; i < size; i++) {
            stateNames1 << QString::fromStdString(stateNames[i]);
            stateValues1 << statePopulation[i];
        }
        setupTableModel(stateNames1, stateValues1);

        // Loop through the array and call addFilePoints for each region
        for (RegionInfo& region : regions1) {
            mOpenGLWidget->addFilePoints(region.filePath, region.r, region.g, region.b, region.statePopulation);
        }

        break;
    }
    case 2: // Handle Education selection
    { 
        // Pass the data to setupTableModel
        QStringList stateNames2;
        QList<int> stateValues2;
        for (int i = 0; i < size; i++) {
            stateNames2 << QString::fromStdString(stateNames[i]);
            stateValues2 << stateEducation[i];
        }
        setupTableModel(stateNames2, stateValues2);

        // Loop through the array and call addFilePoints for each region
        for (RegionInfo& region : regions1) {
            mOpenGLWidget->addFilePoints(region.filePath, region.r, region.g, region.b, region.stateEducation);
        }

        break;
    }
        
    case 3: // Handle Area selection
    {
        // Pass the data to setupTableModel
        QStringList stateNames3;
        QList<int> stateValues3;
        for (int i = 0; i < size; i++) {
            stateNames3 << QString::fromStdString(stateNames[i]);
            stateValues3 << stateArea[i];
        }
        setupTableModel(stateNames3, stateValues3);

        // Loop through the array and call addFilePoints for each region
        for (RegionInfo& region : regions1) {
            mOpenGLWidget->addFilePoints(region.filePath, region.r, region.g, region.b, region.stateArea);
        }

        break;
    }
        
        // We can add more cases as needed
    }
}
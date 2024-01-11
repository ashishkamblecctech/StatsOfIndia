// StatsDataReader.cpp : Defines the exported functions for the DLL.
#include "pch.h"
#include "framework.h"
#include "StatsDataReader.h"

// This is the constructor of a class that has been exported.
StatsDataReader::StatsDataReader()
{
    
}

StatsDataReader::~StatsDataReader()
{}

void StatsDataReader::dataReader(std::vector <std::string>& stateNames, std::vector<long>& statePopulation, 
                                        std::vector<float>& stateEducation, std::vector<float>& stateArea, std::vector<long>& stateActualPopulation,
                                         std::vector<float>& stateActualEducation, std::vector<float>& stateActualArea, std::vector <RegionInfo1>& region1)
{
    stateNames = { "Andra Pradesh", "Arunachal Pradesh","Assam","Bengal","Bihar", "Chattisgarh", "Delhi", "Goa", "Gujarat", "Haryana", "Himachal Pradesh", "Jammu and Kashmir",
                   "Jharkhand", "Karnatak", "Kerala", "Ladakh", "Madhya Pradesh", "Maharashtra", "Manipur", "Meghalay", "Mizoram", "Nagaland", "Odisha", "Punjab",
                   "Rajastan", "Sikkim", "Tamilnadu", "Telangana", "Tripura", "Uttarakhand", "UttarPradesh" };

    stateActualPopulation = {
        //The population data is upto 2022

            54000000,  // Andra Pradesh
             1700000,   // Arunachal Pradesh
            38000000,  // Assam
            99000000,  // Bengal
           130000000, // Bihar
            31000000,  // Chattisgarh
            20000000,  // Delhi
             1600000,   // Goa
            67000000,  // Gujarat
            29000000,  // Haryana
             7300000,   // Himachal Pradesh
            14000000,  // Jammu and Kashmir
            39000000,  // Jharkhand
            67000000,  // Karnatak
            37000000,  // Kerala
              290000,    // Ladakh
            83000000,  // Madhya Pradesh
           128000000, // Maharashtra
             3200000,   // Manipur
             3300000,   // Meghalay
             1200000,   // Mizoram
             2200000,   // Nagaland
            45000000,  // Odisha
            30000000,  // Punjab
            78000000,  // Rajastan
              700000,    // Sikkim
            82000000,  // Tamilnadu
            40000000,  // Telangana
             4000000,   // Tripura
            11000000,  // Uttarakhand
           230000000  // UttarPradesh
    };

    for (size_t i=0; i< stateActualPopulation.size(); i++)
    {
        statePopulation[i] = (stateActualPopulation[i] / 10000000);
    }

    stateActualEducation = { 
        //The data is upto 2022
        
        74.3,   // Andra Pradesh
        71.9,   // Arunachal Pradesh
        82.5,   // Assam
        77.1,   // Bengal
        61.8,   // Bihar
        70.3,   // Chattisgarh
        82.9,   // Delhi
        88.7,   // Goa
        79.3,   // Gujarat
        80.4,   // Haryana
        86.6,   // Himachal Pradesh
        77.3,   // Jammu and Kashmir
        67.6,   // Jharkhand
        78.5,   // Karnatak
        95.2,   // Kerala
        87.2,   // Ladakh
        70.6,   // Madhya Pradesh
        83.2,   // Maharashtra
        76.1,   // Manipur
        74.4,   // Meghalay
        90.0,   // Mizoram
        80.1,   // Nagaland
        73.3,   // Odisha
        76.7,   // Punjab
        66.1,   // Rajastan
        81.4,   // Sikkim
        94.0,   // Tamilnadu
        72.8,   // Telangana
        87.4,   // Tripura
        81.0,   // Uttarakhand
        68.7    // UttarPradesh
    };

    for (size_t i = 0; i < stateActualEducation.size(); i++)
    {
        stateEducation[i] = (stateActualEducation[i] - 60)/2;
    }

    stateActualArea = { 
    //The data is upto 2022
    
        160205,   // Andra Pradesh (in square kilometers)
        83743,    // Arunachal Pradesh
        78438,    // Assam
        88752,    // Bengal
        94163,    // Bihar
        135192,   // Chattisgarh
        1484,     // Delhi
        3702,     // Goa
        196024,   // Gujarat
        44212,    // Haryana
        55673,    // Himachal Pradesh
        222236,   // Jammu and Kashmir
        79714,    // Jharkhand
        191791,   // Karnatak
        38863,    // Kerala
        59146,    // Ladakh
        308245,   // Madhya Pradesh
        307713,   // Maharashtra
        22327,    // Manipur
        22429,    // Meghalay
        21081,    // Mizoram
        16579,    // Nagaland
        155707,   // Odisha
        50362,    // Punjab
        342239,   // Rajastan
        7096,     // Sikkim
        130058,   // Tamilnadu
        112077,   // Telangana
        10486,    // Tripura
        53483,    // Uttarakhand
        243286    // UttarPradesh 
    
    };

    for (size_t i = 0; i < stateActualArea.size(); i++)
    {
        stateArea[i] = (stateActualArea[i] / 20000);
    }

    region1 = {
            {"Resources/andraPradesh.txt",1.0, 0.5, 1.0, statePopulation[0], stateEducation[0], stateArea[0]},
            {"Resources/arunachalPradesh.txt", 1.0, 0.5, 0.5, statePopulation[1], stateEducation[1], stateArea[1]},
            {"Resources/assam.txt", 0.0, 0.5, 0.5, statePopulation[2], stateEducation[2], stateArea[2]},
            {"Resources/bengal.txt",0.5, 0.5, 1.0, statePopulation[3], stateEducation[3], stateArea[3]},
            {"Resources/bihar.txt", 1.0, 1.0, 0.0, statePopulation[4], stateEducation[4], stateArea[4]},
            {"Resources/chattisgarh.txt",1.0, 0.5, 0.5, statePopulation[5], stateEducation[5], stateArea[5]},
            {"Resources/delhi.txt",1.0, 1.0, 1.0, statePopulation[6], stateEducation[6], stateArea[6]},
            {"Resources/goa.txt",1.0, 0.0, 0.0, statePopulation[7], stateEducation[7], stateArea[7]},
            {"Resources/gujarat.txt", 1.0, 0.5, 0.5, statePopulation[8], stateEducation[8], stateArea[8]},
            {"Resources/haryana.txt",0.0, 0.5, 0.5, statePopulation[9], stateEducation[9], stateArea[9]},
            {"Resources/himachalPradesh.txt", 1.0, 0.0, 0.0, statePopulation[10], stateEducation[10], stateArea[10]},
            {"Resources/J&K.txt", 0.0, 1.0, 1.0, statePopulation[11], stateEducation[11], stateArea[11]},

            {"Resources/jharkhand.txt",1.0, 0.0, 0.0, statePopulation[12], stateEducation[12], stateArea[12]},
            {"Resources/karnatak.txt",0.0, 1.0, 1.0, statePopulation[13], stateEducation[13], stateArea[13]},
            {"Resources/kerala.txt",1.0, 0.5, 0.5, statePopulation[14], stateEducation[14], stateArea[14]},
            {"Resources/ladakh.txt", 0.0, 0.0, 1.0, statePopulation[15], stateEducation[15], stateArea[15]},
            {"Resources/madhyaPradesh.txt",1.0, 1.0, 1.0, statePopulation[16], stateEducation[16], stateArea[16]},
            {"Resources/maharashtra.txt",0.5, 0.5, 1.0, statePopulation[17], stateEducation[17], stateArea[17]},
            {"Resources/manipur.txt", 0.0, 1.0, 1.0, statePopulation[18], stateEducation[18], stateArea[18]},
            {"Resources/meghalay.txt", 0.0, 1.0, 0.0, statePopulation[19], stateEducation[19], stateArea[19]},
            {"Resources/mizoram.txt", 0.0, 0.0, 1.0, statePopulation[20], stateEducation[20], stateArea[20]},
            {"Resources/nagaland.txt", 1.0, 1.0, 1.0, statePopulation[21], stateEducation[21], stateArea[21]},
            {"Resources/odisha.txt", 1.0, 1.5, 0.5, statePopulation[22], stateEducation[22], stateArea[22]},
            {"Resources/punjab.txt",1.0, 1.0, 0.0, statePopulation[23], stateEducation[23], stateArea[23]},

            {"Resources/rajastan.txt", 1.0, 0.5, 1.0, statePopulation[24], stateEducation[24], stateArea[24]},
            {"Resources/sikkim.txt", 0.0, 1.0, 0.5, statePopulation[25], stateEducation[25], stateArea[25]},
            {"Resources/tamilnadu.txt",0.0, 1.0, 0.5, statePopulation[26], stateEducation[26], stateArea[26]},
            {"Resources/telangana.txt",0.5, 0.5, 0.5, statePopulation[27], stateEducation[27], stateArea[27]},
            {"Resources/tripura.txt", 1.0, 0.0, 0.0, statePopulation[28], stateEducation[28], stateArea[28]},
            {"Resources/uttarakhand.txt", 0.5, 1.0, 1.0, statePopulation[29], stateEducation[29], stateArea[29]},
            {"Resources/uttarPradesh.txt", 0.0, 1.0, 0.5, statePopulation[30], stateEducation[30], stateArea[30]},
    };
 
}
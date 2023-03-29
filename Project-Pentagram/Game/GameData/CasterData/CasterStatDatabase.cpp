#include "CasterStatDatabase.h"
#include <fstream>
#include <sstream>
#include <iostream>

void CasterStatDatabase::LoadResource()
{

    std::string fileName = "CasterDatabase/CasterDatabase.csv";

    std::ifstream file(fileName);

    if (!file.is_open()) {
        return;
    }

    // Read the remaining rows and parse their values
    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> values;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            values.push_back(cell);
        }

        Element::Type element = static_cast<Element::Type>(std::stoi(values[0]));
        CasterType casterType = static_cast<CasterType>(std::stoi(values[1]));
        int hp = std::stoi(values[2]);
        std::array<int, 6> mana;
        for (int i = 0; i < 6; ++i) {
            mana[i] = std::stoi(values[i + 3]) + 100;
        }
        CasterStat stat(hp, mana);

        // Do something with the values here

        std::cout << Element::GetString(element) << " " << std::to_string((int)casterType) << " " << hp << " ";
        for (int i = 0; i < 6; ++i) {
            std::cout << mana[i] << " ";
        }
        std::cout << std::endl;

        Add(element, casterType, stat);
    }

    file.close();

}

void CasterStatDatabase::Add(Element::Type element, CasterType type, CasterStat stat) {

    if (!CasterStatTables.count(element))
    {
        CasterStatTables.emplace(element, new CasterStatTable());
    }

    CasterStatTables[element]->Add(type, stat);
}

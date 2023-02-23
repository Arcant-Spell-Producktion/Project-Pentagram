#include "CasterMovesetDatabase.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

std::string RemoveBraces(const std::string& str) {
    std::string result = str;

    // Remove all '{'
    size_t pos = result.find('{');
    while (pos != std::string::npos) {
        result.erase(pos, 1);
        pos = result.find('{', pos);
    }

    // Remove all '}'
    pos = result.find('}');
    while (pos != std::string::npos) {
        result.erase(pos, 1);
        pos = result.find('}', pos);
    }

    return result;
}

void CasterMoveSetDatabase::LoadResource()
{

    std::string fileName = "CasterDatabase/CasterMoveSet.csv";

    std::ifstream file(fileName);

    if (!file.is_open()) {
        return;
    }

    // Read the remaining rows and parse their values
    std::string line;
    while (std::getline(file, line)) {

        line = RemoveBraces(line);

        std::vector<int> values;
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ',')) {
            int n = std::stoi(cell);
            values.push_back(n);
        }

        Element::Type element = static_cast<Element::Type>(values[0]);
        CasterType casterType = static_cast<CasterType>(values[1]);

        CasterMoveSet moveSet;

        // Construct the PentagramData_T array from the remaining values
        for (int i = 2,j=0; j < 20; i += 5 , j++) {

            int k = j * 5 + 2;

            PentagramData_T data;

            data.circle = values[k];
            data.complex = values[k + 1];
            data.will = values[k + 2];
            data.effect = values[k + 3];
            data.time = values[k + 4];

            moveSet.SetMove(j, data);
        }

        Add(element, casterType, moveSet);

    }

    file.close();

}

void CasterMoveSetDatabase::Add(Element::Type element, CasterType type, CasterMoveSet moveSet)
{
    if (!CasterMoveSetTables.count(element))
    {
        CasterMoveSetTables.emplace(element, new CasterMoveSetTable());
    }

    CasterMoveSetTables[element]->Add(type, moveSet);
}

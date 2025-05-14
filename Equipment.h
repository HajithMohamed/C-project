#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Equipment {
private:
    int EquipId;
    string EquipName;
    int HallId;
    vector<tuple<int, string, int>> equipments;

public:
    // Constructor
    Equipment() : EquipId(-1), EquipName("-1"), HallId(-1) {}

    // Getters and Setters
    void setEquipID(int id) { EquipId = id; }
    void setName(string name) { EquipName = name; }
    void setHallId(int id) { HallId = id; }
    int getEquipID() const { return EquipId; }
    string getName() const { return EquipName; }
    int getHallId() const { return HallId; }

    // Load all equipment
    bool LoadEquipments() {
        equipments.clear();
        ifstream file("equipments.txt");
        if (!file.is_open()) {
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id, hallId;
            string name;
            
            ss >> id;
            ss.ignore(); // Skip whitespace
            
            // Get name (until next tab)
            string nameTemp;
            getline(ss, nameTemp, '\t');
            name = nameTemp;
            
            ss >> hallId;
            
            equipments.push_back(make_tuple(id, name, hallId));
        }
        file.close();
        return true;
    }

    // Load specific equipment by ID
    bool LoadData(int id) {
        if (equipments.empty()) {
            LoadEquipments();
        }
        
        for (const auto& equipment : equipments) {
            if (get<0>(equipment) == id) {
                EquipId = id;
                EquipName = get<1>(equipment);
                HallId = get<2>(equipment);
                return true;
            }
        }
        return false;
    }

    // Add new equipment
    bool AddEquipment(int id, string name, int hallId) {
        // Check if equipment already exists
        for (const auto& equipment : equipments) {
            if (get<0>(equipment) == id) {
                return false;
            }
        }

        setEquipID(id);
        setName(name);
        setHallId(hallId);
        equipments.push_back(make_tuple(id, name, hallId));
        return true;
    }

    // Edit equipment details
    bool EditEquipment(int oldId, int newId, string newName, int newHallId) {
        // Find the equipment to edit
        for (auto& equipment : equipments) {
            if (get<0>(equipment) == oldId) {
                // Update the equipment
                get<0>(equipment) = newId;
                get<1>(equipment) = newName;
                get<2>(equipment) = newHallId;
                
                // Update current equipment object
                setEquipID(newId);
                setName(newName);
                setHallId(newHallId);
                return true;
            }
        }
        return false;
    }

    // Save equipment to file
    bool SaveEquipments() {
        ofstream file("equipments.txt");
        if (!file.is_open()) {
            return false;
        }

        for (const auto& equipment : equipments) {
            file << get<0>(equipment) << " " << get<1>(equipment) << "\t" << get<2>(equipment) << endl;
        }
        file.close();
        return true;
    }

    // Display all equipment
    void DisplayAllEquipment() {
        cout << "\n===== EQUIPMENT =====" << endl;
        cout << "ID\tName\t\tHall ID" << endl;
        cout << "--------------------------------" << endl;
        
        if (equipments.empty()) {
            cout << "No equipment found." << endl;
            return;
        }
        
        for (const auto& equipment : equipments) {
            cout << get<0>(equipment) << "\t" 
                 << get<1>(equipment) << "\t\t" 
                 << get<2>(equipment) << endl;
        }
    }
};

#endif // EQUIPMENT_H
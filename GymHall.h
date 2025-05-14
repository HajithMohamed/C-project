#ifndef GYMHALL_H
#define GYMHALL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class GymHall {
private:
    int HallId;
    string HallName;
    vector<pair<int, string>> halls;

public:
    // Constructor
    GymHall() : HallId(-1), HallName("-1") {}

    // Getters and Setters
    void setHallId(int id) { HallId = id; }
    void setHallName(string name) { HallName = name; }
    int getHallId() const { return HallId; }
    string getHallName() const { return HallName; }

    // Load halls from file
    bool LoadHalls() {
        halls.clear();
        ifstream file("halls.txt");
        if (!file.is_open()) {
            return false;
        }

        int id;
        string name;
        while (file >> id) {
            file.ignore(); // Skip whitespace
            getline(file, name);
            halls.push_back(make_pair(id, name));
        }
        file.close();
        return true;
    }

    // Check if hall exists
    bool CheckHalls(int id) {
        for (const auto& hall : halls) {
            if (hall.first == id) {
                return true;
            }
        }
        return false;
    }

    // Add new hall
    bool AddHall(int id, string name) {
        // Check if hall already exists
        if (CheckHalls(id)) {
            return false;
        }

        setHallId(id);
        setHallName(name);
        halls.push_back(make_pair(id, name));
        return true;
    }

    // Edit hall details
    bool EditHall(int oldId, int newId, string newName) {
        // Find the hall to edit
        for (auto& hall : halls) {
            if (hall.first == oldId) {
                hall.first = newId;
                hall.second = newName;
                setHallId(newId);
                setHallName(newName);
                return true;
            }
        }
        return false;
    }

    // Save halls to file
    bool SaveHall() {
        ofstream file("halls.txt");
        if (!file.is_open()) {
            return false;
        }

        for (const auto& hall : halls) {
            file << hall.first << " " << hall.second << endl;
        }
        file.close();
        return true;
    }

    // Display all halls
    void DisplayHalls() {
        cout << "\n===== GYM HALLS =====" << endl;
        cout << "ID\tName" << endl;
        cout << "------------------------" << endl;
        
        if (halls.empty()) {
            cout << "No gym halls found." << endl;
            return;
        }
        
        for (const auto& hall : halls) {
            cout << hall.first << "\t" << hall.second << endl;
        }
    }
};

#endif // GYMHALL_H
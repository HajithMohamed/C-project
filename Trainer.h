#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Trainer {
private:
    int TrainerId;
    string TrainerName;
    int HallId;
    vector<tuple<int, string, int>> trainers;

public:
    // Constructor
    Trainer() : TrainerId(-1), TrainerName("-1"), HallId(-1) {}

    // Getters and Setters
    void setID(int id) { TrainerId = id; }
    void setName(string name) { TrainerName = name; }
    void setHallId(int id) { HallId = id; }
    int getID() const { return TrainerId; }
    string getName() const { return TrainerName; }
    int getHallId() const { return HallId; }

    // Load all trainers
    bool LoadData() {
        trainers.clear();
        ifstream file("trainers.txt");
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
            
            trainers.push_back(make_tuple(id, name, hallId));
        }
        file.close();
        return true;
    }

    // Load specific trainer by ID
    bool LoadData(int id) {
        if (trainers.empty()) {
            LoadData();
        }
        
        for (const auto& trainer : trainers) {
            if (get<0>(trainer) == id) {
                TrainerId = id;
                TrainerName = get<1>(trainer);
                HallId = get<2>(trainer);
                return true;
            }
        }
        return false;
    }

    // Add new trainer
    bool AddTrainer(int id, string name, int hallId) {
        // Check if trainer already exists
        for (const auto& trainer : trainers) {
            if (get<0>(trainer) == id) {
                return false;
            }
        }

        setID(id);
        setName(name);
        setHallId(hallId);
        trainers.push_back(make_tuple(id, name, hallId));
        SaveData();
        return true;
    }

    // Edit trainer details
    bool EditTrainer(int oldId, int newId, string newName, int newHallId) {
        // Find the trainer to edit
        for (auto& trainer : trainers) {
            if (get<0>(trainer) == oldId) {
                // Update the trainer
                get<0>(trainer) = newId;
                get<1>(trainer) = newName;
                get<2>(trainer) = newHallId;
                
                // Update current trainer object
                setID(newId);
                setName(newName);
                setHallId(newHallId);
                return true;
            }
        }
        return false;
    }

    // Save trainers to file
    bool SaveData() {
        ofstream file("trainers.txt");
        if (!file.is_open()) {
            return false;
        }

        for (const auto& trainer : trainers) {
            file << get<0>(trainer) << " " << get<1>(trainer) << "\t" << get<2>(trainer) << endl;
        }
        file.close();
        return true;
    }

    // Display all trainers
    void DisplayAllTrainers() {
        cout << "\n===== TRAINERS =====" << endl;
        cout << "ID\tName\t\tHall ID" << endl;
        cout << "--------------------------------" << endl;
        
        if (trainers.empty()) {
            cout << "No trainers found." << endl;
            return;
        }
        
        for (const auto& trainer : trainers) {
            cout << get<0>(trainer) << "\t" 
                 << get<1>(trainer) << "\t\t" 
                 << get<2>(trainer) << endl;
        }
    }
};

#endif // TRAINER_H
#ifndef EXERCISEPLAN_H
#define EXERCISEPLAN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class ExercisePlan {
private:
    int PlanId;
    int TrainerId;
    int EquipId;
    int Duration;
    vector<tuple<int, int, int, int>> plans;

public:
    // Constructor
    ExercisePlan() : PlanId(-1), TrainerId(-1), EquipId(-1), Duration(-1) {}

    // Getters and Setters
    void SetPlanId(int id) { PlanId = id; }
    void SetTid(int id) { TrainerId = id; }
    void SetEid(int id) { EquipId = id; }
    void Setduration(int duration) { Duration = duration; }
    int GetPlanId() const { return PlanId; }
    int GetTid() const { return TrainerId; }
    int GetEid() const { return EquipId; }
    int GetDuration() const { return Duration; }

    // Load all plans from file
    bool LoadPlansFromFile() {
        plans.clear();
        ifstream file("exercise_plans.txt");
        if (!file.is_open()) {
            return false;
        }

        int planId, trainerId, equipId, duration;
        while (file >> planId >> trainerId >> equipId >> duration) {
            plans.push_back(make_tuple(planId, trainerId, equipId, duration));
        }
        file.close();
        return true;
    }

    // Load specific plan by ID
    bool LoadPlans(int id) {
        if (plans.empty()) {
            LoadPlansFromFile();
        }
        
        for (const auto& plan : plans) {
            if (get<0>(plan) == id) {
                PlanId = id;
                TrainerId = get<1>(plan);
                EquipId = get<2>(plan);
                Duration = get<3>(plan);
                return true;
            }
        }
        return false;
    }

    // Add new exercise plan
    bool AddPlans(int planId, int trainerId, int equipId, int duration) {
        // Check if plan already exists
        for (const auto& plan : plans) {
            if (get<0>(plan) == planId) {
                return false;
            }
        }

        SetPlanId(planId);
        SetTid(trainerId);
        SetEid(equipId);
        Setduration(duration);
        plans.push_back(make_tuple(planId, trainerId, equipId, duration));
        return true;
    }

    // Edit exercise plan
    bool EditPlans(int oldPlanId, int newPlanId, int newTrainerId, int newEquipId, int newDuration) {
        // Find the plan to edit
        for (auto& plan : plans) {
            if (get<0>(plan) == oldPlanId) {
                // Update the plan
                get<0>(plan) = newPlanId;
                get<1>(plan) = newTrainerId;
                get<2>(plan) = newEquipId;
                get<3>(plan) = newDuration;
                
                // Update current plan object
                SetPlanId(newPlanId);
                SetTid(newTrainerId);
                SetEid(newEquipId);
                Setduration(newDuration);
                return true;
            }
        }
        return false;
    }

    // Save plans to file
    bool SavePlans() {
        ofstream file("exercise_plans.txt");
        if (!file.is_open()) {
            return false;
        }

        for (const auto& plan : plans) {
            file << get<0>(plan) << " " 
                 << get<1>(plan) << " " 
                 << get<2>(plan) << " " 
                 << get<3>(plan) << endl;
        }
        file.close();
        return true;
    }

    // Display all exercise plans
    void DisplayAllPlans() {
        cout << "\n===== EXERCISE PLANS =====" << endl;
        cout << "Plan ID\tTrainer ID\tEquipment ID\tDuration (mins)" << endl;
        cout << "---------------------------------------------------" << endl;
        
        if (plans.empty()) {
            cout << "No exercise plans found." << endl;
            return;
        }
        
        for (const auto& plan : plans) {
            cout << get<0>(plan) << "\t" 
                 << get<1>(plan) << "\t\t" 
                 << get<2>(plan) << "\t\t" 
                 << get<3>(plan) << endl;
        }
    }
};

#endif // EXERCISEPLAN_H
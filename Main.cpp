#include <iostream>
#include <string>
#include "GymHall.h"
#include "Trainer.h"
#include "Equipment.h"
#include "ExcercisePlan.h"
#include "Customer.h"

using namespace std;

// Function prototypes
void displayMainMenu();
void handleGymHallOperations(GymHall& G);
void handleTrainerOperations(Trainer& T, GymHall& G);
void handleEquipmentOperations(Equipment& E, GymHall& G);
void handleExercisePlanOperations(ExercisePlan& EP, Trainer& T, Equipment& E);
void handleCustomerOperations(Customer& C, GymHall& G, Trainer& T, ExercisePlan& EP);

int main() {
    // Initialize objects
    GymHall G;
    Trainer T;
    Equipment E;
    ExercisePlan EP;
    Customer C;
    
    // Load all data at startup
    G.LoadHalls();
    T.LoadData();
    E.LoadEquipments();
    EP.LoadPlansFromFile();
    C.LoadData();
    C.LoadSubscription();
    
    // Authentication
    string username, password;
    bool authenticated = false;
    
    cout << "===== GYM MANAGEMENT SYSTEM =====" << endl;
    cout << "Please login to continue" << endl;
    
    for (int attempts = 0; attempts < 3; attempts++) {
        cout << "\nUsername: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        
        if (username == "Admin" && password == "admin") {
            authenticated = true;
            cout << "\nAccess Granted. Welcome Admin!" << endl;
            break;
        } else {
            cout << "\nInvalid username or password. Please try again." << endl;
            cout << "Attempts remaining: " << 2 - attempts << endl;
        }
    }
    
    if (!authenticated) {
        cout << "\nToo many failed attempts. Exiting program." << endl;
        return 0;
    }
    
    // Main program loop
    int choice = 0;
    do {
        displayMainMenu();
        cout << "\nEnter your choice (0-5): ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                handleGymHallOperations(G);
                break;
            case 2:
                handleTrainerOperations(T, G);
                break;
            case 3:
                handleEquipmentOperations(E, G);
                break;
            case 4:
                handleExercisePlanOperations(EP, T, E);
                break;
            case 5:
                handleCustomerOperations(C, G, T, EP);
                break;
            case 0:
                cout << "Exiting program. Thank you for using Gym Management System!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    
    return 0;
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Gym Hall Management" << endl;
    cout << "2. Trainer Management" << endl;
    cout << "3. Equipment Management" << endl;
    cout << "4. Exercise Plan Management" << endl;
    cout << "5. Customer Management" << endl;
    cout << "0. Exit" << endl;
}

void handleGymHallOperations(GymHall& G) {
    int choice = 0;
    do {
        cout << "\n===== GYM HALL MANAGEMENT =====" << endl;
        cout << "1. Add New Gym Hall" << endl;
        cout << "2. Edit Gym Hall" << endl;
        cout << "3. View All Gym Halls" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nEnter your choice (0-3): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "\nEnter Gym Hall ID: ";
                cin >> id;
                cout << "Enter Gym Hall Name: ";
                cin.ignore();
                getline(cin, name);
                
                if (!G.CheckHalls(id)) {
                    bool success = G.AddHall(id, name);
                    if (success) {
                        cout << "Gym Hall added successfully!" << endl;
                        G.SaveHall();
                    } else {
                        cout << "Failed to add Gym Hall." << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID already exists!" << endl;
                }
                break;
            }
            case 2: {
                int id, newId;
                string newName;
                cout << "\nEnter Current Gym Hall ID: ";
                cin >> id;
                cout << "Enter New Gym Hall ID: ";
                cin >> newId;
                cout << "Enter New Gym Hall Name: ";
                cin.ignore();
                getline(cin, newName);
                
                if (G.CheckHalls(id)) {
                    bool success = G.EditHall(id, newId, newName);
                    if (success) {
                        cout << "Gym Hall updated successfully!" << endl;
                        G.SaveHall();
                    } else {
                        cout << "Failed to update Gym Hall." << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID does not exist!" << endl;
                }
                break;
            }
            case 3:
                G.DisplayHalls();
                break;
            case 0:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void handleTrainerOperations(Trainer& T, GymHall& G) {
    int choice = 0;
    do {
        cout << "\n===== TRAINER MANAGEMENT =====" << endl;
        cout << "1. Add New Trainer" << endl;
        cout << "2. Edit Trainer" << endl;
        cout << "3. View All Trainers" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nEnter your choice (0-3): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id, hallId;
                string name;
                cout << "\nEnter Trainer ID: ";
                cin >> id;
                cout << "Enter Trainer Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Gym Hall ID: ";
                cin >> hallId;
                
                if (G.CheckHalls(hallId)) {
                    if (!T.LoadData(id)) {
                        bool success = T.AddTrainer(id, name, hallId);
                        if (success) {
                            cout << "Trainer added successfully!" << endl;
                            T.SaveData();
                        } else {
                            cout << "Failed to add Trainer." << endl;
                        }
                    } else {
                        cout << "Error: Trainer ID already exists!" << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID does not exist!" << endl;
                }
                break;
            }
            case 2: {
                int id, newId, hallId;
                string newName;
                cout << "\nEnter Current Trainer ID: ";
                cin >> id;
                cout << "Enter New Trainer ID: ";
                cin >> newId;
                cout << "Enter New Trainer Name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter Gym Hall ID: ";
                cin >> hallId;
                
                if (G.CheckHalls(hallId)) {
                    if (T.LoadData(id)) {
                        bool success = T.EditTrainer(id, newId, newName, hallId);
                        if (success) {
                            cout << "Trainer updated successfully!" << endl;
                            T.SaveData();
                        } else {
                            cout << "Failed to update Trainer." << endl;
                        }
                    } else {
                        cout << "Error: Trainer ID does not exist!" << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID does not exist!" << endl;
                }
                break;
            }
            case 3:
                T.DisplayAllTrainers();
                break;
            case 0:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void handleEquipmentOperations(Equipment& E, GymHall& G) {
    int choice = 0;
    do {
        cout << "\n===== EQUIPMENT MANAGEMENT =====" << endl;
        cout << "1. Add New Equipment" << endl;
        cout << "2. Edit Equipment" << endl;
        cout << "3. View All Equipment" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nEnter your choice (0-3): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id, hallId;
                string name;
                cout << "\nEnter Equipment ID: ";
                cin >> id;
                cout << "Enter Equipment Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Gym Hall ID: ";
                cin >> hallId;
                
                if (G.CheckHalls(hallId)) {
                    if (!E.LoadData(id)) {
                        bool success = E.AddEquipment(id, name, hallId);
                        if (success) {
                            cout << "Equipment added successfully!" << endl;
                            E.SaveEquipments();
                        } else {
                            cout << "Failed to add Equipment." << endl;
                        }
                    } else {
                        cout << "Error: Equipment ID already exists!" << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID does not exist!" << endl;
                }
                break;
            }
            case 2: {
                int id, newId, hallId;
                string newName;
                cout << "\nEnter Current Equipment ID: ";
                cin >> id;
                cout << "Enter New Equipment ID: ";
                cin >> newId;
                cout << "Enter New Equipment Name: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Enter Gym Hall ID: ";
                cin >> hallId;
                
                if (G.CheckHalls(hallId)) {
                    if (E.LoadData(id)) {
                        if (!E.LoadData(newId) || id == newId) {
                            bool success = E.EditEquipment(id, newId, newName, hallId);
                            if (success) {
                                cout << "Equipment updated successfully!" << endl;
                                E.SaveEquipments();
                            } else {
                                cout << "Failed to update Equipment." << endl;
                            }
                        } else {
                            cout << "Error: New Equipment ID already exists!" << endl;
                        }
                    } else {
                        cout << "Error: Equipment ID does not exist!" << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID does not exist!" << endl;
                }
                break;
            }
            case 3:
                E.DisplayAllEquipment();
                break;
            case 0:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void handleExercisePlanOperations(ExercisePlan& EP, Trainer& T, Equipment& E) {
    int choice = 0;
    do {
        cout << "\n===== EXERCISE PLAN MANAGEMENT =====" << endl;
        cout << "1. Add New Exercise Plan" << endl;
        cout << "2. Edit Exercise Plan" << endl;
        cout << "3. View All Exercise Plans" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nEnter your choice (0-3): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int planId, trainerId, equipmentId, duration;
                cout << "\nEnter Plan ID: ";
                cin >> planId;
                cout << "Enter Trainer ID: ";
                cin >> trainerId;
                cout << "Enter Equipment ID: ";
                cin >> equipmentId;
                cout << "Enter Duration (in minutes): ";
                cin >> duration;
                
                if (!EP.LoadPlans(planId)) {
                    if (T.LoadData(trainerId)) {
                        if (E.LoadData(equipmentId)) {
                            bool success = EP.AddPlans(planId, trainerId, equipmentId, duration);
                            if (success) {
                                cout << "Exercise Plan added successfully!" << endl;
                                EP.SavePlans();
                            } else {
                                cout << "Failed to add Exercise Plan." << endl;
                            }
                        } else {
                            cout << "Error: Equipment ID does not exist!" << endl;
                        }
                    } else {
                        cout << "Error: Trainer ID does not exist!" << endl;
                    }
                } else {
                    cout << "Error: Plan ID already exists!" << endl;
                }
                break;
            }
            case 2: {
                int planId, newPlanId, trainerId, equipmentId, duration;
                cout << "\nEnter Current Plan ID: ";
                cin >> planId;
                cout << "Enter New Plan ID: ";
                cin >> newPlanId;
                cout << "Enter Trainer ID: ";
                cin >> trainerId;
                cout << "Enter Equipment ID: ";
                cin >> equipmentId;
                cout << "Enter Duration (in minutes): ";
                cin >> duration;
                
                if (EP.LoadPlans(planId)) {
                    if (T.LoadData(trainerId)) {
                        if (E.LoadData(equipmentId)) {
                            bool success = EP.EditPlans(planId, newPlanId, trainerId, equipmentId, duration);
                            if (success) {
                                cout << "Exercise Plan updated successfully!" << endl;
                                EP.SavePlans();
                            } else {
                                cout << "Failed to update Exercise Plan." << endl;
                            }
                        } else {
                            cout << "Error: Equipment ID does not exist!" << endl;
                        }
                    } else {
                        cout << "Error: Trainer ID does not exist!" << endl;
                    }
                } else {
                    cout << "Error: Plan ID does not exist!" << endl;
                }
                break;
            }
            case 3:
                EP.DisplayAllPlans();
                break;
            case 0:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void handleCustomerOperations(Customer& C, GymHall& G, Trainer& T, ExercisePlan& EP) {
    int choice = 0;
    do {
        cout << "\n===== CUSTOMER MANAGEMENT =====" << endl;
        cout << "1. Add New Customer" << endl;
        cout << "2. Edit Customer" << endl;
        cout << "3. View All Customers" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "\nEnter your choice (0-3): ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int customerId, subscriptionId, trainerId, planId, hallId;
                string name, address, phone, email, date;
                
                cout << "\nEnter Customer ID: ";
                cin >> customerId;
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Customer Address: ";
                getline(cin, address);
                cout << "Enter Customer Phone: ";
                getline(cin, phone);
                cout << "Enter Customer Email: ";
                getline(cin, email);
                cout << "Enter Subscription ID: ";
                cin >> subscriptionId;
                cout << "Enter Registration Date (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, date);
                cout << "Enter Trainer ID: ";
                cin >> trainerId;
                cout << "Enter Plan ID: ";
                cin >> planId;
                cout << "Enter Gym Hall ID: ";
                cin >> hallId;
                
                if (G.CheckHalls(hallId)) {
                    if (!C.CheckCustomer(customerId)) {
                        if (!C.CheckSubscription(subscriptionId)) {
                            if (T.LoadData(trainerId)) {
                                if (EP.LoadPlans(planId)) {
                                    if (!C.CheckTrainer(trainerId)) {
                                        bool success = C.addCustomer(customerId, name, address, phone, email, subscriptionId, date, trainerId, planId, hallId);
                                        if (success) {
                                            cout << "Customer added successfully!" << endl;
                                            C.SaveData();
                                            C.SaveSubscription();
                                        } else {
                                            cout << "Failed to add Customer." << endl;
                                        }
                                    } else {
                                        cout << "Error: Trainer is already booked!" << endl;
                                    }
                                } else {
                                    cout << "Error: Exercise Plan does not exist!" << endl;
                                }
                            } else {
                                cout << "Error: Trainer ID does not exist!" << endl;
                            }
                        } else {
                            cout << "Error: Subscription ID already exists!" << endl;
                        }
                    } else {
                        cout << "Error: Customer ID already exists!" << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID does not exist!" << endl;
                }
                break;
            }
            case 2: {
                int oldCustomerId, newCustomerId, subscriptionId, trainerId, planId, hallId;
                string name, address, phone, email, date;
                
                cout << "\nEnter Current Customer ID: ";
                cin >> oldCustomerId;
                cout << "Enter New Customer ID: ";
                cin >> newCustomerId;
                cout << "Enter Customer Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Customer Address: ";
                getline(cin, address);
                cout << "Enter Customer Phone: ";
                getline(cin, phone);
                cout << "Enter Customer Email: ";
                getline(cin, email);
                cout << "Enter Subscription ID: ";
                cin >> subscriptionId;
                cout << "Enter Registration Date (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, date);
                cout << "Enter Trainer ID: ";
                cin >> trainerId;
                cout << "Enter Plan ID: ";
                cin >> planId;
                cout << "Enter Gym Hall ID: ";
                cin >> hallId;
                
                if (G.CheckHalls(hallId)) {
                    if (C.CheckCustomer(oldCustomerId)) {
                        if (T.LoadData(trainerId)) {
                            if (EP.LoadPlans(planId)) {
                                if (!C.CheckTrainer(trainerId)) {
                                    bool success = C.EditCustomer(oldCustomerId, newCustomerId, name, address, phone, email, subscriptionId, date, trainerId, planId, hallId);
                                    if (success) {
                                        cout << "Customer updated successfully!" << endl;
                                        C.SaveData();
                                        C.SaveSubscription();
                                    } else {
                                        cout << "Failed to update Customer." << endl;
                                    }
                                } else {
                                    cout << "Error: Trainer is already booked!" << endl;
                                }
                            } else {
                                cout << "Error: Exercise Plan does not exist!" << endl;
                            }
                        } else {
                            cout << "Error: Trainer ID does not exist!" << endl;
                        }
                    } else {
                        cout << "Error: Customer ID does not exist!" << endl;
                    }
                } else {
                    cout << "Error: Gym Hall ID does not exist!" << endl;
                }
                break;
            }
            case 3:
                C.DisplayAllCustomers();
                break;
            case 0:
                cout << "Returning to Main Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}
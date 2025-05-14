#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Customer {
private:
    int CustomerId;
    string CustomerName;
    string Address;
    string Phone;
    string Email;
    int SubscriptionId;
    string RegistrationDate;
    int TrainerId;
    int PlanId;
    int HallId;
    
    vector<tuple<int, string, string, string, string, int, string, int, int, int>> customers;
    vector<int> subscriptions;
    vector<int> bookedTrainers;

public:
    // Constructor
    Customer() : CustomerId(-1), CustomerName("-1"), Address("-1"), Phone("-1"), 
                Email("-1"), SubscriptionId(-1), RegistrationDate("-1"), 
                TrainerId(-1), PlanId(-1), HallId(-1) {}

    // Getters and Setters
    void setID(int id) { CustomerId = id; }
    void setName(string name) { CustomerName = name; }
    void setAddress(string addr) { Address = addr; }
    void setPhone(string phone) { Phone = phone; }
    void setEmail(string email) { Email = email; }
    void SetSubId(int id) { SubscriptionId = id; }
    void SetDate(string date) { RegistrationDate = date; }
    void SetTid(int id) { TrainerId = id; }
    void SetPId(int id) { PlanId = id; }
    void setHallId(int id) { HallId = id; }
    
    int getID() const { return CustomerId; }
    string getName() const { return CustomerName; }
    string getAddress() const { return Address; }
    string getPhone() const { return Phone; }
    string getEmail() const { return Email; }
    int getSubId() const { return SubscriptionId; }
    string getDate() const { return RegistrationDate; }
    int getTid() const { return TrainerId; }
    int getPId() const { return PlanId; }
    int getHallId() const { return HallId; }

    // Load customer data from file
    bool LoadData() {
        customers.clear();
        bookedTrainers.clear();
        
        ifstream file("customers.txt");
        if (!file.is_open()) {
            return false;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int cid, sid, tid, pid, hid;
            string name, addr, phone, email, date;
            
            ss >> cid;
            ss.ignore(); // Skip whitespace
            
            // Get name
            getline(ss, name, '\t');
            
            // Get address
            getline(ss, addr, '\t');
            
            // Get phone
            getline(ss, phone, '\t');
            
            // Get email
            getline(ss, email, '\t');
            
            ss >> sid;
            ss.ignore(); // Skip whitespace
            
            // Get date
            getline(ss, date, '\t');
            
            ss >> tid >> pid >> hid;
            
            customers.push_back(make_tuple(cid, name, addr, phone, email, sid, date, tid, pid, hid));
            bookedTrainers.push_back(tid);
        }
        file.close();
        return true;
    }

    // Load subscription data from file
    bool LoadSubscription() {
        subscriptions.clear();
        
        ifstream file("subscriptions.txt");
        if (!file.is_open()) {
            return false;
        }

        int sid;
        while (file >> sid) {
            subscriptions.push_back(sid);
        }
        file.close();
        return true;
    }

    // Check if customer exists
    bool CheckCustomer(int id) {
        for (const auto& customer : customers) {
            if (get<0>(customer) == id) {
                return true;
            }
        }
        return false;
    }

    // Check if subscription exists
    bool CheckSubscription(int id) {
        for (int sid : subscriptions) {
            if (sid == id) {
                return true;
            }
        }
        return false;
    }

    // Check if trainer is already booked
    bool CheckTrainer(int id) {
        for (int tid : bookedTrainers) {
            if (tid == id) {
                return true;
            }
        }
        return false;
    }

    // Add new customer
    bool addCustomer(int id, string name, string addr, string phone, string email, 
                    int sid, string date, int tid, int pid, int hid) {
        // Set current customer object
        setID(id);
        setName(name);
        setAddress(addr);
        setPhone(phone);
        setEmail(email);
        SetSubId(sid);
        SetDate(date);
        SetTid(tid);
        SetPId(pid);
        setHallId(hid);
        
        // Add to vectors
        customers.push_back(make_tuple(id, name, addr, phone, email, sid, date, tid, pid, hid));
        subscriptions.push_back(sid);
        bookedTrainers.push_back(tid);
        
        return true;
    }

    // Edit customer
    bool EditCustomer(int oldId, int newId, string name, string addr, string phone, 
                     string email, int sid, string date, int tid, int pid, int hid) {
        // Find the customer to edit
        for (auto& customer : customers) {
            if (get<0>(customer) == oldId) {
                // Remove old trainer from booked trainers
                for (auto it = bookedTrainers.begin(); it != bookedTrainers.end(); ++it) {
                    if (*it == get<7>(customer)) {
                        bookedTrainers.erase(it);
                        break;
                    }
                }
                
                // Update the customer
                get<0>(customer) = newId;
                get<1>(customer) = name;
                get<2>(customer) = addr;
                get<3>(customer) = phone;
                get<4>(customer) = email;
                get<5>(customer) = sid;
                get<6>(customer) = date;
                get<7>(customer) = tid;
                get<8>(customer) = pid;
                get<9>(customer) = hid;
                
                // Add new trainer to booked trainers
                bookedTrainers.push_back(tid);
                
                // Update current customer object
                setID(newId);
                setName(name);
                setAddress(addr);
                setPhone(phone);
                setEmail(email);
                SetSubId(sid);
                SetDate(date);
                SetTid(tid);
                SetPId(pid);
                setHallId(hid);
                
                return true;
            }
        }
        return false;
    }

    // Save customer data to file
    bool SaveData() {
        ofstream file("customers.txt");
        if (!file.is_open()) {
            return false;
        }

        for (const auto& customer : customers) {
            file << get<0>(customer) << " " 
                 << get<1>(customer) << "\t" 
                 << get<2>(customer) << "\t" 
                 << get<3>(customer) << "\t" 
                 << get<4>(customer) << "\t" 
                 << get<5>(customer) << " " 
                 << get<6>(customer) << "\t" 
                 << get<7>(customer) << " " 
                 << get<8>(customer) << " " 
                 << get<9>(customer) << endl;
        }
        file.close();
        return true;
    }

    // Save subscription data to file
    bool SaveSubscription() {
        ofstream file("subscriptions.txt");
        if (!file.is_open()) {
            return false;
        }

        for (int sid : subscriptions) {
            file << sid << endl;
        }
        file.close();
        return true;
    }

    // Display all customers
    void DisplayAllCustomers() {
        cout << "\n===== CUSTOMERS =====" << endl;
        cout << "ID\tName\t\tPhone\t\tEmail\t\tSub ID\tTrainer ID\tPlan ID\tHall ID" << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
        
        if (customers.empty()) {
            cout << "No customers found." << endl;
            return;
        }
        
        for (const auto& customer : customers) {
            cout << get<0>(customer) << "\t" 
                 << get<1>(customer) << "\t\t" 
                 << get<3>(customer) << "\t" 
                 << get<4>(customer) << "\t" 
                 << get<5>(customer) << "\t" 
                 << get<7>(customer) << "\t\t" 
                 << get<8>(customer) << "\t" 
                 << get<9>(customer) << endl;
        }
    }
};

#endif // CUSTOMER_H
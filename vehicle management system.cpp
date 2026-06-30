

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Vehicle {
public:
    int vehicleID;
    string make;
    string model;
    int year;
    int mileage;

    void input() {
        cout << "Enter vehicle ID: ";
        cin >> vehicleID;
        cin.ignore();
        cout << "Enter vehicle make: ";
        getline(cin, make);
        cout << "Enter vehicle model: ";
        getline(cin, model);
        cout << "Enter vehicle year: ";
        cin >> year;
        cout << "Enter vehicle mileage: ";
        cin >> mileage;
    }

    void display() {
        cout << vehicleID << " | " << make << " | " << model << " | " << year << " | " << mileage << endl;
    }

    void saveToFile(ofstream& outFile) {
        outFile << vehicleID << endl
            << make << endl
            << model << endl
            << year << endl
            << mileage << endl;
    }

    void loadFromFile(ifstream& inFile) {
        getline(inFile, make);
        getline(inFile, model);
        inFile >> vehicleID >> year >> mileage;
        inFile.ignore(); // Clear newline
    }
};

class VehicleSystem {
    Vehicle vehicles[100];
    int numVehicles = 0;
    string filename = "vehicles.txt";

public:
    void load() {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "No previous data found.\n";
            return;
        }

        while (inFile && numVehicles < 100) {
            vehicles[numVehicles].loadFromFile(inFile);
            numVehicles++;
        }

        inFile.close();
        cout << "Data loaded.\n";
    }

    void save() {
        ofstream outFile(filename);
        for (int i = 0; i < numVehicles; i++) {
            vehicles[i].saveToFile(outFile);
        }
        outFile.close();
        cout << "Data saved.\n";
    }

    void add() {
        if (numVehicles < 100) {
            vehicles[numVehicles].input();
            numVehicles++;
            cout << "Vehicle added.\n";
        }
        else {
            cout << "Storage full!\n";
        }
    }

    void displayAll() {
        if (numVehicles == 0) {
            cout << "No vehicles.\n";
            return;
        }

        cout << "ID | Make | Model | Year | Mileage\n";
        for (int i = 0; i < numVehicles; i++) {
            vehicles[i].display();
        }
    }

    void search() {
        int id;
        cout << "Enter ID to search: ";
        cin >> id;

        for (int i = 0; i < numVehicles; i++) {
            if (vehicles[i].vehicleID == id) {
                vehicles[i].display();
                return;
            }
        }

        cout << "Vehicle not found.\n";
    }

    void update() {
        int id;
        cout << "Enter ID to update: ";
        cin >> id;

        for (int i = 0; i < numVehicles; i++) {
            if (vehicles[i].vehicleID == id) {
                cout << "Enter new details:\n";
                vehicles[i].input();
                cout << "Updated.\n";
                return;
            }
        }

        cout << "Vehicle not found.\n";
    }

    void remove() {
        int id;
        cout << "Enter ID to delete: ";
        cin >> id;

        for (int i = 0; i < numVehicles; i++) {
            if (vehicles[i].vehicleID == id) {
                for (int j = i; j < numVehicles - 1; j++) {
                    vehicles[j] = vehicles[j + 1];
                }
                numVehicles--;
                cout << "Deleted.\n";
                return;
            }
        }

        cout << "Vehicle not found.\n";
    }

    void menu() {
        int choice;
        do {
            cout << "\nVehicle Management System\n";
            cout << "1. Add Vehicle\n2. Show All Vehicles\n3. Search Vehicle\n";
            cout << "4. Update Vehicle\n5. Delete Vehicle\n6. Save and Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: add(); break;
            case 2: displayAll(); break;
            case 3: search(); break;
            case 4: update(); break;
            case 5: remove(); break;
            case 6: save(); cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
            }
        } while (choice != 6);
    }
};

int main() {
    VehicleSystem system;
    system.load();
    system.menu();
    return 0;
}
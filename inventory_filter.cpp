#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class InventoryItem {
public:
    string ip;
    string os;
    string memory;
    string cpu;
    string disk;

    InventoryItem(string ip, string os,
                  string memory,
                  string cpu,
                  string disk) {
        this->ip = ip;
        this->os = os;
        this->memory = memory;
        this->cpu = cpu;
        this->disk = disk;
    }

    void display() {
        cout << "IP: " << ip << endl;
        cout << "OS: " << os << endl;
        cout << "Memory: " << memory << endl;
        cout << "CPU: " << cpu << endl;
        cout << "Disk: " << disk << endl;
        cout << "------------------------" << endl;
    }
};

class InventoryManager {
private:
    vector<InventoryItem> inventoryList;

    double extractMemory(string mem) {
        return stod(mem.substr(0, mem.find("GB")));
    }

    double extractCPU(string cpu) {
        return stod(cpu.substr(0, cpu.find("Ghz")));
    }

public:
    void loadData(string filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            throw runtime_error("Unable to open JSON file");
        }

        json data;
        file >> data;

        auto inventory = data["inventory"];

        for (auto& item : inventory.items()) {
            auto value = item.value();

            InventoryItem obj(
                value["ip"],
                value["os"],
                value["memory"],
                value["cpu"],
                value["disk"]
            );

            inventoryList.push_back(obj);
        }
    }

    void filterData(string criteria) {

        if (criteria.empty()) {
            throw invalid_argument("Filter criteria missing");
        }

        if (criteria == "Memory") {

            InventoryItem* maxMem = &inventoryList[0];

            for (auto& item : inventoryList) {
                if (extractMemory(item.memory) >
                    extractMemory(maxMem->memory)) {
                    maxMem = &item;
                }
            }

            cout << "\nSystem with Maximum Memory:\n";
            maxMem->display();
        }

        else if (criteria == "CPU") {

            InventoryItem* maxCPU = &inventoryList[0];

            for (auto& item : inventoryList) {
                if (extractCPU(item.cpu) >
                    extractCPU(maxCPU->cpu)) {
                    maxCPU = &item;
                }
            }

            cout << "\nSystem with Maximum CPU:\n";
            maxCPU->display();
        }

        else if (criteria == "Linux" ||
                 criteria == "Windows") {

            cout << "\nMatching Systems:\n";

            for (auto& item : inventoryList) {
                if (item.os == criteria) {
                    item.display();
                }
            }
        }

        else {
            throw invalid_argument("Invalid filter criteria");
        }
    }
};

int main() {

    try {
        InventoryManager manager;

        manager.loadData("inventory.json");

        string criteria;

        cout << "Enter filter criteria "
             << "(Memory/CPU/Linux/Windows): ";

        cin >> criteria;

        manager.filterData(criteria);
    }

    catch (exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    return 0;
}
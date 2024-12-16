#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Parkzone {
protected:
    string name;
    double waterUs; 

public:
    Parkzone(string name, double waterUs) : name(name), waterUs(waterUs) {}

    virtual void displayInfo() const {
        cout << "Zone name: " << name << endl;
        cout << "Water usage: " << waterUs << " L/day" << endl;
    }

    virtual double calculatedailycost(double waterprice) const {
        return waterUs * waterprice;
    }

    virtual ~Parkzone() {}
};

class Desertzone : public Parkzone {
private:
    int sandDunes; 
    bool solarEnergy;

public:
    Desertzone(string name, double waterUs, int sandDunes, bool solarEnergy)
        : Parkzone(name, waterUs), sandDunes(sandDunes), solarEnergy(solarEnergy) {
    }

    void displayInfo() const override {
        Parkzone::displayInfo();
        cout << "Number of Sand Dunes: " << sandDunes << endl;
        cout << "Using Solar Energy: " << (solarEnergy ? "Yes" : "No") << endl;
    }
};

class OasisZone : public Parkzone {
private:
    int palmTrees; 
    bool recyclingsys; 

public:
    OasisZone(string name, double waterUs, int palmTrees, bool recyclingsys)
        : Parkzone(name, waterUs), palmTrees(palmTrees), recyclingsys(recyclingsys) {
    }

    void displayInfo() const override {
        Parkzone::displayInfo();
        cout << "Number of palm trees: " << palmTrees << endl;
        cout << "Water recycling system: " << (recyclingsys ? "Yes" : "No") << endl;
    }


    double calculatedailycost(double waterPrice) const override {
        double effectiveWaterUsage = recyclingsys ? waterUs * 0.8 : waterUs;
        return effectiveWaterUsage * waterPrice;
    }
};

class Park {
private:
    vector<unique_ptr<Parkzone>> zones;
    double waterPricePerLiter; 

public:
    Park(double wPricePerLit) : waterPricePerLiter(wPricePerLit) {}

    void addZone(unique_ptr<Parkzone> zone) {
        zones.push_back(move(zone));
    }

    void displayParkDetails() const {
        cout << "Park details" << endl;
        for (const auto& zone : zones) {
            zone->displayInfo();
            cout << "Daily water cost: $" << zone->calculatedailycost(waterPricePerLiter) << endl;
            cout << "----------------------" << endl;
        }
    }

    double calculateTotalDailyCost() const {
        double totalCost = 0;
        for (const auto& zone : zones) {
            totalCost += zone->calculatedailycost(waterPricePerLiter);
        }
        return totalCost;
    }
};

int main() {
    Park desertOasisPark(0.05); 
    desertOasisPark.addZone(make_unique<Desertzone>("Sahara simulation", 5200, 15, true));
    desertOasisPark.addZone(make_unique<OasisZone>("Tropical oasis", 6900, 50, true));
    desertOasisPark.addZone(make_unique<Desertzone>("Great desert", 4300, 10, false));
    desertOasisPark.addZone(make_unique<OasisZone>("Small oasis", 3300, 20, false));
    desertOasisPark.displayParkDetails();
    cout << "Total daily water cost $" << desertOasisPark.calculateTotalDailyCost() << " " << endl;

    return 0;
}

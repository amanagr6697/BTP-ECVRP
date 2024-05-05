#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility> // for pair
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace std;
using namespace rapidjson;

int main() {
    // Load JSON data from a file
    FILE* file = fopen("data.json", "rb");
    if (!file) {
        cerr << "Failed to open JSON file." << endl;
        return 1;
    }

    // Parse JSON data
    char readBuffer[65536];
    FileReadStream inputStream(file, readBuffer, sizeof(readBuffer));
    Document jsonData;
    jsonData.ParseStream(inputStream);
    fclose(file);

    // Extract data from JSON and fill variables and arrays
    vector<pair<double, double>> locations;
    vector<double> demandWeights;
    vector<double> mxBatteryLevels;
    vector<double> mxCostAllowed;
    vector<double> mxWeightAllowed;
    double fastChargingTimePerUnitOfCharge;
    double mediumChargingTimePerUnitOfCharge;
    double slowChargingTimePerUnitOfCharge;
    double batterySwappingCost;
    double batterySwappingTime;
    int mxVehicles;
    int mxCustomers;
    vector<pair<double, double>> batteryChargingStations;
    vector<pair<double, double>> batterySwappingStations;
    double dischargingConst;
    double temperature;
    double scalingFactor;
    double parameter;
    int fastTimeChargers;
    int mediumTimeChargers;
    int slowTimeChargers;
    double costPerUnitChargeOfFast;
    double costPerUnitChargeOfMedium;
    double costPerUnitChargeOfSlow;
    vector<double> speedOfVehicles;
    vector<double> weightFactorForSpeed;
    vector<double> weightFactorForDistance;
    int mxBatteryChargingStations;
    int mxBatterySwappingStations;
    vector<string> locationsText;
    vector<string> batteryChargingStationsText;
    vector<string> batterySwappingStationsText;
    int batteriesAvailable;

    // Fill variables and arrays from JSON data
    // locations array

    // // Print arrays and variables
    // cout << "locations array:" << endl;
    // for (auto& loc : locations) {
    //     cout << "(" << loc.first << ", " << loc.second << ")" << endl;
    // }

    // for (auto& loc : batteryChargingStations) {
    //     cout << "(" << loc.first << ", " << loc.second << ")" << endl;
    // }
    
    // for (auto& loc : batterySwappingStations) {
    //     cout << "(" << loc.first << ", " << loc.second << ")" << endl;
    // }

    // cout << "\ndemandWeights array:" << endl;
    // for (auto weight : demandWeights) {
    //     cout << weight << endl;
    // }

    // cout << "\nmxBatteryLevels array:" << endl;
    // for (auto level : mxBatteryLevels) {
    //     cout << level << endl;
    // }

    // cout << "\nmxCostAllowed array:" << endl;
    // for (auto cost : mxCostAllowed) {
    //     cout << cost << endl;
    // }

    // cout << "\nmxWeightAllowed array:" << endl;
    // for (auto weight : mxWeightAllowed) {
    //     cout << weight << endl;
    // }

    // cout << "\nOther variables:" << endl;
    // cout << "fastChargingTimePerUnitOfCharge: " << fastChargingTimePerUnitOfCharge << endl;
    // cout << "mediumChargingTimePerUnitOfCharge: " << mediumChargingTimePerUnitOfCharge << endl;
    // cout << "slowChargingTimePerUnitOfCharge: " << slowChargingTimePerUnitOfCharge << endl;
    // cout << "batterySwappingCost: " << batterySwappingCost << endl;
    // cout << "batterySwappingTime: " << batterySwappingTime << endl;
    // cout << "mxVehicles: " << mxVehicles << endl;
    // cout << "mxCustomer: " << mxCustomers << endl;
    // cout << "dischargingConst: " << dischargingConst << endl;
    // cout << "temperature: " << temperature << endl;
    // cout << "scalingFactor: " << scalingFactor << endl;
    // cout << "parameter: " << parameter << endl;
    // cout << "fastTimeChargers: " << fastTimeChargers << endl;
    // cout << "mediumTimeChargers: " << mediumTimeChargers << endl;
    // cout << "slowTimeChargers: " << slowTimeChargers << endl;
    // cout << "costPerUnitChargeOfFast: " << costPerUnitChargeOfFast << endl;
    // cout << "costPerUnitChargeOfMedium: " << costPerUnitChargeOfMedium << endl;
    // cout << "costPerUnitChargeOfSlow: " << costPerUnitChargeOfSlow << endl;
    // cout << "mxBatteryChargingStations: " << mxBatteryChargingStations << endl;
    // cout << "mxBatterySwappingStations: " << mxBatterySwappingStations << endl;

    return 0;
}

#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>
#include<string>
#include <utility>

extern std::vector<std::pair<double, double>> locations;
extern std::vector<double> demandWeights;
extern std::vector<std::pair<double,double>> batteryChargingStations;
extern std::vector<std::pair<double,double>> batterySwappingStations;
extern std::vector<double> mxBatteryLevels;
extern std::vector<double> mxCostAllowed;
extern std::vector<double> mxWeightAllowed;
extern int mxVehicles;
extern int mxCustomers;
extern int mxBatteryChargingStations;
extern int mxBatterySwappingStations;
extern double fastChargingTimePerUnitOfCharge;
extern double mediumChargingTimePerUnitOfCharge;
extern double slowChargingTimePerUnitOfCharge;
extern double batterySwappingCost;
extern double batterySwappingTime;
extern double dischargingConst;
extern double temperature; //in kelvin
extern double scalingFactor;
extern double parameter;
extern int fastTimeChargers;
extern int mediumTimeChargers;
extern int slowTimeChargers;
extern double costPerUnitChargeOfFast;
extern double costPerUnitChargeOfMedium;
extern double costPerUnitChargeOfSlow;
extern std::vector<double> speedOfVehicles;
extern std::vector<double> weightFactorForSpeed;
extern std::vector<double> weightFactorForDistance;
extern std::vector<std::string> locationsText;
extern std::vector<std::string> batteryChargingStationsText;
extern std::vector<std::string> batterySwappingStationsText;
void parseJSONFileAndFillVariables();
void readTextData();
void writeJSONToFile();
#endif
#include "variables.h"
std::vector<std::pair<double, double>> locations = {
    {23, 27}, // depo location
    {20, 15},
    {10, 25},
    {15, 10},
    {30, 20},
    {25, 5},
    {15, 30},
    {8, 18},
    {22, 28},
    {21, 20},
    {16, 13}};

std::vector<double> demandWeights = {0, 20, 12, 28, 18, 15, 25, 13, 17, 30, 10};

std::vector<double> mxBatteryLevels = {0, 2200, 1910, 2020, 1340}; // in wh

std::vector<double> mxCostAllowed = {0, 4500, 2000, 400, 1200}; // in rs

std::vector<double> mxWeightAllowed = {0, 80, 50, 70, 60}; // in kg

double fastChargingTimePerUnitOfCharge = 0.005; // in hours/wh

double mediumChargingTimePerUnitOfCharge = 0.008; // in hours/wh

double slowChargingTimePerUnitOfCharge = 0.013; // in hours/wh

double batterySwappingCost = 30; // in rs

double batterySwappingTime = 0.2; // in hours

int mxVehicles = 4;

int mxCustomers = 10;

std::vector<std::pair<double, double>> batteryChargingStations = {
    {23, 27},
    {13, 12},
    {19, 12},
    {13, 8},
    {25, 28},
    {8, 19},
    {18, 12},
    {14, 18},
    {19, 12},
    {8, 9},
    {3, 9},
    {2, 11},
    {24, 29}};

std::vector<std::pair<double, double>> batterySwappingStations = {
    {23, 27},
    {15, 11},
    {18, 7},
    {29, 13}};

double dischargingConst = 10;

double temperature = 300;

double scalingFactor = 0.03;

double parameter = 0.5;

int fastTimeChargers = 2;

int mediumTimeChargers = 2;

int slowTimeChargers = 4;

double costPerUnitChargeOfFast = 3; // in rs/wh
double costPerUnitChargeOfMedium = 1.4;
double costPerUnitChargeOfSlow = 0.9;

std::vector<double> speedOfVehicles = {0, 12, 9, 13, 17};

std::vector<double> weightFactorForSpeed = {0, 0.13, 0.17, 0.09, 0.03};

std::vector<double> weightFactorForDistance = {0, 0.13, 0.17, 0.09, 0.03};

int mxBatteryChargingStations = 12;
int mxBatterySwappingStations = 5;


#include "variables.h"
#include <bits/stdc++.h>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"

#include "rapidjson/writer.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;
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

void parseJSONFileAndFillVariables()
{
    cout << "AMAN" << endl;
    string filename = "data.json";

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Failed to open JSON file." << endl;
        return;
    }

    string jsonData((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    Document document;
    document.Parse(jsonData.c_str());

    if (document.HasParseError())
    {
        cerr << "Failed to parse JSON data." << endl;
        return;
    }

    if (!document.HasMember("inputs") || !document["inputs"].IsArray())
    {
        cerr << "Invalid JSON structure." << endl;
        return;
    }

    const Value &inputs = document["inputs"];

    for (SizeType i = 0; i < inputs.Size(); i++)
    {
        const Value &input = inputs[i];
        if (input.HasMember("latitude") && input.HasMember("longitude") &&
            input["latitude"].IsDouble() && input["longitude"].IsDouble())
        {
            double latitude = input["latitude"].GetDouble();
            double longitude = input["longitude"].GetDouble();
            locations[i].first = latitude;
            locations[i].second = longitude;
        }
        else
        {
            cerr << "Invalid input data at index " << i << endl;
        }
    }
}

void writeJSONToFile(const std::string &filename, const rapidjson::Document &document) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    rapidjson::OStreamWrapper osw(file);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    document.Accept(writer);
}

void readTextData() {
    rapidjson::Document document(rapidjson::kObjectType);

    std::ifstream infile("output.txt");

    std::string line;
    rapidjson::Value vehicles(rapidjson::kArrayType);

    while (getline(infile, line)) {
        if (line == "End") {
            continue; // Skip "End" lines
        }

        rapidjson::Value vehicleObj(rapidjson::kObjectType);
        int vehicleNumber = std::stoi(line);

        getline(infile, line); // Read next line for total cost
        double totCost = std::stod(line);

        getline(infile, line); // Read next line for total time
        double totTime = std::stod(line);

        vehicleObj.AddMember("VehicleNumber", vehicleNumber, document.GetAllocator());
        vehicleObj.AddMember("TotCost", totCost, document.GetAllocator());
        vehicleObj.AddMember("TotTime", totTime, document.GetAllocator());

        rapidjson::Value nodes(rapidjson::kArrayType);

        while (getline(infile, line) && line != "End") {
            rapidjson::Value node(rapidjson::kObjectType);
            node.AddMember("Latitude", std::stod(line), document.GetAllocator());

            getline(infile, line); // Read next line for longitude
            node.AddMember("Longitude", std::stod(line), document.GetAllocator());

            getline(infile, line); // Read next line for ChStation
            bool chStation = line == "1";
            node.AddMember("ChStation", chStation, document.GetAllocator());

            getline(infile, line); // Read next line for BatterySwapStation
            bool batterySwapStation = line == "1";
            node.AddMember("BatterySwapStation", batterySwapStation, document.GetAllocator());

            nodes.PushBack(node, document.GetAllocator());
        }

        vehicleObj.AddMember("Nodes", nodes, document.GetAllocator());
        vehicles.PushBack(vehicleObj, document.GetAllocator());
    }

    infile.close();

    document.AddMember("Data", vehicles, document.GetAllocator());

    writeJSONToFile("output.json", document);
}

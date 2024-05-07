
#include <bits/stdc++.h>
#include "rapidjson/document.h"
#include "variables.h"
#include "rapidjson/filereadstream.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;
double pi = 3.14159265358979323846;
double earthRadiusKm = 6371.0;
bool whichDistanceToUse = 0;

double toRadians(double degrees)
{
    return degrees * pi / 180.0;
}

double distance(double lat1, double lon1, double lat2, double lon2)
{

    return (double)sqrtl((lat1 - lat2) * (lat1 - lat2) * 1.00 + (lon1 - lon2) * (lon1 - lon2) * 1.00);
}

double randomDouble(double min, double max)
{
    static mt19937 gen(random_device{}());
    uniform_real_distribution<> dis(min, max);
    double result = dis(gen);

    stringstream ss;
    ss << fixed << setprecision(4) << result;
    ss >> result;
    return result;
}

int randomInt(int min, int max)
{
    static mt19937 gen(random_device{}());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void initialization()
{
    int minNumberOfCustomers = 76;
    int maxNumberOfCustomers = 80;

    int minbatteryChargingStations = 9;
    int maxbatteryChargingStations = 12;

    int minbatterySwappingStations = 7;
    int maxbatterySwappingStations = 10;

    int minNumberOfvehicles = 12;
    int maxNumberOfvehicles = 15;

    mxBatteryChargingStations = randomInt(minbatteryChargingStations, maxbatteryChargingStations);
    mxBatterySwappingStations = randomInt(minbatterySwappingStations, maxbatterySwappingStations);
    mxVehicles = randomInt(minNumberOfvehicles, maxNumberOfvehicles);
    mxCustomers = randomInt(minNumberOfCustomers, maxNumberOfCustomers);

    locations.resize(mxCustomers + 1);
    demandWeights.resize(mxCustomers + 1);
    batteryChargingStations.resize(mxBatteryChargingStations + 1);
    batterySwappingStations.resize(mxBatterySwappingStations + 1);
    mxBatteryLevels.resize(mxVehicles + 1);
    mxCostAllowed.resize(mxVehicles + 1);
    speedOfVehicles.resize(mxVehicles + 1);
    weightFactorForDistance.resize(mxVehicles + 1);
    weightFactorForSpeed.resize(mxVehicles + 1);
    mxWeightAllowed.resize(mxVehicles + 1);

    double minWeightLoadForvehicle = 90;
    double maxWeightLoadForvehicle = 120;

    double mincostAllowedForvehicle = 2000;
    double maxcostAllowedForvehicle = 9000;

    double minChargeLimit = 6500;
    double maxChargeLimit = 7000;

    double minSpeedForvehicle = 8;
    double maxSpeedForvehicle = 20;

    double minWeightFactorForSpeed = 0.01;
    double maxWeightFactorForSpeed = 0.15;

    double minWeightFactorForDistance = 0.01;
    double maxWeightFactorForDistance = 0.15;

    double minCustomerDemandWeight = 5;
    double maxCustomerDemandWeight = 12;

    double minXCoordinate = 9;
    double maxXCoordinate = 35;

    double minYCoordinate = 9;
    double maxYCoordinate = 35;

    for (int i = 1; i <= mxVehicles; i++)
    {
        mxWeightAllowed[i] = randomDouble(minWeightLoadForvehicle, maxWeightLoadForvehicle);
        mxCostAllowed[i] = randomDouble(mincostAllowedForvehicle, maxcostAllowedForvehicle);
        mxBatteryLevels[i] = randomDouble(minChargeLimit, maxChargeLimit);
        speedOfVehicles[i] = randomDouble(minSpeedForvehicle, maxSpeedForvehicle);
        weightFactorForSpeed[i] = randomDouble(minWeightFactorForSpeed, maxWeightFactorForSpeed);
        weightFactorForDistance[i] = randomDouble(minWeightFactorForDistance, maxWeightFactorForDistance);
    }

    for (int i = 1; i <= mxCustomers; i++)
    {
        demandWeights[i] = randomDouble(minCustomerDemandWeight, maxCustomerDemandWeight);
        locations[i].first = randomDouble(minXCoordinate, maxXCoordinate);
        locations[i].second = randomDouble(minYCoordinate, maxYCoordinate);
    }

    for (int i = 1; i <= mxBatteryChargingStations; i++)
    {
        batteryChargingStations[i].first = randomDouble(minXCoordinate, maxXCoordinate);
        batteryChargingStations[i].second = randomDouble(minYCoordinate, maxYCoordinate);
    }

    for (int i = 1; i <= mxBatterySwappingStations; i++)
    {
        batterySwappingStations[i].first = randomDouble(minXCoordinate, maxXCoordinate);
        batterySwappingStations[i].second = randomDouble(minYCoordinate, maxYCoordinate);
    }

    std::ifstream ifs("data.json");
    if (!ifs.is_open())
    {
        std::cerr << "Error: Unable to open data.json\n";
        return;
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string jsonStr = buffer.str();

    Document document;
    document.Parse(jsonStr.c_str());

    Value locationArray(kArrayType);
    for (int i = 0; i <= mxCustomers; ++i)
    {
        Value locationObject(kObjectType);
        locationObject.AddMember("latitude", locations[i].first, document.GetAllocator());
        locationObject.AddMember("longitude", locations[i].second, document.GetAllocator());
        locationObject.AddMember("text", Value((std::string("Location ") + std::to_string(i)).c_str(), document.GetAllocator()).Move(), document.GetAllocator());
        locationObject.AddMember("demandWeight", demandWeights[i], document.GetAllocator());
        locationArray.PushBack(locationObject, document.GetAllocator());
    }
    document["location"] = locationArray;

    Value chargingStationArray(kArrayType);
    for (int i = 0; i < mxBatteryChargingStations; ++i)
    {
        Value chargingStationObject(kObjectType);
        chargingStationObject.AddMember("latitude", batteryChargingStations[i].first, document.GetAllocator());   // Replace with actual latitude
        chargingStationObject.AddMember("longitude", batteryChargingStations[i].second, document.GetAllocator()); // Replace with actual longitude
        chargingStationObject.AddMember("text", Value((std::string("Charging Station ") + std::to_string(i)).c_str(), document.GetAllocator()).Move(), document.GetAllocator());
        chargingStationArray.PushBack(chargingStationObject, document.GetAllocator());
    }

    document["batterychargingstation"] = chargingStationArray;

    Value swappingStationArray(kArrayType);
    for (int i = 0; i < mxBatterySwappingStations; ++i)
    {
        Value swappingStationObject(kObjectType);
        swappingStationObject.AddMember("latitude", batterySwappingStations[i].first, document.GetAllocator());   // Replace with actual latitude
        swappingStationObject.AddMember("longitude", batterySwappingStations[i].second, document.GetAllocator()); // Replace with actual longitude
        swappingStationObject.AddMember("text", Value((std::string("Swapping Station ") + std::to_string(i)).c_str(), document.GetAllocator()).Move(), document.GetAllocator());
        swappingStationArray.PushBack(swappingStationObject, document.GetAllocator());
    }
    document["batteryswappingstation"] = swappingStationArray;

    Value vehicleArray(kArrayType);
    for (int i = 1; i <= mxVehicles; ++i)
    {
        Value vehicleObject(kObjectType);
        vehicleObject.AddMember("mxBatteryLevels", mxBatteryLevels[i], document.GetAllocator());
        vehicleObject.AddMember("mxCostAllowed", mxCostAllowed[i], document.GetAllocator());
        vehicleObject.AddMember("mxWeightAllowed", mxWeightAllowed[i], document.GetAllocator());
        vehicleObject.AddMember("speedOfVehicles", speedOfVehicles[i], document.GetAllocator());
        vehicleObject.AddMember("weightFactorForSpeed", weightFactorForSpeed[i], document.GetAllocator());
        vehicleObject.AddMember("weightFactorForDistance", weightFactorForDistance[i], document.GetAllocator());
        vehicleArray.PushBack(vehicleObject, document.GetAllocator());
    }
    document["vehicle"] = vehicleArray;

    document["mxVehicles"].SetInt(mxVehicles);
    document["mxCustomers"].SetInt(mxCustomers);
    document["mxBatteryChargingStations"].SetInt(mxBatteryChargingStations);
    document["mxBatterySwappingStations"].SetInt(mxBatterySwappingStations);

    StringBuffer buffer2;
    Writer<StringBuffer> writer(buffer2);
    document.Accept(writer);
    std::string jsonString = buffer2.GetString();

    std::ofstream ofs("data.json");
    if (!ofs.is_open())
    {
        std::cerr << "Error: Unable to open data.json for writing\n";
        return;
    }

    ofs << jsonString;
    ofs.close();
}
void randomAllocation(vector<pair<double, vector<int>>> &filledWeights)
{
    mt19937 gen(static_cast<unsigned int>(time(nullptr)));

    bool valid = 0;
    while (valid == 0)
    {

        for (auto &i : filledWeights)
        {
            i.first = 0;
            i.second.clear();
        }
        uniform_int_distribution<> dis(1, mxVehicles);

        for (int obj = 1; obj <= mxCustomers; ++obj)
        {

            int bucketIndex = dis(gen);

            filledWeights[bucketIndex].second.push_back(obj); // Adjust index to start from 1
            filledWeights[bucketIndex].first += (demandWeights[obj]);
        }
        valid = 1;
        for (int i = 1; i <= mxVehicles; i++)
        {
            if (filledWeights[i].first > mxWeightAllowed[i])
            {
                valid = 0;
                break;
            }
        }
    }
}
void heuristicInitialization(vector<pair<double, vector<int>>> &filledWeights)
{

    vector<pair<double, int>> demand;
    int cnt = 1;

    for (int i = 1; i < demandWeights.size(); i++)
    {
        demand.push_back({demandWeights[i], i});
        cnt++;
    }

    sort(demand.begin(), demand.end(), greater<>());

    priority_queue<pair<double, int>> allotWeights;
    for (int i = 1; i < mxWeightAllowed.size(); i++)
        allotWeights.push({mxWeightAllowed[i], i});

    for (auto &i : filledWeights)
        i.first = 0;

    int counter = 0;
    while (1)
    {
        if (counter == mxCustomers)
            break;
        auto top = allotWeights.top();
        if (top.first < demand[counter].first) // If maximum possible vehicle weight can't also fulfill the requirements.
        {
            cout << "Solution not possible... Exiting";
            exit(0);
        }
        else
        {
            int left_weight = top.first - demand[counter].first;
            allotWeights.pop();

            allotWeights.push({left_weight, top.second});

            filledWeights[top.second].first += demand[counter].first;

            filledWeights[top.second].second.push_back(demand[counter].second);

            counter++;
        }
    }
}
void fillVariables()
{
    FILE *file = fopen("data.json", "rb");
    if (!file)
    {
        cerr << "Failed to open JSON file." << endl;
        return;
    }

    char readBuffer[65536];
    FileReadStream inputStream(file, readBuffer, sizeof(readBuffer));
    Document jsonData;
    jsonData.ParseStream(inputStream);
    fclose(file);

    for (auto &loc : jsonData["location"].GetArray())
    {
        locations.push_back({loc["latitude"].GetDouble(), loc["longitude"].GetDouble()});
        demandWeights.push_back(loc["demandWeight"].GetDouble());
    }

    batteryChargingStations.push_back({0, 0});
    batterySwappingStations.push_back({0, 0});
    for (auto &loc : jsonData["batterychargingstation"].GetArray())
    {
        batteryChargingStations.push_back({loc["latitude"].GetDouble(), loc["longitude"].GetDouble()});
    }

    for (auto &loc : jsonData["batteryswappingstation"].GetArray())
    {
        batterySwappingStations.push_back({loc["latitude"].GetDouble(), loc["longitude"].GetDouble()});
    }

    mxBatteryLevels.push_back(0);
    mxCostAllowed.push_back(0);
    mxWeightAllowed.push_back(0);

    for (auto &vehicle : jsonData["vehicle"].GetArray())
    {
        mxBatteryLevels.push_back(vehicle["mxBatteryLevels"].GetDouble());
        mxCostAllowed.push_back(vehicle["mxCostAllowed"].GetDouble());
        mxWeightAllowed.push_back(vehicle["mxWeightAllowed"].GetDouble());
    }

    fastChargingTimePerUnitOfCharge = jsonData["fastChargingTimePerUnitOfCharge"].GetDouble();
    mediumChargingTimePerUnitOfCharge = jsonData["mediumChargingTimePerUnitOfCharge"].GetDouble();
    slowChargingTimePerUnitOfCharge = jsonData["slowChargingTimePerUnitOfCharge"].GetDouble();
    batterySwappingCost = jsonData["batterySwappingCost"].GetDouble();
    batterySwappingTime = jsonData["batterySwappingTime"].GetDouble();
    batteriesAvailable = jsonData["batteriesAvailable"].GetInt();
    mxVehicles = jsonData["mxVehicles"].GetInt();
    mxCustomers = jsonData["mxCustomers"].GetInt();
    dischargingConst = jsonData["dischargingConst"].GetDouble();
    temperature = jsonData["temperature"].GetDouble();
    scalingFactor = jsonData["scalingFactor"].GetDouble();
    parameter = jsonData["parameter"].GetDouble();
    fastTimeChargers = jsonData["fastTimeChargers"].GetInt();
    mediumTimeChargers = jsonData["mediumTimeChargers"].GetInt();
    slowTimeChargers = jsonData["slowTimeChargers"].GetInt();
    costPerUnitChargeOfFast = jsonData["costPerUnitChargeOfFast"].GetDouble();
    costPerUnitChargeOfMedium = jsonData["costPerUnitChargeOfMedium"].GetDouble();
    costPerUnitChargeOfSlow = jsonData["costPerUnitChargeOfSlow"].GetDouble();
    mxBatteryChargingStations = jsonData["mxBatteryChargingStations"].GetInt();
    mxBatterySwappingStations = jsonData["mxBatterySwappingStations"].GetInt();
}
signed main()
{

    initialization();

    vector<pair<double, vector<int>>> filledWeights(mxVehicles + 1);
    
    // randomAllocation(filledWeights);
    heuristicInitialization(filledWeights);

    /************* Vehicle Assignment Part *************/
    int counter = 0;

    string baseCommand1 = "tsp vehicle_";
    // string baseCommand2 = "tspNew vehicle_";


    vector<vector<int>> vehicleCustomerMapping(mxVehicles + 1, vector<int>(mxCustomers + 1, 0));

    for (auto i : filledWeights)
    {

        if (counter == 0)
        {
            counter++;
            continue;
        }
        string fileName = "vehicle_" + to_string(counter) + ".txt";
        ofstream outfile(fileName);
        if (!outfile.is_open())
        {
            cerr << "Error: Unable to open " << fileName << " for writing\n";
            return 1;
        }

        int node_num = 1;
        string command = baseCommand1 + to_string(counter) + ".txt";
        // string command = baseCommand2 + to_string(counter) + ".txt";

        outfile << fixed << setprecision(0) << 0 << " "
                << fixed << setprecision(0) << locations[0].first * 10000 << " "
                << fixed << setprecision(0) << locations[0].second * 10000 << "\n";
        for (auto node : i.second)
        {
            outfile << fixed << setprecision(0) << 0 << " "
                    << fixed << setprecision(0) << locations[node].first * 10000 << " "
                    << fixed << setprecision(0) << locations[node].second * 10000 << "\n";
            vehicleCustomerMapping[counter][node_num] = node;

            node_num++;
        }

        outfile.close();

        system(command.c_str());
        counter++;
    }

    /************* Creating graph from the traversors  *************/

    vector<int> adjacencyMatrix[mxVehicles + 1][mxCustomers + 1];

    vector<int> vehicle_sizes;
    vehicle_sizes.push_back(0);
    for (int i = 1; i <= mxVehicles; i++)
    {
        string fileName = "vehicle_" + to_string(i) + ".txt.tour";

        ifstream file(fileName);
        if (!file.is_open())
        {

            cerr << "Error opening file" << endl;
            return 1;
        }
        string line;
        vector<int> temp_nodes;
        int temp = 0;
        while (getline(file, line))
        {

            if (temp == 0)
            {
                temp++;
                continue;
            }
            int node = stoi(line);

            temp_nodes.push_back(vehicleCustomerMapping[i][node]);
        }
        file.close();
        vehicle_sizes.push_back(temp_nodes.size());
        for (auto meow : temp_nodes)
            double total_weight = filledWeights[i].first;

        for (int j = 0; j < temp_nodes.size() - 1; j++)
        {
            adjacencyMatrix[i][temp_nodes[j]].push_back(temp_nodes[j + 1]);
            adjacencyMatrix[i][temp_nodes[j + 1]].push_back(temp_nodes[j]);
        }
        adjacencyMatrix[i][temp_nodes[0]].push_back(temp_nodes[temp_nodes.size() - 1]);
        adjacencyMatrix[i][temp_nodes[temp_nodes.size() - 1]].push_back(temp_nodes[0]);
    }

    /************* Graph Done *************/

    /************* Satisfying each vehicle's charging constraint by visiting multiple depot's *************/

    vector<vector<vector<int>>> chargeRequirement(mxVehicles + 1, vector<vector<int>>(mxBatteryChargingStations + 1));
    vector<vector<vector<int>>> batterySwappingRequirement(mxVehicles + 1, vector<vector<int>>(mxBatterySwappingStations + 1));

    double dischargingAdditive = dischargingConst * parameter + temperature * scalingFactor;

    vector<int> nodeTraversor[mxVehicles + 1];
    vector<double> totalTimes(mxVehicles + 1);

    for (int i = 1; i <= mxVehicles; i++)
    {
        double weight = filledWeights[i].first;

        int depo = 0;
        nodeTraversor[i].push_back(depo);

        int end_node = depo;

        double batteryLevel = mxBatteryLevels[i];

        double dist_1 = distance(locations[end_node].first, locations[end_node].second, locations[adjacencyMatrix[i][end_node][0]].first, locations[adjacencyMatrix[i][end_node][0]].second);
        double dist_2 = distance(locations[end_node].first, locations[end_node].second, locations[adjacencyMatrix[i][end_node][1]].first, locations[adjacencyMatrix[i][end_node][1]].second);
        int node_selected = -1;
        double distanceValue;

        if (dist_1 < dist_2)
        {
            node_selected = 0;
            distanceValue = dist_1;
        }
        else
        {
            node_selected = 1;
            distanceValue = dist_2;
        }

        double ch_required = 0;

        bool visited[mxCustomers + 1] = {0};
        int counter = 0;
        end_node = adjacencyMatrix[i][end_node][node_selected];
        double distanceBetweenNodes = distance(locations[depo].first, locations[depo].second, locations[end_node].first, locations[end_node].second);
        int temp = depo;
        ch_required = (dischargingAdditive + weight * 1.0 / mxWeightAllowed[i]) * (distanceValue * (1 + weightFactorForDistance[i] * weight));

        int previous_node = depo;

        while (1)
        {
            double residualBatteryLevel = batteryLevel - 150;

            if (end_node == depo)
                residualBatteryLevel = batteryLevel;
            while (ch_required > residualBatteryLevel)
            {

                if (residualBatteryLevel < 100)
                    residualBatteryLevel += 150;

                if (end_node == depo and residualBatteryLevel > ch_required)
                    break;

                double mnBatteryCharging = 1e15;
                int chStation = -1;
                double toChargingStationCharge = -1;

                for (int j = 1; j <= mxBatteryChargingStations; j++)
                {
                    double distBatteryCharging;
                    if (counter == 0)
                        distBatteryCharging = distance(locations[temp].first, locations[temp].second, batteryChargingStations[j].first, batteryChargingStations[j].second);
                    else
                        distBatteryCharging = distance(batteryChargingStations[(nodeTraversor[i].back() / (1e7))].first, batteryChargingStations[(nodeTraversor[i].back() / (1e7))].second, batteryChargingStations[j].first, batteryChargingStations[j].second);

                    double distanceBetweenCharging = distance(locations[end_node].first, locations[end_node].second, batteryChargingStations[j].first, batteryChargingStations[j].second);

                    double batteryChRequiredForPreviousToNext = (dischargingAdditive + weight * 1.0 / mxWeightAllowed[i]) * (distBatteryCharging * (1 + weightFactorForDistance[i] * weight));

                    if (distanceBetweenCharging < distanceBetweenNodes && batteryChRequiredForPreviousToNext < residualBatteryLevel)
                    {

                        mnBatteryCharging = min(mnBatteryCharging, distBatteryCharging);
                        chStation = j;
                        toChargingStationCharge = batteryChRequiredForPreviousToNext;
                    }
                }

                double mnBatterySwapping = 1e15;
                int batterySwappingStation = -1;
                double toBatterySwappingStationCharge = -1;

                for (int j = 1; j <= mxBatterySwappingStations; j++)
                {
                    double distBatterySwapping;
                    if (counter == 0)
                        distBatterySwapping = distance(locations[temp].first, locations[temp].second, batterySwappingStations[j].first, batterySwappingStations[j].second);
                    else
                        distBatterySwapping = distance(batterySwappingStations[(nodeTraversor[i].back() / (1e7))].first, batterySwappingStations[(nodeTraversor[i].back() / (1e7))].second, batterySwappingStations[j].first, batterySwappingStations[j].second);

                    double distance_between_battery_swapping = distance(locations[end_node].first, locations[end_node].second, batterySwappingStations[j].first, batterySwappingStations[j].second);

                    double batteryChRequiredForPreviousToNext = (dischargingAdditive + weight * 1.0 / mxWeightAllowed[i]) * (distBatterySwapping * (1 + weightFactorForDistance[i] * weight));

                    if (distance_between_battery_swapping < distanceBetweenNodes && batteryChRequiredForPreviousToNext < residualBatteryLevel)
                    {

                        mnBatterySwapping = min(mnBatterySwapping, distBatterySwapping);
                        batterySwappingStation = j;
                        toBatterySwappingStationCharge = batteryChRequiredForPreviousToNext;
                    }
                }

                if (chStation == -1 && batterySwappingStation == -1)
                {
                    cout << "Charging/Battery Swapping station not possible: Exiting";
                    return 0;
                }
                else if (batterySwappingStation != -1)
                {
                    distanceBetweenNodes = distance(batterySwappingStations[batterySwappingStation].first, batterySwappingStations[batterySwappingStation].second, locations[end_node].first, locations[end_node].second);
                    if (counter == 0)
                        distanceValue = distance(locations[temp].first, locations[temp].second, batteryChargingStations[batterySwappingStation].first, batterySwappingStations[batterySwappingStation].second);
                    else
                        distanceValue = distance(batterySwappingStations[(nodeTraversor[i].back() / (1e7))].first, batterySwappingStations[(nodeTraversor[i].back() / (1e7))].second, batterySwappingStations[batterySwappingStation].first, batterySwappingStations[batterySwappingStation].second);

                    batterySwappingRequirement[i][batterySwappingStation].push_back(mxBatteryLevels[i] - toBatterySwappingStationCharge);
                    nodeTraversor[i].push_back(-1 * batterySwappingStation * 1e7);
                }
                else
                {
                    distanceBetweenNodes = distance(batteryChargingStations[chStation].first, batteryChargingStations[chStation].second, locations[end_node].first, locations[end_node].second);
                    if (counter == 0)
                        distanceValue = distance(locations[temp].first, locations[temp].second, batteryChargingStations[chStation].first, batteryChargingStations[chStation].second);
                    else
                        distanceValue = distance(batteryChargingStations[(nodeTraversor[i].back() / (1e7))].first, batteryChargingStations[(nodeTraversor[i].back() / (1e7))].second, batteryChargingStations[chStation].first, batteryChargingStations[chStation].second);

                    chargeRequirement[i][chStation].push_back(mxBatteryLevels[i] - toChargingStationCharge);
                    nodeTraversor[i].push_back(chStation * 1e7);
                }

                totalTimes[i] += (distanceValue / ((1 + weightFactorForSpeed[i] * weight) * speedOfVehicles[i]));
                ch_required = (dischargingAdditive + weight * 1.0 / mxWeightAllowed[i]) * (distanceBetweenNodes * (1 + weightFactorForDistance[i] * weight));
                batteryLevel = mxBatteryLevels[i];
                distanceValue = distanceBetweenNodes;
                residualBatteryLevel = batteryLevel - 150;
            }

            totalTimes[i] += (distanceValue / ((1 + weightFactorForSpeed[i] * weight) * speedOfVehicles[i]));

            batteryLevel -= ch_required;
            nodeTraversor[i].push_back(end_node);
            if (end_node == depo)
                break;

            weight -= demandWeights[end_node];
            temp = end_node;
            if (adjacencyMatrix[i][end_node][0] == previous_node)
                end_node = adjacencyMatrix[i][end_node][1];
            else
                end_node = adjacencyMatrix[i][end_node][0];

            distanceBetweenNodes = distance(locations[temp].first, locations[temp].second, locations[end_node].first, locations[end_node].second);

            ch_required = (dischargingAdditive + weight * 1.0 / mxWeightAllowed[i]) * (distanceBetweenNodes * (1 + weightFactorForDistance[i] * weight));
            distanceValue = distanceBetweenNodes;
            counter++;

            previous_node = temp;
        }
    }
    for (auto &i : chargeRequirement)
    {
        for (auto &j : i)
        {
            sort(j.begin(), j.end(), greater<>());
        }
    }

    /************* Charging completed, now ensuring that all the vehicles remain in their cost *************/

    vector<double> chargingTImes(mxVehicles + 1);
    vector<double> swappingTimes(mxVehicles + 1);

    vector<double> costOfCharging(mxVehicles + 1);
    vector<int> batteriesUsed(mxBatterySwappingStations + 1, 0);
    vector<int> fastChargersUsed(mxBatteryChargingStations + 1, 0);
    vector<int> mediumChargersUsed(mxBatteryChargingStations + 1, 0);
    vector<int> slowChargersUsed(mxBatteryChargingStations + 1, 0);

    for (int i = 1; i <= mxVehicles; i++)
    {
        for (auto stations : chargeRequirement[i])
        {
            for (auto charge : stations)
            {
                costOfCharging[i] += (charge * costPerUnitChargeOfFast);
                chargingTImes[i] += (charge * fastChargingTimePerUnitOfCharge);
            }
        }
        for (auto stations : batterySwappingRequirement[i])
        {
            for (auto charge : stations)
            {
                swappingTimes[i] += (batterySwappingTime);
                batteriesUsed[i]++;
                costOfCharging[i] += (batterySwappingCost);
                fastChargersUsed[i]++;
            }
        }
    }

    for (int i = 1; i <= mxVehicles; i++)
    {
        priority_queue<pair<double, pair<int, int>>> chargeStorage;
        for (int j = 1; j <= mxBatteryChargingStations; j++)
        {
            for (int k = 0; k < chargeRequirement[i][j].size(); k++)
            {
                chargeStorage.push({chargeRequirement[i][j][k], {j, k}});
            }
        }

        bool mediumOrSlow = 0; // 0 denotes for fast to medium and 1 dentoes from medium to slow

        map<pair<int, int>, bool> mappingForStation[mxVehicles + 1];

        while (costOfCharging[i] > mxCostAllowed[i] or fastChargersUsed[i] > fastTimeChargers)
        {

            double extra = (costOfCharging[i] - mxCostAllowed[i]);

            if (chargeStorage.size() == 0)
            {
                if (costOfCharging[i] > mxCostAllowed[i])
                {
                    cout << "Solution not possible with this amount for vehicle... Exiting";
                    return 0;
                }
                break;
            }
            auto top = chargeStorage.top();
            mediumOrSlow = mappingForStation[i][top.second];

            double value = top.first * (mediumOrSlow == 0 ? costPerUnitChargeOfMedium : costPerUnitChargeOfSlow);
            double cost_saved = (top.first) * ((mediumOrSlow == 0 ? costPerUnitChargeOfFast : costPerUnitChargeOfMedium) - (mediumOrSlow == 0 ? costPerUnitChargeOfMedium : costPerUnitChargeOfSlow));

            chargingTImes[i] += (top.first) * ((mediumOrSlow == 0 ? mediumChargingTimePerUnitOfCharge : slowChargingTimePerUnitOfCharge) - (mediumOrSlow == 0 ? fastChargingTimePerUnitOfCharge : mediumChargingTimePerUnitOfCharge));

            chargeStorage.pop();
            if (mappingForStation[i][top.second] == 0)
                chargeStorage.push({top.first - cost_saved, top.second});

            costOfCharging[i] -= cost_saved;

            mappingForStation[i][top.second] = 1;
            if (mappingForStation[i][top.second])

                fastChargersUsed[i]--;
        }
    }

    /************* Cost Optimisation Also Done ****************/
    double final_ans = 0.0;
    for (int i = 1; i <= mxVehicles; i++)
    {
        totalTimes[i] += (chargingTImes[i] + swappingTimes[i]);
        final_ans = max(final_ans, totalTimes[i]);
    }

    /************* Battery Swapping Not Done *************/

    ofstream outputFile("output.txt");

    if (!outputFile.is_open())
    {
        cerr << "Failed to open the file for writing." << endl;
        return 1;
    }

    for (int i = 1; i <= mxVehicles; i++)
    {
        outputFile << i << endl;
        outputFile << costOfCharging[i] << endl;
        outputFile << totalTimes[i] << endl;
        for (int j = 0; j < nodeTraversor[i].size(); j++)
        {
            int x = nodeTraversor[i][j];
            int y = x / 1e7;
            if (y < 0)
            {
                outputFile << batterySwappingStations[-y].first << endl;
                outputFile << batterySwappingStations[-y].second << endl;
                outputFile << batterySwappingStationsText[-y] << endl;
                outputFile << 0 << endl;
                outputFile << 1 << endl;
                cout << "Bat-swap(" << -1 * y << ") ->";
            }
            else if (y != 0)
            {
                outputFile << batteryChargingStations[y].first << endl;
                outputFile << batteryChargingStations[y].second << endl;
                outputFile << batteryChargingStationsText[y] << endl;
                outputFile << 1 << endl;
                outputFile << 0 << endl;
                cout << " Ch-st(" << y << ") -> ";
            }
            else
            {
                outputFile << locations[x].first << endl;
                outputFile << locations[x].second << endl;

                outputFile << locationsText[x] << endl;
                outputFile << 0 << endl;
                outputFile << 0 << endl;
                cout << x << " -> ";
            }
        }
        outputFile << "End" << endl;
        cout << "Total cost incurred: " << costOfCharging[i] << endl;
        cout << "Total time taken: " << totalTimes[i] << endl;
        cout << endl;
    }
    outputFile.close();
    readTextData();
    cout << "FINAL ANSWER: MAXIMUM TOTAL TIME: " << final_ans << endl
         << endl
         << endl;
    return 0;
}

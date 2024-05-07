// Author : Aman Agrawal(ILP completed in parts(present in the github url presented), heuristic here)
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

// Convert degrees to radians
double toRadians(double degrees)
{
    return degrees * pi / 180.0;
}

// Calculate the Haversine distance between two points given their latitude and longitude in degrees
double distance(double lat1, double lon1, double lat2, double lon2)
{
    double dLat = toRadians(lat2 - lat1);
    double dLon = toRadians(lon2 - lon1);
    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               sin(dLon / 2) * sin(dLon / 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));


    return (earthRadiusKm*c);

}

double randomDouble(double min, double max)
{
    // Use the current time as a seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(min, max);
    double result = dis(gen);

    std::stringstream ss;
    ss << std::fixed << std::setprecision(4) << result;
    ss >> result;
    return result;
}

int randomInt(int min, int max)
{
    // Use the current time as a seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void initialization()
{

    int minNumberOfCustomers = 10;
    int maxNumberOfCustomers = 40;

    int minbatteryChargingStations = 10;
    int maxbatteryChargingStations = 25;

    int minbatterySwappingStations = 5;
    int maxbatterySwappingStations = 15;

    int minNumberOfvehicles = 4;
    int maxNumberOfvehicles = 7;

    mxBatteryChargingStations = randomInt(minbatteryChargingStations, maxbatteryChargingStations);
    mxBatterySwappingStations = randomInt(minbatterySwappingStations, maxbatterySwappingStations);
    mxVehicles = randomInt(minNumberOfvehicles, maxNumberOfvehicles);

    mxCustomers = 3;

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

    double minWeightLoadForvehicle = 50;
    double maxWeightLoadForvehicle = 90;

    // double max allowed vehicle cost
    double mincostAllowedForvehicle = 2000;
    double maxcostAllowedForvehicle = 4500;

    double minChargeLimit = 1500;
    double maxChargeLimit = 2500;

    double minSpeedForvehicle = 8;
    double maxSpeedForvehicle = 20;

    double minWeightFactorForSpeed = 0.01;
    double maxWeightFactorForSpeed = 0.15;

    double minWeightFactorForDistance = 0.01;
    double maxWeightFactorForDistance = 0.15;

    double minCustomerDemandWeight = 13;
    double maxCustomerDemandWeight = 29;

    double minXCoordinate = 10;
    double maxXCoordinate = 30;

    double minYCoordinate = 10;
    double maxYCoordinate = 30;

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

    double minFastChargerCostPerUnitOfCharge = 2.5;
    double maxFastCHargerCostPerUnitOfCharge = 3.8;

    double minSlowChargerCostPerUnitOfCharge = 0.8;
    double maxSlowChargerCostPerUnitOfCharge = 1.1;

    double minMediumChargerCostPerUnitOfCharge = 1.4;
    double maxMediumChargerCostPerUnitOfCharge = 1.9;

    double minBatterySwappingCost = 28;
    double maxBatterySwappingCost = 45;

    costPerUnitChargeOfMedium = randomDouble(minMediumChargerCostPerUnitOfCharge, maxMediumChargerCostPerUnitOfCharge);
    costPerUnitChargeOfFast = randomDouble(minFastChargerCostPerUnitOfCharge, maxFastCHargerCostPerUnitOfCharge);
    costPerUnitChargeOfSlow = randomDouble(minSlowChargerCostPerUnitOfCharge, maxSlowChargerCostPerUnitOfCharge);

    batterySwappingCost = randomDouble(minBatterySwappingCost, maxBatterySwappingCost);

    double minFastChargingRate = 0.004;
    double maxFastChargingRate = 0.007;

    double minMediumChargingRate = 0.009;
    double maxMediumChargingRate = 0.013;

    double minSlowChargingRate = 0.015;
    double maxSlowChargingRate = 0.020;

    fastChargingTimePerUnitOfCharge = randomDouble(minFastChargingRate, maxFastChargingRate);

    mediumChargingTimePerUnitOfCharge = randomDouble(minMediumChargingRate, maxMediumChargingRate);

    slowChargingTimePerUnitOfCharge = randomDouble(minSlowChargingRate, maxSlowChargingRate);

    double dischargingConst = 10;

    double temperature = 300;

    double scalingFactor = 0.03;

    double parameter = 0.5;

    int minNumberOfFastChargers = 1;
    int maxNumberOfFastChargers = 3;

    int minNumberOfMediumChargers = 1;
    int maxNumberOfMediumChargers = 3;

    int minNumberOfSlowChargers = 1;
    int maxNumberOfSlowChargers = 3;

    fastTimeChargers = randomInt(minNumberOfFastChargers, maxNumberOfFastChargers);

    mediumTimeChargers = randomInt(minNumberOfMediumChargers, maxNumberOfMediumChargers);

    slowTimeChargers = randomInt(minNumberOfSlowChargers, maxNumberOfSlowChargers);

    double minTemperature = 260;
    double maxTemperature = 330;

    temperature = randomDouble(minTemperature, maxTemperature);

    double minScalingFactor = 0.02;
    double maxScalingFactor = 0.05;

    scalingFactor = randomDouble(minScalingFactor, maxScalingFactor);

    double minParameterValue = 0.3;
    double maxParameterValue = 0.5;

    parameter = randomDouble(minScalingFactor, maxScalingFactor);


}
std::vector<std::pair<double, std::vector<int>>> filledWeights(mxVehicles + 1);
void randomAllocation()
{
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize filledWeights

    bool valid = 0;
    while (valid == 0)
    {

        for (auto &i : filledWeights)
        {
            i.first = 0;
            i.second.clear();
        }
        std::uniform_int_distribution<> dis(1, mxVehicles);
        // Distribute objects randomly into filledWeights
        for (int obj = 1; obj <= mxCustomers; ++obj)
        {
            // Generate random bucket index

            int bucketIndex = dis(gen);

            // Assign object to the bucket
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
void heuristicInitialization()
{
    // Weight assigning
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
signed main()
{
    parseJSONFileAndFillVariables();

    filledWeights.resize(mxVehicles+1);
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

     locationsText.resize(mxCustomers+1);
     batteryChargingStationsText.resize(mxBatteryChargingStations+1);
     batterySwappingStationsText.resize(mxBatterySwappingStations+1);





    // initialization();
    // Vehicle Assignment part.
    /************* Vehicle Assignment Part *************/
    // randomAllocation();
    heuristicInitialization();

    for (int i = 1; i <= mxVehicles; i++)
    {
        cout << " FILLED " << filledWeights[i].first << " MAX_WEIGHT " << mxWeightAllowed[i] << endl;
    }
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
            std::cerr << "Error: Unable to open " << fileName << " for writing\n";
            return 1;
        }

        int node_num = 1;
        string command = baseCommand1 + to_string(counter) + ".txt";

        outfile << 0 << " " << locations[0].first * 10000 << " " << locations[0].second * 10000 << "\n";

        for (auto node : i.second)
        {
            outfile << node_num << " " << locations[node].first * 10000 << " " << locations[node].second * 10000 << "\n";

            vehicleCustomerMapping[counter][node_num] = node;

            node_num++;
        }

        outfile.close();

        system(command.c_str());
        counter++;
    }

    // Battery charge specifying
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

            std::cerr << "Error opening file" << std::endl;
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

    // The lesser distance that I cover in the initial phase where I am having lesser weight, it should be better.
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
        cout << "Charge required: " << ch_required << "Vehicle required " << i << endl;
        cout << mxBatteryLevels[i] << endl;

        while (1)
        {
            double residualBatteryLevel = batteryLevel - 150;

            if (end_node == depo)
                residualBatteryLevel = batteryLevel;
            while (ch_required > residualBatteryLevel)
            {

                if (residualBatteryLevel < 100)
                    residualBatteryLevel += 150;
                // introduce charging station
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
    cout << "Mxvehicles" << mxVehicles << endl;
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
                costOfCharging[i] += (batterySwappingCost);
            }
        }
    }
    cout << "Mxvehicles" << mxVehicles << endl;
    // Balancing cost
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
        // 0 means from fast to medium and 1 means from medium to slow if for same charging station
        while (costOfCharging[i] > mxCostAllowed[i])
        {
            double extra = (costOfCharging[i] - mxCostAllowed[i]);

            if (chargeStorage.size() == 0)
            {
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
        }
    }

    /************* Cost Optimisation Also Done ****************/
    cout << "Mxvehicles" << mxVehicles << endl;
    double final_ans = 0.0;
    for (int i = 1; i <= mxVehicles; i++)
    {
        totalTimes[i] += (chargingTImes[i] + swappingTimes[i]);
        final_ans = max(final_ans, totalTimes[i]);



    }


    /************* Battery Swapping Not Done *************/
    cout << "Mxvehicles" << mxVehicles << endl;

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

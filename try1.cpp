// Author : Aman Agrawal(ILP completed in parts(present in the github url presented), heuristic here)
#include <bits/stdc++.h>
#include "variables.h"
using namespace std;

double distance(double x1, double y1, double x2, double y2)
{
    return (double)sqrtl((x1 - x2) * (x1 - x2) * 1.00 + (y1 - y2) * (y1 - y2) * 1.00);
}
double randomDouble(double min, double max)
{
    // Use the current time as a seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
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

    // Resizing
}

signed main()
{
    // initialization();
    // Vehicle Assignment part.
    /************* Vehicle Assignment Part *************/

    // Weight assigning
    vector<pair<double, int>> demand;
    int cnt = 1;

    for (int i = 1; i < demandWeights.size(); i++)
    {
        demand.push_back({demandWeights[i], i});
        cnt++;
    }

    sort(demand.begin(), demand.end(), greater<>());

    priority_queue<pair<double, int>> allot_weights;
    for (int i = 1; i < mxWeightAllowed.size(); i++)
        allot_weights.push({mxWeightAllowed[i], i});

    vector<pair<double, vector<int>>> filled_weights(mxVehicles + 1);

    for (auto &i : filled_weights)
        i.first = 0;

    int counter = 0;
    while (1)
    {

        if (counter == mxCustomers)
            break;
        auto top = allot_weights.top();

        if (top.first < demand[counter].first) // If maximum possible vehicle weight can't also fulfill the requirements.
        {
            cout << "Solution not possible... Exiting";
            return 0;
        }
        else
        {
            int left_weight = top.first - demand[counter].first;
            allot_weights.pop();

            allot_weights.push({left_weight, top.second});

            filled_weights[top.second].first += demand[counter].first;

            filled_weights[top.second].second.push_back(demand[counter].second);

            counter++;
        }
    }

    counter = 0;

    string baseCommand = "tsp vehicle_";

    vector<vector<int>> vehicleCustomerMapping(mxVehicles + 1, vector<int>(mxCustomers + 1, 0));
    for (auto i : filled_weights)
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
        string command = baseCommand + to_string(counter) + ".txt";

        outfile << 0 << " " << locations[0].first << " " << locations[0].second << "\n";

        for (auto node : i.second)
        {
            outfile << node_num << " " << locations[node].first << " " << locations[node].second << "\n";

            vehicleCustomerMapping[counter][node_num] = node;

            node_num++;
        }

        outfile.close();

        system(command.c_str());
        counter++;
    }

    // Battery charge specifying
    /************* Creating graph from the traversors  *************/

    vector<int> adjacency_matrix[mxVehicles + 1][mxCustomers + 1];

    vector<int> vehicle_sizes;
    vehicle_sizes.push_back(0);
    for (int i = 1; i < mxBatteryLevels.size(); i++)
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
            double total_weight = filled_weights[i].first;

        for (int j = 0; j < temp_nodes.size() - 1; j++)
        {
            adjacency_matrix[i][temp_nodes[j]].push_back(temp_nodes[j + 1]);
            adjacency_matrix[i][temp_nodes[j + 1]].push_back(temp_nodes[j]);
        }
        adjacency_matrix[i][temp_nodes[0]].push_back(temp_nodes[temp_nodes.size() - 1]);
        adjacency_matrix[i][temp_nodes[temp_nodes.size() - 1]].push_back(temp_nodes[0]);

        for (int j = 0; j <= mxCustomers; j++)
        {

            if (adjacency_matrix[i][j].size() != 0)
            {
            }
        }
    }

    /************* Graph Done *************/

    /************* Satisfying each vehicle's charging constraint by visiting multiple depot's *************/

    vector<vector<vector<int>>> charge_requirement(mxVehicles + 1, vector<vector<int>>(mxBatteryChargingStations + 1));
    double discharging_additive = dischargingConst * parameter + temperature * scalingFactor;

    // The lesser distance that I cover in the initial phase where I am having lesser weight, it should be better.
    vector<int> node_traversor[mxVehicles + 1];
    vector<double> total_times(mxVehicles + 1);

    for (int i = 1; i <= mxVehicles; i++)
    {
        double weight = filled_weights[i].first;

        int depo = 0;
        node_traversor[i].push_back(depo);

        int end_node = depo;

        double battery_level = mxBatteryLevels[i];
        // node_traversor[i].push_back(end_node);

        double dist_1 = distance(locations[end_node].first, locations[end_node].second, locations[adjacency_matrix[i][end_node][0]].first, locations[adjacency_matrix[i][end_node][0]].second);
        double dist_2 = distance(locations[end_node].first, locations[end_node].second, locations[adjacency_matrix[i][end_node][1]].first, locations[adjacency_matrix[i][end_node][1]].second);
        int node_selected = -1;
        double distance_value;

        if (dist_1 < dist_2)
        {
            node_selected = 0;
            distance_value = dist_1;
        }
        else
        {
            node_selected = 1;
            distance_value = dist_2;
        }

        double ch_required = 0;
        // int node = -1;

        bool visited[mxCustomers + 1] = {0};
        int counter = 0;
        end_node = adjacency_matrix[i][end_node][node_selected];
        double distance_between_nodes = distance(locations[depo].first, locations[depo].second, locations[end_node].first, locations[end_node].second);
        int temp = depo;
        ch_required = (discharging_additive + weight * 1.0 / mxWeightAllowed[i]) * (distance_value * (1 + weightFactorForDistance[i] * weight));

        int previous_node = depo;
        // distance_value =
        while (1)
        {
            double residual_battery_level = battery_level - 150;

            if (end_node == depo)
                residual_battery_level = battery_level;
            while (ch_required > residual_battery_level)
            {
                if (residual_battery_level < 100)
                    residual_battery_level += 150;
                // introduce charging station
                if (end_node == depo and residual_battery_level > ch_required)
                    break;

                double mn = 1e15;
                int ch_station = -1;
                double to_ch_station_charge = -1;

                for (int j = 1; j <= mxBatteryChargingStations; j++)
                {
                    double dist;
                    if (counter == 0)
                        dist = distance(locations[temp].first, locations[temp].second, batteryChargingStations[j].first, batteryChargingStations[j].second);
                    else
                        dist = distance(batteryChargingStations[(node_traversor[i].back() / (1e5))].first, batteryChargingStations[(node_traversor[i].back() / (1e5))].second, batteryChargingStations[j].first, batteryChargingStations[j].second);

                    double distance_between_charging = distance(locations[end_node].first, locations[end_node].second, batteryChargingStations[j].first, batteryChargingStations[j].second);

                    double battery_ch_required_for_previous_to_next = (discharging_additive + weight * 1.0 / mxWeightAllowed[i]) * (dist * (1 + weightFactorForDistance[i] * weight));

                    if (distance_between_charging < distance_between_nodes && battery_ch_required_for_previous_to_next < residual_battery_level)
                    {

                        mn = min(mn, dist);
                        ch_station = j;
                        to_ch_station_charge = battery_ch_required_for_previous_to_next;
                    }
                }
                // double distance_between_swapping;
                // double mnSwap = 1e5;
                // int swap_station = -1;
                // for (int j = 1; j <= mx_battery_swapping_stations; j++)
                // {
                //     double dist;
                //     if (counter == 0)
                //         dist = distance(locations[temp].first, locations[temp].second, battery_swap_stations[j].first, battery_swap_stations[j].second);
                //     else
                //         dist = distance(battery_swap_stations[(node_traversor[i].back() / (1e5))].first, battery_swap_stations[(node_traversor[i].back() / (1e5))].second, battery_swap_stations[j].first, battery_swap_stations[j].second);
                //     double distance_between_swapping = distance(locations[end_node].first, locations[end_node].second, battery_swap_stations[j].first, battery_swap_stations[j].second);

                //     // cout << "j is " << j << " dist is " << dist << "distance between/ charging" << distance_between_charging << "distance between nodes" << distance_between_nodes
                //     if (distance_between_swapping < distance_between_swapping_nodes)
                //     {
                //         mnSwap = min(mnSwap, dist);
                //         swap_station = j;
                //     }
                // }
                // double mnCharge;
                // double mnSwap;
                if (ch_station == -1)
                {

                    return 0;
                }
                // double charging_node_distance_value;
                // double swapping_node_distance_value;
                // if (ch_station != -1)
                // {
                distance_between_nodes = distance(batteryChargingStations[ch_station].first, batteryChargingStations[ch_station].second, locations[end_node].first, locations[end_node].second);
                if (counter == 0)
                    distance_value = distance(locations[temp].first, locations[temp].second, batteryChargingStations[ch_station].first, batteryChargingStations[ch_station].second);
                else
                    distance_value = distance(batteryChargingStations[(node_traversor[i].back() / (1e5))].first, batteryChargingStations[(node_traversor[i].back() / (1e5))].second, batteryChargingStations[ch_station].first, batteryChargingStations[ch_station].second);

                // }
                // if(swap_station!=-1)
                // {
                //     distance_between_swapping_nodes = distance(battery_swap_stations[ch_station].first, battery_swap_stations[ch_station].second, locations[end_node].first, locations[end_node].second);
                //     if (counter == 0)
                //         swapping_node_distance_value = distance(locations[temp].first, locations[temp].second, battery_swap_stations[ch_station].first, battery_swap_stations[ch_station].second);
                //     else
                //         swapping_node_distance_value = distance(battery_swap_stations[(node_traversor[i].back() / (1e5))].first, battery_swap_stations[(node_traversor[i].back() / (1e5))].second, battery_swap_stations[ch_station].first, battery_swap_stations[ch_station].second);
                // }

                charge_requirement[i][ch_station].push_back(mxBatteryLevels[i] - to_ch_station_charge);
                total_times[i] += (distance_value / ((1 + weightFactorForSpeed[i] * weight) * speedOfVehicles[i]));
                node_traversor[i].push_back(ch_station * 1e5);
                ch_required = (discharging_additive + weight * 1.0 / mxWeightAllowed[i]) * (distance_between_nodes * (1 + weightFactorForDistance[i] * weight));

                battery_level = mxBatteryLevels[i];
                distance_value = distance_between_nodes;

                residual_battery_level = battery_level - 150;
            }
            // if (end_node == depo and counter!=0)
            //     break;
            // counter++;

            total_times[i] += (distance_value / ((1 + weightFactorForSpeed[i] * weight) * speedOfVehicles[i]));

            battery_level -= ch_required;
            node_traversor[i].push_back(end_node);
            if (end_node == depo)
                break;

            weight -= demandWeights[end_node];
            temp = end_node;
            if (adjacency_matrix[i][end_node][0] == previous_node)
                end_node = adjacency_matrix[i][end_node][1];
            else
                end_node = adjacency_matrix[i][end_node][0];
            // end_node = adjacency_matrix[i][end_node][node_selected];

            // if (visited[end_node] != 0 or end_node == previous_node)
            // {
            //     node_selected ^= 1;
            //     end_node = adjacency_matrix[i][temp][node_selected];
            // }

            // visited[end_node] = 1;
            // node = end_node == adjacency_matrix[i][end_node][node_selected] ? adjacency_matrix[i][end_node][node_selected ^ 1] : adjacency_matrix[i][end_node][node_selected];

            // int counter = 0;
            // double distance_between_swapping_nodes = distance_between_nodes;
            // if (end_node == depo)
            //     break;

            distance_between_nodes = distance(locations[temp].first, locations[temp].second, locations[end_node].first, locations[end_node].second);

            ch_required = (discharging_additive + weight * 1.0 / mxWeightAllowed[i]) * (distance_between_nodes * (1 + weightFactorForDistance[i] * weight));
            distance_value = distance_between_nodes;
            counter++;

            previous_node = temp;
        }
    }

    for (auto &i : charge_requirement)
    {
        for (auto &j : i)
        {
            sort(j.begin(), j.end(), greater<>());
        }
    }

    /************* Charging completed, now ensuring that all the vehicles remain in their cost *************/

    vector<double> charging_times(mxVehicles + 1);

    vector<double> cost_of_charging(mxVehicles + 1);

    for (int i = 1; i <= mxVehicles; i++)
    {
        for (auto stations : charge_requirement[i])
        {
            for (auto charge : stations)
            {

                cost_of_charging[i] += (charge * costPerUnitChargeOfFast);
                charging_times[i] += (charge * fastChargingTimePerUnitOfCharge);
            }
        }
    }
    for (int i = 1; i <= mxVehicles; i++)
    {
    }

    // Balancing cost
    for (int i = 1; i <= mxVehicles; i++)
    {
        priority_queue<pair<double, pair<int, int>>> charge_storage;
        for (int j = 1; j <= mxBatteryChargingStations; j++)
        {
            for (int k = 0; k < charge_requirement[i][j].size(); k++)
            {
                charge_storage.push({charge_requirement[i][j][k], {j, k}});
            }
        }

        bool medium_or_slow = 0; // 0 denotes for fast to medium and 1 dentoes from medium to slow

        map<pair<int, int>, bool> mapping_for_station[mxVehicles + 1];
        // 0 means from fast to medium and 1 means from medium to slow if for same charging station
        while (cost_of_charging[i] > mxCostAllowed[i])
        {
            double extra = (cost_of_charging[i] - mxCostAllowed[i]);

            if (charge_storage.size() == 0)
            {

                return 0;
            }
            auto top = charge_storage.top();
            medium_or_slow = mapping_for_station[i][top.second];

            double value = top.first * (medium_or_slow == 0 ? costPerUnitChargeOfMedium : costPerUnitChargeOfSlow);
            double cost_saved = (top.first) * ((medium_or_slow == 0 ? costPerUnitChargeOfFast : costPerUnitChargeOfMedium) - (medium_or_slow == 0 ? costPerUnitChargeOfMedium : costPerUnitChargeOfSlow));

            charging_times[i] += (top.first) * ((medium_or_slow == 0 ? mediumChargingTimePerUnitOfCharge : slowChargingTimePerUnitOfCharge) - (medium_or_slow == 0 ? fastChargingTimePerUnitOfCharge : mediumChargingTimePerUnitOfCharge));
            // cost_of_charging[i] -= total_cost_saved;
            charge_storage.pop();
            if (mapping_for_station[i][top.second] == 0)
                charge_storage.push({top.first - cost_saved, top.second});

            cost_of_charging[i] -= cost_saved;

            mapping_for_station[i][top.second] = 1;
        }
    }

    /************* Cost Optimisation Also Done ****************/

    for (int i = 1; i <= mxVehicles; i++)
    {
        total_times[i] += charging_times[i];

        // if(total_times[i]>10.00)
        // total_times[i]/=(100.00);
    }
    // sort(total_times.begin(), total_times.end(), greater<>());

    /************* Battery Swapping Not Done *************/

    for (int i = 1; i <= mxVehicles; i++)
    {
        cout << "Vehicle " << i << ": ";
        for (int j = 0; j < node_traversor[i].size() - 1; j++)
        {
            int x = node_traversor[i][j];
            int y = x / 1e5;
            if (y != 0)
                cout << " Ch-st(" << y << ") -> ";
            else
                cout << x << " -> ";
        }
        cout << "0" << endl;
        cout << "Total cost incurred: " << cost_of_charging[i] << endl;
        cout << "Total time taken: " << total_times[i] << endl;
        cout << endl;
    }
    return 0;
}

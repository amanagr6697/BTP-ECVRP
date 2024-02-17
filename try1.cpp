// Author : Aman Agrawal(ILP completed in parts(present in the github url presented), heuristic here)
#include <bits/stdc++.h>
#include "variables.h"
using namespace std;

double distance(double x1, double y1, double x2, double y2)
{
    return (double)sqrtl((x1 - x2) * (x1 - x2) * 1.00 + (y1 - y2) * (y1 - y2) * 1.00);
}

signed main()
{
    // Vehicle Assignment part completed.
    cout << mx_customers;
    // Weight assigning
    vector<pair<double, int>> demand;
    int cnt = 1;
    // cout << "aman";
    for (int i = 1; i < demand_weights.size(); i++)
    {
        demand.push_back({demand_weights[i], i});
        cnt++;
    }
    // cout << "cnt" << cnt << endl;
    sort(demand.begin(), demand.end(), greater<>());
    // cout << "aman";
    // cout << demand.size();
    priority_queue<pair<double, int>> allot_weights;
    for (int i = 1; i < mx_weight_allowed.size(); i++)
        allot_weights.push({mx_weight_allowed[i], i});
    // cout << "aman";

    vector<pair<double, vector<int>>> filled_weights(mx_vehicles + 1);

    for (auto &i : filled_weights)
        i.first = 0;

    // cout << "size" << allot_weights.size();
    int counter = 0;
    while (1)
    {
        // cout << "counter" << counter << endl;
        if (counter == mx_customers)
            break;
        auto top = allot_weights.top();
        cout << top.first;
        // cout << "top.first" << top.first << endl;
        // cout << demand[counter].first << "\n";
        if (top.first < demand[counter].first)
        {
            cout << "Assignment not possible...Exiting \n";
            return 0;
        }
        else
        {
            int left_weight = top.first - demand[counter].first;
            allot_weights.pop();
            // cout << "Left weight: " << left_weight << endl;
            allot_weights.push({left_weight, top.second});
            // cout << "Left weight: " << left_weight << endl;

            filled_weights[top.second].first += demand[counter].first;
            // cout << "Weights" << top.second << " " << demand[counter].first << filled_weights[top.second].first << endl;
            // cout << "Left weight: " << left_weight << endl;
            // cout<<"demand counter"<<demand[counter].second<<top.second;
            filled_weights[top.second].second.push_back(demand[counter].second);
            // cout << "Top second" << top.second << "Meow" << demand[counter].second << endl;
            counter++;
            // cout << "Left weight: " << left_weight << endl;
            // cout << "counter" << counter;
        }
        // cout << allot_weights.size();
    }
    // cout << "aman";

    counter = 0;

    string baseCommand = "tsp vehicle_";

    vector<vector<int>> vehicleCustomerMapping(mx_vehicles + 1, vector<int>(mx_customers + 1, 0));
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
        // cout << command;
        outfile << 0 << " " << locations[0].first << " " << locations[0].second << "\n";

        for (auto node : i.second)
        {
            outfile << node_num << " " << locations[node].first << " " << locations[node].second << "\n";
            cout << "AMan node" << node << endl;
            vehicleCustomerMapping[counter][node_num] = node;
            cout << "counter" << counter << "node num" << node_num << "node" << node << endl;
            node_num++;
        }

        outfile.close();
        cout << command.c_str();
        system(command.c_str());
        counter++;
    }

    // Battery charge specifying

    vector<int> adjacency_matrix[mx_vehicles + 1][mx_customers + 1];

    for (int i = 1; i < mx_battery_levels.size(); i++)
    {
        string fileName = "vehicle_" + to_string(i) + ".txt.tour";

        ifstream file(fileName);
        if (!file.is_open())
        {
            cout << fileName << endl;
            std::cerr << "Error opening file" << std::endl;
            return 1;
        }
        string line;
        vector<int> temp_nodes;
        int temp = 0;
        while (getline(file, line))
        {
            cout << line << endl;
            if (temp == 0)
            {
                temp++;
                continue;
            }
            int node = stoi(line);
            cout << node << endl;
            temp_nodes.push_back(vehicleCustomerMapping[i][node]);
            cout << "NODE: " << node << "Mapping" << vehicleCustomerMapping[i][node] << endl;
        }
        file.close();
        for (auto meow : temp_nodes)
            cout << "meow" << meow << endl
                 << endl;
        double total_weight = filled_weights[i].first;

        for (int j = 0; j < temp_nodes.size() - 1; j++)
        {
            adjacency_matrix[i][temp_nodes[j]].push_back(temp_nodes[j + 1]);
            adjacency_matrix[i][temp_nodes[j + 1]].push_back(temp_nodes[j]);
        }
        adjacency_matrix[i][temp_nodes[0]].push_back(temp_nodes[temp_nodes.size() - 1]);
        adjacency_matrix[i][temp_nodes[temp_nodes.size() - 1]].push_back(temp_nodes[0]);

        for (int j = 0; j <= mx_customers; j++)
        {
            cout << "yeah i " << i << "j " << j << "size " << adjacency_matrix[i][j].size() << endl;
            if (adjacency_matrix[i][j].size() != 0)
            {
                cout << adjacency_matrix[i][j][0] << " " << adjacency_matrix[i][j][1] << endl;
            }
        }
    }

    cout << "amancompleted";
    vector<vector<vector<int>>> charge_requirement(mx_vehicles + 1, vector<vector<int>>(mx_battery_charging_stations));
    double discharging_additive = discharging_const * parameter + temperature * sclaing_factor;
    // The lesser distance that I cover in the initial phase where I am having lesser weight, it should be better.
    vector<int> node_traversor[mx_vehicles + 1];
    vector<double> total_times(mx_vehicles + 1);

    for (int i = 1; i <= mx_vehicles; i++)
    {
        double weight = filled_weights[i].first;
        cout << "Weight: " << weight << endl;

        int depo = 0;

        int start_node = depo;

        double battery_level = mx_battery_levels[i];
        node_traversor[i].push_back(start_node);
        cout<<"ROCKS"<<adjacency_matrix[i][start_node][0]<<"bhak"<<adjacency_matrix[i][start_node][1]<<endl<<endl;
        double dist_1 = distance(locations[start_node].first, locations[start_node].second, locations[adjacency_matrix[i][start_node][0]].first, locations[adjacency_matrix[i][start_node][0]].second);
        double dist_2 = distance(locations[start_node].first, locations[start_node].second, locations[adjacency_matrix[i][start_node][1]].first, locations[adjacency_matrix[i][start_node][1]].second);
        int node_selected = -1;
        double distance_value;
        cout << "DIST" << dist_1 << " " << dist_2 << endl;
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

        cout << "NODE" << node_selected << endl;
        double ch_required = discharging_additive + weight * 1.0 / mx_weight_allowed[i];
        int node = -1;

        total_times[i] += ((node_selected == 0 ? dist_1 : dist_2) / (weight_factor_for_speed[i] * weight * speed_of_vehicles[i]));
        cout << "Total_times" << total_times[i] << endl;

        cout << "Vehicle" << i << "start node" << start_node << endl
             << endl;
        bool visited[mx_customers + 1] = {0};
        while (1)
        {
            total_times[i] += (distance_value / (weight_factor_for_speed[i] * weight * speed_of_vehicles[i]));
            weight -= demand_weights[adjacency_matrix[i][start_node][node_selected]];
            battery_level -= ch_required;
            node_traversor[i].push_back(start_node);
            cout << "node" << node << endl
                 << "start node" << start_node << "node selected" << node_selected << endl
                 << endl;
            start_node = adjacency_matrix[i][start_node][node_selected];
            
            if(start_node == adjacency_matrix[i][start_node][node_selected] || visited[adjacency_matrix[i][start_node][node_selected]]!=0)
            {
            node_selected^=1;
            }
            visited[start_node]=1;
            // node = start_node == adjacency_matrix[i][start_node][node_selected] ? adjacency_matrix[i][start_node][node_selected ^ 1] : adjacency_matrix[i][start_node][node_selected];

            node = adjacency_matrix[i][start_node][node_selected];
            cout << "node" << node << endl
                 << "start node" << start_node << "node selected" << node_selected << "distance value" << distance_value << "discharging value" << discharging_additive << endl
                 << endl;
            ch_required = (discharging_additive + weight * 1.0 / mx_weight_allowed[i]) * (distance_value * (weight_factor_for_distance[i] * weight));
            cout << "Battery Level: " << battery_level << "charge req" << ch_required << endl;
            int counter = 0;
            while (ch_required > battery_level)
            {
                // introduce charging station
                double mn = 1e15;
                int ch_node;
                int ch_station = -1;
                for (int j = 0; j < mx_battery_charging_stations; j++)
                {
                    double dist;
                    if (counter == 0)
                        dist = distance(locations[start_node].first, locations[start_node].second, battery_ch_stations[j].first, battery_ch_stations[j].second);
                    else
                        dist = distance(battery_ch_stations[(node_traversor[i].back() / (1e9))].first, battery_ch_stations[(node_traversor[i].back() / (1e9))].second, battery_ch_stations[j].first, battery_ch_stations[j].second);

                    if (mn > dist)
                    {
                        mn = dist;
                        ch_station = j;
                    }
                }
                if (counter == 0)
                    distance_value = distance(locations[start_node].first, locations[start_node].second, battery_ch_stations[ch_station].first, battery_ch_stations[ch_station].second);
                else
                    distance_value = distance(battery_ch_stations[(node_traversor[i].back() / (1e9))].first, battery_ch_stations[(node_traversor[i].back() / (1e9))].second, battery_ch_stations[ch_station].first, battery_ch_stations[ch_station].second);

                total_times[i] += (distance_value / (weight_factor_for_speed[i] * weight * speed_of_vehicles[i]));
                node_traversor[i].push_back(ch_station * 1e9);
                charge_requirement[i][ch_station].push_back(mx_battery_levels[i] - battery_level);
                battery_level = mx_battery_levels[i];
            }
            if(node == depo)
            break;
        }
    }
    cout << "aman";

    for (auto &i : charge_requirement)
    {
        for (auto &j : i)
        {
            sort(j.begin(), j.end(), greater<>());
        }
    }

    vector<double> charging_times(mx_vehicles + 1);

    vector<double> cost_of_charging(mx_vehicles + 1);

    for (int i = 1; i <= mx_vehicles; i++)
    {
        for (auto stations : charge_requirement[i])
        {
            for (auto charge : stations)
            {
                cost_of_charging[i] += (charge * cost_per_unit_charge_of_fast);
                charging_times[i] += (charge * fast_ch_time_per_unit_of_charge);
            }
        }
    }
    for(int i=1;i<=mx_vehicles;i++)
    {
        cout<<cost_of_charging[i]<<endl;
        cout<<charging_times[i]<<endl;
    }

    // Balancing cost
    for (int i = 1; i <= mx_vehicles; i++)
    {
        vector<int> num_charges_for_each_station;

        for (auto station : charge_requirement[i])
        {
            num_charges_for_each_station.push_back(station.size());
        }
        sort(num_charges_for_each_station.begin(), num_charges_for_each_station.end(), greater<>());

        int counter = 0;

        bool medium_or_slow = 0; // 0 denotes for fast to medium and 1 dentoes from medium to slow

        while (counter < num_charges_for_each_station.size() && cost_of_charging[i] > mx_cost_allowed[i])
        {
            int extra = (cost_of_charging[i] - mx_cost_allowed[i]);

            vector<bool> dp(2 * extra + 2, 0);

            dp[0] = 1;

            for (int j = 0; j < charge_requirement[i][num_charges_for_each_station[counter]].size(); j++)
            {
                int value = charge_requirement[i][num_charges_for_each_station[counter]][j] * (medium_or_slow == 0 ? cost_per_unit_charge_of_fast : cost_per_unit_charge_of_medium);
                for (int k = 2 * extra; k >= value; k--)
                {
                    if (dp[k - value])
                        dp[k] = 1;
                }
            }

            vector<int> station_numbers;
            bool flag = 0;
            for (int j = extra; j <= 2 * extra; j++)
            {
                if (dp[j])
                {
                    flag = 1;
                    for (int k = 0; k < charge_requirement[i][num_charges_for_each_station[counter]].size(); j++)
                    {
                        int value = charge_requirement[i][num_charges_for_each_station[counter]][k];
                        if (j >= value and dp[j - value])
                        {
                            station_numbers.push_back(k);
                            j -= value;
                        }
                        else if (j == 0)
                            break;
                    }
                }
                if (flag)
                    break;
            }

            int total_cost_saved = 0;
            for (auto j : station_numbers)
            {
                int total_charge = (charge_requirement[i][num_charges_for_each_station[counter]][j]);
                total_cost_saved += (total_charge) * ((medium_or_slow == 0 ? cost_per_unit_charge_of_medium : cost_per_unit_charge_of_slow) - (medium_or_slow == 0 ? cost_per_unit_charge_of_fast : cost_per_unit_charge_of_medium));
                charging_times[i] += (total_charge) * ((medium_or_slow == 0 ? medium_ch_time_per_unit_of_charge : slow_ch_time_per_unit_of_charge) - (medium_or_slow == 0 ? fast_ch_time_per_unit_of_charge : medium_ch_time_per_unit_of_charge));
            }
            cost_of_charging[i] -= total_cost_saved;
            counter++;
            if (counter == num_charges_for_each_station.size())
            {
                if (medium_or_slow == 0)
                    medium_or_slow = 1;
                else
                {
                    cout << "Solution not possible with these limits...Exiting";
                    return 0;
                }
            }
        }
    }

    for (int i = 1; i <= mx_vehicles; i++)
    {
        total_times[i] += charging_times[i];
    }
    sort(total_times.begin(), total_times.end(), greater<>());

    cout << "Answer is: " << total_times[0] << endl;

    // Not including battery saving for now
    return 0;
}
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
    // Vehicle Assignment part.
    /************* Vehicle Assignment Part *************/
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
        if (top.first < demand[counter].first) // If maximum possible vehicle weight can't also fulfill the requirements.
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
    /************* Creating graph from the traversors  *************/

    vector<int> adjacency_matrix[mx_vehicles + 1][mx_customers + 1];

    vector<int> vehicle_sizes;
    vehicle_sizes.push_back(0);
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
        vehicle_sizes.push_back(temp_nodes.size());
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

    /************* Graph Done *************/

    /************* Satisfying each vehicle's charging constraint by visiting multiple depot's *************/

    cout << "amancompleted";
    vector<vector<vector<int>>> charge_requirement(mx_vehicles + 1, vector<vector<int>>(mx_battery_charging_stations + 1));
    double discharging_additive = discharging_const * parameter + temperature * sclaing_factor;
    cout << "DISCHARGIng " << discharging_additive << endl;
    // The lesser distance that I cover in the initial phase where I am having lesser weight, it should be better.
    vector<int> node_traversor[mx_vehicles + 1];
    vector<double> total_times(mx_vehicles + 1);

    for (int i = 1; i <= mx_vehicles; i++)
    {
        double weight = filled_weights[i].first;
        cout << "Weight: " << weight << endl;

        int depo = 0;
        node_traversor[i].push_back(depo);

        int end_node = depo;

        double battery_level = mx_battery_levels[i];
        // node_traversor[i].push_back(end_node);
        cout << "ROCKS" << adjacency_matrix[i][end_node][0] << "bhak" << adjacency_matrix[i][end_node][1] << endl
             << endl;
        double dist_1 = distance(locations[end_node].first, locations[end_node].second, locations[adjacency_matrix[i][end_node][0]].first, locations[adjacency_matrix[i][end_node][0]].second);
        double dist_2 = distance(locations[end_node].first, locations[end_node].second, locations[adjacency_matrix[i][end_node][1]].first, locations[adjacency_matrix[i][end_node][1]].second);
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
        cout << battery_level << endl;
        double ch_required = 0;
        // int node = -1;

        cout << "Vehicle" << i << "start node" << end_node << endl
             << endl;
        bool visited[mx_customers + 1] = {0};
        int counter = 0;
        end_node = adjacency_matrix[i][end_node][node_selected];
        double distance_between_nodes = distance(locations[depo].first, locations[depo].second, locations[end_node].first, locations[end_node].second);
        int temp = depo;
        ch_required = (discharging_additive + weight * 1.0 / mx_weight_allowed[i]) * (distance_value * (1 + weight_factor_for_distance[i] * weight));
        cout << "End node " << end_node << endl;
        cout << "CH REQ " << ch_required << endl;
        cout << "MAX battery " << battery_level << endl;
        cout << "DISTANCE NODES " << distance_between_nodes << endl;
        int previous_node = depo;
        // distance_value =
        while (1)
        {
            double residual_battery_level = battery_level - 150;
            cout << "RESIDUAL battery level " << residual_battery_level << endl;
            cout << "battery level " << battery_level << endl;
            cout << "ch req " << ch_required << endl;
            if(end_node==depo)
            residual_battery_level=battery_level;
            while (ch_required > residual_battery_level)
            {
                if (residual_battery_level < 100)
                    residual_battery_level += 150;
                // introduce charging station
                if(end_node==depo and residual_battery_level>ch_required)
                break;

                double mn = 1e15;
                int ch_station = -1;
                double to_ch_station_charge = -1;

                for (int j = 1; j <= mx_battery_charging_stations; j++)
                {
                    double dist;
                    if (counter == 0)
                        dist = distance(locations[temp].first, locations[temp].second, battery_ch_stations[j].first, battery_ch_stations[j].second);
                    else
                        dist = distance(battery_ch_stations[(node_traversor[i].back() / (1e5))].first, battery_ch_stations[(node_traversor[i].back() / (1e5))].second, battery_ch_stations[j].first, battery_ch_stations[j].second);
                    cout << "DIST   " << dist << endl;
                    double distance_between_charging = distance(locations[end_node].first, locations[end_node].second, battery_ch_stations[j].first, battery_ch_stations[j].second);
                    cout << "Battery " << battery_ch_stations[j].first << " " << battery_ch_stations[j].second << endl;
                    cout << "Temp " << temp << " " << locations[temp].first << " " << locations[temp].second << endl;
                    cout<<"Node between charging distance "<<distance_between_charging<<endl;
                    cout<<"Node between node distance "<<distance_between_nodes<<endl;

                    cout << "j is " << j << " dist is " << dist << "distance between charging" << distance_between_charging << "distance between nodes" << distance_between_nodes << endl;
                    double battery_ch_required_for_previous_to_next = (discharging_additive + weight * 1.0 / mx_weight_allowed[i]) * (dist * (1 + weight_factor_for_distance[i] * weight));
                    cout << "BATTERY CHARGE " << battery_ch_required_for_previous_to_next << endl;
                    cout << "WEIGHT " << weight << endl;
                    if (distance_between_charging < distance_between_nodes && battery_ch_required_for_previous_to_next < residual_battery_level)
                    {
                        cout<<"AMANNNNN"<<endl;
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

                //     // cout << "j is " << j << " dist is " << dist << "distance between/ charging" << distance_between_charging << "distance between nodes" << distance_between_nodes << endl;
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
                    cout << "Solution not feasible...";
                    return 0;
                }
                // double charging_node_distance_value;
                // double swapping_node_distance_value;
                // if (ch_station != -1)
                // {
                distance_between_nodes = distance(battery_ch_stations[ch_station].first, battery_ch_stations[ch_station].second, locations[end_node].first, locations[end_node].second);
                if (counter == 0)
                    distance_value = distance(locations[temp].first, locations[temp].second, battery_ch_stations[ch_station].first, battery_ch_stations[ch_station].second);
                else
                    distance_value = distance(battery_ch_stations[(node_traversor[i].back() / (1e5))].first, battery_ch_stations[(node_traversor[i].back() / (1e5))].second, battery_ch_stations[ch_station].first, battery_ch_stations[ch_station].second);
                cout << "ch station" << ch_station << endl;
                // }
                // if(swap_station!=-1)
                // {
                //     distance_between_swapping_nodes = distance(battery_swap_stations[ch_station].first, battery_swap_stations[ch_station].second, locations[end_node].first, locations[end_node].second);
                //     if (counter == 0)
                //         swapping_node_distance_value = distance(locations[temp].first, locations[temp].second, battery_swap_stations[ch_station].first, battery_swap_stations[ch_station].second);
                //     else
                //         swapping_node_distance_value = distance(battery_swap_stations[(node_traversor[i].back() / (1e5))].first, battery_swap_stations[(node_traversor[i].back() / (1e5))].second, battery_swap_stations[ch_station].first, battery_swap_stations[ch_station].second);
                // }

                charge_requirement[i][ch_station].push_back(mx_battery_levels[i] - to_ch_station_charge);
                total_times[i] += (distance_value / ((1 + weight_factor_for_speed[i] * weight) * speed_of_vehicles[i]));
                node_traversor[i].push_back(ch_station * 1e5);
                ch_required = (discharging_additive + weight * 1.0 / mx_weight_allowed[i]) * (distance_between_nodes * (1 + weight_factor_for_distance[i] * weight));
                cout << "charge required" << ch_required << endl;
                battery_level = mx_battery_levels[i];
                distance_value = distance_between_nodes;
                cout << "batter y level" << battery_level << endl;
                residual_battery_level = battery_level - 150;
            }
            // if (end_node == depo and counter!=0)
            //     break;
            // counter++;
            cout << "OHHHHHHHHHHHHH " << distance_value << endl;
            total_times[i] += (distance_value / ((1 + weight_factor_for_speed[i] * weight) * speed_of_vehicles[i]));
            cout << "Weight" << weight << endl;
            battery_level -= ch_required;
            node_traversor[i].push_back(end_node);
            if (end_node == depo)
                break;
            cout
                << "start node" << end_node << "node selected" << node_selected << endl
                << endl;

            weight -= demand_weights[end_node];
            temp = end_node;
            if (adjacency_matrix[i][end_node][0] == previous_node)
                end_node = adjacency_matrix[i][end_node][1];
            else
                end_node = adjacency_matrix[i][end_node][0];
            // end_node = adjacency_matrix[i][end_node][node_selected];
            cout << "start" << end_node << endl;
            // if (visited[end_node] != 0 or end_node == previous_node)
            // {
            //     node_selected ^= 1;
            //     end_node = adjacency_matrix[i][temp][node_selected];
            // }
            cout << "DEPOOOOOOOOOOOOOOOOOOOOOOOOOO    " << end_node << endl;
            cout << "WEIGHT " << weight << endl;
            // visited[end_node] = 1;
            // node = end_node == adjacency_matrix[i][end_node][node_selected] ? adjacency_matrix[i][end_node][node_selected ^ 1] : adjacency_matrix[i][end_node][node_selected];

            cout
                << "start node" << end_node << "node selected" << node_selected << "distance value" << distance_value << "discharging value" << discharging_additive << endl
                << endl;
            cout << "Battery Level: " << battery_level << "charge req" << ch_required << endl;
            // int counter = 0;
            // double distance_between_swapping_nodes = distance_between_nodes;
            // if (end_node == depo)
            //     break;
            cout << "TEMP    " << temp << " end_node " << end_node << endl;
            distance_between_nodes = distance(locations[temp].first, locations[temp].second, locations[end_node].first, locations[end_node].second);

            ch_required = (discharging_additive + weight * 1.0 / mx_weight_allowed[i]) * (distance_between_nodes * (1 + weight_factor_for_distance[i] * weight));
            distance_value = distance_between_nodes;
            counter++;
            cout << "CH REQ   " << ch_required << endl;
            cout << "BATTERY LEVEL " << battery_level << endl;
            previous_node = temp;
        }
        cout << "END OF VEHICLE            ----------------------------------------------------------" << endl;
    }
    cout << "aman";

    for (auto &i : charge_requirement)
    {
        for (auto &j : i)
        {
            sort(j.begin(), j.end(), greater<>());
        }
    }

    /************* Charging completed, now ensuring that all the vehicles remain in their cost *************/

    vector<double> charging_times(mx_vehicles + 1);

    vector<double> cost_of_charging(mx_vehicles + 1);

    for (int i = 1; i <= mx_vehicles; i++)
    {
        for (auto stations : charge_requirement[i])
        {
            for (auto charge : stations)
            {
                cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << charge << endl;
                cost_of_charging[i] += (charge * cost_per_unit_charge_of_fast);
                charging_times[i] += (charge * fast_ch_time_per_unit_of_charge);
                cout << "charge" << charge << endl;
            }
        }
    }
    for (int i = 1; i <= mx_vehicles; i++)
    {
        cout << "charging cost" << cost_of_charging[i] << endl;
        cout << "charging time" << charging_times[i] << endl;
    }

    // Balancing cost
    for (int i = 1; i <= mx_vehicles; i++)
    {
        priority_queue<pair<double, pair<int, int>>> charge_storage;
        for (int j = 1; j <= mx_battery_charging_stations; j++)
        {
            for (int k = 0; k < charge_requirement[i][j].size(); k++)
            {
                charge_storage.push({charge_requirement[i][j][k], {j, k}});
            }
        }

        bool medium_or_slow = 0; // 0 denotes for fast to medium and 1 dentoes from medium to slow
        cout << "cost of charrging" << cost_of_charging[i] << " mx cost allowed " << mx_cost_allowed[i] << endl;

        map<pair<int, int>, bool> mapping_for_station[mx_vehicles + 1];
        double total_cost_saved = 0;
        // 0 means from fast to medium and 1 means from medium to slow if for same charging station
        while (cost_of_charging[i] > mx_cost_allowed[i])
        {
            double extra = (cost_of_charging[i] - mx_cost_allowed[i]);
            cout << "extra" << extra << endl;

            if (charge_storage.size() == 0)
            {
                cout << "Cost speicification not feasible...Exiting";
                return 0;
            }
            auto top = charge_storage.top();
            medium_or_slow = mapping_for_station[i][top.second];
            cout << "mdium or losw" << medium_or_slow << endl;
            double value = top.first * (medium_or_slow == 0 ? cost_per_unit_charge_of_medium : cost_per_unit_charge_of_slow);
            double cost_saved = (top.first) * ((medium_or_slow == 0 ? cost_per_unit_charge_of_fast : cost_per_unit_charge_of_medium) - (medium_or_slow == 0 ? cost_per_unit_charge_of_medium : cost_per_unit_charge_of_slow));
            cout << "value " << value << " cost saved " << cost_saved << endl;
            total_cost_saved += cost_saved;
            charging_times[i] += (top.first) * ((medium_or_slow == 0 ? medium_ch_time_per_unit_of_charge : slow_ch_time_per_unit_of_charge) - (medium_or_slow == 0 ? fast_ch_time_per_unit_of_charge : medium_ch_time_per_unit_of_charge));
            cout << "total cost savaved" << total_cost_saved << endl;
            cost_of_charging[i] -= total_cost_saved;
            charge_storage.pop();
            if (mapping_for_station[i][top.second] == 0)
                charge_storage.push({top.first - cost_saved, top.second});
            cost_of_charging[i] -= cost_saved;
            mapping_for_station[i][top.second] = 1;
        }
    }

    /************* Cost Optimisation Also Done ****************/

    for (int i = 1; i <= mx_vehicles; i++)
    {
        total_times[i] += charging_times[i];
        cout << "Total time " << total_times[i] << endl;
        cout << " Charging cost" << cost_of_charging[i] << endl;
        if(total_times[i]>10.00)
        total_times[i]/=(100.00);
        // total_times[i]=(total_times[i]>10?total_times[i]/100.00:total_times[i]);
    }
    // sort(total_times.begin(), total_times.end(), greater<>());
    cout << "Answer is: " << total_times[0] << endl;
    cout<<endl<<endl<<endl<<endl;
    /************* Battery Swapping Not Done *************/


















    for (int i = 1; i <= mx_vehicles; i++)
    {
        cout << "Vehicle "<<i<<": ";
        for (int j = 0; j < node_traversor[i].size() -1 ; j++)
        {
            int x = node_traversor[i][j];
            int y = x/1e5;
            if(y!=0)
            cout<<" Ch-st("<<y<<") -> ";
            else
            cout<<x<<" -> ";
        }
        cout<<"0"<<endl;
        cout<<"Total cost incurred: "<<cost_of_charging[i]<<endl;
        cout<<"Total time taken: "<<total_times[i]<<endl;
        cout << endl;
    }
    
    return 0;
}


#include <bits/stdc++.h>
#include "variables.h"
using namespace std;

double distance(double x1, double y1, double x2, double y2)
{
  return (double)sqrtl((x1-x2)*(x1-x2)*1.00 + (y1-y2)*(y1-y2)*1.00);
}

signed main()
{
    // Vehicle Assignment part completed.
    cout << mx_customers;
    // Weight assigning
    vector<pair<double, int>> demand;
    int cnt = 1;
    // cout << "aman";/
    for (auto &weight : demand_weights)
    {
        demand.push_back({weight, cnt});
        cnt++;
    }
    cout << "cnt" << cnt << endl;
    sort(demand.begin(), demand.end(), greater<>());
    // cout << "aman";
    // cout<<demand.size();
    int counter = 1;
    priority_queue<pair<double, int>> allot_weights;
    for (auto weight : mx_weight_allowed)
        allot_weights.push({weight, counter}), counter++;
    // cout << "aman";

    vector<pair<double, vector<int>>> filled_weights(mx_vehicles + 1);

    for (auto &i : filled_weights)
        i.first = 0;

    counter = 0;
    while (1)
    {
        // cout << "counter" << counter << endl;
        if (counter == mx_customers)
            break;
        auto top = allot_weights.top();
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
            // cout << "Left weight: " << left_weight << endl;
            // cout<<"demand counter"<<demand[counter].second<<top.second;
            filled_weights[top.second].second.push_back(demand[counter].second);
            cout << "Top second" << top.second << "Meow" << demand[counter].second << endl;
            counter++;
            // cout << "Left weight: " << left_weight << endl;
        }
        // cout << allot_weights.size();
    }
    // cout << "aman";

    counter = 0;

    string baseCommand = "tsp vehicle_";
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
        cout << command;
        outfile << 0 << " " << depot_location.first << " " << depot_location.second << "\n";

        for (auto node : i.second)
        {
            outfile << node_num << " " << locations[node - 1].first << " " << locations[node - 1].second << "\n";
            node_num++;
        }

        outfile.close();
        cout << command.c_str();
        system(command.c_str());
        counter++;
    }

    // Battery charge specifying
    double discharging_additive = discharging_const * parameter + temperature * sclaing_factor;

    vector<int> adjacency_matrix[mx_vehicles+1][mx_customers];

    for (int i = 0; i < mx_battery_levels.size(); i++)
    {
        string fileName = "vehicle_" + to_string(i + 1) + ".txt";

        ifstream file(fileName);
        if (!file.is_open())
        {
            std::cerr << "Error opening file" << std::endl;
            return 1;

            string line;
            vector<int> temp_nodes;
            int temp = 0;
            while (getline(file, line))
            {
                if (temp == 0)
                {
                    temp++;
                    break;
                }
                int node = stoi(line);
                temp_nodes.push_back(node);
            }
            file.close();

        double total_weight = filled_weights[i].first;

            for (int j = 0; j < temp_nodes.size() - 1; j++)
            {
                adjacency_matrix[i + 1][j].push_back(j + 1);
                adjacency_matrix[i + 1][j + 1].push_back(j);
            }
            adjacency_matrix[i+1][0].push_back(temp_nodes[temp_nodes.size()-1]);
            adjacency_matrix[i+1][temp_nodes[temp_nodes.size()-1]].push_back(temp_nodes[0]);


        }
    }
    
    //The lesser distance that I cover in the initial phase where I am having lesser weight, it should be better.
    for(int i=1;i<=mx_vehicles;i++)
    {
        double total_weight = filled_weights[i].first;

        int depo = 0;

        while()
        {
            
            int node = adjacency_matrix[]
        }
    }


    return 0;
}
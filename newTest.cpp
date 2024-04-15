#include <bits/stdc++.h>
#include "variables.h"
void distributeObjects(int mxCustomers, int mxVehicles)
{
    // Seed random number generator with current time
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));


    // Initialize filledWeights
    std::vector<std::pair<double, std::vector<int>>> filledWeights(mxVehicles + 1);

    for(auto i:filledWeights)
    i.first = 0;
    std::uniform_int_distribution<> dis(1, mxVehicles);
    // Distribute objects randomly into filledWeights
    for (int obj = 1; obj <= mxCustomers; ++obj)
    {
        // Generate random bucket index
        // std::uniform_int_distribution<> dis(1, mxVehicles);
        int  bucketIndex = dis(gen);

        // Assign object to the bucket
        filledWeights[bucketIndex].second.push_back(obj); // Adjust index to start from 1
        filledWeights[bucketIndex].first+=demandWeights[obj];

        // Output the assignment
        // std::cout << "Object " << obj << " assigned to bucket " << bucketIndex << std::endl;
    }
}

int main()
{
    int mxCustomers, mxVehicles;
    std::cout << "Enter the number of objects (mxCustomers): ";
    std::cin >> mxCustomers;
    std::cout << "Enter the number of filledWeights (mxVehicles): ";
    std::cin >> mxVehicles;

    distributeObjects(mxCustomers, mxVehicles);

    return 0;
}

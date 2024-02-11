#include "Variables.h"

std::vector<std::pair<double, double>> locations = {
    {20, 15},
    {10, 25},
    {5, 10},
    {30, 20},
    {25, 5},
    {15, 30},
    {8, 18},
    {22, 28},
    {27, 12},
    {18, 22}};

std::pair<double, double> depot_location = {23, 27};

std::vector<double> demand_weights = {20, 12, 28, 18, 15, 25, 13, 17, 30, 10};

std::vector<double> mx_battery_levels = {5000, 1000, 4000, 2000};

std::vector<double> mx_cost_allowed = {700, 200, 400, 200};

std::vector<double> mx_weight_allowed = {80, 50, 70, 60};

double fast_ch_time = 0.5;

double medium_ch_time = 0.8;

double slow_ch_time = 1.3;

double battery_swapping_cost = 50;

double battery_swapping_time = 0.2;

int mx_vehicles = 4;

int mx_customers = 10;

std::vector<std::pair<double, double>> battery_ch_stations = {
    {13, 12},
    {19, 5},
    {23, 14}};

std::vector<std::pair<double, double>> battery_swap_stations = {
    {15, 11},
    {18, 7},
    {29, 13}};

double discharging_const = 10;

double temperature = 300;

double sclaing_factor = 0.03;

double parameter = 0.5;
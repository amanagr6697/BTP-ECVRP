#include "Variables.h"

std::vector<std::pair<double, double>> locations = {
    {23,27}, //depo location
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

std::vector<double> demand_weights = {0,20, 12, 28, 18, 15, 25, 13, 17, 30, 10};

std::vector<double> mx_battery_levels = {0,5000, 1000, 4000, 2000};

std::vector<double> mx_cost_allowed = {0,700, 200, 400, 200};

std::vector<double> mx_weight_allowed = {0,80, 50, 70, 60};

double fast_ch_time_per_unit_of_charge = 0.5;

double medium_ch_time_per_unit_of_charge = 0.8;

double slow_ch_time_per_unit_of_charge = 1.3;

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

int fast_time_chargers = 2;

int medium_time_chargers = 2;

int slow_time_chargers = 4;

double cost_per_unit_charge_of_fast = 10;
double cost_per_unit_charge_of_medium = 8;
double cost_per_unit_charge_of_slow = 5;

std::vector<double> speed_of_vehicles = {0, 12, 9, 13, 17};

std::vector<double> weight_factor_for_speed = {0, 0.13, 0.17, 0.09, 0.03};

std::vector<double> weight_factor_for_distance = {0, 0.13, 0.17, 0.09, 0.03};

double charge_per_unit_of_distance = 7;

int mx_battery_charging_stations = 3;
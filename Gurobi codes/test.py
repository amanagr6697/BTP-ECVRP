import json

# Load JSON data from a file
with open('data.json', 'r') as file:
    json_data = json.load(file)

# Extract location array
location = {i: {'latitude': location['latitude'], 'longitude': location['longitude']} for i, location in enumerate(json_data['location'])}

# Extract battery charging station array
batteryChargingStations = {i+1: {'latitude': station['latitude'], 'longitude': station['longitude']} for i, station in enumerate(json_data['batterychargingstation'])}

# Extract battery swapping station array
batterySwappingStations = {i+1: {'latitude': station['latitude'], 'longitude': station['longitude']} for i, station in enumerate(json_data['batteryswappingstation'])}

# Append location, battery charging stations, and battery swapping stations with increasing indexes
index = 0

latitude = {}
longitude = {}

for i in range(len(location) + len(batteryChargingStations) + len(batterySwappingStations)+1):
    if i <= len(location):
        latitude[index] = location[(i)%len(location)]['latitude']
        longitude[index] = location[(i)%len(location)]['longitude']
    elif i < len(location) + len(batteryChargingStations)+1:
        latitude[index] = location[i - len(location)]['latitude']
        longitude[index] = location[i - len(location)]['longitude']
    else:
        latitude[index] = location[i - len(location) - len(batteryChargingStations)]['latitude']
        longitude[index] = location[i - len(location) - len(batteryChargingStations)]['longitude']
    index += 1

# Extract demandWeight
demandWeight = {i: location.get("demandWeight", 0) for i, location in enumerate(json_data.get("location", []))}

# Extract other attributes
mxBatteryLevels = {i+1: vehicle.get("mxBatteryLevels", 0) for i, vehicle in enumerate(json_data.get("vehicle", []))}
mxCostAllowed = {i+1: vehicle.get("mxCostAllowed", 0) for i, vehicle in enumerate(json_data.get("vehicle", []))}
mxWeightAllowed = {i+1: vehicle.get("mxWeightAllowed", 0) for i, vehicle in enumerate(json_data.get("vehicle", []))}
speedOfVehicles = {i+1: vehicle.get("speedOfVehicles", 0) for i, vehicle in enumerate(json_data.get("vehicle", []))}
weightFactorForSpeed = {i+1: vehicle.get("weightFactorForSpeed", 0) for i, vehicle in enumerate(json_data.get("vehicle", []))}
weightFactorForDistance = {i+1: vehicle.get("weightFactorForDistance", 0) for i, vehicle in enumerate(json_data.get("vehicle", []))}

# Extract individual variables
fastChargingTimePerUnitOfCharge = json_data.get('fastChargingTimePerUnitOfCharge', 0)
mediumChargingTimePerUnitOfCharge = json_data.get('mediumChargingTimePerUnitOfCharge', 0)
slowChargingTimePerUnitOfCharge = json_data.get('slowChargingTimePerUnitOfCharge', 0)
batterySwappingCost = json_data.get('batterySwappingCost', 0)
batterySwappingTime = json_data.get('batterySwappingTime', 0)
mxVehicles = json_data.get('mxVehicles', 0)
mxCustomers = json_data.get('mxCustomers', 0)
dischargingConst = json_data.get('dischargingConst', 0)
temperature = json_data.get('temperature', 0)
scalingFactor = json_data.get('scalingFactor', 0)
parameter = json_data.get('parameter', 0)
fastTimeChargers = json_data.get('fastTimeChargers', 0)
mediumTimeChargers = json_data.get('mediumTimeChargers', 0)
slowTimeChargers = json_data.get('slowTimeChargers', 0)
batteriesAvailable = json_data.get('batteriesAvailable', 0)
costPerUnitChargeOfFast = json_data.get('costPerUnitChargeOfFast', 0)
costPerUnitChargeOfMedium = json_data.get('costPerUnitChargeOfMedium', 0)
costPerUnitChargeOfSlow = json_data.get('costPerUnitChargeOfSlow', 0)
mxBatteryChargingStations = json_data.get('mxBatteryChargingStations', 0)
mxBatterySwappingStations = json_data.get('mxBatterySwappingStations', 0)

# Print all dictionaries and variables
print("location:")
for key, value in location.items():
    print(f"{key}: {value}")

print("latitude:")
for key, value in latitude.items():
    print(f"{key}: {value}")

print("longitude:")
for key, value in longitude.items():
    print(f"{key}: {value}")

print("\nBattery Charging Stations:")
for key, value in batteryChargingStations.items():
    print(f"{key}: {value}")

print("\nBattery Swapping Stations:")
for key, value in batterySwappingStations.items():
    print(f"{key}: {value}")

print("\nDemandWeight:")
for key, value in demandWeight.items():
    print(f"{key}: {value}")

print("\nmxBatteryLevels:")
for key, value in mxBatteryLevels.items():
    print(f"{key}: {value}")

print("\nmxCostAllowed:")
for key, value in mxCostAllowed.items():
    print(f"{key}: {value}")

print("\nmxWeightAllowed:")
for key, value in mxWeightAllowed.items():
    print(f"{key}: {value}")

print("\nspeedOfVehicles:")
for key, value in speedOfVehicles.items():
    print(f"{key}: {value}")

print("\nweightFactorForSpeed:")
for key, value in weightFactorForSpeed.items():
    print(f"{key}: {value}")

print("\nweightFactorForDistance:")
for key, value in weightFactorForDistance.items():
    print(f"{key}: {value}")

print(f"\nfastChargingTimePerUnitOfCharge: {fastChargingTimePerUnitOfCharge}")
print(f"mediumChargingTimePerUnitOfCharge: {mediumChargingTimePerUnitOfCharge}")
print(f"slowChargingTimePerUnitOfCharge: {slowChargingTimePerUnitOfCharge}")
print(f"batterySwappingCost: {batterySwappingCost}")
print(f"batterySwappingTime: {batterySwappingTime}")
print(f"mxVehicles: {mxVehicles}")
print(f"mxCustomers: {mxCustomers}")
print(f"dischargingConst: {dischargingConst}")
print(f"temperature: {temperature}")
print(f"scalingFactor: {scalingFactor}")
print(f"parameter: {parameter}")
print(f"fastTimeChargers: {fastTimeChargers}")
print(f"mediumTimeChargers: {mediumTimeChargers}")
print(f"slowTimeChargers: {slowTimeChargers}")
print(f"batteriesAvailable: {batteriesAvailable}")
print(f"costPerUnitChargeOfFast: {costPerUnitChargeOfFast}")
print(f"costPerUnitChargeOfMedium: {costPerUnitChargeOfMedium}")
print(f"costPerUnitChargeOfSlow: {costPerUnitChargeOfSlow}")
print(f"mxBatteryChargingStations: {mxBatteryChargingStations}")
print(f"mxBatterySwappingStations: {mxBatterySwappingStations}")
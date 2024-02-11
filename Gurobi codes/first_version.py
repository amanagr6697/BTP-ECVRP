n = 12  # number of clients
f = 5  # number of charging stations
xc = np.random.rand(n + f + 1) * 200
yc = np.random.rand(n + f + 1) * 100

# Randomly choose 5 indices
random_indices = np.random.choice(range(n + f + 1), f, replace=False)

charging_xc = xc[random_indices]
charging_yc = yc[random_indices]

# Remove the chosen points from xc and yc
xc = np.delete(xc, random_indices)
yc = np.delete(yc, random_indices)

# Add 10 copies of each charging station's coordinates to the charging array
charging_xc = np.repeat(charging_xc, 10)
charging_yc = np.repeat(charging_yc, 10)

# Combine the charging_xc and charging_yc into a single array
charging = np.column_stack((charging_xc, charging_yc))

# Shuffle the charging array while maintaining order
np.random.shuffle(charging)

charging_xc = charging[:, 0]
charging_yc = charging[:, 1]

print("Charging Stations' xc:", charging_xc)
print("Charging Stations' yc:", charging_yc)
print("Remaining xc:", xc)
print("Remaining yc:", yc)
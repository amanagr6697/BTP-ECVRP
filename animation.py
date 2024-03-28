import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation

# Define the nodes and connections
nodes = {
    0: (0, 0),
    1: (1, 1),
    2: (2, 2),
    3: (3, 1),
    4: (4, 0)
}

connections = [(0, 1), (1, 2), (2, 3), (3, 4)]

# Parse the output string into a list of nodes
path = [0, 1, 2, 3, 4]

# Create a function to update the animation
def update(num):
    plt.clf()
    plt.plot([nodes[path[num]][0]], [nodes[path[num]][1]], 'ro') # Plot current position
    plt.plot([nodes[path[i]][0] for i in range(num+1)], [nodes[path[i]][1] for i in range(num+1)], 'b-') # Plot path
    plt.xlim(-1, 5)
    plt.ylim(-1, 3)
    plt.gca().set_aspect('equal', adjustable='box')

# Create the animation
fig = plt.figure()
ani = animation.FuncAnimation(fig, update, frames=len(path), interval=1000, repeat=False)

plt.show()

# Installation of necessary packages command to execute in bash :
""" 
pip install swig
pip install gymnasium
pip install gymnasium[box2d]
"""

# Running python script : python Racing-Robot-test.py

""" Racing Robot Test """

import gymnasium as gym

# Create the environment 
env = gym.make('CarRacing-v3',render_mode='human')

# Reste the environment to initial state
observation, info = env.reset()

# print("Action space shape : ", env.action_space.shape)
# print("Action space bounds - Low : ", env.action_space.low)
# print("Action space bounds - High : ", env.action_space.high)

# Main Loop
for _ in range(10):
    # Render the environment for visual
    env.render()

    # Take a random action
    action = env.action_space.sample()

    # Execute the action
    observation, reward, terminated, truncated, info = env.step(action)

    # Check if the episode is done 
    if terminated or truncated:
        observation, info = env.reset()

# Close the environment
env.close()

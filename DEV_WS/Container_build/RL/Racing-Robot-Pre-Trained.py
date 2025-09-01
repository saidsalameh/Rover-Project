# First we need to install baseline3 packages
# pip install stable-baselines3

# export PATH=$PATH:/home/vboxuser/.local/bin
# echo 'export PATH=$PATH:/home/vboxuser/.local/bin' >> ~/.bashrc
# source ~/.bashrc
# pip install "numpy<2.0" --upgrade --user




import gymnasium as gym
from stable_baselines3 import PPO
import time

env = gym.make('CarRacing-v3',render_mode='human')

model = PPO("CnnPolicy", env, verbose=1)
# Train the model
model.learn(total_timesteps=10000)

# Save the model to a file
model.save("/home/vboxuser/Project-VM/DEV_WS/Container_build/RL/ppo_carracing_model")

# Load the pre-trained model
model = PPO.model("/home/vboxuser/Project-VM/DEV_WS/Container_build/RL/ppo_carracing_model")

observation, info = env.reset()

for _ in range(100):
    action, _states = model.predict(observation, deterministic=True)
    # Execute the action
    observation, reward, terminated, truncated, info = env.step(action)

    # Check if the episode is done 
    if terminated or truncated:
        observation, info = env.reset()

# Close the environment
env.close()
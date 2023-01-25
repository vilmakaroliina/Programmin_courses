import gym
import matplotlib.pyplot as plt
import pygame
import numpy as np
import matplotlib.pyplot as plyt

def plot_progress(averages, slippery_averages, c_averages):
    colors = ["bo-", "go-", "ro-", "co-", "mo-", "yo-", "ko-", "bo--", "go--", "ro--"]
    fig = plt.figure()
    fig.tight_layout(pad=5)
    ax1 = fig.add_subplot(311)
    ax2 = fig.add_subplot(312)
    ax3 = fig.add_subplot(313)


    for i in range(len(averages)):
        #fig = plt.figure()
        x = []
        y = []
        for l in averages[i]:
            x.append(l[0])
            y.append(l[1])

        ax1.plot(x, y, colors[i])

    for i in range(len(slippery_averages)):
        x = []
        y = []
        for l in slippery_averages[i]:
            x.append(l[0])
            y.append(l[1])
        print("x: ", x, "y: ", y)
        ax2.plot(x, y, colors[i])

    for i in range(len(c_averages)):
        x = []
        y = []
        for l in c_averages[i]:
            x.append(l[0])
            y.append(l[1])
        print("x: ", x, "y: ", y)
        ax3.plot(x, y, colors[i])

    ax1.set_ylabel("Average reward")
    ax3.set_xlabel("Episodes")
    ax2.set_ylabel("Average reward (slippery)")
    ax3.set_ylabel("Average reward")

    plt.show()
    return

def eval_policy(qtable_, num_of_episodes_, max_steps_, env):
    rewards = []

    for episode in range(num_of_episodes_):
        state, _ = env.reset()
        step = 0
        done = False
        total_rewards = 0

        for step in range(max_steps_):
            action = np.argmax(qtable_[state, :])
            new_state, reward, done, _, info = env.step(action)
            total_rewards += reward

            if done:
                rewards.append(total_rewards)
                break
            state = new_state

    avg_reward = sum(rewards) / num_of_episodes_
    return avg_reward

def trainin_c():
    env = gym.make("FrozenLake-v1", is_slippery=True, render_mode="human")

    env.reset()
    env.render()

    action_size = env.action_space.n
    state_size = env.observation_space.n

    averages = []

    total_episodes = 151
    max_steps = 50

    qtable = np.random.rand(state_size, action_size)

    for episode in range(total_episodes):
        state, _ = env.reset()
        done = False
        step = 0
        for steps in range(max_steps):
            action = np.random.randint(0, 4)
            new_state, reward, done, _, info = env.step(action)
            # nyt pitäs päivittää qtable jotenki
            qtable[state, action] += 0.5*(reward +  0.9* np.max(qtable[new_state]))
            state = new_state
            if done == True:
                break

        if episode % 10 == 0:
            avg_reward = eval_policy(qtable, 10, 50, env)
            list = [episode + 1, avg_reward]
            print(
                f'Average reward after episode {episode + 1} is {avg_reward}')
            averages.append(list)

    print(averages)
    env.close()

    return averages, qtable

def qtable_training(slippery):

    if slippery == "false":
        env = gym.make("FrozenLake-v1", is_slippery=False, render_mode="human")
    else:
        env = gym.make("FrozenLake-v1", is_slippery=True, render_mode="human")

    env.reset()
    env.render()

    action_size = env.action_space.n
    state_size = env.observation_space.n

    averages = []

    total_episodes = 151
    max_steps = 50

    qtable = np.random.rand(state_size, action_size)

    for episode in range(total_episodes):
        state, _ = env.reset()
        done = False
        step = 0
        for steps in range(max_steps):
            action = np.random.randint(0, 4)
            new_state, reward, done, _, info = env.step(action)
            # nyt pitäs päivittää qtable jotenki
            qtable[state, action] = reward + 0.9 * np.max(qtable[new_state])
            state = new_state
            if done == True:
                break

        if episode % 10 == 0:
            avg_reward = eval_policy(qtable, 10, 50, env)
            list = [episode + 1, avg_reward]
            print(
                f'Average reward after episode {episode + 1} is {avg_reward}')
            averages.append(list)

    print(averages)

    return averages, qtable


def main():
    # 0:Left 1:Down 2: Right, 3: Up

    non_slippery_averages = []
    slippery_averages = []
    c_averages = []

    for i in range(10):
        averages, non_slippery_qtable = qtable_training("false")
        non_slippery_averages.append(averages)

    for i in range(10):
        slip_averages, slippery_qtable = qtable_training("true")
        slippery_averages.append(slip_averages)

    for i in range(10):
        c_avg, qtable_c = trainin_c()
        c_averages.append(c_avg)


    plot_progress(non_slippery_averages, slippery_averages, c_averages)


main()
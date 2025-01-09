import gymnasium as gym
import balatro_gym
import numpy as np
import random
env = gym.make("Balatro-v0", render_mode="text")

# Clear the contents of cool.txt
with open("cool.txt", "w") as f:
    pass


def runner():
    obs, info = env.reset()
    deck = obs["deck"]
    hand = obs["hand"]
    playing_hand = np.zeros(53)
    played_cards = random.randint(1, 5)
    cards = 0
    
    actual_hand = info["state"].hand
    selected_cards = random.sample(actual_hand.cards, played_cards)
    sorted_cards = sorted(selected_cards, key=lambda x: int(x), reverse=True)

    with open("cool.txt", "a") as f:
        print(sorted_cards, file=f)

    for card in selected_cards:
        playing_hand[int(card)] = 1

    playing_hand = np.append(playing_hand, [0])  # Add action type (play=0)
    obs, reward, terminated, truncated, info = env.step(playing_hand)
    if reward == -10 or terminated:
        assert False
    # env.render()
for i in range(100_000):
    runner()
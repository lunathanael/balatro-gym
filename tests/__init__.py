import unittest
from timeit import default_timer as timer

import gymnasium as gym
import balatro_gym
import numpy as np
import random
env = gym.make("Balatro-v0", render_mode="text")


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

    for card in selected_cards:
        playing_hand[int(card)] = 1

    playing_hand = np.append(playing_hand, [0])  # Add action type (play=0)
    obs, reward, terminated, truncated, info = env.step(playing_hand)
    if reward == -10 or terminated:
        self.fail()
    # env.render()

    
class TestBalatroGame(unittest.TestCase):
    def test_runner(self):
        for i in range(100_000):
            runner()

if __name__ == "__main__":
    unittest.main()
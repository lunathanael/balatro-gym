import gymnasium as gym
import balatro_gym as bg
import numpy as np
import random
env = gym.make("Balatro-v0", render_mode="text")


def runner():
    obs, info = env.reset()
    deck = obs["deck"]
    hand = obs["hand"]
    played_cards = random.randint(1, 5)
    cards = 0
    
    actual_hand = info["state"].hand
    selected_cards = random.sample(actual_hand.cards, played_cards)

    playing_hand = np.zeros(52)
    for card in selected_cards:
        playing_hand[bg.utils.card_to_index(card)] = 1

    _ph = playing_hand.reshape(4, 13)
    
    for card in selected_cards:
        assert(_ph[int(card.suit)][int(card.rank)] == 1)
 # Add action type (play=0)
    obs, reward, terminated, truncated, info = env.step((playing_hand, False))
    if reward == -10 or terminated:
        assert False
    # env.render()
for i in range(100_000):
    runner()
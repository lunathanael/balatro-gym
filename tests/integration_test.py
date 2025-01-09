import gymnasium as gym
import balatro_gym as bg
import numpy as np
import random
env = gym.make("Balatro-v0", render_mode="text")

SEED = 42
random.seed(SEED)
np.random.seed(SEED)


def runner():
    obs, info = env.reset(seed=SEED)
    deck = obs["deck"]
    hand = obs["hand"]

    played_cards = random.randint(1, 5)
    is_discard = random.random() < 0.5
    actual_hand = info["state"].hand

    selected_cards = random.sample(actual_hand.cards, played_cards)
    selected_cards = sorted(selected_cards, key=lambda x: int(x), reverse=True)

    pred_score = bg.core.score_cards(selected_cards)
    if is_discard:
        pred_score = 0

    playing_hand = np.zeros(52, dtype=np.bool)
    for card in selected_cards:
        playing_hand[bg.utils.card_to_index(card)] = 1

    _ph = playing_hand.reshape(4, 13)
    
    for card in selected_cards:
        assert _ph[int(card.suit)][int(card.rank)] == True
        assert obs["hand"][int(card.suit)][int(card.rank)] == True

    # env.render()
    action = (playing_hand, is_discard)
    obs, reward, terminated, truncated, info = env.step(action)
    if reward == -10 or terminated:
        assert False
    print(reward)
    
    assert reward == pred_score


for i in range(100_000):
    runner()
from typing import Any, Dict, Tuple, Optional
import numpy as np
import gymnasium as gym
from gymnasium import spaces

from balatro_gym.core import GameState, Cards
from balatro_gym.environments import utils
class BalatroEnv(gym.Env):
    """Balatro Playing Environment
    
    A Gymnasium environment for playing Balatro, implementing the standard interface.
    """
    metadata = {"render_modes": ["text", "human"]}

    def __init__(self, render_mode: str = "text"):

        self.observation_space = spaces.Box(low=0, high=4, shape=(13 + 4 + 1 + 2,), dtype=np.int8)

        self.game_state: Optional[GameState] = None
        self.hand: Optional[np.ndarray] = None
        self.deck: Optional[np.ndarray] = None
        # Actions: card selection (0-4) and play type
        self.action_space = spaces.Discrete(54)
        
        self.render_mode = render_mode
        if self.render_mode not in self.metadata["render_modes"]:
            raise ValueError(f"Invalid render mode: {self.render_mode}")

        self.reset()

    def reset(self, *, seed: Optional[int] = None, options: Optional[Dict] = None) -> Tuple[Dict[str, Any], Dict[str, Any]]:
        super().reset(seed=seed)
        self.length = 0

        self.selected = np.zeros(52, dtype=np.int8)
        self.selected_count = 0
        self.score = 0
        self.last_rank = None
        
        # if seed is not None:
        #     self.game_state = GameState(seed=seed)
        # else:
        #     self.game_state = GameState()
        
        self.game_state = GameState(42069)
        # self.game_state.hands = 4
        observation = self._get_obs()
        info = self._get_info()
        
        return observation, info

    def step(self, action: int) -> Tuple[Dict[str, Any], float, bool, bool, Dict[str, Any]]:
        truncated = False
        terminated = self.game_state.is_terminal()

        self.length += 1
        if self.length > 30:
            truncated = True

        if action == 52 or action == 53:
            if self.selected_count == 0:
                return self._get_obs(), 0, terminated, truncated, self._get_info()
            
            if action == 53 and self.game_state.discards == 0:
                return self._get_obs(), 0, terminated, truncated, self._get_info()
            
            action_int = 0
            actual_hand = self.game_state.hand
            cards_selected = []
            for i in range(8):
                if self.selected[utils.card_to_index(actual_hand[i])]:
                    cards_selected.append(actual_hand[i])
                    action_int += 1 << i

            if action == 52:
                reward = self.game_state.play(action_int)
            else:
                self.game_state.discard(action_int)
                reward = 0
            # print(f"Play {cards_selected} for {reward} points")

            self.selected = np.zeros(52, dtype=np.int8)
            self.selected_count = 0
            self.last_rank = None
            
            terminated = self.game_state.is_terminal()
            reward += 0.1
            self.score += reward

            return self._get_obs(), reward, terminated, truncated, self._get_info()

        if self.selected_count == 5:
            return self._get_obs(), 0, terminated, truncated, self._get_info()

        if not self.hand[action] or self.selected[action]:
            # print("Invalid action mask: card not in hand")
            return self._get_obs(), 0, terminated, truncated, self._get_info()

        card = utils.index_to_card(action)
        rank = int(card.rank)
        if self.last_rank is not None and rank < self.last_rank:
            return self._get_obs(), 0, terminated, truncated, self._get_info()
        self.last_rank = rank

        self.selected[action] = 1
        self.selected_count += 1

        observation = self._get_obs()
        info = self._get_info()
        self.score += 0.1
        return observation, 0.1, terminated, truncated, info

    def _get_obs(self) -> Dict[str, Any]:
        """Get the current observation."""
        self.hand = np.zeros((52,), dtype=np.int8)
        self.deck = np.zeros((52,), dtype=np.int8)

        self.hand_ranks = np.zeros((13,), dtype=np.int8)
        self.hand_suits = np.zeros((4,), dtype=np.int8)
        self.deck_ranks = np.zeros((13,), dtype=np.int8)
        self.deck_suits = np.zeros((4,), dtype=np.int8)

        for card in self.game_state.hand:
            self.hand[utils.card_to_index(card)] = 1
            self.hand_ranks[int(card.rank)] += 1
            self.hand_suits[int(card.suit)] += 1

        for card in self.game_state.deck:
            self.deck[utils.card_to_index(card)] = 1
            self.deck_ranks[int(card.rank)] += 1
            self.deck_suits[int(card.suit)] += 1

        selected_count = np.zeros((1,), dtype=np.int8)
        selected_count[0] = self.selected_count

        hand_obs = self.hand
        hand_obs[self.selected] = 0

        hand_discard_count = np.zeros((2,), dtype=np.int8)
        hand_discard_count[0] = self.game_state.hands
        hand_discard_count[1] = self.game_state.discards

        obs = np.concatenate([self.hand, self.selected, self.hand_ranks, self.hand_suits, selected_count, hand_discard_count])

        return obs

    def _get_info(self) -> Dict[str, Any]:
        """Get additional information about the current state."""
        info = {
            "score" : self.score,
            "state" : self.game_state,
        }

        if self.game_state.is_terminal() or self.length > 30:
            info["final_info"] = {
                "r" : self.score,
                "raw_r" : self.game_state.score,
                "l" : self.length,
            }

        return info

    def render(self):
        """Render the current state."""
        if self.render_mode == "text":
            print("Hand: ", self.game_state.hand)
            print("Deck: ", self.game_state.deck)
            print("Hands: ", self.game_state.hands)
            print("Discards: ", self.game_state.discards)
            print("Score: ", self.game_state.score)
            print("Is terminal: ", self.game_state.is_terminal())
            print("--------------------------------")

        elif self.render_mode == "human":
            # TODO: Implement human rendering
            pass 
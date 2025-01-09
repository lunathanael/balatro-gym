from typing import Any, Dict, Tuple, Optional
import numpy as np
import gymnasium as gym
from gymnasium import spaces

from balatro_gym.core import GameState
from balatro_gym.environments import utils
class BalatroEnv(gym.Env):
    """Balatro Playing Environment
    
    A Gymnasium environment for playing Balatro, implementing the standard interface.
    """
    metadata = {"render_modes": ["text", "human"]}

    def __init__(self, render_mode: str = "text"):

        self.observation_space = spaces.Dict({
            "hand": spaces.Box(low=0, high=1, shape=(4, 13,), dtype=np.bool),  # 5 cards in hand as one-hot encoding
            "hands": spaces.Discrete(8, start=0),  # number of hands left as scalar (0-10)
            "deck": spaces.Box(low=0, high=1, shape=(4, 13,), dtype=np.bool),  # remaining cards in deck as one-hot encoding
            "discards": spaces.Discrete(8, start=0),  # number of discards left as scalar (0-10)
        })

        self.game_state: Optional[GameState] = None
        self.hand: Optional[np.ndarray] = None
        self.deck: Optional[np.ndarray] = None
        # Actions: card selection (0-4) and play type
        self.action_space = spaces.Tuple((
            spaces.Box(low=0, high=1, shape=(52,), dtype=np.bool),  # One-hot encoded card selection
            spaces.Discrete(2)  # Boolean flag for discard vs play
        ))
        
        self.render_mode = render_mode
        if self.render_mode not in self.metadata["render_modes"]:
            raise ValueError(f"Invalid render mode: {self.render_mode}")

        self.reset()

    def reset(self, *, seed: Optional[int] = None, options: Optional[Dict] = None) -> Tuple[Dict[str, Any], Dict[str, Any]]:
        super().reset(seed=seed)
        
        if seed is not None:
            self.game_state = GameState(seed)
        else:
            self.game_state = GameState()
        
        observation = self._get_obs()
        info = self._get_info()
        
        return observation, info

    def step(self, action: tuple[np.ndarray, bool]) -> Tuple[Dict[str, Any], float, bool, bool, Dict[str, Any]]:
        truncated = False
        action_mask, is_discard = action

        hand = self.hand.flatten()

        # check invalid action
        if is_discard and self.game_state.discards == 0:
            terminated = True
            return self._get_obs(), -10, terminated, truncated, self._get_info()
        if np.sum(action_mask) > 5 or np.sum(action_mask) < 1:
            terminated = True
            return self._get_obs(), -10, terminated, truncated, self._get_info()
        if np.any(np.logical_and(action_mask, np.logical_not(hand))):
            terminated = True
            return self._get_obs(), -10, terminated, truncated, self._get_info()

        action_int = 0
        for i in range(8):
            card = self.game_state.hand[i]
            if action_mask[utils.card_to_index(card)]:
                action_int += 1 << i

        reward = 0
        if is_discard:
            self.game_state.discard(action_int)
        else:
            reward += self.game_state.play(action_int)

        terminated = self.game_state.is_terminal()
        
        observation = self._get_obs()
        info = self._get_info()
        
        return observation, reward, terminated, truncated, info

    def _get_obs(self) -> Dict[str, Any]:
        """Get the current observation."""
        self.hand = np.zeros((4, 13), dtype=np.bool)
        self.deck = np.zeros((4, 13), dtype=np.bool)

        for card in self.game_state.hand:
            self.hand[int(card.suit)][int(card.rank)] = 1

        for card in self.game_state.deck:
            self.deck[int(card.suit)][int(card.rank)] = 1

        return {
            "hand" : self.hand,
            "hands" : self.game_state.hands,
            "deck" : self.deck,
            "discards" : self.game_state.discards,
        }

    def _get_info(self) -> Dict[str, Any]:
        """Get additional information about the current state."""
        return {
            "score" : self.game_state.score,
            "state" : self.game_state,
        }

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
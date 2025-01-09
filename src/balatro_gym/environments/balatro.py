from typing import Any, Dict, Tuple, Optional
import numpy as np
import gymnasium as gym
from gymnasium import spaces

from balatro_gym.core import GameState

class BalatroEnv(gym.Env):
    """Balatro Playing Environment
    
    A Gymnasium environment for playing Balatro, implementing the standard interface.
    """
    metadata = {"render_modes": ["text", "human"]}

    def __init__(self, render_mode: str = "text"):
        self.observation_space = spaces.Dict({
            "hand": spaces.Box(low=0, high=1, shape=(52,), dtype=np.bool),  # 5 cards in hand as one-hot encoding
            "hands": spaces.Discrete(11, start=0),  # number of hands left as scalar (0-10)
            "deck": spaces.Box(low=0, high=1, shape=(52,), dtype=np.bool),  # remaining cards in deck as one-hot encoding
            "discards": spaces.Discrete(11, start=0),  # number of discards left as scalar (0-10)
        })

        self.game_state: Optional[GameState] = None
        self.hand: Optional[np.ndarray] = None
        self.deck: Optional[np.ndarray] = None
        # Actions: card selection (0-4) and play type
        self.action_space = spaces.Box(low=0, high=1, shape=(53,), dtype=np.bool)  # One-hot encoded action space
        
        self.render_mode = render_mode
        if self.render_mode not in self.metadata["render_modes"]:
            raise ValueError(f"Invalid render mode: {self.render_mode}")

        self.reset()

    def reset(self, *, seed: Optional[int] = None, options: Optional[Dict] = None) -> Tuple[Dict[str, Any], Dict[str, Any]]:
        super().reset(seed=seed)
        
        if seed is not None:
            self.game_state = GameState(seed=seed)
        else:
            self.game_state = GameState()
        
        observation = self._get_obs()
        info = self._get_info()
        
        return observation, info

    def step(self, action: np.ndarray) -> Tuple[Dict[str, Any], float, bool, bool, Dict[str, Any]]:
        # Execute action (play card)
        truncated = False  # Episode truncated due to time limit

        action_mask = action[:52]

        # check invalid action
        if np.sum(action_mask) > 5 or np.sum(action_mask) < 1:
            terminated = True
            return self._get_obs(), -10, terminated, truncated, self._get_info()
        if np.any(np.logical_and(action_mask, np.logical_not(self.hand))):
            terminated = True
            return self._get_obs(), -10, terminated, truncated, self._get_info()

        hand_indices = np.where(self.hand == 1)[0]
        action_indices = np.where(action_mask == 1)[0]

        play_mask = [1 if x in action_indices else 0 for x in hand_indices]
        action_int = sum(bit << i for i, bit in enumerate(reversed(play_mask)))
        
        action_type = action[52]

        reward = 0
        if action_type == 1:
            self.game_state.discard(action_int)
        else:
            reward += self.game_state.play(action_int)

        terminated = self.game_state.is_terminal()
        
        observation = self._get_obs()
        info = self._get_info()
        
        return observation, reward, terminated, truncated, info

    def _get_obs(self) -> Dict[str, Any]:
        """Get the current observation."""
        self.hand = np.zeros(52, dtype=np.bool)
        self.deck = np.zeros(52, dtype=np.bool)

        for card in self.game_state.hand:
            self.hand[int(card)] = 1

        for card in self.game_state.deck:
            self.deck[int(card)] = 1

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
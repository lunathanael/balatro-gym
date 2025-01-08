from typing import Any, Dict, Tuple, Optional
import numpy as np
import gymnasium as gym
from gymnasium import spaces

from balatro_gym.core import GameState

class BalatroEnv(gym.Env):
    """Balatro Playing Environment
    
    A Gymnasium environment for playing Balatro, implementing the standard interface.
    """
    metadata = {"render_modes": ["human", "rgb_array"], "render_fps": 4}

    def __init__(self, render_mode: Optional[str] = None):
        self.observation_space = spaces.Dict({
            "hand": spaces.Box(low=0, high=1, shape=(52,), dtype=np.int32),  # 5 cards in hand as one-hot encoding
            "hands": spaces.Discrete(11, start=0),  # number of hands left as scalar (0-10)
            "deck": spaces.Box(low=0, high=1, shape=(52,), dtype=np.int32),  # remaining cards in deck as one-hot encoding
            "discards": spaces.Discrete(11, start=0),  # number of discards left as scalar (0-10)
        })

        self.game_state: Optional[GameState] = None
        self.hand: Optional[np.ndarray] = None
        self.deck: Optional[np.ndarray] = None
        # Actions: card selection (0-4) and play type
        self.action_space = spaces.Box(low=0, high=1, shape=(53,), dtype=np.int32)  # One-hot encoded action space
        
        
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

        
        action_indices = np.where(action[:52] == 1)[0]
        hand_indices = np.where(self.hand == 1)[0]
        valid_plays = np.intersect1d(action_indices, hand_indices)

        action_int = 0
        
        action_type = action[52]

        if action_type == 1:
            reward = self.game_state.discard(action_int)
        else:
            reward = self.game_state.play(action_int)

        terminated = self.game_state.is_terminal()
        
        observation = self._get_obs()
        info = self._get_info()
        
        return observation, reward, terminated, truncated, info

    def _get_obs(self) -> Dict[str, Any]:
        """Get the current observation."""
        self.hand = np.zeros(52, dtype=np.int32)
        self.deck = np.zeros(52, dtype=np.int32)

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
        }

    def render(self):
        """Render the current state."""
        if self.render_mode == "human":
            # TODO: Implement human rendering
            pass
        elif self.render_mode == "rgb_array":
            # TODO: Implement rgb_array rendering
            pass 
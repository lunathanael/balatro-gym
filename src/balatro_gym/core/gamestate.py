from __future__ import annotations
from typing import TYPE_CHECKING, List

from .types import Card
from .hand import Hand

class GameState:
    """
    A Python interface for the C++ GameState class.

    Attributes:
    -----------
    deck : List[Card]
        The deck of cards.
    hand : Hand
        The current hand.
    score : int
        The current score.
    hands : int
        Number of hands played.
    discards : int
        Number of discards used.

    Methods:
    --------
    play(self, action: int) -> int
        Play a card from the hand.
    discard(self, action: int)
        Discard a card from the hand.
    """

    @property
    def deck(self) -> List[Card]:
        pass

    @deck.setter
    def deck(self, value: List[Card]) -> None:
        pass

    @property
    def hand(self) -> Hand:
        pass

    @hand.setter
    def hand(self, value: Hand) -> None:
        pass

    @property
    def score(self) -> int:
        pass

    @score.setter
    def score(self, value: int) -> None:
        pass

    @property
    def hands(self) -> int:
        pass

    @hands.setter
    def hands(self, value: int) -> None:
        pass

    @property
    def discards(self) -> int:
        pass

    @discards.setter
    def discards(self, value: int) -> None:
        pass

    def __init__(self, seed: int | None = None):
        pass

    def play(self, action: int) -> int:
        pass

    def discard(self, action: int) -> None:
        pass

    def is_terminal(self) -> bool:
        pass

if not TYPE_CHECKING:
    from balatro_gym._core import GameState as CppGameState
    GameState = CppGameState

__all__ = ["GameState"] 
from __future__ import annotations
from typing import TYPE_CHECKING
from array import array

from .types import Card

class Hand:
    """
    A Python interface for the C++ Hand class.

    Attributes:
    -----------
    cards : array[Card]
        Array of 8 cards in the hand.

    Methods:
    --------
    sort(self)
        Sort the cards in the hand.
    __getitem__(self, index: int) -> Card
        Get a card at the specified index.
    __setitem__(self, index: int, card: Card)
        Set a card at the specified index.
    """

    size: int = 8

    @property
    def cards(self) -> array[Card]:
        pass

    @cards.setter
    def cards(self, value: array[Card]) -> None:
        pass

    def __init__(self, cards: array[Card] | None = None):
        pass

    def sort(self) -> None:
        pass

    def __getitem__(self, index: int) -> Card:
        pass

    def __setitem__(self, index: int, card: Card) -> None:
        pass

if not TYPE_CHECKING:
    from balatro_gym._core import Hand as CppHand
    Hand = CppHand

__all__ = ["Hand"] 
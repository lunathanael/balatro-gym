from __future__ import annotations
from typing import TYPE_CHECKING, List

from .types import Card

def score_cards(cards: List[Card]) -> int:
    """
    Score a collection of cards.

    Parameters:
    -----------
    cards : List[Card]
        The cards to score.

    Returns:
    --------
    int
        The score for the cards.
    """
    pass

def calculate_table() -> None:
    """
    Calculate the scoring table.
    """
    pass

if not TYPE_CHECKING:
    from balatro_gym._core import score_cards as cpp_score_cards
    from balatro_gym._core import calculate_table as cpp_calculate_table

    score_cards = cpp_score_cards
    calculate_table = cpp_calculate_table

__all__ = [
    "score_cards",
    "calculate_table",
] 
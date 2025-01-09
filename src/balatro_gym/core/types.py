from __future__ import annotations
from typing import TYPE_CHECKING

class Suit:
    """
    A Python interface for the C++ Suit enum.

    Attributes:
    -----------
    Diamonds : Suit
    Clubs : Suit
    Hearts : Suit
    Spades : Suit
    NUMBER_OF_SUITS : Suit
    NO_SUIT : Suit
    """
    Diamonds: Suit
    Clubs: Suit
    Hearts: Suit
    Spades: Suit
    NUMBER_OF_SUITS: Suit
    NO_SUIT: Suit

class Rank:
    """
    A Python interface for the C++ Rank enum.

    Attributes:
    -----------
    Two : Rank
    Three : Rank
    Four : Rank
    Five : Rank
    Six : Rank
    Seven : Rank
    Eight : Rank
    Nine : Rank
    Ten : Rank
    Jack : Rank
    Queen : Rank
    King : Rank
    Ace : Rank
    NUMBER_OF_RANKS : Rank
    NO_RANK : Rank
    """
    Two: Rank
    Three: Rank
    Four: Rank
    Five: Rank
    Six: Rank
    Seven: Rank
    Eight: Rank
    Nine: Rank
    Ten: Rank
    Jack: Rank
    Queen: Rank
    King: Rank
    Ace: Rank
    NUMBER_OF_RANKS: Rank
    NO_RANK: Rank

class Card:
    """
    A Python interface for the C++ Card class.

    Attributes:
    -----------
    rank : Rank
        The rank of the card.
    suit : Suit
        The suit of the card.

    Methods:
    --------
    __init__(self, rank: Rank, suit: Suit)
        Initialize the card with a rank and suit.
    __int__(self) -> int
        Convert the card to an integer.
    """

    @property
    def rank(self) -> Rank:
        pass

    @rank.setter
    def rank(self, value: Rank) -> None:
        pass

    @property
    def suit(self) -> Suit:
        pass

    @suit.setter
    def suit(self, value: Suit) -> None:
        pass

    def __init__(self, rank: Rank, suit: Suit):
        pass

    def __int__(self) -> int:
        pass
    
class Cards:
    """
    A Python interface for predefined card constants.

    Contains all 52 standard playing cards as constants, named in the format
    {rank}Of{suit}, e.g. AceOfSpades, TwoOfHearts, etc.

    Also contains No_Card as a sentinel value.
    """
    AceOfClubs: Card
    TwoOfClubs: Card  
    ThreeOfClubs: Card
    FourOfClubs: Card
    FiveOfClubs: Card
    SixOfClubs: Card
    SevenOfClubs: Card
    EightOfClubs: Card
    NineOfClubs: Card
    TenOfClubs: Card
    JackOfClubs: Card
    QueenOfClubs: Card
    KingOfClubs: Card

    AceOfDiamonds: Card
    TwoOfDiamonds: Card
    ThreeOfDiamonds: Card
    FourOfDiamonds: Card
    FiveOfDiamonds: Card
    SixOfDiamonds: Card
    SevenOfDiamonds: Card
    EightOfDiamonds: Card
    NineOfDiamonds: Card
    TenOfDiamonds: Card
    JackOfDiamonds: Card
    QueenOfDiamonds: Card
    KingOfDiamonds: Card

    AceOfHearts: Card
    TwoOfHearts: Card
    ThreeOfHearts: Card
    FourOfHearts: Card
    FiveOfHearts: Card
    SixOfHearts: Card
    SevenOfHearts: Card
    EightOfHearts: Card
    NineOfHearts: Card
    TenOfHearts: Card
    JackOfHearts: Card
    QueenOfHearts: Card
    KingOfHearts: Card

    AceOfSpades: Card
    TwoOfSpades: Card
    ThreeOfSpades: Card
    FourOfSpades: Card
    FiveOfSpades: Card
    SixOfSpades: Card
    SevenOfSpades: Card
    EightOfSpades: Card
    NineOfSpades: Card
    TenOfSpades: Card
    JackOfSpades: Card
    QueenOfSpades: Card
    KingOfSpades: Card

    No_Card: Card


if not TYPE_CHECKING:
    from balatro_gym._core import Suit as CppSuit, Rank as CppRank, Card as CppCard, Cards as CppCards

    Suit = CppSuit
    Rank = CppRank
    Card = CppCard
    Cards = CppCards

__all__ = [
    "Suit",
    "Rank",
    "Card",
    "Cards",
]

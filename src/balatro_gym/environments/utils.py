from balatro_gym.core import Card, Suit, Rank

def card_to_index(card: Card) -> int:
    suit: Suit = card.suit
    rank: Rank = card.rank
    return int(suit) * 13 + int(rank)

def index_to_card(index: int) -> Card:
    suit = Suit(index // 13)
    rank = Rank(index % 13)
    return Card(rank, suit)
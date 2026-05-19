#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <iostream>
#include <vector>


using namespace std;

class hand {
private:
  vector<card> cards;

public:
  hand() = default;

  // Add a card
  void addCard(const card &c) { cards.push_back(c); }

  // Clear hand
  void empty() { cards.clear(); }

  // Compute Blackjack score
  int calculateScore() const {
    int score = 0;
    int aces = 0;

    for (const card &c : cards) {
      score += c.getNumber();
      if (c.isAs())
        aces++;
    }

    while (score > 21 && aces > 0) {
      score -= 10;
      aces--;
    }
    return score;
  }

  // Display full hand
  void afficher() const {
    for (const card &c : cards)
      cout << c.getNumber() << " ";
    cout << "| Score = " << calculateScore() << endl;
  }

  // Display dealer hand (hide hole card)
  void afficherDealer() const {
    if (cards.empty())
      return;
    cout << cards[0].getNumber() << " ? | Score = ?" << endl;
  }

  // ---- Strategy helpers ----

  // True if exactly two equal cards
  bool isPair() const {
    return cards.size() == 2 && cards[0].getNumber() == cards[1].getNumber();
  }

  // True if hand is soft (Ace counted as 11)
  bool isSoft() const {
    int score = 0;
    bool ace = false;

    for (const card &c : cards) {
      score += c.getNumber();
      if (c.isAs())
        ace = true;
    }
    return ace && score <= 21;
  }

  // Value of first card (for pairs)
  int firstCardValue() const { return cards[0].getNumber(); }

  // Soft value without Ace (A-7 → 7)
  int softValueWithoutAce() const {
    for (const card &c : cards)
      if (!c.isAs())
        return c.getNumber();
    return 0;
  }

  // Dealer up-card
  int getFirstCardValue() const { return cards[0].getNumber(); }

  const vector<card> &getCards() const { return cards; }
};

#endif

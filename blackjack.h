#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "deck.h"
#include "player.h"
#include "strategy.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>


using namespace std;
#include <string>
#include <vector>


struct GameState {
  vector<int> playerHand;
  vector<int> dealerHand;
  int playerScore;
  int dealerScore;
  bool gameOver;
  string message;
  string recommendation;
};

class blackjack {
private:
  player joueur;
  player dealer;
  deck shoe;
  bool infiniteDeck;

  card drawCard() {
    if (infiniteDeck) {
      static random_device rd;
      static mt19937 generator(rd());
      static uniform_int_distribution<int> distribution(0, 12);
      int values[13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
      return card(values[distribution(generator)]);
    }
    return shoe.draw();
  }

public:
  blackjack(int n, bool infinite) : shoe(n), infiniteDeck(infinite) {}

  Move getBestMove(const hand &h, int dealerUp) {
    int total = h.calculateScore();
    if (total == 21)
      return STAND;

    int d = (dealerUp == 11) ? 9 : dealerUp - 2;

    if (h.isPair())
      return pairStrategy[h.firstCardValue()][d];
    if (h.isSoft())
      return softStrategy[h.softValueWithoutAce()][d];

    if (total >= 17)
      return STAND;

    return hardStrategy[total][d];
  }

  void distribute() {
    joueur.addCard(drawCard());
    dealer.addCard(drawCard());
    joueur.addCard(drawCard());
    dealer.addCard(drawCard());

    joueur.afficher();
    dealer.afficherDealer();

    if (!infiniteDeck)
      cout << "Penetration: " << shoe.penetration() << "%\n";
    else
      cout << "Deck mode: INFINITE\n";
  }

  void playerTurn() {
    while (true) {
      cout << "\nPlayer: ";
      joueur.afficher();

      Move advice = getBestMove(joueur.getHand(), dealer.getUpCard());
      cout << "Recommended: " << moveToString(advice) << endl;

      if (joueur.calculateScore() >= 21)
        break;

      int choice;
      cout << "1. Hit  2. Stand: ";
      cin >> choice;

      if (choice == 1) {
        joueur.addCard(drawCard());
        cout << "After hit → ";
        joueur.afficher();

        if (joueur.calculateScore() > 21) {
          cout << "Bust!\n";
          break;
        }
      } else
        break;
    }
  }

  void dealerTurn() {
    while (dealer.calculateScore() < 17)
      dealer.addCard(drawCard());
  }

  void result() {
    joueur.afficher();
    dealer.afficher();

    int ps = joueur.calculateScore();
    int ds = dealer.calculateScore();

    if (ps > 21)
      cout << "Dealer wins\n";
    else if (ds > 21)
      cout << "Player wins\n";
    else if (ps > ds)
      cout << "Player wins\n";
    else if (ps < ds)
      cout << "Dealer wins\n";
    else
      cout << "Draw\n";
  }

  void cheatMode() {
    hand h;
    int dealerUp, n;

    cout << "\n=== CHEAT MODE ===\n";
    cout << "How many cards? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
      int v;
      cout << "Enter card value: ";
      cin >> v;
      h.addCard(card(v));
    }

    cout << "Dealer up-card: ";
    cin >> dealerUp;

    while (true) {
      h.afficher();

      if (h.calculateScore() == 21) {
        cout << "BLACKJACK → STAND\n";
        break;
      }

      Move advice = getBestMove(h, dealerUp);
      cout << "Recommended: " << moveToString(advice) << endl;

      if (advice != HIT)
        break;

      int next;
      cout << "Next card: ";
      cin >> next;
      h.addCard(card(next));
    }
  }

  void play() {
    joueur.reset();
    dealer.reset();
    distribute();

    if (joueur.calculateScore() == 21) {
      cout << "BLACKJACK!\n";
      return;
    }

    playerTurn();
    dealerTurn();
    result();
  }

  // --- API Methods ---

  GameState getGameState(bool gameOver = false) {
    GameState state;
    const auto &pCards = joueur.getHand().getCards();
    for (const auto &c : pCards)
      state.playerHand.push_back(c.getNumber());

    const auto &dCards = dealer.getHand().getCards();
    if (gameOver || dCards.empty()) {
      for (const auto &c : dCards)
        state.dealerHand.push_back(c.getNumber());
      state.dealerScore = dealer.calculateScore();
    } else {
      // Only show first card + 0 for hidden
      state.dealerHand.push_back(dCards[0].getNumber());
      state.dealerHand.push_back(0); // 0 represents hidden card
      state.dealerScore = 0;         // Hide score
    }

    state.playerScore = joueur.calculateScore();
    state.gameOver = gameOver;

    if (!gameOver && !state.playerHand.empty() && !dCards.empty()) {
      Move advice = getBestMove(joueur.getHand(), dealer.getUpCard());
      state.recommendation = moveToString(advice);
    } else {
      state.recommendation = "";
    }

    return state;
  }

  GameState startGameState(int decks, bool infinite) {
    infiniteDeck = infinite;
    if (!infinite)
      shoe = deck(decks); // Reset deck

    joueur.reset();
    dealer.reset();

    // Distribute
    joueur.addCard(drawCard());
    dealer.addCard(drawCard());
    joueur.addCard(drawCard());
    dealer.addCard(drawCard());

    bool blackjack = (joueur.calculateScore() == 21);
    GameState state = getGameState(blackjack);
    if (blackjack) {
      state.message = "Blackjack! You win!";
      state.gameOver = true;
    } else {
      state.message = "Game started";
      state.gameOver = false;
    }
    return state;
  }

  GameState hitState() {
    joueur.addCard(drawCard());
    bool bust = (joueur.calculateScore() > 21);
    GameState state = getGameState(bust);
    if (bust) {
      state.message = "Bust! You lose.";
    } else {
      state.message = "Hit";
    }
    return state;
  }

  GameState standState() {
    while (dealer.calculateScore() < 17)
      dealer.addCard(drawCard());

    GameState state = getGameState(true);

    int ps = joueur.calculateScore();
    int ds = dealer.calculateScore();

    if (ps > 21)
      state.message = "Dealer wins (Player Bust)";
    else if (ds > 21)
      state.message = "Player wins (Dealer Bust)";
    else if (ps > ds)
      state.message = "Player wins";
    else if (ps < ds)
      state.message = "Dealer wins";
    else
      state.message = "Draw";

    return state;
  }
};

#endif

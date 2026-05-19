#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

class deck {
private:
    vector<card> cards;
    int numDecks;

    void shuffleDeck() {
        random_device rd;
        mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);
    }

public:
    deck(int n = 2) : numDecks(n) {
        init();
    }

    void init() {
        cards.clear();
        int values[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

        for (int d = 0; d < numDecks; d++)
            for (int s = 0; s < 4; s++)
                for (int i = 0; i < 13; i++)
                    cards.push_back(card(values[i]));

        shuffleDeck();
        cout << "\n[RESHUFFLE] Deck reshuffled (" << cards.size() << " cards)\n";
    }

    card draw() {
        if (cards.empty())
            init();

        card c = cards.back();
        cards.pop_back();
        return c;
    }

    int totalCards() const { return numDecks * 52; }
    int cardsUsed() const { return totalCards() - cards.size(); }
    double penetration() const {
        return (double)cardsUsed() / totalCards() * 100.0;
    }
};

#endif

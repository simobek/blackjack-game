#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

class player {
private:
    hand h;

public:
    void addCard(const card& c) { h.addCard(c); }
    int calculateScore() const { return h.calculateScore(); }
    void afficher() const { h.afficher(); }
    void afficherDealer() const { h.afficherDealer(); }
    void reset() { h.empty(); }

    const hand& getHand() const { return h; }
    int getUpCard() const { return h.getFirstCardValue(); }
};

#endif

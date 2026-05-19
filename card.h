#ifndef CARD_H
#define CARD_H

class card {
private:
    int value; // 2–10, 11 = Ace

public:
    card(int v) : value(v) {}

    int getNumber() const {
        return value;
    }

    bool isAs() const {
        return value == 11;
    }
};

#endif

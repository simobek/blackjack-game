#ifndef STRATEGY_H
#define STRATEGY_H

enum Move {
    HIT,
    STAND,
    DOUBLE,
    SPLIT
};

inline const char* moveToString(Move m) {
    switch (m) {
        case HIT:    return "HIT";
        case STAND:  return "STAND";
        case DOUBLE: return "DOUBLE DOWN";
        case SPLIT:  return "SPLIT";
    }
    return "";
}

// Dealer columns: 2 3 4 5 6 7 8 9 10 A
// Index:           0 1 2 3 4 5 6 7  8 9

// =====================
// HARD TOTALS (8–17)
// index = hard total
// =====================
static Move hardStrategy[18][10] = {
    {},{},{},{},{},{},{}, {},

    // 8
    {HIT,HIT,HIT,HIT,HIT,HIT,HIT,HIT,HIT,HIT},

    // 9
    {HIT,HIT,DOUBLE,DOUBLE,DOUBLE,HIT,HIT,HIT,HIT,HIT},

    // 10
    {DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,HIT,HIT},

    // 11
    {DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE},

    // 12
    {HIT,HIT,STAND,STAND,STAND,HIT,HIT,HIT,HIT,HIT},

    // 13
    {STAND,STAND,STAND,STAND,STAND,HIT,HIT,HIT,HIT,HIT},

    // 14
    {STAND,STAND,STAND,STAND,STAND,HIT,HIT,HIT,HIT,HIT},

    // 15
    {STAND,STAND,STAND,STAND,STAND,HIT,HIT,HIT,HIT,HIT},

    // 16
    {STAND,STAND,STAND,STAND,STAND,HIT,HIT,HIT,HIT,HIT},

    // 17
    {STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND}
};

// =====================
// SOFT TOTALS (A-2 → A-9)
// index = soft total value
// =====================
static Move softStrategy[10][10] = {
    {},{},

    // A-2 (13)
    {HIT,HIT,DOUBLE,DOUBLE,DOUBLE,HIT,HIT,HIT,HIT,HIT},

    // A-3 (14)
    {HIT,HIT,DOUBLE,DOUBLE,DOUBLE,HIT,HIT,HIT,HIT,HIT},

    // A-4 (15)
    {HIT,HIT,DOUBLE,DOUBLE,DOUBLE,HIT,HIT,HIT,HIT,HIT},

    // A-5 (16)
    {HIT,HIT,DOUBLE,DOUBLE,DOUBLE,HIT,HIT,HIT,HIT,HIT},

    // A-6 (17)
    {HIT,HIT,DOUBLE,DOUBLE,DOUBLE,HIT,HIT,HIT,HIT,HIT},

    // A-7 (18)
    {STAND,DOUBLE,DOUBLE,DOUBLE,DOUBLE,STAND,STAND,HIT,HIT,HIT},

    // A-8 (19)
    {STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND},

    // A-9 (20)
    {STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND}
};

// =====================
// PAIRS (2-2 → A-A)
// index = card value
// =====================
static Move pairStrategy[12][10] = {
    {},{},

    // 2-2
    {HIT,HIT,SPLIT,SPLIT,SPLIT,SPLIT,HIT,HIT,HIT,HIT},

    // 3-3
    {HIT,HIT,SPLIT,SPLIT,SPLIT,SPLIT,HIT,HIT,HIT,HIT},

    // 4-4
    {HIT,HIT,HIT,HIT,SPLIT,SPLIT,HIT,HIT,HIT,HIT},

    // 5-5 (treat as hard 10)
    {DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,DOUBLE,HIT},

    // 6-6
    {SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,HIT,HIT,HIT,HIT,HIT},

    // 7-7
    {SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,HIT,HIT,HIT,HIT},

    // 8-8
    {SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT},

    // 9-9
    {SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,STAND,STAND,SPLIT,STAND,STAND},

    // 10-10
    {STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND,STAND},

    // A-A
    {SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT,SPLIT}
};

#endif

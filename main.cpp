#include "blackjack.h"
#include <iostream>  

using namespace std;

int main() {
    int mode;
    cout << "Choose deck mode:\n";
    cout << "1. Finite deck\n";
    cout << "2. Infinite deck\n";
    cout << "Choice: ";
    cin >> mode;

    blackjack game(2, mode == 2);

    while (true) {
        int choice;
        cout << "\n1. Play round\n2. Cheat mode\n3. Quit\nChoice: ";
        cin >> choice;

        if (choice == 1) game.play();
        else if (choice == 2) game.cheatMode();
        else break;
    }
    return 0;
}

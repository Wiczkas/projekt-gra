#include <iostream>
#include <limits>
#include "game.h"

void showMenu() {
    std::cout << "\n====== SNAKE GAME ======\n";
    std::cout << "1. Nowa gra\n";
    std::cout << "2. Wyjscie\n";
    std::cout << "Wybor: ";
}

int main() {
    int choice = 0;

    while (true) {
        showMenu();

        if (!(std::cin >> choice)) {
            // błąd wejścia
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            Game game;
            game.run();

            // 🔑 KLUCZOWA LINIA — czyści bufor po ncurses
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (choice == 2) {
            std::cout << "Do zobaczenia!\n";
            break;
        }
        else {
            std::cout << "Nieprawidlowy wybor!\n";
        }
    }

    return 0;
}

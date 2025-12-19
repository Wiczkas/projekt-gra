#include <iostream>
#include <limits>
#include "game.h"

using std::cin;
using std::cout;
using std::endl;

void showMenu() {
    cout << "\n========== SNAKE GAME ==========\n";
    cout << "1. Nowa gra (EASY)\n";
    cout << "2. Nowa gra (MEDIUM)\n";
    cout << "3. Nowa gra (HARD)\n";
    cout << "4. Zasady\n";
    cout << "5. Wyjscie\n";
    cout << "================================\n";
    cout << "Wybor: ";
}

void showRules() {
    cout << "\n=== ZASADY GRY ===\n";
    cout << "- Steruj wezem: W A S D\n";
    cout << "- Zbieraj jedzenie (*) aby rosnac i zdobywac punkty\n";
    cout << "- Unikaj scian i wlasnego ciala\n";
    cout << "- Q konczy gre\n";
    cout << "\nWcisnij Enter aby wrocic do menu...";
    cin.get();
}

int main() {
    int choice = 0;

    while (true) {
        showMenu();

        // BEZPIECZNE WCZYTANIE
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Podaj liczbe od 1 do 5.\n";
            continue;
        }

        // WYCZYSC RESZTE LINII (ENTER)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            Game game(EASY);
            game.run();
            cout << "\nWcisnij Enter aby wrocic do menu...";
            cin.get();
        }
        else if (choice == 2) {
            Game game(MEDIUM);
            game.run();
            cout << "\nWcisnij Enter aby wrocic do menu...";
            cin.get();
        }
        else if (choice == 3) {
            Game game(HARD);
            game.run();
            cout << "\nWcisnij Enter aby wrocic do menu...";
            cin.get();
        }
        else if (choice == 4) {
            showRules();
        }
        else if (choice == 5) {
            cout << "Do zobaczenia!\n";
            break;
        }
        else {
            cout << "Nieprawidlowy wybor!\n";
        }
    }

    return 0;
}

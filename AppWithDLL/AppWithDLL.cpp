#include "../Dll/Dll.h"
#include <iostream>


int main() {
    int choice;
    do {
        choice = controlPanelMenu();
        if (choice == 6) break;

        auto start = high_resolution_clock::now();
        controlPanel(choice);
        auto end = high_resolution_clock::now();

        auto duration = trukmesSkaiciavimas(start, end);
        cout << "Operacija uztruko: " << duration.count() << " ms\n";
    } while (true);

    return 0;
}
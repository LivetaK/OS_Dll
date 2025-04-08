#include "../Dll/Dll.h"


int main() {
    int choice;
    do {
        choice = controlPanelMenu();
        if (choice == 6) break;
        controlPanel(choice);
    } while (true);
    auto pradzia = high_resolution_clock::now();
	cout << "Vykdomas surasymas i failus \n";
    int proc = 0;
	vector<string> paths;
    folders(paths);
	double x0 = -(2313980 % 19); 
	double xn = 2313980 % 25;
	double xl = 2313980.0/ 1000000000000;
    for (int i = 0; i < 5; i++) {
        tCubic(i-2, x0, xn, xl, paths);
		merge(i - 2, paths);
		deleteTxtFiles(paths);
        proc += 20;
        cout << proc << " proc baigta\n";
    }
	deleteFolders(paths);
    auto pabaiga = high_resolution_clock::now();
    cout << "Programos vykdymas truko: " << trukmesSkaiciavimas(pradzia, pabaiga).count()/60000.0 << " min" << endl;

    return 0;
}
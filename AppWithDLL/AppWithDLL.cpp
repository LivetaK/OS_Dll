#include "../Dll/Dll.h"


int main() {
    //int choice;
    //do {
    //    choice = controlPanelMenu();
    //    if (choice == 6) break;

    //    auto start = high_resolution_clock::now();
    //    controlPanel(choice);
    //    auto end = high_resolution_clock::now();

    //    auto duration = trukmesSkaiciavimas(start, end);
    //    cout << "Operacija uztruko: " << duration.count() << " ms\n";
    //} while (true);
    auto pradzia = high_resolution_clock::now();
	vector<string> paths;
    folders(paths);
	double x0 = -(2313980 % 19); 
	double xn = 2313980 % 25;
	double xl = 2313980/ 1000000000000;
    for (int i = 0; i < 5; i++) {
        tCubic(i-2, x0, xn, xl, paths);
		cout << "Iteracija: " << i << endl;
		merge(i - 2, paths);
		deleteTxtFiles(paths);
    }
	deleteFolders(paths);
    auto pabaiga = high_resolution_clock::now();
    cout << "Programos vykdymas truko: " << trukmesSkaiciavimas(pradzia, pabaiga).count() << " ms" << endl;

    return 0;
}
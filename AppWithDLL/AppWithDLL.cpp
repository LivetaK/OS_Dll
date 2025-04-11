#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <execution>
#include <iostream>
#include <iomanip>

using namespace std::chrono;
extern std::vector<std::ofstream> fileStreams;
using std::cout;
using std::endl;
using std::wcout;
using std::wstring;
using std::cin;
using std::string;
using std::to_string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::istringstream;
using std::fixed;
using std::setprecision;

typedef milliseconds(*TRUKMES_SKAICIAVIMAS)(high_resolution_clock::time_point, high_resolution_clock::time_point);
typedef void (*CONTROL_PANEL)(int);
typedef int (*CONTROL_PANEL_MENU)();
typedef void (*FOLDERS)(vector<string>&);
typedef void (*TXT_FILES)(vector<string>&);
typedef void (*T_CUBIC)(double, double, double, double, vector<string>&);
typedef void (*MERGE)(double, vector<string>&);
typedef void (*DELETE_FOLDERS)(vector<string>&);
typedef void (*DELETE_TXT_FILES)(vector<string>&);



int main() {
    HMODULE hDll = LoadLibrary(TEXT("Dll.dll"));
    if (!hDll) {
        cerr << "DLL could not be loaded" << endl;
        return 1;
    }

    auto folders = (FOLDERS)GetProcAddress(hDll, "folders");
    auto tCubic = (T_CUBIC)GetProcAddress(hDll, "tCubic");
    auto merge = (MERGE)GetProcAddress(hDll, "merge");
    auto deleteTxtFiles = (DELETE_TXT_FILES)GetProcAddress(hDll, "deleteTxtFiles");
    auto deleteFolders = (DELETE_FOLDERS)GetProcAddress(hDll, "deleteFolders");
    auto controlPanelMenu = (CONTROL_PANEL_MENU)GetProcAddress(hDll, "controlPanelMenu");
    auto controlPanel = (CONTROL_PANEL)GetProcAddress(hDll, "controlPanel");
    auto trukmesSkaiciavimas = (TRUKMES_SKAICIAVIMAS)GetProcAddress(hDll, "trukmesSkaiciavimas");

	if (!folders || !tCubic || !merge || !deleteTxtFiles || !deleteFolders || !controlPanelMenu || !controlPanel || !trukmesSkaiciavimas) {
		cerr << "Could not find one or more functions in the DLL" << endl;
		FreeLibrary(hDll);
		return 1;
	}

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
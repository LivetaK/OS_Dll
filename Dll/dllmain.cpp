#include "pch.h"
#include "Dll.h"



//DLL_API void NumberList()
//{
//    TCHAR mod[MAX_PATH];
//    GetModuleFileName(NULL, mod, MAX_PATH);
//    wcout << "\nThis function was called from " << (wstring)mod << endl;
//    cout << "NumberList(): ";
//    for (int i = 0; i < 10; i++)
//    {
//        cout << i << endl;
//    }
//    cout << endl << endl;
//}

DLL_API milliseconds trukmesSkaiciavimas(high_resolution_clock::time_point pradzia, high_resolution_clock::time_point pabaiga) {
    auto trukme = duration_cast<milliseconds>(pabaiga - pradzia);
    return trukme;
}

DLL_API void controlPanel(int choice) {
    string powerShellCommand;

    switch (choice) {
    case 1: // Display
        powerShellCommand = "start ms-settings:display";
        break;
    case 2: // Security
        powerShellCommand = "start windowsdefender:";
        break;
    case 3: // Power
        powerShellCommand = "start powercfg.cpl";
        break;
    case 4: // Storage
        powerShellCommand = "start diskmgmt.msc";
        break;
    case 5: // Update
        powerShellCommand = "start ms-settings:windowsupdate";
        break;
	case 6: // Exit
		return;
    default:
        cout << "Neteisingas pasirinkimas!\n";
        return;
    }

    system(powerShellCommand.c_str());
}

DLL_API int controlPanelMenu() {
	int choice;
    cout << "Pasirinkite valdymo skydo komponenta:\n";
    cout << "1. Display\n";
    cout << "2. Security\n";
    cout << "3. Power\n";
    cout << "4. Storage\n";
    cout << "5. Update\n";
    cout << "6. Iseiti\n\n";
    cout << "Jusu pasirinkimas (1-5): ";
    while (!(cin >> choice) || choice < 1 || choice > 6) {
        cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << endl;
    return choice;
}


DLL_API void folders(vector<string>& paths) {
    string name = "Liveta", surname = "Kavaliauskaite";
    string command = "mkdir " + surname;
	paths.push_back(surname);
    system(command.c_str());
    for (int i = 1; i <= 3; i++) {
		string path = surname + "\\" + name + to_string(i);
        command = "mkdir " + path;
        paths.push_back(path);
        system(command.c_str());

        for (int j = 1; j <= 3; j++) {
            path = surname + "\\" + name + to_string(i) + "\\" +
                name + to_string(i) + name + to_string(j);
            paths.push_back(path);
            command = "mkdir " + path;
            system(command.c_str());
        }
    }
}

DLL_API void txtFiles(vector<string>& paths) {

    for (const auto& folderPath : paths) {
        string filePath = folderPath + "\\data.txt";

        ifstream test(filePath);
        if (!test) {
            ofstream file(filePath);
            if (!file) {
                cerr << "Klaida kuriant: " << filePath << endl;
                continue;
            }
            cout << "Sukurtas: " << filePath << endl;
        }
        else {
            test.close();
            cout << "Failas jau egzistuoja: " << filePath << endl;
        }
    }
}



DLL_API void tCubic(double F, double x0, double xn, double xl, vector<string>& paths) {
	folders(paths);
    txtFiles(paths);

    vector<ofstream> fileStreams;
    for (const auto& folderPath : paths) {
        string filePath = folderPath + "\\data.txt";
        fileStreams.emplace_back(filePath, std::ios::app);
        if (!fileStreams.back()) {
            cerr << "Nepavyko atidaryti: " << filePath << endl;
            fileStreams.pop_back();
        }
    }

    int currentFile = 0;
    for (double x = x0; x <= xn; x += xl) {
        double funY = x * x * x + 3 * x * x - F;

        if (funY >= 0) {
            double y = sqrt(funY);
            fileStreams[currentFile] << "X: " << x << ", Y: " << y << endl;
            fileStreams[currentFile] << "X: " << x << ", Y: " << -y << endl << endl;

            currentFile = (currentFile + 1) % fileStreams.size();
        }
        else {
            cout << "Bandoma traukti sakni is neigiamo skaiciaus.\n";
        }
    }

    for (auto& file : fileStreams) {
        file.close();
    }
}

DLL_API void merge(double F, vector<string>& paths) {
    struct Point {
        double x, y;
        bool operator<(const Point& other) const { return x < other.x; }
    };

    vector<Point> allPoints;

    for (const auto& folderPath : paths) {
        string filePath = folderPath + "\\data.txt";
        ifstream file(filePath);

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                    Point point;
                    char Char;
                    istringstream iss(line);
                    iss >> Char >> Char >> point.x >> Char >> Char >> Char >> point.y;
                    allPoints.push_back(point);
                
            }
            file.close();

            remove(filePath.c_str());
        }
    }
    std::sort(std::execution::par, allPoints.begin(), allPoints.end(),
        [](const Point& a, const Point& b) { return a.x < b.x; });

    string outputFileName = "sulieti_pagal_F_" + to_string(F) + ".txt";
    ofstream outputFile(outputFileName);

    for (const auto& point : allPoints) {
        outputFile << "X: " << point.x << ", Y: " << point.y << endl;
    }

    cout << "Sulieti duomenys irasyti i: " << outputFileName << endl;
}

DLL_API void deleteFolders(vector<string>& paths) {
    for (const auto& folderPath : paths) {
        string command = "rmdir /s /q " + folderPath;
        system(command.c_str());
    }
}

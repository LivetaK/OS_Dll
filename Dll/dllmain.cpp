#include "pch.h"
#include "Dll.h"
#include <stdlib.h>

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


DLL_API void folders() {
    
}
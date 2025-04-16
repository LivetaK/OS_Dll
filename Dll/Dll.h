#pragma once
#ifndef _DLL_H_
#define _DLL_H_

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
namespace fs = std::filesystem;
extern std::vector<std::ofstream> fileStreams;

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

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
using std::exception;

extern "C"
DLL_API milliseconds trukmesSkaiciavimas(high_resolution_clock::time_point pradzia, high_resolution_clock::time_point pabaiga);

extern "C"
DLL_API void controlPanel(int choice);

extern "C"
DLL_API int controlPanelMenu();

extern "C"
DLL_API void folders(vector<string> &paths);

extern "C"
DLL_API void txtFiles(vector<string>& paths);

extern "C"
DLL_API void tCubic(double F, double x0, double xn, double xl, vector<string>& paths);

extern "C"
DLL_API void merge(double F, vector<string>& paths);

extern "C"
DLL_API void deleteFolders(vector<string>& paths);	

extern "C"
DLL_API void deleteTxtFiles(vector<string>& paths);
#endif
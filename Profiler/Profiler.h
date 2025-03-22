#pragma once

//In-Built Header-files
#include <iostream>
#include <chrono>
#include <map>
#include <set>
#include <string>
#include <cstdlib>
#include <typeinfo>
#include <iomanip>

//Macros
#define PROFILE(x) Profiler obj1(x);
#define END static Report obj2;
#define START static Status obj2;

using namespace std;

//Class - Profiler

class Profiler {
private:
    string functionName; // For storing the function name for the destructor !!
    chrono::time_point<chrono::steady_clock> StartTimer;
public:
    map<string,pair<int,double>> functionStore;  // Stores function call counts

    void start(const string& functionName);
    void addTime(const string& functionName, double time);
    void Report();

    static Profiler& getInstance();
    Profiler(){}
    Profiler(const string& functionName);
    ~Profiler();
};

//Class - SetFlag

struct SetFlag{
public:
    static set<void*> AddressSet;  // Shared across all instances
    static bool newFlag;  // Declare static variable for new opeators
    static bool deleteFlag; //Declare static variable for delete operators
};

//Class - Status
class Status{
public:
    Status(){};
    ~Status();
};

//Class - Report
class Report{
public:
    Report(){};
    ~Report();
};

//Overloading new operator

void* operator new(size_t Size);
void* operator new[](size_t Size);

//Overloading delete operator
void operator delete(void* ptr) noexcept;
void operator delete(void* ptr, size_t size) noexcept;
void operator delete[](void* ptr) noexcept;

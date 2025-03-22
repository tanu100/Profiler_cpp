#include "Profiler.h"
// Define static members outside the class
//from SetFlag
set<void*> SetFlag::AddressSet;
bool SetFlag::newFlag = false;
bool SetFlag::deleteFlag=false;

//Class - Profiler
Profiler& Profiler::getInstance(){
    static Profiler obj;
    return obj;
}

void Profiler::start(const string& functionName) {
    Profiler::getInstance().functionStore[functionName].first++;
}
void Profiler::addTime(const string& functionName, double time) {
    Profiler::getInstance().functionStore[functionName].second = time;  // Add execution time
}

Profiler::Profiler(const string &functionName){
    this->functionName = functionName;
    start(functionName);
    StartTimer = chrono::steady_clock::now();
}

Profiler::~Profiler(){
    auto StopTimer = chrono::steady_clock::now();
    chrono::duration<double> elapsed = StopTimer - StartTimer;
    addTime(functionName, elapsed.count());
}

//Class- Status

Status::~Status(){
    cout<<"\033[1;31m MEMORY LEAK STATUS -\033[0m";
    if(!SetFlag::AddressSet.empty()){
        cout<<"There is Memory Leak"<<endl;
        for(auto it : SetFlag::AddressSet){
            cout<<"Memory is occupied at = "<<it<<endl;
        }
    }else{
        cout<<"There is no Memory Leak"<<endl;
    }
}

//Class - Report
Report::~Report(){
    if(!Profiler::getInstance().functionStore.empty()){
        cout<<"\033[1;31m RESULT OF PROFILING\033[0m"<<endl;
        cout<<"=========================================================================="<<endl;
            cout<<setw(15)<<left<<"Function-Name"
            <<setw(1)<<left<<"|"
            <<setw(15)<<right<<"No of Calls"<<"|"
            <<setw(15)<<right<<"Function ExecutionTime"<<"|"
            <<setw(15)<<right<<"Average Time (ms)"<<"|"<<endl;

        cout<<"=========================================================================="<<endl;
        for (const auto& it : Profiler::getInstance().functionStore) {
                cout<<setw(15)<<left<<it.first
                <<setw(1)<<left<<"|"
                <<setw(15)<<right<< it.second.first <<"|"
                <<setw(20)<<right<< it.second.second<<"|"
                <<setw(20)<<right<<setprecision(4)<<it.second.second/it.second.first<<"|"<<endl;
        }
        cout<<"=========================================================================="<<endl;
        Profiler::getInstance().functionStore.clear();
    }
}

//Overloading New Operator
void* operator new(size_t Size) {
    void* ptr = malloc(Size);
    if (!ptr) throw bad_alloc(); // Handle allocation failure

    if (SetFlag::newFlag) {
        SetFlag::newFlag = false;
    } else {
        SetFlag::newFlag = true;
        SetFlag::AddressSet.insert(ptr);
    }
    return ptr;
}


void* operator new[](size_t Size) {
    void* ptr = malloc(Size);
    if (!ptr) throw bad_alloc(); // Handle allocation failure
    if (SetFlag::newFlag) {
        SetFlag::newFlag = false;
    } else {
        SetFlag::newFlag = true;
        SetFlag::AddressSet.insert(ptr);
    }
    return ptr;
}

//Overloading delete operator

void operator delete(void* ptr) noexcept { // This Delete operator is used by Maps and sets basically stl
    if(SetFlag::AddressSet.find(ptr)!=SetFlag::AddressSet.end()){
        SetFlag::AddressSet.erase(ptr);
    }
    free(ptr);
}


void operator delete(void* ptr, size_t size) noexcept { //This Delete operator is used by simple Pointers
    if (ptr) {                                          //like - int * ptr = new int(5)
        SetFlag::AddressSet.erase(ptr);                 // delete ptr;
        free(ptr);
    }
}
void operator delete[](void* ptr) noexcept {            //This Delete operator is used for deallocation of
    if (ptr) {                                          //dynamic array
        SetFlag::AddressSet.erase(ptr);                 //like - int * arr = new int[5]
        free(ptr);                                      //delete arr;
    }
}

#include "Profiler.h"
#include <thread>

using namespace std;
START;

void delayedFunction() {
    PROFILE(__FUNCTION__);
    cout << "Function started..." << endl;
    this_thread::sleep_for(chrono::seconds(1));  // Delay for 2 seconds
    cout << "Function finished after delay!" << endl;
}

int fact(int n) {
    PROFILE(__FUNCTION__);
    if (n == 0){
        return 1;
    }
    delayedFunction();
    return n * fact(n - 1);
}


int main() {
    PROFILE(__FUNCTION__);
    delayedFunction();
    cout << "Value of factorial(25) is -> " << fact(25) << endl;
    int * ptr = new int(4);
    END;
}


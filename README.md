
# 🔍 C++ Profiler

C++ Profiler is a lightweight and easy-to-use performance analysis tool for C++ applications. It provides detailed runtime insights by tracking function call counts, measuring execution time, and detecting memory leaks. Perfect for developers looking to optimize and debug their code with minimal setup.


## ✨ Features
📊 Function-Level Profiling

Tracks the number of calls for each function
Measures the total execution time
Computes the average execution time per call (in milliseconds)

🧠 Memory Leak Detection

Detects memory leaks by tracking allocations and deallocations via new and delete
Provides a clear memory leak status report at the end of execution

## ⚠️ Limitations

Memory leak detection only works with new and delete.
Memory allocated using malloc, calloc, or other C-style memory management functions is not tracked.

## 📦 How to Use

To use the profiler in your C++ project:

__Add profiler.h and profiler.cpp to your project source files.  
Include the header at the top of your main source file:__

1. Include the Profiler Header
```bash
#include "profiler.h"
```

2. Initialize the Profiler  
Right after the header includes, add:
```bash
#include "Profiler.h"
START;
```

3. Terminate the Profiler
At the end of your main() function:
```bash
int main() {
    // Your application logic here

    END  // Outputs profiling results and checks for memory leaks
    return 0;
}
```
4. Profile Individual Functions
Inside any function you want to profile, insert:

PROFILE(__FUNCTION __);

```bash
int demo(int n) {
    PROFILE(__FUNCTION__);
    /
    your code
    /
}
```

## ✅ Benefits

    1. Single-header integration — no complex setup   
    2. Clear and readable output for profiling data     
    3. Helps identify performance bottlenecks and memory issues   
    4. Suitable for both small utilities and large-scale applications



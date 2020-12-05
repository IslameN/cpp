#include <iostream>

using namespace std;

struct Snitch {  // Note: All methods have side effects
    Snitch() { cout << "c'tor: " << this << endl; }
    ~Snitch() { cout << "d'tor: " << this << endl; }

    Snitch(const Snitch&) { cout << "copy c'tor: " << this << endl; }
    Snitch(Snitch&&) { cout << "move c'tor: " << this << endl; }

    Snitch& operator=(const Snitch&) {
        cout << "copy assignment: " << this << endl;
        return *this;
    }

    Snitch& operator=(Snitch&&) {
        cout << "move assignment: " << this << endl;
        return *this;
    }
};
// 1
Snitch ExampleRVO() {
    return Snitch();
}

// 2
Snitch ExampleNRVO() {
    Snitch snitch;
    return snitch;
}

// 3
void foo(Snitch s) {
}

// 4
Snitch CreateSnitch(bool runtime_condition) {
    Snitch a, b;
    if (runtime_condition) {
        return a;
    } else {
        return b;
    }
}

// 5
// Snitch global_snitch;

Snitch ReturnParameter(Snitch snitch) {
    return snitch;
}

// Snitch ReturnGlobal() {
//     return global_snitch;
// }

// 6
// Snitch CreateSnitch() {
//     Snitch snitch;
//     return std::move(snitch);
// }

// 7
Snitch CreateSnitch() {
    return Snitch();
}

// 8
struct Wrapper {
    Snitch snitch;
};

Snitch foo() {
    return Wrapper().snitch;
}

// https://shaharmike.com/cpp/rvo/
int main() {
    // Snitch snitch = ExampleRVO(); // 1
    // ExampleNRVO(); // 2
    // foo(Snitch()); // 3
    // Snitch snitch = CreateSnitch(true);  // 4
    // Snitch snitch = ReturnParameter(global_snitch);  // 5 uncomment
    // global_snitch
    // Snitch snitch2 = ReturnGlobal();  // 5
    // Snitch snitch = CreateSnitch(); // 6
    // Snitch s = CreateSnitch(); // 7
    // s = CreateSnitch(); // 7
    Snitch s = foo();  // 8
}
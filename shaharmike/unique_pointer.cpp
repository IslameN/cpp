#include <iostream>
#include <memory>

using namespace std;

// 2
class MyClass {};

// 4
std::unique_ptr<MyClass> CreateMyObject() {
    return make_unique<MyClass>();
}
void SomeFunction() {}
void SomeOtherFunction() {}

// 5
void TakeOwnership(std::unique_ptr<int> obj) {}

// 6
class SomeObject {
    // No destructor needed

   private:
    std::unique_ptr<int> m_SomethingElse;
};

// 7
struct Base {
    virtual ~Base() = default;
};
struct Derived : Base {};

// C++14
// https://shaharmike.com/cpp/unique-ptr/
int main() {
    // 1
    auto u_int = std::make_unique<int>(123);
    cout << (*u_int == 123) << endl;
    auto u_string = std::make_unique<std::string>(3, '#');
    cout << (*u_string == "###") << endl;

    // 2
    // The best one is a. It is the cleanest and the less verbose.
    auto a = std::make_unique<MyClass>();
    auto b = std::unique_ptr<MyClass>(new MyClass());
    std::unique_ptr<MyClass> c(new MyClass());

    // 3
    auto a3 = std::make_unique<int>(123);
    a3 = std::make_unique<int>(456);          // Cool.
    a3.reset(new int(789));                   // Works, but not as nice.
    a3 = std::unique_ptr<int>(new int(456));  // Works, but see example 2.

    // 4 Return a dynamically allocated object from a function
    SomeFunction();
    CreateMyObject();  // no assignment, yet no leak
    SomeOtherFunction();

    // 5 Take ownership of a dynamically-allocated object
    // TakeOwnership(3);  // ERROR: no conversion from 'int' to 'std::unique_ptr<int>'

    int* p = new int(3);
    // TakeOwnership(p);    // ERROR: no conversion from 'int*' to 'std::unique_ptr<int>'
    // This is because unique_ptr's constructor is explicit.

    auto u = std::make_unique<int>(3);
    // TakeOwnership(u);  // ERROR: no copy constructor

    TakeOwnership(std::move(u));              // OK
    TakeOwnership(std::make_unique<int>(3));  // OK
    TakeOwnership(nullptr);                   // OK -- due to constructor accepting nullptr_t

    // 6 Dynamically-allocated class members
    auto someClass = SomeObject();

    // 7 Casting
    std::unique_ptr<Derived> derived = std::make_unique<Derived>();
    std::unique_ptr<Base> base(std::move(derived));  // We need std::move() beacuse there can't be two instances of the same unique pointer.

    // 8 Custom deleter
    FILE* file = fopen("...", "r");
    auto FILE_releaser = [](FILE* f) { fclose(f); };
    std::unique_ptr<FILE, decltype(FILE_releaser)> file_ptr(file, FILE_releaser);

    // 9 Misususing
    int* p9 = new int(123);
    std::unique_ptr<int> a9(p9);
    // std::unique_ptr<int> b9(p9); // Oops - b's destructor will double delete p. g++ 9.3.0-17ubuntu1~20.04: free(): double free detected in tcache 2. Aborted(core dumped)

    std::unique_ptr<int> a99_2 = std::make_unique<int>(123);
    // std::unique_ptr<int> b99_2(a99_2.get()); // g++ 9.3.0-17ubuntu1~20.04: free(): double free detected in tcache 2. Aborted(core dumped)

    auto u10 = std::make_unique<int>(123);
    // delete u10.get(); // g++ 9.3.0-17ubuntu1~20.04: free(): double free detected in tcache 2. Aborted(core dumped)
}
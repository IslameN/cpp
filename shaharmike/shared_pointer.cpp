#include <iostream>
#include <memory>
#include <type_traits>

struct Snitch {
   public:
    Snitch() { std::cout << "c'tor: " << this << std::endl; }
    ~Snitch() { std::cout << "d'tor: " << this << std::endl; }
    Snitch(Snitch const&) { std::cout << "copy c'tor: " << this << std::endl; }
    Snitch(Snitch&&) { std::cout << "move c'tor: " << this << std::endl; }
};

// 2
std::unique_ptr<Snitch> CreateMyObject() {
    return std::make_unique<Snitch>();
}

// 4
struct Node {  // Binary tree
    Node() { std::cout << "c'tor: " << this << std::endl; }
    ~Node() { std::cout << "d'tor: " << this << std::endl; }

    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};

// 5
struct WeakNode {  // Binary tree
    WeakNode() { std::cout << "c'tor: " << this << std::endl; }
    ~WeakNode() { std::cout << "d'tor: " << this << std::endl; }

    std::weak_ptr<WeakNode> parent;
    std::shared_ptr<WeakNode> left;
    std::shared_ptr<WeakNode> right;
};

// 7
struct DatabaseConnection {};  // exposed to the user

struct InternalDatabaseConnection {
    // socket
    // authentication information
    DatabaseConnection connection;
};

std::shared_ptr<DatabaseConnection> CreateDatabaseConnection() {
    auto tmp = std::make_shared<InternalDatabaseConnection>();
    return std::shared_ptr<DatabaseConnection>(tmp, &tmp->connection);
}

// 8
struct Base {
    ~Base() { std::cout << "non-virtual ~Base()" << std::endl; }
};
struct Derived : Base {
    ~Derived() { std::cout << "~Derived()" << std::endl; }
};

// 10
struct WeirdClass {
    std::shared_ptr<WeirdClass> CreateSharedPtrToThis() {
        return std::shared_ptr<WeirdClass>(this);  // DON'T DO THIS.
    }
};

struct WeirdClass2 : std::enable_shared_from_this<WeirdClass2> {
    std::shared_ptr<WeirdClass2> CreateSharedPtrToThis() {
        return shared_from_this();
    }
};

int main() {
    // // 1
    // auto snitch = std::make_shared<Snitch>();
    // auto another_snitch = snitch;
    // std::cout << "Equal? " << (snitch == another_snitch) << std::endl;

    // {
    //     auto scoped_snitch = snitch;
    //     auto another_scoped_snitch = scoped_snitch;
    // }  // destroy 'another_scoped_snitch' and 'scoped_snitch'

    // // 2 Construct from unique_ptr
    // std::shared_ptr<Snitch> shared_object = CreateMyObject();

    // // 3 No release() method, reset() doesn’t necessarily release
    // std::cout << "Creating 1st Snitch" << std::endl;
    // auto snitch1 = std::make_shared<Snitch>();
    // auto snitch2 = snitch1;

    // std::cout << "Calling reset" << std::endl;
    // snitch1.reset();  // object will *not* be released

    // std::cout << "Moving out of scope" << std::endl;

    // 4 Cyclic references & std::weak_ptr
    auto root = std::make_shared<Node>();
    root->left = std::make_shared<Node>();
    root->left->parent = root;

    // 5
    auto root5 = std::make_shared<WeakNode>();
    root5->left = std::make_shared<WeakNode>();
    root5->left->parent = root5;

    // 6 weak pointers have no get() and should be upgraded
    std::weak_ptr<std::string> weak;  // = std::make_shared<std::string>("lo2l");
    std::shared_ptr<std::string> shared = weak.lock();
    if (shared) {
        std::cout << "Exists" << std::endl;
    } else {
        std::cout << "Released" << std::endl;
    }

    // 8 Casting
    std::shared_ptr<Base> base = std::make_shared<Derived>();  // If we were to replace shared_ptr with unique_ptr (and make_shared with make_unique) the program would not call ~Derived.

    // 9
    auto derived = std::make_shared<Derived>();
    std::shared_ptr<Base> base9 = derived;  // OK.
    // std::shared_ptr<Derived> derived2 = base;  // ERROR: no implicit down-cast.
    std::shared_ptr<Derived> derived2 = std::static_pointer_cast<Derived>(base9);
    // std::shared_ptr<Derived> derived3 =
    // std::dynamic_pointer_cast<Derived>(base9); // ERROR: do not know why

    auto shared_short = std::make_shared<short>(123);
    //std::shared_ptr<int> shared_int = shared_short;  // ERROR: no cast from
    //short* to int*.

    // 10 std::enable_shared_from_this
    auto weird_class = std::make_shared<WeirdClass>();
    // auto tmp = weird_class->CreateSharedPtrToThis();  // ERROR: double delete

    auto weird_class2 = std::make_shared<WeirdClass2>();
    auto tmp = weird_class2->CreateSharedPtrToThis();
}  // 1 destroy 'snother_snitch' and 'snitch'
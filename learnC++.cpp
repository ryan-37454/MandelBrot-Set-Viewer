#include <iostream>
#include <vector>
#include <cmath>

// typdef is used to create an additional name for another data type
typedef std::vector<std::pair<std::string, int>> pairlist_t;
typedef std::string text_t;
using text_t = std::string;


// struct groups different variables under one name
struct student{
    std::string name;
    double gpa;
    bool enrolled;
};

enum Day{monday = 0, tuesday = 1, wednesday = 2};

double getTotal(double prices[], int size, student student1);

template <typename T> // template parameter declaration, works with many data types
T max(T x, T y){
    return (x > y) ? x : y;
}

template <typename T, typename U>
auto min(T x, U y){ // auto - compiler deduces what the return type should be
    return (x > y) ? x : y;
}

namespace first{
    int x = 2;
}

int main(){
    // cout << (insertion operator)
    // cin >> (extraction operator)

    // namespace prevents name conflicts, allowing identically named identities
    // local still overides namespace, but there is no need for first::x
    int x = 1;
    using namespace first; 
    std::cout << x << first::x << '\n'; // standard output (not good with whitespace inputs)

    int correct = 8;
    int questions = 10;
    double score = correct/(double)questions * 100;
    std::cout << (char) 100 << ' ' << score << '\n'; // outputs d 80

    // int z = std: max(x, y); // standard max function (not user made)
    // int z = std: min(x, y);
    // ternary operator: condition ? expression1 : expression2
    // && = and, || = or

    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name); // string input with whitespaces use getline
    if(name.length() > 12){
        std::cout << "Your name can't be over 12 characters";
    } else {
        std::cout << "Welcome " << name;
    }
    //name.length();
    //name.empty();
    //name.append("@gmail.com");
    //name.at(0); // outputs n
    //name.insert(0, "@"); // outputs @name
    //name.find(' '); // finds the index of the first space
    //name.erase(0, 3); // end and beginning index, outputs e

    int number;
    do{
        std::cout << "Enter a positive #: ";
        std::cin >> number;
    } while (number < 0);

    for(int i = 1; i <= 20; i++){
        std::cout << i << '\n';
        // break = break out of a loop
        // continue = skip current iteration
    }

    // arrays should be of the same data type
    std::string cars[] = {"Corvette", "Mustang", "Camry"};
    cars[0] = "Camaro";
    for(std::string car : cars){  // basically for car in cars:
        std::cout << car << '\n';
    }

    double gpa = 2.5;
    std::cout << sizeof(gpa) << sizeof(double); // 8 bytes

    student student1;
    student1.name = "Spongebob";
    student1.enrolled = true;
    double prices[] = {49.99, 15.05, 75, 9.99};
    int size = sizeof(prices)/sizeof(prices[0]);
    double total = getTotal(prices, size, student1);

    const int SIZE = 100;
    std::string foods[size];
    // fill(begin, end, value)
    fill(foods, foods + size, "pizza");

    // memory address = a location in memory where data is stored
    // accessed with & (address-of operator)
    bool teacher = true;
    std::cout << &teacher << '\n'; // output x7fffffffcf6d

    // pointer = variable that stores a memory address of another variable
    // accessed with * (dereference operator)
    // A pointer is pointing to nothing = null point = nullptr

    std::string location = "location";
    std::string *plocation = &location; // this is a pointer to an address
    std::cout << *plocation;

    int *pointer = nullptr;
    int u = 123;
    pointer = &u;
    if(pointer == nullptr){
        std::cout << "address was not assigned!\n";
    }else{
        std::cout << "address was assigned";
    }

    // dynamic memory = Memory that is allocated after the program is already compiled & running
    // new memory is allocated in the heap rather than the stack
    int *pNum = NULL;
    pNum = new int; // new returns an address (malloc)
    *pNum = 21;
    std::cout << "address: " << pNum << '\n';
    std::cout << "value: " << *pNum << '\n';
    delete pNum; // free the memory (free)

    // std::cout << max('1', '2') << '\n';

    Day today = monday;
    switch(today){
        // case only takes integers, so using enums creates paired named-integer constants
        case monday:
            std::cout << "It is monday";
            break;
        case 2:
            std::cout << "It is tuesday";
            break;
    }

    return 0;
}

double getTotal(double prices[], int size, student student1){
    //can't use sizeof() since function is taking the pointer to the 
    // first value of the array, so pass the size as the second argument
    double total = 0;
    for(int i = 0; i < size - 1; i++){
        total += prices[i];
    }
    return total;
}
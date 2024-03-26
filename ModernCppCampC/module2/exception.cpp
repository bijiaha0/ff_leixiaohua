#include <iostream>
#include <exception>

using namespace std;

class MyClass {
};

class MyException : public exception {
    string text;

public:
    MyException(string text){

    }
};

double process(int a, int b) {
    MyClass mc;//=new MyClass();

    if (b <= 0) {
        MyException mexp("argument b mush be greater than 0");
        throw mexp;
    }

    //delete mc;
    return (a / b);
}

int main() {
    try {
        process(10, -10);
    } catch (MyException &e) {
        std::cout << "MyException caught" << std::endl;
        std::cout << e.what() << std::endl;
    } catch (std::exception &e) {
    } catch (...) {
    }
}

class Base {
public:
    virtual void func1() noexcept;

    virtual void func2();

    virtual void func3() noexcept;
};

class Sub : Base {
public:
    void func2() noexcept override; // OK
    //void func3() = delete; // OK
};
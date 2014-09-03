#include <iostream>
#include <string>
using	namespace	std;

class SubSystemOne {
    public:
        void methodOne() {
            cout << "method 1" << endl;
        }
};

class SubSystemTwo {
    public:
        void methodTwo() {
            cout << "method 2" << endl;
        }
};

class SubSystemThree {
    public:
        void methodThree () {
            cout << "method 3" << endl;
        }
};

class Facade {
    public:
        Facade() {
            one = new SubSystemOne();
            two = new SubSystemTwo();
            three = new SubSystemThree();
        }

        void methodA() {
            one->methodOne();
            two->methodTwo();
        }

        void methodB() {
            one->methodOne();
            three->methodThree();
        }

    private:
        SubSystemOne* one;
        SubSystemTwo* two;
        SubSystemThree* three;
};

int
main(void) {
    Facade* ins_facade = new Facade();
    ins_facade->methodA();
    ins_facade->methodB();

    return 0;
}

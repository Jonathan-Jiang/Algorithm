#include <iostream>
#include <string>
using	namespace	std;

class AbstractClass {
    public:
        void templateMethod() {
            cout << "public template method" << endl;
            primitiveOperation1();
            primitiveOperation2();
        }

        virtual void primitiveOperation1() = 0;
        virtual void primitiveOperation2() = 0;
};

class ConcreteClassA : public AbstractClass {
    public:
        void primitiveOperation1() {
            cout << "ConcreteClassA::primitiveOperation1" << endl;
        }

        void primitiveOperation2() {
            cout << "ConcreteClassA::primitiveOperation2" << endl;
        }
};

class ConcreteClassB : public AbstractClass {
    public:
        void primitiveOperation1() {
            cout << "ConcreteClassB::primitiveOperation1" << endl;
        }

        void primitiveOperation2() {
            cout << "ConcreteClassB::primitiveOperation2" << endl;
        }
};

int
main(void) {
    AbstractClass* ins_abstract_class = NULL;
    ins_abstract_class = new ConcreteClassA();
    ins_abstract_class->templateMethod();

    ins_abstract_class = new ConcreteClassB();
    ins_abstract_class->templateMethod();

    return 0;
}

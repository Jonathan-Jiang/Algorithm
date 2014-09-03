#include <iostream>
using	namespace	std;

class Operation {
    public:
        double getNumberA() {
            return _numberA;
        }

        double getNumberB() {
            return _numberB;
        }

        void setNumberA(double numberA) {
            _numberA = numberA;
        }

        void setNumberB(double numberB) {
            _numberB = numberB;
        }

        virtual double GetResult() = 0;

        double _numberA;
        double _numberB;
};

class OperationAdd : public Operation {
    public:
        double GetResult() {
            return _numberA + _numberB;
        }
};

class OperationSub : public Operation {
    public:
        double GetResult() {
            return _numberA - _numberB;
        }
};

class OperationMul : public Operation {
    public:
        double GetResult() {
            return _numberA * _numberB;
        }
};

class OperationDiv : public Operation {
    public:
        double GetResult() {
            return _numberA / _numberB;
        }
};

class Factory {
    public:
        virtual Operation* createOperation() = 0;
};

class AddFactory: public Factory {
    public:
        Operation* createOperation() {
            return new OperationAdd();
        }
};

class SubFactory: public Factory {
    public:
        Operation* createOperation() {
            return new OperationSub();
        }
};

class MulFactory: public Factory {
    public:
        Operation* createOperation() {
            return new OperationMul();
        }
};

class DivFactory: public Factory {
    public:
        Operation* createOperation() {
            return new OperationDiv();
        }
};

int
main(void) {
    Factory* ins_factory = new AddFactory();
    Operation* ins_operation = ins_factory->createOperation();
    ins_operation->setNumberA(1);
    ins_operation->setNumberB(2);
    cout << ins_operation->GetResult() << endl;

	return 0;
}

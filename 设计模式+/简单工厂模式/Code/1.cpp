#include <iostream>
using	namespace	std;

enum optType {
    ADD, SUB, MUL, DIV
};

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

class OperationFactory {
    public:
        static Operation* createOperation(enum optType type) {
            Operation* ins_operation = NULL;
            switch (type) {
                case ADD:
                    ins_operation = new OperationAdd();
                    break;
                case SUB:
                    ins_operation = new OperationSub();
                    break;
                case MUL:
                    ins_operation = new OperationMul();
                    break;
                case DIV:
                    ins_operation = new OperationDiv();
                    break;
            }
            return ins_operation;
        }
};

int
main(void) {
    Operation* ins_operation = OperationFactory::createOperation(ADD);
    ins_operation->setNumberA(1);
    ins_operation->setNumberB(2);
    cout << ins_operation->GetResult() << endl;

	return 0;
}

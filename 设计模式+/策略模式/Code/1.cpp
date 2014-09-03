#include <iostream>
using	namespace	std;

class Strategy {
    public:
        virtual void AlgorithmInterface() = 0;
};

class ConcreteStrategyA : public Strategy {
    public:
        void AlgorithmInterface() {
            cout << "A Strategy" << endl;
        }
};

class ConcreteStrategyB : public Strategy {
    public:
        void AlgorithmInterface() {
            cout << "B Strategy" << endl;
        }
};

class ConcreteStrategyC : public Strategy {
    public:
        void AlgorithmInterface() {
            cout << "C Strategy" << endl;
        }
};

class Context {
    public:
        Context(Strategy* ins_strategy) {
            _ins_strategy = ins_strategy;
        }

        void ContextInterface() {
            _ins_strategy->AlgorithmInterface();
        }

    private:
        Strategy* _ins_strategy;
};

int
main(void) {
    Context* ins_context = NULL;
    ins_context = new Context(new ConcreteStrategyA());
    ins_context->ContextInterface();

    ins_context = new Context(new ConcreteStrategyB());
    ins_context->ContextInterface();

    ins_context = new Context(new ConcreteStrategyC());
    ins_context->ContextInterface();

	return 0;
}

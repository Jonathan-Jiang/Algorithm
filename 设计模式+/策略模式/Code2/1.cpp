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

template < typename STRATEGY >
class Context {
    public:
        void ContextInterface() {
            _ins_strategy.AlgorithmInterface();
        }

    private:
        STRATEGY _ins_strategy;
};

int
main(void) {
    Context< ConcreteStrategyA >* ins_contextA = new Context< ConcreteStrategyA >();
    ins_contextA->ContextInterface();

    Context< ConcreteStrategyB >* ins_contextB = new Context< ConcreteStrategyB >();
    ins_contextB->ContextInterface();

    Context< ConcreteStrategyC >* ins_contextC = new Context< ConcreteStrategyC >();
    ins_contextC->ContextInterface();

	return 0;
}

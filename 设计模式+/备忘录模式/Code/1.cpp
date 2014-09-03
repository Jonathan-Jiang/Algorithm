#include <iostream>
#include <string>
using    namespace    std;

class Memento {
    public:
        Memento(string state) : _state(state) {}

        string getState() {
            return this->_state;
        }

    private:
        string _state;
};

class Originator {
    public:
        string state;

        Memento* createMemento() {
            return new Memento(state);
        }

        void setMemento(Memento* memento) {
            state = memento->getState();
        }

        void show() {
            cout << "State: " << state << endl;
        }
};

class CareTaker {
    public:
        Memento* memento; 
};

int
main(void) {
    Originator* o = new Originator();
    o->state = "On";
    o->show();

    CareTaker* c = new CareTaker();
    c->memento = o->createMemento();

    o->state = "off";
    o->show();

    o->setMemento(c->memento);
    o->show();

    return 0;
}

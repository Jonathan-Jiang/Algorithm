#include <iostream>
#include <string>
using	namespace	std;

class Person {
    public:
        Person() {
        }

        Person(string name) {
            _name = name;
        }

        virtual void show() {
            cout << _name << endl;
        }
    private:
        string _name;
};

class Finery : public Person {
    public:
        void Decorate(Person* component) {
            _component = component;
        }

        void show() {
            if (_component != NULL) {
                _component->show();
            }
        }

    protected:
        Person* _component;
};

class TShirts : public Finery {
    public:
        void show() {
            cout << "TShirt" << endl;
            Finery::show();
        }
};

class BigTrouser : public Finery {
    public:
        void show() {
            cout << "BigTrouser" << endl;
            Finery::show();
        }
};

class Sneakers : public Finery {
    public:
        void show() {
            cout << "Sneakers" << endl;
            Finery::show();
        }
};

class LeatherShoes : public Finery {
    public:
        void show() {
            cout << "LeatherShoes" << endl;
            Finery::show();
        }
};

class Tie : public Finery {
    public:
        void show() {
            cout << "Tie" << endl;
            Finery::show();
        }
};

class Suit: public Finery {
    public:
        void show() {
            cout << "Suit" << endl;
            Finery::show();
        }
};

int
main(void) {
    Person* ins_person = new Person("arthur");
    cout << "first decoration" << endl;
    Sneakers* pqx = new Sneakers();
    BigTrouser* kk = new BigTrouser();
    TShirts* dtx = new TShirts();

    pqx->Decorate(ins_person);
    kk->Decorate(pqx);
    dtx->Decorate(kk);
    dtx->show();

    cout << "second decoration" << endl;
    LeatherShoes* px = new LeatherShoes();
    Tie* ld = new Tie();
    Suit* xz = new Suit();

    px->Decorate(ins_person);
    ld->Decorate(px);
    xz->Decorate(ld);
    xz->show();

	return 0;
}

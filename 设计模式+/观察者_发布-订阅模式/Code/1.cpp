#include <iostream>
#include <string>
#include <list>
using	namespace	std;

class Subject;
class ConcreteSubject;
class Observer;
class ConcreteObserver;

class Observer {
	public:
		int id;
		virtual void update() = 0;
};

class Subject {
    public:
        void attach(Observer* observer) {
            observers.push_back(observer);
        }

        void detach(Observer* observer) {
			// in C++, this would not work
            // observers.remove(observer);
        }

        void notify() {
            for (list< Observer* >::iterator it = observers.begin(); it != observers.end(); ++it) {
				(*it)->update();
            }
        }
    private:
        list< Observer* > observers;
};

class ConcreteSubject : public Subject {
	public:
		string subjectState;
};

class ConcreteObserver : public Observer {
	public:
		ConcreteObserver(ConcreteSubject* subject, string name) {
			this->subject = subject;
			this->name = name;
		}

		void update() {
			observerState = subject->subjectState;
			cout << name << "\t" << observerState << endl;
		}
	private:
		string name;
		string observerState;
		ConcreteSubject* subject;
};

int
main(void) {
	ConcreteSubject* s = new ConcreteSubject();
	ConcreteObserver* ob1 = new ConcreteObserver(s, "arthur");
	ConcreteObserver* ob2 = new ConcreteObserver(s, "daishengdong");
	s->attach(ob1);
	s->attach(ob2);

	s->subjectState = "abc";
	s->notify();

    return 0;
}

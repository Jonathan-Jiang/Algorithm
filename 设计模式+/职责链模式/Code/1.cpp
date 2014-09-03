#include <iostream>
#include <string>
#include <list>
using    namespace    std;

class Handler {
    public:
        Handler(string name) : _name(name) {}

        void setSuccessor(Handler* successor) {
			_successor = successor;
		}

        virtual void handlerRequest(int request) = 0;

	protected:
        string _name;
        Handler* _successor;
};

class ConcreteHandler1 : public Handler {
    public:
        ConcreteHandler1(string name) : Handler(name) {}

        void handlerRequest(int request) {
            if (request >= 0 && request < 10) {
                cout << _name << "\t" << request << endl;
            } else if (_successor != NULL) {
                _successor->handlerRequest(request);
            }
        }
};

class ConcreteHandler2 : public Handler {
    public:
        ConcreteHandler2(string name) : Handler(name) {}

        void handlerRequest(int request) {
            if (request >= 10 && request < 20) {
                cout << _name << "\t" << request << endl;
            } else if (_successor != NULL) {
                _successor->handlerRequest(request);
            }
        }
};

class ConcreteHandler3 : public Handler {
    public:
        ConcreteHandler3(string name) : Handler(name) {}

        void handlerRequest(int request) {
            if (request >= 20 && request < 30) {
                cout << _name << "\t" << request << endl;
            } else if (_successor != NULL) {
                _successor->handlerRequest(request);
            }
        }
};

int
main(void) {
    Handler* h1 = new ConcreteHandler1("arthur");
    Handler* h2 = new ConcreteHandler2("sky");
    Handler* h3 = new ConcreteHandler3("daishengdong");
    
    h1->setSuccessor(h2);
    h2->setSuccessor(h3);

    int requests[8] = {
        2, 5, 14, 22, 18, 3, 27, 20,
    };

    for (int i = 0; i < 8; ++i) {
        h1->handlerRequest(requests[i]);
    }

    return 0;
}

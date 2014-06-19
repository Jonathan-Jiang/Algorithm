#include <iostream>
#include <string>
using	namespace	std;

class Subject {
    public:
        virtual void Request() = 0;
};

class RealSubject : public Subject {
    public:
        void Request() {
            cout << "RealSubject's Request" << endl;
        }
};

class Proxy : public Subject {
    public:
		Proxy() {
			_real_subject = NULL;
		}

        void Request() {
            if ( _real_subject == NULL ) {
                _real_subject = new RealSubject();
            }
            _real_subject->Request();
        }
    private:
        RealSubject* _real_subject;
};

int
main( void ) {
    Proxy* ins_proxy = new Proxy();
    ins_proxy->Request();

    return 0;
}

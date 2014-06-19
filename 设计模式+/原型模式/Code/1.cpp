#include <iostream>
#include <string>
using	namespace	std;

class Prototype;

class Cloneable {
	public:
		Cloneable( string id ) : _id( id ) {}

		virtual Prototype* clone() = 0;

	protected:
		string _id;
};

class  Prototype : public Cloneable {
    public:
        Prototype( string id ) : Cloneable( id ) {}

        string getId() {
            return _id;
        }

		void setId( string id ) {
			_id = id;
		}

        Prototype* clone() {
            return new Prototype( _id );
        }
};

int
main( void ) {
	Prototype* ins_prototype1 = new Prototype( "arthur" );
	cout << ins_prototype1->getId() << endl;

	Prototype* ins_prototype2 = ins_prototype1->clone();
	ins_prototype2->setId( "daishengdong" );
	cout << ins_prototype2->getId() << endl;

    return 0;
}

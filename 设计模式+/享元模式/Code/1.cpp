#include <iostream>
#include <string>
#include <map>
using    namespace    std;

class Flyweight {
    public:
        virtual void operation( int extrinsicstate ) = 0;
};

class ConcreteFlyweight : public Flyweight {
    public:
        void operation( int extrinsicstate ) {
            cout << "ConcreteFlyWeight " << extrinsicstate << endl;
        }
};

class UnsharedConcreteFlyweight : public Flyweight {
    public:
        void operation( int extrinsicstate ) {
            cout << "UnsharedConcreteFlyweight " << extrinsicstate << endl;
        }
};

class FlyweightFactory {
    public:
        FlyweightFactory() {
            flyweights[ "X" ] = new ConcreteFlyweight();
            flyweights[ "Y" ] = new ConcreteFlyweight();
            flyweights[ "Z" ] = new ConcreteFlyweight();
        }

        Flyweight* getFlyweight( string key ) {
            return flyweights[ key ];
        }

    private:
        map< string, ConcreteFlyweight* > flyweights;
};

int
main( void ) {
    int extrinsicstate = 22;
    FlyweightFactory* f = new FlyweightFactory();
    Flyweight* fx = f->getFlyweight( "X" );
    fx->operation( --extrinsicstate );

    Flyweight* fy = f->getFlyweight( "Y" );
    fy->operation( --extrinsicstate );

    Flyweight* fz = f->getFlyweight( "Z" );
    fz->operation( --extrinsicstate );

    UnsharedConcreteFlyweight* uf = new UnsharedConcreteFlyweight();
    uf->operation( --extrinsicstate );

    return 0;
}

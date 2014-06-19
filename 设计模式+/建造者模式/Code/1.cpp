#include <iostream>
#include <string>
#include <vector>
using	namespace	std;

class Product {
    public:
        void add( string part ) {
            parts.push_back( part );
        }
        
        void show() {
            for ( vector< string >::iterator it = parts.begin(); it != parts.end(); ++it ) {
                cout << *it << endl;
            }
        }
    private:
        vector< string > parts;
};

class Builder {
    public:
        virtual void buildPartA() = 0;
        virtual void buildPartB() = 0;
        virtual Product getResult() = 0;
};

class ConcreteBuilder1 : public Builder {
    public:
        void buildPartA() {
            ins_product.add( "part a" );
        }

        void buildPartB() {
            ins_product.add( "part b" );
        }

        Product getResult() {
            return ins_product;
        }
    private:
        Product ins_product;
};

class ConcreteBuilder2 : public Builder {
    public:
        void buildPartA() {
            ins_product.add( "part x" );
        }

        void buildPartB() {
            ins_product.add( "part y" );
        }

        Product getResult() {
            return ins_product;
        }
    private:
        Product ins_product;
};

class Director {
    public:
        void construct( Builder* builder ) {
            builder->buildPartA();
            builder->buildPartB();
        }
};

int
main( void ) {
    Director ins_director;
    Builder* b1 = new ConcreteBuilder1();
    Builder* b2 = new ConcreteBuilder2();

    ins_director.construct( b1 );
    Product p1 = b1->getResult();
    p1.show();

    ins_director.construct( b2 );
    Product p2 = b2->getResult();
    p2.show();

    return 0;
}

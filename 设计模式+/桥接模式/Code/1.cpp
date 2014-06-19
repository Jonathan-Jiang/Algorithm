#include <iostream>
#include <string>
#include <list>
using    namespace    std;

// 下面的 Implementor 和 Abstraction 是可以互换的
// 我们可以进行不同的分类
// 比如可以按手机系统平台分，每个平台下又有不同的应用
// 我们也可以按手机应用分，每个不同的应用又有不同的平台
// 这种多分类(实现)取决于类的设计者

// Implementor 表示具体的实现
// 比如不同的手机应用，iReader、相机
class Implementor {
    public:
        virtual void operation() = 0;	
};

class ConcreteImplementorA : public Implementor {
    public:
        void operation() {
            cout << "implementor A" << endl;
        }
};

class ConcreteImplementorB : public Implementor {
    public:
        void operation() {
            cout << "implementor B" << endl;
        }
};

// Abstraction 表示抽象
// 比如不同类型的平台，android、ios
class Abstraction {
    public:
		Abstraction( string type ) : _type( type ) {}

        void addImplementor( Implementor* implementor ) {
            this->implementor.push_back( implementor );
        }

        virtual void operation() = 0;
    protected:
        string _type;
        list< Implementor* > implementor;
};

class RefinedAbstraction : public Abstraction {
    public:
        RefinedAbstraction( string type ) : Abstraction( type ) {}

        void operation() {
            cout << "now on " << _type << endl;
            for ( list< Implementor* >::iterator it = implementor.begin(); it != implementor.end(); ++it ) {
                ( *it )->operation();
            }
        }
};

int
main( void ) {
    Abstraction* android = new RefinedAbstraction( "android" );
    Abstraction* ios = new RefinedAbstraction( "ios" );

    Implementor* i_reader = new ConcreteImplementorA();
    Implementor* camera = new ConcreteImplementorB();

    android->addImplementor( i_reader );
    android->addImplementor( camera );

    ios->addImplementor( i_reader );
    ios->addImplementor( camera );

    android->operation();
    ios->operation();

    return 0;
}

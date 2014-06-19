#include <iostream>
#include <string>
using    namespace    std;

class SingleCore {
    public:
        virtual void putsInfo() = 0;
        virtual SingleCore* get() = 0;
};

class DualCore {
    public:
        virtual void putsInfo() = 0;
        virtual DualCore* get() = 0;
};

class IntelSingleCore : public SingleCore {
    public:
        void putsInfo() {
            cout << "intel" << "\t" << "single core" << endl;
        }

        SingleCore* get() {
            return this;
        }
};

class IntelDualCore: public DualCore {
    public:
        void putsInfo() {
            cout << "intel" << "\t" << "dual core" << endl;
        }

        DualCore* get() {
            return this;
        }
};

class AMDSingleCore : public SingleCore {
    public:
        void putsInfo() {
            cout << "AMD" << "\t" << "single core" << endl;
        }

        SingleCore* get() {
            return this;
        }
};

class AMDDualCore: public DualCore {
    public:
        void putsInfo() {
            cout << "AMD" << "\t" << "dual core" << endl;
        }

        DualCore* get() {
            return this;
        }
};

enum COMPANY { intel, amd };

class SuperFactory {
    public:
		SuperFactory( COMPANY company ) : _company( company ) {
		}

        SingleCore* createSingleCore( ) {
			SingleCore* ret_single_core = NULL;
			switch ( _company ) {
			case intel:
				ret_single_core = new IntelSingleCore();
				break;
			case amd:
				ret_single_core = new AMDSingleCore();
				break;
			}
			return ret_single_core;
		}

        DualCore* createDualCore() {
			DualCore* ret_dual_core = NULL;
			switch ( _company ) {
			case intel:
				ret_dual_core = new IntelDualCore();
				break;
			case amd:
				ret_dual_core = new AMDDualCore();
				break;
			}
			return ret_dual_core;
		}
	private:
		COMPANY _company;
};

int
main( void ) {
	SuperFactory* factory = new SuperFactory( intel );

    SingleCore* intel_single_core = factory->createSingleCore();
    DualCore* intel_dual_core = factory->createDualCore();

    ( intel_single_core->get() )->putsInfo();
    ( intel_dual_core->get() )->putsInfo();

    return 0;
}

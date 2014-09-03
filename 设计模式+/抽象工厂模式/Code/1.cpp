#include <iostream>
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

class Factory {
    public:
        virtual SingleCore* createSingleCore() = 0;
        virtual DualCore* createDualCore() = 0;
};

class IntelFactory : public Factory {
    public:
        SingleCore* createSingleCore() {
            return new IntelSingleCore();
        }

        DualCore* createDualCore() {
            return new IntelDualCore();
        }
};

class AMDFactory : public Factory {
    public:
        SingleCore* createSingleCore() {
            return new AMDSingleCore();
        }

        DualCore* createDualCore() {
            return new AMDDualCore();
        }
};

int
main(void) {
    Factory* intel_factory = new IntelFactory();
    Factory* amd_factory = new AMDFactory();

    SingleCore* intel_single_core = intel_factory->createSingleCore();
    DualCore* intel_dual_core = intel_factory->createDualCore();

    SingleCore* amd_single_core = amd_factory->createSingleCore();
    DualCore* amd_dual_core = amd_factory->createDualCore();

    (intel_single_core->get())->putsInfo();
    (intel_dual_core->get())->putsInfo();
    (amd_single_core->get())->putsInfo();
    (amd_dual_core->get())->putsInfo();

    return 0;
}

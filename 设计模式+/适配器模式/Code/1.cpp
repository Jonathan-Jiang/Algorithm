#include <iostream>
#include <string>
using    namespace    std;

class Linux {
public:
	virtual void ls() = 0;
};

class Windows {
public:
	void dir() {
		cout << "windows dir cmd executed!" << endl;
	}
};

class MingwAdapter : public Linux {
public:
	void ls() {
		cout << "now I can use ls command in Windows" << endl;
		windows.dir();
	}
private:
	Windows windows;
};

int
main(void) {
	MingwAdapter ma;
	ma.ls();

    return 0;
}

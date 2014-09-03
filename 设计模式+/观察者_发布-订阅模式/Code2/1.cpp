#include <iostream>
#include <string>
#include <list>
using	namespace	std;

typedef void (*update)();

template < typename FUNC_TYPE >
class Delegate {
	public:
		void add(FUNC_TYPE update_func) {
			func_list.push_back(update_func);
		}

		void operator ()() {
			for (list< FUNC_TYPE >::iterator it = func_list.begin(); it != func_list.end(); ++it) {
				(*it)();
			}
		}

	private:
		list< FUNC_TYPE > func_list;
};

class Subject {
    public:
		string subjectState;
		virtual void notify() = 0;
};

template < typename FUNC_TYPE >
class Boss : public Subject {
	public:
		Delegate< FUNC_TYPE > update_delegate;
		string subjectState;

		void notify() {
			update_delegate();
		}
};

template < typename FUNC_TYPE >
class Secretary : public Subject {
	public:
		Delegate< FUNC_TYPE > update_delegate;
		string subjectState;

		void notify() {
			update_delegate();
		}
};

class StockObserver {
	public:
		StockObserver(Subject* subject, string name) {
			this->subject = subject;
			this->name = name;
		}

		void closeStockMarket() {
			cout << name << "\t" << subject->subjectState << endl;
		}
	private:
		string name;
		Subject* subject;
};

class NBAObserver {
	public:
		NBAObserver(Subject* subject, string name) {
			this->subject = subject;
			this->name = name;
		}

		void closeNBADirectSeeding() {
			cout << name << "\t" << subject->subjectState << endl;
		}
	private:
		string name;
		Subject* subject;
};

int
main(void) {
	Boss< update >* huhansan = new Boss< update >();

	StockObserver* tongshi1 = new StockObserver(huhansan, "arthur");
	NBAObserver* tongshi2 = new NBAObserver(huhansan, "daishengdong");

	huhansan->update_delegate.add(StockObserver::closeStockMarket);
	huhansan->update_delegate.add(NBAObserver::closeNBADirectSeeding);

	huhansan->subjectState = "I'm back";

	huhansan->notify();

    return 0;
}

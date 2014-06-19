// 在这种实现方式中，类的单例实被 Context 持有例
// 懒汉模式一定要加 synchronized, 以确保多线程时单例依旧成立
class Context {
	public static HungrySingletonClass getHungryInstance() {
		return hsc;
	}

	public static synchronized LazySingletonClass getLazyInstance() {
		if ( lsc == null ) {
			lsc = new LazySingletonClass();
		}
		return lsc;
	}

	private Context() {};
	private static HungrySingletonClass hsc = new HungrySingletonClass();
	private static LazySingletonClass lsc = null;
}

class HungrySingletonClass {
	public HungrySingletonClass() {};
}

class LazySingletonClass {
    public LazySingletonClass() {};
} 

public class SingletonPattern {
	public static void main( String args[] ) {
		HungrySingletonClass hsc1 = Context.getHungryInstance();
		HungrySingletonClass hsc2 = Context.getHungryInstance();

		if ( hsc1 == hsc2 ) {
			System.out.println( "h" );
		}

		LazySingletonClass lsc1 = Context.getLazyInstance();
		LazySingletonClass lsc2 = Context.getLazyInstance();

		if ( lsc1 == lsc2 ) {
			System.out.println( "l" );
		}
	}
}

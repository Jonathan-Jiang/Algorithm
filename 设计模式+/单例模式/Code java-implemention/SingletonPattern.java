// 在这两种实现方式中，类的单例实例作为 static 成员被类本身持有
// 若要取得该实例，需通过 static 的成员方法
// 懒汉模式一定要加 synchronized, 以确保多线程时单例依旧成立
class HungrySingletonClass {
	public static HungrySingletonClass getInstance() {
		return instance;
	}

	private HungrySingletonClass() {};
	private static HungrySingletonClass instance = new HungrySingletonClass();
}

class LazySingletonClass {
    public static synchronized LazySingletonClass getInstance(){
         if( instance == null ) {
             instance = new LazySingletonClass ();
         }
        return instance;
    }
    private static LazySingletonClass instance = null;
} 

public class SingletonPattern {
	public static void main( String args[] ) {
		HungrySingletonClass hsc1 = HungrySingletonClass.getInstance();
		HungrySingletonClass hsc2 = HungrySingletonClass.getInstance();

		if ( hsc1 == hsc2 ) {
			System.out.println( "h" );
		}

		LazySingletonClass lsc1 = LazySingletonClass.getInstance();
		LazySingletonClass lsc2 = LazySingletonClass.getInstance();

		if ( lsc1 == lsc2 ) {
			System.out.println( "l" );
		}
	}
}

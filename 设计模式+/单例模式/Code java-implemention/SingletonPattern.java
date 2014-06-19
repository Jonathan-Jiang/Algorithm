// ��������ʵ�ַ�ʽ�У���ĵ���ʵ����Ϊ static ��Ա���౾�����
// ��Ҫȡ�ø�ʵ������ͨ�� static �ĳ�Ա����
// ����ģʽһ��Ҫ�� synchronized, ��ȷ�����߳�ʱ�������ɳ���
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

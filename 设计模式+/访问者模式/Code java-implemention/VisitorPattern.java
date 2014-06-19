import java.util.ArrayList;
import java.util.List;

// "״̬"�ĳ�����
abstract class Action {
	// �õ����˵Ľ��ۻ�Ӧ
	public abstract void getManConclusion( Man concreteElementA );
	public abstract void getWomanConclusion( Woman concreteElementB );
	// �õ�Ů�˵Ľ��ۻ�Ӧ
}

abstract class Person {
	// ����
	// ���"״̬"����
	public abstract void accept( Action visitor );
}

// �ɹ�ʱ��Ů�Ľ���
class Success extends Action {
	public void getManConclusion( Man concreteElementA ) {
		System.out.println( "���� �� �ɹ� ��̬��" );
	}

	public void getWomanConclusion( Woman concreteElementB ) {
		System.out.println( "Ů�� �� �ɹ� ��̬��" );
	}
}

class Failing extends Action {
	public void getManConclusion( Man concreteElementA ) {
		System.out.println( "���� �� ʧ�� ��̬��" );
	}

	public void getWomanConclusion( Woman concreteElementB ) {
		System.out.println( "Ů�� �� ʧ�� ��̬��" );
	}
}

class Man extends Person {
	public void accept( Action visitor ) {
		visitor.getManConclusion( this );
	}
}

class Woman extends Person {
	public void accept( Action visitor ) {
		visitor.getWomanConclusion( this );
	}
}

class ObjectStructure {
	public void attach( Person element ) {
		elements.add( element );
	}

	public void detach( Person element ) {
		elements.remove( element );
	}

	public void display( Action visitor ) {
		for ( Person element : elements ) {
			element.accept( visitor );
		}
	}

	private List< Person > elements = new ArrayList< Person >();
}

public class VisitorPattern {
	public static void main( String args[] ) {
		ObjectStructure o = new ObjectStructure();
		o.attach( new Man() );
		o.attach( new Woman() );

		// �ɹ�ʱ�ķ�Ӧ
		Success v1 = new Success();
		o.display( v1 );

		// ʧ��ʱ�ķ�Ӧ
		Failing v2 = new Failing();
		o.display( v2 );
	}

}

import java.util.ArrayList;
import java.util.List;

// "状态"的抽象类
abstract class Action {
	// 得到男人的结论或反应
	public abstract void getManConclusion( Man concreteElementA );
	public abstract void getWomanConclusion( Woman concreteElementB );
	// 得到女人的结论或反应
}

abstract class Person {
	// 接受
	// 获得"状态"对象
	public abstract void accept( Action visitor );
}

// 成功时男女的结论
class Success extends Action {
	public void getManConclusion( Man concreteElementA ) {
		System.out.println( "男人 对 成功 的态度" );
	}

	public void getWomanConclusion( Woman concreteElementB ) {
		System.out.println( "女人 对 成功 的态度" );
	}
}

class Failing extends Action {
	public void getManConclusion( Man concreteElementA ) {
		System.out.println( "男人 对 失败 的态度" );
	}

	public void getWomanConclusion( Woman concreteElementB ) {
		System.out.println( "女人 对 失败 的态度" );
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

		// 成功时的反应
		Success v1 = new Success();
		o.display( v1 );

		// 失败时的反应
		Failing v2 = new Failing();
		o.display( v2 );
	}

}

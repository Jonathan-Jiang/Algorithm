import java.util.ArrayList;
import java.util.List;

abstract class Visitor {
	// 得到男人的结论或反应
	public abstract void visitConcreteElementA( ConcreteElementA concreteElementA );
	// 得到女人的结论或反应
	public abstract void visitConcreteElementB( ConcreteElementB concreteElementB );
}

class ConcreteVistor1 extends Visitor {
	public void visitConcreteElementA( ConcreteElementA concreteElementA ) {
		System.out.println( "concreteElementA 被 ConcreteVistor1 访问" );
	}

	public void visitConcreteElementB( ConcreteElementB concreteElementB ) {
		System.out.println( "concreteElementB 被 ConcreteVistor1 访问" );
	}
}

class ConcreteVistor2 extends Visitor {
	public void visitConcreteElementA( ConcreteElementA concreteElementA ) {
		System.out.println( "concreteElementA 被 ConcreteVistor2 访问" );
	}

	public void visitConcreteElementB( ConcreteElementB concreteElementB ) {
		System.out.println( "concreteElementB 被 ConcreteVistor2 访问" );
	}
}

abstract class Element {
	public abstract void accept( Visitor visitor );
}

class ConcreteElementA extends Element {
	public void accept( Visitor visitor ) {
		visitor.visitConcreteElementA( this );
	}

	public void operationA() {
	}
}

class ConcreteElementB extends Element {
	public void accept( Visitor visitor ) {
		visitor.visitConcreteElementB( this );
	}

	public void operationB() {
	}
}

class ObjectStructure {
	public void attach( Element element ) {
		elements.add( element );
	}

	public void detach( Element element ) {
		elements.remove( element );
	}

	public void accept( Visitor visitor ) {
		for ( Element element : elements ) {
			element.accept( visitor );
		}
	}

	private List< Element > elements = new ArrayList< Element >();
}

public class VisitorPattern {
	public static void main( String args[] ) {
		ObjectStructure o = new ObjectStructure();
		o.attach( new ConcreteElementA() );
		o.attach( new ConcreteElementB() );
		
		ConcreteVistor1 v1 = new ConcreteVistor1();
		ConcreteVistor2 v2 = new ConcreteVistor2();

		o.accept( v1 );
		o.accept( v2 );
	}
}
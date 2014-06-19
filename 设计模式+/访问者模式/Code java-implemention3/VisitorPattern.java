import java.util.ArrayList;
import java.util.List;

// �ÿ��кܶ࣬����ҿɹ����˲ι۵ĵط����ǹ̶����������ط�
// ��ҵĻ�԰��Ӿ�ء�����
abstract class Visitor {
	public abstract void visitGarden( Place garden );
	public abstract void visitKitchen( Place kitchen );
	public abstract void visitSwimpool( Place swimpool );

	public Visitor( String name ) {
		this.name = name;
	}

	protected String name;
}

class Sky extends Visitor {
	public Sky( String name ) {
		super( name );
	}

	public void visitGarden( Place garden ) {
		System.out.println( name + "������" + garden.name );
	}

	public void visitKitchen( Place kitchen ) {
		System.out.println( name + "������" + kitchen.name );
	}

	public void visitSwimpool( Place swimpool ) {
		System.out.println( name + "������" + swimpool.name );
	}
}
 
class Arthur extends Visitor {
	public Arthur( String name ) {
		super( name );
	}

	public void visitGarden( Place garden ) {
		System.out.println( name + "������" + garden.name );
	}

	public void visitKitchen( Place kitchen ) {
		System.out.println( name + "������" + kitchen.name );
	}

	public void visitSwimpool( Place swimpool ) {
		System.out.println( name + "������" + swimpool.name );
	}
} 

// ����һ���ÿ�֮���������ʼ����
abstract class Place {
	public Place( String name ) {
		this.name = name;
	}

	public abstract void acceptVisitor( Visitor visitor );

	protected String name;
}

class Garden extends Place {
	public Garden( String name ) {
		super( name );
	}

	public void acceptVisitor( Visitor visitor ) {
		visitor.visitGarden( this );
	}
}

class Kitchen extends Place {
	public Kitchen( String name ) {
		super( name );
	}

	public void acceptVisitor( Visitor visitor ) {
		visitor.visitKitchen( this );
	}
}

class Swimpool extends Place {
	public Swimpool( String name ) {
		super( name );
	}

	public void acceptVisitor( Visitor visitor ) {
		visitor.visitSwimpool( this );
	}
}

// �ÿ�̫�࣬��Ҫ�Ŷ�
class VisitorHolder {
	public void add( Visitor visitor ) {
		visitors.add( visitor );
	}

	public void remove( Visitor visitor ) {
		visitors.remove( visitor );
	}

	// �������źö�֮�󣬽�ȥ�ι�
	// ÿ����ͬ�ĵط��Ų�ͬ�Ķ�
	public void visit( Place place ) {
		for ( Visitor visitor : visitors ) {
			place.acceptVisitor( visitor );	
		}
	}

	private List< Visitor > visitors = new ArrayList< Visitor >();
}

public class VisitorPattern {
	public static void main( String args[] ) {
		VisitorHolder vh = new VisitorHolder();
		Visitor arthur = new Arthur( "arthur" );
		Visitor sky = new Sky( "sky" );

		Place garden = new Garden( "garden" );
		Place kitchen = new Garden( "kitchen" );
		Place swimpool = new Garden( "swimpool" );

		vh.add( arthur );
		vh.add( sky );

		vh.visit( garden );
		vh.visit( kitchen );
		vh.visit( swimpool );
	}
}
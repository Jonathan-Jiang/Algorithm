import java.util.ArrayList;
import java.util.List;

// 访客有很多，但你家可供别人参观的地方就是固定的那三个地方
// 你家的花园、泳池、卧室
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
		System.out.println( name + "访问了" + garden.name );
	}

	public void visitKitchen( Place kitchen ) {
		System.out.println( name + "访问了" + kitchen.name );
	}

	public void visitSwimpool( Place swimpool ) {
		System.out.println( name + "访问了" + swimpool.name );
	}
}
 
class Arthur extends Visitor {
	public Arthur( String name ) {
		super( name );
	}

	public void visitGarden( Place garden ) {
		System.out.println( name + "访问了" + garden.name );
	}

	public void visitKitchen( Place kitchen ) {
		System.out.println( name + "访问了" + kitchen.name );
	}

	public void visitSwimpool( Place swimpool ) {
		System.out.println( name + "访问了" + swimpool.name );
	}
} 

// 接受一个访客之后就让他开始访问
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

// 访客太多，需要排队
class VisitorHolder {
	public void add( Visitor visitor ) {
		visitors.add( visitor );
	}

	public void remove( Visitor visitor ) {
		visitors.remove( visitor );
	}

	// 所有人排好队之后，进去参观
	// 每个不同的地方排不同的队
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
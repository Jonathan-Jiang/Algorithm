import java.util.ArrayList;
import java.util.List;

abstract class Component {
	protected String name;

	public Component( String name ) {
		this.name = name;
	}

	abstract void add( Component c );
	abstract void remove( Component c );
	abstract void display( int depth );
}

class Leaf extends Component {
	public Leaf( String name ) {
		super( name );
	}

	public void add( Component c ) {
		System.out.println( "Cannot add to a leaf" );
	}
 
	public void remove( Component c ) {
		System.out.println( "Cannot remove from a leaf" );
	} 

	public void display( int depth ) {
		for ( int i = 0; i < depth; ++i ) {
			System.out.print( '-' ) ;
		}
		System.out.println( ' ' + name );
	} 
}

class Composite extends Component {
	public Composite( String name ) {
		super( name );
	}
	public void add( Component c ) {
		children.add( c );
	}

	public void remove( Component c ) {
		children.remove( c );
	} 

	public void display( int depth ) {
		for ( int i = 0; i < depth; ++i ) {
			System.out.print( '-' ) ;
		}
		System.out.println( ' ' + name );

		for ( Component component : children ) {
			component.display( depth + 2 );
		}
	} 

	private List< Component > children = new ArrayList< Component >();
}

public class CompositePattern {
	public static void main( String args[] ) {
		Composite root = new Composite( "root" );
		root.add( new Leaf( "Leaf A" ) );
		root.add( new Leaf( "Leaf B" ) );

		Composite comp = new Composite( "Composite X" );
		comp.add( new Leaf( "Leaf XA" ) );
		comp.add( new Leaf( "Leaf XB" ) );

		root.add( comp );

		Composite comp2 = new Composite( "Composite XY" );
		comp2.add( new Leaf( "Leaf XYA" ) );
		comp2.add( new Leaf( "Leaf XYB" ) );

		comp.add( comp2 );

		root.add( new Leaf( "Leaf C" ) );

		Leaf leaf = new Leaf( "Leaf D" );
		root.add( leaf );
		root.remove( leaf );

		root.display( 1 );
	}
}

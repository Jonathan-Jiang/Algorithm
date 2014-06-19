import java.util.ArrayList;
import java.util.List;

abstract class Iterator {
	public abstract Object first();
	public abstract Object next();
	public abstract boolean isDone();
	public abstract Object currentItem();
}

abstract class Aggregate {
	public abstract Iterator createIterator();
}

class ConcreteIterator extends Iterator {
	public ConcreteIterator( ConcreteAggregate aggregate ) {
		this.aggregate = aggregate;
	}

	@Override
	public Object first() {
		// TODO Auto-generated method stub
		return aggregate.get( 0 );
	}

	@Override
	public Object next() {
		// TODO Auto-generated method stub
		Object ret = null;
		++current;
		if ( current < aggregate.count() ) {
			ret = aggregate.get( current );
		}
		return ret;
	}

	@Override
	public boolean isDone() {
		// TODO Auto-generated method stub
		return current >= aggregate.count() ? true : false;
	}

	@Override
	public Object currentItem() {
		// TODO Auto-generated method stub
		return aggregate.get( current );
	}
	
	private ConcreteAggregate aggregate;
	private int current = 0;
}

class ConcreteIteratorDesc extends Iterator {
	public ConcreteIteratorDesc( ConcreteAggregate aggregate ) {
		this.aggregate = aggregate;
		current = aggregate.count() - 1;
	}

	@Override
	public Object first() {
		// TODO Auto-generated method stub
		return aggregate.get( aggregate.count() - 1 );
	}

	@Override
	public Object next() {
		// TODO Auto-generated method stub
		Object ret = null;
		--current;
		if ( current >= 0 ) {
			ret = aggregate.get( current );
		}
		return ret;
	}

	@Override
	public boolean isDone() {
		// TODO Auto-generated method stub
		return current < 0 ? true : false;
	}

	@Override
	public Object currentItem() {
		// TODO Auto-generated method stub
		return aggregate.get( current );
	}
	
	private ConcreteAggregate aggregate;
	private int current;
}

class ConcreteAggregate extends Aggregate {
	@Override
	public Iterator createIterator() {
		// TODO Auto-generated method stub
		return new ConcreteIterator( this );
	}

	public int count() {
		return items.size();
	}

	public Object get( int index ) {
		return items.get( index );
	}

	public void set( int index, Object element ) {
		items.set( index, element );
	}

	public void add( Object element ) {
		items.add( element );
	}

	private List< Object > items = new ArrayList< Object >();
}

public class IteratorPattern {
	public static void main( String args[] ) {
		ConcreteAggregate a = new ConcreteAggregate();
		
		a.add( "00" );
		a.add( "01" );
		a.add( "02" );
		a.add( "03" );
		a.add( "04" );
		a.add( "05" );

		// Iterator i = new ConcreteIterator( a );
		Iterator i = new ConcreteIteratorDesc( a );

		Object item = i.first();
		while ( !i.isDone() ) {
			System.out.println( i.currentItem() );
			item = i.next();
		}
	}
}

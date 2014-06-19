import java.util.Hashtable;

// 每个棋子的位置是外部状态
class Position {
	public int x;
	public int y;

	public Position( int x, int y ) {
		this.x = x;
		this.y = y;
	}
}

// 棋子是享元对象，每下一步棋不可能都重新创建一个新的棋子对象
// 我们共享棋子对象
abstract class Chessmen {
	public abstract void set( Position position );
}

// 棋子的颜色是内部状态
class ConcreteChessmen extends Chessmen {
	public ConcreteChessmen( String color ) {
		this.color = color;
	}

	public void set( Position position ) {
		System.out.println( color + "\t" + position.x + " " + position.y );
	}

	private String color;
}

class ChessmenFactory {
	public ChessmenFactory() {
		chessmens.put( "black", new ConcreteChessmen( "black" ) );
		chessmens.put( "white", new ConcreteChessmen( "white" ) );
	}

	public Chessmen getChessmenCategory( String color ) {
		if ( !chessmens.contains( color ) ) {
			chessmens.put( color, new ConcreteChessmen( color ) );
		}
		return ( Chessmen )chessmens.get( color );
	}

	public int getChessmenCount() {
		return chessmens.size();
	}

	private Hashtable< String, Chessmen > chessmens = new Hashtable< String, Chessmen >();
}

public class FlyweightPattern {
	public static void main( String args[] ) {
		ChessmenFactory cf = new ChessmenFactory();
		Chessmen bc1 = cf.getChessmenCategory( "black" );
		bc1.set( new Position( 0, 0 ) );

		Chessmen bc2 = cf.getChessmenCategory( "black" );
		bc2.set( new Position( 1, 2 ) );

		Chessmen bc3 = cf.getChessmenCategory( "black" );
		bc3.set( new Position( 10, 99 ) );

		Chessmen wc1 = cf.getChessmenCategory( "white" );
		wc1.set( new Position( 11, 99 ) );

		Chessmen wc2 = cf.getChessmenCategory( "white" );
		wc2.set( new Position( 22, 44 ) );

		Chessmen wc3 = cf.getChessmenCategory( "white" );
		wc3.set( new Position( 77, 77 ) );

		System.out.println( cf.getChessmenCount() );
	}
}

import java.util.ArrayList;
import java.util.List;

abstract class AbstractExpression {
	public abstract void interpret( Context context );
}

class TerminalExpression extends AbstractExpression {
	public void interpret( Context context ) {
		System.out.println( "÷’∂ÀΩ‚ Õ∆˜" );
	}
}

class NonTerminalExpression extends AbstractExpression {
	public void interpret( Context context ) {
		System.out.println( "∑«÷’∂ÀΩ‚ Õ∆˜" );
	}
}

class Context {
	public String input;
	public String output;
}

public class InterpreterPattern {
	public static void main( String args[] ) {
		Context context = new Context();
		List< AbstractExpression > list = new ArrayList< AbstractExpression >();
		list.add( new TerminalExpression() );
		list.add( new NonTerminalExpression() );
		list.add( new TerminalExpression() );
		list.add( new TerminalExpression() );

		for ( AbstractExpression exp : list ) {
			exp.interpret( context );
		}
	}
}
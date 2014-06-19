class Context {
    Context( State state ) {
    	this._state = state;
    }

    public State getState() {
		return this._state;
    }

    public void setState( State state ) {
        this._state = state;
        this._state.printState();
    }

    public void request() {
        this._state.handle( this );
    }

    private State _state;
}

abstract class State {
	public abstract void handle( Context context );
	public abstract void printState();
}

class ConcreteStateA extends State {
	 public void handle( Context context ) {
        context.setState( new ConcreteStateB() );
    }

	 public void printState() {
        System.out.println( "State A" );
	 }
}

class ConcreteStateB extends State {
	public void handle( Context context ) {
        context.setState( new ConcreteStateA() );
    }

	 public void printState() {
        System.out.println( "State B" );
	 }
}

public class StatePattern {
	public static void main( String args[] ) {
	    Context c = new Context( new ConcreteStateA() );
	
	    c.request();
	    c.request();
	    c.request();
	    c.request();
	}
}

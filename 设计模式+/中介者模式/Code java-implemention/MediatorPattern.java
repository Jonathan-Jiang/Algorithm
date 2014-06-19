import java.util.ArrayList;
import java.util.List;

// 联合国，相当于中介者
abstract class UnitedNations {
	public abstract void declare( String message, Country country );
}

abstract class Country {
	protected UnitedNations mediator;

	public Country( UnitedNations mediator ) {
		this.mediator = mediator;
	}
}

class USA extends Country {
	public USA( UnitedNations mediator ) {
		super( mediator );
	}

	public void declare( String message ) {
		mediator.declare( message, this );
	}

	public void getMessage( String message ) {
		System.out.println( "USA get message " + message );
	}
}

class Iraq extends Country {
	public Iraq( UnitedNations mediator ) {
		super( mediator );
	}

	public void declare( String message ) {
		mediator.declare( message, this );
	}

	public void getMessage( String message ) {
		System.out.println( "Iraq get message " + message );
	}
}

class UnitedNationsSecurityCouncil extends UnitedNations {
	private USA usa_country;
	private Iraq iraq_country;

	void setUSA( USA usa_country ) {
		this.usa_country = usa_country;
	}

	void setIraq( Iraq iraq_country ) {
		this.iraq_country = iraq_country;
	}

	public void declare( String message, Country country ) {
		if ( usa_country == country ) {
			iraq_country.getMessage( message );
		} else {
			usa_country.getMessage( message );
		}
	}
}

public class MediatorPattern {
	public static void main( String args[] ) {
		UnitedNationsSecurityCouncil unsc = new UnitedNationsSecurityCouncil();
		USA c1 = new USA( unsc );
		Iraq c2 = new Iraq( unsc );

		unsc.setUSA( c1 );
		unsc.setIraq( c2 );

		c1.declare( "no nuclear weapon" );
		c2.declare( "we have no nuclear weapon" );
	}
}
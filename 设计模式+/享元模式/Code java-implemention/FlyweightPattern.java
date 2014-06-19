import java.util.Hashtable;

class User {
	public String name;

	public User( String name ) {
		this.name = name;
	}
}

abstract class WebSite {
	public abstract void use( User user );
}

class ConcreteWebSite extends WebSite {
	public ConcreteWebSite( String name ) {
		this.name = name;
	}

	public void use( User user ) {
		System.out.println( name + "\t" + user.name );
	}

	private String name;
}

class WebSiteFactory {
	public WebSite getWebSiteCategory( String key ) {
		if ( !flyweights.contains( key ) ) {
			flyweights.put( key, new ConcreteWebSite( key ) );
		}
		return ( WebSite )flyweights.get( key );
	}

	public int getWebSiteCount() {
		return flyweights.size();
	}

	private Hashtable< String, ConcreteWebSite > flyweights = new Hashtable< String, ConcreteWebSite >();
}

public class FlyweightPattern {
	public static void main( String args[] ) {
		WebSiteFactory f = new WebSiteFactory();

		WebSite fx = f.getWebSiteCategory( "��Ʒչʾ" );
		fx.use( new User( "С��" ) );

		WebSite fy = f.getWebSiteCategory( "��Ʒչʾ" );
		fy.use( new User( "����" ) );

		WebSite fz = f.getWebSiteCategory( "��Ʒչʾ" );
		fz.use( new User( "����" ) );

		WebSite fl = f.getWebSiteCategory( "����" );
		fl.use( new User( "����ͯ" ) );

		WebSite fm = f.getWebSiteCategory( "����" );
		fm.use( new User( "�ҹ�����" ) );

		WebSite fn = f.getWebSiteCategory( "����" );
		fn.use( new User( "�Ϻ�����" ) );

		System.out.println( f.getWebSiteCount() );
	}
}
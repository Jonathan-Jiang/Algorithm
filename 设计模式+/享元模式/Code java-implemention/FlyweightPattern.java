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

		WebSite fx = f.getWebSiteCategory( "产品展示" );
		fx.use( new User( "小菜" ) );

		WebSite fy = f.getWebSiteCategory( "产品展示" );
		fy.use( new User( "大鸟" ) );

		WebSite fz = f.getWebSiteCategory( "产品展示" );
		fz.use( new User( "娇娇" ) );

		WebSite fl = f.getWebSiteCategory( "博客" );
		fl.use( new User( "老顽童" ) );

		WebSite fm = f.getWebSiteCategory( "博客" );
		fm.use( new User( "桃谷六仙" ) );

		WebSite fn = f.getWebSiteCategory( "博客" );
		fn.use( new User( "南海鳄神" ) );

		System.out.println( f.getWebSiteCount() );
	}
}
import java.util.ArrayList;
import java.util.List;

// 相当于不同的点菜命令
// 点烤羊肉串、烤鸡翅
abstract class Command {
	public Command( Receiver receiver, String action_item ) {
		this.receiver = receiver;
		this.action_item = action_item;
	}

	protected Receiver receiver;
	protected String action_item;

	abstract public void execute();
}

// 具体的点菜命令
class ConcreteCommand extends Command {
	public ConcreteCommand( Receiver receiver, String action_item ) {
		super( receiver, action_item );
	}

	@Override
	// 每个具体点菜命令的落实需要厨师来执行
	public void execute() {
		// TODO Auto-generated method stub
		receiver.action( action_item );
	}
}

// 命令的记录者，比如服务员
class Invoker {
	public void addCommand( Command command ) {
		// 可以添加一些条件判断
		// 比如鸡翅已经卖完了此命令就可以不加了
		command_list.add( command );
	}

	public void removeCommand( Command command ) {
		// 命令清单执行之前可以移除命令
		command_list.remove( command );
	}

	public void executeCommand() {
		for ( Command command : command_list ) {
			command.execute();
		}
	}

	private List< Command > command_list = new ArrayList< Command >();
}

// 命令的落实者，比如厨师
class Receiver {
	public void action( String action_item) {
		System.out.println( action_item );
	}
}

// 相当于点菜者
public class CommandPattern {
	public static void main( String args[] ) {
		Receiver r = new Receiver();
		Command c1 = new ConcreteCommand( r, "烤鸡翅" );
		Command c2 = new ConcreteCommand( r, "烤羊肉串" );
		Command c3 = new ConcreteCommand( r, "澳洲鲍鱼" );
		Invoker i = new Invoker();

		i.addCommand( c1 );
		i.addCommand( c2 );
		i.addCommand( c3 );
		i.removeCommand( c3 );

		i.executeCommand();
	}
}

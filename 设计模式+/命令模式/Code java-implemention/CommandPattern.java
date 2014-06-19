import java.util.ArrayList;
import java.util.List;

// �൱�ڲ�ͬ�ĵ������
// �㿾���⴮��������
abstract class Command {
	public Command( Receiver receiver, String action_item ) {
		this.receiver = receiver;
		this.action_item = action_item;
	}

	protected Receiver receiver;
	protected String action_item;

	abstract public void execute();
}

// ����ĵ������
class ConcreteCommand extends Command {
	public ConcreteCommand( Receiver receiver, String action_item ) {
		super( receiver, action_item );
	}

	@Override
	// ÿ���������������ʵ��Ҫ��ʦ��ִ��
	public void execute() {
		// TODO Auto-generated method stub
		receiver.action( action_item );
	}
}

// ����ļ�¼�ߣ��������Ա
class Invoker {
	public void addCommand( Command command ) {
		// �������һЩ�����ж�
		// ���缦���Ѿ������˴�����Ϳ��Բ�����
		command_list.add( command );
	}

	public void removeCommand( Command command ) {
		// �����嵥ִ��֮ǰ�����Ƴ�����
		command_list.remove( command );
	}

	public void executeCommand() {
		for ( Command command : command_list ) {
			command.execute();
		}
	}

	private List< Command > command_list = new ArrayList< Command >();
}

// �������ʵ�ߣ������ʦ
class Receiver {
	public void action( String action_item) {
		System.out.println( action_item );
	}
}

// �൱�ڵ����
public class CommandPattern {
	public static void main( String args[] ) {
		Receiver r = new Receiver();
		Command c1 = new ConcreteCommand( r, "������" );
		Command c2 = new ConcreteCommand( r, "�����⴮" );
		Command c3 = new ConcreteCommand( r, "���ޱ���" );
		Invoker i = new Invoker();

		i.addCommand( c1 );
		i.addCommand( c2 );
		i.addCommand( c3 );
		i.removeCommand( c3 );

		i.executeCommand();
	}
}

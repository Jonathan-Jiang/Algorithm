//ͼ�����Ϣ����ϵͳ
//ʹ��C++���Կ���
//С���Ա����ʤ��(�鳤)����ӭ������ΰ�ס�����������
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200	//����ͼ����
//����ĺ궨���������������ʽ
#define print_title printf("ͼ����\t\t     ������   ������\t\t   ISBN\t\t\t��������     ������\t  �۸�\t �ɽ�   �ؼ���\t\t     ����\t\t  ���\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n")
#define print_content printf("%-20s %-8s %-20s %-20s %-12s %-12s %-4.2f  %-6s %-20s %-20s %-12s\n", library.book[i].name, library.book[i].author, library.book[i].publisher, library.book[i].ISBN, library.book[i].time, library.book[i].number, library.book[i].price, library.book[i].available, library.book[i].keyword, library.book[i].theme, library.book[i].classification)

typedef struct {	
	char name[20];	//����
	char author[20];	//����
	char publisher[50];	//������
	char ISBN[20];		//ISBN
	char time[20];	//����ʱ��
	char number[20];	//������
	float price;	//�۸�
	char available[20];		//�Ƿ�ɽ�
	char keyword[20];	//�ؼ���
	char theme[50];		//����
	char classification[20];	//���
} mbook;

typedef struct {
	int count;	//��ı���
	mbook book[N];	//������N����
} mlibrary;

mlibrary library;	//ͼ���

void save();	//����ͼ����Ϣ��
void putin();     //������Ӻ���
void print();	//��ӡ
void del();                   //����ɾ������
void search_by_name();         //���尴������ѯ
void search_by_author();          //���尴��������ѯ
void search_by_publisher();		//���������ѯ
void search_by_ISBN();		//��ISBN��ѯ
void search_by_time();		//���������ڲ�ѯ
void search_by_number();		//�������Ų�ѯ
void search_by_price();	//���۸��ѯ
void search_by_available();		//���ɽ������ѯ
void search_by_keyword();		//���ؼ��ʲ���
void search_by_theme();	//���������
void search_by_classification();	//��������
void search();        //�����ѯ����
void swap(mbook &book1, mbook &book2);	//����
void display_by_time();	//������˳����ʾ
void display_by_name();	//������˳����ʾ
void display_by_author();	//������˳����ʾ
void display_by_number();	//��������˳����ʾ
void display_by_ISBN();	//��ISBN˳����ʾ
void display();	//��ʾ��Ϣ
void modify();	//�޸�ͼ����Ϣ
void Borrow();		//����
void Return();		//�黹
void borrowOrReturn();		//���ĺ͹黹
void count_1();	//ͳ�ƶ���1
void count_2();	//ͳ�ƹ���2
void count_3();	//ͳ�ƹ���3
void count();		//ͳ�ƺ���

void save()	{	//����ͼ����Ϣ��
	FILE *fp;
	if ((fp = fopen("library.txt", "w")) == NULL) {
		printf("\n���ܱ���ͼ����Ϣ\n");
		return;
	}
	fwrite(&library.count, sizeof(int), 1, fp);
	fwrite(library.book, sizeof(library.book[0]), library.count, fp);
	fclose(fp);
}

void putin() {      //������Ӻ���
	int go = 1;
	system("cls");
	while (go) {
		printf("\t\t������������");
		scanf("%s", library.book[library.count].name);
		printf("\t\t��������������");
		scanf("%s", library.book[library.count].author);
		printf("\t\t����������磺");
		scanf("%s", library.book[library.count].publisher);
		printf("\t\t�����������鼮��ISBN��");
		scanf("%s", library.book[library.count].ISBN);
		printf("\t\t���������ʱ�䣺");
		scanf("%s", library.book[library.count].time);
		printf("\t\t�����������鼮�ļ����ţ�");
		scanf("%s", library.book[library.count].number);
		printf("\t\t���������ļ۸�");
		fflush(stdin);
		scanf("%f", &library.book[library.count].price);
		printf("\t\t�����������鼮�Ƿ�ɽ裺");
		scanf("%s", library.book[library.count].available);
		printf("\t\t�����������鼮�Ĺؼ��֣�");
		scanf("%s", library.book[library.count].keyword);
		printf("\t\t�����������鼮���⣺");
		scanf("%s", library.book[library.count].theme);
		printf("\t\t�����������鼮�����");
		scanf("%s", library.book[library.count].classification);
		library.count++;
		printf("\n\t\t��ӳɹ���");
		printf("\n\t\t�Ƿ����¼��(1.������0.�˳�¼��)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
	save();
}

void print() {		//��ӡ
	int i;
	if (library.count) {
		print_title;
		for (i = 0; i < library.count; ++i)
			print_content;
	}
}

void del() {                   //����ɾ������
	int go = 1;
	system("cls");            //����
	print();			//�ȴ�ӡ
	if (library.count) {
		while (go) {
			char ISBN[20];	
			printf("\t\t��������Ҫɾ����ͼ���ISBN��");
			fflush(stdin);
			scanf("%s", ISBN);
			int i;
			for (i = 0; i < library.count; ++i)
				if (!strcmp(ISBN, library.book[i].ISBN))
					break;	
			if (i != library.count) {
				for(; i < library.count - 1; ++i) {
					strcpy(library.book[i].name, library.book[i + 1].name);
					strcpy(library.book[i].author, library.book[i + 1].author);
					strcpy(library.book[i].publisher, library.book[i + 1].publisher);
					strcpy(library.book[i].ISBN, library.book[i + 1].ISBN);
					strcpy(library.book[i].time, library.book[i + 1].time);
					strcpy(library.book[i].number, library.book[i + 1].number);
					library.book[i].price = library.book[i + 1].price;
					strcpy(library.book[i].available, library.book[i + 1].available);
					strcpy(library.book[i].keyword, library.book[i + 1].keyword);
					strcpy(library.book[i].theme, library.book[i + 1].theme);
					strcpy(library.book[i].classification, library.book[i + 1].classification);
				}
				library.count--;		
				printf("\n\t\tɾ���ɹ���");
			} else {		
				printf("\n\t\t����޴��飡");
			}
			printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
			fflush(stdin);
			scanf("%d", &go);
			printf("\n");
			if (go != 1) {
				go = 0;
				break;
			}
		}
		save();
		printf("\t\t��⵱ǰ���������\n\n");
		print();		//�ٴ�ӡ
		printf("\t\t���س�������");
		fflush(stdin);
		getchar();
	} else {
		printf("\t\tĿǰ������޲��飡\n");
		printf("\t\t���س�������");
		fflush(stdin);
		getchar();
	}

}

void swap(mbook &book1, mbook &book2) {		//����
	mbook tempbook;
	tempbook = book1;
	book1 = book2;
	book2 = tempbook;
}

void display_by_time() {	//������˳����ʾ
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].time, library.book[i + 1].time) > 0) {
				swap(library.book[i], library.book[i + 1]);		//����
			}
	save();
	printf("\n");
	print();
	printf("\t\t���س�������");
	fflush(stdin);
	getchar();
}

void display_by_name() {	//������˳����ʾ
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].name, library.book[i + 1].name) > 0) {
				swap(library.book[i], library.book[i + 1]);		//����
			}
	save();
	printf("\n");
	print();
	printf("\t\t���س�������");
	fflush(stdin);
	getchar();
}

void display_by_author() {	//������˳����ʾ
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].author, library.book[i + 1].author) > 0) {
				swap(library.book[i], library.book[i + 1]);		//����
			}
	save();
	printf("\n");
	print();
	printf("\t\t���س�������");
	fflush(stdin);
	getchar();
}

void display_by_number() {	//��������˳����ʾ
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].number, library.book[i + 1].number) > 0) {
				swap(library.book[i], library.book[i + 1]);		//����
			}
	save();
	printf("\n");
	print();
	printf("\t\t���س�������");
	fflush(stdin);
	getchar();
}

void display_by_ISBN() {	//��ISBN˳����ʾ
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].ISBN, library.book[i + 1].ISBN) > 0) {
				swap(library.book[i], library.book[i + 1]);		//����
			}
	save();
	printf("\n");
	print();
	printf("\t\t���س�������");
	fflush(stdin);
	getchar();
}

void display() {	//��ʾ��Ϣ
	if (library.count) {
		int chose;
		do {
			system("cls");            //����
			printf("\t\t*********************************************\n");
			printf("\t\t\t1------------------������˳����ʾ\n");
			printf("\t\t\t2------------------������˳����ʾ\n");
			printf("\t\t\t3------------------������˳����ʾ\n");
			printf("\t\t\t4------------------��������˳����ʾ\n");
			printf("\t\t\t5------------------��ISBN˳����ʾ\n");
			printf("\t\t\t0------------------����\n");
			printf("\t\t*********************************************\n") ;
			printf("\t\t��ѡ��");
			scanf("%d", &chose);
			switch (chose) {
			case 1:
				display_by_time();
				break;
			case 2:
				display_by_name();
				break;
			case 3:
				display_by_author();
				break;
			case 4:
				display_by_number();
				break;
			case 5:
				display_by_ISBN();
				break;
			case 0:
				return;
			default:
				printf("\n\t\tѡ������������ѡ��");
				printf("\n\t\t���س�������");
				fflush(stdin);
				getchar();
			}
		} while (chose);
		fflush(stdin);
		getchar();
	} else {
		system("cls");
		printf("\t\tĿǰ������޲��飡\n");
		printf("\t\t���س�������");
	}
}

void modify() {		//�޸�ͼ����Ϣ
	if (library.count) {
		int go = 1;
		system("cls");            //����
		while (go) {
			char ISBN[20];	
			printf("\t\t��������Ҫ�޸ĵ�ͼ���ISBN��");
			fflush(stdin);
			scanf("%s", ISBN);
			printf("\n");
			int i;
			for (i = 0; i < library.count; ++i)
				if (!strcmp(ISBN, library.book[i].ISBN)) {
					print_title;
					print_content;
				   break;
			   }
			if (i != library.count) {
				mbook book;
				printf("\n\t\t�������޸ĺ��ͼ�����Ϣ\n");
				printf("\t\t������ͼ������");
				scanf("%s", book.name);
				printf("\t\t��������������");
				scanf("%s", book.author);
				printf("\t\t����������磺");
				scanf("%s", book.publisher);
				printf("\t\t������ISBN��");
				scanf("%s", book.ISBN);
				printf("\t\t�������������:");
				scanf("%s", book.time);
				printf("\t\t����������ţ�");
				scanf("%s", book.number);
				printf("\t\t������۸�");
				fflush(stdin);
				scanf("%f", &book.price);
				printf("\t\t�������Ƿ�ɽ裺");
				scanf("%s", book.available);
				printf("\t\t������ؼ��֣�");
				scanf("%s", book.keyword);
				printf("\t\t���������⣺");
				scanf("%s", book.theme);
				printf("\t\t���������");
				scanf("%s", book.classification);
				strcpy(library.book[i].name, book.name);
				strcpy(library.book[i].author, book.author);
				strcpy(library.book[i].publisher, book.publisher);
				strcpy(library.book[i].ISBN, book.ISBN);
				strcpy(library.book[i].time, book.time);
				strcpy(library.book[i].number, book.number);
				library.book[i].price = book.price;
				strcpy(library.book[i].available, book.available);
				strcpy(library.book[i].keyword, book.keyword);
				strcpy(library.book[i].theme, book.theme);
				strcpy(library.book[i].classification, book.classification);
				printf("\n\t\t�޸ĳɹ���");
				save();
			} else {
				printf("\t\t����޴��飡");
			}
			printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
			fflush(stdin);
			scanf("%d", &go);
			printf("\n");
			if (go != 1) {
				go = 0;
				break;
			}
		}
	} else {
		system("cls");
		printf("\t\tĿǰ������޲��飡\n");
		printf("\t\t���س�������");
	}
}

void search_by_name() {          //���尴������ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ������: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].name)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_author() {          //���尴��������ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ��������: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].author)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_publisher() {		//���������ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ�ĳ�����: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].publisher)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_ISBN() {		//��ISBN��ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ��ISBN: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].ISBN)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_time() {		//���������ڲ�ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ������: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].time)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_number() {		//�������Ų�ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ�ļ�����: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].number)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_price() {	//���۸��ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		float price = 0.0;;
		printf("\t\t������Ҫ��ѯ�ļ۸�: ");
		fflush(stdin);
		scanf("%f", price);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (library.book[i].price == price) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_available() {		//���ɽ������ѯ
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ�Ŀɽ����: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].available)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_keyword() {		//���ؼ��ʲ���
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ�Ĺؼ���: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].keyword)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_theme() {	//���������
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ������: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].theme)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_classification() {	//��������
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t������Ҫ��ѯ�����: ");
		fflush(stdin);
		scanf("%s", s);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (!strcmp(s, library.book[i].classification)) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			} 
		if (flag) {
			printf("\t\t����޴��飡\n");
			fflush(stdin);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search() {        //�����ѯ����
	if (library.count) {
		int chose;
		do {
			system("cls");
		    printf("\t\t*********************************************\n");
			printf("\t\t\t1------------------����������\n");
			printf("\t\t\t2------------------������������\n");
			printf("\t\t\t3------------------�����������\n");
			printf("\t\t\t4------------------��ISBN����\n");
			printf("\t\t\t5------------------���������ڲ���\n");
			printf("\t\t\t6------------------�������Ų���\n");
			printf("\t\t\t7------------------���۸����\n");
			printf("\t\t\t8------------------���Ƿ�ɽ����\n");
			printf("\t\t\t9------------------���ؼ��ֲ���\n");
			printf("\t\t\t10-----------------���������\n");
			printf("\t\t\t11-----------------��������\n");
			printf("\t\t\t0------------------����\n");
			printf("\t\t*********************************************\n") ;
			printf("\t\t��ѡ��");
			fflush(stdin);
			scanf("%d", &chose);
			switch(chose) {
			case 1:
				search_by_name();
				break;
			case 2:
				search_by_author();
				break;
			case 3:
				search_by_publisher();
				break;
			case 4:
				search_by_ISBN();
				break;
			case 5:
				search_by_time();
				break;
			case 6:
				search_by_number();
				break;
			case 7:
				search_by_price();
				break;
			case 8:
				search_by_available();
				break;
			case 9:
				search_by_keyword();
				break;
			case 10:
				search_by_theme();
				break;
			case 11:
				search_by_classification();
				break;
			case 0:
				return;
			default:
				printf("\n\t\tѡ������������ѡ��");
				printf("\n\t\t���س�������");
				fflush(stdin);
				getchar();
			}
		} while (chose);
	} else {
		system("cls");
		printf("\t\tĿǰ������޲��飡\n");
		printf("\t\t���س�������");
	}
}

void count_1() {	//ͳ�ƹ���1
	int go  = 1;
	while (go) {
		int i, flag = 1, t = 0;
		float from, to;
		printf("\t\t������۸����ʼ�㣺\n");
		printf("\t\t�ӣ�");
		scanf("%f", &from);
		printf("\t\t����");
		scanf("%f", &to);
		printf("\n");
		for (i = 0; i < library.count; ++i)
			if (library.book[i].price <= to && library.book[i].price >= from) {
				flag = 0;
				++t;
				if (t == 1)
					print_title;
				print_content;
			}
		if (flag) {
				printf("\t\t����޷���������ͼ�飡");
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void count_2() {	//ͳ�ƹ���2
	int go = 1;
	while (go) {
		int i, num = 0, flag = 1;
		float sum = 0.0, average = 0.0;
		char classification[20];
		printf("\t\t��������Ҫͳ�Ƶ�ͼ�����");
		scanf("%s", classification);
		for (i = 0; i < library.count; ++i)
			if (!strcmp(classification, library.book[i].classification)) {
				++num;
				flag = 0;
				sum += library.book[i].price;
			}
		if (flag) {
				printf("\n\t\t����޸�����ͼ�飡");
		} else {
			average = sum / num;
			printf("\t\t%s����ͼ��ƽ���۸��ǣ�%3.2f\n", classification, average);
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void count_3() {	//ͳ�ƹ���3
	int i, num = 0, flag = 1;
	float rate;
	char available[10] = "��";
	for (i = 0; i < library.count; ++i)
		if (!strcmp(available, library.book[i].available)) {
			++num;
			flag = 0;
		}
	if (flag) {
			printf("\n\t\t����޿ɽ��ͼ�飡");			
	} else {
		rate = ((float)num / library.count) * 100;
		printf("\t\t�ɽ�ͼ��������ǣ�%d", num);
		printf("\n\t\t��ռ����Ϊ��%3.2f%%", rate);
	}
	printf("\n\n\t\t���س�������");
	fflush(stdin);
	getchar();
}

void count() {		//ͳ�ƺ���
	int chose;
	do {
		system("cls");
		printf("\t\t*********************************************\n");
		printf("\t\t\t1------ͳ��ĳһ�۸�ε�ͼ����Ϣ\n");
		printf("\t\t\t2------ͳ��ĳһ��ͼ���ƽ���۸�\n");
		printf("\t\t\t3------ͳ��ÿ�տɽ��鼮�������ͱ���\n");
		printf("\t\t\t0------����\n");
		printf("\t\t*********************************************\n") ;
		printf("\t\t��ѡ��");
		fflush(stdin);
		scanf("%d", &chose);
		switch(chose) {
		case 1:
			count_1();
			break;      
		case 2:
			count_2();
			break;
		case 3:
			count_3();
			break;
		case 0:
			return;
		default:
			printf("\n\t\tѡ������������ѡ��");
			printf("\n\t\t���س�������");
			fflush(stdin);
			getchar();
		}
	} while (chose);
}

void Borrow() {		//����
	if (library.count) {
		int go = 1;
		while (go) {
			int i, flag = 1;
			char ISBN[20];
			printf("\t\t�������������ͼ���ISBN��");
			scanf("%s", ISBN);
			for (i = 0; i < library.count; ++i)
				if (!strcmp(ISBN, library.book[i].ISBN)) {
					flag = 0;
					if (!strcmp("��", library.book[i].available)) {
						strcpy(library.book[i].available, "��");
						printf("\n\t\t���ĳɹ���");
					} else {
						printf("\n\t\t�����ѽ��, ����ʧ�ܣ�");
					}
					break;
				}
			if (flag) {
				printf("\n\t\t����޴��飡");
			}
			printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
			fflush(stdin);
			scanf("%d", &go);
			printf("\n");
			if (go != 1) {
				go = 0;
				break;
			}
		}
		save();
	} else {
		printf("\n\t\tĿǰ������޲���ɽ裡");
		printf("\n\t\t���س�������");
		fflush(stdin);
		getchar();
	}
}

void Return() {		//�黹
	int go = 1;
	while (go) {
		int i, flag = 1;
		char ISBN[20];
		printf("\t\t����������黹ͼ���ISBN��");
		scanf("%s", ISBN);
		for (i = 0; i < library.count; ++i)
			if (!strcmp(ISBN, library.book[i].ISBN)) {
				flag = 0;
				if (!strcmp("��", library.book[i].available)) {
					strcpy(library.book[i].available, "��");
					printf("\n\t\t�黹�ɹ���");
				} else {
					printf("\n\t\t�������������, �黹ʧ�ܣ�");
				}
				break;
			}
		if (flag) {
			printf("\n\t\t����޴��飡");
		}
		printf("\n\t\t�Ƿ�������в���(1.������0.����)��");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
	save();
}

void borrowOrReturn() {		//���ĺ͹黹
	int chose;
	do {
		system("cls");            //����
		printf("\t\t*********************************************\n");
		printf("\t\t\t1------------------����ͼ��\n");
		printf("\t\t\t2------------------�黹ͼ��\n");
		printf("\t\t\t0------------------����\n");
		printf("\t\t*********************************************\n") ;
	    printf("\t\t��ѡ��");
		scanf("%d", &chose);
		switch (chose) {
		case 1:
			Borrow();
			break;
		case 2:
			Return();
			break;
		case 0:
			return;
		default:
			printf("\n\t\tѡ������������ѡ��");
			printf("\n\t\t���س�������");
			fflush(stdin);
			getchar();
		}
	} while (chose);
}

void main()
{
	system("color 0A");
	FILE *fp;
	if ((fp = fopen("library.txt", "r")) == NULL) {
		printf("\n���ܴ�ͼ����Ϣ��\n");
		fp = fopen("library.txt", "w+");
		printf("\n��ʼ��ͼ����Ϣ��,��ʼ��֮��Ҫ��������\n");
		library.count = 0;
		fwrite(&library.count, sizeof(int), 1, fp);
		fclose(fp);
		return;
	}
	fread(&library.count, sizeof(int), 1, fp);
	fread(library.book, sizeof(library.book[0]), library.count, fp);
	fclose(fp);
	int chose;
	do {
		system("cls");
		printf("\n\n\n\n\n\t\t\t\tͼ����Ϣ����ϵͳ\t\t\t\t\n");
		printf("\t\t*********************************************\n");
		printf("\t\t\t1 ------------------���ͼ����Ϣ\n");
		printf("\t\t\t2 ------------------ɾ��ͼ����Ϣ\n");
   		printf("\t\t\t3 ------------------��ѯͼ����Ϣ\n");
		printf("\t\t\t4 ------------------��ʾͼ����Ϣ\n");
		printf("\t\t\t5 ------------------�޸�ͼ����Ϣ\n");
		printf("\t\t\t6 ------------------���Ĺ黹ͼ��\n");
		printf("\t\t\t7 ------------------ͳ��ͼ����Ϣ\n");
		printf("\t\t\t0 ------------------�˳�ϵͳ\n");
		printf("\t\t*********************************************\n");
		printf("\t\t��ѡ��");
		fflush(stdin);
		scanf("%d", &chose);
		switch(chose) {
		case 1:
			putin();
			break;
		case 2:
			del();
			break;
		case 3:
			search();
			break;
		case 4:
			display();
			break;
		case 5:
			modify();
			break;
		case 6:
			borrowOrReturn();
			break;
		case 7:
			count();
			break;
		case 0:
			printf("\n\t\t�˳�\n\n");
			break;
		default:
			printf("\n\t\tѡ������������ѡ��");
			printf("\n\t\t���س�������");
			fflush(stdin);
			getchar();
		}
	} while(chose);
	save();
}

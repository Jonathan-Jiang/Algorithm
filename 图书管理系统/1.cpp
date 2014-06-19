//图书馆信息管理系统
//使用C++语言开发
//小组成员：戴胜冬(组长)、方迎春、徐伟雷、江进、汪晖
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 200	//最大的图书数
//下面的宏定义用来控制输出格式
#define print_title printf("图书名\t\t     作者名   出版社\t\t   ISBN\t\t\t出版日期     检索号\t  价格\t 可借   关键字\t\t     主题\t\t  类别\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n")
#define print_content printf("%-20s %-8s %-20s %-20s %-12s %-12s %-4.2f  %-6s %-20s %-20s %-12s\n", library.book[i].name, library.book[i].author, library.book[i].publisher, library.book[i].ISBN, library.book[i].time, library.book[i].number, library.book[i].price, library.book[i].available, library.book[i].keyword, library.book[i].theme, library.book[i].classification)

typedef struct {	
	char name[20];	//书名
	char author[20];	//作者
	char publisher[50];	//出版社
	char ISBN[20];		//ISBN
	char time[20];	//出版时间
	char number[20];	//检索号
	float price;	//价格
	char available[20];		//是否可借
	char keyword[20];	//关键字
	char theme[50];		//主题
	char classification[20];	//类别
} mbook;

typedef struct {
	int count;	//书的本数
	mbook book[N];	//最大可有N本书
} mlibrary;

mlibrary library;	//图书馆

void save();	//保存图书信息。
void putin();     //定义添加函数
void print();	//打印
void del();                   //定义删除函数
void search_by_name();         //定义按书名查询
void search_by_author();          //定义按作者名查询
void search_by_publisher();		//按出版社查询
void search_by_ISBN();		//按ISBN查询
void search_by_time();		//按出版日期查询
void search_by_number();		//按检索号查询
void search_by_price();	//按价格查询
void search_by_available();		//按可借情况查询
void search_by_keyword();		//按关键词查找
void search_by_theme();	//按主题查找
void search_by_classification();	//按类别查找
void search();        //定义查询函数
void swap(mbook &book1, mbook &book2);	//交换
void display_by_time();	//按年月顺序显示
void display_by_name();	//按书名顺序显示
void display_by_author();	//按作者顺序显示
void display_by_number();	//按检索号顺序显示
void display_by_ISBN();	//按ISBN顺序显示
void display();	//显示信息
void modify();	//修改图书信息
void Borrow();		//借阅
void Return();		//归还
void borrowOrReturn();		//借阅和归还
void count_1();	//统计动能1
void count_2();	//统计功能2
void count_3();	//统计功能3
void count();		//统计函数

void save()	{	//保存图书信息。
	FILE *fp;
	if ((fp = fopen("library.txt", "w")) == NULL) {
		printf("\n不能保存图书信息\n");
		return;
	}
	fwrite(&library.count, sizeof(int), 1, fp);
	fwrite(library.book, sizeof(library.book[0]), library.count, fp);
	fclose(fp);
}

void putin() {      //定义添加函数
	int go = 1;
	system("cls");
	while (go) {
		printf("\t\t请输入书名：");
		scanf("%s", library.book[library.count].name);
		printf("\t\t请输入作者名：");
		scanf("%s", library.book[library.count].author);
		printf("\t\t请输入出版社：");
		scanf("%s", library.book[library.count].publisher);
		printf("\t\t请输入您的书籍的ISBN：");
		scanf("%s", library.book[library.count].ISBN);
		printf("\t\t请输入出版时间：");
		scanf("%s", library.book[library.count].time);
		printf("\t\t请输入您的书籍的检索号：");
		scanf("%s", library.book[library.count].number);
		printf("\t\t请输入该书的价格：");
		fflush(stdin);
		scanf("%f", &library.book[library.count].price);
		printf("\t\t请输入您的书籍是否可借：");
		scanf("%s", library.book[library.count].available);
		printf("\t\t请输入您的书籍的关键字：");
		scanf("%s", library.book[library.count].keyword);
		printf("\t\t请输入您的书籍主题：");
		scanf("%s", library.book[library.count].theme);
		printf("\t\t请输入您的书籍的类别：");
		scanf("%s", library.book[library.count].classification);
		library.count++;
		printf("\n\t\t添加成功！");
		printf("\n\t\t是否继续录入(1.继续；0.退出录入)：");
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

void print() {		//打印
	int i;
	if (library.count) {
		print_title;
		for (i = 0; i < library.count; ++i)
			print_content;
	}
}

void del() {                   //定义删除函数
	int go = 1;
	system("cls");            //清屏
	print();			//先打印
	if (library.count) {
		while (go) {
			char ISBN[20];	
			printf("\t\t请输入您要删除的图书的ISBN：");
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
				printf("\n\t\t删除成功！");
			} else {		
				printf("\n\t\t书库无此书！");
			}
			printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
			fflush(stdin);
			scanf("%d", &go);
			printf("\n");
			if (go != 1) {
				go = 0;
				break;
			}
		}
		save();
		printf("\t\t书库当前存书情况：\n\n");
		print();		//再打印
		printf("\t\t按回车键返回");
		fflush(stdin);
		getchar();
	} else {
		printf("\t\t目前书库中无藏书！\n");
		printf("\t\t按回车键返回");
		fflush(stdin);
		getchar();
	}

}

void swap(mbook &book1, mbook &book2) {		//交换
	mbook tempbook;
	tempbook = book1;
	book1 = book2;
	book2 = tempbook;
}

void display_by_time() {	//按年月顺序显示
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].time, library.book[i + 1].time) > 0) {
				swap(library.book[i], library.book[i + 1]);		//交换
			}
	save();
	printf("\n");
	print();
	printf("\t\t按回车键返回");
	fflush(stdin);
	getchar();
}

void display_by_name() {	//按书名顺序显示
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].name, library.book[i + 1].name) > 0) {
				swap(library.book[i], library.book[i + 1]);		//交换
			}
	save();
	printf("\n");
	print();
	printf("\t\t按回车键返回");
	fflush(stdin);
	getchar();
}

void display_by_author() {	//按作者顺序显示
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].author, library.book[i + 1].author) > 0) {
				swap(library.book[i], library.book[i + 1]);		//交换
			}
	save();
	printf("\n");
	print();
	printf("\t\t按回车键返回");
	fflush(stdin);
	getchar();
}

void display_by_number() {	//按检索号顺序显示
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].number, library.book[i + 1].number) > 0) {
				swap(library.book[i], library.book[i + 1]);		//交换
			}
	save();
	printf("\n");
	print();
	printf("\t\t按回车键返回");
	fflush(stdin);
	getchar();
}

void display_by_ISBN() {	//按ISBN顺序显示
	int i, j;
	for (j = 0; j < library.count; ++j)
		for (i = 0; i < library.count - j - 1; ++i)
			if (strcmp(library.book[i].ISBN, library.book[i + 1].ISBN) > 0) {
				swap(library.book[i], library.book[i + 1]);		//交换
			}
	save();
	printf("\n");
	print();
	printf("\t\t按回车键返回");
	fflush(stdin);
	getchar();
}

void display() {	//显示信息
	if (library.count) {
		int chose;
		do {
			system("cls");            //清屏
			printf("\t\t*********************************************\n");
			printf("\t\t\t1------------------按年月顺序显示\n");
			printf("\t\t\t2------------------按书名顺序显示\n");
			printf("\t\t\t3------------------按作者顺序显示\n");
			printf("\t\t\t4------------------按检索号顺序显示\n");
			printf("\t\t\t5------------------按ISBN顺序显示\n");
			printf("\t\t\t0------------------返回\n");
			printf("\t\t*********************************************\n") ;
			printf("\t\t请选择：");
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
				printf("\n\t\t选择有误，请重新选择");
				printf("\n\t\t按回车键返回");
				fflush(stdin);
				getchar();
			}
		} while (chose);
		fflush(stdin);
		getchar();
	} else {
		system("cls");
		printf("\t\t目前书库中无藏书！\n");
		printf("\t\t按回车键返回");
	}
}

void modify() {		//修改图书信息
	if (library.count) {
		int go = 1;
		system("cls");            //清屏
		while (go) {
			char ISBN[20];	
			printf("\t\t请输入您要修改的图书的ISBN：");
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
				printf("\n\t\t请输入修改后此图书的信息\n");
				printf("\t\t请输入图书名：");
				scanf("%s", book.name);
				printf("\t\t请输入作者名：");
				scanf("%s", book.author);
				printf("\t\t请输入出版社：");
				scanf("%s", book.publisher);
				printf("\t\t请输入ISBN：");
				scanf("%s", book.ISBN);
				printf("\t\t请输入出版日期:");
				scanf("%s", book.time);
				printf("\t\t请输入检索号：");
				scanf("%s", book.number);
				printf("\t\t请输入价格：");
				fflush(stdin);
				scanf("%f", &book.price);
				printf("\t\t请输入是否可借：");
				scanf("%s", book.available);
				printf("\t\t请输入关键字：");
				scanf("%s", book.keyword);
				printf("\t\t请输入主题：");
				scanf("%s", book.theme);
				printf("\t\t请输入类别：");
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
				printf("\n\t\t修改成功！");
				save();
			} else {
				printf("\t\t书库无此书！");
			}
			printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
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
		printf("\t\t目前书库中无藏书！\n");
		printf("\t\t按回车键返回");
	}
}

void search_by_name() {          //定义按书名查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的书名: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_author() {          //定义按作者名查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的作者名: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_publisher() {		//按出版社查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的出版社: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_ISBN() {		//按ISBN查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的ISBN: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_time() {		//按出版日期查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的日期: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_number() {		//按检索号查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的检索号: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_price() {	//按价格查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		float price = 0.0;;
		printf("\t\t请输入要查询的价格: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_available() {		//按可借情况查询
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的可借情况: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_keyword() {		//按关键词查找
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的关键词: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_theme() {	//按主题查找
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的主题: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search_by_classification() {	//按类别查找
	int go = 1;
	while (go) {
		int i, flag = 1, t = 0;
		char s[20]; 
		printf("\t\t请输入要查询的类别: ");
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
			printf("\t\t书库无此书！\n");
			fflush(stdin);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void search() {        //定义查询函数
	if (library.count) {
		int chose;
		do {
			system("cls");
		    printf("\t\t*********************************************\n");
			printf("\t\t\t1------------------按书名查找\n");
			printf("\t\t\t2------------------按作者名查找\n");
			printf("\t\t\t3------------------按出版社查找\n");
			printf("\t\t\t4------------------按ISBN查找\n");
			printf("\t\t\t5------------------按出版日期查找\n");
			printf("\t\t\t6------------------按检索号查找\n");
			printf("\t\t\t7------------------按价格查找\n");
			printf("\t\t\t8------------------按是否可借查找\n");
			printf("\t\t\t9------------------按关键字查找\n");
			printf("\t\t\t10-----------------按主题查找\n");
			printf("\t\t\t11-----------------按类别查找\n");
			printf("\t\t\t0------------------返回\n");
			printf("\t\t*********************************************\n") ;
			printf("\t\t请选择：");
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
				printf("\n\t\t选择有误，请重新选择");
				printf("\n\t\t按回车键返回");
				fflush(stdin);
				getchar();
			}
		} while (chose);
	} else {
		system("cls");
		printf("\t\t目前书库中无藏书！\n");
		printf("\t\t按回车键返回");
	}
}

void count_1() {	//统计功能1
	int go  = 1;
	while (go) {
		int i, flag = 1, t = 0;
		float from, to;
		printf("\t\t请输入价格的起始点：\n");
		printf("\t\t从：");
		scanf("%f", &from);
		printf("\t\t到：");
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
				printf("\t\t书库无符合条件的图书！");
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void count_2() {	//统计功能2
	int go = 1;
	while (go) {
		int i, num = 0, flag = 1;
		float sum = 0.0, average = 0.0;
		char classification[20];
		printf("\t\t请输入你要统计的图书类别：");
		scanf("%s", classification);
		for (i = 0; i < library.count; ++i)
			if (!strcmp(classification, library.book[i].classification)) {
				++num;
				flag = 0;
				sum += library.book[i].price;
			}
		if (flag) {
				printf("\n\t\t书库无该类别的图书！");
		} else {
			average = sum / num;
			printf("\t\t%s类别的图书平均价格是：%3.2f\n", classification, average);
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
		fflush(stdin);
		scanf("%d", &go);
		printf("\n");
		if (go != 1) {
			go = 0;
			break;
		}
	}
}

void count_3() {	//统计功能3
	int i, num = 0, flag = 1;
	float rate;
	char available[10] = "是";
	for (i = 0; i < library.count; ++i)
		if (!strcmp(available, library.book[i].available)) {
			++num;
			flag = 0;
		}
	if (flag) {
			printf("\n\t\t书库无可借的图书！");			
	} else {
		rate = ((float)num / library.count) * 100;
		printf("\t\t可借图书的数量是：%d", num);
		printf("\n\t\t所占比例为：%3.2f%%", rate);
	}
	printf("\n\n\t\t按回车键返回");
	fflush(stdin);
	getchar();
}

void count() {		//统计函数
	int chose;
	do {
		system("cls");
		printf("\t\t*********************************************\n");
		printf("\t\t\t1------统计某一价格段的图书信息\n");
		printf("\t\t\t2------统计某一类图书的平均价格\n");
		printf("\t\t\t3------统计每日可借书籍的数量和比例\n");
		printf("\t\t\t0------返回\n");
		printf("\t\t*********************************************\n") ;
		printf("\t\t请选择：");
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
			printf("\n\t\t选择有误，请重新选择");
			printf("\n\t\t按回车键返回");
			fflush(stdin);
			getchar();
		}
	} while (chose);
}

void Borrow() {		//借阅
	if (library.count) {
		int go = 1;
		while (go) {
			int i, flag = 1;
			char ISBN[20];
			printf("\t\t请输入您想借阅图书的ISBN：");
			scanf("%s", ISBN);
			for (i = 0; i < library.count; ++i)
				if (!strcmp(ISBN, library.book[i].ISBN)) {
					flag = 0;
					if (!strcmp("是", library.book[i].available)) {
						strcpy(library.book[i].available, "否");
						printf("\n\t\t借阅成功！");
					} else {
						printf("\n\t\t此书已借出, 借阅失败！");
					}
					break;
				}
			if (flag) {
				printf("\n\t\t书库无此书！");
			}
			printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
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
		printf("\n\t\t目前书库中无藏书可借！");
		printf("\n\t\t按回车键返回");
		fflush(stdin);
		getchar();
	}
}

void Return() {		//归还
	int go = 1;
	while (go) {
		int i, flag = 1;
		char ISBN[20];
		printf("\t\t请输入您想归还图书的ISBN：");
		scanf("%s", ISBN);
		for (i = 0; i < library.count; ++i)
			if (!strcmp(ISBN, library.book[i].ISBN)) {
				flag = 0;
				if (!strcmp("否", library.book[i].available)) {
					strcpy(library.book[i].available, "是");
					printf("\n\t\t归还成功！");
				} else {
					printf("\n\t\t此书已在书库中, 归还失败！");
				}
				break;
			}
		if (flag) {
			printf("\n\t\t书库无此书！");
		}
		printf("\n\t\t是否继续进行操作(1.继续；0.返回)：");
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

void borrowOrReturn() {		//借阅和归还
	int chose;
	do {
		system("cls");            //清屏
		printf("\t\t*********************************************\n");
		printf("\t\t\t1------------------借阅图书\n");
		printf("\t\t\t2------------------归还图书\n");
		printf("\t\t\t0------------------返回\n");
		printf("\t\t*********************************************\n") ;
	    printf("\t\t请选择：");
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
			printf("\n\t\t选择有误，请重新选择");
			printf("\n\t\t按回车键返回");
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
		printf("\n不能打开图书信息库\n");
		fp = fopen("library.txt", "w+");
		printf("\n初始化图书信息库,初始化之后要重启程序\n");
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
		printf("\n\n\n\n\n\t\t\t\t图书信息管理系统\t\t\t\t\n");
		printf("\t\t*********************************************\n");
		printf("\t\t\t1 ------------------添加图书信息\n");
		printf("\t\t\t2 ------------------删除图书信息\n");
   		printf("\t\t\t3 ------------------查询图书信息\n");
		printf("\t\t\t4 ------------------显示图书信息\n");
		printf("\t\t\t5 ------------------修改图书信息\n");
		printf("\t\t\t6 ------------------借阅归还图书\n");
		printf("\t\t\t7 ------------------统计图书信息\n");
		printf("\t\t\t0 ------------------退出系统\n");
		printf("\t\t*********************************************\n");
		printf("\t\t请选择：");
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
			printf("\n\t\t退出\n\n");
			break;
		default:
			printf("\n\t\t选择有误，请重新选择");
			printf("\n\t\t按回车键返回");
			fflush(stdin);
			getchar();
		}
	} while(chose);
	save();
}

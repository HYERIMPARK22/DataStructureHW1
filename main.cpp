#include <iostream>
using namespace std;
#define BOOKCNT 20
#define SAMPLECNT 100
#include <string>
#include "book.h"
#include <stdlib.h>
#include <time.h>
#include <iomanip>	//��� ����
typedef book ElementType;

int search(ElementType(&)[BOOKCNT]);
int searchIsbn(ElementType(&)[BOOKCNT]);
int searchName(ElementType(&)[BOOKCNT]);
void myflush();
ElementType ary[BOOKCNT];
void quicksort(ElementType(&)[BOOKCNT], int first, int last);
int partition(ElementType(&)[BOOKCNT], int first, int last);
void swapElements(ElementType *a, int first, int last);
void makedata();
void inputBorrowCnt();
void borrow(ElementType(&)[BOOKCNT], int findIndex);
int comp;
int randomSeed = 0;
void printLine();
void calComp();
void printBorrowCnt();
void printAry();

int main()
{
	int findIndex;
	makedata();
	printAry();
	inputBorrowCnt();
	findIndex = search(ary);
	borrow(ary, findIndex);
	calComp();

}
/*@preconditions:makedata()�� ���� å ������ ����Ǿ��ִ� book �迭 ���� �Ϸ�*/
/*@postconditions:�˻� ����� �����ϰ� �� ��Ŀ� ���� �˻��� å�� index�� ã�� findIndex ������ �����Ѵ�. */
/*@return:findIndex*/
int search(ElementType(&b)[BOOKCNT])
{
	int findIndex;
	int menuNum;
	printLine();
	cout << "\t\t    ������ ���� ���� �ý��� ����" << endl;
	printLine();
	while (1)
	{

		cout << "# �����Ϸ��� å�� �˻� �� ����� �����ϼ���(1.ISBN, 2.å ����) : ";
		cin >> menuNum;
		if (menuNum == 1)
		{
			findIndex = searchIsbn(ary);
			if (findIndex == -1) cout << "�ش��ϴ� å�� �������� �ʽ��ϴ�. �˻� ��ĺ��� �ٽ� �������ּ���. " << endl;
			else break;
		}
		else if (menuNum == 2)
		{
			findIndex = searchName(ary);
			if (findIndex == -1) cout << "�ش��ϴ� å�� �������� �ʽ��ϴ�. �˻� ��ĺ��� �ٽ� �������ּ���. " << endl;
			else break;
		}
		else
		{
			cout << "�޴� ��ȣ�� �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���" << endl;
			myflush();
		}
	}
	return findIndex;

}
/*@preconditions:search()�Լ� ���� ������ menuNum==1*/
/*@postconditions:�Է��� ISBN�� ������ ISBN�� ���� å�� index���� ã�� �� å�� ������ ����Ѵ�. */
/*@return:å�� index���� ����. ã�� ���ϸ� -1�� �����Ѵ�. */
int searchIsbn(ElementType(&b)[BOOKCNT])
{
	string temp;
	cout << "# �˻� �� å�� ISBN�� �Է��ϼ��� : ";
	cin >> temp;
	myflush();
	printLine();
	for (int i = 0; i < BOOKCNT; i++)
	{
		if (temp == b[i].getIsbn())
		{
			cout << "�˻� �� å �̸� : " << ary[i].getName() << endl;
			return i;
		}
	}
	return -1; //��ã���� -1 return 
}
/*@preconditions:search()�Լ� ���� ������ menuNum==2*/
/*@postconditions:�Է��� �ܾ ���� å�� index���� ã�� �� index���� findAry[]�� �����ϰ�, �� å�� ������ ����Ѵ�.
�������� �˻��Ǿ��� ��쿡�� ����� �Ϸù�ȣ�� �Բ� ����Ѵ�. �� �� ã�����ϴ� å�� �Ϸù�ȣ�� �߰��� �Է¹޴´�.
�Ϸù�ȣ�� ��ȿ���� findAry[]�� �̿��Ѵ�. */
/*@return:å�� index���� ����. ã�� ���ϸ� -1�� �����Ѵ�. */
int searchName(ElementType(&b)[BOOKCNT])		//å �̸����� �˻��Ұ�� �Ϸù�ȣ�� �Բ� ������ش�.(�ߺ��Ǵ� �ܾ�� �˻��� ��츦 ����)
{
	string temp;
	int findIndex;
	int i, j;
	int fcnt = 0;
	int findAry[BOOKCNT];		//�˻��� å�� �Ϸù�ȣ�� ������(��ȿ�� �˻�� ���)
	cout << "# �˻� �� å�� ������ �Է��ϼ��� : ";
	cin >> temp;
	myflush();
	printLine();
	for (i = 0; i < BOOKCNT; i++)
	{
		if (b[i].getName().find(temp) != -1)
		{
			cout << fcnt + 1 << ". �˻� �� å �̸� : " << ary[i].getName() << endl;
			cout << "* å�� �Ϸù�ȣ : " << ary[i].getNum() << endl;
			findAry[fcnt] = i;
			++fcnt;
			findIndex = i;
		}
	}

	if (fcnt == 0)		//å�� ��ã������
	{
		return -1;
	}


	else if (fcnt == 1)		//ã�� å�� 1���϶�
	{
		return findIndex;
	}

	else		//2�� �̻��� å�� ã������
	{
		printLine();
		while (1)
		{
			cout << "# �����Ϸ��� å�� �Ϸù�ȣ�� �Է��ϼ��� : ";		//�������� �˻��Ǿ����Ƿ� ���ϴ� å�� �������� �Ϸù�ȣ�� ���� �Է¹���
			cin >> findIndex;
			if (cin.fail())
			{
				cout << "�߸��� ������ �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
				myflush();
			}

			else 
			{
				for (j = 0; j < fcnt; j++)		//�Ϸù�ȣ ��ȿ�� �˻�
				{
					if (findIndex == findAry[j])
						return findIndex;
				}
				cout << "�Ϸù�ȣ�� �߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���." << endl;
				myflush();
			}
			
		}
	}
}
/*@preconditions:none*/
/*@postconditions:cin��ü�� ���λ��� �÷���(cin.fail()��)�� �ʱ�ȭ�ϰ� buffer�� ����. */
/*@return:none*/
void myflush()
{
	cin.clear();
	while (cin.get() != '\n');
}
/*@preconditions:first���� last���� quicksort�� �迭�� index��*/
/*@postconditions:����Ƚ���� �������� ������������ ����*/
/*@return:none*/
void quicksort(ElementType(&a)[BOOKCNT], int first, int last)
{
	if (first >= last) 
	{
		++comp;
		return;
	}


	int split(partition(a, first, last));
	++comp;

	quicksort(a, first, split - 1);
	++comp;
	quicksort(a, split + 1, last);
	++comp;

}
/*@preconditions:first���� last���� quicksort�� �迭�� index��*/
/*@postconditions:if���� �̿��� lastSmall�� ������Ű�� swapElements()�Լ��� ȣ���Ͽ� �����Ѵ�. */
/*@return:lastSmall��(pivot�� ��ġ)*/
int partition(ElementType(&a)[BOOKCNT], int first, int last)
{
	int lastSmall(first), i;

	for (i = first + 1; i <= last; i++) {
		++comp;

		if (a[i] > a[first]) { 
			++comp;
			++lastSmall;
			swapElements(a, lastSmall, i);

		}
	}

	++comp;
	swapElements(a, first, lastSmall); 
	return lastSmall; 
}
/*@preconditions:first���� last���� data�� swap�� �迭�� index��*/
/*@postconditions:first�� ����Ǿ��ִ� ���� last�� ����Ǿ��ִ� ���� swap�Ѵ�. */
/*@return:none*/
void swapElements(ElementType *a, int first, int last) {
	ElementType temp;
	temp = a[first];
	a[first] = a[last];
	a[last] = temp;

}
/*@preconditions:BOOKCNT���� ũ�� ��ŭ�� �迭�� ����*/
/*@postconditions:������ �Լ��� ���� ��ü ���� */
/*@return:none*/
void makedata() {		//�������� �˻��Ǵ� �ܾ�:�뼭,���,�µ�,���
	ElementType a("��� ������ �ʿ���", "���¿�", "������Ͽ콺", "��/������", 0, "9791162202913");
	ary[0] = a;
	ElementType b("�뼭�� �׿�", "�� Ƽ��", "����۰�����", "��ȭ", 1, "9788972889410");
	ary[1] = b;
	ElementType c("�ֽ� �µ����� �������", "������", "ȫ���������ǻ�", "���/����", 2, "9791156003434");
	ary[2] = c;
	ElementType d("�׿� ������ �����", "���� ���Ͻ�", "Ǫ����", "�Ҽ�", 3, "9791156756552");
	ary[3] = d;
	ElementType e("�����ε� �� ������", "��� �ɺ���", "��������", "�Ҽ�", 4, "9788937857591");
	ary[4] = e;
	ElementType f("�Ƴ����� ���� ���", "���� ���Ͻ�", "Ǫ����", "�Ҽ�", 5, "9791156756934");
	ary[5] = f;
	ElementType g("�̺��� ����ִ� �µ� �̾߱�", "���漷", "����������", "����", 6, "9788954420822");
	ary[6] = g;
	ElementType h("���� �� ���", "�迵��", "���е���", "�Ҽ�", 7, "9788954645614");
	ary[7] = h;
	ElementType i("����� ��Ź��", "JTBC ����� ��Ź�� ������", "�߾ӺϽ�", "�丮", 8, "9788927806837");
	ary[8] = i;
	ElementType j("�°����� ��ſ� �ָ��丮", "������", "������", "�丮", 9, "9788991193352");
	ary[9] = j;
	ElementType k("���� �ʴ� ���", "�����ں��� ����", "�˿���ġ�ڸ���", "�ǰ�", 10, "9788925563275");
	ary[10] = k;
	ElementType l("���۱��� ���ر��", "������", "��Ƽ�Ͻ�", "��/�������", 11, "9788997408139");
	ary[11] = l;
	ElementType m("���� ���ϱ� ���", "���� ������", "���÷翣��", "�ڱ���", 12, "9791186560617");
	ary[12] = m;
	ElementType n("ũ���̺� ���ε�", "���彼 ����", "��ũ�ν�", "�ι�", 13, "9791160560404");
	ary[13] = n;
	ElementType o("�뼭", "�޶��� ��", "�����ȹ̷�", "��/������", 14, "9788995501467");
	ary[14] = o;
	ElementType p("������", "������", "��������", "��ȭ", 15, "9791196287801");
	ary[15] = p;
	ElementType q("���� û�ҳ⹮�� 20��", "�ڻ��", "�б�����������", "��/������", 16, "9788969150233");
	ary[16] = q;
	ElementType r("����� �µ�", "�̱���", "������", "��/������", 17, "9791195522125");
	ary[17] = r;
	ElementType s("���� �� ����", "���� ȣŲ��", "��������", "�Ҽ�", 18, "9791162332528");
	ary[18] = s;
	ElementType t("Ǫ�� �� �� ��Ƽ", "������ ��ũ��ŷ", "��õ��", "��ġ/��ȸ", 19, "9788994898261");
	ary[19] = t;
}
/*@preconditions:BOOKCNT ũ���� �迭�� �� �濡 ��ü�� �����Ǿ��ִ�. */
/*@postconditions:����Ƚ�� ������ random�� ���� ����. */
/*@return:none*/
void inputBorrowCnt()
{
	srand((unsigned int)time(NULL) + randomSeed);
	for (int i = 0; i < BOOKCNT; i++)
	{
		ary[i].setBorrowCount((rand() % 100) + 100);	//100ȸ �̻��� �뿩 Ƚ��
	}
	++randomSeed;		//seed���� �ٸ��� �־� ����Ƚ���� �����ϰ� ���� ���� �����ش�.
}
/*@preconditions:BOOKCNT ũ���� �迭�� �� �濡 ��ü�� �����Ǿ��ְ� �����ϰ����ϴ� å �˻��� �Ϸ�Ǿ��ִ�.*/
/*@postconditions:������ �̸�,���� ��¥,�ݳ� ��¥ ���� �Ϸ�. ���� ��¥�� ���� �ð��� �޾ƿ��� �ݳ� ��¥�� �Ѵ� ��*/
/*@return:none*/
void borrow(ElementType(&b)[BOOKCNT], int findIndex)
{
	string tname;
	int borrowCnt;
	time_t ntime;	//���� ��¥�� �ð��� �޾ƿ��� ���� ����
	date rtime;
	struct tm *t;

	ntime = time(NULL);		//���� �ð��� �� ������ ��´�
	t = localtime(&ntime);	//�� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	printLine();
	cout << "\t\t\t    ���� ���� ���" << endl;
	printLine();
	cout << "* �����Ϸ��� ������ ����" << endl;
	cout << "1. ���� : " << ary[findIndex].getName() << endl;
	cout << "2. ���� : " << ary[findIndex].getAuthor() << endl;
	cout << "3. ���ǻ� : " << ary[findIndex].getCompany() << endl;
	cout << "4. category : " << ary[findIndex].getCategory() << endl;
	cout << "5. �Ϸù�ȣ : " << ary[findIndex].getNum() << endl;
	cout << "6. ISBN : " << ary[findIndex].getIsbn() << endl;
	printLine();

	cout << "# ������ �̸��� �Է��ϼ��� : ";
	cin >> tname;
	b[findIndex].setBorrowerName(tname);		//�����ϴ� ��� �̸� ����

	cout << "���� ��¥ : " << t->tm_year + 1900 << " �� " << t->tm_mon + 1 << " �� " << t->tm_mday << " �� �Դϴ�." << endl;
	rtime.year = t->tm_year + 1900;
	rtime.month = t->tm_mon + 2;	//�ݳ� ��¥�� �Ѵ� ��
	rtime.day = t->tm_mday - 1;
	if (rtime.month == 13)	//13���� ���� 1������ ó��
	{
		rtime.month = 1;
		++rtime.year;
	}
	b[findIndex].setReturnDate(rtime);		//�ݳ� ��¥ ����
	cout << "�ݳ� ��¥ : " << b[findIndex].getReturnDate().year << " �� " << b[findIndex].getReturnDate().month << " �� " << b[findIndex].getReturnDate().day << " �� �Դϴ�." << endl;
	borrowCnt = b[findIndex].getBorrowCount();		//����Ƚ�� 1ȸ ����
	b[findIndex].setBorrowCount(++borrowCnt);
}
/*@preconditions:none*/
/*@postconditions:line�� ����Ѵ�.*/
/*@return:none*/
void printLine()
{
	cout << "------------------------------------------------------------------------" << endl;
}
/*@preconditions:BOOKCNT ũ���� �迭�� �� �濡 ��ü�� �����Ǿ��ְ� �����ϰ����ϴ� å �˻��� �Ϸ�Ǿ� ������ �̸��� ���� ��¥, �ݳ� ��¥�� �ԷµǾ��ִ�.*/
/*@postconditions:quickSort ���� �� ���⵵�� ����Ͽ� ������ش�. �̸� SAMPLECNT�� �ݺ��ϰ� quickSort�� ���⵵�� ���Ѵ�. */
/*@return:none*/
void calComp()
{
	double avgComp = 0;
	cout.setf(ios::right);
	printLine();
	for (int i = 0; i < SAMPLECNT; i++) {
		comp = 0;		//���⵵ ���� �ʱ�ȭ
		inputBorrowCnt();		//���� Ƚ���� ä���ִ´�.
		//printAry();		//QuickSort �� ��� Ȯ��
		quicksort(ary, 0, BOOKCNT - 1);		//index���� �����ش�.
		cout << "* " << setw(3) << i+1 << setw(10) << ". the DB sample of quick sort's complexity : " << comp << endl;
		avgComp += comp;
		/*printBorrowCnt();*/		//����Ƚ�� Ȯ��
		//printAry();		//QuickSort �� ��� Ȯ��
	}
	avgComp = avgComp / SAMPLECNT;
	cout << "* the average of the DB sample's complexity : " << avgComp << endl;
	cout << endl;

	cout << "* the best of quick sort's complexity(nlog2(n)) is about 20log2(20) = 86.44" << endl;			//���� 2�̰� ������ 20
	cout << "* the average of quick sort's complexity(nlog4/3(n)) is about 20log4/3(20) = 208.27" << endl;	//���� 4/3�̰� ������ 20
	cout << "* the worst of quick sort's complexity(n^2) is about 20^2 = 400" << endl;

	printLine();
	cout << "\t\t    ������ ���� ���� �ý��� ����" << endl;
	printLine();
}
/*@preconditions:���� Ƚ�� ������ random���� ����Ǿ��ְ� �� ���� ���� QuickSort�� �Ǿ��ִ�.*/
/*@postconditions:���� Ƚ�� ���� ����Ѵ�.*/
/*@return:none*/
void printBorrowCnt()		//����Ƚ�� Ȯ�� �� ���
{
	for (int i = 0; i < BOOKCNT; i++)
	{
		cout << ary[i].getBorrowCount() << " ";
	}
	cout << endl;
}
/*@preconditions:�迭�� ��ü�� �����Ǿ��ִ�.*/
/*@postconditions:������ �ش��ϴ� ���� ����Ѵ�.*/
/*@return:none*/
void printAry()		//ary �� Ȯ�� �� ���
{
	cout.setf(ios::right);
	cout << setw(30) << "å����";
	cout << setw(30) << "���ڸ�";
	cout << setw(30) << "���ǻ�";
	cout << setw(30) << "ī�װ�";
	cout << setw(30) << "�Ϸù�ȣ";
	cout << setw(30) << "ISBN";
	cout << setw(30) << "����Ƚ��" << endl << endl;
	for (int i = 0; i < BOOKCNT; i++)
	{
		cout << setw(30) << ary[i].getName();
		cout << setw(30) << ary[i].getAuthor();
		cout << setw(30) << ary[i].getCompany();
		cout << setw(30) << ary[i].getCategory();
		cout << setw(30) << ary[i].getNum();
		cout << setw(30) << ary[i].getIsbn();
		cout << setw(30) << ary[i].getBorrowCount() << endl << endl;
	}
}
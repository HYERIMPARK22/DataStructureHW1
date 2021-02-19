#include <iostream>
using namespace std;
#define BOOKCNT 20
#define SAMPLECNT 100
#include <string>
#include "book.h"
#include <stdlib.h>
#include <time.h>
#include <iomanip>	//출력 정렬
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
/*@preconditions:makedata()를 통해 책 정보가 저장되어있는 book 배열 생성 완료*/
/*@postconditions:검색 방식을 선택하고 그 방식에 따라 검색한 책의 index를 찾고 findIndex 변수에 저장한다. */
/*@return:findIndex*/
int search(ElementType(&b)[BOOKCNT])
{
	int findIndex;
	int menuNum;
	printLine();
	cout << "\t\t    도서관 대출 관리 시스템 시작" << endl;
	printLine();
	while (1)
	{

		cout << "# 대출하려는 책을 검색 할 방식을 선택하세요(1.ISBN, 2.책 제목) : ";
		cin >> menuNum;
		if (menuNum == 1)
		{
			findIndex = searchIsbn(ary);
			if (findIndex == -1) cout << "해당하는 책이 존재하지 않습니다. 검색 방식부터 다시 선택해주세요. " << endl;
			else break;
		}
		else if (menuNum == 2)
		{
			findIndex = searchName(ary);
			if (findIndex == -1) cout << "해당하는 책이 존재하지 않습니다. 검색 방식부터 다시 선택해주세요. " << endl;
			else break;
		}
		else
		{
			cout << "메뉴 번호를 잘못 입력하셨습니다. 다시 입력해주세요" << endl;
			myflush();
		}
	}
	return findIndex;

}
/*@preconditions:search()함수 내의 변수인 menuNum==1*/
/*@postconditions:입력한 ISBN과 동일한 ISBN을 가진 책의 index값을 찾고 그 책의 제목을 출력한다. */
/*@return:책의 index값을 리턴. 찾지 못하면 -1을 리턴한다. */
int searchIsbn(ElementType(&b)[BOOKCNT])
{
	string temp;
	cout << "# 검색 할 책의 ISBN을 입력하세요 : ";
	cin >> temp;
	myflush();
	printLine();
	for (int i = 0; i < BOOKCNT; i++)
	{
		if (temp == b[i].getIsbn())
		{
			cout << "검색 한 책 이름 : " << ary[i].getName() << endl;
			return i;
		}
	}
	return -1; //못찾으면 -1 return 
}
/*@preconditions:search()함수 내의 변수인 menuNum==2*/
/*@postconditions:입력한 단어를 가진 책의 index값을 찾고 그 index값을 findAry[]에 저장하고, 그 책의 제목을 출력한다.
여러권이 검색되었을 경우에는 제목과 일련번호를 함께 출력한다. 그 후 찾고자하는 책의 일련번호를 추가로 입력받는다.
일련번호의 유효성은 findAry[]를 이용한다. */
/*@return:책의 index값을 리턴. 찾지 못하면 -1을 리턴한다. */
int searchName(ElementType(&b)[BOOKCNT])		//책 이름으로 검색할경우 일련번호를 함께 출력해준다.(중복되는 단어로 검색할 경우를 위해)
{
	string temp;
	int findIndex;
	int i, j;
	int fcnt = 0;
	int findAry[BOOKCNT];		//검색된 책의 일련번호를 저장함(유효성 검사시 사용)
	cout << "# 검색 할 책의 제목을 입력하세요 : ";
	cin >> temp;
	myflush();
	printLine();
	for (i = 0; i < BOOKCNT; i++)
	{
		if (b[i].getName().find(temp) != -1)
		{
			cout << fcnt + 1 << ". 검색 한 책 이름 : " << ary[i].getName() << endl;
			cout << "* 책의 일련번호 : " << ary[i].getNum() << endl;
			findAry[fcnt] = i;
			++fcnt;
			findIndex = i;
		}
	}

	if (fcnt == 0)		//책을 못찾았을때
	{
		return -1;
	}


	else if (fcnt == 1)		//찾은 책이 1권일때
	{
		return findIndex;
	}

	else		//2권 이상의 책을 찾았을때
	{
		printLine();
		while (1)
		{
			cout << "# 대출하려는 책의 일련번호를 입력하세요 : ";		//여러권이 검색되었으므로 원하는 책이 무엇인지 일련번호를 통해 입력받음
			cin >> findIndex;
			if (cin.fail())
			{
				cout << "잘못된 형식을 입력하셨습니다. 다시 입력해주세요." << endl;
				myflush();
			}

			else 
			{
				for (j = 0; j < fcnt; j++)		//일련번호 유효성 검사
				{
					if (findIndex == findAry[j])
						return findIndex;
				}
				cout << "일련번호를 잘못 입력하셨습니다. 다시 입력해주세요." << endl;
				myflush();
			}
			
		}
	}
}
/*@preconditions:none*/
/*@postconditions:cin객체의 내부상태 플래그(cin.fail()값)를 초기화하고 buffer를 비운다. */
/*@return:none*/
void myflush()
{
	cin.clear();
	while (cin.get() != '\n');
}
/*@preconditions:first값과 last값은 quicksort될 배열의 index값*/
/*@postconditions:대출횟수를 기준으로 오름차순으로 정렬*/
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
/*@preconditions:first값과 last값은 quicksort될 배열의 index값*/
/*@postconditions:if문을 이용해 lastSmall을 증가시키며 swapElements()함수를 호출하여 정렬한다. */
/*@return:lastSmall값(pivot의 위치)*/
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
/*@preconditions:first값과 last값은 data가 swap될 배열의 index값*/
/*@postconditions:first에 저장되어있는 값과 last에 저장되어있는 값을 swap한다. */
/*@return:none*/
void swapElements(ElementType *a, int first, int last) {
	ElementType temp;
	temp = a[first];
	a[first] = a[last];
	a[last] = temp;

}
/*@preconditions:BOOKCNT값의 크기 만큼의 배열이 잡힘*/
/*@postconditions:생성자 함수를 통해 객체 생성 */
/*@return:none*/
void makedata() {		//여러권이 검색되는 단어:용서,기술,온도,사람
	ElementType a("모든 순간이 너였다", "하태완", "위즈덤하우스", "시/에세이", 0, "9791162202913");
	ary[0] = a;
	ElementType b("용서해 테오", "질 티보", "어린이작가정신", "동화", 1, "9788972889410");
	ary[1] = b;
	ElementType c("최신 온도센서 기술동향", "정용택", "홍릉과학출판사", "기술/공학", 2, "9791156003434");
	ary[2] = c;
	ElementType d("죽여 마땅한 사람들", "피터 스완슨", "푸른숲", "소설", 3, "9791156756552");
	ary[3] = d;
	ElementType e("비하인드 허 아이즈", "사라 핀보로", "북폴리오", "소설", 4, "9788937857591");
	ary[4] = e;
	ElementType f("아낌없이 뺏는 사랑", "피터 스완슨", "푸른숲", "소설", 5, "9791156756934");
	ary[5] = f;
	ElementType g("켈빈이 들려주는 온도 이야기", "김충섭", "자음과모음", "과학", 6, "9788954420822");
	ary[6] = g;
	ElementType h("오직 두 사람", "김영하", "문학동네", "소설", 7, "9788954645614");
	ary[7] = h;
	ElementType i("냉장고를 부탁해", "JTBC 냉장고를 부탁해 제작팀", "중앙북스", "요리", 8, "9788927806837");
	ary[8] = i;
	ElementType j("온가족이 즐거운 주말요리", "구본길", "리스컴", "요리", 9, "9788991193352");
	ary[9] = j;
	ElementType k("늙지 않는 비밀", "엘리자베스 블랙번", "알에이치코리아", "건강", 10, "9788925563275");
	ary[10] = k;
	ElementType l("나쁜국어 독해기술", "진형석", "쏠티북스", "중/고등참고서", 11, "9788997408139");
	ary[11] = l;
	ElementType m("불행 피하기 기술", "롤프 도벨리", "인플루엔셜", "자기계발", 12, "9791186560617");
	ary[12] = m;
	ElementType n("크레이빙 마인드", "저드슨 브루어", "어크로스", "인문", 13, "9791160560404");
	ary[13] = n;
	ElementType o("용서", "달라이 라마", "오래된미래", "시/에세이", 14, "9788995501467");
	ary[14] = o;
	ElementType p("며느라기", "수신지", "귤프레스", "만화", 15, "9791196287801");
	ary[15] = p;
	ElementType q("나와 청소년문학 20년", "박상률", "학교도서관저널", "시/에세이", 16, "9788969150233");
	ary[16] = q;
	ElementType r("언어의 온도", "이기주", "말글터", "시/에세이", 17, "9791195522125");
	ary[17] = r;
	ElementType s("인투 더 워터", "폴라 호킨스", "북폴리오", "소설", 18, "9791162332528");
	ary[18] = s;
	ElementType t("푸드 앤 더 시티", "제니퍼 코크럴킹", "삼천리", "정치/사회", 19, "9788994898261");
	ary[19] = t;
}
/*@preconditions:BOOKCNT 크기의 배열의 각 방에 객체가 생성되어있다. */
/*@postconditions:대출횟수 변수에 random한 값이 들어간다. */
/*@return:none*/
void inputBorrowCnt()
{
	srand((unsigned int)time(NULL) + randomSeed);
	for (int i = 0; i < BOOKCNT; i++)
	{
		ary[i].setBorrowCount((rand() % 100) + 100);	//100회 이상의 대여 횟수
	}
	++randomSeed;		//seed값을 다르게 주어 대출횟수가 동일하게 들어가는 것을 막아준다.
}
/*@preconditions:BOOKCNT 크기의 배열의 각 방에 객체가 생성되어있고 대출하고자하는 책 검색이 완료되어있다.*/
/*@postconditions:대출자 이름,대출 날짜,반납 날짜 설정 완료. 대출 날짜는 현재 시간을 받아오고 반납 날짜는 한달 후*/
/*@return:none*/
void borrow(ElementType(&b)[BOOKCNT], int findIndex)
{
	string tname;
	int borrowCnt;
	time_t ntime;	//현재 날짜와 시간을 받아오기 위한 변수
	date rtime;
	struct tm *t;

	ntime = time(NULL);		//현재 시각을 초 단위로 얻는다
	t = localtime(&ntime);	//초 단위의 시간을 분리하여 구조체에 넣기
	printLine();
	cout << "\t\t\t    도서 대출 모드" << endl;
	printLine();
	cout << "* 대출하려는 도서의 정보" << endl;
	cout << "1. 제목 : " << ary[findIndex].getName() << endl;
	cout << "2. 저자 : " << ary[findIndex].getAuthor() << endl;
	cout << "3. 출판사 : " << ary[findIndex].getCompany() << endl;
	cout << "4. category : " << ary[findIndex].getCategory() << endl;
	cout << "5. 일련번호 : " << ary[findIndex].getNum() << endl;
	cout << "6. ISBN : " << ary[findIndex].getIsbn() << endl;
	printLine();

	cout << "# 대출자 이름을 입력하세요 : ";
	cin >> tname;
	b[findIndex].setBorrowerName(tname);		//대출하는 사람 이름 저장

	cout << "대출 날짜 : " << t->tm_year + 1900 << " 년 " << t->tm_mon + 1 << " 월 " << t->tm_mday << " 일 입니다." << endl;
	rtime.year = t->tm_year + 1900;
	rtime.month = t->tm_mon + 2;	//반납 날짜는 한달 후
	rtime.day = t->tm_mday - 1;
	if (rtime.month == 13)	//13월은 내년 1월으로 처리
	{
		rtime.month = 1;
		++rtime.year;
	}
	b[findIndex].setReturnDate(rtime);		//반납 날짜 저장
	cout << "반납 날짜 : " << b[findIndex].getReturnDate().year << " 년 " << b[findIndex].getReturnDate().month << " 월 " << b[findIndex].getReturnDate().day << " 일 입니다." << endl;
	borrowCnt = b[findIndex].getBorrowCount();		//대출횟수 1회 증가
	b[findIndex].setBorrowCount(++borrowCnt);
}
/*@preconditions:none*/
/*@postconditions:line을 출력한다.*/
/*@return:none*/
void printLine()
{
	cout << "------------------------------------------------------------------------" << endl;
}
/*@preconditions:BOOKCNT 크기의 배열의 각 방에 객체가 생성되어있고 대출하고자하는 책 검색이 완료되어 대출자 이름과 대출 날짜, 반납 날짜가 입력되어있다.*/
/*@postconditions:quickSort 실행 후 복잡도를 계산하여 출력해준다. 이를 SAMPLECNT번 반복하고 quickSort의 복잡도와 비교한다. */
/*@return:none*/
void calComp()
{
	double avgComp = 0;
	cout.setf(ios::right);
	printLine();
	for (int i = 0; i < SAMPLECNT; i++) {
		comp = 0;		//복잡도 변수 초기화
		inputBorrowCnt();		//대출 횟수를 채워넣는다.
		//printAry();		//QuickSort 전 출력 확인
		quicksort(ary, 0, BOOKCNT - 1);		//index값을 보내준다.
		cout << "* " << setw(3) << i+1 << setw(10) << ". the DB sample of quick sort's complexity : " << comp << endl;
		avgComp += comp;
		/*printBorrowCnt();*/		//대출횟수 확인
		//printAry();		//QuickSort 후 출력 확인
	}
	avgComp = avgComp / SAMPLECNT;
	cout << "* the average of the DB sample's complexity : " << avgComp << endl;
	cout << endl;

	cout << "* the best of quick sort's complexity(nlog2(n)) is about 20log2(20) = 86.44" << endl;			//밑이 2이고 진수가 20
	cout << "* the average of quick sort's complexity(nlog4/3(n)) is about 20log4/3(20) = 208.27" << endl;	//밑이 4/3이고 진수가 20
	cout << "* the worst of quick sort's complexity(n^2) is about 20^2 = 400" << endl;

	printLine();
	cout << "\t\t    도서관 대출 관리 시스템 종료" << endl;
	printLine();
}
/*@preconditions:대출 횟수 변수에 random값이 저장되어있고 이 값을 통해 QuickSort가 되어있다.*/
/*@postconditions:대출 횟수 값을 출력한다.*/
/*@return:none*/
void printBorrowCnt()		//대출횟수 확인 시 사용
{
	for (int i = 0; i < BOOKCNT; i++)
	{
		cout << ary[i].getBorrowCount() << " ";
	}
	cout << endl;
}
/*@preconditions:배열에 객체가 생성되어있다.*/
/*@postconditions:변수에 해당하는 값을 출력한다.*/
/*@return:none*/
void printAry()		//ary 값 확인 시 사용
{
	cout.setf(ios::right);
	cout << setw(30) << "책제목";
	cout << setw(30) << "저자명";
	cout << setw(30) << "출판사";
	cout << setw(30) << "카테고리";
	cout << setw(30) << "일련번호";
	cout << setw(30) << "ISBN";
	cout << setw(30) << "대출횟수" << endl << endl;
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
/*
일별 지출 목록은 리스트로 작성
일별 현황? 사용액은 큐로 작성
*/


#include <iostream>
#include <fstream>
#include "PQType.h"
#include "QueType.h"

using namespace std;

void nextDay(int& last_date)
{
	int year, month, day;

	year = last_date / 10000;
	month = (last_date / 100) % 100;
	day = last_date % 100;


	// 일 계산
	day += 1;

	// 월 계산
	if ((month == 1) || (month == 3) || (month == 5) || (month == 1) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
	{
		if (day == 32)
		{
			day = 1;
			month += 1;
		}
	}
	else if ((month == 4) || (month == 6) || (month == 1) || (month == 9) || (month == 11))
	{
		if (day == 31)
		{
			day = 1;
			month += 1;
		}
	}
	else if (month == 2)
	{
		if (day == 29)
		{
			day = 1;
			month += 1;
		}
	}

	//년 계산
	if (month == 13)
	{
		month = 1;
		year += 1;
	}


	last_date = year * 10000 + month * 100 + day;
}//이후에 구체적으로 바꿈

int main()
{
	QueType spend_writer;
	QueType temp;
	UnsortedType<int> spend_per_date;

	string save_category, usage;
	int command = 0, spending_goal = 0, spending_current = 0; //메뉴 조작용
	int last_date = 180620, load_date, garbage_date; //날짜 구분용
	fstream card("card usage.txt");
	ifstream load("savefile.txt");
	load >> spending_goal;
	

	PQType<int> statistics(6); //통계용
	PQType<int> temp_statistics(6); //통계용
	int number_percens, sum_for_st = 0, rank = 1;
	string string_percents;

	//위는 건들면 안되는 것들
	//아래는 프로그램 사용중 입력받을 것들
	
	int current_usage, usage_category, sum = 0;
	int i = 0;


	while (!load.eof())
	{
		load >> load_date >> current_usage >> usage_category >> usage;
		if (load_date != last_date)
		{
			while(load_date != last_date)
				nextDay(last_date);
			
			spending_current *= spend_writer.LengthIs();
			spend_writer.Enqueue(spend_per_date, last_date);
			spending_current /= spend_writer.LengthIs();
		}

		spend_writer.Enter_Usage(current_usage, usage_category, usage);
		
		if (usage_category == 1)
			statistics.Enqueue( "식비");
		else if (usage_category == 2)
			statistics.Enqueue( "교통");
		else if (usage_category == 3)
			statistics.Enqueue( "쇼핑");
		else if (usage_category == 4)
			statistics.Enqueue( "취미");
		else if (usage_category == 5)
			statistics.Enqueue( "기타");
		else statistics.Enqueue("기타");
		
		
		if (spend_writer.LengthIs() == 1)
			spending_current += current_usage;
		else
			spending_current = ((spending_current * (spend_writer.LengthIs())) + current_usage) / spend_writer.LengthIs();
		
		//지금까지의 내역 불러오기
		//last_date 업데이트
	}
	
	while (command != 7)
	{
		cout << endl << endl << last_date / 10000 << "년 " << (last_date / 100) % 100 << "월 " << last_date % 100 << "일" << endl;
		cout << "목표 평균 지출액 : " << spending_goal << "원" << endl;
		cout << "현재 평균 지출액 : " << spending_current << "원" << endl;
		cout << "지출액 종합 평가 : ";
		if (spending_current < spending_goal)
			cout << "양호" << endl;
		else cout << "초과" << endl;

		cout << " -----<MENU>-----" << endl;
		cout << " 0. 날  짜  변  경" << endl; //날짜를 하루 더함 = spendwriter에 원소를 추가함
		cout << " 1. 현금 지출 입력" << endl;
		cout << " 2. 카드 지출 입력" << endl;
		cout << " 3. 최근 지출 목록" << endl;
		cout << " 4. 일별 소비 현황" << endl;
		cout << " 5. 지  출  통  계" << endl;
		cout << " 6.  목표 재설정  " << endl;
		cout << " 7.   종   료    " << endl;
		cout << " ----------------" << endl;
		cout << "메뉴를 선택해 주세요 :";
		cin >> command;
		switch (command)
		{
		case 0:
			if (spend_writer.IsFull())
			{
				spend_writer.Dequeue(spend_per_date, garbage_date);
				sum = 0;
				spend_per_date.ResetList();
				for (i = 0; i < spend_per_date.LengthIs(); i++)
				{
					spend_per_date.GetNextItem(current_usage, save_category, usage);
					sum += current_usage;
				}
				spending_current = ((spending_current * spend_writer.LengthIs()) - sum) / (spend_writer.LengthIs());
				sum = 0;
			}
			
			nextDay(last_date);
			spend_per_date.MakeEmpty();

			spending_current *= spend_writer.LengthIs();
			spend_writer.Enqueue(spend_per_date, last_date);
			spending_current /= spend_writer.LengthIs();
			cout << "<<날짜가 하루 더해졌습니다>>" << endl;
			break;
		case 1:
			if (spend_writer.IsEmpty())
			{
				cout << "<<날짜가 입력되지 않았습니다>>" << endl << "<<날짜를 하루 더해주세요>>" << endl;
				break;
			}
			cout << "지출액을 입력하세요 : ";
			cin >> current_usage;
			cout << "(1.식비 2.교통 3.쇼핑 4.취미 5.기타)" << endl << "(5이상의 입력은 기타로 입력됩니다)";
			cin >> usage_category;
			cout << "사용처를 입력하세요(띄어쓰기 제외): ";
			cin >> usage; //이부분은 나중에 겟라인으로 바꿈
			spend_writer.Enter_Usage(current_usage, usage_category, usage);
			

			if (usage_category == 1)
				statistics.Enqueue("식비");
			else if (usage_category == 2)
				statistics.Enqueue("교통");
			else if (usage_category == 3)
				statistics.Enqueue("쇼핑");
			else if (usage_category == 4)
				statistics.Enqueue("취미");
			else if (usage_category == 5)
				statistics.Enqueue("기타");
			else statistics.Enqueue("기타");


			spending_current = ((spending_current * (spend_writer.LengthIs() )) + current_usage) / spend_writer.LengthIs();
			cout << "<<현금 지출이 입력되었습니다>>" << endl;
				//현금 사용 입력받음
			break;
		case 2:
			if (spend_writer.IsEmpty())
			{
				cout << "<<날짜가 입력되지 않았습니다>>" << endl << "<<날짜를 하루 더해주세요>>" << endl;
				break;
			}
			if (!card.eof())
			{

				card >> current_usage >> usage_category >> usage;
				spend_writer.Enter_Usage(current_usage, usage_category, usage);

				if (usage_category == 1)
					statistics.Enqueue("식비");
				else if (usage_category == 2)
					statistics.Enqueue("교통");
				else if (usage_category == 3)
					statistics.Enqueue("쇼핑");
				else if (usage_category == 4)
					statistics.Enqueue("취미");
				else if (usage_category == 5)
					statistics.Enqueue("기타");
				else statistics.Enqueue("기타");

				if (spend_writer.LengthIs() == 1)
					spending_current += current_usage;
				else
					spending_current = ((spending_current * (spend_writer.LengthIs())) + current_usage) / spend_writer.LengthIs();
				cout << "<<카드 지출 " << current_usage << "원 입력되었습니다>>" << endl;
				//카드 사용 입력받음
			}
			else
				cout << "<<더이상 카드 지출이 없습니다>>" << endl;
			break;
		case 3:
			if (!spend_writer.IsEmpty())
			{
				spend_writer.copy(temp);
				cout << "-------------------------------------------" << endl;
				cout << "      사용분야      사용 금액     사용처" << endl;
				cout << "-------------------------------------------" << endl;
				while (!temp.IsEmpty())
				{
					temp.Dequeue(spend_per_date, last_date);
					spend_per_date.ResetList();
					for (i = 0; i < spend_per_date.LengthIs(); i++)
					{
						spend_per_date.GetNextItem(current_usage, save_category, usage);
						cout << "       " << save_category << "          " << current_usage << "          " << usage << endl;
					}
				}
				cout << "-------------------------------------------" << endl;
				cout << "<<지출 내역을 모두 출력했습니다>>" << endl;
			}
			else
				cout << "<<지출 내역이 없습니다>>" << endl;
				//최근 지출 목록 불러옴
			break;
		case 4:
			if (!spend_writer.IsEmpty())
			{
				spend_writer.copy(temp);
				while (!temp.IsEmpty())
				{
					temp.Dequeue(spend_per_date, last_date);
					if (spend_per_date.LengthIs() != 0)
					{
						spend_per_date.ResetList();
						cout << endl << "---------<<날짜 " << last_date / 10000 << "년 " << (last_date / 100) % 100 << "월 " << last_date % 100 << "일>>---------" << endl;
						for (i = 0; i < spend_per_date.LengthIs(); i++)
						{
							spend_per_date.GetNextItem(current_usage, save_category, usage);
							cout << "    " << current_usage << "          " << save_category << "          " << usage << endl;
							sum += current_usage;
						}
						cout << "-----------------------------------------" << endl;
						cout << "  지출 건수 :" << spend_per_date.LengthIs() << "건    지출 총액 : " << sum << "원" << endl;
						cout << "-----------------------------------------" << endl;
						sum = 0;
					}
				}
				cout << endl << "<<지출 내역을 모두 출력했습니다>>" << endl;
			}
			else
				cout << "<<지출 내역이 없습니다>>" << endl;
				//일별 소비 현황 불러옴
			break;
		case 5:
			while (!statistics.IsEmpty())
			{
				statistics.Dequeue(number_percens, string_percents);
				temp_statistics.Enqueue_for_temp(number_percens, string_percents);
				sum_for_st += number_percens;
			}
			cout << "--------------------------" << endl;
			cout << " 총 사용 건수 : " << sum_for_st << " 건" << endl;
			cout << "--------------------------" << endl;
			while (!temp_statistics.IsEmpty())
			{
				temp_statistics.Dequeue(number_percens, string_percents);
				statistics.Enqueue_for_temp(number_percens, string_percents);
				cout << "   " <<  rank++ << "   " << string_percents << "  :  " << (float)(number_percens*100 / sum_for_st) << "%"<< endl;
			}

			cout << "--------------------------" << endl;
			cout << " << 통계를 모두 출력했습니다 >>" << endl;
			sum_for_st = 0;
			rank = 1;
				//분야별 통계 보여줌
			break;
		case 6:
			cout << "목표금액을 입력해 주세요 : ";
			cin >> spending_goal;
			cout << "<목표가 재설정 되었습니다>" << endl;
			break;
		case 7:
			cout << "프로그램을 종료합니다" << endl;
			break;
		default:
			cout << "해당하는 명령이 없습니다" << endl;
			break;
		}
	}


	//이후 세이브 파일 업데이트
	ofstream save("savefile.txt");
	save << spending_goal; //목표금액과 현재금액 업데이트

	//내역 저장
	while (!spend_writer.IsEmpty())
	{
		spend_writer.Dequeue(spend_per_date,last_date);

		if (spend_per_date.LengthIs() >= 1)
		{
			spend_per_date.ResetList();
			for (int i = 0; i < spend_per_date.LengthIs(); i++)
			{
				save << endl;

				spend_per_date.GetNextItem(current_usage, save_category, usage);
				save << last_date << " " << current_usage << " ";
				if (save_category == "식비")
					save << 1;
				else if (save_category == "교통")
					save << 2;
				else if (save_category == "쇼핑")
					save << 3;
				else if (save_category == "취미")
					save << 4;
				else if (save_category == "기타")
					save << 5;
				else save << 5;

				save << " " << usage;
			}
		}
		spend_per_date.MakeEmpty();
	}

	temp.~QueType();
	spend_writer.~QueType();
	spend_per_date.~UnsortedType();
	load.close();
	save.close();
	card.close();

	return 0;
}
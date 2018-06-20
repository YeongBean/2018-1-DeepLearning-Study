/*
�Ϻ� ���� ����� ����Ʈ�� �ۼ�
�Ϻ� ��Ȳ? ������ ť�� �ۼ�
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


	// �� ���
	day += 1;

	// �� ���
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

	//�� ���
	if (month == 13)
	{
		month = 1;
		year += 1;
	}


	last_date = year * 10000 + month * 100 + day;
}//���Ŀ� ��ü������ �ٲ�

int main()
{
	QueType spend_writer;
	QueType temp;
	UnsortedType<int> spend_per_date;

	string save_category, usage;
	int command = 0, spending_goal = 0, spending_current = 0; //�޴� ���ۿ�
	int last_date = 180620, load_date, garbage_date; //��¥ ���п�
	fstream card("card usage.txt");
	ifstream load("savefile.txt");
	load >> spending_goal;
	

	PQType<int> statistics(6); //����
	PQType<int> temp_statistics(6); //����
	int number_percens, sum_for_st = 0, rank = 1;
	string string_percents;

	//���� �ǵ�� �ȵǴ� �͵�
	//�Ʒ��� ���α׷� ����� �Է¹��� �͵�
	
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
			statistics.Enqueue( "�ĺ�");
		else if (usage_category == 2)
			statistics.Enqueue( "����");
		else if (usage_category == 3)
			statistics.Enqueue( "����");
		else if (usage_category == 4)
			statistics.Enqueue( "���");
		else if (usage_category == 5)
			statistics.Enqueue( "��Ÿ");
		else statistics.Enqueue("��Ÿ");
		
		
		if (spend_writer.LengthIs() == 1)
			spending_current += current_usage;
		else
			spending_current = ((spending_current * (spend_writer.LengthIs())) + current_usage) / spend_writer.LengthIs();
		
		//���ݱ����� ���� �ҷ�����
		//last_date ������Ʈ
	}
	
	while (command != 7)
	{
		cout << endl << endl << last_date / 10000 << "�� " << (last_date / 100) % 100 << "�� " << last_date % 100 << "��" << endl;
		cout << "��ǥ ��� ����� : " << spending_goal << "��" << endl;
		cout << "���� ��� ����� : " << spending_current << "��" << endl;
		cout << "����� ���� �� : ";
		if (spending_current < spending_goal)
			cout << "��ȣ" << endl;
		else cout << "�ʰ�" << endl;

		cout << " -----<MENU>-----" << endl;
		cout << " 0. ��  ¥  ��  ��" << endl; //��¥�� �Ϸ� ���� = spendwriter�� ���Ҹ� �߰���
		cout << " 1. ���� ���� �Է�" << endl;
		cout << " 2. ī�� ���� �Է�" << endl;
		cout << " 3. �ֱ� ���� ���" << endl;
		cout << " 4. �Ϻ� �Һ� ��Ȳ" << endl;
		cout << " 5. ��  ��  ��  ��" << endl;
		cout << " 6.  ��ǥ �缳��  " << endl;
		cout << " 7.   ��   ��    " << endl;
		cout << " ----------------" << endl;
		cout << "�޴��� ������ �ּ��� :";
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
			cout << "<<��¥�� �Ϸ� ���������ϴ�>>" << endl;
			break;
		case 1:
			if (spend_writer.IsEmpty())
			{
				cout << "<<��¥�� �Էµ��� �ʾҽ��ϴ�>>" << endl << "<<��¥�� �Ϸ� �����ּ���>>" << endl;
				break;
			}
			cout << "������� �Է��ϼ��� : ";
			cin >> current_usage;
			cout << "(1.�ĺ� 2.���� 3.���� 4.��� 5.��Ÿ)" << endl << "(5�̻��� �Է��� ��Ÿ�� �Էµ˴ϴ�)";
			cin >> usage_category;
			cout << "���ó�� �Է��ϼ���(���� ����): ";
			cin >> usage; //�̺κ��� ���߿� �ٶ������� �ٲ�
			spend_writer.Enter_Usage(current_usage, usage_category, usage);
			

			if (usage_category == 1)
				statistics.Enqueue("�ĺ�");
			else if (usage_category == 2)
				statistics.Enqueue("����");
			else if (usage_category == 3)
				statistics.Enqueue("����");
			else if (usage_category == 4)
				statistics.Enqueue("���");
			else if (usage_category == 5)
				statistics.Enqueue("��Ÿ");
			else statistics.Enqueue("��Ÿ");


			spending_current = ((spending_current * (spend_writer.LengthIs() )) + current_usage) / spend_writer.LengthIs();
			cout << "<<���� ������ �ԷµǾ����ϴ�>>" << endl;
				//���� ��� �Է¹���
			break;
		case 2:
			if (spend_writer.IsEmpty())
			{
				cout << "<<��¥�� �Էµ��� �ʾҽ��ϴ�>>" << endl << "<<��¥�� �Ϸ� �����ּ���>>" << endl;
				break;
			}
			if (!card.eof())
			{

				card >> current_usage >> usage_category >> usage;
				spend_writer.Enter_Usage(current_usage, usage_category, usage);

				if (usage_category == 1)
					statistics.Enqueue("�ĺ�");
				else if (usage_category == 2)
					statistics.Enqueue("����");
				else if (usage_category == 3)
					statistics.Enqueue("����");
				else if (usage_category == 4)
					statistics.Enqueue("���");
				else if (usage_category == 5)
					statistics.Enqueue("��Ÿ");
				else statistics.Enqueue("��Ÿ");

				if (spend_writer.LengthIs() == 1)
					spending_current += current_usage;
				else
					spending_current = ((spending_current * (spend_writer.LengthIs())) + current_usage) / spend_writer.LengthIs();
				cout << "<<ī�� ���� " << current_usage << "�� �ԷµǾ����ϴ�>>" << endl;
				//ī�� ��� �Է¹���
			}
			else
				cout << "<<���̻� ī�� ������ �����ϴ�>>" << endl;
			break;
		case 3:
			if (!spend_writer.IsEmpty())
			{
				spend_writer.copy(temp);
				cout << "-------------------------------------------" << endl;
				cout << "      ���о�      ��� �ݾ�     ���ó" << endl;
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
				cout << "<<���� ������ ��� ����߽��ϴ�>>" << endl;
			}
			else
				cout << "<<���� ������ �����ϴ�>>" << endl;
				//�ֱ� ���� ��� �ҷ���
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
						cout << endl << "---------<<��¥ " << last_date / 10000 << "�� " << (last_date / 100) % 100 << "�� " << last_date % 100 << "��>>---------" << endl;
						for (i = 0; i < spend_per_date.LengthIs(); i++)
						{
							spend_per_date.GetNextItem(current_usage, save_category, usage);
							cout << "    " << current_usage << "          " << save_category << "          " << usage << endl;
							sum += current_usage;
						}
						cout << "-----------------------------------------" << endl;
						cout << "  ���� �Ǽ� :" << spend_per_date.LengthIs() << "��    ���� �Ѿ� : " << sum << "��" << endl;
						cout << "-----------------------------------------" << endl;
						sum = 0;
					}
				}
				cout << endl << "<<���� ������ ��� ����߽��ϴ�>>" << endl;
			}
			else
				cout << "<<���� ������ �����ϴ�>>" << endl;
				//�Ϻ� �Һ� ��Ȳ �ҷ���
			break;
		case 5:
			while (!statistics.IsEmpty())
			{
				statistics.Dequeue(number_percens, string_percents);
				temp_statistics.Enqueue_for_temp(number_percens, string_percents);
				sum_for_st += number_percens;
			}
			cout << "--------------------------" << endl;
			cout << " �� ��� �Ǽ� : " << sum_for_st << " ��" << endl;
			cout << "--------------------------" << endl;
			while (!temp_statistics.IsEmpty())
			{
				temp_statistics.Dequeue(number_percens, string_percents);
				statistics.Enqueue_for_temp(number_percens, string_percents);
				cout << "   " <<  rank++ << "   " << string_percents << "  :  " << (float)(number_percens*100 / sum_for_st) << "%"<< endl;
			}

			cout << "--------------------------" << endl;
			cout << " << ��踦 ��� ����߽��ϴ� >>" << endl;
			sum_for_st = 0;
			rank = 1;
				//�оߺ� ��� ������
			break;
		case 6:
			cout << "��ǥ�ݾ��� �Է��� �ּ��� : ";
			cin >> spending_goal;
			cout << "<��ǥ�� �缳�� �Ǿ����ϴ�>" << endl;
			break;
		case 7:
			cout << "���α׷��� �����մϴ�" << endl;
			break;
		default:
			cout << "�ش��ϴ� ����� �����ϴ�" << endl;
			break;
		}
	}


	//���� ���̺� ���� ������Ʈ
	ofstream save("savefile.txt");
	save << spending_goal; //��ǥ�ݾװ� ����ݾ� ������Ʈ

	//���� ����
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
				if (save_category == "�ĺ�")
					save << 1;
				else if (save_category == "����")
					save << 2;
				else if (save_category == "����")
					save << 3;
				else if (save_category == "���")
					save << 4;
				else if (save_category == "��Ÿ")
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
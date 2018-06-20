
//�ִ� 500�ϰ��� ������ �����Ѵ�
//�����ϵ� ���� ǥ���Ҷ��� �ֱٳ�¥���� �����ش�
//�ֱٳ�¥�� ���� �������� �Էµȴ�

#include "UnsortedType.h"
class FullQueue
{};  

class EmptyQueue
{};  
class QueType
{
public: 
    QueType();
    // Class constructor.
    // Because there is a default constructor, the precondition 
    // that the queue has been initialized is omitted.
    QueType(int max);
    // Parameterized class constructor.
    ~QueType();
    // Class destructor.
    void MakeEmpty();
    // Function: Initializes the queue to an empty state.
    // Post: Queue is empty.
    bool IsEmpty() const;
    // Function: Determines whether the queue is empty.
    // Post: Function value = (queue is empty)
    bool IsFull() const;
    // Function: Determines whether the queue is full.
    // Post: Function value = (queue is full)
    void Enqueue(UnsortedType<int>& spend_per_date, int& f_date);
    // Function: Adds newItem to the rear of the queue.
    // Post: If (queue is full) FullQueue exception is thrown
    //       else newItem is at rear of queue.
    void Dequeue(UnsortedType<int>& spend, int& f_date);
    // Function: Removes front item from the queue and returns it in item.
    // Post: If (queue is empty) EmptyQueue exception is thrown
    //       and item is undefined
    //       else front element has been removed from queue and
    //       item is a copy of removed element.
	void Enter_Usage(int item, int categ, string usages);
	//ť�� ������ UnsortedType = ���� �Ǵ� ���� �ֱ� ��¥
	//ť�� ������ UnwortedType�� ������ �Է�
	int LengthIs();
	void copy(QueType& other);

private:
    int front;
    int rear;
	int* date;
	UnsortedType<int>* spend_per_date;
    int maxQue;
	int length;
};



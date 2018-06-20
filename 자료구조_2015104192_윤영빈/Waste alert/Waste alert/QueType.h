
//최대 500일간의 지출을 저장한다
//지출목록등 원소 표시할때는 최근날짜부터 보여준다
//최근날짜는 가장 마지막에 입력된다

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
	//큐의 마지막 UnsortedType = 오늘 또는 가장 최근 날짜
	//큐의 마지막 UnwortedType에 아이템 입력
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



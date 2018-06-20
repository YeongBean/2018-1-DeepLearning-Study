#include "QueType.h"

QueType::QueType(int max)
// Parameterized class constructor
// Post: maxQue, front, and rear have been initialized.
//       The array to hold the queue elements has been dynamically
//       allocated.
{ 
  maxQue = max + 1;
  front = maxQue - 1;
  rear = maxQue - 1;
  spend_per_date = new UnsortedType<int>[maxQue];
  date = new int[maxQue];
  length = 0;
}
QueType::QueType()          // Default class constructor
// Post: maxQue, front, and rear have been initialized.
//       The array to hold the queue elements has been dynamically
//       allocated.
{
  maxQue = 11;
  front = maxQue - 1;
  rear = maxQue - 1;
  spend_per_date = new UnsortedType<int>[maxQue];
  date = new int[maxQue];
  length = 0;
}
QueType::~QueType()         // Class destructor
{
	if (length > 0)
	{
		delete[]spend_per_date;
		delete[]date;
	}
}

void QueType::MakeEmpty()
// Post: front and rear have been reset to the empty state.
{
  front = maxQue - 1;
  rear = maxQue - 1;
  length = 0;
}

bool QueType::IsEmpty() const
// Returns true if the queue is empty; false otherwise.
{
  return (rear == front);
}

bool QueType::IsFull() const
// Returns true if the queue is full; false otherwise.
{
  return ((rear + 1) % maxQue == front);
}

void QueType::Enqueue(UnsortedType<int>& spend, int& f_date)
// Post: If (queue is not full) newItem is at the rear of the queue;
//       otherwise a FullQueue exception is thrown.  
{
  if (IsFull())
    throw FullQueue();
  else
  {
    rear = (rear +1) % maxQue;
    spend_per_date[rear] = spend;
	date[rear] = f_date;
	length += 1;
  }
}

void QueType::Dequeue(UnsortedType<int>& spend, int& f_date)
// Post: If (queue is not empty) the front of the queue has been 
//       removed and a copy returned in item; 
//       othersiwe a EmptyQueue exception has been thrown.
{
  if (IsEmpty())
    throw EmptyQueue();
  else
  {
    front = (front + 1) % maxQue;
    spend = spend_per_date[front];
	f_date = date[front];
	length -= 1;
  }
}

void QueType::Enter_Usage(int item, int categ, string usages)
{
	spend_per_date[rear].InsertItem(item, categ, usages);
}

int QueType::LengthIs()
{
	return length;
}

void QueType::copy(QueType& other)
{
	UnsortedType<int> temp;
	int date;
	other.MakeEmpty();
	for (int i = 0; i < length; i++)
	{
		other.Enqueue(this->spend_per_date[i], this->date[i]);
	}
}
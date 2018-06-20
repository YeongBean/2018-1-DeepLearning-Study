#include <string>
using namespace std;


template<class ItemType>
// Assumes ItemType is either a built-in simple type or a class
// with overloaded relational operators.
struct HeapType
{
  void ReheapDown(int root, int bottom);
  void ReheapUp(int root, int bottom);
  ItemType* elements;   // Array to be allocated dynamically
  string* categories_use; //지출 카테고리
  int numElements;
};

template <class ItemType>
void Swap(ItemType& item1, ItemType& item2, string& categ1, string& categ2)
{
	ItemType temp1;
	string temp2;
	
	temp1 = item1;
	item1 = item2;
	item2 = temp1;

	temp2 = categ1;
	categ1 = categ2;
	categ2 = temp2;
}

template<class ItemType>
void HeapType<ItemType>::ReheapUp(int root, int bottom)
// Post: Heap property is restored.
{
  int parent;
  
  if (bottom > root)
  {
    parent = (bottom-1) / 2;
    if (elements[parent] < elements[bottom])
    {
      Swap(elements[parent], elements[bottom], categories_use[parent], categories_use[bottom]);
      ReheapUp(root, parent);
    }
  }
}


template<class ItemType>
void HeapType<ItemType>::ReheapDown(int root, int bottom)
// Post: Heap property is restored.
{
  int maxChild;
  int rightChild;
  int leftChild;

  leftChild = root*2+1;
  rightChild = root*2+2;
  if (leftChild <= bottom)
  {
    if (leftChild == bottom)
      maxChild = leftChild;
    else
    {
      if (elements[leftChild] <= elements[rightChild])
        maxChild = rightChild;
      else
        maxChild = leftChild;
    }
    if (elements[root] < elements[maxChild])
    {
	  Swap(elements[root], elements[maxChild], categories_use[root], categories_use[maxChild]);

      ReheapDown(maxChild, bottom);
    }
  }
}
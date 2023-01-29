#include <iostream>
#include <time.h>

using namespace std;

template <class T>
class Element
{
public:
	Element(T _v, Element<T>* _next = nullptr, Element<T>* _prev = nullptr)
		:value(_v), next(_next), prev(_prev) {
		//cout << this << endl; //для перевірки, що всі елементи видаляються...
	}
	~Element() { /*cout << this << endl; для перевірки, що всі елементи видаляються...*/ }
	void setValue(T _v) { value = _v; }
	void setNext(Element<T>* _next) { next = _next; }
	void setPrev(Element<T>* _prev) { prev = _prev; }

	T getValue()const { return value; }

	Element<T>* getNext()const { return next; }
	Element<T>* getPrev()const { return prev; }

	void Print()const {
		if (this == nullptr) {
			cout << "Eror" << endl;
			return;
		}
		cout << value << "\t";
	}

private:
	T value;
	Element<T>* next;
	Element<T>* prev;
};

template <class T>
class LinkedList {
public:
	LinkedList();
	~LinkedList()
	{
		//cout << this << endl; //для перевірки, що всі елементи видаляються...
		Clear();
	}
	size_t size()const
	{
		return this->count;
	}
	void AddToHead(const T _v);
	void AddToTail(const T _v);
	void DeleteFromHead();
	void DeleteFromTail();

	Element<T>* getElement(const size_t _index);
	int getIndex(const T v);
	int replacing(const T data, const T v);
	void addElem(const T data, const size_t _index);
	void delElem(const size_t _index);
	void reverse();
	void Clear();

	void print()const;
private:
	size_t count;
	Element<T>* begin;
	Element<T>* end;
};

template<class T>
LinkedList<T>::LinkedList()
{
	begin = nullptr;
	end = nullptr;
	count = 0;
	//cout << this << endl; //для перевірки, що всі елементи видаляються...
}

template<class T>
void LinkedList<T>::AddToHead(const T _v)
{
	Element<T>* elem = new Element<T>(_v);
	elem->setNext(begin);
	if (begin != nullptr) {
		begin->setPrev(elem);
	}
	if (end == nullptr)
		end = elem;
	begin = elem;

	count++;
}

template<class T>
void LinkedList<T>::AddToTail(const T _v)
{
	Element<T>* elem = new Element<T>(_v);
	elem->setPrev(end);
	if (end != nullptr) {
		end->setNext(elem);
	}
	if (begin == nullptr)
		begin = elem;
	end = elem;

	count++;
}

template<class T>
void LinkedList<T>::DeleteFromHead()
{
	if (!begin) {
		return;
	}
	Element<T>* elem = begin->getNext();
	if (elem != nullptr)
		elem->setPrev(nullptr);
	else
		end = nullptr;
	delete begin;
	begin = elem;

	count--;
}

template<class T>
void LinkedList<T>::DeleteFromTail()
{
	if (!end) {
		return;
	}
	Element<T>* elem = end->getPrev();
	if (elem != nullptr)
		elem->setNext(nullptr);
	else
		begin = nullptr;
	delete end;
	end = elem;

	count--;
}

template<class T>
Element<T>* LinkedList<T>::getElement(const size_t _index)
{
	if (_index >= count)return nullptr;
	Element<T>* ind = begin;
	size_t i = 0;

	while (i != _index)
	{
		if (ind == nullptr) {
			return ind;
		}
		ind = ind->getNext();
		i++;
	}
	return ind;
}

template<class T>
int LinkedList<T>::getIndex(const T v)
{
	int ind = -1, i = 0;
	if (!begin)return ind;

	Element<T>* temp = begin;

	while (temp != nullptr)
	{
		if (temp->getValue() == v) {
			return ind = i;
		}
		temp = temp->getNext();
		i++;
	}
	if (ind == -1)
	{
		return ind;
	}
	return ind;
}

template<class T>
int LinkedList<T>::replacing(const T data, const T v)
{
	if (!begin) return 0;
	int i = 0;

	Element<T>* temp = begin;

	while (temp != nullptr)
	{
		if (temp->getValue() == data)
		{
			temp->setValue(v);
			i++;
		}
		temp = temp->getNext();
	}

	return i;
}

template<class T>
void LinkedList<T>::addElem(const T data, const size_t _index)
{
	if (_index > count) return;

	Element<T>* next = getElement(_index);
	if (next == nullptr) {
		return AddToTail(data);
	}

	Element<T>* prev = next->getPrev();
	if (prev == nullptr) {
		return AddToHead(data);
	}
	Element<T>* elem = new Element<T>(data);

	elem->setPrev(prev);
	elem->setNext(next);
	next->setPrev(elem);
	prev->setNext(elem);

	count++;
}

template<class T>
void LinkedList<T>::delElem(const size_t _index)
{
	Element<T>* elem = getElement(_index);
	if (elem == nullptr || _index > count)
		return;
	if (elem->getPrev() == nullptr) {
		DeleteFromHead();
		return;
	}
	if (elem->getNext() == nullptr) {
		DeleteFromTail();
		return;
	}

	Element<T>* prev = elem->getPrev();
	Element<T>* next = elem->getNext();
	next->setPrev(prev);
	prev->setNext(next);

	delete elem;
	count--;
}

template<class T>
void LinkedList<T>::reverse()
{
	Element<T>* current = begin;
	Element<T>* prev = NULL, * next = NULL;
	end = begin;

	while (current != NULL) {
		next = current->getNext();

		current->setNext(prev);
		current->setPrev(next);

		prev = current;
		current = next;
	}
	begin = prev;
}

template<class T>
void LinkedList<T>::print()const
{
	Element<T>* number = begin;
	while (number)
	{
		number->Print();
		number = number->getNext();
	}
	cout << endl;
}

template<class T>
void LinkedList<T>::Clear()
{
	if (!begin) {
		return;
	}
	while (begin)
	{
		DeleteFromHead();
	}
}

int main()
{
	srand(time(NULL));
	LinkedList<int>  lst;
	for (int i = 0; i < 6; i++) {
		lst.AddToTail(rand() % 100 + 1);
	}

	cout << "Size: " << lst.size() << endl;
	cout << "Array:" << endl;
		lst.print();
	//cout << "Size to replace: " << lst.replacing(1, 6) << endl;
	lst.reverse();
	cout << "Revers array:" << endl;
	lst.print();
	cout << "Size: " << lst.size() << endl;
	cout << "First element:" << endl;
	lst.getElement(0)->Print();
	cout << "\nLast element:" << endl;
	lst.getElement(lst.size()-1)->Print();
	cout << endl;

	return 0;
}
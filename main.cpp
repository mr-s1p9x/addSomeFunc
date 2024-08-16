#include <iostream>
using namespace std;

struct Element
{
    char data; // Данные
    Element* Next; // Адрес следующего элемента списка
};

class List
{
    Element* Head; // Адрес головного элемента списка
    Element* Tail; // Адрес хвостового элемента списка
    int Count; // Количество элементов списка

public:
    List();
    ~List();

    void Add(char data); // Добавление элемента в список
    void Del(); // Удаление головного элемента списка
    void DelAll(); // Удаление всего списка
    void Print(); // Распечатка содержимого списка
    int GetCount(); // Получение количества элементов в списке
    void AddIndex(char data, int index); // Добавление элемента на заданную позицию

    void DelAtIndex(int index); // Удаление элемента по заданной позиции
    void DelLast(); // Удаление последнего элемента
    int FindElement(char data); // Поиск заданного элемента
};

List::List()
{
    Head = Tail = NULL;
    Count = 0;
}

List::~List()
{
    DelAll();
}

int List::GetCount()
{
    return Count;
}

void List::Add(char data)
{
    Element* temp = new Element;
    temp->data = data;
    temp->Next = NULL;
    if (Head != NULL) {
        Tail->Next = temp;
        Tail = temp;
    }
    else {
        Head = Tail = temp;
    }
    Count++;
}

void List::Del()
{
    if (Head != NULL) {
        Element* temp = Head;
        Head = Head->Next;
        delete temp;
        Count--;
    }
}

void List::DelAll()
{
    while (Head != NULL)
        Del();
}

void List::Print()
{
    Element* temp = Head;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->Next;
    }
    cout << "\n\n";
}

void List::AddIndex(char data, int index)
{
    if (index < 1 || index > Count + 1) {
        cout << "Invalid index!" << endl;
        return;
    }

    Element* temp = Head;
    int i = 1;
    while (i < index - 1 && temp != NULL)
    {
        temp = temp->Next;
        i++;
    }

    Element* NewNode = new Element;
    NewNode->data = data;

    if (index == 1) {
        NewNode->Next = Head;
        Head = NewNode;
        if (Count == 0) Tail = NewNode;
    } else {
        NewNode->Next = temp->Next;
        temp->Next = NewNode;
        if (NewNode->Next == NULL) Tail = NewNode;
    }
    Count++;
}

void List::DelAtIndex(int index)
{
    if (index < 1 || index > Count) {
        cout << "Invalid index!" << endl;
        return;
    }

    if (index == 1) {
        Del();
    }
    else {
        Element* temp = Head;
        for (int i = 1; i < index - 1; i++) {
            temp = temp->Next;
        }

        Element* toDelete = temp->Next;
        temp->Next = toDelete->Next;
        if (toDelete == Tail) Tail = temp;
        delete toDelete;
        Count--;
    }
}

void List::DelLast()
{
    DelAtIndex(Count);
}

int List::FindElement(char data)
{
    Element* temp = Head;
    int index = 1;
    while (temp != NULL)
    {
        if (temp->data == data)
            return index;
        temp = temp->Next;
        index++;
    }
    return -1; // Если элемент не найден
}

// Тестовый пример
int main()
{
    List lst;
    lst.Add('A');
    lst.Add('B');
    lst.Add('C');
    lst.Add('D');
    lst.Add('E');
    lst.Add('F');
    lst.Print();

    lst.AddIndex('Z', 2);
    lst.Print();

    lst.DelAtIndex(3);
    lst.Print();

    lst.DelLast();
    lst.Print();

    int pos = lst.FindElement('D');
    if (pos != -1) {
        cout << "'D' found at position: " << pos << endl;
    } else {
        cout << "'D' not found!" << endl;
    }

    return 0;
}

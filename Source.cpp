
#include <iostream>

using namespace std;
class List {
public:
	List();
	~List();
	void push_front(int data);
	void push_back(int data);
	void push_mid(int data,int index);
	int get_index(int index);
	int get_size() { return size; }
	void del_back();
	void del_front();
	void del_mid(int index);
	void replace(int data, int index);
	void clear();
	int check();

private:
	class Node {
	public:
		Node* pNext;
		int data;
		Node(int data, Node* pNext = nullptr) {
			this->data = data;
			this->pNext = pNext;
		}
	};
	int size;
	Node* head;
	Node* current;
};


List::List() {
	size = 0;
	head = nullptr;
}
List::~List() {

}
void List::push_back(int data) {
	if (head == nullptr) {
		head = new Node(data);
	}
	else {
		current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(data);
	}
	size++;
}
void List::push_front(int data) {
	head = new Node(data,head);
	size++;
}
int List::get_index(int index) {
	current = this->head;
	for (int i = 0; i < index; i++) {
		current = current->pNext;
	}
	return current->data;
}
void List::del_front() {
	Node* temp = head;
	head = head->pNext;
	delete temp;
	size--;
}
void List::del_back() {
	current = this->head;
	while (current->pNext != nullptr) {
		current = current->pNext;
	}
	delete current;
	size--;
}
void List::push_mid(int data,int index) {
	current = this->head;
	for (int i = 0; i < index-1; i++) {
		current = current->pNext;
	}
	Node *cur = new Node(data, current->pNext);
	current->pNext = cur;
	size++;
}
void List::del_mid(int index) {
	current = this->head;
	for (int i = 0; i < index - 1; i++) {
		current = current->pNext;
	}
	current->pNext = current->pNext->pNext;
	size--;
}
void List::clear() {
	while (size) {
		del_front();
	}
}
void List::replace(int data,int index) {
	push_mid(data, index);
	del_mid(index + 1);
}
int List::check() {
	if (size == 0) {
		return 0;
	}
	else return 1;
}

int compare(List l1, List l2) {
	int index = 0;
	bool flag = 1;
	while (index != l1.get_size()){
		for (int i = 0; i != l2.get_size();i++) {
			if (l1.get_index(index) == l2.get_index(i)) {
				flag = 0;
			}
		}
		if (flag == 0) {
			break;
		}
		index++;
	}
	return index;
}
void main() {
	setlocale(LC_ALL, "Russian");
	cout << "Лабораторная работа 1" << endl << "Выполнил Герасимов Артемий гр. 1301" << endl;
	List l2;
	List l1;

	cout << "Вставка числа в конец списка" << endl;
	l1.push_back(12);
	for (int i = 0; i < l1.get_size(); i++) {
		cout << l1.get_index(i) << " | ";
	}
	cout << endl;
	cout << "Вставка числа в начало списка" << endl;
	l1.push_front(13);
	for (int i = 0; i < l1.get_size(); i++) {
		cout << l1.get_index(i) << " | ";
	}
	cout << endl;
	cout << "Вставка числа в середину списка (индекс 1)" << endl;
	l1.push_mid(13, 1);
	for (int i = 0; i < l1.get_size(); i++) {
		cout << l1.get_index(i) << " | ";
	}
	cout << endl;
	cout << "Получение числа по индексу 1" << endl;
	cout <<l1.get_index(1) << endl;
	cout << "Размер списка" << endl;
	cout << l1.get_size() << endl;
	cout << "Список дополнен 10 числами" << endl;
	for (int i = 0; i < 10; i++) {
		l1.push_back(i);
	}
	cout << "Удаление числа с индексом 1" << endl;
	l1.del_mid(1);
	for (int i = 0; i < l1.get_size(); i++) {
		cout << l1.get_index(i) << " | ";
	}
	cout << endl;
	cout << "Удаление числа из конца списка" << endl;
	l1.del_back();
	for (int i = 0; i < l1.get_size(); i++) {
		cout << l1.get_index(i) << " | ";
	}
	cout << endl;
	cout << "Удаление числа из начала списка" << endl;
	l1.del_front();
	for (int i = 0; i < l1.get_size(); i++) {
		cout << l1.get_index(i) << " | ";
	}
	cout << endl;
	cout << "Замена числа с индексом 1 на 555" << endl;
	l1.replace(555,1);
	for (int i = 0; i < l1.get_size(); i++) {
		cout << l1.get_index(i) << " | ";
	}
	cout << endl;
	l2.push_back(4);
	l2.push_back(5);
	cout << "Поиск первого вхождения списка l1 c l2 ( 4 | 5 )" << endl;
	cout << compare(l1, l2) << endl;
	l1.clear();
	l2.clear();


}
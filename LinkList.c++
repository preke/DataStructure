# include <iostream>
using namespace std;

typedef struct link {
	int value;
	struct link* next;
}Link;

void insertFromTail(Link* &head, int v){
	if (head == NULL) {
		head = new Link;
		head->value = 0;
		head->next = NULL;
	}
	
	//创建新节点
	Link* temp = new Link;
	temp->value = v;
	temp->next = NULL;
	
	Link* head_temp = head;
	Link* &tail = head_temp;
	
	while (tail) {
		if (tail->next == NULL) {
			break;
		}
		tail = tail->next;
	}

	tail->next = temp;
}

void insertFromHead(Link* &head, int v){
	if (head == NULL) {
		head = new Link;
		head->value = 0;
		head->next = NULL;
	}
	
	//创建新节点
	Link* temp = new Link;
	temp->value = v;
	temp->next = NULL;
	
	Link* next_temp = head->next;
	head->next = temp;
	temp->next = next_temp;
}

void print(Link* head){
	if (head == NULL) {
		cout << "Empty!\n";
		return;
	}

	Link* temp = head;
	while (temp != NULL) {
		cout << temp->value << " - ";
		temp = temp->next;
	}
	cout << endl;
}

void Delete(Link* &head, int v){
	if (head == NULL) {
		cout << "No element to delete.\nThe list is already empty!\n";
		return;
	}	
	
	//头
	if (head->value == v) {
		Link* temp = head->next;
		delete head;
		head = temp;
	}

	//中间
	else {
		Link* head_temp = head;
		Link* &Mid = head_temp;
		while (Mid) {
			if (Mid->next && Mid->next->value == v) {
				Link* mid_temp = Mid->next->next;
				delete Mid->next;
				Mid->next = mid_temp;
			} else {
				Mid = Mid->next;
			}
		}
	}

	cout << "The element you want to delete is not in the list.\n";
}

void reverse(Link* &head){
	if (head == NULL) {
		return;
	}

	Link* temp_head = head->next;
	Link* new_head = NULL;
	
	while (temp_head) {
		insertFromHead(new_head, temp_head->value);
		temp_head = temp_head->next;
	}
	head = new_head;
}

int main(){
	Link* head = NULL;
	int a;
	while (cin >> a && a != -1) {
		insertFromHead(head, a);
	}
	print(head);
	
	reverse(head);
	print(head);


}






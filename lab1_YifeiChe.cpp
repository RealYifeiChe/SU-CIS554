//HW1_Yifei Che
//SUNETID:yche03 SUID:636109055

#include <iostream>
using namespace std;

class node {
public:
	int value;
	node* next;
	node* previous;
	//constructors to initialize object contents

	node(int i) { value = i; next = previous = nullptr; }
	node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	node* head;
	node* tail;
	//constructor
	DoublyLinkedList() { head = tail = nullptr; } //check
	DoublyLinkedList(int n, int m); //check
	void print_f(); //check
	void print_r(); //check
	DoublyLinkedList(const initializer_list<int>& I);
	void reverse(); //check
	void sort();//You are only allowed to change next and previous of nodes, but not value;
	void remove_all(int k);//Remove all nodes with value k .

};

void DoublyLinkedList::remove_all(int k) {//Remove all nodes with value k;
//Your code
	if (!head || !head->next) return; //if linked list is empty or has only one node, return.
	node* p2{head};
	node* p1{p2->previous};
	node* p3{p2->next};

	while (p2) {
		p3 = p2->next;
		p1 = p2->previous;
		if (p2->value == k) {
			if (p1 == nullptr) { //head
				delete p2;
				head = p3;
				head->previous = nullptr;
			}
			else if (p1 != nullptr && p3 !=nullptr) { //middle
				delete p2;
				p1->next = p3;
				p3->previous = p1;
			}
			else if (p3 == nullptr) { // tail
				delete p2;
				p1->next = nullptr;
				tail = p1;
			}
		}
		//jump anyways
		p2 = p3;
	}
}

void DoublyLinkedList::sort() {
//Your code
	if (!head || !head->next) return; //if linked list is empty or has only one node, return.
	node* p2{ head };
	node* p1{ p2->previous };
	node* p3{ p2->next };
	
	while (p2) { //p2->next != nullptr;
		node* p3{p2->next}; //make p3 the pointer to go through later nodes
		node* p1{p2->previous}; //update p1 and p3 every time p2 is updated.
		node* pmin{p2}; //initially set p2 the minimum
		int min{ p2->value }; //initially set the int value same as p2->value
		while (p3){//let p3 go though all the nodes after p2, and set the new pmin if there is a smallest value found, this pmin needs to be further compared with p2
			if (p3->value < min) { 
				min = p3->value;
				pmin = p3;
			}
			p3 = p3->next; //let p3 move to its next
		}
		//the above code applies to both scenarios. (head and non-head)

		//head scenario
		if (p1 == nullptr) {//when p2 is the head
			if (pmin != p2) { //compare pmin with p2, if pmin is smaller, swap them, and connect the list.
				if (pmin->next != nullptr) { //pmin points to middle node
					(pmin->previous)->next = pmin->next;     //let pmin's previous and next connect
					(pmin->next)->previous = pmin->previous; //let pmin's previous and next connect
					pmin->next = p2; //put pmin in the foremost position, p2 natually moves to the second foremost position
					pmin->previous = p2->previous;//place pmin on the ralatively first position; p2->presious is nullptr rn.
					p2->previous = pmin; //1st and 2nd node connect successfully.
					p2 = pmin; //make p2 return to the 1st node.
					head = p2; //head is set perpetually since it contains the smallest value permanently. 
				}
				else if (pmin->next == nullptr) { //pmin points to tail
					(pmin->previous)->next = nullptr;  //make the new tail
					tail = pmin->previous;             //make the new tail
					pmin->next = p2; //put pmin in the foremost position, p2 natually moves to the second foremost position
					pmin->previous = p2->previous; //place pmin on the ralatively first position; p2->presious is nullptr rn.
					p2->previous = pmin;  //1st and 2nd node connect successfully.
					p2 = pmin; //make p2 return to the 1st node.
					head = p2; //head is set perpetually since it contains the smallest value permanently. 
				}
			}
			p2 = p2->next;
		}
		else {//non-head scenario
			if (pmin != p2) { //compare pmin with p2, if pmin is smaller, swap them, and connect the list.
				if (pmin->next != nullptr) { //pmin points to middle node
					(pmin->previous)->next = pmin->next;     //let pmin's previous and next connect
					(pmin->next)->previous = pmin->previous; //let pmin's previous and next connect
					pmin->next = p2; //put pmin in the foremost position, p2 natually moves to the second foremost position
					pmin->previous = p2->previous;//place pmin on the ralatively first position; p2->presious is p1 rn.
					p1->next = pmin; //connect p1 with pmin
					p2->previous = pmin; //1st and 2nd node connect successfully.
					p2 = pmin; //make p2 return to the 1st node.
					//head = p2; //head is set perpetually since it contains the smallest value permanently. 
				}
				else if (pmin->next == nullptr) { //pmin points to tail
					(pmin->previous)->next = nullptr;  //make the new tail
					tail = pmin->previous;             //make the new tail
					pmin->next = p2; //put pmin in the foremost position, p2 natually moves to the second foremost position
					pmin->previous = p2->previous; //place pmin on the ralatively first position; p2->presious is p1 rn.
					p1->next = pmin; //connect p1 with pmin
					p2->previous = pmin;  //1st and 2nd node connect successfully.
					p2 = pmin; //make p2 return to the 1st node.
					//head = p2; //head is set perpetually since it contains the smallest value permanently. 
				}
			}
			p2 = p2->next;

		}
	}
	//make sure head and tail are set to the correct nodes.
	
}

void DoublyLinkedList::reverse() {
//Your code
	if (!head || !head->next) return; //if linked list is empty or has only one node, return.
	node* p1{ head };
	node* temp { nullptr }; 
	node* temp2{ nullptr };

	while (p1) {
		temp = p1->next;
		p1->next = p1->previous;
		p1->previous = temp; //swap next and previous of the current node

		p1 = temp; // move to the next node
	}
	
	
	temp = head;
	head = tail;
	tail = temp; //swap head and tail
	return;
	
}

DoublyLinkedList::DoublyLinkedList(int n, int m) {//construct a linked list of n modes with values in 0..m-1
//Your code
	head = nullptr;
	tail = nullptr;
	for (int i = 0; i < n; ++i) { //the earlier created node is at more rear position
		node* p1 = new node(rand() % m); //create a new node with value within 0 to m-1
		p1->next = head; //make the newly created node the one behind head

		if (p1->next != nullptr) { // if the current p1->next is not pointing to nullpyr (which means p1 doesn't point to the first node)
			(p1->next)->previous = p1; // make the previous node(p1->next)'s previous pointer points to the newly created node (p1)
		}
		else { // if the current p1->next points to nullptr (which means p1 points to the first and only node)
			tail = p1; // make the first and only node the tail
		}

		head = p1; // make head point to the newly created node
	}
}

DoublyLinkedList::DoublyLinkedList(const initializer_list<int>& I) : DoublyLinkedList() {
	//Your code
	auto p1{ I.end() - 1 };//end() returns the address after the last element of I.

	//the first created node should be tail
	node* p3 = new node(*p1); // tail node (p3)
	p3->next = head;
	head = p3;
	tail = p3;
	p1--;

	for (size_t i = 0; i<I.size()-1; ++i) { // loop for the rest of the nodes (except for the first node (tail))
			node* p2 = new node(*p1); // 
			p2->next = head;
			head->previous = p2;
			head = p2;
			p1--;
		}
	head->previous = nullptr; //finish the constructor by setting the head->previous to nullptr
}


void DoublyLinkedList::print_f() {//print forward from head
//Your code
	node* p1 = head; //make p1 points to where head points to.
	while (p1) { //while p1 != nullptr
		cout << p1->value << " ";
		p1 = p1->next; // move to the next node
	}
	cout << endl;
}
void DoublyLinkedList::print_r() {//print backward from tail
	//Your code
	node* p1 = tail; //make p1 points to where tail points to.
	while (p1) { //while p1 != nullptr
		cout << p1->value << " ";
		p1 = p1->previous; // move to the previous node
	}
	cout << endl;
}

int main() {
	DoublyLinkedList L1(20, 10);
	L1.print_f();
	L1.print_r(); //reverse previous result
	L1.reverse();
	L1.print_f(); //similar to the previous result
	L1.print_r(); //reverse previous result
	L1.remove_all(7);
	L1.print_f(); //print list after removing int.
	L1.print_r();
	L1.sort();
	L1.print_f();
	L1.print_r();

	DoublyLinkedList L2{ 4,5,6,7,8 };//Declare and call initializer_list
	L2.print_f();//4 5 6 7 8
	L2.print_r();

	return 0;
}
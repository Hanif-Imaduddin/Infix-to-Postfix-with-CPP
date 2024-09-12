#include <iostream>
#inlcude <string>

using namespace std;

struct Node{
	char data;
	Node *next;
};

class Queue{
	private:
		Node *head;
		Node *tail;
	public:
		int length;
		Queue() : head(nullptr),tail(nullptr),length(0){}
		
		void enqueue(int data){
			Node *temp = new Node();
			temp->data = data;
			if (this->tail == nullptr){
				this->head = this->tail = temp;
			}else{
				this->tail->next = temp;
				this->tail = this->tail->next;
			}
			this->length++;
		}
		
		char dequeue(){
			char data = '';
			if (this->head == nullptr){
				return data;
			}else if (this->head->next == nullptr){
				data = this->head->data;
				delete this->head;
				this->head = nullptr;
				return data;
			}else{
				data = this->head->data;
				Node *temp = this->head->next;
				delete this->head;
				this->head = temp;
				return data;
			}
		}
};	

class Stack{
	private:
		Node *head;
		Node *tail;
	public:
		int length;
		Stack() : tail(nullptr),head(nullptr),length(0) {}
		void push(char data){
			if (this->tail == nullptr){
				this->head = new Node;
				this->head->data = data;
				this->head->next = nullptr;
				
				this->tail = this->head;
			}else{
				Node *temp = new Node;
				temp->data = data;
				temp->next = nullptr;
				
				this->tail->next = temp;
				this->tail = this->tail->next;
			}
			this->length++;
		}
		char pop(){
			if (this->head == nullptr){
				return '';
			}else if (this->head->next == nullptr){
				char data = this->head->data;
				delete this->head;
				this->head = nullptr;
				this->tail = this->head;
				this->length--;
				return data;
			}else{
				char data = this->tail->data;
				Node *temp;
				temp = this->head;
				while (temp->next->next != nullptr){
					temp = temp->next;
				}
				temp->next = nullptr;
				delete this->tail;
				this->tail = temp;
				this->length--;
				return data;
			}
		}
		char getRecent(){
			if (this->tail != nullptr){
				return this->tail->data;
			}else{
				return '';
			}
		}
};

bool isNumber(char c){
	if (c >= '0' && c <= '9'){
		return true;
	}else{
		return false;
	} 
}

bool isValidOperators(char c){
	if (c == '*' || c == '/' || c == '+' || c == '-' ||c == '^'){
		return true;
	}else{
		return false;
	}
}

int getPriority(char c){
	if (c == '(' || c == ')'){
		return 1;
	}else if (c == '^'){
		return 2;
	}else if (c == '*' || c == '/'){
		return 3;
	}else if (c == '+' || c == '-'){
		return 4;
	}else{
		return 999;
	}
}

int ciToi(char ci){
	return int(ci)-'0';
}

Queue infixToPostfix(string infix){
	Stack operators;
	Queue postfix;
	
	for (size_t i = 0;i < infix.size();i++){
		if (isNumber(infix[i])){
			postfix.enqueue(infix);
		}else if (isValidOperators(infix[i])){
			if (getPriority(infix[i]) < getPriority(postfix.getRecent())){
				operators.push(infix[i]);
			}else{
				postfix.enqueue(operators.pop());
				while (getPriority(infix[i]) < getPriority(postfix.getRecent())){
					postfix.enqueue(operators.pop());
				}
				operators.push(infix[i]);
			}
		}else if (infix[i] == '('){
			operators.push(infix[i]);
		}else if (infix[i] == '('){
			while (operators.getRecent() != '('){
				postfix.enqueue(operators.pop());
			}
		}else if (infix[i] == '='){
			break;
		}
	}
	return postfix;
}

void cetakQueue(Queue Q){
	for (int i = 0;i < Q.length;i++){
		cout<<Q.dequeue();
	}
	cout<<endl;
}

int main(){
	string infix;
	Queue postfix;
	getline(cin,infix);
	postfix = infixToPostfix(infix);
	cetakQueue(postfix);
	
	
	return 0;
}
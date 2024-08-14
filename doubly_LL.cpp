#include <iostream>
using namespace std;

class DLL{
    private:
    struct Node{
        int data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;

    public:
    // this is constructor 
    DLL():head(nullptr),tail(nullptr) {}

    // push back
    void push_back(int val){
        Node* newnode= new Node;
        newnode->data=val;
        if(tail==nullptr){
            tail=newnode;
            head=newnode;
            newnode->next=nullptr;
            newnode->prev=nullptr;
        }
        else{
            newnode->next=nullptr;
            newnode->prev=tail;
            tail->next=newnode;
            tail=newnode;
        }
    }

    // pop back
    void pop_back(){
        if(tail==nullptr){
            cout<< "Linked List is Empty" << endl;
        }
        else{
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            } else {
                head = nullptr; 
            }
            delete temp;
        }
    }

    // push front 
    void push_front(int val){
        Node* newnode= new Node;
        newnode->data=val;
        if(head==nullptr){
            head=newnode;
            tail=newnode;
            newnode->next=nullptr;
            newnode->prev=nullptr;
        }
        else{
            newnode->next=head;
            head->prev=newnode;
            head=newnode;
        }
    }    
    // pop front 
    void pop_front(){
        if(head==nullptr){
            cout<< "Linked List is Empty" << endl;
        }
        else{
            Node* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr; 
            }
            delete temp;
        }
    }
    // print
    void print(){ 
        if(head==nullptr || tail== nullptr){
            cout<< "Nothing to print" << endl;
        }
        else{
            Node* temp= head;
            cout<< "The elements are" ;
            while(temp!=nullptr){
               cout << temp->data ;
                temp=temp->next;
            }
        }       
    }

    // find 
    void contains(int val){
        Node* temp= head;
        while(temp!=nullptr){
            if(temp->data==val){
                cout<< " Yes it contains:" << temp->data;
                return;
            }
            else{
                temp=temp->next;
            }
        }
        cout<< " No it doesnt contains:" << temp->data;
    } 
};

int main(){
    DLL d1;
    d1.push_back(1);
    d1.push_back(2);
    //d1.print();
    d1.push_front(11);
    d1.push_front(12);
    d1.print();
    d1.contains(1);

    d1.pop_back();
    d1.print();
    d1.contains(2);
    d1.pop_front();
    d1.print();
    d1.contains(12);
}
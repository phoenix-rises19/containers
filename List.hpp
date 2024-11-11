#include <stddef.h>
#ifndef list.hpp
#define list.hpp



namespace vai{
    
    template<typename T>
    class List{

    public:
        List():
            head(nullptr)
            tail(nullptr)
            size_(0){}
        


        List& operator=(List& other){
            if(this==&other){
                return *this;
        }
        
        bool operator==(const List& other) const{
            if(this->size_!=other.size_){
                return false;
            }
            ListNode* current=this->head;
            ListNode* otherCurrent=other.head;
            while(current and otherCurrent){
                if(current->value!=otherCurrent.value){
                    return false;
                }
                current=current->next;
                otherCurrent=otherCurrent->next;
            }
            return true;
        }

            clear();

            size_=other.size_;
            if(other.head){
                head= new ListNode(other.head->value);
                ListNode* current= head;
                ListNode* nextCurrent= other.head->next;

                while(nextCurrent){
                    current->next=new ListNode(nextCurrent->value);
                    current->next->previous= current;
                    current=current->next;
                    nextCurrent=nextCurrent->next;
                }
                tail=current;
            }
            else{
                head=tail=nullptr;
            }
            return *this;
        }

        List& operator=(List&& other){
            if(this==&other){
                return *this;
            }
            clear();
            size_=other.size_;
            head=other.head;
            tail=other.tail;
            other.size=0;
            other.head=nullptr;
            other.tail=nullptr;
            return *this;
        }
        
        class Iterator{
            public:
                Iterator(ListNode* node)
                    current(node){}

                T& operator*(){
                    return current->value;
                }

                Iterator& operator ++(){
                    if(current->next==nullptr){
                       std::cout<<"This is the last element";
                        return *this;
                    }
                        this->current=this->current->next;
                        return *this;
                }

                Iterator& operator --(){
                    if(current->previous==nullptr){
                        std::cout<<"This is the first element";
                        return *this;
                    }
                       current = current->previous;
                       return *this;
                }

                ListNode* getNode(){
                    return current;
                }


            private:
                ListNode* current;
            
        };
        
        void push_back(T& value){
            ListNode* node= new ListNode(value);
            if(head==nullptr){
                head=node;
                tail=node;
            }
            else{
                tail->next=node;
                node->previous=tail;
                tail=node;
            }
            ++size_;
        }

        

        ListNode* front(){
            if(head==nullptr){
                std::cout<<"List is empty\n";
                return nullptr;
            }
            return head;
        }
        ListNode* back(){
            if(head==nullptr){
                std::cout<<"List is empty\n";
                return nullptr;
            }
            return tail;
        }

        bool empty(){
            return head==nullptr;
        }

        size_t size(){
            return size_;
        }

        void clear(){
           ListNode* current=head;
           while(current){
            ListNode* delete_this=current;
            current=current->next;
            delete delete_this;
           }
           head=nullptr;
           tail=nullptr;
           size_=0;
        }

        

        Iterator insert(Iterator pos, T& data){
            ListNode* node= pos.getNode();
            ListNode* new_node= new ListNode(data);
            ++size_;
            if(node==tail){ 
                new_node->previous=tail;
                new_node->next=nullptr;
                tail->next=new_node;
                tail=new_node;
                return Iterator(tail);
            }
            if(node==head){
                new_node->previous=nullptr;
                new_node->next=head;
                head->previous=new_node;
                head=new_node;
                return Iterator(head);
            }
            ListNode* temp=node->next;
            new_node->next=temp;
            new_node->previous=node;
            node->next=new_node;
            temp->previous=new_node;
            return Iterator(new_node);
        }

        Iterator& begin(){
            return Iterator(head);
        }
        Iterator& end(){
            return Iterator(nullptr);
        }

        Iterator rbegin(){
            return Iterator(tail);
        }

        Iterator rend(){
            return Iterator(head);
        }

    private:

        struct ListNode{
            T value;
            ListNode* next;
            ListNode* previous;

            ListNode(T& val):
                value(val),
                next(nullptr),
                previous(nullptr){}
            
            ListNode():
                value(0),
                next(nullptr),
                previous(nullptr){}

            ListNode(ListNode* oth):
                value(oth ? oth->value : 0),            
                next(oth ? oth->next : nullptr),        
                previous(oth ? oth->previous : nullptr){}

            ~ListNode(){}
        }
        ListNode<T>* head;
        ListNode<T>* tail;
        size_t size_;


};

 






}
#endif

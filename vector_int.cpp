#include<iostream>
#include<vector>
using namespace std;

int main(){
std::vector<int> v1;
v1.push_back(10);
v1.push_back(12);
v1.push_back(14);

std::cout<< "Printing elements" ;

for(int i=0; i<v1.size(); i++){
    cout<< v1[i] << endl;
}

cout<< v1.size() << endl;
cout<< v1.capacity() <<endl;

v1.pop_back();

cout<< "Printing after pop back" << endl; 

for(int i=0; i<v1.size(); i++){
    cout<< v1[i]<< endl;
}

cout<< "Printing sizes after pop back" << endl;

cout<< v1.size()<< endl;
cout<< v1.capacity()<< endl;

}

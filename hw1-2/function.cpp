#include "function.h"
#include <iostream>
#include <string>
using namespace std;

BaseQueue<char> board[30];
BaseStack<string> MStack;

template<class T>
BaseStack<T>::BaseStack(){
    capacity=100;
    _stack = new T[capacity];
    _top=-1;
    for(int i = 0; i < capacity; i++ )
        _stack[i] = '€0';
}

template<class T>
BaseStack<T>::~BaseStack(){
    delete [] _stack;
}

template<class T>
bool BaseStack<T>::empty(){
    if(_top==-1)
        return true;
    return false;
}

template<class T>
int BaseStack<T>:: size(){
    return _top+1;
}

template<class T>
T& BaseStack<T>::top(){
    return _stack[_top];
}

template<class T>
void BaseStack<T>::push(const T& item){
    T* new_stack;
    int newCapacity;
    if(_top+1==capacity){
        newCapacity=2*capacity;
        new_stack=new T[newCapacity];

        for(int i=0;i<capacity;i++){
            new_stack[i] = _stack[i];
        }
        delete[] _stack;

        _stack=new_stack;
    }
    _stack[++_top]=item;
}

template<class T>
void BaseStack<T>::pop(){
    if(!empty())
        _top--;
}

//Queue

template < class T >
BaseQueue<T>::BaseQueue(){
    int capacity = 100;
    _queue = new T[capacity];
    int _front = -1;
    int _rear = -1;
    for(int i = 0; i < capacity; i++ )
        _queue[i] = '€0';
}

template < class T >
BaseQueue<T>::~BaseQueue(){
    delete[] _queue;
}

template < class T >
bool BaseQueue<T>::empty(){
    if(_front==_rear)
        return true;
    return false;
}
template < class T >

int BaseQueue<T>::size(){
    return _rear-_front;
}

template < class T >
T& BaseQueue<T>::front(){
    return _queue[_front+1];
}

template < class T >
void BaseQueue<T>::push(const T& item){
    T* new_queue;
    int new_queue_Capacity;
    if(_rear+1==capacity){
        new_queue_Capacity=2*capacity;
        new_queue=new T[new_queue_Capacity];

        for(int i=0;i<capacity;i++){
            new_queue[i] = _queue[i];
        }
        delete[] _queue;
        _queue=new_queue;
    }
    _queue[++_rear] = item;
}

template<class T>
void BaseQueue<T>::pop(){
    if(!empty())
        _front++;
}


void insert(int L){
    int i,j=0, start_from;
    string name;
    cin >> start_from;
    cin >> name;
    for (i = start_from ; i < start_from + name.length(); i++){
        if (board[i-1].size() > board[i].size()+1 && i>0) {
            int temp = board[i - 1].size()-1;
            while (temp) {
                board[i].push('@');
                temp--;
            }
            //cout << 1;
        }
        else {
            //cout << 2;
            board[i].push(name[j++]);
        }
    }
}
/*
 string first_row(int L, bool print) {
 cout << "BOTTOM_ROW" << endl;
 string a = "returnvalue";
 for (int i = 0; i < L; i++) {
 if (board[i].front() == ' ' || board[i].front() == '€0'  )
 cout << '~';
 else cout << board[i].front();
 }
 cout << endl;
 return a;
 }
 */
string first_row(int L, bool print) {
    // TODO
    cout << "BOTTOM_ROW"<< endl;
    string endchar="€0";
    //char wave='~';
    for( int i = 0 ; i < L ; i++){
        if( board[i].front() != '€0')
            endchar = endchar.append( 1, board[i].front() );
        else
            endchar = endchar.append( 1, '~');
    }
    if(print)
        cout << endchar << endl;

    return endchar;
}

void query(int L){
    int flag=0, count=0, j=0, tempi;
    string qu;
    cin >> qu;
    // substring compare
    for(int i = 0; i < L ; i++){
        for (int j = 0; j < qu.length();j++){
            if (board[i+j].front() == qu[j])
                count++;
            else {
                count = 0;
                break;
            }
        }
        if (count == qu.length()) {
            tempi = i;
            flag = 1;
            break;
        }
    }
    //cout << flag;
    // push to stack and pop from queue
    if (flag) {
        //for (int i = qu.length(); i > 0 ;i--){
        MStack.push(qu);
        //}
        for (int i = tempi; i<tempi+qu.length() ;i++)
            board[i].pop();
    }
    //cout <<    MStack.size();
}

void flush(void){
    cout << "FLUSH" << endl;
    while(!MStack.empty()){
        cout << MStack.top() <<endl;
        MStack.pop();
    }
}

void reset(int L){
    //stack reset
    while(!MStack.empty()){
        MStack.pop();
    }
    //queue reset
    for (int i = 0; i<L ; i++){
        while(!board[i].empty()){
            board[i].pop();
        }
    }

}

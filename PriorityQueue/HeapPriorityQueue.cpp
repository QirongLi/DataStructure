// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "HeapPriorityQueue.h"
#include "math.h"

HeapPriorityQueue::HeapPriorityQueue() {
    // TODO: implement
    elements = new PQEntry[10]();
    capacity = 10;
    mysize = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    // TODO: implement
    delete[] elements;
}

void HeapPriorityQueue::changePriority(string value, int newPriority) {
    // TODO: implement
    int index = 0;
    for(int i=1; i<mysize+1; i++){
        if(elements[i].value == value){
            if (elements[i].priority<newPriority) {
                cout << "Error: new priority cannot be greater than old priority" << endl;
                return;
            }
            elements[i].priority = newPriority;
            index=i;
            break;
        }
    }

    while(index/2>0&&elements[index/2]>elements[index]){
        PQEntry entry = elements[index/2];
        elements[index/2] = elements[index];
        elements[index] = entry;
        index /= 2;
    }
}

void HeapPriorityQueue::clear() {
    // TODO: implement
    elements = new PQEntry[10]();
    mysize = 0;
    capacity = 10;
}

string HeapPriorityQueue::dequeue() {
    // TODO: implement
    if(mysize==0) return "";   // remove this

    string str = elements[1].value;
    int index = 1;
    while(index*2 <= mysize){
        if(index*2+1 <= mysize){
            if(elements[index*2]>elements[index*2+1]){
                elements[index] = elements[index*2+1];
                index = index*2+1;
            }else{
                elements[index] = elements[index*2];
                index = index*2;
            }
        }else{
            elements[index] = elements[index*2];
            index = index*2;
        }
    }
    elements[index] = elements[mysize];
    mysize--;
    return str;
}

void HeapPriorityQueue::enqueue(string value, int priority) {
    // TODO: implement
    PQEntry entry(value, priority);
    if (mysize==0) {
        elements[1] = entry;
        mysize++;
        return;
    }

    checkCapacity();
    int index = mysize+1;
    elements[index] = entry;
    while(index/2>0&&elements[index/2]>elements[index]){
        PQEntry temp = elements[index/2];
        elements[index/2] = entry;
        elements[index] = temp;
        index /= 2;
    }
    mysize++;
}

bool HeapPriorityQueue::isEmpty() const {
    // TODO: implement
    return mysize==0;   // remove this
}

string HeapPriorityQueue::peek() const {
    // TODO: implement
    if(mysize==0) return "";   // remove this
    return elements[1].value;
}

int HeapPriorityQueue::peekPriority() const {
    // TODO: implement
    if(mysize==0) return 0;   // remove this
    return elements[1].priority;
}

int HeapPriorityQueue::size() const {
    // TODO: implement
    return mysize;   // remove this
}

void HeapPriorityQueue::checkCapacity(){
    if(mysize+1==capacity){
        PQEntry* biggun = new PQEntry[capacity*2]();
        for(int i = 1; i < mysize+1; i++){
            biggun[i] = elements[i];
        }
        delete[] elements;
        elements = biggun;
        capacity *= 2;
    }
}

ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {
    // TODO: implement
    out << "{";
    if (!queue.isEmpty()) {
        out << queue.elements[1];
        for(int i = 2; i < queue.mysize+1; i++){
            out << ", " << queue.elements[i];
        }
    }
    out << "}";
    return out;
}

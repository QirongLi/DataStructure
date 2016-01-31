// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {
    // TODO: implement
    front = NULL;
}

LinkedPriorityQueue::~LinkedPriorityQueue() {
    // TODO: implement

}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    // TODO: implement
    ListNode *current = front;
    while(current != NULL){
        if (current->value==value) {
            if(current->priority < newPriority){
                cout << "Error: new priority cannot be greater than old priority" << endl;
                return;
            }
            current->priority = newPriority;
            return;
        }
        current = current->next;
    }
    cout << "No value match." << endl;

}

void LinkedPriorityQueue::clear() {
    // TODO: implement
    front = NULL;
}

string LinkedPriorityQueue::dequeue() {
    // TODO: implement
    if (front == NULL) return "";
    ListNode *current = front;
    front = front->next;
    return current->value;   // remove this
}

void LinkedPriorityQueue::enqueue(string value, int priority) {
    // TODO: implement
    if (front==NULL) {
        front = new ListNode(value, priority, NULL);
        return;
    }

    ListNode *previous = NULL;
    ListNode *current = front;

    while(current != NULL){
        if(current->priority >= priority){
            current = new ListNode(value, priority, current);

            if(previous==NULL){
                front = current;
                return;
            }
            previous->next = current;
            previous = NULL;
            return;
        }else{
            previous = current;
            current = current->next;
        }
    }
    previous->next = new ListNode(value, priority, NULL);
    previous = NULL;
}

bool LinkedPriorityQueue::isEmpty() const {
    // TODO: implement
    return front==NULL;   // remove this
}

string LinkedPriorityQueue::peek() const {
    // TODO: implement
    if (front==NULL) return "";
    return front->value;   // remove this
}

int LinkedPriorityQueue::peekPriority() const {
    // TODO: implement
    if (front==NULL) return 0;
    return front->priority;   // remove this
}

int LinkedPriorityQueue::size() const {
    // TODO: implement
    if (front==NULL) return 0;
    ListNode *current = front;
    int size=0;
    while(current!=NULL){
        size++;
        current = current->next;
    }
    return size;   // remove this
}

ostream& operator<<(ostream& out, const LinkedPriorityQueue& queue) {
    // TODO: implement

    out << "{";
    if(!queue.isEmpty()){
        ListNode *current = queue.front;
        out << current->value << ":" << current->priority;
        current = current->next;
        while(current != NULL){
            out << ", " << current->value << ":" << current->priority;
            current = current->next;
        }
    }

    out << "}";
    return out;
}

// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "VectorPriorityQueue.h"

VectorPriorityQueue::VectorPriorityQueue() {
    // TODO: implement

}

VectorPriorityQueue::~VectorPriorityQueue() {
    // TODO: implement
}

void VectorPriorityQueue::changePriority(string value, int newPriority) {
    // TODO: implement
    if (elements.isEmpty()) return;

    PQEntry *entry;
    for(int i=0; i<elements.size();i++){
         entry = &(elements[i]);
         if(equalsIgnoreCase(entry->value,value)){
             if (entry->priority < newPriority) {
                 cout << "Error: new priority cannot be greater than old priority" << endl;
                 entry = NULL;
                 return;
             }
             entry->priority = newPriority;
             entry = NULL;
             return;
        }
    }
    cout << "Cannot find the value" << endl;
}

void VectorPriorityQueue::clear() {
    // TODO: implement
    elements = Vector<PQEntry>(0);
}

string VectorPriorityQueue::dequeue() {
    // TODO: implement
    if(elements.size()==0) return "";

    int min = elements.get(0).priority;
    string value = elements.get(0).value;
    int index = 0;
    for (int i = 0; i < elements.size(); i++) {
        if(elements.get(i).priority < min){
            min = elements.get(i).priority;
            value = elements.get(i).value;
            index = i;
        }
    }

    for(int j = index; j < elements.size()-1; j++){
        elements.set(j, elements.get(j+1));
    }
    elements.remove(elements.size()-1);
    return value;   // remove this
}

void VectorPriorityQueue::enqueue(string value, int priority) {
    // TODO: implement
    PQEntry entry(value, priority);
    elements.add(entry);
}

bool VectorPriorityQueue::isEmpty() const {
    // TODO: implement
    return elements.size()==0;   // remove this
}

string VectorPriorityQueue::peek() const {
    // TODO: implement
    if(elements.size()==0) return "";

    int min = elements.get(0).priority;
    string value = elements.get(0).value;
    for (int i = 0; i < elements.size(); i++) {
        if(elements.get(i).priority < min){
            min = elements.get(i).priority;
            value = elements.get(i).value;
        }
    }
    return value;
}

int VectorPriorityQueue::peekPriority() const {
    // TODO: implement
    if(elements.size()==0) return 0;

    int min = elements.get(0).priority;
    for (int i = 0; i < elements.size(); i++) {
        if(elements.get(i).priority < min){
            min = elements.get(i).priority;
        }
    }
    return min;
}

int VectorPriorityQueue::size() const {
    // TODO: implement
    return elements.size();   // remove this
}

ostream& operator<<(ostream& out, const VectorPriorityQueue& queue) {
    // TODO: implement
    out << "{";
    if (!queue.isEmpty()) {
        out << queue.elements.get(0);
        for (int i = 1; i < queue.elements.size(); i++) {
            out << ", " << queue.elements.get(i);
        }
    }
    out << "}";
    return out;
}

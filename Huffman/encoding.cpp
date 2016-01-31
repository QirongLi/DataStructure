// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "pqueue.h"
#include "foreach.h"
#include "HuffmanNode.h"
#include "filelib.h"

// TODO: include any other headers you need
void buildEncodingMapHelper(HuffmanNode* node, string path, Map<int, string>& encodingMap);
void generateTable(ibitstream& input, Map<int, int>& freqTable);

Map<int, int> buildFrequencyTable(istream& input) {
    // init variables
    Map<int, int> freqTable;
    bool endOfFile = false;
    int currCharacter;

    // count character frequencies
    while (!endOfFile) {
        currCharacter = input.get();
        if (currCharacter == -1) { // end of file
            endOfFile = true;
            freqTable.put(PSEUDO_EOF, 1);
        } else { // otherwise, valid character
            freqTable[currCharacter]++;
        }
    }

    return freqTable;
}

HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    // TODO: implement this function
    PriorityQueue<HuffmanNode *> pqueue;
    HuffmanNode *node;
    foreach (int key in freqTable) {
        int count = freqTable.get(key);
        node = new HuffmanNode(key, count, NULL, NULL);
        pqueue.enqueue(node, count);
    }

    HuffmanNode *node1;
    HuffmanNode *node2;
    HuffmanNode *temp;
    while(pqueue.size()>1){
        node1 = pqueue.dequeue();
        node2 = pqueue.dequeue();

        temp = new HuffmanNode(NOT_A_CHAR, node1->count+node2->count, node1, node2);
        pqueue.enqueue(temp, temp->count);
    }

    return pqueue.peek();   // this is just a placeholder so it will compile
}

void buildEncodingMapHelper(HuffmanNode* node, string path, Map<int, string>& encodingMap){
    if(node->zero==NULL&&node->one==NULL){
        encodingMap.put(node->character, path);
        return;
    }

    if (node->zero != NULL) {
        buildEncodingMapHelper(node->zero, path+"0", encodingMap);
    }

    if (node->one != NULL) {
        buildEncodingMapHelper(node->one, path+"1", encodingMap);
    }
}

Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    Map<int, string> encodingMap;   // this is just a placeholder so it will compile
    HuffmanNode* curr = encodingTree;
    string s;
    buildEncodingMapHelper(curr, s, encodingMap);
    return encodingMap;             // this is just a placeholder so it will compile
}


void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    // TODO: implement this function
    //if (input.size()==0) return;

    rewindStream(input);
    bool isEnd = true;
    int c = input.get();
    while(isEnd){      
        string s;
        if(c==-1){
            s = encodingMap.get(PSEUDO_EOF);
            isEnd = false;
        }else{
            s = encodingMap.get(c);
        }
        for(int i=0; i<s.length(); i++){
            if(s[i]=='0') output.writeBit(0);
            else if(s[i]=='1') output.writeBit(1);
        }
        c= input.get();
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
    if (input.size()==0) return;

    HuffmanNode* curr = encodingTree;
    int i = input.readBit();
    while(i != -1){
        if(curr->isLeaf()){
            if(curr->character==PSEUDO_EOF) break;
            output.put(curr->character);
            curr=encodingTree;
        }

        if(i==0){
            curr = curr->zero;
        }
        if(i==1){
            curr = curr->one;
        }

        i = input.readBit();
    }
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
    //if (input.size()==0) return;

    Map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* node =  buildEncodingTree(freqTable);
    Map<int, string> encodingMap =  buildEncodingMap(node);
    output << freqTable;
    encodeData(input, encodingMap, output);
    freeTree(node);
}

void generateTable(ibitstream& input, Map<int, int>& freqTable){
    int bit = input.get();
    string key;
    string val;
    string s = "";
    while (bit != '}'){
        if(bit=='{'){

        }else if(bit == ':'){
            key = s;
            s = "";
        }else if(bit == ','){
            val = s;
            key = trim(key);
            val = trim(val);
            freqTable.put(stringToInteger(key), stringToInteger(val));
            s = "";
        }else{
            s += bit;
        }
        bit = input.get();
    }
    freqTable.put(PSEUDO_EOF, 1);
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
    if (input.size()==0) return;
    Map<int, int> freqTable;
    generateTable(input, freqTable);
    HuffmanNode* node =  buildEncodingTree(freqTable);
    decodeData(input, node, output);
    freeTree(node);
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
    if(node==NULL) return;
    if(node->isLeaf()){
        delete node;
        return;
    }
    freeTree(node->one);
    freeTree(node->zero);
    delete node;
}

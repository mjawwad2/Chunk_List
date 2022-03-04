//
// Your code here
//

#include "ChunkList.h"

template<class T>
ChunkList<T>::ChunkList(){          //construction setting everything to 0 and null
    head = nullptr;
    tail = nullptr;
    iterNode = nullptr;
    arrPos=0;
    listLen=0;
    numChunks=0;
}
template<class T>
ChunkList<T>::ChunkList(T arr[], int arrLen) {
    if (arrLen < 0){
        throw InvalidArrayLength();
    }
    head = nullptr;
    tail = nullptr;
    iterNode = nullptr;
    arrPos=0;
    listLen=0;
    numChunks=0;

    for (arrPos=0; arrPos < arrLen; arrPos++){       //constructor builds the chunklist using append
        Append(arr[arrPos]);
    }
    ResetIterator();
}
// Deconstructor
template<class T>
ChunkList<T>::~ChunkList() {            //destructor destroys the chunklist before closing the program
    while (head != nullptr){
        Node* temp = head->next;
        delete head;
        head = temp;
    }
}

// Add/remove elements
template<class T>
void ChunkList<T>:: Append(T value) {           //appending alements passed from user
    Node *curr = tail;
    if (head == nullptr) {                      //if the list is empty start by adding first node and first element in the list
        Node *newNode = new Node();
        newNode->next = nullptr;
        newNode->len = 0;
        newNode->values[newNode->len] = value;
        newNode->len++;
        head = newNode;
        tail = newNode;
        listLen++;                              //increase the list length
        numChunks++;                               // increase the number of chunks when a new node is made
    } else {
        if (head != nullptr && tail->len == ARRAY_SIZE) {   //if the current node array is full make
            Node *newNode = new Node();                     //a new node and value to that first element of that node
            newNode->next = nullptr;
            newNode->len = 0;
            newNode->values[newNode->len] = value;
            newNode->len++;
            tail->next = newNode;
            tail = newNode;
            listLen++;
            numChunks++;
        }else{                                              //else if the current node array is not full
            curr->values[curr->len] = value;                // add the element to the next position available in array
            curr->len++;
            listLen++;
        }
    }
}

template<class T>
void ChunkList<T>:: Remove(T value) {               // removing passed value by user- first instance only
    if (listLen <= 0) {
        IsEmpty();
    } else {
        Node *prev = head;                      // to keep track of previous node- would help deleting in middle
        Node *curr = head;
        while (curr != nullptr) {               //iterate through the list until the value is found
            int i = 0;
            while (i < curr->len) {             //iterate through the node array length until the value is found
                if (curr->values[i] == value) {     //if the value is found go into if statement
                    if (i <= ARRAY_SIZE && i > 1) {     //if it is 2nd element or higher in the current node list
                        for (i; i < curr->len; i++) { //the element will be replaced by next one in the array and
                            curr->values[i] = curr->values[i + 1];  //rest of the array moves up
                        }                                           //listlength and curr node length decreased by 1
                        listLen--;
                        curr->len--;
                        return;                                 //return;
                    }else if (i == 0){//if only 1 in array. so node will be deleted
                        if (curr->next == nullptr && curr == head){//if first node and rest of list empty
                            delete curr;
                        }else if(curr->next != nullptr && curr == head) {//if first node and rest of list isn't empty
                            Node *del = curr;
                            head = curr->next;
                            delete del;
                        }else if (curr->next != nullptr && curr != head) {//if node is somewhere in middle
                            Node *del = curr;
                            curr = curr->next;
                            prev->next = curr;
                            del->next = nullptr;
                            delete del;
                        } else if (curr->next == nullptr && curr != head) {//if node is last in list
                            //delete curr;
                            prev->next = nullptr;
                            tail = prev;
                        }
                        return;
                    }
                    listLen--;             //decrease the length of chunks after deleting node and decrease list length
                    numChunks--;
                }
                i++;                        //iterate through node
            }
            prev = curr;
            curr = curr->next;          //iterating through nodes
        }
        return;
    }
}

//ChunkList<T>::~ChunkList()
// Stuff to find out about the ChunkList
template<class T>
int ChunkList<T>:: GetLength(){             //return the length od the list
    return listLen;
}
template<class T>
double ChunkList<T>:: LoadFactor() {        //return the used spaces divided by available spaces
    if (listLen <= 0) {
        IsEmpty();
    } else {
        return static_cast<float>(listLen) / static_cast<float>(ARRAY_SIZE * numChunks);
    }
}

template<class T>
bool ChunkList<T>:: Contains(T value) {     // looks for element passed by use to see if it is in list
    if (listLen==0){                    //if list is empty throw error
        IsEmpty();
    }else {
        Node *temp = head;                  //start at head(first node)
        while (temp != nullptr) {               //iterate through the list
            int i = 0;
            while (i < temp->len) {             //iterate through through the node length
                for (i=i; i < temp->len; i++) {
                    if (temp->values[i] == value) {         //when the value iss found return it
                        return true;
                    }
                }
            }
            temp = temp->next;
        }
        return false;
    }
}

// Accessing elements
template<class T>
T ChunkList<T>::  GetIndex(int i) {     //get the value at specific index
    int l = GetLength();

    if(head==nullptr){          //if the index is bad throw an error
        IsEmpty();
    }else if(i<0 || i>l){
        throw IndexOutOfBounds();
    }
    Node *curr = head;          //start at head
    int count=0;                    //keeping tack of total number of index even when its next node.
    // this value wont reset for finding an index in the next nodes
    while(curr != nullptr){         //while its the last node keep iterating in list
        int p = 0;                     // keeping tack of array eleemnt count
        while(p<curr->len){         //if its not the end of node array keep pregressing
            if(count==i){
                return curr->values[p];
            }
            count++;        //iterate the array element
            p++;
        }
        curr = curr->next;          //iterate the nodes
    }
    return 0;
}

template<class T>
void ChunkList<T>::ResetIterator() {        //reset the nodes to beginning
    iterNode = head;
    arrPos = 0;
}

template<class T>
T ChunkList<T>::  GetNextItem() {                       //return the next item
    if(iterNode==nullptr){                      //return the next item
        throw IteratorOutOfBounds();            //if the list s empty throw an error
    }else{
        if( arrPos == iterNode->len -1){        //if curr node length is reached increment it
            T temp = iterNode->values[arrPos];
            iterNode = iterNode->next;          //incrementing the node
            arrPos = 0;                         //resetting array position to beginning
            return temp;
        }else{
            int a = arrPos++;
            return iterNode->values[a];      //send the next one in array if not max length of node
        }
    }
}
template<class T>
bool ChunkList<T>::  IsEmpty() {        //just checking if the list is empty
    if (head == nullptr){               //if there is no nodes in the chunklist. that means nothing's been added yet
        throw EmptyList();
    } else {
        return false;
    }
}
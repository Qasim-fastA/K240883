#include<iostream>
using namespace std ;

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        height = 1; 
        left = right = NULL;
    }
};

int getHeight(Node* n){
    if(n==NULL){
        return  0 ;
    }
    return n->height ;
}

int getBalance(Node* n){
    if(n==NULL){
        return  0 ;
    }
    return getHeight(n->left) - getHeight(n->right) ;
}

int updateHeight(Node* n){
     if(n!=NULL){
       int rh= getHeight(n->right);
       int lh = getHeight(n->left) ;
       n->height = (lh>rh?lh:rh)+1;
     }
}


Node* rightRotate(Node*y){
      Node* x = y->left ;
      Node* t2 = x-> right ;

      x->right = y ;
      y->left = t2 ;

      updateHeight(y);
      updateHeight(x);

      return x ;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    updateHeight(x);
    updateHeight(y);

    return y; 
}


Node* rebalance(Node* n) {
    if (n == NULL) return n;

    // Step 1: update height of this node
    updateHeight(n);

    // Step 2: get balance factor
    int balance = getBalance(n);

    // CASE 1: Left Left
    if (balance > 1 && getBalance(n->left) >= 0) {
        return rightRotate(n);
    }

    // CASE 2: Left Right
    if (balance > 1 && getBalance(n->left) < 0) {
        n->left = leftRotate(n->left); 
        return rightRotate(n);
    }

    // CASE 3: Right Right
    if (balance < -1 && getBalance(n->right) <= 0) {
        return leftRotate(n);
    }

    // CASE 4: Right Left
    if (balance < -1 && getBalance(n->right) > 0) {
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }

    // already balanced
    return n;
}

Node* insertNode(Node* root, int key) {
    if (root == NULL)
        return new Node(key);

    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    else
        return root;

    return rebalance(root);
}

Node* minValueNode(Node* n) {
    while (n->left != NULL)
        n = n->left;
    return n;
}

 Node* remove(Node* root, int key) {

    if(root == NULL) 
        return NULL;

    if(key < root->key) {
        root->left = remove(root->left, key);
    }
    else if(key > root->key) {
        root->right = remove(root->right, key);
    }
    else {
        if(root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        else if(root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
    }
    
     
    if(root == NULL)return root;
    
    return rebalance(root);
}

bool searchNode(Node* root, int key) {
    if (root == NULL)
        return false;
    if (root->key == key)
        return true;
    if (key < root->key)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}



//heap
#include<iostream>
using namespace std ;

class heap{
    public:
    int arr[100];
    int size ;

    heap(){
        size = 0;
    }

    int getParent(int i){
        return (i-1) /2 ;
    }

    int getLeft(int i ){
        return 2* i+1 ;
    }

    int getRight(int i){
        return 2*i+2 ;
    }

    void swap(int &a, int &b) {
        int t = a;
        a = b;
        b = t;
    }

    void HeapifyUp(int i){
         while(i!=0 && arr[getParent(i)]>arr[i]){
             swap(arr[i],arr[getParent(i)]);
             i = getParent(i) ;
         }
        }
    
    void HeapifyDown(int i){
        
        while(true){
            int right = getRight(i);
            int left = getLeft(i);
            int smallest = i;
            
            if(left<size && arr[left]<arr[smallest]){
              smallest = left ;
            } 
            
            if(right<size && arr[right]<arr[smallest]){
              smallest = right;
            } 

            if(smallest!=i){
                swap(arr[i],arr[smallest]);
                i = smallest ;
            }else{
                break;
            }
        }
}    
            void insert(int val){
                 arr[size] = val ;
                 size++;
                 HeapifyUp(size-1);
            }

            int deletemin(){
                if(size==0){return -1;}

                int root = arr[0];
                arr[0] = arr[size-1];
                size--;
                HeapifyDown(0);

                return root ;
            }
            
    void printHeap() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void heapSort(int arr[], int n) {
    buildMaxHeap(arr, n);

    for(int i = n - 1; i > 0; i--) {
        swapValues(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

};


int main(){
    heap h ;
    h.insert(8);
    h.insert(7);
    h.insert(6);
    h.insert(5);
    h.insert(4);
    
    h.printHeap();

    h.deletemin();

    h.printHeap();


    
    return 0 ;
}  

//rabin karp
#include<iostream>
using namespace std ;

void rabinKarp(string text , string pattern){
     int n = text.length() ;
     int m = pattern.length();
     
     int prime = 101;
     int base = 256 ;

     int phash = 0;
     int thash = 0; 
     int  h = 0 ;
 
     for(int i = 0 ;i<m-1 ;i++){
       h = (h*base)%prime ; 
     }

     for(int i = 0;i<m ;i++){
        phash = (base*phash+pattern[i])%prime ; 
        thash = (base*thash+text[i])%prime ;

     }

     for(int i=0 ; i<=n-m ;i++){
        if(phash == thash){
            bool match = true ;
            for(int j = 0 ; j<m ;j++){
               if(text[i+j]!= pattern[i]){
                  match = false;
                  break ;
               }
            }
            if(match){
                cout<<"match at index"<<i;
            }
     }
    if (i < n - m) {
            thash = (base * (thash - text[i] * h) + text[i + 1 + m - 1]) % prime;
            if (thash < 0)
                thash += prime; 
    }
}
}

//boyer mooe

#include<iostream>
using namespace std ;

void BuildBadChar(string pattern , int badchar[]){
    for(int i = 0 ; i<256 ;i++){
        badchar[i] = -1 ;
    }

    for(int i = 0 ; i<pattern.length() ;i++){
        badchar[(unsigned char)pattern[i]] = i;
    }
}


void BoyerMoores(string text , string pattern){
     int n = text.length();
     int m = pattern.length();
     
     int badChar[256];
     BuildBadChar(pattern , badChar);

     int s = 0;
     while(s<=n-m){
          int j = m-1 ;
          
          while(j>=0 && pattern[j]==text[s+j]){
              j--;
          }

          if(j==0){
            cout<<"foundat index "<<s ;
            s+= (s+m<n)? m - badChar[(unsigned char)text[s+m]] : 1;
          }else{
            s += max(1, j - badChar[(unsigned char)text[s + j]]);
          }
     }
}


//kmp

#include<iostream>
using namespace std ;

void BuildLps(string pattern ,int lps[]){
       int m = pattern.length();
       int len = 0 ;
       lps[0]=0;

       int i = 1;
       while(i<m){
          if(pattern[i]==pattern[len]){
            len++;
            lps[i] = len ;
            i++;
          }else{
            if(len!=0){
                 len = lps[len-1] ;
            }else{
               lps[i] = 0 ;
               i++;
            }
          }
       }
}


void KMP(string text , string pattern ){
      int n = text.length();
      int m = pattern.length();

      int* lps = new int[m];

      BuildLps(pattern , lps);

      int i , j = 0 ;

      while(i<n){
         if(text[i]==pattern[j]){
            i++;
            j++;
         }
         if(j==m){
            cout<<"found at index "<<i-j <<endl ;
            j = lps[j-1] ;
          }else if(i<n && text[i]!= pattern[j]){
                 if(j!=0){
                    j = lps[j-1] ;
                 }else{
                    i++;
                 }
          }
        

         
      }
      delete[] lps ; 

      
}


//brute force 

#include<iostream>
using namespace std ;

void bruteForce(string text , string pat ){
    int n = text.length();
    int m = pat.length();

    for(int i = 0 ; i<n-m ;i++){
        int j = 0;

        while(j<m && text[i+j]==pat[j]){
             j++;
        }

        if(j==m){
            cout << "Found at index " << i << endl;
        }
    }
}

//merge sort 
#include <iostream>
using namespace std;

void mergeArrays(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        mergeArrays(arr, left, mid, right);
    }
}

void printArr(int arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[8] = {9, 4, 7, 3, 1, 2, 6, 5};
    int n = 8;

    cout << "Before Merge Sort: ";
    printArr(arr, n);

    mergeSort(arr, 0, n - 1);

    cout << "After Merge Sort:  ";
    printArr(arr, n);

    return 0;
}


//quick sort 
#include <iostream>
using namespace std;

int partitionArray(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if(low < high) {
        int pi = partitionArray(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int arr[8] = {10, 7, 8, 9, 1, 5, 4, 3};
    int n = 8;

    cout << "Before Quick Sort: ";
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    cout << "After Quick Sort:  ";
    printArray(arr, n);

    return 0;
}


//stack 

#include <iostream>
using namespace std;

class Stack {
private:
    int arr[100];
    int top;
    int capacity;

public:
    Stack(int size = 100) {
        capacity = size;
        top = -1;
    }

    bool isFull() {
        return top == capacity - 1;
    }

    bool isEmpty() {
        return top == -1;
    }

    void push(int val) {
        if(isFull()) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = val;
    }

    int pop() {
        if(isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if(isEmpty()) {
            cout << "Stack is Empty\n";
            return -1;
        }
        return arr[top];
    }

    void display() {
        if(isEmpty()) {
            cout << "Stack is Empty\n";
            return;
        }
        for(int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    Stack s(10);

    s.push(5);
    s.push(10);
    s.push(15);

    cout << "Top element: " << s.peek() << endl;

    cout << "Stack elements: ";
    s.display();

    s.pop();
    cout << "After pop: ";
    s.display();

    return 0;
}



//queue
#include <iostream>
using namespace std;

class Queue {
private:
    int arr[100];
    int front;
    int rear;
    int capacity;

public:
    Queue(int size = 100) {
        capacity = size;
        front = 0;
        rear = -1;
    }

    bool isFull() {
        return rear == capacity - 1;
    }

    bool isEmpty() {
        return front > rear;
    }

    void enqueue(int val) {
        if(isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        arr[++rear] = val;
    }

    int dequeue() {
        if(isEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        return arr[front++];
    }

    int frontElement() {
        if(isEmpty()) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return arr[front];
    }

    int rearElement() {
        if(isEmpty()) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return arr[rear];
    }

    void display() {
        if(isEmpty()) {
            cout << "Queue is Empty\n";
            return;
        }
        for(int i = front; i <= rear; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    Queue q(10);

    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);

    cout << "Front element: " << q.frontElement() << endl;
    cout << "Rear element: " << q.rearElement() << endl;

    cout << "Queue elements: ";
    q.display();

    q.dequeue();
    cout << "After dequeue: ";
    q.display();

    return 0;
}

//hashing 
const int TABLE_SIZE = 10;

struct Node {
    int key;           
    string value;    
    Node* next;        

    Node(int k, const string& v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable {
private:
    Node* table[TABLE_SIZE];  

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void insert(int key, const string& name) {
        int index = hashFunction(key);

        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = name;  
                return;
            }
            current = current->next;
        }
        
        Node* newNode = new Node(key, name);
        newNode->next = table[index];
        table[index] = newNode;
    }

    string search(int key) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        return "NOT FOUND";
    }


    void remove(int key) {
        int index = hashFunction(key);
        Node* temp = table[index];
        Node* prev = nullptr;

        while (temp != nullptr && temp->key!=key) {
            prev = temp;
            temp = temp->next;
        }
        if(temp==nullptr){
        	cout << "Key " << key << " not found\n";
		}
        if (prev == nullptr) {
            table[index] = temp->next;
        } 
		else {
            prev->next = temp->next;
        }
        delete temp;
        cout << "Key " << key << " deleted\n";
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << " : ";
            Node* current = table[i];
            if (!current) {
                cout << "EMPTY";
            }
            while (current != nullptr) {
                cout << " -> [Key: " << current->key
                     << ", Name: " << current->value << "]";
                current = current->next;
            }
            cout << endl;
        }
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
};

// Linear Probing
const int TABLE_SIZE = 10;

class HashTable {
private:
    int keys[TABLE_SIZE];        
    string values[TABLE_SIZE];   
    bool occupied[TABLE_SIZE];   

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            occupied[i] = false;
            keys[i] = 0;
            values[i] = "";
        }
    }

    void insert(int key, const string& name) {
        int index = hashFunction(key);
        int startIndex = index; 

        while (occupied[index]) {
            if (keys[index] == key) {
                values[index] = name;
                return;
            }

            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) {
                cout << "Hash table is full, cannot insert key " << key << endl;
                return;
            }
        }

        keys[index] = key;
        values[index] = name;
        occupied[index] = true;
    }

    string search(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (occupied[index]) {
            if (keys[index] == key) {
                return values[index];   
            }

            index = (index + 1) % TABLE_SIZE;

            if (index == startIndex) {
                break;
            }
        }

        return "NOT FOUND";
    }

    void display() {
        cout << "Index\tKey\tName\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) {
                cout << i << "\t" << keys[i] << "\t" << values[i] << "\n";
            } else {
                cout << i << "\t" << "-\t" << "-\n";
            }
        }
    }
};

// Quadratic Probing
const int TABLE_SIZE = 10;

class HashTable {
private:
    int keys[TABLE_SIZE];
    string values[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            keys[i] = 0;
            values[i] = "";
            occupied[i] = false;
        }
    }

    void insert(int key, const string& name) {
        int hash = hashFunction(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (hash + i * i) % TABLE_SIZE;

            if (!occupied[index] || keys[index] == key) {
                keys[index] = key;
                values[index] = name;
                occupied[index] = true;
                return;
            }

            i++;
        }

        cout << "Hash table full, cannot insert key " << key << endl;
    }

    string search(int key) {
        int hash = hashFunction(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (hash + i * i) % TABLE_SIZE;

            if (!occupied[index]) return "NOT FOUND";
            if (keys[index] == key) return values[index];

            i++;
        }

        return "NOT FOUND";
    }

    void display() {
        cout << "Index\tKey\tName\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i])
                cout << i << "\t" << keys[i] << "\t" << values[i] << "\n";
            else
                cout << i << "\t-\t-\n";
        }
    }
};

// Double Hashing
const int TABLE_SIZE = 10;

class HashTable {
private:
    int keys[TABLE_SIZE];
    string values[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

    int hash1(int key) {
        return key % TABLE_SIZE;
    }

    int hash2(int key) {
        int R = 7;
        return R - (key % R);
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            keys[i] = 0;
            values[i] = "";
            occupied[i] = false;
        }
    }

    void insert(int key, const string& name) {
        int h1 = hash1(key);
        int h2 = hash2(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (h1 + i * h2) % TABLE_SIZE;

            if (!occupied[index] || keys[index] == key) {
                keys[index] = key;
                values[index] = name;
                occupied[index] = true;
                return;
            }

            i++;
        }

        cout << "Hash table full, cannot insert key " << key << endl;
    }

    string search(int key) {
        int h1 = hash1(key);
        int h2 = hash2(key);
        int index;
        int i = 0;

        while (i < TABLE_SIZE) {
            index = (h1 + i * h2) % TABLE_SIZE;

            if (!occupied[index]) return "NOT FOUND";
            if (keys[index] == key) return values[index];

            i++;
        }

        return "NOT FOUND";
    }

    void display() {
        cout << "Index\tKey\tName\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i])
                cout << i << "\t" << keys[i] << "\t" << values[i] << "\n";
            else
                cout << i << "\t-\t-\n";
        }
    }
};
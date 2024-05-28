#include <iostream>
#include <queue>

using namespace std;

// Define a struct representing your data
struct Data {
    int priority;
    string name;
    
    // Constructor
    Data(int p, const string& n) : priority(p), name(n) {}
    
    // Overload the < operator for priority comparison
    bool operator<(const Data& other) const {
        return priority < other.priority;
    }
};

int main() {
    // Define a priority queue of Data structs
    priority_queue<Data> pq; //max-heap
    //can use multiply by -1 logic for minheap abilities
    //or you can priority_queue <Data, vector<Data>, greater<Data>> gq;
    //or better yet what chatgpt said (first time using it for this alr)
    //to use priority_queue<Data> pq;
    //and replace priority < other.priority with priority > other.priority

    // Push some elements into the priority queue
    pq.push(Data(3, "Alice"));
    pq.push(Data(1, "Bob"));
    pq.push(Data(2, "Charlie"));

    // Pop elements from the priority queue
    while (!pq.empty()) {
        Data d = pq.top();
        cout << "Name: " << d.name << ", Priority: " << d.priority << endl;
        pq.pop();
    }

    return 0;
}

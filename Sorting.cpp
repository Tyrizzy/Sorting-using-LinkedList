#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Node {
    string name;
    double rating;
    struct Node* next;
    Node(string n, double x)
    {
        this->name = n;
        this->rating = x;
        next = NULL;
    }
};
 
class LinkedlistIS {
    public:
    Node* head;
    Node* sorted;
 
    void push(string name, double rating)
    {
        /* allocate node */
        Node* newnode = new Node(name,rating);
        /* link the old list off the new node */
        newnode->next = head;
        /* move the head to point to the new node */
        head = newnode;
    }
 
    // function to sort a singly linked list using insertion
    // sort
    void insertionSort(Node* headref)
    {
        // Initialize sorted linked list
        sorted = NULL;
        Node* current = headref;
        // Traverse the given linked list and insert every
        // node to sorted
        while (current != NULL) {
            // Store next for next iteration
            Node* next = current->next;
            // insert current in sorted linked list
            sortedInsert(current);
            // Update current
            current = next;
        }
        // Update head_ref to point to sorted linked list
        head = sorted;
    }
 
    /*
     * function to insert a new_node in a list. Note that
     * this function expects a pointer to head_ref as this
     * can modify the head of the input linked list
     * (similar to push())
     */
    void sortedInsert(Node* newnode)
    {
        /* Special case for the head end */
        if (sorted == NULL || sorted->rating >= newnode->rating) {
            newnode->next = sorted;
            sorted = newnode;
        }
        else {
            Node* current = sorted;
            /* Locate the node before the point of insertion
             */
            while (current->next != NULL && current->next->rating < newnode->rating) {
                current = current->next;
            }
            newnode->next = current->next;
            current->next = newnode;
        }
    }

    // Function to reverse the list
    void reverse(Node **head_ref) {
        Node *temp = NULL;
        Node *prev = NULL;
        Node *current = (*head_ref);
        while(current != NULL) {
            temp = current->next;
            current->next = prev;
            prev = current;
            current = temp;
        }
        (*head_ref) = prev;
    }
};

int main(){
    LinkedlistIS list;
    list.head = NULL;
    string name;
    double rating;
    fstream datafile_ratings;
    fstream datafile_ratings_output;
    datafile_ratings.open("ratings.txt", ios::in);
    datafile_ratings_output.open("sorted_ratings.txt", ios::out);
    if (datafile_ratings.is_open() && datafile_ratings_output.is_open()){
        while(getline(datafile_ratings,name,',')){
            datafile_ratings >> rating;
            list.push(name,rating);
            list.insertionSort(list.head);
            list.reverse(&list.head);
        }
        
        while (list.head != NULL) {
            datafile_ratings_output << list.head->name << " - " << list.head->rating;
            cout << list.head->name << " - " << list.head->rating;
            list.head = list.head->next;
        }
        datafile_ratings.close();
        datafile_ratings_output.close();
    }
    else{
        cout << "CANNOT READ FILE" << endl;
    }
    return 0;
}
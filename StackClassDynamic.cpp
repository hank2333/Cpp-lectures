#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class node {
public:
    string name;
    char grade;
    int marks;
    double gpa;
    node* next;

    node(string namepara, char gradepara, int markspara, double gpapara)
        : name(namepara), grade(gradepara), marks(markspara), gpa(gpapara), next(nullptr) {}
};

class list {
protected:
    node* head;   // 改成 protected，让子类更自然访问
    friend class stack;

public:
    list() : head(nullptr) {}
    ~list();

    bool IsEmpty() { return head == nullptr; }
    node* InsertNode(int index, string a, char b, int c, double d);
    void DeleteNode(int index);
    void DisplayList();
};

list::~list() {
    while (head != nullptr) {
        node* temp = head;
        head = head->next;
        delete temp;
    }
}

node* list::InsertNode(int index, string a, char b, int c, double d) {

    node* newnode = new node(a, b, c, d);

    if (index == 0 || head == nullptr) {
        newnode->next = head;
        head = newnode;
        return head;
    }

    node* curr = head;
    for (int i = 0; i < index - 1 && curr->next != nullptr; i++) {
        curr = curr->next;
    }

    newnode->next = curr->next;
    curr->next = newnode;

    return head;
}

void list::DeleteNode(int index) {
    if (IsEmpty()) {
        cout << "List empty!\n";
        return;
    }

    if (index == 0) {
        node* temp = head;
        head = head->next;
        delete temp;
        cout << "Delete success!\n";
        return;
    }

    node* curr = head;
    for (int i = 0; i < index - 1 && curr->next != nullptr; i++) {
        curr = curr->next;
    }

    if (curr->next == nullptr) {
        cout << "Index out of range!\n";
        return;
    }

    node* rubbish = curr->next;
    curr->next = curr->next->next;
    delete rubbish;
    cout << "Delete success!\n";
}

void list::DisplayList() {
    node* temp = head;
    cout << fixed << setprecision(2);
    cout << "Name\tGrade\tMarks\tGPA\n";
    while (temp != nullptr) {
        cout << temp->name << "\t"
            << temp->grade << "\t"
            << temp->marks << "\t"
            << temp->gpa << endl;
        temp = temp->next;
    }
}


class stack : public list {
public:
    node* Top();
    void Push(string a, char b, int c, double d);
    void Pop();
};

node* stack::Top() {
    if (IsEmpty()) {
        cout << "Stack empty!\n";
        return nullptr;
    }

    node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }

    cout << fixed << setprecision(2);
    cout << "The top is:\n"
         << curr->name << "\t" << curr->grade << "\t"
         << curr->marks << "\t" << curr->gpa << endl;

    return curr;
}

void stack::Push(string a, char b, int c, double d) {
    // Tail insertion: avoid computing index
    node* newnode = new node(a, b, c, d);

    if (IsEmpty()) {
        head = newnode;
        return;
    }

    node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }

    curr->next = newnode;
}

void stack::Pop() {
    if (IsEmpty()) {
        cout << "Stack empty!\n";
        return;
    }

    if (head->next == nullptr) {
        cout << head->name << "\t" << head->grade << "\t"
             << head->marks << "\t" << head->gpa << "\nPoped!\n";

        delete head;
        head = nullptr;
        return;
    }

    node* curr = head;
    while (curr->next->next != nullptr) {
        curr = curr->next;
    }

    node* topNode = curr->next;

    cout << fixed << setprecision(2);
    cout << topNode->name << "\t" << topNode->grade << "\t"
         << topNode->marks << "\t" << topNode->gpa << "\nPoped!\n";

    delete topNode;
    curr->next = nullptr;
}


int main() {
    stack s1;
    s1.Push("john", 'C', 61, 2.30);
    s1.Push("stephen", 'D', 43, 0.00);
    s1.Push("ann", 'A', 92, 4.00);
    s1.Push("dave", 'B', 77, 3.30);

    s1.Top();
    s1.Pop();
    s1.DisplayList();

    system("pause");
    return 0;
}

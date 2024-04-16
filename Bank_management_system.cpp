#include <iostream>
#include <queue>
using namespace std;

struct customerinfo 
{
    string name;
    int accno;
    string address;
    int contact;
    customerinfo *next;
    customerinfo *prev;
    queue<string> transactionHistory;

    customerinfo(string name, int accno, string address, int contact) {
        this->name = name;
        this->accno = accno;
        this->address = address;
        this->contact = contact;
        next = NULL;
        prev = NULL;
    }
};

struct Node 
{
    int key;
    customerinfo* customer;
    Node* left;
    Node* right;

    Node(int key, customerinfo* customer) : key(key), customer(customer), left(NULL), right(NULL) {}
};

class accountbook {
private:
    customerinfo* head;
    customerinfo* hashtable[10];
    Node* root;

    int hashFunction(int accno) {
        return accno % 10;
    }

    Node* insert(Node* node, int key, customerinfo* customer) {
        if (!node) return new Node(key, customer);

        if (key < node->key)
            node->left = insert(node->left, key, customer);
        else if (key > node->key)
            node->right = insert(node->right, key, customer);

        return node;
    }

    customerinfo* searchBST(Node* node, int key) {
        if (!node || node->key == key) return (node ? node->customer : NULL);

        if (key < node->key)
            return searchBST(node->left, key);
        else
            return searchBST(node->right, key);
    }

public:
    accountbook() {
        head = NULL;
        root = NULL;
        for (int i = 0; i < 10; i++) {
            hashtable[i] = NULL;
        }
    }

    void addAccount(string name, int accno, string address, int contact)
     {
        customerinfo* customer = new customerinfo(name, accno, address, contact);
        root = insert(root, accno, customer);

        int hashValue = hashFunction(accno);
        if (head == NULL) {
            head = customer;
        } else {
            customerinfo* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = customer;
            customer->prev = temp;
        }
        customer->next = hashtable[hashValue];
        hashtable[hashValue] = customer;
    }

    void deleteAccount(int accno)
     {
        int hashValue = hashFunction(accno);
        customerinfo* temp = hashtable[hashValue];
        
        while (temp) {
            if (temp->accno == accno) {
                if (temp->prev) {
                    temp->prev->next = temp->next;
                } else {
                    hashtable[hashValue] = temp->next;
                }

                if (temp->next) {
                    temp->next->prev = temp->prev;
                }
                
                delete temp;
                cout << "Account deleted successfully!" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Account not found!" << endl;
    }

    void addTransaction(int accno, const string& transaction)
    {
        int hashValue = hashFunction(accno);
        customerinfo* temp = hashtable[hashValue];
        
        while (temp) {
            if (temp->accno == accno) {
                temp->transactionHistory.push(transaction);
                return;
            }
            temp = temp->next;
        }
        cout << "Account not found!" << endl;
    }

    void getCustomer(int accno) 
    {
        customerinfo* found = searchBST(root, accno);
        if (found) {
            cout << "Customer found with Account Number: " << found->accno << endl;
            cout << "Name: " << found->name << endl;
            cout << "Address: " << found->address << endl;
            cout << "Contact: " << found->contact << endl;
        } else {
            cout << "Customer with Account Number not found." << endl;
        }
    }

    void printTransactionHistory(int accno) 
    {
        int hashValue = hashFunction(accno);
        customerinfo* temp = hashtable[hashValue];
        
        while (temp) {
            if (temp->accno == accno) {
                queue<string> tempQueue = temp->transactionHistory;
                cout << "Transaction history for Account No. " << accno << ":" << endl;
                while (!tempQueue.empty()) {
                    cout << tempQueue.front() << endl;
                    tempQueue.pop();
                }
                return;
            }
            temp = temp->next;
        }
        cout << "Account not found!" << endl;
    }

    void printList() 
    {
        customerinfo* temp = head;
        while (temp != NULL) {
            cout << temp->name << " " << temp->accno << " " << temp->address << " " << temp->contact << endl;
            temp = temp->next;
        }
    }
};

int main() 
{
    accountbook a1;
    int choice;
    int accno;
    string name, address, transaction;
    int contact;

    do {
        cout << "\n===== Account Management System =====" << endl;
        cout << "1. Add Account" << endl;
        cout << "2. Delete Account" << endl;
        cout << "3. Add Transaction" << endl;
        cout << "4. View Customer Details" << endl;
        cout << "5. View Transaction History" << endl;
        cout << "6. Print All Customers" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin.ignore(); // to clear the buffer
                getline(cin, name);
                cout << "Enter account number: ";
                cin >> accno;
                cout << "Enter address: ";
                cin.ignore();
                getline(cin, address);
                cout << "Enter contact: ";
                cin >> contact;
                a1.addAccount(name, accno, address, contact);
                break;

            case 2:
                cout << "Enter account number to delete: ";
                cin >> accno;
                a1.deleteAccount(accno);
                break;

            case 3:
                cout << "Enter account number for transaction: ";
                cin >> accno;
                cout << "Enter transaction details: ";
                cin.ignore();
                getline(cin, transaction);
                a1.addTransaction(accno, transaction);
                break;

            case 4:
                cout << "Enter account number to view details: ";
                cin >> accno;
                a1.getCustomer(accno);
                break;

            case 5:
                cout << "Enter account number to view transaction history: ";
                cin >> accno;
                a1.printTransactionHistory(accno);
                break;

            case 6:
                cout << "\n===== List of Customers =====" << endl;
                a1.printList();
                break;

            case 7:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }

    } while (choice != 7);

    return 0;
}


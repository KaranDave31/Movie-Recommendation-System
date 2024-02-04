
#include <iostream>

#include <string>

using namespace std;

//Here, we define a Node class that represents a contact in the phonebook. It contains three fields: name, number, and email. It also has two pointers, left and right, for the left and right children in a binary search tree. The constructor initializes these fields when a new Node object is created.

class Node {

public:

   string name;

   string number;

   string email;

   Node* left;

   Node* right;

   Node(string name, string number, string email) {

       this->name = name;

       this->number = number;

       this->email = email;

       left = right = nullptr;

   }

};

//The Phonebook class is defined to manage the phonebook. It has a private root pointer, which points to the root node of the binary search tree. The constructor initializes the root as nullptr.

class Phonebook {

private:

   Node* root;

public:

   Phonebook() {

       root = nullptr;

   }

//The insert function is a recursive function to insert a new contact into the binary search tree. It takes a reference to a Node pointer, the name, number, and email of the contact. It checks if the current node is null, and if so, it creates a new node with the given data. Otherwise, it navigates to the left or right subtree based on the comparison of name.

   void insert(Node*& node, string name, string number, string email) {

       if (node == nullptr) {

           node = new Node(name, number, email);

       }

       else if (name < node->name) {

           insert(node->left, name, number, email);

       }

       else if (name > node->name) {

           insert(node->right, name, number, email);

       }

   }

//This is a public method for inserting a new contact into the phonebook. It calls the private insert method with the root node as the starting point.

   void insert(string name, string number, string email) {

       insert(root, name, number, email);

   }

//The search function is used to find a contact in the binary search tree. It is a recursive function that takes a reference to a Node pointer and the name to search for. It returns the node if found, or nullptr if not found.

   Node* search(Node* node, string name) {

       if (node == nullptr || node->name == name) {

           return node;

       }

       if (name < node->name) {

           return search(node->left, name);

       }

       return search(node->right, name);

   }

//This is a public method for searching a contact by name. It calls the private search method and displays the contact's information if found.

   void search(string name) {

       Node* result = search(root, name);

       if (result != nullptr) {

           cout << "Contact found:" << endl;

           cout << "Name: " << result->name << endl;

           cout << "Number: " << result->number << endl;

           cout << "Email: " << result->email << endl;

       }

       else {

           cout << "Contact not found." << endl;

       }

   }

//The findMin function is used to find the minimum node in a binary search tree, which is the leftmost node. It takes a Node as an argument and returns the minimum node.

   Node* findMin(Node* node) {

       while (node->left != nullptr) {

           node = node->left;

       }

       return node;

   }

//The remove function is used to delete a contact from the binary search tree. It is a recursive function that takes a Node and the name of the contact to remove. It returns the modified tree after removing the contact.

   Node* remove(Node* node, string name) {

       if (node == nullptr) {

           return node;

       }

       if (name < node->name) {

           node->left = remove(node->left, name);

       }

       else if (name > node->name) {

           node->right = remove(node->right, name);

       }

       else {

           if (node->left == nullptr) {

               Node* temp = node->right;

               delete node;

               return temp;

           }

           else if (node->right == nullptr) {

               Node* temp = node->left;

               delete node;

               return temp;

           }

           Node* temp = findMin(node->right);

           node->name = temp->name;

           node->number = temp->number;

           node->email = temp->email;

           node->right = remove(node->right, temp->name);

       }

       return node;

   }

//This is a public method for removing a contact by name. It calls the private remove method and updates the root if necessary.

   void remove(string name) {

       root = remove(root, name);

   }

//The display function is used to print the contacts in the binary search tree in sorted order. It is a recursive function that traverses the tree in-order and displays each contact.

   void display(Node* node) {

       if (node != nullptr) {

           display(node->left);

           cout << "Name: " << node->name << ", Number: " << node->number << ", Email: " << node->email << endl;

           display(node->right);

       }

   }

//This is a public method for displaying all the contacts. It calls the private display method with the root as the starting point.

   void display() {

       display(root);

   }

};

//In the main function, we create a Phonebook object and provide a simple command-line menu for interacting with the phonebook. The user can add, search, remove, display contacts, or exit the program. The program continues to run until the user chooses to exit.

int main() {

   Phonebook phonebook;

   int choice;

   string name, number, email;

   do {

       cout << "1. Add Contact\n2. Search Contact\n3. Remove Contact\n4. Display All Contacts\n5. Exit\n";

       cout << "Enter your choice: ";

       cin >> choice;

       switch (choice) {

           case 1:

               cout << "Enter Name: ";

               cin >> name;

               cout << "Enter Number: ";

               cin >> number;

               cout << "Enter Email: ";

               cin >> email;

               phonebook.insert(name, number, email);

               break;

           case 2:

               cout << "Enter Name to Search: ";

               cin >> name;

               phonebook.search(name);

               break;

           case 3:

               cout << "Enter Name to Remove: ";

               cin >> name;

               phonebook.remove(name);

               break;

           case 4:

               phonebook.display();

               break;

           case 5:

               cout << "Exiting Phonebook. Goodbye!" << endl;

               break;

           default:

               cout << "Invalid choice. Please try again." << endl;

       }

   } while (choice != 5);

   return 0;

}


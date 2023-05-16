//  Program12BinarySearchTree
//  Created by Minjing Liang on 11/23/20.
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class BinarySearchTree { // Class Declaration
private:
    struct TreeNode{
        double value; //Value in the node
        TreeNode *left; //Pointer to left child node
        TreeNode *right; //Pointer to right child node
    };
    TreeNode *root; //Pointer to the root node
    int number1, number2; //To hold level and leaf count
    bool search(double, TreeNode *);
    void inorder(TreeNode *, vector <double>&);
    void size(TreeNode *);
    void leafCount(TreeNode *);
    void height(TreeNode*);
    void width(TreeNode*, int *);
    void copy(TreeNode*);
    void remove(TreeNode*);
    void displayInOrder(TreeNode*) const;
public:
    BinarySearchTree()
    { root = NULL; }
    BinarySearchTree(const BinarySearchTree&);
    void insert(double);
    bool search(double);
    void inorder(vector <double>&);
    int size();//Total nodes
    int leafCount();//Total leaf nodes
    int height();//Total levels
    int width(); //Width of the tree
    const BinarySearchTree & operator=(const BinarySearchTree &);
    void displayInOrder()const;
};
void BinarySearchTree::insert(double x){
    TreeNode *newNode = NULL; //Pointer to a new node
    newNode = new TreeNode; //Create a new node
    newNode->value = x;     //Store num in it
    newNode->left = newNode->right = NULL;
    if (root == NULL){
        root = newNode; //If empty newnode is root
    }
    else{
        TreeNode *temp = root;//Pointer to root
        while (temp != NULL){ //Traverse the tree
            if (x == temp->value){ //Num already exist
              cout << "Value Already exist," << "insert another value!" << endl;
              return;
            }
            else if ((x < temp->value) && (temp->left == NULL)){
              temp->left = newNode;//num insert to left leaf node
              break;
            }
            else if (x < temp->value){
              temp = temp->left;
            }
            else if ((x > temp->value) && (temp->right == NULL)){
              temp->right = newNode; //Num insert to right leaf node
              break;
            }
            else{
              temp =temp->right;
            }
        }
    }
}
bool BinarySearchTree::search(double x, TreeNode *node){
    if (node == NULL) //Empty tree
        return false;
    if(x == node->value)//Num found at the root
        return true;
    else if((x < node->value) && (node->left == NULL))
        return false;//Not found from left
    else if (x < node->value)
        return search(x, node->left);
    else if((x > node->value) && (node->right == NULL))
        return false;//Not found from right
    else
        return search(x, node->right);
    return true;
}
bool BinarySearchTree::search(double val){
    if (root == NULL){ //Empty tree
        cout << "The value " << val << " was not found in the tree" << endl;
        return false;
    }
    else if (val == root->value){ //Found at the root
        cout << "The value " << val << " was located" << endl;
        return true;
    }
    else if (val < root->value){ //Traverse left to find num
        if(search(val, root->left) == true)
            cout << "The value " << val << " was located" << endl;
        else
            cout << "The value " << val << " was not found" << endl;
    }
    else{ //Traverse right to find num
        if(search(val, root->right) == true)
            cout << "The value " << val << " was located" << endl;
        else
            cout << "The value " << val << " was not found" << endl;
    }
    return true;
}
//Copy elements from tree to list
void BinarySearchTree::inorder(TreeNode *node, vector <double>& list){
    if(node){
        inorder(node->left, list);
        list.push_back(node->value);
        inorder(node->right, list);
    }
}
void BinarySearchTree::inorder(vector <double>& list){
    inorder(root, list);
}
void BinarySearchTree::size(TreeNode *node){
    if(node->left != NULL)//Traverse the left
        size(node->left);
    if (node->right != NULL)//Traverse the right
        size(node->right);
    number1++;//size count increase
}
int BinarySearchTree::size(){
    number1 = 0;
    if (root == NULL)//Empty tree
        return number1;
    else
        size(root);//Call size(TreeNode) func
    return number1;
}
void BinarySearchTree:: leafCount(TreeNode* node){
    if(node->left != NULL) //Traverse
        leafCount(node->left); //Recursive call
    if (node->right != NULL) //Traverse
        leafCount(node->right);
    if ((node->left == NULL) && (node->right == NULL)) //Leaf node
        number1++;
}
int BinarySearchTree:: leafCount(){
    number1 = 0; //Hold the leaf count
    if (root == NULL) //Empty tree
        return number1;
    else
        leafCount(root);//Call leafCount(TreeNode*) func
    return number1;
}
void BinarySearchTree::height(TreeNode* node){
    number2++;//Level increase
    if (node->left != NULL)//Traverse
        height(node->left); //Recursive call
    if (node->right != NULL)//Traverse
        height(node->right);
    if ((node->left == NULL) && (node->right == NULL)){
        if (number2 > number1)
            number1 = number2;
    }
    number2--;
}
int BinarySearchTree::height(){
    number1 = 0;
    number2 = 0;
    if (root == NULL)//Empty tree
        return number1;
    else
        height(root);//Call height(TreeNode*) func
    return number1; //Level count
}
void BinarySearchTree::width(TreeNode* node, int *w){
    number2++;//The level increase
    w[number2-1]++;
    if (node->left != NULL) //Traverse
        width(node->left,w);
    if (node->right != NULL)
        width(node->right,w);
    number2--;
}
int BinarySearchTree::width(){
    int h = BinarySearchTree::height();//Get the hight of the tree
    number1 = 0;
    number2 = 0;
    int w[h];//Array to hold the width for each level
    for (int n=0;n<h;n++)
        w[n] = 0;//Initial to 0
    if(root==NULL) //Empty tree
        return 0;
    else
        width(root,w);//Call width(TreeNode*)func
    for (int n=0;n<h;n++){
        if(w[n] > number1)
            number1 = w[n]; //number1 hold the width
    }
    return number1;
}
void BinarySearchTree::copy(TreeNode* node){
    if(node){
        insert(node->value);//Call insert functin
        copy(node->left); //Recursive call
        copy(node->right);
    }
}
void BinarySearchTree::remove(TreeNode* node){
    if(node){ //Reursive delete nodes
        remove(node->left);
        remove(node->right);
        delete node;
    }
}
BinarySearchTree::BinarySearchTree(const BinarySearchTree& obj){
    root = NULL;
    copy(obj.root);//Call copy nodes function
}
const BinarySearchTree & BinarySearchTree::operator=(const BinarySearchTree & obj){
    if(this != &obj){ //The new tree is not the right one
        remove(root); //Delete the elements in the new tree
        root = NULL;
        copy(obj.root);//Call copy function
    }
    return *this;
}

void BinarySearchTree::displayInOrder(TreeNode* node)const{
    if(node){ //Recursive tree inorder display
        displayInOrder(node->left);
        cout << node->value << " ";
        displayInOrder(node->right);
    }
}
void BinarySearchTree::displayInOrder() const{
    displayInOrder(root);
    cout << endl;
}
int main(){
    BinarySearchTree tree1; //Create a BST obj
    vector <double> treeList; // Create a list(use vector)
    cout << "Inserting nodes.\n";
    tree1.insert(14.5); //Call insert function
    tree1.insert(12.6);
    tree1.insert(20.3);
    tree1.insert(19.1);
    tree1.insert(10);
    tree1.insert(13.9);
    tree1.insert(8.4);
    tree1.insert(21.8);
    tree1.insert(22.7);
    tree1.insert(28);
    tree1.insert(39);
    tree1.insert(45.2);
    cout <<"Inorder display tree1\n";
    tree1.displayInOrder(); //Dispaly BST
    tree1.search(10); //Call search function
    tree1.search(23);
    tree1.search(20.3);
    cout << "\nThe total number of nodes is " << tree1.size() << endl;
    cout << "The total number of leaf nodes is " << tree1.leafCount() << endl;
    cout << "The height of the tree is " << tree1.height() << endl;
    cout << "The width of the tree is " << tree1.width() << endl;
    tree1.inorder(treeList);//Call inorder func copy element to list
    cout << "\nPrinting tree list" << endl;
    for (int x = 0; x < treeList.size(); x++){ //Display list
        cout << treeList[x] << " ";
    }
    BinarySearchTree tree2(tree1);//Create new tree call copy constructor
    cout <<"\nInorder display tree2\n";
    tree2.displayInOrder();
    BinarySearchTree tree3;//Create new tree
    tree3 = tree1; //Call overloaded assignment operation func
    cout <<"Inorder display tree3\n";
    tree3.displayInOrder();
    return 0;
}


#include "TreeNode.h"

//constructor
TreeNode::TreeNode(DBentry* _entryPtr) {
    this -> entryPtr = _entryPtr;
    this -> left = NULL;
    this -> right = NULL;
}

//destructor
TreeNode::~TreeNode() {
    delete entryPtr;
}

//set left child of TreeNode
void TreeNode::setLeft(TreeNode* newLeft) {
    this -> left = newLeft;
}

//set right child of TreeNode
void TreeNode::setRight(TreeNode* newRight) {
    this -> right = newRight;
}

//get left child of TreeNode
TreeNode* TreeNode::getLeft() const {
    return left;
}

//get right child of TreeNode
TreeNode* TreeNode::getRight() const {
    return right;
}

//return pointer to DBentry the TreeNode contains
DBentry* TreeNode::getEntry() const {
    return entryPtr;
}

//function to re-attach two subtrees to above node
void TreeNode::removeHelper(TreeNode*& node) {
    if (right == NULL)
        return;
    if (right -> left == NULL) {
        right = node;
        return;
    }
    
    TreeNode* temp = right -> left;
    removeHelper(right -> left);
    
    temp -> right = right;
    temp -> left = left;
    node = temp;
}

//remove a node with the given name and re-attach the left and right subtrees to the above node
bool TreeNode::remove(string name, TreeNode*& node) {
    string currentNodeName = node -> getEntry()-> getName();
    if (name.compare(currentNodeName) > 0) {
        if (right == NULL)
            return false;
        else
            return right -> remove(name, right);
    }
    else if (name.compare(currentNodeName) < 0) {
        if (left == NULL)
            return false;
        else return left -> remove(name, left);
    }
    if (name.compare(currentNodeName) == 0) {
        if (left == NULL && right == NULL) {
            node = NULL;
            delete this;
        }
        else if (left == NULL && right != NULL) {
            node = right;
            delete this;
        }
        else if (left != NULL && right == NULL) {
            node = left;
            delete this;
        }
        else {
            removeHelper(node);
            delete this;
        }
        return true;
    }
}
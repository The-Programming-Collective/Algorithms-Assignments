#include <iostream>
#include "queue"
#include "map"

//FINAL//
////////////////////////////////// NODE CLASS //////////////////////////////////


enum Color{RED, BLACK};

template <typename T>
class Node{
public:
    T m_value;
    Color m_color;
    Node *m_leftChild, *m_rightChild, *m_parent;

    Node(T value, Node<T> *leftChild = nullptr, Node<T> *rightChild = nullptr, Node<T> *parent = nullptr, Color color = RED ){
        this->m_value = value;
        this->m_leftChild = leftChild;
        this->m_rightChild = rightChild;
        this->m_parent = parent;
        this->m_color = color;
    }


    // Printing utility
    void print() {
        std::string colors[] = {"RED", "BLACK"};

        std::cout << "Value: " << m_value << '\n';
        std::cout << "Color: " << colors[m_color] << '\n';
    }
    template <typename nodeType>
    friend std::ostream& operator << (std::ostream& out, Node<nodeType>& node) {
        node.print();
        return out;
    }
};









////////////////////////////////// RED-BLACK TREE CLASS //////////////////////////////////


template <typename T>
class RBTree{
public: Node<T> *m_root;
private:
    /**
     * @brief standard binary search tree insertion function
     * @param root reference to pointer of the root node of the tree.
     * @param node reference to pointer of the node to be inserted.
     * @return root pointer it started at.
     */
    Node<T>* insertNode(Node<T> *&root, Node<T> *&node);

    /**
     * @brief function that performs LEFT rotation on nodes when balancing is violated.
     * @param root, node two nodes that are going to be rotated against each other.
     */
    void leftRotation(Node<T> *&root, Node<T> *&node);

    /**
     * @brief function that performs RIGHT rotation on nodes when balancing is violated.
     * @param root, node two nodes that are going to be rotated against each other.
     */
    void rightRotation(Node<T> *&root, Node<T> *&node);

    /**
     * @brief contains the necessary logic to fix the Red-Black Tree when its violated.
     */
    void fixTree(Node<T> *&root, Node<T> *&node);

    /**
     *  @brief Normal search function but without the printing.
     *  @param  value a thing of arbitrary type
     *
     *  @return   true if found,
     *  false otherwise.
     *
     */
    bool exists(T value);

    /**
     *  @brief searches for node.
     *  @param  value a thing of arbitrary type
     *  @return node pointer if found, nullptr otherwise.
     *
     */
    Node<T>* returnNode(T value);

    /**
     *  @brief Recursively checks if tree with given node is balanced.
     *  A more efficient implementation than calling the getHeight() function recursively as its calculated internally.
     *  @param  root a pointer to the node whose subtrees you want to check.
     *  @param  height a pointer to an int value to store the height of the bigger subtree.
     *  @return  true if tree is balanced
     */
    bool isBalancedHelper(Node<T> *root, int *height);

    /**
     * @brief checks if m_root is a nullptr
     * @return true if tree is empty.
     */
    bool isEmpty();

    /**
     * @biref displays tree inorder.
     * @param root  a pointer to the root node of a subtree.
     */
    void displayInorderHelper(Node<T> *root);

    /**
     * @brief recursively calculates the height of a subtree.
     * @param root a pointer to the root node of a subtree
     * @return height of the tree.
     * @note uses the convention that root is level 1.
     */
    int getHeightHelper(Node<T> *root);

    /**
     * @brief calculates the vertical sum for every column in the binary
     * search tree using the std::map data structure (dictionary).
     * @param root a pointer to the root node of a subtree.
     * @param dictionary a reference to the dictionary that will be used to store the sum of each column.
     * Pairs inside the dictionary will be of types <int, T>, where T is an arbitrary object.
     * @param distance an int value that represents the vertical line position
     * @note THIS FUNCTION ASSUMES THAT THE GENERIC TYPE <T>
     * HAS THE APPROPRIATE LOGIC AND OVERLOADING OF THE += OPERATOR.
     */
    void printVerticalSumHelper(std::map<int, T> &dictionary, Node<T> *root, int distance);

public:
    RBTree() {m_root = nullptr;}

    /**
     *  @brief calls insertNode() and then fixeTree() to correct unbalanced nodes.
     */
    void insert(T value);

    /**
     * @brief gets height of the Red-Black tree by calling getHeightHelper()
     * @return height of the Red-Black tree.
     */
    int getHeight();

    /**
     * @brief returns the uncle node of the node with the value given.
     * @param value an arbitrary value of node you want to query.
     * @return uncle node pointer of node with given value if exists.
     */
    Node<T>* uncle(T value);

    /**
     * @brief checks if subtree of given root value is balanced by calling isBalancedHelper().
     * @param value an arbitrary value of root you want to query.
     * @return true if tree balanced
     */
    bool isBalanced(T value);

    /**
     * @brief searches for value and prints the path to the value
     * @param value arbitrary value you want to search for.
     * @return true if value is found.
     */
    bool search(T value);

    /**
     * @brief calls displayInorderHelper() which prints tree inorder.
     */
    void print();

    /**
     * @brief prints tree vertical sums using the modified dictionary
     * that is passed into the printVerticalSumHelper() function.
     *
     * @note THE FUNCTION printVerticalSumHelper()
     * ASSUMES THAT THE GENERIC TYPE <T>
     * HAS THE APPROPRIATE LOGIC AND OVERLOADING OF THE += OPERATOR.
     */
     void printVerticalSum();
};

////////////////////////////////// PRIVATE METHODS //////////////////////////////////


template <typename T>
Node<T>* RBTree<T>::insertNode(Node<T> *&root, Node<T> *&node) {
    /* If the tree is empty, the node we're searching for*/
    if (root == nullptr)
        return node;

    if (node->m_value < root->m_value)
    {
        root->m_leftChild = insertNode(root->m_leftChild, node);
        root->m_leftChild->m_parent = root;
    }
    else if (node->m_value > root->m_value)
    {
        root->m_rightChild = insertNode(root->m_rightChild, node);
        root->m_rightChild->m_parent = root;
    }
    return root;
}




template <typename T>
void RBTree<T>::leftRotation(Node<T> *&root, Node<T> *&node) {
    Node<T> *nodeRight = node->m_rightChild;

    node->m_rightChild = nodeRight->m_leftChild;

    if (node->m_rightChild != nullptr)
        node->m_rightChild->m_parent = node;

    nodeRight->m_parent = node->m_parent;

    if (node->m_parent == nullptr)
        root = nodeRight;

    else if (node == node->m_parent->m_leftChild)
        node->m_parent->m_leftChild = nodeRight;

    else
        node->m_parent->m_rightChild = nodeRight;

    nodeRight->m_leftChild = node;
    node->m_parent = nodeRight;
}


template <typename T>
void RBTree<T>::rightRotation(Node<T> *&root, Node<T> *&node) {
    Node<T> *leftNode = node->m_leftChild;

    node->m_leftChild = leftNode->m_rightChild;

    if (node->m_leftChild != nullptr)
        node->m_leftChild->m_parent = node;

    leftNode->m_parent = node->m_parent;

    if (node->m_parent == nullptr)
        root = leftNode;

    else if (node == node->m_parent->m_leftChild)
        node->m_parent->m_leftChild = leftNode;

    else
        node->m_parent->m_rightChild = leftNode;

    leftNode->m_rightChild = node;
    node->m_parent = leftNode;
}




template <typename T>
void RBTree<T>::fixTree(Node<T> *&root, Node<T> *&node) {
    Node<T> *parentNode = nullptr;
    Node<T> *grandParentNode = nullptr;

    while ((node != root) && (node->m_color != Color::BLACK) &&
           (node->m_parent->m_color == Color::RED))
    {

        parentNode = node->m_parent;
        grandParentNode = node->m_parent->m_parent;

        // if node parent is right child of ITS parent

        if (parentNode == grandParentNode->m_leftChild)
        {

            Node<T> *uncleNode = grandParentNode->m_rightChild;

            // uncle is red so recolor
            if (uncleNode != nullptr && uncleNode->m_color == Color::RED)
            {
                grandParentNode->m_color = Color::RED;
                parentNode->m_color = Color::BLACK;
                uncleNode->m_color = Color::BLACK;
                node = grandParentNode;
            }

            else
            {
                // node is right so rotate left
                if (node == parentNode->m_rightChild)
                {
                    leftRotation(root, parentNode);
                    node = parentNode;
                    parentNode = node->m_parent;
                }

                // node is left so rotate right
                rightRotation(root, grandParentNode);
                std::swap(parentNode->m_color,
                     grandParentNode->m_color);
                node = parentNode;
            }
        }





            // if node parent is right child of ITS parent
        else
        {
            Node<T> *uncle_node = grandParentNode->m_leftChild;

            // uncle is red so recolor
            if ((uncle_node != nullptr) && (uncle_node->m_color == Color::RED))
            {
                grandParentNode->m_color = Color::RED;
                parentNode->m_color = Color::BLACK;
                uncle_node->m_color = Color::BLACK;
                node = grandParentNode;
            }
            else
            {
                // node is left so rotate right
                if (node == parentNode->m_leftChild)
                {
                    rightRotation(root, parentNode);
                    node = parentNode;
                    parentNode = node->m_parent;
                }

                // node is right so rotate left
                leftRotation(root, grandParentNode);
                std::swap(parentNode->m_color,
                     grandParentNode->m_color);
                node = parentNode;
            }
        }
    }

    root->m_color = Color::BLACK;
}




template <typename T>
bool RBTree<T>::exists(T value) {
    if (isEmpty())
        return false;


    Node<T> *curr = m_root;
    while(curr != nullptr)
    {
        if (curr->m_value == value)
            return true;

        if (value < curr->m_value)
            curr = curr->m_leftChild;
        else
            curr = curr->m_rightChild;
    }
    return false;
}





template <typename T>
Node<T>* RBTree<T>::returnNode(T value) {
    if (isEmpty())
        return nullptr;


    Node<T> *curr = m_root;
    while(curr != nullptr)
    {
        if (curr->m_value == value)
            return curr;

        if (value < curr->m_value)
            curr = curr->m_leftChild;
        else
            curr = curr->m_rightChild;
    }
    return nullptr;
}




template <typename T>
bool RBTree<T>::isBalancedHelper(Node<T> *root, int *height) {
    if (root == nullptr)
        return true;

    int leftTreeHeight = 0;
    int rightTreeHeight = 0;

    if (!isBalancedHelper(root->m_leftChild, &leftTreeHeight))
        return false;
    if  (!isBalancedHelper(root->m_rightChild, &rightTreeHeight))
        return false;

//    if (leftTreeHeight >= rightTreeHeight)
//        *height = leftTreeHeight + 1;
//    else
//        *height = rightTreeHeight + 1;

    *height = (leftTreeHeight >= rightTreeHeight) ? leftTreeHeight + 1 : rightTreeHeight + 1;

    if (std::abs(leftTreeHeight - rightTreeHeight) <= 1)
        return true;
    else
        return false;
}





template <typename T>
bool RBTree<T>::isEmpty() {return !m_root;}




template <typename T>
void RBTree<T>::displayInorderHelper(Node<T> *root) {
    if(root == nullptr)
        return;
    displayInorderHelper(root->m_leftChild);
    std::cout << *root << '\n';
    displayInorderHelper(root->m_rightChild);
}



template <typename T>
int RBTree<T>::getHeightHelper(Node<T> *root) {
    if (root == nullptr)
        return 0;

    int leftSubTreeHeight = getHeightHelper(root->m_leftChild);
    int rightSubTreeHeight = getHeightHelper(root->m_rightChild);

    if (leftSubTreeHeight > rightSubTreeHeight)
        return leftSubTreeHeight + 1;
    else
        return rightSubTreeHeight + 1;
}




template <typename T>
void RBTree<T>::printVerticalSumHelper(std::map<int, T> &dictionary, Node<T> *root, int distance) {
    /*
     * root -> 0
     * going left of root-> -1
     * going right of root-> 1
     */
    if(root == nullptr)
        return;

    /*
     * add the value of the sum in the same vertical line in its corresponding row.
     * dictionary values -> vertical_line_position(or distance): sum of vertical line
     */
    dictionary[distance] += root->m_value;

    // recurse on left and right subtrees until a nullptr is reached.
    printVerticalSumHelper(dictionary, root->m_leftChild, distance - 1);
    printVerticalSumHelper(dictionary, root->m_rightChild, distance + 1);
}


////////////////////////////////// PUBLIC METHODS //////////////////////////////////


template <typename T>
void RBTree<T>::insert(T value) {
    if (exists(value)) // if the value already exists, then insert fails and returns
        throw std::runtime_error("\nValue already exists.\n");
    Node<T> *node = new Node<T>(value);
    m_root = insertNode(m_root, node);
    fixTree(m_root, node);
}




template <typename T>
int RBTree<T>::getHeight() {
    return getHeightHelper(m_root);
}




template <typename T>
Node<T>* RBTree<T>::uncle(T value) {
    if (isEmpty())
        throw std::runtime_error("\nTree is empty\n");

    if (getHeight() <= 2) // if the tree contains 3 or fewer nodes, then uncle doesn't exist for any node.
        throw std::runtime_error("\nTree contains 3 nodes or less, uncle does not exist for any of the nodes\n");

    if (value == m_root->m_value) // if the root value was provided, throw error
        throw std::runtime_error("\nNode value given is the root, no uncle for root\n");

    Node<T>* node = returnNode(value);

    // if returnNode returns a nullptr, then node doesn't exist in the first place.
    if (node == nullptr)
        throw std::runtime_error("\nNode does not exist\n");

    if (node->m_parent == m_root) // if node's parent is the root then, uncle doesn't exist
        throw std::runtime_error("\nNode is in the second level of the tree, it cannot have an uncle.\n");


    Node<T>* grandParent = node->m_parent->m_parent;

    // if any of grandparent's children are null, then uncle does not exist
    if (grandParent->m_rightChild == nullptr || grandParent->m_leftChild == nullptr)
        return nullptr;

    // the uncle is the one that is NOT the node's parent.
    if (grandParent->m_leftChild == node->m_parent)
        return grandParent->m_rightChild;
    else
        return grandParent->m_leftChild;
}




template <typename T>
bool RBTree<T>::isBalanced(T value) {
    if (isEmpty())
        throw std::runtime_error("\nTree is empty\n");

    Node<T> *root = returnNode(value);
    if (root == nullptr)
        throw std::runtime_error("\nNode not found\n");

    int treeHeight = 0;
    return isBalancedHelper(root, &treeHeight);
}






template <typename T>
bool RBTree<T>::search(T value) {
    if (isEmpty())
        throw std::runtime_error("\nTree is empty\n");

    std::queue<T> queue;
    Node<T> *curr = m_root;
    while(curr != nullptr)
    {
        queue.push(curr->m_value); // add value to queue to print out path.
        if (curr->m_value == value)
        {
            std::cout << "\nPath to node: ";
            while(!queue.empty()) // print path to value
            {
                std::cout << '(' << queue.front() << ")->";
                queue.pop();
            }
            std::cout << "END\n";
            return true;
        }

        if (value < curr->m_value)
            curr = curr->m_leftChild;
        else
            curr = curr->m_rightChild;
    }
    return false;
}

template <typename T>
void RBTree<T>::print(){
    if (isEmpty())
        throw std::runtime_error("\nTree is empty\n");

    std::cout << "\nPrinting tree inorder (left->root->right):\n\n";
    displayInorderHelper(m_root);
}




template <typename T>
void RBTree<T>::printVerticalSum() {
    if (isEmpty())
        throw std::runtime_error("\nTree is empty\n");

    std::map<int, T> dictionary;
    printVerticalSumHelper(dictionary, m_root, 0);

    std::cout << "\nvertical line sums starting from left-most column (FORMAT-> Column(n): sum)\n\n";
    for (std::pair<int, T> pair: dictionary) {
        if (pair.first == 0)
        {
            std::cout << "ROOT COLUMN (0): " << pair.second << ", ";
            continue;
        }
        std::cout << "Column(" << pair.first << "): " << pair.second << ", ";
    }

}




////////////////////////////////// MAIN FUNCTION //////////////////////////////////




int main() {

    RBTree<int> tree;
    while (true){
        std::cout << "\n\nPlease choose an action to continue:\n"
                     "1. Insert value\n"
                     "2. Display height\n"
                     "3. Display uncle of value\n"
                     "4. Check if subtree is balanced\n"
                     "5. Search for value\n"
                     "6. Print tree\n"
                     "7. Print vertical sum\n"
                     "8. Exit\n"
                     "Choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "How many values do you want to insert\n"
                             "values: ";
                int valuesToInsert;
                std::cin >> valuesToInsert;

                for (int i = 0; i < valuesToInsert; ++i) {
                    int value;
                    std::cout << "Value " << i + 1 << ": ";
                    std::cin >> value;
                    try{tree.insert(value);}
                    catch (std::exception &exception){
                        std::cout << exception.what() << "Please re-enter value.\n";
                        i--;
                    }
                }
                break;
            }

            case 2: {
                std::cout << "\nTree Height is: " << tree.getHeight() << '\n';
                break;
            }
            case 3: {
                std::cout << "Enter the value of the node you want to find its uncle\n"
                             "value: ";
                int value;
                std::cin >> value;

                try {
                    Node<int> *nodeptr = tree.uncle(value);
                    std::cout << "\nUncle Node is:\n" << *nodeptr;
                }
                catch (std::exception &exception) {
                    std::cout << exception.what();
                }
                break;
            }

            case 4: {
                std::cout << "Enter the value of the node whose subtree you want to check\n"
                             "value: ";
                int value;
                std::cin >> value;

                try {
                    if (tree.isBalanced(value))
                        std::cout << "\nTree/Subtree with root " << value <<" is balanced.\n";
                    else
                        std::cout << "\nTree/Subtree with root " << value <<" is NOT balanced.\n";
                }
                catch (const std::exception &exception) {
                    std::cout << exception.what();
                }
                break;
            }

            case 5: {
                std::cout << "Enter the value of the node you want to find\n"
                             "value: ";
                int value;
                std::cin >> value;

                try {
                    if (!tree.search(value))
                        std::cout << "\nValue " << value << " not found\n";
                }
                catch (std::exception &exception) {
                    std::cout << exception.what();
                }
                break;
            }

            case 6: {
                try {
                    tree.print();
                }
                catch (std::exception &exception) {
                    std::cout << exception.what();
                }
                break;
            }
            case 7:{
                try{ tree.printVerticalSum(); }
                catch (std::exception &exception) {
                    std::cout << exception.what();
                }
                break;
            }

            case 8: {
                std::cout << "You've exited the program, bye :)";
                exit(EXIT_SUCCESS);
            }

            default:
                std::cout << "\nInvalid choice, please try again.";
        }
    }
}

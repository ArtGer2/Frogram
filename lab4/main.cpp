
#include <fstream>
#include <string>
#include <iostream>
#include <vector>



using namespace std;
string buf;
enum Notation {
    Prefix,
    Infix,
    Postfix,
};

class Node {
public:
    int _value;
    Node* left;
    Node* right;
    Node* parent;


    Node(int value,Node* par) {
        _value = value;
        left = NULL;
        right = NULL;
        parent = par;
    } Node() :_value(0), left(NULL), right(NULL), parent(NULL) {
    }

    void SetLeft(Node* ptr) {
        left = ptr;
    }

    void SetRight(Node* ptr) {
        right = ptr;
    }

    void SetParent(Node* ptr) {
        parent = ptr;
    }

    void SetValue(int iValue) {
        _value = iValue;
    }

    int GetValue() {
        return _value;
    }

    Node* GetLeft() {
        return left;
    }

    Node* GetRight() {
        return right;
    }

    Node* GetParent() {
        return parent;
    }

    void SetLowParent(Node* node, Node* lowerNode) {
        lowerNode->SetParent(node);
    }

};

class Tree {
private:
    Node* head;

    int GetMin(Node* root) {
        if (root->GetLeft() == NULL)return root->GetValue();
        GetMin(root->GetLeft());
    }

    int GetMax(Node* root) {
        if (root->GetRight() == NULL)return root->GetValue();
        GetMin(root->GetRight());
    }

    void preorder(Node* n) {
        if (n != nullptr) {
            std::cout << n->GetValue() << " ";
            preorder(n->GetLeft());
            preorder(n->GetRight());
        }
    }
    void preorderChar(Node* n) {
        if (n != nullptr) {
            std::cout << char(n->GetValue());
            preorderChar(n->GetLeft());
            preorderChar(n->GetRight());
        }
    }

    void inorder(Node* n) {
        if (n != nullptr) {
            inorder(n->GetLeft());

            std::cout << n->GetValue() << " ";

            inorder(n->GetRight());
        }
    }
    void inorderChar(Node* n) {
        if (n != nullptr) {
            inorderChar(n->GetLeft());

            std::cout << char(n->GetValue());

            inorderChar(n->GetRight());
        }
    }

    void postorder(Node* n) {
        if (n != nullptr) {
            postorder(n->GetRight());
            std::cout << n->GetValue() << " ";
            postorder(n->GetLeft());
        }
    }
    void postorderChar(Node* n) {
        if (n != nullptr) {
            postorderChar(n->GetRight());
            std::cout << char(n->GetValue());
            postorderChar(n->GetLeft());
        }
    }

    void printLevel(Node* n, int level) {
        if (n == nullptr)
            return;
        else if (level == 1)
            std::cout << n->GetValue() << " ";
        else if (level > 1) {
            printLevel(n->GetLeft(), level - 1);
            printLevel(n->GetRight(), level - 1);
        }
    }

    void getLevelCount(Node* n, int count, int& max_count) const {
        if (n == nullptr)
            max_count = (max_count > count) ? max_count : count;
        else {
            count++;
            getLevelCount(n->GetLeft(), count, max_count);
            getLevelCount(n->GetRight(), count, max_count);
        }
    }

    int levels() const {
        int ans = INT_MIN;
        getLevelCount(head, 0, ans);
        return ans;
    }



public:

    Tree() :head(NULL) {
    } Tree(int value) {
        Node* node = new Node(value,NULL);
        head = node;
    }

    Tree(Node* node) {
        head = node;
    }

    Node* GetHead() {
        return this->head;
    }

    bool Add(Node* node, int value) {
        if (head == NULL) {
            Node* node = new Node(value,NULL);
            head = node;
            return true;
        }
        if (value >= node->GetValue()) {
            if (node->GetRight() != NULL)
                return Add(node->GetRight(), value);
            else {
                Node* newNode = new Node(value,NULL);
                node->SetRight(newNode);
                node->SetLowParent(node, newNode);
                return true;
            }
        }
        else {
            if (node->GetLeft() != NULL)
                Add(node->GetLeft(), value);
            else {
                Node* newNode = new Node(value,NULL);
                node->SetLeft(newNode);
                node->SetLowParent(node, newNode);
                return true;
            }
        }
    }

    bool Add(int value) {
        if (this->search(value))return false;

        if (head == NULL) {
            Node* node = new Node(value,NULL);
            head = node;
            return true;
        }
        if (value >= head->GetValue()) {
            if (head->GetRight() != NULL)
                return Add(head->GetRight(), value);
            else {
                Node* newNode = new Node(value,NULL);
                head->SetRight(newNode);
                head->SetLowParent(head, newNode);
                return true;
            }
        }
        else {
            if (head->GetLeft() != NULL)
                return Add(head->GetLeft(), value);
            else {
                Node* newNode = new Node(value,NULL);
                head->SetLeft(newNode);
                head->SetLowParent(head, newNode);
                return true;
            }
        }
    }

    Node* search(int value, Node* node) {

        while (node != NULL) {
            if (value == node->GetValue()) {
                return node;
            }
            else {
                if (value <= node->GetValue()) return search(value, node->GetLeft());
                else return search(value, node->GetRight());
            }
        }
        return NULL;
    }

    Node* search(int value) {
        while (head != NULL) {
            if (value == head->GetValue()) {
                return head;
            }
            else {
                if (value <= head->GetValue()) return search(value, head->GetLeft());
                else return search(value, head->GetRight());
            }
        }
        return NULL;
    }

    Node* RemoveNode(Node* root, int x)
    {
        Node* node = new Node;
        if (root == NULL)
            return NULL;
        if (x == root->GetValue()) {
            if (root->GetLeft() == NULL) {
                node = root->GetRight();
                delete root;
                return node;
            }
            node = root->GetLeft();
            while (node->GetRight()) {
                node = node->GetRight();
            }
            node->SetRight(root->GetRight());
            head = root->GetLeft();
            delete root;
            return NULL;
        }
        if (x < root->GetValue())
            root->SetLeft(RemoveNode(root->GetLeft(), x));
        else
            root->SetRight(RemoveNode(root->GetRight(), x));
        return root;
    }

    int GetMin() {
        if (head->GetLeft() == NULL)return head->GetValue();
        GetMin(head->GetLeft());
    }

    int GetMax() {
        if (head->GetRight() == NULL)return head->GetValue();
        GetMax(head->GetRight());
    }

    int GetNext(int n) {

        Node* node = search(n);
        if (!node)return 0;

        if (node->GetRight() != NULL) return GetMin(node->GetRight());
        node = node->GetParent();
        while (node != head && node->GetValue() <= n) { node = node->GetParent(); }
        if (node->GetValue() > n) return node->GetValue();
        else return NULL;

    }

    int GetPrev(int n) {

        Node* node = search(n);
        if (!node)return 0;

        if (node->GetLeft() != NULL) return GetMax(node->GetLeft());
        node = node->GetParent();
        while (node != head && node->GetValue() >= n) { node = node->GetParent(); }
        if (node->GetValue() < n) return node->GetValue();
        else return NULL;

    }

    void inorderPrint() {
        inorder(head);
        std::cout << "\n";
    }

    void preorderPrint() {
        preorder(head);
        std::cout << "\n";
    }

    void postorderPrint() {
        postorder(head);
        std::cout << "\n";
    }

    void inorderPrintChar() {
        inorderChar(head);
        std::cout << "\n";
    }

    void preorderPrintChar() {
        preorderChar(head);
        std::cout << "\n";
    }

    void postorderPrintChar() {
        postorderChar(head);
        std::cout << "\n";
    }

    void width() {
        int levelsCount = this->levels();
        for (int i = 1; i <= levelsCount; ++i) {
            printLevel(head, i);
            std::cout << " ";
        }
    }

    void bfsPrint() {
        int levelsCount = this->levels();
        for (int i = 1; i <= levelsCount; ++i) {
            printLevel(head, i);
            std::cout << " \n";
        }
    }

    bool is_operation(char operand) {
        return ((operand == '*') || (operand == '+') || (operand == '-') || (operand == '/'));
    }

    void insert(char symbol){
        auto iter = head;
        auto newNode= new Node(int(symbol),iter);

        while (true) {
            if (is_operation(iter->_value)) {
                if (iter->left == nullptr) {
                    iter->left = new Node(int( symbol), iter);
                    return;
                }
                else if (is_operation(iter->left->_value)) {
                    iter = iter->left;
                    continue;
                }
                else if (iter->right == nullptr) {
                    iter->right = new Node(int(symbol), iter);
                    return;
                }
                else if (is_operation(iter->right->_value)) {
                    iter = iter->right;
                    continue;
                }
                else {
                    if (iter->parent->right == nullptr) {
                        iter->parent->right = newNode;
                        return;
                    }
                    else {
                        iter = iter->parent->right;
                    }
                }
            }
            else {
                if (iter->parent->right == nullptr) {
                    iter->parent->right = newNode;
                    return;
                }
                else {
                    iter = iter->parent->right;
                }
            }
        }
    }
    string reverse(string const& s)
    {
        string rev;
        for (int i = s.size() - 1; i >= 0; i--) {
            rev = rev.append(1, s[i]);
        };

        return rev;
    }
    void MathExample(string str, Notation n) {
            if (n == Prefix) {
                head = new Node(int(str[0]), NULL);
                for (int i = 1; i < str.size(); ++i) {
                    insert(str[i]);
                }
                cout << "Prefix " << str << endl;
                cout << "Postfix " << reverse(str) << endl;
            }

            else if (n == Postfix) {
                head = new Node(int(str[str.size()-1]), NULL);
                for (int i = str.size() - 2; i >= 0; --i) {
                    insert(str[i]);
                }
                cout << "Prefix " << reverse(str) << endl;
                cout << "Postfix " << str << endl;

            }
            cout << "Infix ";
            inorderPrintChar();
    }
};

void PrintTree(Node const* node, string const& prefix = " ", bool root = true, bool last = true) {
    cout << prefix << (root ? "" : (last ? "\\-" : "|-")) << '('<<(node ? buf = char(node->_value) : "")<<')' << endl;
    if (!node || (!node->right && !node->left))
        return;
    vector<Node*> v{ node->right, node->left };
    for (size_t i = 0; i < v.size(); ++i)
        PrintTree(v[i], prefix + (root ? "" : (last ? "  " : "| ")), false, i + 1 >= v.size());
}


int main() {

    Tree tree;
    Tree math1;
    Tree math2;
    tree.Add(8); tree.Add(4); tree.Add(12); tree.Add(2); tree.Add(5); tree.Add(9); tree.Add(14); tree.Add(3); tree.Add(7); tree.Add(10);
    tree.bfsPrint();
    cout << "Max" << endl;
    cout<< tree.GetMax()<< endl;
    cout << "Min" << endl;
    cout << tree.GetMin() << endl;
    cout <<"preorder"<< endl;
    tree.preorderPrint();
    cout <<"inorder"<< endl;
    tree.inorderPrint();
    cout <<"postorder"<< endl;
    tree.postorderPrint();
    cout << "width" << endl;
    tree.width();
    cout << endl;

    cout << endl<< "Math Example 1 :" << endl;
    math1.MathExample("-+/ABC*DE",Prefix);
    cout << "Tree:" << endl;
    PrintTree(math1.GetHead());

    cout <<endl<< "Math Example 2 :" << endl;
    math2.MathExample("KCDE**AB---", Postfix);
    cout << "Tree:" << endl;
    PrintTree(math2.GetHead());

    return 0;
}

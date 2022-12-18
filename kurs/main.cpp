
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;
string buf;
enum Notation {
    Prefix,
    Infix,
    Suffix
};
class Node {
public:
    int _value;
    Node* left;
    Node* right;
    Node* parent;


    Node(int value, Node* par) {
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

};

class Tree {
public:
    Node* head;

    Node* GetHead() {
        return this->head;
    }

    bool is_operation(char operand) {
        return ((operand == '*') || (operand == '+') || (operand == '-') || (operand == '/') || (operand == '^'));
    }

    void insert(int symbol) {
        auto iter = head;
        auto newNode = new Node(int(symbol), iter);

        while (true) {
            if (is_operation(iter->_value)) {
                if (iter->left == nullptr) {
                    iter->left = new Node(int(symbol), iter);
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
        string buffer;
        if (n == Prefix) {
            head = new Node(int(str[0]), NULL);
            for (int i = 2; i < str.size(); ++i) {
                if (!is_operation(str[i])) {
                    if (str[i] == ' ') {
                        insert(stoi(buffer)+100);
                        buffer.clear();
                    }
                    else buffer.push_back(str[i]);
                }
                else {
                    insert(int(str[i]));
                    i++;
                }

            }
            insert(stoi(buffer)+100);
            buffer.clear();
        }

        else if (n == Suffix) {
            head = new Node(int(str[str.size() - 1]), NULL);
            for (int i = str.size() - 3; i >= 0; --i) {
                if (!is_operation(str[i])) {
                    if (str[i] == ' ') {
                        insert(stoi(reverse(buffer))+100);
                        buffer.clear();
                    }
                    else buffer.push_back(str[i]);
                }
                else {
                    insert(int(str[i]));
                    i--;
                }
            }
            insert(stoi(reverse(buffer))+100);
            buffer.clear();
        }

        else if (n == Infix) {
            string final;
            InfixReader(str, final);
            MathExample(final.erase(final.size()-1, 1), Prefix);
        }

    }
    void InfixReader(string expr, string& fin) {
        string expr1;
        string expr2;
        char final;
        bool flag = 0;
        int k = 0;

        for (int i = 0; i < expr.size(); i++) {
            if (expr[i] == '+' || expr[i] == '-') {
                fin.push_back(expr[i]);
                fin.push_back(' ');
                for (int j = 0; j < i - 1; j++) {
                    expr1.push_back(expr[j]);
                }
                for (int j = i + 2; j < expr.size(); j++) {
                    expr2.push_back(expr[j]);
                }
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            for (int i = 0; i < expr.size(); i++) {
                if (expr[i] == '*' || expr[i] == '/') {
                    fin.push_back(expr[i]);
                    fin.push_back(' ');
                    for (int j = 0; j < i - 1; j++) {
                        expr1.push_back(expr[j]);
                    }
                    for (int j = i + 2; j < expr.size(); j++) {
                        expr2.push_back(expr[j]);
                    }
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0) {
            for (int i = 0; i < expr.size(); i++) {
                if (expr[i] == '^') {
                    fin.push_back(expr[i]);
                    fin.push_back(' ');
                    for (int j = 0; j < i - 1; j++) {
                        expr1.push_back(expr[j]);
                    }
                    for (int j = i + 2; j < expr.size(); j++) {
                        expr2.push_back(expr[j]);
                    }
                    flag = 1;
                    break;
                }
            }
        }
        if (flag == 0) {
            for (int i = 0; i < expr.size();i++) {
                fin.push_back(expr[i]);
            }
            fin.push_back(' ');
        }
        if (expr1.size() != 0 || expr2.size() != 0) {
            InfixReader(expr1, fin);
            InfixReader(expr2, fin);

        }
    }
    int MathTree(Node* cur) {
        int result;
        if (is_operation(cur->_value)) {
            if (cur->_value == '+') {
                result = MathTree(cur->left) + MathTree(cur->right);
            }
            if (cur->_value == '-') {
                result = MathTree(cur->left) - MathTree(cur->right);
            }
            if (cur->_value == '/') {
                result = MathTree(cur->left) / MathTree(cur->right);
            }
            if (cur->_value == '*') {
                result = MathTree(cur->left) * MathTree(cur->right);
            }
            if (cur->_value == '^') {
                result = pow(MathTree(cur->left), MathTree(cur->right));
            }
            return result;
        }
        else { return int(cur->_value)-100; }
    }
};


void main() {
    string expr;
    Tree tree;
    char n;

    while (true) {
        cout << "Write P for prefix, I for Infix and S for Suffix (Postfix) notation: " << endl;
        cin >> n;
        if (n == 'P' || n == 'I' || n == 'S')break;
        else cout << "Wrong notation, try again" << endl;
    }
    map<char, Notation> notations = { {'S', Suffix}, {'I', Infix}, {'P', Prefix} };
    Notation notation = notations[n];

    while (1) {
        try {
            cout << "Enter an expression" << endl;
            getline(cin, expr);
            tree.MathExample(expr, notation);
            cout << "Answer: " << endl;
            cout << tree.MathTree(tree.head) << endl;
            break;
        }
        catch (...) {
            cout << "Invalid expression" << endl;
        }
    }

}



#pragma once

#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;



class Wordlist : public Wordlist_base
{
 
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height;
    };

    Node *root = nullptr;

    // HELPER PRIVATE RECURSIVE FUNCTIONS

    void delete_tree(Node *n)
    { // used in the destructor
        if (n == nullptr)
        {
            return;
        }
        delete_tree(n->left);
        delete_tree(n->right);
        delete n;
    }

    int height(Node *n)
    { // used to calculate balance of each node when inserting
        if (n == nullptr)
        {
            return 0;
        }
        return n->height;
    }

    Node *right_rotation(Node *z)
    {                       // if left subtree is higher than the right subtree
        Node *y = z->left;  // save y as the left child of z
        z->left = y->right; // set the left child of z to be the right child of y
        y->right = z;       // rotate z to be the right child of y, balancing the height differences
        // update the heights
        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    Node *left_rotation(Node *z)
    {                       // if right subtree is higher then the left subtree
        Node *y = z->right; // save y as the right child of z
        z->right = y->left; // set the right child of z to be the left child of y, balancing the height difference 
        y->left = z;        // rotate z to be the left child of y
        // update the heights
        z->height = 1 + max(height(z->left), height(z->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    Node *insert(Node *z, const string &w)
    {
        if (z == nullptr)
        {
            Node *new_node = new Node{w, 1, nullptr, nullptr, 1}; // height of new leaf is 1
            return new_node;
        }
        // preform regular BST insertion
        if (w < z->word)
        {
            z->left = insert(z->left, w);
        }
        else if (w > z->word)
        {
            z->right = insert(z->right, w);
        }
        // once the node is inserted, update the height of the current node z
        z->height = 1 + max(height(z->left), height(z->right));
        // compute the balance factor
        int bal = height(z->left) - height(z->right);
        if (bal > 1)
        { // left subtree is higher then right subtree
            if (w < z->left->word)
            {
                // case 1: if y is the left child of z and x is the left child of y
                return right_rotation(z); // regular right rotation
            }
            else
            {
                // case 2: y is the left child of z and x is right child of y
                //  need to left_rotate(y) first so it is the same as case 1

                z->left = left_rotation(z->left);
                return right_rotation(z); // regular right rotation
            }
        }
        else if (bal < -1)
        {

            if (w > z->right->word)
            {
                // case 1: if y is the right child of z and x is the right child of y
                return left_rotation(z); // regular left rotation
            }
            else
            {
                // case 2: if y is the right child of z and x is the left child of y
                // need to right_rotate(y) first so it is the same as case 1

                z->right = right_rotation(z->right);
                return left_rotation(z); // regular left rotation
            }
        }
        return z;
    }

    bool is_sorted_rec(Node *n) const
    { // recursively checks if the tree is sorted
        if (n == nullptr)
        {
            return true;
        }
        // if word to the left of current node is greater BST rule is violated
        if (n->left != nullptr && n->word < n->left->word)
        {
            return false;
        }
        // if word to the right of current node is smaller BST rule is violated
        if (n->right != nullptr && n->word > n->right->word)
        {
            return false;
        }
        // check right and left subtrees
        bool is_sorted_left = is_sorted_rec(n->left);
        bool is_sorted_right = is_sorted_rec(n->right);
        // if any subtree is not a BST return false
        if (is_sorted_left == false || is_sorted_right == false)
        {
            return false;
        }
        // if control reaches this point, BST conditions satisfied
        return true;
    }
    // recursivley searchs the tree until the word is found or until it has searched the entire tree
    Node *find_word_rec(Node *n, const string &w) const
    {
        if (n == nullptr)
        { // implicit base case
            return nullptr;
        }
        if (n->word == w)
        { // explicit base case
            return n;
        }
        else if (n->word > w)
        {
            return find_word_rec(n->left, w);
        }
        else
        {
            return find_word_rec(n->right, w);
        }
    }
    // recursively traverses the tree and sums the counts of each node
    int total_words_rec(Node *n) const
    {
        if (n == nullptr)
        {
            return 0;
        }
        int count_left = total_words_rec(n->left);
        int count_right = total_words_rec(n->right);
        // add up the count of each node
        return n->count + count_left + count_right;
    }

    // recursively traverses the tree and sums 1 for each node
    // same as total_words_rec expect we are not interested in the count
    // of each node, so we add one for each node to count the toal number of different words
    int total_diff_words_rec(Node *n) const
    {
        if (n == nullptr)
        {
            return 0;
        }
        int count_left = total_diff_words_rec(n->left);
        int count_right = total_diff_words_rec(n->right);
        // add one for each node in the tree
        return 1 + count_left + count_right;
    }

    // recursively travereses the tree and returns the count of word w
    int get_count_rec(Node *n, const string &w) const
    {
        if (n == nullptr)
        { // returns 0 if w is not in the tree
            return 0;
        }
        if (n->word == w)
        {
            return n->count;
        }
        else if (n->word > w)
        {
            return get_count_rec(n->left, w);
        }
        else
        {
            return get_count_rec(n->right, w);
        }
    }
    void print_in_order_rec(Node *n, int &index) const
    {
        if (n == nullptr)
        {
            return;
        }
        // print left child first
        print_in_order_rec(n->left, index);

        cout << index++ << ". {\"" << n->word << "\", " << n->count << "}\n"; // print parent second

        // print right child last
        print_in_order_rec(n->right, index);
    }
    // recursivley traverses the tree and returns the node with the highest count
    Node *find_most_freq(Node *n) const
    {
        if (n == nullptr)
        {
            return nullptr;
        }
        Node *most_freq = n;
        // check both subtrees
        Node *most_freq_left = find_most_freq(n->left);
        Node *most_freq_right = find_most_freq(n->right);
        // compare the values and make sure the result of the recursive call is not nullptr
        if (most_freq_left != nullptr && most_freq_left->count > most_freq->count)
        {
            // if the node with the highest count in the left subtree has a higher count than
            // n, set the most_freq node to that node in the left subtree
            most_freq = most_freq_left;
        }
        if (most_freq_right != nullptr && most_freq_right->count > most_freq->count)
        {
            // if the node with the highest count in the right subtree has a higher count than
            // n, set the most_freq node to that node in the right subtree
            most_freq = most_freq_right;
        }
        return most_freq; // returns node with highest count

        /*NOTE: in this implementation, if there is a tie for most freq nodes, it will consider
         the one that comes first alphabetically, since it only updates most_freq if the count of
        most_freq_left or most_freq_left is striclty larger than the count of the current node */
    }

public:

    // implementation of the public methods

    Wordlist() {} // default constructor

    Wordlist(const std::string &filename)
    {
        ifstream file(filename);
        string word;

        if (file.is_open())
        {
            // read from the file
            while (file >> word)
            {
                add_word(word);
            }
            file.close();
        }
        else
        {
            // return an error message if file cannot be opened
            cout << "Unable to open file: " << filename << endl;
        }
    }

    ~Wordlist()
    {
        delete_tree(root);
    }

    void add_word(const string &w)
    {
        if (contains(w))
        {                                    // if word is already in the list
            find_word_rec(root, w)->count++; // increment the count
            return;
        }
        root = insert(root, w); // if word is not in the list, insert a new node into the AVL tree
    }

    bool is_sorted() const
    {
        if (root == nullptr)
        {
            return true;
        }
        return is_sorted_rec(root);
    }

    string most_frequent() const
    {
        if (root == nullptr)
        {
            return " "; //  -->  is this fine?
        }
        Node *most_freq = find_most_freq(root);
        return most_freq->word + " " + to_string(most_freq->count);
    }

    int count_singletons(Node *n) const
    { // helper recursive function for num_singletons()
        if (n == nullptr)
        {
            return 0;
        }
        int count_left = count_singletons(n->left);
        int count_right = count_singletons(n->right);
        // n->count==1 returns 0 or 1, adding 1 for each singleton gives the total count
        return (n->count == 1) + count_left + count_right;
    }

    int num_singletons() const
    {
        return count_singletons(root);
    }

    int total_words() const
    {
        return total_words_rec(root);
    }

    int num_different_words() const
    {
        return total_diff_words_rec(root);
    }

    int get_count(const string &w) const
    {
        return get_count_rec(root, w);
    }

    void print_words() const
    {
        int ind = 1;
        print_in_order_rec(root, ind);
    }

}; // class Wordlist


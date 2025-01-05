#pragma once
#include <vector>
#include <string>
#include <stdexcept>

class Trie {
private:
    struct Node {
        char symbol;
        int value;
        bool isEndOfWord;
        Node* children[26];

        Node(char c) : symbol(c), value(-1), isEndOfWord(false) {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }

        ~Node() {
            for (int i = 0; i < 26; i++) {
                delete children[i];
            }
        }
    };

    Node* root;

public:
    Trie() : root(new Node('\0')) {}
    ~Trie() { delete root; }

    void insert(const std::string& word, int value) {
        if (value < 0) throw std::invalid_argument("Value must be non-negative");

        Node* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                current->children[index] = new Node(c);
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
        current->value = value;
    }
    bool contains(const std::string& word) const {
        Node* current = root;
        for (char c : word) {
            int index = c - 'a';
            if (!current->children[index]) {
                return false;
            }
            current = current->children[index];
        }
        return current->isEndOfWord;  // важно е да проверим дали завършва дума тук
    }

    int valueOfWord(const std::string& word) const {
        if (!contains(word)) {
            throw std::invalid_argument("Word not found in trie");
        }
        const Node* current = root;  // ???const
        for (char c : word) {
            int index = c - 'a';
            current = current->children[index];
        }
        return current->value;
    }
};
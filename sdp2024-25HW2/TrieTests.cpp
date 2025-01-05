#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Trie.hpp"
using namespace std;


void testTrie() {
    // ���� 1: ��������� �� ����� � ������ �� ����
    cout << "Test 1: Reading from file and creating trie" << endl;

    ifstream file("words.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Trie trie;
    string word;
    int value;

    cout << "Reading words:" << endl;
    while (file >> word >> value) {
        cout << "Adding word: " << word << " with value: " << value << endl;
        trie.insert(word, value);
    }
    cout << "------------------------" << endl;

    // ���� 2: ���� �� �������� �� ���� � ����������� ��������
    cout << "\nTest 2: Trying to insert word with negative value" << endl;
    try {
        trie.insert("test", -5);
        cout << "This should not be printed!" << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    cout << "------------------------" << endl;

    // ���� 3: ��������� �� ����� � ������ �� �������
    cout << "\nTest 3: Creating trie with example words" << endl;
    Trie exampleTrie;
    exampleTrie.insert("bear", 5);
    exampleTrie.insert("bell", 3);
    exampleTrie.insert("bid", 4);
    exampleTrie.insert("bull", 6);
    exampleTrie.insert("buy", 2);
    exampleTrie.insert("sell", 7);
    exampleTrie.insert("stock", 8);
    exampleTrie.insert("stop", 1);
    cout << "Example words inserted" << endl;
    cout << "------------------------" << endl;

    // ���� 4: �������� �� ���������� �� ����
    cout << "\nTest 4: Testing contains functionality" << endl;
    cout << "Word 'bear' is in trie: " << (exampleTrie.contains("bear") ? "yes" : "no") << endl;
    cout << "Word 'bell' is in trie: " << (exampleTrie.contains("bell") ? "yes" : "no") << endl;
    cout << "Word 'cat' is in trie: " << (exampleTrie.contains("cat") ? "yes" : "no") << endl;
    cout << "Word 'sto' is in trie: " << (exampleTrie.contains("sto") ? "yes" : "no") << endl; // ������� �� stop/stock
    cout << "------------------------" << endl;


    // ���� 5: �������� �� valueOfWord ������
    cout << "\nTest 5: Testing value retrieval" << endl;

    try {
        cout << "Value of 'bear': " << exampleTrie.valueOfWord("bear") << endl;    // ������ �� � 5
    }
    catch (const invalid_argument& e) {
        cout << "Unexpected error for 'bear': " << e.what() << endl;
    }

    try {
        cout << "Value of 'sto': " << exampleTrie.valueOfWord("sto") << endl;      // ������ �� ������ ������
    }
    catch (const invalid_argument& e) {
        cout << "Caught expected error for 'sto': " << e.what() << endl;
    }

    try {
        cout << "Value of 'cat': " << exampleTrie.valueOfWord("cat") << endl;      // ������ �� ������ ������
    }
    catch (const invalid_argument& e) {
        cout << "Caught expected error for 'cat': " << e.what() << endl;
    }

    cout << "------------------------" << endl;


    // ���� 7: �������� �� ������ �������� ��������
    cout << "\nTest 7: Testing all prefixes" << endl;
    vector<string> prefixes = { "b", "be", "bea", "bu", "s", "st", "sto" };

    cout << "Checking prefixes:" << endl;
    for (const string& prefix : prefixes) {
        cout << prefix << ": ";
        cout << "exists=" << (exampleTrie.contains(prefix) ? "yes" : "no");
        try {
            cout << ", value=" << exampleTrie.valueOfWord(prefix);
        }
        catch (const invalid_argument& e) {
            cout << " (Expected error: not a complete word)";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;

    // ���� 8: �������� �� �������� �������� �� ����
    cout << "\nTest 8: Special cases (lowercase only)" << endl;
    vector<string> cases = {
        "",             // ������ ������
        "stocks",       // ��-����� ���� �� ������������
        "sto",          // ������� �� ��� ���� (stock � stop)
        "bee",          // ������� ���� ������������ �� ���������� ��������
        "a",            // �������� �����
        "z"            // �����, ����� �� ������� � ���� ���� ����
    };

    cout << "Checking special cases:" << endl;
    for (const string& word : cases) {
        cout << "\"" << word << "\": ";
        cout << "exists=" << (exampleTrie.contains(word) ? "yes" : "no");
        try {
            cout << ", value=" << exampleTrie.valueOfWord(word);
        }
        catch (const invalid_argument& e) {
            cout << " (Error: " << e.what() << ")";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
}


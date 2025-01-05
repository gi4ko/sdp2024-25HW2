#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Trie.hpp"
using namespace std;


void testTrie() {
    // Тест 1: Създаване на дърво и четене от файл
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

    // Тест 2: Опит за вмъкване на дума с отрицателна стойност
    cout << "\nTest 2: Trying to insert word with negative value" << endl;
    try {
        trie.insert("test", -5);
        cout << "This should not be printed!" << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    cout << "------------------------" << endl;

    // Тест 3: Създаване на дърво с думите от примера
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

    // Тест 4: Проверка за съдържание на думи
    cout << "\nTest 4: Testing contains functionality" << endl;
    cout << "Word 'bear' is in trie: " << (exampleTrie.contains("bear") ? "yes" : "no") << endl;
    cout << "Word 'bell' is in trie: " << (exampleTrie.contains("bell") ? "yes" : "no") << endl;
    cout << "Word 'cat' is in trie: " << (exampleTrie.contains("cat") ? "yes" : "no") << endl;
    cout << "Word 'sto' is in trie: " << (exampleTrie.contains("sto") ? "yes" : "no") << endl; // префикс на stop/stock
    cout << "------------------------" << endl;


    // Тест 5: Проверка на valueOfWord метода
    cout << "\nTest 5: Testing value retrieval" << endl;

    try {
        cout << "Value of 'bear': " << exampleTrie.valueOfWord("bear") << endl;    // трябва да е 5
    }
    catch (const invalid_argument& e) {
        cout << "Unexpected error for 'bear': " << e.what() << endl;
    }

    try {
        cout << "Value of 'sto': " << exampleTrie.valueOfWord("sto") << endl;      // трябва да хвърли грешка
    }
    catch (const invalid_argument& e) {
        cout << "Caught expected error for 'sto': " << e.what() << endl;
    }

    try {
        cout << "Value of 'cat': " << exampleTrie.valueOfWord("cat") << endl;      // трябва да хвърли грешка
    }
    catch (const invalid_argument& e) {
        cout << "Caught expected error for 'cat': " << e.what() << endl;
    }

    cout << "------------------------" << endl;


    // Тест 7: Проверка на всички възможни префикси
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

    // Тест 8: Проверка на различни варианти на думи
    cout << "\nTest 8: Special cases (lowercase only)" << endl;
    vector<string> cases = {
        "",             // празен стринг
        "stocks",       // по-дълга дума от съществуваща
        "sto",          // префикс на две думи (stock и stop)
        "bee",          // започва като съществуваща но продължава различно
        "a",            // единична буква
        "z"            // буква, която не участва в нито една дума
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


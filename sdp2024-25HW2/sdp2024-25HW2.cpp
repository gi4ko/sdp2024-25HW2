#include <iostream>
#include <fstream>
#include "KHeap.hpp"
#include "Trie.hpp"
#include <map>
using namespace std;

//void testHeap();
//void testTrie();
struct WordScore {
    std::string word;
    int score;

    WordScore(const std::string& w, int s) : word(w), score(s) {}

    bool operator<(const WordScore& other) const {
        return score < other.score;
    }
    bool operator<=(const WordScore& other) const {
        return score <= other.score;
    }
};
void findTopWords(const string& filename, const Trie& dictionary, int M) {
    // ����� ������� ����
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Cannot open input file");
    }

    // ����� ���������� �� ����� ����
    map<string, int> wordCount;
    string word;
    while (file >> word) {
        wordCount[word]++;
    }

    if (M > wordCount.size()) {
        throw runtime_error("Cannot extract " + to_string(M) +
            " words from text with " + to_string(wordCount.size()) +
            " unique words!");
    }

    // ��������� ����� � ������ ���� � ������� ������
    vector<WordScore> scores;
    for (const auto& pair : wordCount) {
        int score;
        if (dictionary.contains(pair.first)) {
            score = pair.second * dictionary.valueOfWord(pair.first);
        }
        else {
            score = pair.second;
        }
        scores.push_back(WordScore(pair.first, score));
    }

    // ������ �������� �� ������
    KHeap<WordScore> heap(2);
    heap.heapify(scores);

    // ��������� ������� � ����
    cout << "Top " << M << " words:" << endl;
    for (int i = 0; i < M && !heap.empty(); i++) {
        WordScore ws = heap.extractMin();
        cout << ws.word << " (score: " << ws.score << ")" << endl;
    }
}
int main() {
    //testHeap();
    //testTrie();

    // ��������� ������� �� words.txt
    Trie dictionary;
    ifstream dictFile("words.txt");
    if (!dictFile) {
        cout << "Error opening dictionary file!" << endl;
        return 1;
    }

    string word;
    int value;
    while (dictFile >> word >> value) {
        dictionary.insert(word, value);
    }

    // ����� M �� �����������
    int M;
    cout << "Enter number of words to display (M): ";
    cin >> M;
    if (M < 0) {
        cout << "M must be non-negative!" << endl;
        return 1;
    }

    try {
        findTopWords("text.txt", dictionary, M);
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    //�ODO: ��� � > �� .size na ���������� throw "You cannot extraxt "M"  min words from ".size"  lenght of a text!"
    return 0;
}
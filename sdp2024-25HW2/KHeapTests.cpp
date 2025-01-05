#include <iostream>
#include <string>
#include <iomanip>
#include "KHeap.hpp"
using namespace std;

// Помощна функция за печатане на състоянието на пирамидата
template<typename T>
void printHeapState(const KHeap<T>& heap, const string& message) {
    cout << message << endl;
    cout << "Size: " << heap.size() << endl;
    cout << "Is empty: " << (heap.empty() ? "yes" : "no") << endl;
    if (!heap.empty()) {
        cout << "Min element: " << heap.peekMin() << endl;
    }
    cout << "------------------------" << endl;
}
void testHeap() {
    // Тест 1: Създаване на 3-ична пирамида за integers
    cout << "Test 1: Creating 3-ary heap for integers" << endl;
    KHeap<int> heap3(3);
    printHeapState(heap3, "Initial state");

    // Тест 2: Вмъкване на елементи
    cout << "\nTest 2: Inserting elements" << endl;
    heap3.insert(5);
    heap3.insert(3);
    heap3.insert(7);
    heap3.insert(1);
    heap3.insert(4);
    heap3.insert(6);
    printHeapState(heap3, "After insertions");

    // Тест 3: Извличане на минималните елементи
    cout << "\nTest 3: Extracting minimum elements" << endl;
    cout << "Extracted: " << heap3.extractMin() << endl;
    cout << "Extracted: " << heap3.extractMin() << endl;
    printHeapState(heap3, "After extractions");

    // Тест 4: Работа с double стойности
    cout << "\nTest 4: Working with doubles" << endl;
    KHeap<double> heapDouble(2); // двоична пирамида
    heapDouble.insert(3.14);
    heapDouble.insert(1.41);
    heapDouble.insert(2.71);
    printHeapState(heapDouble, "Double heap state");

    // Тест 5: Извличане докато пирамидата не стане празна
    cout << "\nTest 5: Extracting until empty" << endl;
    cout << "Extracting elements in order: ";
    while (!heapDouble.empty()) {
        cout << heapDouble.extractMin() << " ";
    }
    cout << endl;
    printHeapState(heapDouble, "After extracting all elements");

    // Тест 6: Обработка на грешки
    cout << "\nTest 6: Error handling" << endl;
    try {
        heapDouble.extractMin(); // опит за извличане от празна пирамида
    }
    catch (const runtime_error& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }

    // Тест 7: Двоична пирамида (k=2)
    cout << "\nTest 7: Binary heap operations" << endl;
    KHeap<int> binaryHeap(2);

    cout << "Inserting elements: 8 3 9 4 1 5" << endl;
    binaryHeap.insert(8);
    binaryHeap.insert(3);
    binaryHeap.insert(9);
    binaryHeap.insert(4);
    binaryHeap.insert(1);
    binaryHeap.insert(5);
    printHeapState(binaryHeap, "After insertions");

    cout << "\nExtracting minimums one by one:" << endl;
    cout << "Extracted: " << binaryHeap.extractMin() << endl;
    printHeapState(binaryHeap, "After first extraction");

    cout << "\nExtracting more:" << endl;
    cout << "Extracted: " << binaryHeap.extractMin() << endl;
    cout << "Extracted: " << binaryHeap.extractMin() << endl;
    printHeapState(binaryHeap, "After more extractions");

    cout << "\nInserting new elements: 2 7" << endl;
    binaryHeap.insert(2);
    binaryHeap.insert(7);
    printHeapState(binaryHeap, "After new insertions");

    cout << "\nExtracting all remaining elements in order: ";
    while (!binaryHeap.empty()) {
        cout << binaryHeap.extractMin() << " ";
    }
    cout << endl;

    // Тест 8: Подред номера при двоична пирамида
    cout << "\nTest 8: Sequential numbers in binary heap" << endl;
    KHeap<int> seqHeap(2);
    cout << "Inserting numbers from 1 to 10 in order" << endl;
    for (int i = 1; i <= 10; i++) {
        seqHeap.insert(i);
    }
    printHeapState(seqHeap, "After inserting 1-10");

    cout << "Extracting all numbers: ";
    while (!seqHeap.empty()) {
        cout << seqHeap.extractMin() << " ";
    }
    cout << endl;

    // Тест 9: Обратен ред при 4-ична пирамида
    cout << "\nTest 9: Reverse sequential numbers in 4-ary heap" << endl;
    KHeap<int> revHeap(4);
    cout << "Inserting numbers from 20 to 10" << endl;
    for (int i = 20; i >= 10; i--) {
        revHeap.insert(i);
    }
    printHeapState(revHeap, "After inserting 20-10");

    cout << "Extracting all numbers: ";
    while (!revHeap.empty()) {
        cout << revHeap.extractMin() << " ";
    }
    cout << endl;

    // Тест 10: Смесица от вмъкване и извличане
    cout << "\nTest 10: Mixed operations with 3-ary heap" << endl;
    KHeap<int> mixHeap(3);
    for (int i = 1; i <= 5; i++) {
        mixHeap.insert(i);
    }
    printHeapState(mixHeap, "After inserting 1-5");

    cout << "First minimum extracted: " << mixHeap.extractMin() << endl;
    cout << "Second minimum extracted: " << mixHeap.extractMin() << endl;

    cout << "Inserting 1 and 2 again" << endl;
    mixHeap.insert(1);
    mixHeap.insert(2);
    printHeapState(mixHeap, "Final state");

    cout << "Final extraction sequence: ";
    while (!mixHeap.empty()) {
        cout << mixHeap.extractMin() << " ";
    }
    cout << endl;


    // Тест 11: Малко K (k=2) с много операции
    cout << "\nTest 11: Small K (k=2) stress test" << endl;
    KHeap<int> smallK(2);

    cout << "Inserting numbers in random order: 7,3,9,1,5,2,8,4,6" << endl;
    int nums[] = { 7,3,9,1,5,2,8,4,6 };
    for (int x : nums) {
        smallK.insert(x);
        cout << "After inserting " << x << ", min is: " << smallK.peekMin() << endl;
    }

    cout << "Extraction sequence: ";
    while (!smallK.empty()) {
        cout << smallK.extractMin() << " ";
    }
    cout << endl;

    // Тест 12: Голямо K (k=5) с екстремни стойности
    cout << "\nTest 12: Large K (k=5) with extreme values" << endl;
    KHeap<int> largeK(5);

    cout << "Inserting alternating large and small numbers" << endl;
    largeK.insert(1000);
    cout << "After 1000, min: " << largeK.peekMin() << endl;
    largeK.insert(1);
    cout << "After 1, min: " << largeK.peekMin() << endl;
    largeK.insert(999);
    cout << "After 999, min: " << largeK.peekMin() << endl;
    largeK.insert(2);
    cout << "After 2, min: " << largeK.peekMin() << endl;
    largeK.insert(998);
    cout << "After 998, min: " << largeK.peekMin() << endl;

    cout << "Extraction sequence: ";
    while (!largeK.empty()) {
        cout << largeK.extractMin() << " ";
    }
    cout << endl;

    // Тест 13: Смесени операции с променливо извличане
    cout << "\nTest 13: Mixed operations with varying extractions" << endl;
    KHeap<int> mixedOps(3);

    cout << "Series of insertions and extractions:" << endl;
    mixedOps.insert(5);
    cout << "Insert 5, min: " << mixedOps.peekMin() << endl;
    mixedOps.insert(3);
    cout << "Insert 3, min: " << mixedOps.peekMin() << endl;
    cout << "Extract: " << mixedOps.extractMin() << endl;
    mixedOps.insert(4);
    cout << "Insert 4, min: " << mixedOps.peekMin() << endl;
    mixedOps.insert(1);
    cout << "Insert 1, min: " << mixedOps.peekMin() << endl;
    cout << "Extract: " << mixedOps.extractMin() << endl;
    cout << "Extract: " << mixedOps.extractMin() << endl;
    mixedOps.insert(2);
    cout << "Insert 2, min: " << mixedOps.peekMin() << endl;

    cout << "Final extraction sequence: ";
    while (!mixedOps.empty()) {
        cout << mixedOps.extractMin() << " ";
    }
    cout << endl;

    // Тест 14: Edge case с K=1 (вырожденный случай)
    cout << "\nTest 14: Edge case with K=1" << endl;
    KHeap<int> degenerateHeap(1);
    for (int i = 5; i > 0; i--) {
        degenerateHeap.insert(i);
        cout << "After inserting " << i << ", min is: " << degenerateHeap.peekMin() << endl;
    }

    cout << "Final sequence: ";
    while (!degenerateHeap.empty()) {
        cout << degenerateHeap.extractMin() << " ";
    }
    cout << endl;

    // Тест 15: Задълбочен тест на K=1 с гранични случаи
    cout << "\nTest 15: Extensive K=1 edge cases" << endl;
    KHeap<int> k1heap(1);

    cout << "Test sequence for K=1:" << endl;

    // Вмъкване и изваждане на единичен елемент
    cout << "Single element test:" << endl;
    k1heap.insert(42);
    cout << "Inserted 42, min is: " << k1heap.peekMin() << endl;
    cout << "Extracted: " << k1heap.extractMin() << endl;
    cout << "Heap empty? " << (k1heap.empty() ? "yes" : "no") << endl;

    // Вмъкване на еднакви елементи
    cout << "\nDuplicate elements test:" << endl;
    k1heap.insert(5);
    k1heap.insert(5);
    k1heap.insert(5);
    cout << "After inserting three 5s, size: " << k1heap.size() << ", min: " << k1heap.peekMin() << endl;
    cout << "Extraction sequence: ";
    while (!k1heap.empty()) {
        cout << k1heap.extractMin() << " ";
    }
    cout << endl;

    // Последователно вмъкване и изваждане
    cout << "\nAlternating insert/extract:" << endl;
    k1heap.insert(3);
    cout << "Insert 3, min: " << k1heap.peekMin() << endl;
    cout << "Extract: " << k1heap.extractMin() << endl;
    k1heap.insert(1);
    cout << "Insert 1, min: " << k1heap.peekMin() << endl;
    cout << "Extract: " << k1heap.extractMin() << endl;
    cout << "Heap empty? " << (k1heap.empty() ? "yes" : "no") << endl;

    // Тест със спадащи стойности
    cout << "\nDescending values test:" << endl;
    for (int i = 10; i > 0; i--) {
        k1heap.insert(i);
        cout << "After inserting " << i << ", min: " << k1heap.peekMin() << endl;
    }

    cout << "Extraction sequence: ";
    while (!k1heap.empty()) {
        cout << k1heap.extractMin() << " ";
    }
    cout << endl;

    // Тест с редуващи се големи и малки числа
    cout << "\nAlternating high-low values test:" << endl;
    int values[] = { 100, 1, 99, 2, 98, 3, 97, 4 };
    for (int x : values) {
        k1heap.insert(x);
        cout << "After inserting " << x << ", min: " << k1heap.peekMin() << endl;
    }

    cout << "Extraction sequence: ";
    while (!k1heap.empty()) {
        cout << k1heap.extractMin() << " ";
    }
    cout << endl;

    // Тест 16: String heap
    cout << "\nTest 16: Testing heap with strings" << endl;
    KHeap<string> strHeap(2);

    cout << "Inserting strings..." << endl;
    strHeap.insert("banana");
    strHeap.insert("apple");
    strHeap.insert("cherry");
    strHeap.insert("date");

    printHeapState(strHeap, "After string insertions");

    cout << "Extraction sequence: ";
    while (!strHeap.empty()) {
        cout << strHeap.extractMin() << " ";
    }
    cout << endl;

    // Тест със специални стрингове
    strHeap.insert("");
    strHeap.insert("a");
    strHeap.insert(" ");
    strHeap.insert("A");

    cout << "Special strings extraction: ";
    while (!strHeap.empty()) {
        cout << "\"" << strHeap.extractMin() << "\" ";
    }
    cout << endl;

    // Тест 17: Float heap
    cout << "\nTest 17: Testing heap with floats" << endl;
    KHeap<float> floatHeap(3);

    floatHeap.insert(3.14f);
    floatHeap.insert(2.71f);
    floatHeap.insert(1.41f);
    floatHeap.insert(1.73f);

    printHeapState(floatHeap, "After float insertions");

    cout << "Extraction sequence: ";
    while (!floatHeap.empty()) {
        cout << fixed << setprecision(2) << floatHeap.extractMin() << " ";
    }
    cout << endl;


    // Тест 18: Heapify за двоична пирамида
    cout << "\nTest 18: Testing heapify with binary heap" << endl;
    vector<int> arr = { 6, 8, 3, 9, 2, 4, 7, 1, 5 };
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    KHeap<int> heapTest(2);
    heapTest.heapify(arr);

    cout << "After heapify: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    cout << "Extraction sequence: ";
    while (!heapTest.empty()) {
        cout << heapTest.extractMin() << " ";
    }
    cout << endl;

    // Тест 19: Heapify с k=3
    cout << "\nTest 19: Testing heapify with k=3" << endl;
    vector<int> arr2 = { 10, 8, 9, 7, 6, 5, 4, 3, 2, 1 };
    cout << "Original array: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    KHeap<int> heapTest2(3);
    heapTest2.heapify(arr2);

    cout << "After heapify: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    cout << "Extraction sequence: ";
    while (!heapTest2.empty()) {
        cout << heapTest2.extractMin() << " ";
    }
    cout << endl;

    

    
}


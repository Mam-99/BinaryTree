#ifndef TEST_H
#define TEST_H

#include<iostream>

#include "avltree.h"

void smallTestForBugFoundInLecture(AVLTree &avl)
{
    // I fixed my bug from the lecture:
    avl.insert(17);
    avl.insert(42);
    avl.insert(1337);
    avl.insert(21);
    avl.show();
    avl.writeDot("testbefore");
    avl.insert(9);
    avl.writeDot("testafter");
}

void bigInsertionTest(AVLTree &avl)
{
    avl.insert(23);
    avl.insert(29);
    avl.insert(84);
    avl.insert(58);
    avl.insert(19);
    avl.insert(81);
    avl.insert(17);
    avl.insert(15);
    avl.insert(36);
    avl.insert(49);
    avl.insert(91);
    avl.insert(26);
    avl.insert(22);
    avl.insert(57);
    avl.insert(33);
    avl.insert(50);
    avl.insert(56);
    avl.insert(85);
    avl.insert(4);
    avl.insert(10);
    avl.insert(63);
    avl.insert(1);
    avl.insert(72);
    avl.insert(48);
    avl.insert(25);
    avl.insert(67);
    avl.insert(75);
    avl.insert(90);
    avl.insert(92);
    avl.insert(37);
    avl.insert(89);
    avl.insert(77);
    avl.writeDot("bigInsertionTest1");
}


void removeTest(AVLTree &avl)
{
    // to be called after bigInsertionTest
    avl.remove(33); // simple leaf node remove
    avl.writeDot("removeTest1"); // should have rebalanced
    avl.remove(26); // simple single child node remove
    avl.writeDot("removeTest2");
    avl.remove(23); // some more difficult removes
    avl.writeDot("removeTest3");
    avl.remove(81);
    avl.writeDot("removeTest4");
    avl.remove(29);
    avl.writeDot("removeTest5");
    avl.remove(80); //removal of non-existent key
    avl.writeDot("removeTest6"); // should be the same
    avl.show();
}

void findTest(AVLTree &avl)
{
    //to be called after removeTest
    string s;

    if (avl.member(80)) cout << "fail: precondition of test";
    if (avl.member(42)) cout << "fail: precondition of test";

    if (!avl.member(17)) cout << "fail: precondition of test";

    avl.insert(80,"something");
    if (avl.find(80,s)) cout << "good: found " << s << endl;
    if (s!="something") cout << "fail: test failed, something not found" << endl;

    if (!avl.find(42,s)) cout << "good: 42 not found" << endl;
    else cout << "fail: precondition of test failed" << endl;

    if (!avl.probe(42,"an answer")) cout << "good: 42 not found, and should be inserted now" << endl;
    else cout << "fail: 42 already there";

    if (avl.probe(42,"something stupid")) cout << "good: 42 already there, nothing should be changed" << endl;
    else cout << "fail: 42 not found, but should be there already" << endl;

    if (avl.find(42,s)) cout << "good: found (" << s << ") " << endl;
    else cout << "fail: 42 not found" << endl;
    if (s!="an answer") cout << "fail: test failed, expected an answer, found" << s << endl;

    avl.set(42,"the answer to the ultimate question of life, the universe, and everything");
    if (avl.find(42,s)) cout << "42 is " << s << endl;

    //avl.clear();
    avl.show();
}



#endif // TEST_H

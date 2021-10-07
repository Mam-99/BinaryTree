#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <iostream>
#include "avltree.h"

using namespace std;
using namespace std::chrono;

void benchmark()
{
    AVLTree avl;
    list<int> l;
    unordered_map<int,string> hash;

    steady_clock::time_point begin;
    steady_clock::time_point end;

    vector<int> sizes {10,100,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000};

    for (int n : sizes)
    {
        // AVL-Tree (make sure to disable terminal output!)
        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            avl.insert(rand()%10000,"");
        }
        end = steady_clock::now();
        cout << "avl-insertions " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            avl.member(rand()%10000);
        }
        end = steady_clock::now();
        cout << "avl-search " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            avl.remove(rand()%10000);
        }
        end = steady_clock::now();
        cout << "avl-remove " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

//        avl.clear();
    }

    for (int n : sizes)
    {
        // linked list (stl implementation)
        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            l.push_front(rand()%10000);
        }
        end = steady_clock::now();
        cout << "list-insertions " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            list<int>::iterator it;
            it = find(l.begin(), l.end(), rand()%10000);
        }
        end = steady_clock::now();
        cout << "list-search " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            list<int>::iterator it;
            it = remove(l.begin(), l.end(), rand()%10000);
        }
        end = steady_clock::now();
        cout << "list-remove " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        l.clear();
    }

    for (int n : sizes)
    {
        // hash (stl implementation)
        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            hash.insert(make_pair(rand()%10000,""));
        }
        end = steady_clock::now();
        cout << "hash-insertions " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            hash.find(rand()%10000);
        }
        end = steady_clock::now();
        cout << "hash-search " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        begin = steady_clock::now();
        for(int i=0; i<n; i++)
        {
            hash.erase(rand()%10000);
        }
        end = steady_clock::now();
        cout << "hash-remove " << n << " iterations, "
             << duration_cast<nanoseconds>(end - begin).count() << " ns" << endl;

        hash.clear();
    }
}

#endif // BENCHMARK_H

// a5_main.cpp

#include "Wordlist.h"

///
// test_read() is a helper function that reads words, one at a time
// Wordlist class, e.g.:
//
//    > make a5_main
//    g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a5_main.cpp   -o a5_main
//   
//    > ./a5_main < tiny_shakespeare.txt
//    Number of different words: 25670
//        Total number of words: 202651
//           Most frequent word: the 5437
//         Number of singletons: 14919 (58%)
//
void test_read()
{//
    // Wordlist lst;
    // string w;
    // while (cin >> w)
    // {
    //     lst.add_word(w);
    // }
    // lst.print_words();
    // cout << endl;
    // lst.print_stats();


    //using file constructor 
    // string filename;
    // cin>>filename;
    // Wordlist lst(filename);
    // lst.print_words();
    // lst.print_stats();
    Wordlist lst("tiny_shakespeare.txt");
   // Wordlist lst("small.txt");
    lst.print_words();
    cout<< endl;
    lst.print_stats();
}

int main()
{
   test_read();///
    Wordlist lst2;
    assert(lst2.most_frequent()==" ");
    assert(lst2.is_sorted());
    assert(lst2.num_singletons()==0);
    assert(lst2.num_different_words()==0);
    lst2.print_words();

    lst2.add_word("abc");
    assert(lst2.is_sorted());
    assert(lst2.num_singletons()==1);
    assert(lst2.num_different_words()==1);
    lst2.print_words();

    lst2.add_word("def");
    assert(lst2.is_sorted());
    assert(lst2.num_singletons()==2);
    assert(lst2.num_different_words()==2);
    assert(lst2.total_words()==2);
    lst2.print_words();

    lst2.add_word("def");

    lst2.add_word("hij");
    assert(lst2.is_sorted());
    assert(lst2.num_singletons()==2);
    assert(lst2.num_different_words()==3);
    assert(lst2.total_words()==4);

    lst2.print_words();
    lst2.print_stats();
    assert(lst2.get_count("hij")==1);
    assert(lst2.get_count("hi")==0);
    assert(lst2.most_frequent()!=" ");

    return 0; 


}

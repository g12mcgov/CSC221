//Driver.cpp

/*

Grant McGovern 
Dr. Burg 
CSC 221 
8 April 2014 

<For description and how-to-run, please see the ReadMe.txt file/>

*/

#include <iostream>
#include "Sort.h"
#include <vector>
#include <string>
#include <ctime>
#include <time.h> 
#include <unistd.h>

using namespace std;

void displayMenu(); //function to simply display the menu choices

template <typename Comparable>
void print(vector<Comparable> & a)
{
    for(int i = 0; i < a.size(); i++)
    {
        cout << a[i] << endl;
    }
    cout << endl;
}

int main()
{
    srand(time(NULL)); //seeds random gen with the system clock to make authentically random 

    int vec_length;
    int num;
    unsigned long begin;
    unsigned long end;
    long double ms;
    int user_response;

    cout << "What would you like the length of the vector to be?" << endl;
    cin >> vec_length;
    cout << endl;

    //creates a vector of integers. (ORIGINAL ONE)
    vector<int> a(vec_length); 
    //vector for insertSort()
    vector<int> b(vec_length);
    //vector for heapSort()
    vector<int> c(vec_length);
    //vector for mergeSort()
    vector<int> d(vec_length);
    //vector for quickSort()
    vector<int> e(vec_length);

    for(int i = 0; i < a.size(); i++)
    {
        a[i] = rand() % 100 + 1;
    }

    do
    {
        displayMenu(); //function to read off the menu options
        cin >> num; //takes in switch option response 
        cout << endl;

        switch(num)
        {
            case 1:
                b = a; //copies vector over so as to not insert an already sorted vector
                begin = clock();
                insertionSort(b);
                end = clock();
                ms = (long double)(end - begin)/CLOCKS_PER_SEC;
                cout << "Insertion Time: " << ms << endl;
                /////
                cout << "Would you like to print the sorted list? (1) for Yes / for (2) No "<< endl;
                heapsort_tryagain1:;
                cin >> user_response;
                /////
                if(user_response == 1)
                {
                    print(b);
                }
                else if(user_response == 2)
                {
                //    goto jumpahead1;
                }
                else
                {
                    cout << "Invalid Selection, please try again. " << endl;
                    goto heapsort_tryagain1; // allows the user to try again 
                }
                //jumpahead1:;

                break;

            case 2:
                c = a;  //copies vector over so as to not insert an already sorted vector
                begin = clock();
                heapsort(c);
                end = clock();
                ms = (long double)(end - begin)/CLOCKS_PER_SEC;
                cout << "Insertion Time: " << ms << endl;
                /////
                cout << "Would you like to print the sorted list? (1) for Yes / for (2) No "<< endl;
                heapsort_tryagain2:;
                cin >> user_response;
                /////
                if(user_response == 1)
                {
                    print(c);
                }
                else if(user_response == 2)
                {
                //    goto jumpahead2;
                }
                else
                {
                    cout << "Invalid Selection, please try again. " << endl;
                    goto heapsort_tryagain2; // allows the user to try again 
                }
                //jumpahead2:;
                break;

            case 3:
                d = a;  //copies vector over so as to not insert an already sorted vector
                begin = clock();
                mergeSort(d);
                end = clock();
                ms = (long double)(end - begin)/CLOCKS_PER_SEC;
                cout << "Insertion Time: " << ms << endl;
                /////
                cout << "Would you like to print the sorted list? (1) for Yes / for (2) No "<< endl;
                heapsort_tryagain3:;
                cin >> user_response;
                /////
                if(user_response == 1)
                {
                    print(d);
                }
                else if(user_response == 2)
                {
                //    goto jumpahead3;
                }
                else
                {
                    cout << "Invalid Selection, please try again. " << endl;
                    goto heapsort_tryagain3; // allows the user to try again 
                }
                //jumpahead3:;

                break;

            case 4:
                e = a;  //copies vector over so as to not insert an already sorted vector
                begin = clock();
                quicksort(e);
                end = clock();
                ms = (long double)(end - begin)/CLOCKS_PER_SEC;
                cout << "Insertion Time: " << ms << endl;
                /////
                cout << "Would you like to print the sorted list? (1) for Yes / for (2) NO "<< endl;
                heapsort_tryagain4:;
                cin >> user_response;
                /////
                if(user_response == 1)
                {
                    print(c);
                }
                else if(user_response == 2)
                {
                    //goto jumpahead4;
                }
                else
                {
                    cout << "Invalid Selection, please try again. " << endl;
                    goto heapsort_tryagain4; // allows the user to try again 
                }
                // jumpahead4:;
                break;

            case 5:
                cout << "Quitting Program..." << endl;
                usleep(1000000);
                exit(0); //quits the program
                break;

            default: 
                cout << "Invalid Selection." << endl;
                break;
        }
    }while(num != 5);

    return 0;
}

void displayMenu()
{
    cout << "Menu Options: " << endl;
    cout << "1) insertionSort" << endl;
    cout << "2) heapSort" << endl;
    cout << "3) mergeSort" << endl;
    cout << "4) quickSort" << endl;
    cout << "5) print" << endl;   
}

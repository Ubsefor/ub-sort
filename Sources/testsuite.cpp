    //
    //  testsuite.cpp
    //  ub-sort
    //
    //  Created by Alexander Makhov on 5/10/20.
    //

#include "../TestSuite/testsuite.hpp"

#include <iostream>
#include <cstdio>

#include "../Headers/fileworks.hpp"
#include "../Headers/quicksort.hpp"

#define GREEN    "\033[0;32m"
#define RED      "\033[0;31m"
#define WHITE    "\033[0;37m"

void UnitBeginningsComparator( const char * line1, const char * line2, int result )
{
    int res = BeginningsComparator( line1, line2 );
    if ( result == res )
    {
        std::cout << GREEN << "[PASSED] " << WHITE << "BegginingsComparator(" << line1 << ", " << line2
        << ") = " << result << std::endl;
    }
    else
    {
        std::cout << RED << "[ERROR]  " << WHITE << "BegginingsComparator(" << line1 << ", " << line2
        << ") = " << result << " != " << result << std::endl;
    }
}

void UnitEndingsComparator( const char * line1, const char * line2, int result )
{
    int res = EndingsComparator( line1, line2 );
    if ( result == res )
    {
        std::cout << GREEN << "[PASSED] " << WHITE << "EndingsComparator(" << line1 << ", " << line2
        << ") = " << result << std::endl;
    }
    else
    {
        std::cout << RED << "[ERROR]  " << WHITE << "EndingsComparator(" << line1 << ", " << line2
        << ") = " << result << " != " << result << std::endl;
    }
}

void UnitQuicksort( char ** sorted_text, long long left, long long right, const char * mode, char ** answer )
{
    if ( strcmp( mode, "Beginnings" ) == 0 )
    {
        QuickSort( sorted_text, left, right, BeginningsComparator );
    }
    else
    {
        QuickSort( sorted_text, left, right, EndingsComparator );
    }
    
    long long i = 0;
    for ( i = 0; i <= right; i++ )
    {
        if ( sorted_text[i] != answer[i] )
        {
            std::cout << RED << "[ERROR]  " << WHITE << "Error at Quicksort() implementation..." << std::endl;
            return;
        }
    }
    std::cout << GREEN << "[PASSED]" "(quicksort)" << WHITE << std::endl;
}

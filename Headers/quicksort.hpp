    //
    //  quicksort.hpp
    //  ub-sort
    //
    //  Created by Alexander Makhov on 5/10/20.
    //

#ifndef quicksort_hpp
#define quicksort_hpp

#include <stdio.h>
#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

    //! Compares two strings alphabetically  by beginning of lines
    //!
    //! @param [in] line1 first line to compare
    //! @param [in] line2 second line to compare
    //!
    //! @return 0 if strings are same alphabetically, 1 in case the first string is earlier alphabetically,
    //! -1 in case the second string is earlier alphabetically, -2 in case of bad parametrs
    //!
    //! @note Only letters recognized
    //! @note In case of error prints eroor message in standart error stream

int BeginningsComparator( const char * line1, const char * line2 );

    //! Compares two strings alphabetically  by ends of lines
    //!
    //! @param [in] line1 first line to compare
    //! @param [in] line2 second line to compare
    //!
    //! @return Returns 0 if strings are same alphabetically, 1 in case the first string is earlier alphabetically,
    //! -1 in case the second string is earlier alphabetically, -2 in case of an error
    //!
    //! @note Only letters recognized
    //! @note In case of error prints eroor message in standart error stream

int EndingsComparator( const char * line1, const char * line2 );

    //! Sorts array of strings alphabetically using standart Quick Sorting algorithm
    //!
    //! @param [in] sorted  input array
    //! @param [in] leftptr  pointer to first element
    //! @param [in] rightptr  pointer to last element
    //! @param [in] Comparator pointer to a function for lines comparison
    //!
    //! @return 0 in case sorting finished successfuly, -1 otherwise
    //!
    //! @note In case of error prints eroor message in standart error stream

int QuickSort( char ** sorted, long long leftptr, long long rightptr,
              int ( *Comparator )( const char *, const char * ) );

    //!  Actually sorting function
    //!
    //! @param [in] origin  input text
    //! @param [in] sorted  array of pointers to sort
    //! @param [in] linesNumber  number of lines in original text
    //! @param [in] Comparator pointer to a function for lines comparison
    //!
    //! @return 0 in case sorting finished successfuly, -1 otherwise
    //!
    //! @note In case of error prints eroor message in standart error stream

int SortText( char * origin, char ** sorted, long long linesNumber,
             int ( *Comparator )( const char *, const char * ) );

    //! Initializes two arrays of pointers with pointers to strings of original text
    //!
    //! @param [in] sortedBegins  array of pointers for sorting by beginnings of lines
    //! @param [in] sortedEnds  array of pointers for sorting by ends of lines
    //! @param [in] text  input text
    //! @param [in] linesNum  number of lines in original text
    //!
    //! @return 0 in case sorting finished successfuly, -1 otherwise
    //!
    //! @note In case of error, prints an error message in STDERR

int InitSortedArrs( char *** sortedBegins, char *** sortedEnds,
                           char * text, long long linesNum );

#endif /* quicksort_hpp */

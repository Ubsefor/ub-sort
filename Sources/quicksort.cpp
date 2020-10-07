    //
    //  quicksort.cpp
    //  ub-sort
    //
    //  Created by Alexander Makhov on 5/10/20.
    //

#include "../Headers/quicksort.hpp"

int BeginningsComparator( const char * line1, const char * line2 )
{
    if ( ( line1 == NULL ) || ( line2 == NULL ) )
    {
        std::cerr << "ERR: BeginningsComparator: Got NULL pointer..." << std::endl;
        return -2;
    }
    
    if ( ( line1[0] == '\0' ) && ( line2[0] == '\0' ) )
    {
        return 0;
    }
    
    if ( line1[0] == '\0' )
    {
        return 1;
    }
    
    if ( line2[0] == '\0' )
    {
        return -1;
    }
    
    if ( strcmp( line1, line2 ) == 0 )
    {
        return 0;
    }
    
    long long pointer1 = 0;
    long long pointer2 = 0;
    char      tmpChar1 = 0;
    char      tmpChar2 = 0;
    
    while ( ( line1[pointer1] != '\0' ) && ( line2[pointer2] != '\0' ) )
    {
        while ( ( line1[pointer1] != '\0' ) && ( !std::isalpha( line1[pointer1] ) ) )
        {
            pointer1++;
        }
        if ( line1[pointer1] == '\0' )
        {
            return 1;
        }
        
        while ( ( line2[pointer2] != '\0' ) && ( !std::isalpha( line2[pointer2] ) ) )
        {
            pointer2++;
        }
        if ( line2[pointer2] == '\0' )
        {
            return -1;
        }
        
        if ( line1[pointer1] > 'Z' )
        {
            tmpChar1 = line1[pointer1] - ( 'a' - 'A' );
        }
        else
        {
            tmpChar1 = line1[pointer1];
        }
        if ( line2[pointer2] > 'Z' )
        {
            tmpChar2 = line2[pointer2] - ( 'a' - 'A' );
        }
        else
        {
            tmpChar2 = line2[pointer2];
        }
        
        if ( tmpChar1 > tmpChar2 )
        {
            return -1;
        }
        if ( tmpChar1 < tmpChar2 )
        {
            return 1;
        }
        pointer1++;
        pointer2++;
    }
    
    if ( ( line1[pointer1] == '\0' ) && ( line2[pointer2] == '\0' ) )
    {
        return 0;
    }
    if ( line1[pointer1] == '\0' )
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int EndingsComparator( const char * line1, const char * line2 )
{
    if ( ( line1 == NULL ) || ( line2 == NULL ) )
    {
        std::cerr << "ERR: EndingsComparator: Got NULL pointer..." << std::endl;
        return -2;
    }
    
    long long line1Lenght = strlen( line1 );
    long long line2Lenght = strlen( line2 );
        // checks
    if ( ( line1[line1Lenght - 1] == '\0' ) && ( line2[line2Lenght - 1] == '\0' ) )
    {
        return 0;
    }
    if ( line1[line1Lenght - 1] == '\0' )
    {
        return 1;
    }
    if ( line2[line2Lenght - 1] == '\0' )
    {
        return -1;
    }
    
    if ( strcmp( line1, line2 ) == 0 )
    {
        return 0;
    }
    
    long long pointer1 = line1Lenght - 1;
    long long pointer2 = line2Lenght - 1;
    char      tmpChar1 = 0;
    char      tmpChar2 = 0;
    
    while ( ( line1[pointer1] != '\0' ) && ( line2[pointer2] != '\0' ) )
    {
        while ( ( line1[pointer1] != '\0' ) && ( !std::isalpha( line1[pointer1] ) ) )
        {
            pointer1--;
        }
        if ( line1[pointer1] == '\0' )
        {
            return 1;
        }
        
        while ( ( line2[pointer2] != '\0' ) && ( !std::isalpha( line2[pointer2] ) ) )
        {
            pointer2--;
        }
        if ( line2[pointer2] == '\0' )
        {
            return -1;
        }
        
        if ( line1[pointer1] > 'Z' )
        {
            tmpChar1 = line1[pointer1] - ( 'a' - 'A' );
        }
        else
        {
            tmpChar1 = line1[pointer1];
        }
        if ( line2[pointer2] > 'Z' )
        {
            tmpChar2 = line2[pointer2] - ( 'a' - 'A' );
        }
        else
        {
            tmpChar2 = line2[pointer2];
        }
        
        if ( tmpChar1 > tmpChar2 )
        {
            return -1;
        }
        if ( tmpChar1 < tmpChar2 )
        {
            return 1;
        }
        pointer1--;
        pointer2--;
    }
    
    if ( ( line1[pointer1] == '\0' ) && ( line2[pointer2] == '\0' ) )
    {
        return 0;
    }
    if ( line1[pointer1] == '\0' )
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

int QuickSort( char ** sorted, long long leftprt, long long rightptr,
              int ( *Comparator )( const char *, const char * ) )
{
    if ( sorted == NULL )
    {
        std::cerr << "ERR: QuickSort: got NULL pointer..." << std::endl;
        return -1;
    }
    
    char * buf = NULL;
    int  cmp   = 0;
    
        // arr size = 0 – nothing to do
    if ( rightptr - leftprt == 0 )
    {
        return 0;
    }
    
        // arr size = 2
    if ( rightptr - leftprt == 1 )
    {
        cmp = Comparator( sorted[leftprt], sorted[rightptr] );
        if ( cmp == -2 )
        {
            return -1;
        }
        if ( cmp < 0 )
        {
            buf              = sorted[leftprt];
            sorted[leftprt]  = sorted[rightptr];
            sorted[rightptr] = buf;
        }
        return 0;
    }
    
    char      * mid     = sorted[( rightptr + leftprt ) / 2];
    long long right_itr = rightptr;
    long long left_itr  = leftprt;
    
    do
    {
        cmp = Comparator( sorted[left_itr], mid );
        if ( cmp == -2 )
        {
            return -1;
        }
            // walking from left to mid
        while ( cmp > 0 )
        {
            left_itr++;
            cmp = Comparator( sorted[left_itr], mid );
            if ( cmp == -2 )
            {
                return -1;
            }
        }
        
        cmp = Comparator( sorted[right_itr], mid );
        if ( cmp == -2 )
        {
            return -1;
        }
            // walking from right to mid
        while ( cmp < 0 )
        {
            right_itr--;
            cmp = Comparator( sorted[right_itr], mid );
            if ( cmp == -2 )
            {
                return -1;
            }
        }
        
        if ( left_itr <= right_itr )
        {
            buf = sorted[right_itr];
            sorted[right_itr] = sorted[left_itr];
            sorted[left_itr]  = buf;
            left_itr++;
            right_itr--;
        }
    } while ( left_itr <= right_itr );
    
        // should not get there if everything is OK (pointers did not cross)
    if ( QuickSort( sorted, leftprt, right_itr, Comparator ) != 0 )
    {
        return -1;
    }
    
    if ( QuickSort( sorted, left_itr, rightptr, Comparator ) != 0 )
    {
        return -1;
    }
    return 0;
}

int SortText( char * origin, char ** sorted, long long linesNumber,
             int ( *Comparator )( const char *, const char * ) )
{
    if ( origin == NULL )
    {
        std::cerr << "ERR: SortText: got NULL pointer..." << std::endl;
        return -1;
    }
    if ( linesNumber == 0 )
    {
        std::cerr << "ERR: SortText: got 0 for lines number..." << std::endl;
        return -1;
    }
    
    if ( QuickSort( sorted, 0, linesNumber - 1, Comparator ) != 0 )
    {
        std::cerr << "ERR: SortText: sorting failed..." << std::endl;
        return -1;
    }
    return 0;
}

int InitSortedArrs( char *** sortedBegins, char *** sortedEnds,
                   char * text, long long linesNum )
{
    if ( text == NULL )
    {
        std::cerr << "ERR: InitSortedArrs: got NULL pointer..." << std::endl;
        return -1;
    }
    
    *sortedBegins = (char **) calloc( sizeof ( char* ), linesNum );
    if ( sortedBegins == NULL )
    {
        std::cerr << "ERR: InitSortedArrs: could not allocate requested memory for beginnings..." << std::endl;
        return -1;
    }
    
    *sortedEnds = (char **) calloc( sizeof ( char* ), linesNum );
    if ( sortedEnds == NULL )
    {
        std::cerr << "ERR: InitSortedArrs: could not allocate requested memory for endings..." << std::endl;
        return -1;
    }
    
    long long i         = 0;
    char      * curLine = text + 1;
    for ( i = 0; i < linesNum; i++ )
    {
        ( *sortedEnds )[i]   = curLine;
        ( *sortedBegins )[i] = curLine;
        
        while ( *curLine != '\0' )
        {
            curLine++;
        }
        curLine++;
    }
    return 0;
}

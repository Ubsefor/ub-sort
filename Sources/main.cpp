    //
    //  main.cpp
    //  ub-sort
    //
    //  Created by Alexander Makhov on 2/10/20.
    //

#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../Headers/quicksort.hpp"
#include "../Headers/fileworks.hpp"

#ifdef DEBUG
#include "../TestSuite/testsuite.hpp"
#endif

#define OUT_PATH    "../../../../Output/"
#define IN_PATH     "../../../../Files/"


#ifdef DEBUG
    // for testing
std::string cur_dir()
{
    char* cwd = getcwd( 0, 0 );
    std::string working_directory( cwd );
    std::free( cwd );
    return working_directory;
}
#endif

int main( int argc, const char * argv[] )
{
#ifdef DEBUG
        // test suite goes brrr
    std::cout << "Working dir:" << cur_dir() << std::endl;
    
    char ** input = (char**) calloc( sizeof ( char* ), 5 );
    input[0] = (char *) &"ccaa";
    input[1] = (char *) &"bbbbbb";
    input[2] = (char *) &"dddzzz";
    input[3] = (char *) &"hhhhmmm";
    input[4] = (char *) &"aaalll";
    
    char ** answer1 = (char**) calloc( sizeof ( char* ), 5 );
    char ** answer2 = (char**) calloc( sizeof ( char* ), 5 );
    
    answer1[0] = input[4];
    answer1[1] = input[1];
    answer1[2] = input[0];
    answer1[3] = input[2];
    answer1[4] = input[3];
    answer2[0] = input[0];
    answer2[1] = input[1];
    answer2[2] = input[4];
    answer2[3] = input[3];
    answer2[4] = input[2];
    
    UnitBeginningsComparator( "a", "bb", 1 );
    UnitBeginningsComparator( "a,aa", "aaa", 0 );
    UnitBeginningsComparator( "Abc", "abc", 0 );
    UnitBeginningsComparator( "bbbb", "bbbb", 0 );
    UnitBeginningsComparator( "b", "A", -1 );
    UnitEndingsComparator( "aaa", "bbb", 1 );
    UnitEndingsComparator( "ksjlfwemla", "lsjjbwke", 1 );
    UnitEndingsComparator( "sjdlsB", "aa", -1 );
    UnitEndingsComparator( "bbb", "bb,b", 0 );
    UnitEndingsComparator( "BBB", "bbb", 0 );
    UnitQuicksort( input, 0, 4, "Beginnings", answer1 );
    UnitQuicksort( input, 0, 4, "Endings", answer2 );
    
    free( input );
    free( answer1 );
    free( answer2 );
    
    return 0;
    
#endif
    
    if ( argc != 4 )
    {
        std::cout << "Wrong number of arguments! Please, try again:" << std::endl;
        std::cout << "1st arg: Input file name" << std::endl;
        std::cout << "2nd arg: Output file name, sorted by beginnings of lines" << std::endl;
        std::cout << "3rd arg: Output file name, sorted by endings of lines" << std::endl;
        std::cout << "The program will look for these files in \"Files\" directory and write them \"Output\" directory" << std::endl;
        return 1;
    }
    
    char fileName[128];
    if ( sizeof ( fileName ) < strlen( argv[0] ) + 1 ) /* +1 is for null character */
    {
        std::cerr << "ERR: main: Filename too long!" << std::endl;
        return 1;
    }
    
    strncpy( fileName, IN_PATH, sizeof ( fileName ) );
    strcat( fileName, argv[1] );
    
    char outLeft[128];
    strncpy( outLeft, OUT_PATH, sizeof ( outLeft ) );
    strcat( outLeft, argv[2] );
    
    char outRight[128];
    strncpy( outRight, OUT_PATH, sizeof ( outRight ) );
    strcat( outRight, argv[3] );
    
    int inputFileD = OpenFile( fileName, O_RDONLY, 0 );
    if ( inputFileD < 0 )
    {
        std::cerr << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    
    int outBegsFile = OpenFile( outLeft, O_WRONLY | O_TRUNC | O_CREAT, S_IWRITE | S_IREAD );
    if ( outBegsFile < 0 )
    {
        std::cerr << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    
    int outEndsFile = OpenFile( outRight, O_WRONLY | O_TRUNC | O_CREAT, S_IWRITE | S_IREAD );
    if ( outEndsFile < 0 )
    {
        std::cerr << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    
    char      * origin = NULL;
    long long lineno   = ReadFile( inputFileD, &origin );
    close( inputFileD );
    if ( lineno <= 0 )
    {
        close( outBegsFile );
        close( outEndsFile );
        if ( origin != NULL )
        {
            free( origin );
        }
        std::cout << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    
    char ** sortedBegs = NULL;
    char ** sortedEnds = NULL;
    if ( InitSortedArrs( &sortedBegs, &sortedEnds,
                        origin, lineno ) != 0 )
    {
        close( outBegsFile );
        close( outEndsFile );
        free( origin );
        if ( sortedBegs != NULL )
        {
            free( sortedBegs );
        }
        if ( sortedBegs != NULL )
        {
            free( sortedBegs );
        }
        std::cout << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    
    if ( SortText( origin, sortedBegs, lineno, BeginningsComparator ) != 0 )
    {
        close( outBegsFile );
        close( outEndsFile );
        free( origin );
        free( sortedBegs );
        free( sortedEnds );
        std::cout << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    
    if ( SortText( origin, sortedEnds, lineno, EndingsComparator ) != 0 )
    {
        close( outEndsFile );
        close( outBegsFile );
        free( origin );
        free( sortedEnds );
        free( sortedBegs );
        std::cout << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    
    if ( WriteFile( outBegsFile, sortedBegs, lineno ) != 0 )
    {
        close( outBegsFile );
        close( outEndsFile );
        free( origin );
        free( sortedBegs );
        free( sortedEnds );
        std::cout << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    free( sortedBegs );
    close( outBegsFile );
    
    if ( WriteFile( outEndsFile, sortedEnds, lineno ) != 0 )
    {
        close( outEndsFile );
        free( origin );
        free( sortedEnds );
        std::cout << "ERR: main: Unsuccessful sorting..." << std::endl;
        return 1;
    }
    free( sortedEnds );
    close( outEndsFile );
    
    free( origin );
    std::cout << "Successfully sorted the text!" << std::endl;
    return 0;
}

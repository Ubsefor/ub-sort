    //
    //  fileworks.hpp
    //  ub-sort
    //
    //  Created by Alexander Makhov on 5/10/20.
    //

#ifndef fileworks_hpp
#define fileworks_hpp

#include <iostream>
#include <fcntl.h>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

    //! Opens file with given parametrs
    //!
    //! @param [in] fileName file name to open
    //! @param [in] oflag  Opening flags for the file
    //! @param [in] mode  create mode (in case O_CREATE was setted)
    //!
    //! @return file descriptor in case file was successfully opened, -1 otherwise
    //!
    //! @note In case of error prints eroor message in standart error stream

int OpenFile( const char * fileName, int oflag, unsigned mode );


    //! Reads text from input file and writes all text to array of char
    //!
    //! @param [in] inFile file name to read from
    //! @param [out] text  pointer to array of char to write the text
    //!
    //! @return number of lines in the text in case of successful reading, -1 otherwise
    //!
    //! @note All '\n' symbols will be replaced with '\0'
    //! @note In case of error prints eroor message in standart error stream

long long ReadFile( int inFile, char ** text );


    //! Reads text from input file and writes all text to array of char
    //!
    //! @param [in] outFile file name to write to
    //! @param [out] text array of pointers to char (strings for output)
    //!
    //! @return 0 in case of successful writing, -1 otherwise
    //!
    //! @note In case of error prints eroor message in standart error stream

int WriteFile( int outFile, char ** text, long long lineno );

#endif /* fileworks_hpp */

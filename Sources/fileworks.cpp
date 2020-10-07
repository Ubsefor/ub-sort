    //
    //  fileworks.cpp
    //  ub-sort
    //
    //  Created by Alexander Makhov on 5/10/20.
    //

#include "../Headers/fileworks.hpp"

int OpenFile( const char * fileName, int oflag, unsigned mode )
{
    int fd = open( fileName, oflag, mode );
    if ( fd == -1 )
    {
        switch ( errno )
        {
            case ENOENT:
                std::cerr << "ERR: OpenFile: File " << fileName << " not found." << std::endl;
                return -1;
            case EMFILE:
                std::cout << "ERR: OpenFile: Too many opened file descriptors, please try again" << std::endl;
                return -1;
            default:
                std::cerr << "ERR: OpenFile: Could not open file..." << fileName << std::endl;
                return -1;
        }
    }
    return fd;
}

long long ReadFile( int inFile, char ** text )
{
    if ( inFile <= 0 )
    {
        std::cerr << "ERR: ReadFile: Got an errorneous file descriptor..." << std::endl;
        return -1;
    }
    
    if ( *text != NULL )
    {
        std::cerr << "ERR: ReadFile: Got a pointer with something..." << std::endl;
        return -1;
    }
    
    struct stat file_info;
    if ( fstat( inFile, &file_info ) != 0 )
    {
        std::cerr << "ERR: ReadFile: Could not get file info..." << std::endl;
        return -1;
    }
    
    long long text_size = file_info.st_size + 2;
    *text = (char *) calloc( sizeof ( char ), text_size );
    if ( *text == NULL )
    {
        std::cerr << "ERR: ReadFile: Could not allocate memory for input text." << std::endl;
        return -1;
    }
    
    if ( read( inFile, *text + 1, text_size ) < 0 )
    {
        std::cerr << "ERR: ReadFile: Could not read input text..." << std::endl;
        return -1;
    }
    
    long long i      = 0;
    long long lineno = 0;
    for ( i = 1; i < text_size; i++ )
    {
        if ( ( *text )[i] == '\n' )
        {
            ( *text )[i] = '\0';
            lineno++;
        }
    }
    ( *text )[text_size - 1] = '\0';
    ( *text )[0]             = '\0';
    
    if ( lineno == 0 )
    {
        std::cout << "WARN: ReadFile: Empty input file." << std::endl;
    }
    return lineno + 1;
}

int WriteFile( int outFile, char ** text, long long lineno )
{
    if ( outFile <= 0 )
    {
        std::cerr << "ERR: WriteFile: Errorneous file descriptor..." << std::endl;
        return -1;
    }
    
    if ( text == NULL )
    {
        std::cerr << "ERR: WriteFile: Got NULL pointer." << std::endl;
        return -1;
    }
    if ( lineno == 0 )
    {
        std::cerr << "ERR: WriteFile: Got zero lines number..." << std::endl;
        return -1;
    }
    
    long long i   = 0;
    char      ret = '\n';
    for ( i = 0; i < lineno; i++ )
    {
        if ( write( outFile, text[i], strlen( text[i] ) ) < 0 )
        {
            std::cerr << "ERR: WriteFile: Could not write the file..." << std::endl;
            return -1;
        }
        if ( write( outFile, (char *) &ret, sizeof ( char ) ) < 0 )
        {
            std::cerr << "ERR: WriteFile: Could not write the file..." << std::endl;
            return -1;
        }
    }
    return 0;
}

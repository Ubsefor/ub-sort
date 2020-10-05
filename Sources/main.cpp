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

#include "quicksort.hpp"
#include "fileworks.hpp"

#ifdef DEBUG
#include "testsuite.hpp"
#define LOG_PATH "./Logs/"
#endif
 
#define OUT_PATH "./Output/"
#define IN_PATH "./Files/"


std::string current_working_directory()
{
  char* cwd = getcwd( 0, 0 ) ; // **** microsoft specific ****
  std::string working_directory(cwd) ;
  std::free(cwd) ;
  return working_directory ;
}


int main(int argc, const char * argv[]) {
  // insert code here...
  
#ifdef DEBUG
    // test suite goes brrr
#endif
  
  std::cout << "Working dir:" << current_working_directory() << std::endl;
  test();
  std::cout << "Hello, World!\n";
  return 0;
}

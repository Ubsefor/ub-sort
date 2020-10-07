    //
    //  testsuite.hpp
    //  ub-sort
    //
    //  Created by Alexander Makhov on 5/10/20.
    //

#ifndef testsuite_hpp
#define testsuite_hpp

void UnitBeginningsComparator( const char * line1, const char * line2, int answer );

void UnitEndingsComparator( const char * line1, const char * line2, int answer );

void UnitQuicksort( char ** sorted_text, long long left, long long right, const char * mode, char ** answer );

#endif /* testsuite_hpp */


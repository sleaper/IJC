#include <stdio.h>

#define KOTESENI /* Block comment in the middle of macro definition */ 42

int main(){
    /*
            Multi
                    Line
        Block
                Comment
    
    */

    char *comment = "/* This is not a block comment */";
    char *string = "// This is not a line comment";

    /* Random block comment */
    char a = 'a'; // This is a line comment with escape sequences: \t \r \n
    char b = 'b';
    char c = '/'; // The line below should be treated as a comment \
    char d = 'd';

    /* Line comment inside // of block comment */

    // Line \
    comment \
    that \
    continues \
    on \
    different \
    lines

    char d = '\\';
    char e = '\'';

    /* This is a block comment with escape sequences: \t \r \n*/

    char *string2 = "/***/";
    char *string3 = "text\"//text\'\"\\";

    return 0;
}

// #include <stdio.h>
// #include <string.h>


// // This code outputs: h is in "This is my test string"
// int main(int argc, char* argv[])
// {
//    const char *invalid_characters = "hz";
//    char *mystring = "This is my test string";
//    char *c = mystring;
//    while (*c)
//    {
//        if (strchr(invalid_characters, *c))
//        {
//           printf("%c is in \"%s\"\n", *c, mystring);
//        }


//        c++;
//    }


//    return 0;
// }






#include <stdio.h>
 
int main() {
    int arr[] = {2, 4, 6, 8, 10};
    int x = 8;
     
    int arrLen = sizeof arr / sizeof arr[0];
    int isElementPresent = 0;
     
    for (int i = 0; i < arrLen; i++) {
        if (arr[i] == x) {
            isElementPresent = 1;
            break;
        }
    }
     
    if (isElementPresent) {
        printf("%d is present in this array.\n", x);
    } else {
        printf("%d is not present in this array.\n", x);
    }
     
    return 0;
}
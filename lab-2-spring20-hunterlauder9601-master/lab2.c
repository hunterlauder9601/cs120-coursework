#include <stdio.h>
#include <stdlib.h>
/*
    the slightly different look to main allows me
    to pass in data on startup.
    Everything works exactly the same.
*/
int main(int argc, char* argv[]){

    /**********   PART A   ***********/
    //complete Part A here
    printf("Hello World!\n******\n*    *\n*    *\n******");


    /**********   PART B   ***********/
    //This is just some scaffolding to allow you to
    //pass in arguments to your program
    int x, y, z;
    if(argc != 4){
        printf("ERROR: 3 integer arguments required on execution");
        printf("Usage: ./lab2 <num> <num> <num>\n Example: ./lab2 4 12 9");
        exit(1);
    }else{
        x = atoi(argv[1]);
        y = atoi(argv[2]);
        z = atoi(argv[3]);
    }

    //complete Part B here. Use the variables x, y, z.
    if(x>y){
        if(x>z){
	    printf("%d is the greatest among the 3 variables.", x);
	}
	else{
	    printf("%d is the greatest among the 3 variables.", z);
	}
    }
    else{
        if(y>z){
	    printf("%d is the greatest among the 3 variables.", y);
	}
	else{
	    printf("%d is the greatest among the 3 variables.", z);
	}
    }

    return 0; //optional
}

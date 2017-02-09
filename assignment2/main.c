/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: JonChan
 *
 * Created on February 1, 2017, 11:47 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
/*
 * 
 */

// function to check whether plaintext password is in the %pwd/password.txt file
// also checks if the plaintext password meets the requirements specified in the handout
// ******Need to create efficient way of comparing with the reverse password*******

bool checkFlip (char original[], int hashval){
    
    char flip[128];
    // check if there is a way to copy the reverse instead
    strcpy(flip, original);
    
    // check the hashtable at hashval+1
    
}

char *flipString (char original[]){
    
    char *flipped[128];
    int i;
    int j=0;
    
    for( i=strlen(original)-1 ; i >= 0; i--, j++ ){
        flipped[j]=original[i];
    }
    return flipped;
    
}

bool checkReqs (char password[], int length){
    
    int i;
    char pass[128];
    strcpy(pass, password);
    
    // Check to make sure that the length requirements are met
    if( (length >= 6) && (length <= 12) ){
        // Check to make sure that all characters are alphanumeric
        for( i = 0; i < length; i++ )
        {
            if( !isalnum(pass[i]) ){
                return false;
            }
        }
    }
    else{
        printf("length violation\n");
        return false;
    }
    //pass[0] = '\0';
    
    return true;
    // Meets the password requirements, need to check if there exists an entry already in passwords.txt
    
}

// hashing function that hashes the plaintext password inputted from the user
// USING DBJ2 HASHING ALGORITHM FOUND ON http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%100000;
}

int main(int argc, char** argv) {

    // Need to parse the password.txt file and store all passwords in a hash table
    // about n = 10000 passwords
    // Use fgets on password.txt and store into a string, make sure t account for newline
    /*
     * Requirements:
     * 1. alphanumeric only - no symbols
     * 2. minimum 6 to 12 characters long
     * 
     * Additional, add the reverse to hashval+1 
     */
    FILE *fp;
    char pass[128];
    char *table[100000];
    int i = 0;
    int hashval;
    
    // Open file for reading
    fp = fopen("password.txt", "r");
    if(fp == NULL)
    {
        printf("Password file empty or does not exist\n");
        return -1;
    }
    // Read a line from the file and store into str if there is a line
    while( fgets(pass, 128, fp)!=NULL )
    {
        // Check for the length requirements
        //printf("in loop\n");
        if( checkReqs(pass, strlen(pass)-1) ){
            printf("VALID\n");
            hashval = (int)hash(pass);
            table[hashval] = pass;
            printf("table[%d] value with %s", hashval, table[hashval]);
        }
        else{
            printf("INVALID\n");
        }
        
    }
    
    //printf("Finished parsing password.txt file!\n");
    
    // Correct arguments
    if ( argc == 2 ){
    // check the password to make sure it meets the basic requirements (length, 
        hashval = (int)hash(argv[1]);
        //printf("hashval = %d\n", hashval);
    }
    // Too many arguments
    else{
        printf ("INVALID\n");
    }
    fclose(fp);
    return (EXIT_SUCCESS);
}


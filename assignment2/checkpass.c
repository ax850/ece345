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

typedef struct {
    char password[128];
    struct hashEntry *next;
}hashEntry;

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
    
    for( i=strlen(original)-1 ; i >= 0&& i != j; i--, j++ ){
        flipped[j]=original[i];
    }
    return *flipped;
    
}

bool checkReqs (char password[], int length){
    
    int i;
    char pass[128];
    strcpy(pass, password);
    
    printf ("length: %d\npassword: %s", length, password);
    
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
    FILE *fp;
    hashEntry newEntry;
    newEntry.next = NULL;
    char pass[128];
    hashEntry *table[100000];
    int i = 0;
    int hashval;
    
    // Open file for reading
    fp = fopen("password.txt", "rw");
    if(fp == NULL)
    {
        printf("Password file empty or does not exist\n");
        return -1;
    }
    // Read a line from the file and store into str if there is a line
    while( fgets(pass, 128, fp)!=NULL )
    {
        // Check for the length requirements
        // **** DON'T NEED TO CHECK IF THE REQUIREMENTS ARE MET FOR PASSWORD IN THE TEXT FILES
        printf("VALID\n");
        strcpy(newEntry.password, pass);
        newEntry.next = NULL;
        hashval = (int)hash(pass);
        // *** CHECK HERE IF THERE IS A COLLISION AND DEAL WITH IT HERE
        table[hashval] = &newEntry;
        printf("table[%d] value with %s", hashval, table[hashval]->password);
    }
    
    // Correct arguments
    if ( argc == 2 ){
    // check the password to make sure it meets the basic requirements (length, 
        if( checkReqs(argv[1], strlen(argv[1])) ){
            // Need to check if the password exists or not
            printf("VALID\n");
            hashval = (int)hash(argv[1]);
        }
        else{
            printf("INVALID\n");
        }
    }
    // Too many arguments
    else{
        printf ("INVALID\n");
    }
    fclose(fp);
    return (EXIT_SUCCESS);
}


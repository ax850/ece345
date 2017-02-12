#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char password[128];
    struct hashEntry *next;
}hashEntry;

// Global Hash Table
hashEntry *table[100000];
hashEntry *last;

void sanitize (char string[]){
    int i;

    for ( i = strlen(string)-1; i > 0 ; i-- ){
            if( !isalnum(string[i]) ){
                    string[i] = 0;
            }
            else{
                    return;
            }
    }
}

void flipString (char original[], char flipped[]){
    
    int i;
    int j=0;
    for( i=strlen(original)-1 ; i >= 0 ; i--, j++ ){
        flipped[j]=original[i];
    }
	flipped[strlen(original)] = 0;
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
    
    return true;   
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

bool checkChains (hashEntry *root, char password[]){

    root = root->next;
    while( root->next != NULL ){
        // Checks all entries except last one
        if( !strcmp(root->password, password) ){
            return false;
        }
        root = root->next;
    }
    // Check last hashEntry
    if( !strcmp(root->password, password) ){
        return false;
    }
    last = root;
    return true;
}


int main(int argc, char** argv) {
    FILE *fp;
    char pass[128];
    char flipped[128];
    hashEntry *newEntry;
    int i = 0;
    unsigned long hashval = 0;
    int reverseHashval = 0;
    int numCol = 0;
    // Open file for reading
    fp = fopen("password.txt", "a+");
    if(fp == NULL){
        printf("Password file empty or does not exist\n");
        return -1;
    }
    // Parse password.txt file and store into hash table
    // Assume that all passwords in the text file meet the requirements
    while( fgets(pass, 128, fp)!=NULL ){
        // Copy the passwords into the hashtable
        newEntry = malloc(sizeof(hashEntry));
        sanitize(pass);
        strcpy(newEntry->password, pass);
        newEntry->next = NULL;
        hashval = (int)hash(pass);
        if ( table[hashval] == NULL ){
            table[hashval] = newEntry;
        }
        else{
            table[hashval]->next = newEntry;
        }
    }
    
    // Correct number of arguments
    if ( argc == 2 ){
    // check the password to make sure it meets the basic requirements (length, no complex chars)
        if( checkReqs(argv[1], strlen(argv[1])) ){
            // Need to check if the password exists or not
            hashval = hash(argv[1]);
            // Entry in table is empty
            // Check to make sure the reverse is not in the table
            flipped[0] = 0;
            flipString(argv[1], flipped);
            reverseHashval = hash(flipped);
            //printf("strlen = %d reverseHashval %d for password %s", strlen(flipped), reverseHashval, flipped);
            // Entry does not exist for password and reverse password
            if ( table[hashval] == NULL && table[reverseHashval] == NULL ){
                //printf("CASE 1\n");
                printf("VALID\n");
                newEntry = malloc(sizeof(hashEntry));
                strcpy(newEntry->password, argv[1]);
                newEntry->next = NULL;
                hashval = (int)hash(argv[1]);
                // Add entry to the hashtable
                table[hashval] = newEntry;
                // Write password to password.txt
                fprintf(fp, "%s\n", argv[1]);
                fclose(fp);
                return 0;
                // Reverse of password may exist, need to check chains
            }
            // Possible collision
            else if( table[hashval] == NULL && table[reverseHashval] != NULL ){
                //printf("CASE 2\n");
                //printf("REVERSEHASHVAL NOT EQUAL TO NULL\n");
                // Only one entry, check that
                if( table[reverseHashval]->next == NULL ){
                    //printf("reverse hashval password string %s\n", table[reverseHashval]->password);
                    //printf("inputted password string %s\n", argv[1]);
                    if (!strcmp(table[reverseHashval]->password, flipped)){
                        printf("INVALID\n");
                        fclose(fp);
                        return -1;
                    }
                    // Reverse password does not exist, insert into hashtable and write to file
                    else{
                        printf("VALID\n");
                        newEntry = malloc(sizeof(hashEntry));
                        strcpy(newEntry->password, argv[1]);
                        newEntry->next = NULL;
                        hashval = (int)hash(pass);
                        // Add entry to the hashtable
                        table[hashval] = newEntry;
                        // Write password to password.txt
                        fprintf(fp, "%s\n", argv[1]);
                        fclose(fp);
                        return 0;
                    }
                }
                // Need to check chains!
                else if( table[reverseHashval]->next != NULL ){
                    if( !checkChains(table[reverseHashval], flipped) ){
                        printf("INVALID\n");
                        fclose(fp);
                        return -1;
                    }
                    else{
                        printf("VALID\n");
                        newEntry = malloc(sizeof(hashEntry));
                        strcpy(newEntry->password, argv[1]);
                        newEntry->next = NULL;
                        hashval = (int)hash(argv[1]);
                        // Add entry to the hashtable
                        table[hashval] = newEntry;
                        // Write password to password.txt
                        fprintf(fp, "%s\n", argv[1]);
                        fclose(fp);
                        return 0;
                    }
                }
            }
            else if( table[hashval] != NULL && table[reverseHashval] == NULL ){
                    //printf("CASE 3\n");
                if( table[hashval]->next == NULL ){
                    //printf("HASHVAL NOT NULL REVERSEHASHVAL NULL\n");
                    //printf("HASHTABLE PASS %s\n", table[hashval]->password);
                    //printf("INPUT PASS %s\n", argv[1]);
                    if( !strcmp(table[hashval]->password, argv[1]) ){
                        printf("INVALID\n");
                        fclose(fp);
                        return -1;
                    }
                    else{
                        printf("VALID\n");
                        newEntry = malloc(sizeof(hashEntry));
                        strcpy(newEntry->password, argv[1]);
                        newEntry->next = NULL;
                        hashval = (int)hash(argv[1]);
                        // Add entry to the hashtable
                        table[hashval]->next = newEntry;
                        // Write password to password.txt
                        fprintf(fp, "%s\n", argv[1]);
                        fclose(fp);
                        return 0;
                    }
                }
                else if( table[hashval]->next != NULL ){
                    if( !checkChains(table[hashval], argv[1]) ){
                        printf("INVALID\n");
                        fclose(fp);
                        return -1;
                    }
                    else{
                        printf("VALID\n");
                        newEntry = malloc(sizeof(hashEntry));
                        strcpy(newEntry->password, argv[1]);
                        newEntry->next = NULL;
                        hashval = (int)hash(argv[1]);
                        // Add entry to the hashtable
                        last->next = newEntry;
                        // Write password to password.txt
                        fprintf(fp, "%s\n", argv[1]);
                        fclose(fp);
                        return 0;
                    }
                }
            }
            else if( table[hashval] != NULL && table[reverseHashval] != NULL ){
				//printf("CASE 4\n");
                if( table[hashval]->next == NULL && table[reverseHashval]->next == NULL ){
                    if( !strcmp(table[hashval]->password, argv[1]) || !strcmp(table[reverseHashval]->password, flipped) ){
                        printf("INVALID\n");
                        fclose(fp);
                        //printf("Reverse Password Found");
                        return -1;
                    }
                    else{
                        printf("VALID\n");
                        newEntry = malloc(sizeof(hashEntry));
                        strcpy(newEntry->password, argv[1]);
                        newEntry->next = NULL;
                        hashval = (int)hash(argv[1]);
                        // Add entry to the hashtable
                        table[hashval]->next = newEntry;
                        // Write password to password.txt
                        fprintf(fp, "%s\n", argv[1]);
                        fclose(fp);
                        return 0;
                    }
                }
                else if( table[hashval]->next != NULL && table[reverseHashval]->next == NULL ) {
                    if( !strcmp(table[hashval]->password, argv[1]) || !strcmp(table[reverseHashval]->password, flipped) ){
                        printf("INVALID\n");
                        fclose(fp);
                        printf("Reverse Password Found");
                        return -1;
                    }
                    else{
                        if( !checkChains(table[hashval], argv[1]) ){
                            printf("INVALID\n");
                            fclose(fp);
                            printf("Reverse Password Found");
                            return -1;
                        }
                        else{
                            printf("VALID\n");
                            newEntry = malloc(sizeof(hashEntry));
                            strcpy(newEntry->password, argv[1]);
                            newEntry->next = NULL;
                            hashval = (int)hash(argv[1]);
                            // Add entry to the hashtable
                            last = newEntry;
                            // Write password to password.txt
                            fprintf(fp, "%s\n", argv[1]);
                            fclose(fp);
                            return 0;
                        }
                    }
                }
                else if( table[hashval]->next != NULL && table[reverseHashval]->next != NULL ) {
                    if( !strcmp(table[hashval]->password, argv[1]) || !strcmp(table[reverseHashval]->password, flipped) ){
                        printf("INVALID\n");
                        fclose(fp);
                        printf("Reverse Password Found");
                        return -1;
                    }
                    else{
                        if( checkChains(table[reverseHashval], flipped) ){
                            if( checkChains(table[hashval], argv[1]) ){
                                printf("VALID\n");
                                newEntry = malloc(sizeof(hashEntry));
                                strcpy(newEntry->password, argv[1]);
                                newEntry->next = NULL;
                                hashval = (int)hash(argv[1]);
                                // Add entry to the hashtable
                                last = newEntry;
                                // Write password to password.txt
                                fprintf(fp, "%s\n", argv[1]);
                                fclose(fp);
                                return 0;
                            }
                        printf("INVALID\n");
                        fclose(fp);
                        printf("Reverse Password Found");
                        return -1;
                    }
                }
            }
        }
        // Does not meet requirements
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
}


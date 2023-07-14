/*
Author: Jasmine Nguyen
RedID: 826620932
Course: CS420-Advanced Programming Languages
Instructor: Magda Tsintsadze
Date: 02/05/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_WORDS 1000 //maximum number of words that can be stored
#define MAX_WORD_SIZE 50 //maximum length of a word in characters

// Custom strcpy function that limits the number of characters to copy
int my_strcpy(char *dest, const char *src, size_t n) {
    size_t i = 0;
    while (i < n - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

// Custom strlen function that counts the number of characters in a string
int my_strlen(const char *str) {
    int len = 0;
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

// Function to check if a word is valid based on the minimum length and allowed characters
int is_valid_word(const char *word, int size) {
    if (word == NULL || *word == '\0') {
        return 0;
    }
    int len = my_strlen(word);
    if (len >= size) {
        for (int i = 0; i < len; i++) {
            char c = word[i];
            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int main(int argc, char **argv) {
    // Allocate memory for the array of words
    char **words = (char **)malloc(MAX_WORDS * sizeof(char *));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }
    int num_words = 0;
    int degree = 4;
    int size = 6;
    int count = 1;
    int insert_space = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                
                case 'd':
                    // Specify the number of words to combine in each output string
                    if (i+1 < argc) {
                        degree = atoi(argv[i+1]);
                        i++;
                    } else {
                        fprintf(stderr, "Error: missing argument for -d option\n");
                        return 1;
                    }
                    break;
                case 'm':
                    // Specify the minimum length of each word used
                    if (i+1 < argc) {
                        size = atoi(argv[i+1]);
                        i++;
                    } else {
                        fprintf(stderr, "Error: missing argument for -m option\n");
                        return 1;
                    }
                    break;
                case 'n':
                    // Specify the number of output strings to produce
                    if (i+1 < argc) {
                        count = atoi(argv[i+1]);
                        i++;
                    } else {
                        fprintf(stderr, "Error: missing argument for -n option\n");
                        return 1;
                    }
                    break;
                case 's':
                    // Indicate to insert a space between words in the output
                    insert_space = 1;
                    break;
                default:
                    // Error checking - Invalid argument 
                    fprintf(stderr, "Error: invalid argument: %s\n", argv[i]);
                    return 1;
            }
        } else {
            fprintf(stderr, "Error: invalid argument: %s\n", argv[i]);
            return 1;
        }
    }

    // Read in words from input stream and store in the words
    char word[MAX_WORD_SIZE];
    while (scanf("%s", word) != EOF) {
        if (num_words >= MAX_WORDS) {
            fprintf(stderr, "Error: too many words, maximum is %d\n", MAX_WORDS);
            return 1;
        }
        if (is_valid_word(word, size)) {
            words[num_words] = (char *)malloc(MAX_WORD_SIZE * sizeof(char));
            if (words[num_words] == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                return 1;
            }
            my_strcpy(words[num_words], word, MAX_WORD_SIZE);
            num_words++;
        }
    }

    // Randomly combine words and send to output stream
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int length = 0;
        int used[MAX_WORDS] = {0};
        int num_used = 0;
        while (num_used < degree && num_used < num_words) {
            // Choose a random word that hasn't been used yet and meets the length requirement
            int idx;
            int word_len;
            do {
                idx = rand() % num_words;
                word_len = my_strlen(words[idx]);
            } while (word_len < size || used[idx]);
            used[idx] = 1;
            num_used++;
            if (num_used > 1 && insert_space) {
                // Insert a space between words if required
                printf(" ");
                length++;
            }
            // Remove periods and commas from the output
            char *word = words[idx];
            int len = my_strlen(word);
            for (int k = 0; k < len; k++) {
                char c = word[k];
                if (c != '.' && c != ',') {
                    printf("%c", c);
                    length++;
                }
            }
        }
        if (length > 0) {
            printf("\n");
        }
    }

    // Free memory
    for (int i = 0; i < num_words; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}
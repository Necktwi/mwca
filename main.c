/* 
 * File:   main.c
 * Author: Gowtham
 *
 * Created on August 14, 2014, 7:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * 
 */
int main(int argc, char** argv) {
    FILE* f = fopen(argv[1], "r");
    if (f != NULL) {
        char c;
        int char_count = 0;
        int word_count = 0;
        int line_count = 0;
        char longest_words[10][100];
        int longest_word_length = 0;
        int longest_words_count = 0;
        int white_space_flag = 0;
        char word_buf[100];
        int word_length = 0;
        int freq_char_count[26];
        int freq_char = 0;
        int freq_char_freq = 0;
        int i = 0;
        for (i = 0; i < 26; i++)freq_char_count[i] = 0;
        while ((c = getc(f)) != EOF) {
            while (c == '\n' || c == ' ' || c == ',' || c == '.') {
                if (white_space_flag == 0) {
                    white_space_flag = 1;
                    word_buf[word_length] = '\0';
                    if (word_length > 0) {
                        word_count++;
                        if (word_length > longest_word_length) {
                            longest_words_count = 1;
                            strcpy(longest_words[0], word_buf);
                            longest_word_length = word_length;
                        } else if (word_length == longest_word_length) {
                            strcpy(longest_words[longest_words_count], word_buf);
                            longest_words_count++;
                            assert(longest_words_count <= 10);
                        }
                        word_length = 0;
                    }
                }
                if (c == '\n') {
                    line_count++;
                }
                char_count++;
                c = getc(f);
            }
            white_space_flag = 0;
            if ((int) c >= 65 && (int) c <= 90) {
                freq_char_count[c - 65] += 1;
            } else if ((int) c >= 97 && (int) c <= 122) {
                freq_char_count[c - 97] += 1;
            } else if ((int) c == EOF) {
                break;
            }
            word_buf[word_length] = c;
            word_length++;
            assert(word_length <= 100);
            char_count++;
        }
        line_count++;
        for (i = 0; i < 26; i++) {
            if (freq_char_count[i] > freq_char_freq) {
                freq_char_freq = freq_char_count[i];
                freq_char = i;
            }
        }
        printf("Number of lines = %d\n", line_count);
        printf("Number of words = %d\n", word_count);
        printf("Number of characters = %d\n", char_count);
        printf("The longest words = ");
        for (i = 0; i < longest_words_count; i++)
            printf("%s, ", longest_words[i]);
        printf("(%d)\n", longest_word_length);
        printf("The most frequently used characters = %c (%d)",
                (char) (freq_char + 97), freq_char_freq);
        fclose(f);
    } else {
        printf("Invalid input file.\n");
    }
    return (EXIT_SUCCESS);
}


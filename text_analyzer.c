#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void analyze_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    int c; // To store each character
    int line_count = 0, word_count = 0, char_count = 0;
    int in_word = 0; // Flag to detect if we are inside a word

    // Read the file character by character
    while ((c = fgetc(file)) != EOF) {
        char_count++; // Increment character count

        if (c == '\n') {
            line_count++; // Increment line count for each newline
        }

        if (isspace(c) || c == '\n') {
            // If space or newline is encountered, check for word boundary
            if (in_word) {
                word_count++; // We were in a word, so increment word count
                in_word = 0; // Reset the flag
            }
        } else {
            // If we encounter a non-whitespace character, we are inside a word
            in_word = 1;
        }
    }

    // If the last word in the file wasn't followed by a space or newline, count it
    if (in_word) {
        word_count++;
    }

    // Print the results
    printf("Lines: %d\n", line_count);
    printf("Words: %d\n", word_count);
    printf("Characters: %d\n", char_count);

    fclose(file); // Close the file
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1; // Exit with error code if no file path is provided
    }

    const char *filename = argv[1]; // Get the file path from the command line argument
    analyze_file(filename);
    return 0;
}

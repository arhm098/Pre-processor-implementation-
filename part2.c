#include <stdio.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 256
#define MAX_TOKENS 256

//helper function
void replaceWord(char *line, const char *word, const char *replacement)
{
    char *pos = strstr(line, word);
    while (pos != NULL)
    {
        size_t wordLength = strlen(word);
        size_t replacementLength = strlen(replacement);
        size_t tailLength = strlen(pos + wordLength);
        memmove(pos + replacementLength, pos + wordLength, tailLength + 1);
        memcpy(pos, replacement, replacementLength);
        pos = strstr(pos + replacementLength, word);
    }
}

int macroExpansion(char* filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    char line[MAX_TOKEN_LENGTH];
    char var[MAX_TOKENS][MAX_TOKEN_LENGTH];
    char target[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int var_n = 0, target_n = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "#define") != NULL)
        {
            char *token;
            int i = 0;

            token = strtok(line, " "); // First call to strtok using space as the delimiter

            while (token != NULL)
            {
                printf("%s\n", token);

                if (i == 1)
                {
                    strcpy(var[var_n++], token);
                }

                if (i == 2)
                {
                    strcpy(target[target_n++], token);
                }

                token = strtok(NULL, " ");
                i++;
            }
        }
    }

    fclose(file);

    printf("Before Replacement:\n");
    for (int i = 0; i < var_n; i++)
    {
        printf("Variable: %s, Target: %s\n", var[i], target[i]);
    }

    file = fopen(filename, "r+");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }
    FILE* outputFile = fopen("out2.c", "w");
    while (fgets(line, sizeof(line), file) != NULL)
    {
        for (int i = 0; i < var_n; i++)
        {
            replaceWord(line, var[i], target[i]);
        }
        if (strstr(line, "#define") == NULL)
        {
            fprintf(outputFile, "%s", line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("File missing.\n");
        return 1;
    }

    char *filename = argv[1];
    int result = macroExpansion(filename);
    if (result == -1)
    {
        printf("file not found\n");
        return -1;
    }
}
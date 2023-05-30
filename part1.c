#include <stdio.h>
#include <string.h>
//helper functions
void removeDoubleSlashComments(char* line)
{
    int i, j;
    int inComment = 0;
    int len = strlen(line);

    for (i = 0, j = 0; i < len; i++)
    {
        if (!inComment)
        {
            if (line[i] == '/' && line[i + 1] == '/')
            {
                inComment = 1;
                i++;
            }
            else
            {
                line[j] = line[i];
                j++;
            }
        }
    }

    line[j] = '\0';
}

int stripOffComments(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }
    char line[256];
    char final[256][256];
    int lineNumber = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        int i = 0;
        int i_2 = 0;
        int inComment = 0;

        while (line[i] != '\0')
        {
            if (line[i] == '/' && line[i+1] == '*')
            {
                inComment = 1;
            }
            else if (line[i-2] == '*' && line[i-1] == '/')
            {
                inComment = 0;
            }
            else if (!inComment)
            {
                final[lineNumber][i_2] = line[i];
                i_2++;
            }
            i++;
        }

        lineNumber++;
    }

    fclose(file);

    // Writing the modified lines to out1.c
    FILE* outputFile = fopen("out1.c", "w");
    if (outputFile == NULL)
    {
        printf("Error creating output file: out1.c\n");
        return -1;
    }

    for (int line = 0; line < lineNumber; line++)
    {
        removeDoubleSlashComments(final[line]);
        fprintf(outputFile, "%s", final[line]);
    }

    fclose(outputFile);

    printf("Output written to out1.c\n");
}
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("File missing.\n");
        return -1;
    }
    char* filename = argv[1];
    int result = stripOffComments(filename);
    if (result == -1)
    {
        printf("file not found\n");
        return -1;
    }
    return 0;
}

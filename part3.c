#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int includeHeaderFiles(char* filename)
{
    FILE *file = fopen(filename, "r");
    FILE *outputFile = fopen("final.c","w");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    char line[256];char line_stdlib[256];char line_stdio[256];char line_string[256];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, "#include") != NULL)
        {
            printf("library found");
            if (strstr(line,"<stdio.h>"))
            {
                FILE *stdio = fopen("pa2_stdio", "r");
                while (fgets(line_stdio, sizeof(line_stdio), stdio) != NULL)
                {
                    //printf("%s\n",line_stdio);
                    fprintf(outputFile, "%s", line_stdio);
                }   
                fclose(stdio);
            }
            else if (strstr(line,"<stdlib.h>"))
            {
                FILE *stdlib = fopen("pa2_stdlib", "r");
                while (fgets(line_stdlib, sizeof(line_stdlib), stdlib) != NULL)
                {
                    fprintf(outputFile, "%s", line_stdlib);
                }   
                fclose(stdlib);
            }
            else if (strstr(line,"<string.h>"))
            {
                FILE *string = fopen("pa2_string", "r");
                while (fgets(line_string, sizeof(line_string), string) != NULL)
                {
                    fprintf(outputFile, "%s", line_string);
                }   
                fclose(string);
            }
 
        }
        else 
        {
            fprintf(outputFile, "%s", line);
        }
    }
        fclose(file);
        fclose(outputFile);

}
int main(int argc, char *argv[])
{
   if (argc < 2)
    {
        printf("File missing.\n");
        return 1;
    }

    char *filename = argv[1];
     int result = includeHeaderFiles(filename);
    if (result == -1)
    {
        printf("file not found\n");
        return -1;
    }
    return 0;
}
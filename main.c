#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>

int main() {
    
    int err = 0;
    size_t bytesRead = 0;
    char* buffer = (char*) malloc(sizeof(char) * 1024);
    FILE* fp;
    FILE* fp2;

    if (buffer != NULL) {
        
        printf("Buffer allocation succeed\n");
    } else {

        printf("Error occurred on allocating buffer, exitng...\n");
        return -1;
    }

    fp = fopen("sample.txt", "w");
    if (fp != NULL) {

        printf("File creation succeed\n");
    } else {

        printf(
            "Error occurred on creating the file, errno is: %s\n"
            "exiting...\n",
            strerror(errno)
        );
        fclose(fp);
        return -1;
    }

    err = fprintf(fp, "Hello world!\nIt's me writing to you!\n");
    if (err >= 0) {

        printf("Writing to newly created file succeed\n");
    } else {
        
        printf("Error occurred on writing to newly created file, exiting...");
        fclose(fp);
        return -1;
    }

    fclose(fp);

    fp = fopen("sample.txt", "r");
    if (fp != NULL) {

        printf("Reading file succeed\n");
    } else {

        printf(
            "Error occurred on reading the file, errno is: %s\n"
            "exiting...\n",
            strerror(errno)
        );
        fclose(fp);
        return -1;
    }

    fp2 = fopen("sample_copy.txt", "w");
    if (fp2 != NULL) {

        printf("Copy of file creation succeed\n");
    } else {

        printf(
            "Error occurred on creating of the copy of the file, errno is: %s\n"
            "exiting...\n",
            strerror(errno)
        );
        fclose(fp);
        return -1;
    }

    while ((bytesRead = fread(buffer, sizeof(char), 1024, fp)) > 0) {
        
        fwrite(buffer, sizeof(char), bytesRead, fp2);
    }

    fclose(fp);
    fclose(fp2);
    memset(buffer, 0, 1024);
    free(buffer);

    printf("Copy succeed\n");

    return 0;
}
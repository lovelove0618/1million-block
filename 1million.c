#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URL_LENGTH 256
#define MAX_HOST_LENGTH 128

void extract_hosts(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    char line[MAX_URL_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char* token;
        token = strtok(line, ",");
        for (int i = 0; i < 2; ++i) {
            token = strtok(NULL, ",");
            if (token == NULL) {
                break;
            }
        }

        if (token != NULL) {
            char host[MAX_HOST_LENGTH];
            strcpy(host, token);
            
            char* start_pos = strstr(host, "//");
            if (start_pos != NULL) {
                start_pos += 2;
                char* end_pos = strchr(start_pos, '/');
                if (end_pos != NULL) {
                    *end_pos = '\0';
                    printf("%s\n", start_pos);
                }
            }
        }
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3 || strcmp(argv[1], "1m-block") != 0) {
        printf("Usage: ./1million 1m-block <site_list_file>\n");
        return 1;
    }

    const char* file_path = argv[2];
    
    extract_hosts(file_path);

    return 0;
}


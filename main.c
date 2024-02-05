#include <stdio.h>
#include <string.h>
#include <dirent.h>

void save_current_id(const char *username, const char *email) {
    FILE *file = fopen("current_id", "w");
    if (file) {
        fprintf(file, "%s\n%s\n", username, email);
        fclose(file);
    } else {
        printf("Error: Unable to open or create the file 'current_id'.\n");
    }
}

int config_handle(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("No command provided.\n");
        return 1;
    }

    if (strcmp(argv[1], "config") != 0) {
        printf("Invalid command. Please use 'config'.\n");
        return 1;
    }

    if (argc < 3) {
        printf("Insufficient arguments for 'config' command.\n");
        return 1;
    }

    if (strcmp(argv[2], "-global") == 0) {
        if (argc < 4) {
            printf("Insufficient arguments for '-global' command.\n");
            return 1;
        }

        if (strcmp(argv[3], "user.name") == 0){
            printf("%s\n", argv[4]);
            FILE *file = fopen("global_username_config", "r");
            if (file) {
                fclose(file);
                printf("Error: File 'global_username_config' already exists.\n");
                return 1;
            }
            file = fopen("global_username_config", "w");
            if (file) {
                fprintf(file, "%s\n", argv[4]);
                fclose(file);
                save_current_id(argv[4], "");
                return 0;
            } else {
                printf("Error: Unable to create the file 'global_username_config'.\n");
                return 1;
            }
        } 
        else if(strcmp(argv[3], "user.email") == 0){
            printf("%s\n", argv[4]);
            FILE *file = fopen("global_email_config", "r");
            if (file) {
                fclose(file);
                printf("Error: File 'global_email_config' already exists.\n");
                return 1;
            }
            file = fopen("global_email_config", "w");
            if (file) {
                fprintf(file, "%s\n", argv[4]);
                fclose(file);
                char username[100];
                FILE *current_id_file = fopen("current_id", "r");
                if (current_id_file) {
                    fscanf(current_id_file, "%s", username);
                    fclose(current_id_file);
                    save_current_id(username, argv[4]);
                }
                return 0;
            } else {
                printf("Error: Unable to create the file 'global_email_config'.\n");
                return 1;
            }
        } 
        else {
            printf("Invalid sub-command for '-global'. Please use 'user.name' or 'user.email'.\n");
            return 1;
        }
    } 
    else if (strcmp(argv[2], "user.name") == 0) {
        printf("%s\n", argv[3]);
        FILE *file = fopen("local_username_config", "a");
        if (file) {
            fprintf(file, "%s\n", argv[3]);
            fclose(file);
            save_current_id(argv[3], "");
            return 0;
        } else {
            printf("Error: Unable to open or create the file 'local_username_config'.\n");
            return 1;
        }
    } 
    else if(strcmp(argv[2], "user.email") == 0){
        printf("%s\n", argv[3]);
        FILE *file = fopen("local_email_config", "a");
        if (file) {
            fprintf(file, "%s\n", argv[3]);
            fclose(file);
            char username[100];
            FILE *current_id_file = fopen("current_id", "r");
            if (current_id_file) {
                fscanf(current_id_file, "%s", username);
                fclose(current_id_file);
                save_current_id(username, argv[3]); 
            }
            return 0;
        } else {
            printf("Error: Unable to open or create the file 'local_email_config'.\n");
            return 1;
        }
    }
    else {
        printf("Invalid command. Please use 'config', 'user.name', or'user.email'.\n");
        return 1;
    }
}

int main(int argc, char const *argv[]) {
    printf("Hello!\n");
    printf("The Number of arguments is: %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("The Argument[%d] is: \"%s\"\n", i, argv[i]);
    }

    printf("\n\n");

    if (argc >= 2 && strcmp(argv[1], "config") == 0) {
        return config_handle(argc, argv);
    } 
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
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
    else {printf("Invalid command. Please use 'config', 'user.name', or 'user.email'.\n");
        return 1;
    }
}

int init_handle(int argc, char const *argv[]) {
    if (argc >= 3) {
        printf("Error: Too many arguments.\n");
        return 1;
    }
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("Error getting current directory");
        return 1;
    }
    struct stat st;
    if (stat(".neogit", &st) == 0 && S_ISDIR(st.st_mode)) {
        printf("Error: A .neogit folder already exists.\n");
        return 1;
    }
    if (mkdir(".neogit",0777) == -1) {
        perror("Error creating .neogit directory");
        return 1;
    }
    printf("Successfully created .neogit directory.\n");

    return 0;
}


int add_handle(int argc, char *const argv[]) {
    if (argc < 3) {
        perror("Error : please specify a file");
        return 1;
    }
	else{
		//code
		return 0;
	}
}

int reset_handle(int argc, char *const argv[]) { 
    if (argc < 3) {
        perror("Error : please specify a file");
        return 1;
    }
	else{
		//code
		return 0;
	}
}

int commit_handle(int argc, char *const argv[]) { 
    if (argc < 3) {
        perror("Error : please use the correct format");
        return 1;
    }
	else{
		//code
		return 0;
	}
}

int main(int argc, char const *argv[]) {
    printf("Hello!\n");
    if (argc >= 2 && strcmp(argv[1], "config") == 0) {
        return config_handle(argc, argv);
    } 
	else if (argc >= 2 && strcmp(argv[1], "init") == 0) {
		return init_handle(argc, argv);
	}
	else if (argc >= 2 && strcmp(argv[1], "add") == 0) {
		return add_handle(argc, argv);
	}
	else if (argc >= 2 && strcmp(argv[1], "commit") == 0) {
		return commit_handle(argc, argv);
	}
	else if (argc >= 2 && strcmp(argv[1], "reset") == 0) {
		return reset_handle(argc, argv);
	}
}

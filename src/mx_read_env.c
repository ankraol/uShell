#include "header.h"

char *mx_read_env(char *file, char *path, t_builtin_command *my_command) {
    extern char **environ;
    char **bin_arr;
    DIR *dir = NULL;
    char *exe = NULL;
    int flag = 0;
    char *last_path = NULL;
    int i = 0;
    struct stat sb;

    if  (lstat(file, &sb) >= 0) {
        if ((sb.st_mode & S_IFREG) == S_IFREG)
            return strdup(file);
        else
        {
           mx_printerr("ush: permission denied:");
           mx_printerr(file);
           mx_printerr("\n");
           return NULL;
        }
        
    }
    else {
            printf("READ_ENV1\n");
            if (path != NULL) {
                last_path = mx_strjoin(path, "/");
                last_path = mx_strjoin_two(last_path, file);
                if (lstat(last_path, &sb) < 0)
                    return NULL;
                printf("READ_ENV2\n");
            }
            else {
                char *name = getenv("PATH");
                if (name != NULL) {
                    bin_arr = mx_strsplit(name, ':');
                    printf("READ_ENV3\n");
                }
                else {
                    if (my_command->unset_path == true) {
                        printf("READ_ENV4\n");
                        return NULL;
                    }

                    
                    else { 
                        //char *arr[] = { "/usr/bin", "/bin", NULL};
                        //*bin_arr[] = { "/usr/bin", "/bin", NULL};
                        //bin_arr = arr;
                        bin_arr = (char **)malloc(sizeof(char *) * 3);
                        bin_arr[0] = strdup("/usr/bin");
                        bin_arr[1] = strdup("/bin");
                        bin_arr[2] = NULL;
                    }
            }
                printf("READ_ENV\n");
                for(i = 0; bin_arr[i]; i++) {
                    dir = opendir(bin_arr[i]);
                    struct dirent *entry;
                    if (dir != NULL) {
                        entry = readdir(dir);
                        while (entry) {
                            if (strcmp(entry->d_name, file) == 0) {
                                exe = strdup(entry->d_name);
                                flag = 1;
                                break;
                            }
                            entry = readdir(dir);
                        }
                        //printf("\n");
                        closedir(dir);
                    }
                    if (flag == 1)
                        break;
                }
                last_path = mx_strjoin(bin_arr[i], "/");
                last_path = mx_strjoin_two(last_path, file);
                }
            }
    printf("%--s--\n", last_path);
    return last_path;

}

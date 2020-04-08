#include "header.h"


char *if_program(char *file, struct stat sb) {

    if ((sb.st_mode & S_IFREG) == S_IFREG)
        return strdup(file);
    else {
        mx_printerr("ush: permission denied:");
        mx_printerr(file);
        mx_printerr("\n");
        return NULL;
    }
}
char *is_path(char *path, char *file) {
    char *last_path = NULL;
    struct stat sb;

    last_path = mx_strjoin(path, "/");
    last_path = mx_strjoin_two(last_path, file);
    if (lstat(last_path, &sb) < 0) {
        mx_strdel(&last_path);
        return NULL;
    }
    return last_path;
}

void inside_dir(char *file, char *bin_dir, int *flag) {
    struct dirent *entry;
    DIR *dir = NULL;

    dir = opendir(bin_dir);
    if (dir != NULL) {
        entry = readdir(dir);
        while (entry) {
            if (strcmp(entry->d_name, file) == 0) {
                *flag = 1;
                break;
            }
            entry = readdir(dir);
        }
        closedir(dir);
    }
}

char *find_in_dir(char **bin_arr, char *file) {
    int i = 0;
    int flag = 0;
    char *last_path = NULL;

    for(i = 0; bin_arr[i]; i++) {
        inside_dir(file, bin_arr[i], &flag);
        if (flag == 1)
            break;
    }
    if (flag == 0)
        return NULL;
    last_path = mx_strjoin(bin_arr[i], "/");
    last_path = mx_strjoin_two(last_path, file);    
    return last_path;
}

char *mx_no_path(char *file, t_builtin_command *my_command) {
    char *name = getenv("PATH");
    char **bin_arr = NULL;
    char *last_path = NULL;

    if (name != NULL)
        bin_arr = mx_strsplit(name, ':');
    else {
        if (my_command->unset_path == true)
            return NULL;
        else {
            bin_arr = (char **)malloc(sizeof(char *) * 3);
            bin_arr[0] = strdup("/usr/bin");
            bin_arr[1] = strdup("/bin");
            bin_arr[2] = NULL;
        }
    }
    last_path = find_in_dir(bin_arr, file);
    mx_del_strarr(&bin_arr);
    return last_path;
}


char *mx_read_env(char *file, char *path, t_builtin_command *my_command) {
    //extern char **environ;
    //char **bin_arr;
    // DIR *dir = NULL;
    // char *exe = NULL;
    // int flag = 0;
    char *last_path = NULL;
   // int i = 0;
    struct stat sb;

    if (lstat(file, &sb) >= 0) {
        last_path = if_program(file, sb);
        // if ((sb.st_mode & S_IFREG) == S_IFREG)
        //     return strdup(file);
        // else
        // {
        //    mx_printerr("ush: permission denied:");
        //    mx_printerr(file);
        //    mx_printerr("\n");
        //    return NULL;
        // }
        
    }
    else {
           // printf("READ_ENV1\n");
        if (path != NULL) {
            // last_path = mx_strjoin(path, "/");
            // last_path = mx_strjoin_two(last_path, file);
            // if (lstat(last_path, &sb) < 0)
            //     return NULL;
            last_path = is_path(path, file);
        }
        else {
            last_path = mx_no_path(file, my_command);
        //     char *name = getenv("PATH");
        //     if (name != NULL) {
        //         bin_arr = mx_strsplit(name, ':');
        //         printf("READ_ENV3\n");
        //     }
        //     else {
        //         if (my_command->unset_path == true) {
        //             printf("READ_ENV4\n");
        //             return NULL;
        //         }

                
        //         else { 
        //             //char *arr[] = { "/usr/bin", "/bin", NULL};
        //             //*bin_arr[] = { "/usr/bin", "/bin", NULL};
        //             //bin_arr = arr;
        //             bin_arr = (char **)malloc(sizeof(char *) * 3);
        //             bin_arr[0] = strdup("/usr/bin");
        //             bin_arr[1] = strdup("/bin");
        //             bin_arr[2] = NULL;
        //         }
        // }
        //     printf("READ_ENV\n");
        //     for(i = 0; bin_arr[i]; i++) {
        //         dir = opendir(bin_arr[i]);
        //         struct dirent *entry;
        //         if (dir != NULL) {
        //             entry = readdir(dir);
        //             while (entry) {
        //                 if (strcmp(entry->d_name, file) == 0) {
        //                     exe = strdup(entry->d_name);
        //                     flag = 1;
        //                     break;
        //                 }
        //                 entry = readdir(dir);
        //             }
        //             //printf("\n");
        //             closedir(dir);
        //         }
        //         if (flag == 1)
        //             break;
        //     }
        //     last_path = mx_strjoin(bin_arr[i], "/");
        //     last_path = mx_strjoin_two(last_path, file);
        }
    }
    printf("%--s--\n", last_path);
    return last_path;

}

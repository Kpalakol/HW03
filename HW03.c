#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

/*
Name: Kavya Palakolanu
BlazerId: Kpalakol
Project #: hw2
To compile: gcc hw2,c
To run: ./a.out -S
        ./a.out -s <size>
        ./a.out -t d
        ./a.out -t f
        ./a.out -f
        ./a.out -S -s <size>
        ./a.out -S -s <size> -t d
        ./a.out -S -s <size> -t f 
        ./a.out -f a 2
        ./a.out -f jpg 1
        ./a.out -S -s 1024 -f jpg 3
*/

char bitcmde[1028], bitCmdE[3000];
char displayE[1028][1028];
int esetBit = 0;
int BitE = 0;
void E_e_run(char *dummy[1028]){

    int ChildStatusRunData;                                                                                                                                                                                                                                                                                                                                                                                                                                      
    pid_t ChildPID;
    ChildPID = fork();  
    if (ChildPID == 0) {
        execvp(dummy[0], dummy);
        perror("process run error");
        exit(-1);
    } 
    else if (ChildPID > 0) {
        wait(&ChildStatusRunData);
	    if (WIFEXITED(ChildStatusRunData)==0)
	        printf("Child Process run exited incorrectly\n");
	} 
    else {
		perror("child process fork issue"); 
		exit(EXIT_FAILURE);
	}
}


int CounterToken = 0;
void print_file_info(const char *path, const char *name, int file_details_flag)
{
    char *full_path = malloc(strlen(path) + strlen(name) + 2);
    sprintf(full_path, "%s/%s", path, name);

    struct stat st;
    if (stat(full_path, &st) == -1)
    {
        perror("stat");
        return;
    }
    else if (S_ISLNK(st.st_mode))
    {
        char target_path[1024];
        int count = readlink(full_path, target_path, sizeof(target_path));
        target_path[count] = '\0';

        if (file_details_flag)
        {
            printf("%s (%s) (%d) (%o) (%s)\n", name, target_path, (int)st.st_size, st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO), ctime(&st.st_atime));
        }
        else
        {
            printf("%s -> %s\n", name, target_path);
        }
    }
    else
    {
        if (file_details_flag)
        {
            printf("%s (%d) (%o) (%s) \n", name, (int)st.st_size, st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO), ctime(&st.st_atime));
        }
        else
        {
            printf("%s\n", name);
        }
    }

    free(full_path);
}



void traverse_directory(char *dir_path, int indent, int file_details_flag, int size_flag, int max_size, int file_flag, char *pattern, int max_depth, int tflag, int isFiles, int esetBit)
{
    DIR *dir = opendir(dir_path);
    if (dir == NULL)
    {
        fprintf(stderr, "Error: could not open directory %s\n", dir_path);
        exit(1);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        for (int i = 0; i < indent && tflag == 0; i++)
        {
            printf("\t");
        }
        struct stat st;
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        if (stat(path, &st) == 0)
        {
            if (S_ISDIR(st.st_mode))
            {
                if (tflag)
                {
                    if (isFiles)
                    {
                        continue;
                    }
                }
                if (file_details_flag)
                {
                    printf("%s (0)\n", entry->d_name);
                }
                else
                {
                    printf("%s\n", entry->d_name);
                }
                traverse_directory(path, indent + 1, file_details_flag, size_flag, max_size, file_flag, pattern, max_depth, tflag, isFiles,esetBit);
            }
            else
            {
                if (tflag)
                {
                    if (isFiles == 0)
                    {
                        continue;
                    }
                }
                if (file_flag)
                {
                    if (strstr(entry->d_name, pattern) != NULL && indent <= max_depth)
                    {
                        if (size_flag)
                        {
                            if ((int)st.st_size <= max_size)
                            {
                                print_file_info(dir_path, entry->d_name, file_details_flag);
                            }
                        }
                        else
                        {

                            print_file_info(dir_path, entry->d_name, file_details_flag);
                        }
                    }
                }
                else if (size_flag)
                {
                    if ((int)st.st_size <= max_size)
                    {
                        print_file_info(dir_path, entry->d_name, file_details_flag);
                    }
                }
                else
                {

                    print_file_info(dir_path, entry->d_name, file_details_flag);
                }
            }
        }
        
        if (strcmp(entry->d_name,"")!=0){
        if(BitE==1 && file_flag==0){
            if (strcmp(dir_path,"")!=0  ){
                strcpy(displayE[CounterToken++],dir_path);
                
            }
        }
       if (esetBit == 1 && BitE == 0 && strcmp(entry->d_name, "") != 0 && !S_ISDIR(st.st_mode)) {
            char* tkinterSplitECmdpath[1028];
            int tkpcnt = 0;
            char ecmd[1024];
            strcpy(ecmd, bitcmde);
            char* tkinterSplit = strtok(ecmd, " ");
            while (tkinterSplit != NULL) {
                tkinterSplitECmdpath[tkpcnt] = tkinterSplit;
                tkpcnt++;
                tkinterSplit = strtok(NULL, " ");
            }
            tkinterSplitECmdpath[tkpcnt] = entry->d_name;
            tkinterSplitECmdpath[tkpcnt + 1] = NULL;
            E_e_run(tkinterSplitECmdpath);
        }
        }
        else
        {
            printf("Error: while opening %s\n", path);
            exit(1);
        }
    }

    closedir(dir);
}

void getE_e_data(int str1Val, char **str2Val){
    int dataitr = 0;
    while(dataitr<str1Val){
        if(!strcmp(str2Val[dataitr],"-e")){
            esetBit = 1;
            strcpy(bitcmde,str2Val[dataitr+1]);
        }if(!strcmp(str2Val[dataitr],"-E")){
            BitE = 1;
            strcpy(bitCmdE,str2Val[dataitr+1]);
            char *tkinterSplit = strtok(bitCmdE," ");   
            for(;tkinterSplit != NULL ;) {
                strcpy(displayE[CounterToken++],tkinterSplit);
                tkinterSplit = strtok(NULL, " ");
            }
        }dataitr+=1;
    }
}

int main(int argc, char *argv[])
{
    int opt;
    int file_details_flag = 0;
    int size_flag = 0;
    int max_size = 0;
    int file_flag = 0;
    char *pattern = NULL;
    int max_depth = -1;
    int tflag = 0;
    int isFiles = 0;
    char *path = NULL;
    while ((opt = getopt(argc, argv, "Ss:f:t:e:E")) != -1)
    {
        switch (opt)
        {
        case 'S':
            file_details_flag = 1;
            break;
        case 's':
            size_flag = 1;
            max_size = atoi(optarg);
            break;
        case 'f':
            file_flag = 1;
            pattern = optarg;
            max_depth = atoi(argv[optind++]);
            break;
        case 't':
            tflag = 1;
            if (strcmp(optarg, "f") == 0)
            {
                isFiles = 1;
            }
            break;
        case '?':
            printf("Unknown option '%c'\n", optopt);
            exit(EXIT_FAILURE);
        }
    }
    getE_e_data(argc,argv);
    
    path = argv[argc-1];

    if (path == NULL)
    {
        path = ".";
    }
    else if (path[0]!='/')
    {
        path = ".";
    }
    traverse_directory(path, 0, file_details_flag, size_flag, max_size, file_flag, pattern, max_depth, tflag, isFiles,esetBit);
    if (BitE) {
    char *tkinterSplitECmdpath[1028];
    int CounterECmd = 0;
    while (CounterECmd < CounterToken) {
        tkinterSplitECmdpath[CounterECmd] = displayE[CounterECmd];CounterECmd++;
    }
    tkinterSplitECmdpath[CounterECmd] = NULL; E_e_run(tkinterSplitECmdpath);
}
}
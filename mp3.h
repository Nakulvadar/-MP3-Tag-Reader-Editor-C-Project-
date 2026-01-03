#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS 0
#define FAILURE 1

typedef enum{
    e_view,
    e_edit,
    e_help,
    e_unsupport,
}opretion_type;


typedef struct mp3tag{
char tag[5];
char fname[50];
int size;
FILE *S_fp;
FILE *D_fp;
char new_content[100];
char content[6][100];
}mp3_t;


/*===================================View part=======================================*/
// check opretion for view or edit
opretion_type check_opretion(char *argv[]);

//read and validation
int read_validation_mp3tag(int argc , char *argv[],mp3_t *ptr);

// making big indin to littel indin
int conversion(int num, int size);

//Display the data
int View_data(mp3_t *ptr, int index);


/*====================================Edit==========================================*/

int check_validation_edit(int argc , char *argv[],mp3_t *ptr);

int do_edit(int argc , char *argv[], mp3_t *ptr);

int copy_header(mp3_t *ptr);

int copy_remaining_data(mp3_t *ptr);
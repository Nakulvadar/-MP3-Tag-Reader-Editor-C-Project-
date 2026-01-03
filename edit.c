#include "mp3.h"
int check_validation_edit(int argc , char *argv[],mp3_t *ptr)
{
    if (argc < 5)
    {
        printf("Error : Invalide number of arguments passed\n");
        return FAILURE;
    }
    
    if(strcmp(argv[2],"-t")==0){
        strcpy(ptr->tag,"TIT2");
    }   
    else if(strcmp(argv[2],"-a")==0){
        strcpy(ptr->tag,"TPE1");
    }
    else if(strcmp(argv[2],"-A")==0){
        strcpy(ptr->tag,"TALB");
    }
    else if(strcmp(argv[2],"-y")==0){
        strcpy(ptr->tag,"TYER");
    }       
    else if(strcmp(argv[2],"-m")==0){
        strcpy(ptr->tag,"TCON");
    }    
    else if(strcmp(argv[2],"-c")==0){
        strcpy(ptr->tag,"COMM");
    }    
    else{
        return FAILURE;
    }

    char *S_file = argv[4];
    ptr->S_fp= fopen(S_file,"rb");
    if(!ptr->S_fp){
    printf("Error : File not open.\n");
    return FAILURE;
}
    char Tmark[4];
    fread(Tmark, 1, 3, ptr->S_fp);
    Tmark[3] = '\0';
    printf("Mp3 name : %s\n", Tmark);
    if (strcmp(Tmark, "ID3") != 0)
    {
        printf("Erorr : wrong MP3 tag ragar id.\n");
        fclose(ptr->S_fp);
        return FAILURE;
    }
    
    strcpy(ptr->new_content,argv[3]);
    fclose(ptr->S_fp);
    return SUCCESS;
}

int do_edit(int argc , char *argv[], mp3_t *ptr)
{
    ptr->S_fp = fopen(argv[4], "rb");
    if (!ptr->S_fp) {
        printf("Error : Source file open failed\n");
        return FAILURE;
    }

    ptr->D_fp = fopen("temp.mp3","wb");
    if(!ptr->D_fp){
        printf("Error : File not open.\n");
        return FAILURE;
    }

    if(copy_header(ptr)==FAILURE){
        printf("Error! Copy header failed\n");
        return FAILURE;
    }
    printf("Header copy Successfuly.\n");

    char flag[2];
    char tag[5];
 
    for (int i = 0; i < 6; i++)
    {
        int size =0;

        fread(tag, 1, 4,ptr->S_fp);
        tag[4] = '\0';
        fwrite(tag,4,1,ptr->D_fp);
        
        fread(&size, 4, 1, ptr->S_fp);
        size = conversion(size, 4);

        int be_size = conversion(size, 4);
        fwrite(&be_size, 4, 1, ptr->D_fp);

        fread(flag,2,1,ptr->S_fp);
        fwrite(flag,2,1,ptr->D_fp);
        
        if(strcmp(tag,ptr->tag) == 0)
        {
            fseek(ptr->S_fp, size, SEEK_CUR);

            char buffer[size];
            memset(buffer, 0, size);
            buffer[0] = 0x03;
            strncpy(&buffer[1], ptr->new_content, size - 2);
            fwrite(buffer, size, 1, ptr->D_fp);
        }
        else{
            char *content = malloc(size);
            fread(content, size, 1, ptr->S_fp);
            fwrite(content, size, 1, ptr->D_fp);
            free(content);
        }
    }
    if(copy_remaining_data(ptr) != SUCCESS)
        return FAILURE;

    return SUCCESS;
}

int copy_header(mp3_t *ptr)
{
    rewind(ptr->S_fp);
    char buffer[10];
    if(fread(buffer, 10, 1, ptr->S_fp) != 1){
        return FAILURE;
    }
    if(fwrite(buffer,10,1,ptr->D_fp) != 1){
        return FAILURE;
    }
    return SUCCESS;
}

int copy_remaining_data(mp3_t *ptr)
{
    char ch;
    while (fread(&ch, 1, 1, ptr->S_fp) == 1)
    {
        if (fwrite(&ch, 1, 1, ptr->D_fp) != 1)
        return FAILURE;
    }
    return SUCCESS;
}

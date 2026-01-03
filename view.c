#include "mp3.h"

int read_validation_mp3tag(int argc , char *argv[],mp3_t *ptr)
{
    if (argc != 3)
    {
        printf("Error : Invalide number of arguments passed\n");
        return FAILURE;
    }

    FILE *fp = fopen(argv[2] , "rb");
    if (!fp)
    {
        printf("Erorr : Invalid file name.\n");
        return FAILURE;
    }

    char mp3name[4];
    fread(mp3name, 1, 3, fp);
    mp3name[3] = '\0';
    printf("Mp3 name : %s\n", mp3name);

    if (strcmp(mp3name, "ID3") != 0)
    {
        printf("Erorr : wrong MP3 tag ragar id.\n");
        fclose(fp);
        return FAILURE;
    }

    // skiping 7 bytes 
    fseek(fp, 7, SEEK_CUR);

    int size;
    char tag[5];
    char content[100];

    for (int i = 0; i < 6; i++)
    {
        fread(tag, 1, 4, fp);
        tag[4] = '\0';
        strcpy(ptr->tag, tag);

        fread(&size, 1, 4, fp);
        ptr->size = conversion(size, 4);

        //skeping 2 bytes for flag.
        fseek(fp, 2, SEEK_CUR);

        fgetc(fp);

        fread(content, 1, ptr->size - 1, fp);
        content[ptr->size - 1] = '\0';

        strcpy(ptr->content[i], content);

        if (View_data(ptr, i) == FAILURE)
        {
            printf("Print Metadata failed\n");
            fclose(fp);
            return FAILURE;
        }
    }

    printf("-------------------------------------------------------------------\n");
    fclose(fp);
    return SUCCESS;
}

int View_data(mp3_t *ptr, int index)
{
    printf("-------------------------------------------------------------------\n");

    if (strcmp(ptr->tag, "TIT2") == 0)
        printf("Title   |\t%-50s|\n", ptr->content[index]);
    else if (strcmp(ptr->tag, "TPE1") == 0)
        printf("Artist  |\t%-50s|\n", ptr->content[index]);
    else if (strcmp(ptr->tag, "TALB") == 0)
        printf("Album   |\t%-50s|\n", ptr->content[index]);
    else if (strcmp(ptr->tag, "TYER") == 0)
        printf("Year    |\t%-50s|\n", ptr->content[index]);
    else if (strcmp(ptr->tag, "TCON") == 0)
        printf("Content |\t%-50s|\n", ptr->content[index]);
    else if (strcmp(ptr->tag, "COMM") == 0)
        printf("Comment |\t%-50s|\n", ptr->content[index]);

    return SUCCESS;
}

int conversion(int num, int size)
{
    char temp;
    char *ptr = (char *)&num;
    for (int i = 0; i < size / 2; i++)
    {
        temp = ptr[i];
        ptr[i] = ptr[size - 1 - i];
        ptr[size - 1 - i] = temp;
    }
    return num;
}

/*=====================================================================
Project Name : MP3 Tag Reader & Editor
Name         : Nakul Anil Vadar
Batch ID     : 25021_325
======================================================================

1. INTRODUCTION
-----------------------------------------------------------------------
The MP3 Tag Reader & Editor project is a command-line based application
developed in C to read and modify ID3 metadata tags of MP3 audio files.

ID3 tags store information such as song title, artist name, album,
year, content (genre), and comments. This project allows users to view
existing tag information and edit selected fields without affecting
the actual audio data of the MP3 file.

-----------------------------------------------------------------------
2. FEATURES
-----------------------------------------------------------------------
1. Reads ID3 tag information from MP3 files
2. Displays metadata in a structured and readable format
3. Supports editing of individual ID3 tags
4. Creates a temporary MP3 file during edit operations
5. Preserves original audio data while updating metadata
6. Menu-driven command-line interface
7. Validates input arguments and MP3 file format

-----------------------------------------------------------------------
3. ID3 TAGS SUPPORTED
-----------------------------------------------------------------------
The project supports the following ID3v2 tags:

1. TIT2  -> Song Title
2. TPE1  -> Artist Name
3. TALB  -> Album Name
4. TYER  -> Year
5. TCON  -> Content / Genre
6. COMM  -> Comment

-----------------------------------------------------------------------
4. COMMAND-LINE OPERATIONS
-----------------------------------------------------------------------
The program supports three main operations:

1. View MP3 Tag Information
2. Edit MP3 Tag Information
3. Help

Operation selection is done using command-line arguments.

-----------------------------------------------------------------------
5. PROGRAM USAGE
-----------------------------------------------------------------------

5.1 View MP3 Metadata
----------------------
Command:
./a.out -v <mp3_file>

Example:
./a.out -v sample.mp3

This command reads and displays all supported ID3 tag information
from the given MP3 file.

-----------------------------------------------------------------------
5.2 Edit MP3 Metadata
----------------------
Command:
./a.out -e <option> <new_value> <mp3_file>

Edit Options:
-t  -> Edit song title
-a  -> Edit artist name
-A  -> Edit album name
-y  -> Edit year
-m  -> Edit content / genre
-c  -> Edit comment

Example:
./a.out -e -t NewSongTitle sample.mp3

During editing:
1. Header information is copied safely
2. Selected tag value is updated
3. Remaining file data is preserved

-----------------------------------------------------------------------
5.3 Help Option
----------------
Command:
./a.out --help

Displays usage instructions and available edit options.

-----------------------------------------------------------------------
6. WORKING FLOW
-----------------------------------------------------------------------
1. Validate command-line arguments
2. Determine operation type (view / edit / help)
3. Validate MP3 file and ID3 header
4. Perform selected operation:
   - View: Read and display ID3 tag values
   - Edit: Modify selected tag and create updated MP3 file
5. Display success or error message

-----------------------------------------------------------------------
7. SAMPLE OUTPUT (VIEW MODE)
-----------------------------------------------------------------------
Mp3 name : ID3
-------------------------------------------------------------------
Title   |       Sunny Sunny - Yo Yo Honey Singh
-------------------------------------------------------------------
Artist  |       Yo Yo Honey Singh
-------------------------------------------------------------------
Album   |       Yaariyan
-------------------------------------------------------------------
Year    |       2013
-------------------------------------------------------------------
Content |       Bollywood Music
-------------------------------------------------------------------
Comment |       eng
-------------------------------------------------------------------

-----------------------------------------------------------------------
8. SAMPLE OUTPUT (EDIT MODE)
-----------------------------------------------------------------------
Header copy Successfuly.
Edit data is Successful

Updated file verification:
./a.out -v temp.mp3

-----------------------------------------------------------------------
9. DATA STRUCTURES USED
-----------------------------------------------------------------------
1. Structure (mp3_t)
   - Stores MP3 file pointers
   - Stores tag information
   - Manages metadata offsets and sizes

2. Enumeration (opretion_type)
   - e_view
   - e_edit
   - e_help
   - e_unsupport

-----------------------------------------------------------------------
10. ADVANTAGES
-----------------------------------------------------------------------
1. Safe editing without corrupting audio data
2. Modular and readable code structure
3. Efficient binary file handling
4. User-friendly command-line interface
5. Suitable for system-level programming practice

-----------------------------------------------------------------------
11. CONCLUSION
-----------------------------------------------------------------------
The MP3 Tag Reader & Editor project successfully demonstrates how to
work with binary files and structured metadata in C. The program
accurately reads and updates ID3 tags while preserving the integrity
of the MP3 audio data.

This project showcases strong understanding of:
- Binary file handling
- Command-line argument parsing
- Structures and enums
- Modular C programming
- File system operations

=====================================================================
*/

#include"mp3.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("ERROR: INVALID ARGUMENTS\n");
        printf("./a.out --help\n");
        return FAILURE;
    }

    mp3_t info;
    opretion_type op = check_opretion(argv);

    if (op == e_view)
    {
        if (read_validation_mp3tag(argc, argv, &info) == SUCCESS)
        {
            printf("View data successfully\n");
            return SUCCESS;
        }
        printf("View data not shown\n");
        return FAILURE;
    }
    else if (op == e_edit)
    {
        if (check_validation_edit(argc, argv, &info) == SUCCESS)
        {
            if (do_edit(argc, argv, &info) == SUCCESS)
            {
                printf("Edit data is Successful\n");
                return SUCCESS;
            }
        }
        printf("ERROR : Edit data not Successful\n");
        return FAILURE;
    }
    else if (op == e_help)
    {
        printf("MP3 Tag Reader\n");
        printf("1. -v -> to view mp3 file contents\n");
        printf("2. -e -> to edit mp3 file contents\n");
        printf("\tEdit tags --> -t/-a/-A/-y/-m/-c\n");
        printf("\t2.1  -t -> to edit song title\n\t2.2  -a -> to edit artist name\n\t2.3  -A -> to edit album name\n\t2.4  -y -> to edit year\n\t2.5  -m -> to edit content\n\t2.6  -c -> to edit comment\n");
        printf("3. --help -> to view help\n");
        return SUCCESS;
    }

    printf("Invalid operation\n");
    return FAILURE;
}

opretion_type check_opretion(char *argv[])
{
    if(strcmp(argv[1],"-v")==0)
    {
        return e_view;
    }
    else if(strcmp(argv[1],"-e")==0){
        return e_edit;
    }
    else if(strcmp(argv[1],"--help")==0)
    {
        return e_help;
    }
    return e_unsupport;
}
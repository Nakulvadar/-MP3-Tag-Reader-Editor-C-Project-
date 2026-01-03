MP3 Tag Reader & Editor
Project Overview
A C-based command-line application to read and edit ID3v2 metadata tags of MP3 audio files. The project safely modifies metadata such as title, artist, album, year, genre, and comments without corrupting the actual audio data, using low-level binary file handling.
Features
•	Read ID3v2 metadata from MP3 files
•	Display tag information in a structured format
•	Edit individual ID3 tags safely
•	Preserve original audio data
•	Temporary file creation during edit operations
•	Command-line interface with validation
Supported ID3 Tags
•	TIT2 – Song Title
•	TPE1 – Artist Name
•	TALB – Album Name
•	TYER – Year
•	TCON – Genre / Content
•	COMM – Comment
How to Run
1. Compile the project:
gcc *.c -o mp3_tag_editor

2. Run the program:
./mp3_tag_editor
Usage
View MP3 Metadata:
./mp3_tag_editor -v sample.mp3

Edit MP3 Metadata:
./mp3_tag_editor -e <option> <new_value> <mp3_file>

Help:
./mp3_tag_editor --help
File Structure
MP3_Tag_Reader_Editor/
├── main.c
├── mp3.h
├── view.c
├── edit.c
├── utils.c
└── README.md
Author
Nakul Anil Vadar
Electronics & Telecommunication Engineering
Embedded & System Programming Enthusiast

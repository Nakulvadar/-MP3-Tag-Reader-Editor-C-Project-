# -MP3-Tag-Reader-Editor-C-Project-
C-based MP3 metadata editor demonstrating binary file handling, endianness conversion, and safe ID3 tag manipulation.
Project Overview
The MP3 Tag Reader & Editor is a command-line based application written in C. It is designed to read and safely modify ID3v2 metadata tags of MP3 audio files without affecting the actual audio data.
Features
- Read ID3v2 metadata from MP3 files
- Display metadata in a structured format
- Edit individual ID3 tags safely
- Preserve original audio data
- Temporary file creation for secure updates
- Command-line interface
Supported ID3 Tags
TIT2  - Song Title
TPE1  - Artist Name
TALB  - Album Name
TYER  - Year
TCON  - Genre
COMM  - Comment
Build Instructions
Compile the source files using GCC:

gcc *.c -o mp3_tag_editor
Usage
View Metadata:
./mp3_tag_editor -v sample.mp3

Edit Metadata:
./mp3_tag_editor -e <option> <new_value> <mp3_file>

Help:
./mp3_tag_editor --help
Advantages
- Prevents MP3 audio corruption
- Modular and readable code
- Demonstrates system-level file handling
- Suitable for academic and interview use
Conclusion
This README describes a system-level MP3 metadata editor implemented in C, demonstrating safe binary file manipulation and structured programming.

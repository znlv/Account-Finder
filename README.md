# Account-Finder

## Overview

**Account-Finder** is a C++ program designed to help you search for social media accounts associated with a given name. It checks platforms such as Facebook, Twitter, Instagram, and YouTube. The program provides the option to export the search results to a text file.

**Disclaimer:** This tool is intended for research purposes only. Use responsibly and within the bounds of legality.

## Features

- Search for social media accounts across Facebook, Twitter, Instagram, and YouTube.
- Export search results to a text file (`social_media_accounts.txt`).
- Detect the existence of social media accounts.
- Extract Facebook ID if available.

## Platforms Supported

- **Facebook**
- **Twitter**
- **Instagram**
- **YouTube**

## Prerequisites

- **Windows OS** (as it uses WinINet API).
- A C++ compiler (e.g., Visual Studio or g++ with MinGW).
  
## Installation

1. Clone the repository or download the source code.
2. Compile the code using your preferred C++ compiler. For example, using `g++` with MinGW:

   ```bash
   g++ -o Account-Finder social_media_finder.cpp -lwininet
   ```

3. Run the compiled program:

   ```bash
   Account-Finder.exe
   ```

## Usage

1. Launch the program.
2. Choose the platform(s) where you want to search for accounts by entering a number corresponding to the platform:
   - 1 for Facebook
   - 2 for Twitter
   - 3 for Instagram
   - 4 for YouTube
   - 5 for searching all platforms.
3. Enter the name you wish to search for.
4. Optionally, export the results to a file (`social_media_accounts.txt`).
5. View the search results and account statuses directly in the terminal or in the output file.

## Example Run

```bash
Choose an option:
1. Search for Facebook accounts
2. Search for Twitter accounts
3. Search for Instagram accounts
4. Search for YouTube accounts
5

. Search for all accounts
6. Exit
Enter your choice: 5
Enter the name to search for social media accounts: JohnDoe
Do you want to export the results to a text file? (y/n): y
Results written to social_media_accounts.txt
```

## Disclaimer

This tool is for **research purposes** only. It is the user's responsibility to ensure that the usage of this tool complies with all applicable laws and regulations. Misuse of this tool is not encouraged.
``` 

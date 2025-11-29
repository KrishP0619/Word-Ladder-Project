# Word-Ladder-Project
This program creates a Word Ladder, which is a sequence of words where only one letter changes at each step, and every intermediate word must be found in the dictionary.  
The program loads a dictionary file, asks the user for two words of the same length, and finds the shortest ladder connecting them.

Step-by-Step Explanation

1. Start the program 
-either do gcc main.c and then ./a.out
- or do make build -> make run 
-either way works for running the program

2. Choose a word length
   - The program counts how many words in the dictionary have that length.  
   - It creates an array containing only words of that size.
   - When prompted, type `dictionary.txt` to use the dictionary.txt file for finding the shortest ladders as that file contains only valid words to be used
   
3.Enter start and final words  
   - The program checks that both words exist in the dictionary.  
   - If not, it will ask again.

4. Build ladders step-by-step  
   - The program takes the current word and tries changing one letter at a time.  
   - If the new word exists in the dictionary and hasn’t been used, it creates a new ladder path with that word added.  
   - This continues until the final word is found or no ladders remain.

5. Output the result  
   - If a ladder exists, the program prints the full word ladder.  
   - If no ladder is possible, it prints a message saying none was found.  
   - All dynamic memory is freed before the program exits.


Video Demonstration: 

https://www.loom.com/share/97022a87ea0043e584ad5341730931ba

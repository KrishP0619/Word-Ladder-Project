#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) { 
    int count = 0;
    FILE* file = fopen(filename,"r");//Opens file in read only mode
    if(file == NULL){//Checks if the file is successfully opened or not
        return -1;//if file is not opened successfully, return -1
    }
    char tempWord[256];//temp string to store word
    //fscanf instead of fgets to parse the words that are seperated from white spaces as
    //a "word" is ANY set of characters that falls between two whitespaces
    while(fscanf(file,"%s",tempWord) == 1){//read in each line of the word into tempWord
        int tempLength = strlen(tempWord);//Store the length of the word we read in
        if(tempLength == wordSize){//compares the length of the word to the wordSize and then increments count if it matches
            count++;
        }
    }
    fclose(file);
    return count; //modify this
}
bool test_countWordsOfLength(){
    int result = countWordsOfLength("testInput.txt",3);
    if(result != 4){
        printf("TEST FAILED, EXPECTED VALUE IS: 4, ACTUAL: %d\n",result);
    } else {
        printf("TEST PASSED FOR COUNT WORDS OF LENGTH\n");
    }
    return true;
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
  //Okay, so memory is already allocated for us, was just messing up on the code.
  FILE* file = fopen(filename,"r");
  if(file == NULL){
    return false;
  }
  int index = 0;
  //Create a temp word string
  char tempWord[256];
  //Scan the firs word in through hte file
  while(fscanf(file,"%s",tempWord)==1){
    //Take the length of the temp word
    int tempLength = strlen(tempWord);
    //If the lenght of the temp word is the word size, then we first check if the current index > wordSize,
    //If so, then we return false, otehrwise, just copy the tempWrod into the words array at the current index
    if(tempLength == wordSize){
        if(index > numWords){
            return false;
        }
    strcpy(words[index],tempWord);
    index++;
    }
  }
  fclose(file);
  if(index == numWords){
    return true;
  } else {
    return false;
  }
}
bool test_buildWordArray(){
    int numWords = 4;
    int wordSize = 3;
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }
    bool result = buildWordArray("testInput.txt",words,numWords,wordSize);
    if(result == true){
        printf("TEST PASSED FOR BUILD WORD ARRAY\n");
    } else {
        printf("TEST FAILED FOR BUILD WORD ARRAY\n");
    }
    return true;
}
int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    while(loInd <= hiInd){
        //Get the middle index by adding the low and high indexes then dividng by 2
        int mid = (loInd + hiInd) / 2;
        //First compare the words to see if they are a match, if they are return the index
        if(strcmp(words[mid],aWord) == 0){
            return mid;
            //If aWord is less than words at the index mid from strcmp, we change the low index to mid + 1
        } else if(strcmp(words[mid],aWord) < 0){
            loInd = mid + 1;
            //If the word is longer than the word at words[mid], change high index to mid - 1
        } else if(strcmp(words[mid],aWord) > 0){
            hiInd = mid - 1;
        }
    }
    return -1; // modify this line
}

bool test_findWord(){
    //Need to make sure I have it where we find the word, and where we dont find a word.
    //to test I can just make an array of how ever many words and just do the calculations for it
    //Have to make sure list is sorted as it is a binary search
    //also words have to be same length
    char* testList[] = {"Hayes","Krish","Patel","Scott","Truck"};
    char* aWord = "Krish";
    int testResult = findWord(testList,aWord,0,4);
    if(testResult == 1){
        printf("TEST PASSED FOR FIND WORD, WORD IS IN THE ARRAY\n");
    } else {
        printf("TEST FAILED: EXPECTED: 1, ACTUAL: %d\n",testResult);
    }
    char* testList2[] = {"Hayes","Rando","Patel","Scott","Truck"};
    testResult = findWord(testList2,aWord,0,4);
    if(testResult == -1){
        printf("TEST PASSED FOR FIND WORD, word is not in the array\n");
    } else {
        printf("TEST FAILED\n");
    }
    return true;
}
void freeWords(char** words, int numWords) {
    for(int i = 0; i < numWords;i++){//Loops through numWords times and frees words[i] and then the words pointer
        free(words[i]);
    }
    free(words);
}

void insertWordAtFront(WordNode** ladder, char* newWord) {
//First create a newNode of WordNode type
WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
//Assign the myWord subitem to the newWord we want to add
newNode->myWord = newWord;
//Assign it's next to the ladder, which is the head of that ladder
newNode->next = *ladder;
//Then assign the head of the ladder to the newNode to insert the new node at the front
*ladder = newNode;
}
bool test_insertWordAtFront(){
    WordNode* testLadder = NULL;
    insertWordAtFront(&testLadder,"Krish");
    insertWordAtFront(&testLadder,"Patel");
        if(strcmp(testLadder->myWord,"Patel") == 0){
            printf("TEST PASSED FOR INSERT AT FRONT\n");
            return true;
        } else {
            printf("TEST FAILED FOR INSERTATFRONT");
            return false;
        }
    //Need to make sure I free
}
int getLadderHeight(WordNode* ladder) {
    //Create a counter
    int count = 0;
    //A new WordNode pointer currentNode to assign it to the ldder
    WordNode* currentNode = ladder;
    //Use currentNode to loop through each node until it hits a null node
    while(currentNode!= NULL){
        //For each iteration increment count and then set currentNode to it's next pointer
        count++;
        currentNode = currentNode->next;
    }
    return count; // modify this line
} 
bool test_getLadderHeight(){
    WordNode* testLadder = NULL;
    insertWordAtFront(&testLadder,"Krish");
    insertWordAtFront(&testLadder,"Patel");
    int testResult = getLadderHeight(testLadder);
    if(testResult == 2){
        printf("TEST PASSED FOR GET LADDER HEIGHT\n");
    } else {
        printf("TEST FAILED FOR GET LADDER: EXPECTED 2, ACTUAL: %d\n",testResult);
    }
    return true;
}
WordNode* copyLadder(WordNode* ladder) {
  // So we need to allocate a new WordNode ladder times.
  // Use a while loop, that goes until ladder is not NULL.
  // Then inside it, we need to allocate a new WordNode each time to and set the
  // subitem to the ladder->myword subitem
  WordNode* copiedList = NULL;
  while (ladder != NULL) {  // loop through word node in ladder
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode)); // Allocate new space for each word
    newNode->myWord = ladder->myWord; //Assign the newWord sub item to the  subitem at the ladder
    newNode->next = NULL; // Assign next to NULL for now.
    // This if statement creates the new list originally, and we dont modify the
    // contents then. copiedList = newNode creates the head of the new copied
    // list, then we modify the next pointers
    if (copiedList == NULL) {
      copiedList = newNode;
    } else {
      // Create a new pointer currentNode and assign it to copiedList.
      // This will point to our copiedList, and we can modify the copiedList
      // with currentNode from the next pointers Since they point to the same
      // memory address, and we aren't changing head,
      WordNode* currentNode = copiedList;
      while (currentNode->next != NULL) {
        currentNode = currentNode->next;
      }
      currentNode->next = newNode;
    }
    ladder = ladder->next;
  }
  return copiedList;  // modify this
}
bool test_copiedLadder(){
    //Edge case, have one where we copy words, and one where it is a null
    WordNode* testLadder = NULL;
    WordNode* copiedLadder = copyLadder(testLadder);
    if(copiedLadder == NULL){
        printf("TEST PASSED, COPIED AN EMPTY LIST\n");
    }else {
        printf("TEST FAILED: COPYLADDER DID NOT PASS\n");
    }
    insertWordAtFront(&testLadder,"Krish");
    copiedLadder = copyLadder(testLadder);
    if(copiedLadder != NULL && strcmp(copiedLadder->myWord,"Krish")==0){
        printf("TEST PASSED: SUCCESSFULLY COPIED LADDER\n");
    } else {
        printf("TEST FAILED: DID NOT COPY LADDER SUCCESSFULYL\n");
    }
    return true;
}


void freeLadder(WordNode* ladder) {
    WordNode* curr = ladder;//Create a pointer for the head of the ladder
    WordNode* temp = NULL;//Create a temp pointer
    while(curr!=NULL){//Keoping until we reach the end
        temp = curr->next;//Set the temp pointer to the next word
        free(curr);//Free the current word
        curr = temp;//Set teh current word to temp which is the next word 
        
    }
}

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
  //Create a newNode that we want to add with the subItem topWord with the newLadder vairable
  LadderNode* newNode = (LadderNode*)malloc(sizeof(LadderNode));
  newNode->topWord = newLadder;
  newNode->next = NULL;
  //I created two pointers, one for currentNode which keeps track of the nodes in the list
  //And a previos node which keeps track of the node behind currentNode
  LadderNode* currentNode = *list;
  LadderNode* previousNode = NULL;
//Iterate currentNode until it hits a NULL, and for each iteration, we assign previousNode to the current iteration
//of currentNode and then assign currentNode to the next next
  while(currentNode != NULL){
    previousNode = currentNode;
    currentNode = currentNode->next;
  }
  //if previousNode == NULL after the while loop ends, that means that the list was empty, so we just insert
  //The new node to the front of list
  if(previousNode == NULL){
    *list = newNode;
  } else {
    //Otherwise, we assign the next pointer of previous node to be the newNode
    previousNode->next = newNode;
  }
}
bool test_insertLadderAtBack(){
    //testList->myWord gets the word for the subitem
    LadderNode* testList = NULL;
    //Create a new word Node used for testing
    WordNode* testLadder = (WordNode*)malloc(sizeof(WordNode));
    testLadder->myWord = "Krish";
    testLadder->next = NULL;

    //First test case to add to the back, but it will add to the front since the list is empty at first
    //Add the testLadder word to the back of the testList, it should be the first word of the list now
    insertLadderAtBack(&testList,testLadder);
        if(strcmp(testList->topWord->myWord,"Krish") == 0 ){
            printf("Test Passed: Succesfully add ladder to the back\n");
        } else{
            printf("Test Failed: Did not add ladder to the back\n");
        }
    WordNode* testLadder2 = (WordNode*)malloc(sizeof(WordNode));
    testLadder2->myWord = "Patel";
    testLadder2->next = NULL;
    //Create a new word and add to the back of the testList, it should now correctly add to the back of the list
    insertLadderAtBack(&testList,testLadder2);
    if(strcmp(testList->next->topWord->myWord, "Patel") == 0){
        printf("Test Passed: Succesfully add ladder to the back\n");
    } else {
        printf("Test Failed: Did not add ladder to the back\n");
    }
}

WordNode* popLadderFromFront(LadderNode** list) {
    LadderNode* head = *list;//Create head pointer that is assigned to *list, which si the first ladder
    WordNode* result = head->topWord;//WordNode* result is a pointer that points to the head node subitem topWord, and we return this
    *list = (*list)->next;//Directly modify the list, NOTE: Doing head = (*list)->next will not work because we modify the local copy then
    free(head);//Free the head which points to the original first ladder
    return result;//Return the pointer of the head subitem.
}
bool test_popLadderFromFront(){
    LadderNode* testList = NULL;
    WordNode* testLadder = NULL;
    insertWordAtFront(&testLadder,"Patel");
    insertWordAtFront(&testLadder,"Krish");
    insertLadderAtBack(&testList,testLadder);
    WordNode* result = popLadderFromFront(&testList);
    if(strcmp(result->myWord,"Krish") == 0){
        printf("TEST PASSED: POP LADDER SUCCESFULLY REMOVED THE FIRST WORD\n");
    } else {
        printf("TEST FAILED: POP LADDER DID NOT REMOVE THE FIRST WORD\n");
    }
    return true;
}

void freeLadderList(LadderNode* myList) {
    LadderNode* curr = myList;//Create a pointer for the head of the ladder
    LadderNode* temp = NULL;//Create a temp pointer
    while(curr!=NULL){//Keep looping until we reach the end
        temp = curr->next;//Set the temp pointer to the next word
        freeLadder(curr->topWord);
        free(curr);//Free the current word
        curr = temp;//Set teh current word to temp which is the next word 
        
    }
}

WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
    //Pass usedWord in by an index to use. it is the same size as the words array
    //So we use findWords to get the index of the word to set true if it is in the array.
    LadderNode* myList = NULL;
    WordNode* myLadder = NULL;
    insertWordAtFront(&myLadder,startWord);
    insertLadderAtBack(&myList,myLadder);
    int startWordIndex = findWord(words,startWord,0,numWords-1);
    if(startWordIndex != -1){
        usedWord[startWordIndex] = true;
    }
    while(myList != NULL){
        WordNode* newLadder = popLadderFromFront(&myList); 
        char* neighborWord = newLadder->myWord;
        //Create a temp variable for comparison, make it +1 so it holds the wordSize and the null character
        //Nested for loop to iterate through each letter and shift it according to J
        for(int i = 0; i < wordSize;i++){
            char tempNeighborWord[wordSize + 1];//Make new temp vairable is size wordSize + 1 for null char
            strcpy(tempNeighborWord,neighborWord);//Copy the original into tempNeighborWord for each new iteration
            for(int j = 0; j < 26;j++){
                char shiftedLetters = 'a' + j;//Shifts letters according to J
                tempNeighborWord[i] = shiftedLetters;//Assigns the char at i to the new shiftedLetter
                //At this point we have the new shifted letter
                //This chekcs if the new shiftedWord is in the words array
                int shiftedWordIndex = findWord(words,tempNeighborWord,0,numWords-1);
                //This checks if the new shiftedWord is in the words array
                //And that the word isn't being used
                if(shiftedWordIndex != -1 && usedWord[shiftedWordIndex] == false) {
                  usedWord[shiftedWordIndex] = true;
                  if(strcmp(tempNeighborWord,finalWord) == 0){
                    insertWordAtFront(&newLadder,words[shiftedWordIndex]);
                    freeLadderList(myList);
                    return newLadder;
                  } else {
                    WordNode* copiedLadder = copyLadder(newLadder);
                    insertWordAtFront(&copiedLadder,words[shiftedWordIndex]);
                    insertLadderAtBack(&myList,copiedLadder);
                  }
                }
            }
        }
        freeLadder(newLadder);
    }
    return NULL;
}


// interactive user-input to set a word; 
//  ensures the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}
bool run_tests(){
    test_countWordsOfLength();
    test_buildWordArray();
    test_findWord();
    test_insertWordAtFront();
    test_getLadderHeight();
    test_copiedLadder();
    test_insertLadderAtBack();
    test_popLadderFromFront();

}

//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main(), except for 
//  testing-related purposes (such as command-line 
//  arguments for "TESTING MODE" to call a test case 
//  master function, or something similar)
//-----------------------------------------------------
int main(int argc, char* argv[]) {
    if(argc > 1 && strcmp(argv[1], "testMode") == 0){
        run_tests();
    }
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}

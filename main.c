/** Created by David Praise Chukwuma Kalu  25/01/2018. **/
/**    Includes     **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**  Constants | Variables**/
enum { gameBoardSpaces = 42 };
char player1[10], player2[10], playerX = 'X', playerO = 'O';
int COLUMN_LENGTH = 7, ROW_LENGTH = 6, UserInput;
const char FILENAME [12] = {"record.txt"};
const char GAMES[15] = {"savedGames.txt"};
char gameBoard [gameBoardSpaces];
int spaceLeft;

typedef struct{
    int id;
    char player1Username [15];
    char player2Username [15];
    char newGameBoard[42];
    int numberOfSpaceLeft;
}UserDetails;

                    /**************First_Part***************/
/** Instructions on how to play the game. **/
void instructions(void){ printf("\nStarting a new game.....\n\n"); printf("Please select an operation from ( 1 - 7 )\n\n"); printf("To win Connect Four you must be the first player to get four of your Symbol in a row either horizontally, vertically or diagonally. \n\n"); }

/** Getting the Users Name. **/
void player_names(){ printf("\nEnter the name of the first player - "); scanf("%s",&(player1)); printf("\nEnter the name of the second player - "); scanf("%s",&(player2)); }

/** Print out to the board **/
void printboard(char array[], int COLUMN_LENGTH, int ROW_LENGTH){
 /** Attempting to create this board
    |  |  |  |  |  |  |  |
    ----------------------
    |  |  |  |  |  |  |  |
    ----------------------
    |  |  |  |  |  |  |  |
    ----------------------
    |  |  |  |  |  |  |  |
    ----------------------
    |  |  |  |  |  |  |  |
    ----------------------
    |  |  |  |  |  |  |  |
    ----------------------
    **/
    char helperArray[ROW_LENGTH][COLUMN_LENGTH]; int counter = 0;
    // Putting all the elements from the 1D-Array into a 2D-Array
    for(int row = 0; row < ROW_LENGTH; row++){ for(int column = 0; column < COLUMN_LENGTH; column++){ helperArray[row][column] = array[counter]; counter++; } }
    // Printing out the board to the console in a matrix format.
    for(int row = 0; row < ROW_LENGTH; row++){ printf("\n"); printf("-----------------------------\n"); for(int column = 0; column < COLUMN_LENGTH; column++){ printf(" %c |",helperArray[row][column]); } }
    printf("\n-----------------------------\n"); printf("1    2   3   4   5   6   7"); printf("\n\n"); //free(array); free(helperArray);
}

/**Custom scan function that only accepts integers **/
float readInput(){ float num; while (scanf("%f",&num) !=1){ while((getchar()!='\n')); printf("Please enter a number\n"); } return num; }

/** Initializing the board with empty space. **/
void settingBoard(char array[]){ for(int i=0; i<gameBoardSpaces; i++){ array[i]= ' '; } }

/** The player making a move.**/
void making_a_move(char array[], char playerSymbol, int inputLocation, int COLUMN_LENGTH){
    int exitLoop = 0, innerLoop = 0, newLocation = inputLocation - 1, SpaceLeft = (COLUMN_LENGTH-1); // takes account to the space left below
    while(exitLoop == 0){
        // place what the user input on that spot of the matrix
            if(array[newLocation+(SpaceLeft*COLUMN_LENGTH)] == 'X' || array[newLocation+(SpaceLeft*COLUMN_LENGTH)] == 'O'){ }
            if(array[newLocation+(SpaceLeft*COLUMN_LENGTH)] == ' '){ array[newLocation+(SpaceLeft*COLUMN_LENGTH)] = playerSymbol; spaceLeft++; exitLoop++; }
            SpaceLeft = SpaceLeft - 1;
    }
}

/** Check if there is a winner during the game. **/
int win(char array[], int COLUMN_LENGTH){
	/** Check vertical axis for a winner. || Check the length of the column + 1 **/
    int winner = 0;
    for(int i=0; i< gameBoardSpaces; i++){
        if(array[i]=='X' && array[i+COLUMN_LENGTH]== 'X' && array[i+(2*COLUMN_LENGTH)]== 'X' && array[i+(3*COLUMN_LENGTH)]=='X'){
            printf("%s has won the game X Vertical!!\n\n", &player1);
            winner = 1;
            break;
        }
        if(array[i]== 'O' && array[i+COLUMN_LENGTH]== 'O' && array[i+(2*COLUMN_LENGTH)]== 'O' && array[i+(3*COLUMN_LENGTH)]=='O'){
            printf("%s has won the game O Vertical!!\n\n", &player2);
            winner = 1;
            break;
       }
    }
	/** Check horizontal axis for a winner.|| Checking line by line for a winner.**/
	for(int i=0; i < gameBoardSpaces; i++){
        if(array[i]=='X' && array[i+1] == 'X' && array[i+2] == 'X' && array[i+3] == 'X'){
            printf("%s has won the game X Horizontal!!\n\n", &player1);
            winner = 1;
            break;
        }
		if(array[i]=='O' && array[i+1] == 'O' && array[i+2] == 'O' && array[i+3] == 'O'){
			printf("%s has won the game O Horizontal!!\n\n", &player2);
            winner = 1;
            break;
		}
	}

    /** check right diagonal**/
    for(int diagA=0; diagA< 25; diagA++){ // The user only has 24 spot to win diagonal.
        if(array[diagA+(COLUMN_LENGTH-1)]=='X' && array[diagA+(2*(COLUMN_LENGTH-1))]== 'X' && array[diagA+(3*(COLUMN_LENGTH-1))]== 'X' && array[diagA+(4*(COLUMN_LENGTH-1))]=='X'){
            winner = 1;
            printf("%s has won the game X Left Diagonal!!\n\n", &player1);
            break;
        }
        if(array[diagA+(COLUMN_LENGTH-1)]=='O' && array[diagA+(2*(COLUMN_LENGTH-1))]== 'O' && array[diagA+(3*(COLUMN_LENGTH-1))]== 'O' && array[diagA+(4*(COLUMN_LENGTH-1))]=='O'){
            winner = 1;
            printf("%s has won the game O Left Diagonal!!\n\n", &player2);
            break;
        }
    }

    /** check left diagonal **/
    for(int diagB=3; diagB<25; diagB++){  // The user only has 24 spot to win diagonal.
        if(array[diagB]=='X' && array[diagB+(COLUMN_LENGTH+1)]=='X' && array[diagB+(2*(COLUMN_LENGTH+1))]== 'X' && array[diagB+(3*(COLUMN_LENGTH+1))]== 'X'){
            winner = 1;
            printf("%s has won the game X Right Diagonal!!\n\n", &player1);
            break;
        }
        if(array[diagB]=='O' &&array[diagB+(COLUMN_LENGTH+1)]== 'O' && array[diagB+(2*(COLUMN_LENGTH+1))]== 'O' && array[diagB+(3*(COLUMN_LENGTH+1))]== 'O'){
            winner = 1;
            printf("%s has won the game O Right Diagonal!!\n\n", &player2);
            break;
        }
    }
	return winner;
}

/** Writing and Reading from the file function**/
void savingGameToFIle(const char *filename, char array [], int gameBoardSpaces){
    FILE *file = fopen(filename, "a+");
    int id = linesInAFile(FILENAME);
    for(int n=0; n<gameBoardSpaces; n++) {
        fprintf(file,"%c",array[n]);
    }
    fprintf(file,"\n");
    fclose(file);
}

/** Read a line in a file, gets it's data, print it out, and return the numbers of empty spaces in that line. **/
int readingSavedGameFromAFileToAnArray(const char *filename, char array [], int arraySize){
    FILE *file = fopen(filename, "r");
    while(EOF){
        for(int n=0; n<arraySize; n++){
            if(array[n] == ' ' || array[n] == 'X' || array[n] == 'O'){
                fscanf(file,"%c",&array[n]);
            }
        }
    }
    printboard(array, COLUMN_LENGTH, ROW_LENGTH);
    fclose(file);
    free(array);
}

/** Players interaction with the board **/
void playersInteraction(int gameBoard, int counter, int isWinner, int UserInput, int innerCaseOneLoop, int id){
        while(innerCaseOneLoop = 1  || isWinner == 0){ //|| counter >= gameBoardSpaces
            /** Player 1 **/
            do{
                printf("\nPlayer 1 please enter an input - "); UserInput = readInput();
                if(UserInput > 0 && UserInput < 8){ printf("Number Accepted ...\n");    }
                else if(UserInput == 0){
                    putAllSavedGamesIntoAFile(GAMES);
                    id = linesInAFile(FILENAME);
                    printf("\nThe game has been saved. ID number - %d\n",id);
                    savingGameToFIle(FILENAME, gameBoard, gameBoardSpaces);
                }
                else{ printf("\nThe number you entered is out of range\n"); }
            }while(UserInput < 1 || UserInput > 7);

            making_a_move(gameBoard, playerX, UserInput, COLUMN_LENGTH);
            printboard(gameBoard, COLUMN_LENGTH, ROW_LENGTH);
            isWinner = win(gameBoard, COLUMN_LENGTH); /** Check if they is a winner in the game. **/
            if(isWinner != 0){ break;  }

            /** Player 2 **/
            do{
                printf("\nPlayer 2 please enter an input - ");  UserInput = readInput();
                if(UserInput > 0 && UserInput < 8){ printf("Number Accepted..\n");  }
                else if(UserInput == 0){
                    putAllSavedGamesIntoAFile(GAMES);
                    id = linesInAFile(FILENAME);
                    printf("\nThe game has been saved. ID number - %d\n",id);
                    savingGameToFIle(FILENAME, gameBoard, gameBoardSpaces);
                }
                else{   printf("\nThe number you entered is out of range\n");   }
            }while(UserInput < 1 || UserInput > 7);

            making_a_move(gameBoard, playerO, UserInput, COLUMN_LENGTH);
            printboard(gameBoard, COLUMN_LENGTH, ROW_LENGTH);
            isWinner = win(gameBoard, COLUMN_LENGTH); /** Check if they is a winner in the game. **/
            if(isWinner != 0){ break; }
            counter += 2; /** Increment the counter by 2 **/
            //if(counter >= gameBoardSpaces){ printf("The board is full. It's a tie.");  break;  }
        }
        spaceLeft = 0;
    }

/** Menu of the game **/
void menu(char gameBoard [], int gameBoardSpaces){
	int option, id=linesInAFile(FILENAME),counter, caseOneLoop=1, innerCaseOneLoop=1, startNewGame, isWinner=0; /** options to choose from the switch case. **/
    printf("\n\n\t\t\tWelcome to connect four.\n\n"); instructions(); printf(" \n\nPlease Enter one of the following options.\n\n 1.) Play a new game \n 2.) Load already saved game\n 3.) Exit the game\n Option <--> ");
    option = readInput(); /** gets integer from the user.**/
    switch(option){
        case 1:
            while(caseOneLoop != 0){
                settingBoard(gameBoard);
                printboard(gameBoard, COLUMN_LENGTH, ROW_LENGTH);
                counter=0;
                player_names(player1,player2);
                playersInteraction(gameBoard,counter, isWinner, UserInput, innerCaseOneLoop, id); /** Interaction between two players **/
                /** When we have a winner or a tie in the game display the below.**/
                printf("\n\nWould you like to go back to start a New Game or go back to the Main Menu\n1) New Game.\n2) Main Menu.\n");
                startNewGame = readInput(); /** Gets users option**/
                if(startNewGame == 1){ innerCaseOneLoop=1;}
                else if(startNewGame == 2){ caseOneLoop=0; break;  }
                else{   printf("\nInvalid input\n");  break;  startNewGame = readInput(); }
            }
            break;
        case 2:
            printf("\nLoading already saved game....\n\n");
            menuCase2(caseOneLoop,startNewGame,counter,isWinner,UserInput,innerCaseOneLoop,id);
            break;
        case 3: printf("\nThank you for playing the game. Hope you enjoyed it.\n\n"); exit(0); break;
        default: printf("\nInvalid Option entered by the user. Please read the Instructions carefully.\n\n"); break;
    }
}

                            /*******Second_Part************/
void menuCase2(int caseOneLoop,int startNewGame,int counter,int isWinner,int UserInput,int innerOneLoop,int id){
    int stayInLoop = 1;
    while(stayInLoop != 0){
        int length = linesInAFile(FILENAME);
        int option; UserDetails info[length];
        printf("\nPlease Select on of the options below-->\n1.) List all saved games\n2.) List all saved games for a particular player\n3.) Show the board of one of the saved games\n4.) Load a game\n5.) Return to main menu\n\n");
        printf("Option -> "); option = readInput();
        switch(option){
        case 1:
            printf("\nListing all saved games..\n");
            printAllDataInFile(GAMES, info , length);
            break;
        case 2:
            printf("\nListing all saved games for a particular player...\n");
            listAllGameDetailOfAParticularPlayer(GAMES, info, length);
            break;
        case 3:
            printf("\nShowing the board of one of the saved games...\n");
            showBoardOfOneOfTheSavedGames(GAMES, FILENAME, info,length);
            break;
        case 4:
            printf("\nLoading a game...\n");
            loadSavedGameWithIdAndStartPlaying(FILENAME, GAMES, info,length,caseOneLoop,startNewGame,counter,isWinner,UserInput,innerOneLoop,id);
            break;
        case 5:
            printf("\nReturn to main menu...\n");
            stayInLoop--;
            break;
        default :
            printf("\nInvalid Entry by the user.\n");
            continue;
        }
    }
}

/** Get the numbers of lines in a file for the ID **/
int linesInAFile(const char *filename){ int lines=1; char ch; FILE *file = fopen(filename,"r"); while((ch=fgetc(file))!=EOF){ if (ch=='\n') { lines++; } }  fclose(file);  return lines;    }

/** Put the ID, X_player, Y_player and Empty space left into a file **/
void putAllSavedGamesIntoAFile(const char *filename){
    int id = linesInAFile(FILENAME);
    int emptySpace = gameBoardSpaces - spaceLeft;
    FILE *file = fopen(filename,"a+");
    fprintf(file,"%d %s %s %d", id, &player1, &player2, &emptySpace);
    fclose(file);
}

/** Print out all the details in the file, for the list of users. **/
void printAllDataInFile(const char *filename, UserDetails x[], int totalLength){
    FILE *file = fopen(filename, "r");
    printf("\n\n******* List of Saved Games ***********\n\n");
    for(int i=0; i<totalLength; i++){
        fscanf(file, "%d %s %s %d" , &x[i].id, &x[i].player1Username, &x[i].player2Username, &x[i].numberOfSpaceLeft);
        printf("Id-%d   Player1-%s   Player2-%s   Spaces-%d\n",x[i].id, x[i].player1Username, x[i].player2Username, x[i].numberOfSpaceLeft);
    }
    fclose(file);
}

/** Print out all the saved games for a particular player.**/
void listAllGameDetailOfAParticularPlayer(const char *filename, UserDetails x[], int totalLength){
    char searchName [15]; int result, result2;
    printf("Please Enter your name - ");
    scanf("%s",&searchName);
    FILE *file = fopen(filename, "r");
    printf("************\n");
    for(int i=0; i<totalLength; i++){
        fscanf(file, "%d %s %s %d" , &x[i].id, &x[i].player1Username, &x[i].player2Username, &x[i].numberOfSpaceLeft);
        result = strcmp(x[i].player1Username, searchName);
        result2 = strcmp(x[i].player2Username, searchName);
        if(result == 0 || result2 == 0) {
            printf("Id-%d   Player1-%s   Player2-%s   Spaces-%d\n",x[i].id, x[i].player1Username, x[i].player2Username, x[i].numberOfSpaceLeft);
        }
    }
    if((result2 > 0 && result2 < 0) || (result > 0 && result < 0)){
        printf("\nThe Name - %s. Not Found\n",searchName);
    }
    fclose(file);
}

/** Display the game details and the board of a particular player **/
void showBoardOfOneOfTheSavedGames(const char *ReadPlayer, const char *filename, UserDetails x[], int totalLength){ //const char *RecordFileName
    int idNumber, n=0, id = linesInAFile(FILENAME);;
    char c;
    char array[gameBoardSpaces];
    printf("Enter an ID of the saved game - ");
    idNumber = readInput();
    settingBoard(array);
    if(idNumber > id){
        printf("\nId number doesn't exist\n");
    }else{
        FILE *file2 = fopen(ReadPlayer,"r");
        for(int i=0; i<totalLength; i++){
            fscanf(file2, "%d %s %s %d" , &x[i].id, &x[i].player1Username, &x[i].player2Username, &x[i].numberOfSpaceLeft);
            if(idNumber == x[i].id) {
                printf("\n ID- %d. -->>> TODAY WE HAVE [ PLAYER1 (' %s ')  VS.  PLAYER2 (' %s ') ] CAN TO SEE THE WINNER. %d EMPTY SPACE LEFT.\n",x[i].id, x[i].player1Username, x[i].player2Username, x[i].numberOfSpaceLeft);
            }
        }
        fclose(file2);

        FILE *file = fopen(filename,"r");
        do{
            fscanf(file, "%c",&c);
            if(c=='\n'){
                n++;
            }
        }while(n < (idNumber-1));

        for(int i=0; i < gameBoardSpaces ; i++){
            printf("%c",c);
            fscanf(file, "%c", &c);
            array[i] = c;
        }
        printboard(array, COLUMN_LENGTH, ROW_LENGTH);
        fclose(file);
    }
}

void loadSavedGameWithIdAndStartPlaying(const char *filename, const char *ReadPlayer, UserDetails x[],int totalLength,int caseOneLoop,int startNewGame,int counter,int isWinner,int UserInput,int innerOneLoop,int id){
 int idNumber, n=0, idFunction = linesInAFile(FILENAME);
    char c;
    char *player[2];
    char array[gameBoardSpaces];
    printf("Enter an ID of the saved game - ");
    scanf("%d",&idNumber);
    settingBoard(array);
    if(idNumber > idFunction){
        printf("\nId number doesn't exist\n");
    }else{
        FILE *file2 = fopen(ReadPlayer,"r");
        for(int i=0; i<totalLength; i++){
            fscanf(file2, "%d %s %s %d" , &x[i].id, &x[i].player1Username, &x[i].player2Username, &x[i].numberOfSpaceLeft);
            if(idNumber == x[i].id) {
                player[0] = x[i].player1Username;
                player[1] = x[i].player2Username;
                printf("\n ID- %d. -->>> TODAY WE HAVE [ PLAYER1 (' %s ')  VS.  PLAYER2 (' %s ') ] CAN TO SEE THE WINNER. %d EMPTY SPACE LEFT.\n",x[i].id, x[i].player1Username, x[i].player2Username, x[i].numberOfSpaceLeft);
                spaceLeft = x[i].numberOfSpaceLeft;
            }
        }
        fclose(file2);

        FILE *file = fopen(filename,"r");
        do{
            fscanf(file, "%c",&c);
            if(c=='\n'){
                n++;
            }
        }while(n < (idNumber-1));

        for(int i=0; i < gameBoardSpaces ; i++){
            printf("%c",c);
            fscanf(file, "%c", &c);
            array[i] = c;
        }
        fclose(file);
        printboard(array, COLUMN_LENGTH, ROW_LENGTH);
        playersInteraction(player[0], player[1],array,counter, isWinner, UserInput, innerOneLoop, id);
    }
}

int main(){
    int OutterExitLoop = 1;
    while(OutterExitLoop != 0){
        menu(gameBoard, gameBoardSpaces);
    }
    return 0;
}

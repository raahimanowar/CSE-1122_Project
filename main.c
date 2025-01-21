#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Player {
    char username[50];
    int quizGame_score;
    int game2_score;
    int game3_score;
};

void saveScore(struct Player player) {
    FILE *file = fopen("scores.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d %d %d\n", 
                player.username, 
                player.quizGame_score, 
                player.game2_score, 
                player.game3_score);
        fclose(file);
    }
}

void displayScore(char username[]) {
    FILE *file = fopen("scores.txt", "r");
    struct Player player = {0}; 
    int found = 0;
    
    strcpy(player.username, username);
    
    if (file != NULL) {
        char stored_username[50];
        int score1, score2, score3;
        
        while (fscanf(file, "%s %d %d %d", 
                stored_username, &score1, &score2, &score3) == 4) {
            if (strcmp(stored_username, username) == 0) {
                player.quizGame_score = score1;
                player.game2_score = score2;
                player.game3_score = score3;
                found = 1;
                break;
            }
        }
        fclose(file);
    }
    
    printf("\n%s scored:\n", username);
    printf("Game 1: %d Points\n", player.quizGame_score);
    printf("Game 2: %d Points\n", player.game2_score);
    printf("Game 3: %d Points\n", player.game3_score);
}

// Quiz Game by Md Raahim Anowar-C243009

struct Question {
    char question[200];
    char options[4][50];  
    char correct_answer;  
};

int playQuizGame() {
    //Questions and answers
    struct Question questions[] = {
        {
            "Who won the battle of 1st Panipat?",
            {"Babur", "Ibrahim", "Sher Shah Suri", "Humayun"},
            'A'
        },
        {
            "Who was the first muslim to led conquest in India?",
            {"Muhammad Ghori", "Muhammad Bin Qasim", "Babur", "Emir Timur"},
            'B'
        },
        {
            "What is the first capital of Bengal Sultanate?",
            {"Sonargaon", "Lakhnauti", "Pandua", "Gaur"},
            'C'
        },
        {
            "Who almost destroyed Ottoman Empire?",
            {"Emir Timur", "Vlad The Impaler", "King of Hungary", "Eskander Beg"},
            'A'
        },
        {
            "Who conqured Spain and establish muslim rule?",
            {"Tariq Bin Ziyad", "Abdul Rahman Al Ghafiqi", "Muhammad Bin Qasim", "Sultan Alauddin"},
            'A'
        }
    };

    int num_questions = sizeof(questions) / sizeof(questions[0]);
    int score = 0;
    char answer;

    printf("\n===== WELCOME TO THE QUIZ GAME =====\n");
    printf("Answer these multiple-choice questions!\n");
    printf("Enter A, B, C, or D for your answer.\n\n");

    for (int i = 0; i < num_questions; i++) {
        printf("\nQuestion %d: %s\n", i + 1, questions[i].question);
        printf("A) %s\n", questions[i].options[0]);
        printf("B) %s\n", questions[i].options[1]);
        printf("C) %s\n", questions[i].options[2]);
        printf("D) %s\n", questions[i].options[3]);

        printf("Your answer: ");
        scanf(" %c", &answer);
        answer = toupper(answer);

        if (answer == questions[i].correct_answer) {
            printf("Correct! Well done!\n");
            score += 1; 
        } else {
            printf("Sorry, that's incorrect. The correct answer was %c.\n", 
                   questions[i].correct_answer);
        }
    }

    printf("\n===== QUIZ COMPLETE =====\n");
    printf("Your final score: %d\n", score);
    
    return score; 
}

//Game launching function
void launchGame(char username[], int gameChoice) {
    printf("\n***** %s is playing Game %d *****\n", username, gameChoice);

    struct Player player = {0}; 
    strcpy(player.username, username); 
    
    // This space is reserved for actual game code
    switch(gameChoice) {
        case 1:
            player.quizGame_score = playQuizGame();
            saveScore(player);
            break;
        case 2:
            // Game 2 code will go here
            break;
        case 3:
            // Game 3 code will go here
            break;
    }
}

//Menu function by Afif-C243017

int main() {
    char username[50];
    char choice;
    
    printf("Good Day! from RetroTriad\n");
    printf("Please enter your username: ");
    scanf("%s", username);
    
    while(1) {
        printf("\nSelect a game %s:\n", username);
        printf("A. Quiz Game\n");
        printf("B. Game 2\n");
        printf("C. Game 3\n");
        printf("# Press X see your score\n");
        printf("# Press Q to quit\n");
        
        scanf(" %c", &choice);
        choice = toupper(choice);  
        
        switch(choice) {
            case 'A':
                launchGame(username, 1);
                break;
            case 'B':
                launchGame(username, 2);
                break;
            case 'C':
                launchGame(username, 3);
                break;
            case 'X':
                displayScore(username);
                break;
            case 'Q':
                printf("Thanks for playing!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
#include <cstdio>
#include <chrono>

enum rps{
    rock = 1,
    paper = 2,
    scissors = 3
};

int rpsWin(const int &currentScore, const rps &choice){
    return currentScore + static_cast<int>(choice) + 6;
}

int rpsLose(const int &currentScore, const rps &choice){
    return currentScore + static_cast<int>(choice);
}

void rpsEvaluate(const char &choiceOne, const char &choiceTwo, int &playerOneScore, int &playerTwoScore){
    rps playerOne;
    rps playerTwo;

    rps *winningChoice = nullptr;
    rps *losingChoice = nullptr;
    int *winningScore = nullptr;
    int *losingScore = nullptr;

    switch(choiceOne){
        case 'A':
            playerOne = rock;
            break;
        case 'B':
            playerOne = paper;
            break;
        case 'C':
            playerOne = scissors;
            break;
        default:
            break;
    }

    switch(choiceTwo){
        case 'X':
            playerTwo = rock;
            break;
        case 'Y':
            playerTwo = paper;
            break;
        case 'Z':
            playerTwo = scissors;
            break;
        default:
            break;
    }

    if(playerOne == playerTwo){
        playerOneScore = playerOneScore + 3 + static_cast<int>(playerOne);
        playerTwoScore = playerTwoScore + 3 + static_cast<int>(playerOne);
    }
    else{
        if(playerOne < playerTwo){
            if(playerOne == rock && playerTwo == scissors){
                winningChoice = &playerOne;
                winningScore = &playerOneScore;
                losingChoice = &playerTwo;
                losingScore = &playerTwoScore;
            }
            else{
                winningChoice = &playerTwo;
                winningScore = &playerTwoScore;
                losingChoice = &playerOne;
                losingScore = &playerOneScore;
            }
        }
        else{
            if(playerOne == scissors && playerTwo == rock){
                winningChoice = &playerTwo;
                winningScore = &playerTwoScore;
                losingChoice = &playerOne;
                losingScore = &playerOneScore;
            }
            else{
                winningChoice = &playerOne;
                winningScore = &playerOneScore;
                losingChoice = &playerTwo;
                losingScore = &playerTwoScore;
            }
        }

        *winningScore = rpsWin(*winningScore, *winningChoice);
        *losingScore = rpsLose(*losingScore, *losingChoice);
    }
}

int main(int argc, char *argv[]){
    auto startTime = std::chrono::high_resolution_clock::now();

    // trying something new, avoiding c++ style streams
    std::FILE *inputFile = std::fopen(argv[1], "r+");

    if(inputFile != 0){
        char choiceOne = ' ';
        char choiceTwo = ' ';

        int playerOneScore = 0;
        int playerTwoScore = 0;

        int buf = 0;
        for(char choice; std::fscanf(inputFile, "%c", &choice) != EOF; ){
            if(choice != '\n'){
                if(choice != ' '){
                    if(buf == 1){
                        choiceTwo = choice;
                        buf = 0;
                    }
                    else{
                        choiceOne = choice;
                        ++buf;
                    }
                }
            }
            // the next character will overwrite choiceOne after this, evaluate score before moving to it
            else{
                rpsEvaluate(choiceOne, choiceTwo, playerOneScore, playerTwoScore);
            }
        }

        std::printf("Your score is: %d!\n"
                    "Your opponent's score is: %d!",
                    playerTwoScore, playerOneScore);

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = endTime - startTime;
        std::printf("Execution time: %f milliseconds", duration.count());

        return 0;
    }

    std::perror("Error");
    return 1;
}

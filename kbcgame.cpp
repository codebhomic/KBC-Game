#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

class Question
{
private:
    string text;
    vector<string> options;
    string correctAnswer;

public:
    Question(string t, vector<string> o, string c)
        : text(t), options(o), correctAnswer(c) {}

    void shuffleOptions()
    {
        std::vector<int> indices = {0, 1, 2, 3};
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);
    }

    void display(int qNumber, string amount)
    {
        cout << "--------------------------------------------------" << endl;
        cout << "Question " << qNumber << " for Rs " << amount << endl;
        cout << "--------------------------------------------------" << endl;
        cout << text << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "a. " << options[0] << endl;
        cout << "b. " << options[1] << endl;
        cout << "c. " << options[2] << endl;
        cout << "d. " << options[3] << endl;
        cout << "--------------------------------------------------" << endl;
    }

    bool checkAnswer(char userChoice)
    {
        int idx;
        if (userChoice == 'a')
            idx = 0;
        else if (userChoice == 'b')
            idx = 1;
        else if (userChoice == 'c')
            idx = 2;
        else if (userChoice == 'd')
            idx = 3;
        else
            return false;

        return options[idx] == correctAnswer;
    }

    string getCorrectAnswer()
    {
        return correctAnswer;
    }
};

class KBCGame
{
private:
    vector<Question> questions;
    vector<string> amounts;
    int currentAmount;

    void displayMessage(string level)
    {
        if (level == "start")
        {
            cout << "\n.....Welcome to Kaun Banega Crorepati....\n";
            cout << "Rules:\n";
            cout << "1. 15 questions with 4 options each.\n";
            cout << "2. Answer correctly to win increasing amounts.\n";
            cout << "3. One wrong answer ends the game with zero amount.\n";
            cout << "4. You can quit anytime.\n\n";
        }
        else if (level == "wrong")
        {
            cout << "Sorry, that's the wrong answer.\n";
        }
        else if (level == "right")
        {
            cout << "Congratulations, your answer is correct!\n";
        }
        else
        {
            cout << "You have quit the game.\n";
        }
    }

public:
    KBCGame(vector<Question> q, vector<string> a)
        : questions(q), amounts(a), currentAmount(0) {}

    void play()
    {
        displayMessage("start");

        char ready;
        cout << "Are you ready to play the game? (y/n): ";
        cin >> ready;
        if (ready == 'n' || ready == 'N')
        {
            displayMessage("");
            return;
        }

        srand(time(0));
        std::vector<int> indices = {0, 1, 2, 3};
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);
        for (auto &q : questions)
        {
            q.shuffleOptions();
        }

        for (size_t i = 0; i < 15 && i < questions.size(); ++i)
        {
            questions[i].display(i + 1, amounts[i]);
            cout << "Enter your answer (a/b/c/d) or q to quit: ";
            string userInput;
            cin >> userInput;

            if (userInput == "q" || userInput == "Q")
            {
                displayMessage("");
                cout << "You have won Rs " << currentAmount << endl;
                return;
            }

            char userChoice = userInput[0];
            if (questions[i].checkAnswer(userChoice))
            {
                displayMessage("right");
                currentAmount = stoi(amounts[i]);
            }
            else
            {
                displayMessage("wrong");
                cout << "Correct answer is: " << questions[i].getCorrectAnswer() << endl;
                cout << "You have not won any amount due to a wrong answer.\n";
                return;
            }

            if (i != 14)
            {
                cout << "Amount won till now: Rs " << currentAmount << endl;
            }
            else
            {
                cout << "Congratulations! You have won Rs " << currentAmount << " by answering all questions.\n";
            }
        }
    }
};

int main()
{
    vector<Question> questionList = {
        Question("Which planet is known as the Red Planet?", {"Venus", "Mars", "Jupiter", "Saturn"}, "Mars"),
        Question("Who wrote the play 'Romeo and Juliet'?", {"William Shakespeare", "Charles Dickens", "Mark Twain", "Jane Austen"}, "William Shakespeare"),
        Question("What is the capital city of Japan?", {"Beijing", "Seoul", "Tokyo", "Bangkok"}, "Tokyo"),
        Question("Which element has the chemical symbol 'O'?", {"Gold", "Oxygen", "Osmium", "Octane"}, "Oxygen"),
        Question("Who was the first President of the United States?", {"Thomas Jefferson", "John Adams", "Benjamin Franklin", "George Washington"}, "George Washington"),
        Question("Which country is known as the Land of the Rising Sun?", {"India", "Japan", "Australia", "China"}, "Japan"),
        Question("What is the largest mammal in the world?", {"Elephant", "Whale Shark", "Blue Whale", "Giraffe"}, "Blue Whale"),
        Question("Who painted the Mona Lisa?", {"Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Claude Monet"}, "Leonardo da Vinci"),
        Question("What is the capital of Australia?", {"Sydney", "Melbourne", "Canberra", "Brisbane"}, "Canberra"),
        Question("In which year did the Titanic sink?", {"1905", "1912", "1918", "1923"}, "1912"),
        Question("Who is known as the Father of the Indian Nation?", {"Jawaharlal Nehru", "Bhagat Singh", "Mahatma Gandhi", "Subhas Chandra Bose"}, "Mahatma Gandhi"),
        Question("What is the hardest natural substance on Earth?", {"Gold", "Iron", "Diamond", "Platinum"}, "Diamond"),
        Question("Which planet is closest to the Sun?", {"Venus", "Earth", "Mercury", "Mars"}, "Mercury"),
        Question("What is the main ingredient in traditional Japanese miso soup?", {"Rice", "Tofu", "Miso paste", "Seaweed"}, "Miso paste"),
        Question("Who invented the telephone?", {"Alexander Graham Bell", "Thomas Edison", "Nikola Tesla", "Guglielmo Marconi"}, "Alexander Graham Bell")};

    vector<string> amounts = {
        "1000", "2000", "3000", "5000", "10000", "20000", "40000", "80000",
        "160000", "320000", "640000", "1250000", "2500000", "5000000", "10000000"};

    KBCGame game(questionList, amounts);

    bool playAgain = true;
    while (playAgain)
    {
        game.play();
        cout << "--------------------------------------------------\n";
        cout << "Do you want to play again? (y/n): ";
        char again;
        cin >> again;
        playAgain = (again == 'y' || again == 'Y');
    }

    cout << "Thank you for playing!\n";
    return 0;
}

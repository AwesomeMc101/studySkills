/*
- studySkills v0.1
- Written by AwesomeMc101 for Lunar Guard LLC
- 5/5/2022

-- TODO --
- More types of learning/studying
- Interactive games
- Quizlet/Quiziz/Kahoot/Gimkit Set Loader
- More user-friendly user-interface
- More secure loading && placing the files in the 'studyset' folder
- Finish preload sets
- Print each question/answer

Feel free to use this code/application, just please credit me (AwesomeMc101)! :)
*/

#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

#include <sstream>
#include <istream>
#include <ostream>
#include <fstream>

#include <math.h>

/*.03*/
#include <chrono>
#include <time.h>

#include "consoleColors.h"

typedef unsigned int CORRECT_COUNT;

/*global vars*/
BOOL isLoaded = FALSE;

int scramble_seed = 0;

int main();

namespace settingsVariables
{
    int clearPerQuestion=0;
}

class err
{
public:
    BOOL error;
    int errorCode;
};

err newErr()
{
    err newError;
    newError.error = FALSE;
    newError.errorCode = 0;

    return newError;
}

class scrambleVector
{
public:
    std::vector<std::string> vec1; //question
    std::vector<std::string> vec2; //answer
    bool errorTrue = false;
};

scrambleVector scrambleVectorNoSeed(std::vector<std::string> vec1, std::vector<std::string> vec2)
{

    scrambleVector finalResult;
    for (int i = 0; i < vec1.size(); i++)
    {
        finalResult.vec1.push_back("");
        finalResult.vec2.push_back("");
    }

    if (finalResult.vec1.size() != vec1.size())
    {
        std::cout << "Scramble Error [vector size mismatch]";
        std::cout << "\nfinalResultV1.size(): " << finalResult.vec1.size();
        std::cout << "\noriginalV1.size(): " << vec1.size();
        finalResult.errorTrue = true;
        return finalResult;
    }

    std::vector<int> magicNumberList;

    for (int i = 0; i < vec1.size(); i++)
    {
        entry:
        int magicNumber = rand() % vec1.size();
        for (int z = 0; z < magicNumberList.size(); z++)
        {
            if (magicNumberList[z] == magicNumber)
            {
                goto entry;
            }
        }

        finalResult.vec1[i] = vec1[magicNumber];
        finalResult.vec2[i] = vec2[magicNumber];
    }

    return finalResult;

}

namespace Import
{

    std::vector<std::string> question;
    std::vector<std::string> answer;

    BOOL isEven(int line)
    {
        //this function should maybe be redone haha
        //It was redone.
        if (line % 2 == 0)
            return TRUE;
        else
            return FALSE;
    }

    BOOL lineInfoChecker()
    {
        if (question.size() == answer.size())
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }


    /////////////////////////////////////////////////////////////////////////


    err load(std::string fileName)
    {
       // std::cout << fileName << std::endl;
        err errorData = newErr();
        std::ifstream file;
        file.open(fileName);
        if (!file)
        {
            errorData.error = TRUE;
            errorData.errorCode = 404;
            return errorData;
        }

        std::string line;
        int lineNumber = 2;
        while (std::getline(file, line))
        {

            if (isEven(lineNumber))
            {
                question.push_back(line);
            }
            else
            {
                answer.push_back(line);
            }
            lineNumber++;
        }

        if (!errorData.error) { isLoaded = TRUE; };
        
        if (lineInfoChecker())
        {
            return errorData; //everything is normal, return;
        }
        
        errorData.error = TRUE;
        errorData.errorCode = 230;

        std::cout << red << "\nThere was a problem loading your file. Please ensure there is an answer for every question." << std::endl;
        return errorData;

        //make more code in case of error pls
    }

    err preloader()
    {
        printf("unfinished");
        err errorData = newErr();
        return errorData;
    }
}

namespace Advanced
{
    //if user did like #456 instead of 456, we need to tell them that!!
    namespace specialChar
    {
        std::string CLEAN_SPECIAL_CHAR(std::string ans) //SPECIAL_CHAR
        {
            ans.erase(remove(ans.begin(), ans.end(), '.'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '/'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '('), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), ')'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), ','), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '|'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '['), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), ']'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '!'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '<'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '>'), ans.end());

            ans.erase(remove(ans.begin(), ans.end(), '$'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '%'), ans.end());
            ans.erase(remove(ans.begin(), ans.end(), '#'), ans.end());
            return ans;
        }

        /*returns true if the user was correct via special char*/
        BOOL checkSpecialChar(std::string input, std::string correctans)
        {
           // std::cout << "checkspecial ret" << (CLEAN_SPECIAL_CHAR(input) == CLEAN_SPECIAL_CHAR(correctans));
            return (CLEAN_SPECIAL_CHAR(input) == CLEAN_SPECIAL_CHAR(correctans));
        }
    }
   
    namespace offBySome
    {
        CORRECT_COUNT isOffBy(std::string input, std::string correctAnswer)
        {
            std::vector<size_t> wrongPositions; //did this incase i ever needed
            if (input.length() == correctAnswer.length())
            {
                CORRECT_COUNT correctChars = 0;
                for (int i = 0; i < correctAnswer.length(); i++)
                {
                    std::cout << "[OFFBY DEBUG A] Compare: " << std::tolower(input[i]) << " | " << std::tolower(correctAnswer[i]) << std::endl;

                    if (std::tolower(input[i]) == std::tolower(correctAnswer[i]))
                    {
                        std::cout << "ATRUE\n";
                        ++correctChars;
                        continue;
                    }
                    std::cout << "AFALSE\n";
                    wrongPositions.push_back(correctAnswer[i]);

                }
                return correctChars;
            }
            else if(input.length() > correctAnswer.length())
            {
                CORRECT_COUNT correctChars = 0;
                for (int i = 0; i < correctAnswer.length(); i++)
                {
                    std::cout << "[OFFBY DEBUG B] Compare: " << std::tolower(input[i]) << " | " << std::tolower(correctAnswer[i]) << std::endl;
                    if (std::tolower(input[i]) == std::tolower(correctAnswer[i]))
                    {
                        std::cout << "BTRUE\n";
                        ++correctChars;
                        continue;
                    }
                    std::cout << "BFALSE\n";
                    wrongPositions.push_back(correctAnswer[i]);

                }
                return correctChars;
            }
            else if(input.length() < correctAnswer.length())
            {
                CORRECT_COUNT correctChars = 0;
                for (int i = 0; i < input.length(); i++)
                {
                    std::cout << "[OFFBY DEBUG C] Compare: " << std::tolower(input[i]) << " | " << std::tolower(correctAnswer[i]) << std::endl;

                    if (std::tolower(input[i]) == std::tolower(correctAnswer[i]))
                    {
                        std::cout << "CTRUE\n";
                        ++correctChars;
                        continue;
                    }
                    std::cout << "CFALSE\n";
                    wrongPositions.push_back(correctAnswer[i]);

                }
                return correctChars;
            }
            else
            {
                return 0xFFF;
            }
        }
    }

    err runAdvanced(std::vector<std::string> _questions, std::vector<std::string> _answers)
    {
        err errorData = newErr();

        scrambleVector scrambledData = scrambleVectorNoSeed(_questions, _answers);

        std::vector<std::string> questions, answers;

        if (scrambledData.errorTrue)
        {
            
            questions = _questions;
            answers = _answers;
        }
        else
        {
            questions = scrambledData.vec1;
            answers = scrambledData.vec2;
        }

        std::cout << "\n";
        system("cls");
        std::cout << blue << "Advanced Learn v.03" << white << std::endl << std::endl;
        if (scrambledData.errorTrue)
        {
            std::cout << "Unscrambled";
        }
        CORRECT_COUNT correctAnswers = 0;
        for (int i = 0; i < questions.size(); i++)
        {

            /*Current completed checks:
            - Casing Problems (no longer a problem)
            - Letter misses
            - Special Character Misses
            */
            std::cout << questions[i] << std::endl;
            std::cout << blue << "Please type your answer: " << white;

            std::string userAnswer;
            

            std::getline(std::cin, userAnswer);
            if (userAnswer == answers[i])
            {
                std::cout << green << "Correct! " << white << "Next question." << std::endl;
                ++correctAnswers;
                continue;
            }
           

            if (specialChar::checkSpecialChar(userAnswer, answers[i]))
            {
                std::cout << green << "Correct, however you were missing a little bit. " << white << "The full answer is "<<answers[i]<<"\nNext question." << std::endl;
                ++correctAnswers;
                continue;
            }

            CORRECT_COUNT correctCharacters = offBySome::isOffBy(userAnswer, answers[i]); //correct chars

            double offbypercent = .50; //this should eventually be found in a settings file

            // (answers[i].length()-correctCharacters)  / answers[i].length(); //this returns the % of missed chars
            //if (((double)correctCharacters / (double)answers[i].length()) > offbypercent)
            std::cout << "Correct %: " << (double)correctCharacters / 100.0;
            if (((double)correctCharacters / 10.0) > offbypercent)
            {
                std::cout << green << "Correct, but you were a little off. " << white << "The full answer is  " << answers[i] << "\nNext question." << std::endl;
                ++correctAnswers;
                continue;
            }

            std::cout << red << "Incorrect. " << white << "The correct answer is " << answers[i] << std::endl;
        }

        double score = (double)correctAnswers / (double)questions.size();

        std::cout << "The learn is over. Your total score was: "<<100*score<<"% (" << correctAnswers << "/" << questions.size() << ")\n";


        return errorData;
    }
}

namespace Basic
{
    err runBasic(std::vector<std::string> questions, std::vector<std::string> answers)
    {
        err errorData = newErr();
        std::cout << "\n";
        system("cls");

        std::cout << blue << "Learn has begun.\n" << white << std::endl;

        CORRECT_COUNT correctAnswers = 0;
  
        for (int i = 0; i < questions.size(); i++)
        {
            std::cout << questions[i] << std::endl;
            std::cout << blue << "Please type your answer: " << white;
            std::string ans;
            std::getline(std::cin, ans);
            if (ans == answers[i])
            {
                std::cout << green << "Correct! "<<white<<"Next question." << std::endl;
                ++correctAnswers;
            }
            else
            {
                std::cout << red << "Incorrect. "<< white << "The correct answer is " << answers[i] << std::endl;
            }
        }

        float score = 100*(correctAnswers / questions.size());

        std::cout << "The learn is over. Your total score was: " << correctAnswers << "/"<<questions.size();

        return errorData;
    }
}

namespace Games
{
    namespace Speed
    {
        void countdown()
        {
            std::cout << "3.. ";
            Sleep(1000);
            std::cout << "2.. ";
            Sleep(1000);
            std::cout << "1.. ";
            Sleep(1000);
        }
        err runSpeed(std::vector<std::string> questions, std::vector<std::string> answers)
        {
            err errorData = newErr();
            std::cout << "\n";
            system("cls");

            std::cout << blue << "Welcome to SpeedTest. When you see the definition, type the answer!" << white << std::endl;
            countdown(); //lol
            std::cout << "Go!\n";

            std::chrono::time_point<std::chrono::system_clock> start;
            std::chrono::time_point<std::chrono::system_clock> end;

            start = std::chrono::system_clock::now(); //get time rn
            int correctAnswers = 0;
            for (int i = 0; i < questions.size(); i++)
            {
                std::string ans="";
                std::cout << questions[i] << std::endl;
                if (ans == answers[i])
                {
                        std::cout << green << "Correct! " << white << "Next question." << std::endl;
                        ++correctAnswers;
                        continue;
                }


                if (Advanced::specialChar::checkSpecialChar(ans, answers[i]))
                {
                  
                    ++correctAnswers;
                    continue;
                }

                CORRECT_COUNT correctCharacters = Advanced::offBySome::isOffBy(ans, answers[i]); //correct chars

                double offbypercent = .50; //this should eventually be found in a settings file

                if (((double)correctCharacters / 10.0) > offbypercent)
                {
                   
                    ++correctAnswers;
                    continue;
                }

            }
            end = std::chrono::system_clock::now();

            std::chrono::duration<double> userTime = end - start;
            std::cout << "Your time was: " << userTime << " seconds. Not bad!\n";
            return errorData;
        }
    }
}

namespace Essential
{
    int askType()
    {
       
       
       // return 0xF7489; //basic (dont use this unless you want your answers to be 100% identical.)
        return 0x657E48; //advanced
    }



    err run(std::vector<std::string> questions, std::vector<std::string> answers)
    {
        err errorData = newErr();
        int type = askType();
        if (type == 0x657E48) //6651464
        {
            //advanced learn
            Advanced::runAdvanced(questions, answers);
        }
        if (type == 0xF7489) //this shouldn't really be used anymore
        {
            Basic::runBasic(questions, answers);
        }

        return errorData;
    }
}

void setseed(int vectorSize)
{
    int random = rand() % 100;
    scramble_seed = random * vectorSize;
}

int main()
{
    srand(time(NULL));
   // scramble_seed = rand() % 6754839 + 1000000;

    std::cout << yellow << "WARNING | SCRAMBLING IS UNFINISHED. PLEASE DISABLE IT TO ALLOW FULL FUNCTIONALITY." << white << std::endl;
    std::cout << "studySkills v.03 | By AwesomeMc101\nIf you want to load a pre-made studyset, type in 'preload'\nIf not, type in the name of the file which should be inside the 'studysets' folder! (example: type 'example.txt')\n";
    std::string fileName = "";
    std::getline(std::cin, fileName);

    if (fileName.empty())
    {
        system("cls");
        std::cout << "Please enter something!" << std::endl;
        Sleep(2000);
        system("cls");
        main();
    }

    if (fileName != "preload") // != for a reason!
    {
        if (!Import::load(fileName).error)
        {
            setseed(Import::question.size());
            if (!Essential::run(Import::question, Import::answer).error)
            {
                main();
            }
        }
        else
        {
            std::cout << red << "ERROR LOADING FILE: " << blue << Import::load(fileName).errorCode << white;

        }
    }
    else
    {
        if (!Import::preloader().error)
        {
            //this should be done by v.03
            //hi from v.04, might discontinue this and just have sets in there that user can load in like normal. we'll see!
        }
    }
    

}


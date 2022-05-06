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

#include "consoleColors.h"

/*global vars*/
BOOL isLoaded = FALSE;

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
        
        std::cout << "break error";
        //make more code in case of error pls
    }

    err preloader()
    {
        printf("unfinished");
        err errorData = newErr();
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

        int correctAnswers = 0;
  
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

        float score = correctAnswers / questions.size();

        std::cout << "The learn is over. Your total score was: " << correctAnswers << "/"<<questions.size();

        return errorData;
    }
}

namespace Essential
{
    int askType()
    {
        std::cout << "Running basic learn\n" << std::endl;
       //advanced learn: return 0x657E48; //fun
        return 0xF7489;
    }



    err run(std::vector<std::string> questions, std::vector<std::string> answers)
    {
        err errorData = newErr();
        int type = askType();
        if (type == 0x657E48)
        {
            //advanced learn
        }
        if (type == 0xF7489)
        {
            Basic::runBasic(questions, answers);
        }

        return errorData;
    }
}

int main()
{
    std::cout << "studySkills v.01 | By AwesomeMc101\nIf you want to load a pre-made studyset, type in 'preload'\nIf not, type in the name of the file which should be inside the 'studysets' folder! (example: type 'example.txt')\n";
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
            Essential::run(Import::question, Import::answer);
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

        }
    }
    

}


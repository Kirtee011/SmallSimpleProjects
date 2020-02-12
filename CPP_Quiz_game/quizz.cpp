#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <Windows.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#define ESCAPE 27

using namespace std;

const char password[6] = "Admin"; //Password to reset highscore
int countr=0; //counts no of correctly answered questions in challenge round
int r, r1, i, n;
int c1 = 1,c = 1;
char choice;
char playername[20];
char guess,C_guess;
float score;
static int count = 1;
int correctly_answered;
int total;
// no of questions in in file
int no_of_warmup_ques=25,no_of_challenge_ques=104;
//question stored in files:
string warmup_filename="warmupRound.txt";
string challenge_filename="challengeRound.txt";
string highscore_filename="highscore.txt";
/*--------------------------------------------------------------------------------------------------------------*/
/*----------------------------------- RECORD SESSIOM START----------------------------------------------------------*/

class Record
{

public:
    void show_record(); // shows the high score
    int reset_score();  //resets highscore
    void help();
    void edit_score(float, char[]);      // just for adding to score.txt
    void edit_high_score(float, char[]); //updates the highscore
};

// function declaration to display
// high score
void Record::show_record()
{
    char rec[50];
    system("cls");
    cout << "\t\t Highscore:\n";
    cout << "\t--------------------------------\n"
         << endl;
    cout << "\t Score" << setw(10) << "Name\n"
         << endl;
    ifstream show;
    show.open(highscore_filename.c_str());
    if (!show)
        return;
    while (!(show.eof()))
    {
        show.getline(rec, 50);
        cout << "\tRs." << rec << endl;
    }
    show.close();
    getch();
}

//function declaration to
//reset the highscore
int Record::reset_score()
{
    string password2;
    system("cls");
    cout << "Enter password:  ";
    cin >> password2;

    if (password == password2)
    {

        cin.clear();
        cin.ignore(1000, '\n');
        char what;
        cout << "Are you sure you want to reset? Y or N :  ";
        cin >> what;
        if (toupper(what) == 'Y')
        {
            ofstream reset;
            reset.open(highscore_filename.c_str(), ios::trunc);
            reset.close();
            cout << "\nReset Complete!\n";
        }
        else
        {
            cout << "\n Reset not done!";
        }

        return 1;
    }
    else
    {
        cout << "\t\t\t Invalid password! \n\n Any key to Enter again! or \n Press esc to return to menu:  ";

        if (getch() == ESCAPE)
        {
            return -13;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        reset_score();
    }

    getch();
}

void Record::edit_score(float score, char name[20])
{
    fstream recordFile;
    recordFile.open("score.txt", ios_base::app);
    recordFile << score << "\t\t" << name << "\n";
    recordFile.close();
}
void Record::edit_high_score(float score, char plnm[20])
{
    system("cls");
    float high_score;
    fstream record;
    record.open(highscore_filename.c_str(), ios::in);
    record >> high_score;
    if (score > high_score)
    {
        record.close();
        record.open(highscore_filename.c_str(), ios::out);
        record << score << setw(10) << plnm;
    }
    record.close();
}

void Record::help()
{
    system("cls");
    cout << "\n\n \t\t\t\t HELP!!!";
    cout << "\n -------------------------------------------------------------------------";
    cout << "\n ************************** C++ Quiz Game***********************************";
    cout << "\n >> There are two rounds in the game, WARMUP ROUND & CHALLANGE ROUND";
    cout << "\n >> In warmup round you will be asked a total of 3 questions to test your general";
    cout << "\n    knowledge. You will be eligible to play the game if you can give atleast 2";
    cout << "\n    right answers otherwise you can't play the Game...........";
    cout << "\n >> Your game starts with the CHALLANGE ROUND. In this round you will be asked";
    cout << "\n    total 10 questions each right answer will be awarded Rs. 100,000.";
    cout << "\n    By this way you can win upto ONE MILLION cash prize...............";
    cout << "\n >> You will be given 4 options and you have to press A, B ,C or D for the";
    cout << "\n    right option";
    cout << "\n >> You will be asked questions continuously if you keep giving the right answers.";
    cout << "\n >> No negative marking for wrong answers";

    cout << "\n\n\t*******************BEST OF LUCK*********************************";
}
/*--------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------RECORD SEDDION END ---------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------- WARMUP SESSION START -------------------------------------------------------*/
class Warmup
{
private:
    string Question;
    string Answer_1;
    string Answer_2;
    string Answer_3;
    string Answer_4;
    char Correct_Answer;

public:
    void Set_Questions(string question, string ans1, string ans2, string ans3, string ans4, char correct_ans)
    {
        Question = question;
        Answer_1 = ans1;
        Answer_2 = ans2;
        Answer_3 = ans3;
        Answer_4 = ans4;
        Correct_Answer = correct_ans;
    }
    void AskQuestion();
};
void Warmup::AskQuestion()
{
    int seconds = 10;
    while (seconds >= 0)
    {
         // display the timer

        system("cls");

        cout << setfill(' ') << setw(55) << "           TIMER         \n";
        cout << setfill(' ') << setw(55) << " --------------------------\n";
        cout << setfill(' ') << setw(43) << seconds << "  " << endl;
        cout << setfill(' ') << setw(55) << " --------------------------\n";

        // displaying the questions
        cout << "\n\n\n";
        cout << "Q" << c << "." << Question << endl;
        cout << "a. " << Answer_1 << endl;
        cout << "b. " << Answer_2 << endl;
        cout << "c. " << Answer_3 << endl;
        cout << "d. " << Answer_4 << "\n\n";
        cout << "Your Answer?" << endl;

        if (kbhit()) // to know if key has been pressed
        {
            cin>>guess;
            guess = tolower(guess);
            break;
                
        }
        // sleep system call to sleep
        // for 1 second
        sleep(1);
        // decrement seconds
        seconds--;
    }

    c++;

    if (seconds == -1)
    {
        cout << " \n Time out !! " << endl;
        getch();
    }
    else if (guess == Correct_Answer)
    {
        cout << "\n CORRECT!!";
        count++;
        getch();
    }
    else
    {
        cout << "\n Wrong Answer!\nThe correct answer is " << Correct_Answer << endl;
        getch();
    }
    return;
}

/*--------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------WARMUP SESSION END----------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------CHALLENGE SESSION END----------------------------------------------------------*/

class Challenge
{
private:
    string Ques;
    string Ans_1;
    string Ans_2;
    string Ans_3;
    string Ans_4;
    char Correct_Ans;

public:
    Challenge(){};
    void Set_Scoring_Ques(string ques, string a1, string a2, string a3, string a4, char correct_a)
    {
        Ques = ques;
        Ans_1 = a1;
        Ans_2 = a2;
        Ans_3 = a3;
        Ans_4 = a4;
        Correct_Ans = correct_a;
    }
    void AskQues();
};

void Challenge::AskQues()
{
    cout << "\n\n\n";
    cout << "Q" << c1 << "." << Ques << endl;
    cout << "a. " << Ans_1 << endl;
    cout << "b. " << Ans_2 << endl;
    cout << "c. " << Ans_3 << endl;
    cout << "d. " << Ans_4 << "\n\n";
    cout << "Your Answer?" << endl;
    cin >> C_guess;

    c1++;
    tolower(C_guess);

    if (C_guess == Correct_Ans)
    {
        cout << "\n CORRECT!!";
        countr++;
        getch();
    }
    else
    {
        cout << "Wrong Answer!\nThe correct answer is " << Correct_Ans << endl;
        getch();
    }
    system("cls");
    score = (float)countr * 100000;
}

/*--------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------CHALLENGE SESSION END----------------------------------------------------------*/

// function to randomly select the question from the file
// this will store the random numbers [upto to no of ques]
// in an array
inline int Random(int number[], int max_no)
{
    int ind = 0;
    srand(time(NULL));
    int store[max_no], r;
    for (int a = 0; a < max_no; a++)
    {
        store[a] = a + 1;
    }
    for (int l = max_no; l > 0; l--)
    {
        r = rand() % l;

        number[ind++] = store[r];
        while (r < l - 1)
        {
            store[r] = store[r + 1];
            r++;
        }
    }

    return 0;
}

void mainhome();
void home(Record);
void game(Record);
void go(Record);
/*--------------------------------------------------------------------------*/
/*--------------------------MAIN FUNCTION STARTS----------------------------*/
int main()
{
    //-------------------for Loading part ----------------------------------//
   /* system("color 0b");

    cout << "\n\n\n\n\t\t\tLOADING...\n\n";
    char a = 177, b = 219;

    cout << "\t\t";
    for (i = 0; i <= 60; i++)
    {
        cout << a;
        cout << "\r";
        cout << "\t";
    }

    for (i = 0; i <= 60; i++)
    {
        cout << b;
        Sleep(80);
    }
    system("color 0f");*/
    //-------------------------------------------------------------------------//
    mainhome();
    return 0;
}
void mainhome()
{
    system("cls");

    cout << "\n\t\t			WELCOME ";
    cout << "\n\t\t			  TO ";
    cout << "\n\t\t			THE GAME " << endl;
    cout << "\n\t\t*******************************************";
    cout << "\n\t\t*******************************************\n";
    cout << "\n\t\t  KO BANCHA CROREPATI  " << endl;
    cout << "\n\t\t*******************************************";
    cout << "\n\t\t*******************************************" << endl;
    cout << "\n\t\t > Press S to start the game";
    cout << "\n\t\t > Press V to view the highest score  ";
    cout << "\n\t\t > Press R to reset score";
    cout << "\n\t\t > press H for help            ";
    cout << "\n\t\t > press Q to quit             ";

    Record e;

    choice = toupper(getch());
    switch (choice)
    {
        case 'V':
            e.show_record();
            getch();
            mainhome();
            break;
        
        case 'H':
            e.help();
            getch();
            mainhome();
            break;
        
        case 'R':
            e.reset_score();
            getch();
            mainhome();
            break;
        
        case 'Q':
            exit(1);
            break;

        case 'S':
            system("cls");

            cout << "\n\n\n\n\n\n\n\n\n\n\t\t\tResister Your Name:";
            gets(playername);

            system("cls");
            cout << "\n ------------------  Welcome " << playername << " to C++ Quiz Game: KO BANCHA CROREPATI --------------------------";
            cout << "\n\n Here are some tips you might wanna know before playing:";
            cout << "\n -------------------------------------------------------------------------";
            cout << "\n >> There are 2 rounds in this Quiz Game, WARMUP ROUND & CHALLANGE ROUND";
            cout << "\n >> In warmup round you will be asked a total of 3 questions to test your";
            cout << "\n    general knowledge. You are eligible to play the game if you give at least 2";
            cout << "\n    right answers, otherwise you can't proceed further to the Challenge Round.";
            cout << "\n >> Your game starts with CHALLANGE ROUND. In this round you will be asked a";
            cout << "\n    total of 10 questions. Each right answer will be awarded RS.100000";
            cout << "\n    By this way you can win upto TEN CRORE cash prize !!!!!..........";
            cout << "\n >> You will be given 4 options and you have to press A, B ,C or D for the";
            cout << "\n    right option.";
            cout << "\n >> You will be asked questions continuously, till right answers are given";
            cout << "\n >> No negative marking for wrong answers!" << endl;
            cout << "\n\n\t!!!!!!!!!!!!! GOOD LUCK !!!!!!!!!!!!!";
            cout << "\n\n\n Press Y to start the game!\n";
            cout << "\n Press any other key to return to the main menu!";

            if (toupper(getch()) == 'Y')
            {
                home(e);
            }

            mainhome();
            system("cls");
            break;
        
        default:
            mainhome();
    }
}
void home(Record e)
{
    Warmup warmup;
    system("cls");
    count = 0;
    int number[no_of_warmup_ques-1];    // the array should be the size of the number of questions in the file
    int j,skip_till = 0; // for gertting to the question in nth line in the file
    string Ques, ans1, ans2, ans3, ans4;
	char correct_ans;

    Random(number, no_of_warmup_ques-1); // random no. generation here
    char line[150];
    for (i = 0; i <= 2; i++)
    {
        skip_till = number[i];
        system("cls");
        // to get to the number[i]th question
        ifstream file_read(warmup_filename.c_str());
        if(!file_read)
        	cout<<"Error";
        else
        {
            for (j = 1; j <= skip_till*6; j++)
            {
                file_read.getline(line, 150);
                //cout<<line<<endl;
            }
            getline(file_read, Ques);
            getline(file_read, ans1);
            getline(file_read, ans2);
            getline(file_read, ans3);
            getline(file_read, ans4);
            file_read>>correct_ans;
        	//setting questions
            warmup.Set_Questions(Ques,ans1,ans2,ans3,ans4,correct_ans);
            //asking questions
            warmup.AskQuestion();
        }
        

    }

    if (count >= 2)
    {
        system("cls");
        cout << "\n\n\t*** CONGRATULATION " << playername << " you are eligible to play the Game ***";
        cout << "\n\n\n\n\t!Press any key to Start the Game!";
        if (getch()!=ESCAPE)
        {
            game(e);
        }
    }
    else
    {
        system("cls");
        printf("\n\n SORRY YOU ARE NOT ELIGIBLE TO PLAY THIS GAME, BETTER LUCK NEXT TIME");
        getch();
        mainhome();
    }
}
void game(Record e)
{
	system("cls");
    Challenge challenge;
	countr = 0;
    int number1[no_of_challenge_ques-1];
    int j,skip_till = 0; // for gertting to the question in nth line in the file
    string Ques, ans1, ans2, ans3, ans4;
	char correct_ans;
    char line[150];
    
    //generaring array with random numbers upto no of challenge questions
	Random(number1, no_of_challenge_ques-1);
    
	for (i = 0; i < 10; i++)
    {
        system("cls");
        skip_till = number1[i];
        // to get to the number[i]th question
        ifstream file_read(challenge_filename.c_str());
        if(!file_read)
        	cout<<"Error";
        else
        {
            for (j = 1; j <= skip_till*6; j++)
            {
                file_read.getline(line, 150);
            }
            getline(file_read, Ques);
            getline(file_read, ans1);
            getline(file_read, ans2);
            getline(file_read, ans3);
            getline(file_read, ans4);
            file_read>>correct_ans;
        	//setting questions
            challenge.Set_Scoring_Ques(Ques,ans1,ans2,ans3,ans4,correct_ans);
            //asking questions
            challenge.AskQues();
        }
    }

    if (score > 0.00 && score < 1000000)
    {
        cout << "\n\n\t\t****************CONGRATULATION *****************";
        cout << "\n\t              You won Rs." << score;
        go(e);
    }

    else if (score == 1000000.0)
    {
        cout << "\n\n\n \t\t****************CONGRATULATION ****************";
        cout << "\n\t\t\t\t YOU ARE A CROREPATI !!!";
        cout << "\n\t\t You won Rs." << score;
        cout << "\t\t Thank You For Playing the Game!!!";
    }

    else
    {
        cout << "\n\n\t********SORRY YOU DIDN'T WIN ANY CASH********";
        cout << "\n\t\t Thank you for your participation";
        cout << "\n\t\t TRY AGAIN :( :(";
        go(e);
    }
}
void go(Record e)
{
    puts("\n\n Press Y if you want to play the next game");
    puts(" Press any key if you want to go to main menu");
    if (toupper(getch()) == 'Y')
    {
        c = 1;
        c1 = 1;
        home(e);
    }

    else
    {
        e.edit_score(score, playername);
        e.edit_high_score(score, playername);
        mainhome();
    }
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <ctype.h>
#include <ctime>


using namespace std;

class Game 
{ 
    public: 
    vector <string> dict;
    int num_words = 0;
    int word_length = 0;
    set <string> user_words;
    string file_name = "list.txt";
    
    void read_file();
    void start();
    char user_in();
    void remove_words();
    void print_last_word();
}; 

void Game::read_file()
{
    string word;
    ifstream read_file_input(file_name);
    //cout << "Reading file: " << file_name << endl;

    while (getline(read_file_input, word))
    {
        dict.push_back(word);
        num_words++;
    }
    read_file_input.close();
}

void Game::start()
{
    cout << "Welcome to Hangman!" << endl;
    read_file();
    //cout << num_words <<" words in the dictionary" << endl;

    srand((unsigned)time(0)); 
    word_length = rand() %(4) + 4;
    cout << "Word Length : " << word_length << endl;

    int attempt = 0;
    while(attempt < 5)
    {
        remove_words();
         attempt++;
    }
    print_last_word();
}

char Game::user_in()
{
  string in;
  int loop_condition = 1;
  do
  {
    cout << "Enter a character:" << endl;
    cin >> in;

    if (in.length() != 1)
    {
      cout << "You have entered more than one character, please try again." << endl;
    }
    else if (!(std::isalpha(in[0])))
    {
      cout << "You have entered an invalid character, please try again." << endl;
    }
    else
    {
      char input = in[0];
      return input;
    }
  }
  while(loop_condition);
}

void Game::remove_words()
{
    char input = user_in();
    string temp;
    int flag = 0;

    for (int i = 0; i < num_words; i++)
    {
        flag = 0; 
        temp = dict[i];

        for (int j = 0; j < temp.length(); j++)
        {
            if (input == temp[j])
            {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
        {
            dict[i] = "0";
        }
    }
}

void Game::print_last_word()
{
    string out;
    for (int i = 0; i < num_words; i++)
    {
        if (dict[i] != "0" && dict[i].length() == word_length)
        {
            cout << "You have lost the game!\nThe word was: " << dict[i] << endl;
            break;
        }
    }
}

int main()
{
    Game new_game;
    new_game.start();
}

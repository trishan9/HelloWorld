#include <iostream>
#include <vector>
using namespace std;

void man(int k);

int main()
{
    // variables
    vector<char> word;
    char temp;
    bool guessed = false;
    vector<int> hit_arr(26, 0);
    vector<int> detection(26, 0);
    int length{0};
    int fails{0};

    // word intialization
    cout << "Please enter the the word (Please refrain from using special characters in the word)(End with ;) \n";
    for (int x = 0;; x++)
    {
        scanf("%c", &temp);
        if (temp == ';')
            break;
        else if (temp == ' ')
            word.push_back(' ');
        else if (temp >= 'a' && temp <= 'z')
            word.push_back(temp - 32);
        else
            word.push_back(temp);
    }
    length = static_cast<int>(word.size());
    for (int x = 0; x < length; x++)
        cout << word[x];

    // hit initialization
    for (int x = 0; x < length; x++)
    {
        detection[(int)(word[x] - 'A')]++;
    }

    // word hide
    for (int x = 0; x < 100; x++)
    {
        cout << endl;
    }
    cout << "Hand over to the player \n";

    // guess
    while (!guessed)
    {
        int run = 0;
        int dashes = 0;
        cout << endl;
        for (int x = 0; x < length; x++)
        {
            if (word[x] == ' ')
                cout << " ";
            else if (hit_arr[word[x] - 'A'] == 0 && detection[word[x] - 'A'] != 0)
            {
                cout << "-";
                dashes++;
            }
            else if (hit_arr[word[x] - 'A'] != 0 && detection[word[x] - 'A'] != 0)
                cout << word[x];
        }
        cout << endl;
        if (dashes == 0)
        {
            guessed = true;
            cout << "CONGRATS!! YOU GUESSED THE WORD!!" << endl;
            break;
        }
        cout << "Player, please enter a letter: ";
        cin >> temp;
        if ((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z'))
        {
            if (temp >= 'a' && temp <= 'z')
                temp = temp - 32;

            if (hit_arr[(int)(temp - 'A')] != 0)
            {
                cout << "Already guessed please enter a new character! \n";
                continue;
            }
            else if (hit_arr[(int)(temp - 'A')] == 0)
            {
                hit_arr[(int)(temp - 'A')]++;
            }
        }
        else
        {
            cout << "Invalid guess try again!!" << endl;
            continue;
        }
        if (detection[temp - 'A'] == 0)
            fails++;
        cout << "\n";
        man(fails);
        cout << endl;
        if (fails == 6)
        {
            guessed = true;
            cout << "You failed to guess the word ";
            for (int y = 0; y < length; y++)
                cout << word[y];
            cout << endl;
        }
    }
}

void man(int k)
{
    if (k == 0)
    {
        cout << "____" << endl;
        cout << "|  |" << endl;
        cout << "|  " << endl;
        cout << "| " << endl;
        cout << "| " << endl;
        cout << "-" << endl;
    }
    else if (k == 1)
    {
        cout << "____" << endl;
        cout << "|  |" << endl;
        cout << "|  O" << endl;
        cout << "| " << endl;
        cout << "| " << endl;
        cout << "-" << endl;
    }
    else if (k == 2)
    {
        cout << "____" << endl;
        cout << "|  |" << endl;
        cout << "|  O" << endl;
        cout << "|  |" << endl;
        cout << "| " << endl;
        cout << "-" << endl;
    }
    else if (k == 3)
    {
        cout << "____" << endl;
        cout << "|  |" << endl;
        cout << "|  O" << endl;
        cout << "| /|" << endl;
        cout << "| " << endl;
        cout << "-" << endl;
    }
    else if (k == 4)
    {
        cout << "____" << endl;
        cout << "|  |" << endl;
        cout << "|  O" << endl;
        cout << "| /|\\" << endl;
        cout << "| " << endl;
        cout << "-" << endl;
    }
    else if (k == 5)
    {
        cout << "____" << endl;
        cout << "|  |" << endl;
        cout << "|  O" << endl;
        cout << "| /|\\" << endl;
        cout << "| / " << endl;
        cout << "-" << endl;
    }
    else if (k == 6)
    {
        cout << "____" << endl;
        cout << "|  |" << endl;
        cout << "|  O" << endl;
        cout << "| /|\\" << endl;
        cout << "| / \\" << endl;
        cout << "-" << endl;
    }
}

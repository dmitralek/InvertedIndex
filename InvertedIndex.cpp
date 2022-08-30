#include <iostream>
#include <fstream>
#include <streambuf>
#include <filesystem>
#include <conio.h>
#include <locale>
#include <string>
#include <map>
#include <vector>
#include <memory>
using namespace std;

template <typename T>
class InvertedIndex
{
public:
    InvertedIndex() {};
    InvertedIndex(T *texts) : texts(texts) {};
    ~InvertedIndex() {};

    T &get(int num);
    void set(T &str, int num);

private:
    T *texts;
};

template <typename T>
T &InvertedIndex<T>::get(int num)
{
    return this->texts[num];
}

template <typename T>
void InvertedIndex<T>::set(T &str, int num)
{
    this->texts[num] = str;
    cout << "Inserted: " << this->texts[num] << endl;
}

void readWords(string &words, vector<string> &allWords);
template <typename T>
void printWords(const vector<T> &allWords);
void searchWords(const vector<string> &allWords, const vector<string> &allTexts, map<string,vector<int>> &invertedIndexDictionary);
void printDictionary(const map<string,vector<int>> &invertedIndexDictionary);

int main()
{
    setlocale(LC_ALL, "Russian");

/*    string *texts = new string [4];
    
    for (int i=0; i < 4; i++)
    {
        cout << "Please, insert a text:" << endl;
        cin >> texts[i];
    }

    InvertedIndex myText(texts);
    cout << "myText: " << myText.get(1) <<endl;
    string change;
    cout << "Text to change: ";
    cin >> change;
    myText.set(change, 2);
    cout << "myText: " << myText.get(2) <<endl;

    delete [] texts;
*/

//    map<string, vector<int>> test = {{"one", {1,2,3}}};

    int stop = 1;
    char num;
    string filename;
    string text;
    string words;
    vector<string> allTexts;
    vector<string> allWords;
    map<string,vector<int>> invertedIndexDictionary;

    cout << "Enter the words: ";
    getline(cin,words);
    readWords(words, allWords);
    printWords(allWords);

    cout << "Do you want to upload texts or isert them?" << endl;
    cout << "1 - Download; 2 - Insert" << endl << "Please, enter the number: ";
    cin >> num;
    cin.ignore();

    switch (num) {
        case '1':
            cout << "Enter the file names:" << endl;
            
            while (getline(cin,filename)) {
                if (filename.empty()) {
                    break;
                }
                ifstream file(filename);
                if (!file) {
                    cout << "No such file!" << endl;
                }
                else {
                    istreambuf_iterator<char> beg{file}, end;
                    string text{beg, end};

                    allTexts.push_back(text);
                    text.clear();
                }
            }
            break;
        case '2':
            while (stop != 0) {
                cout << "Enter text: " << endl;
                getline(cin, text);
                allTexts.push_back(text);
                cout << "Continue?" << endl << "1 - Yes" << endl << "0 - No" << endl;
                cin >> stop;
                cin.ignore();
            }
            break;
    }

    searchWords(allWords, allTexts, invertedIndexDictionary);
    printDictionary(invertedIndexDictionary);

    system("pause");
    return 0;
}

void readWords(string &words, vector<string> &allWords)
{
    size_t j = 0;
    for (size_t i = 0; words[i] != 0; ++i) {
        if (words[i+1] == ' ' || words[i+1] == 0) {
            allWords.push_back(words.substr(j,i+1-j));
            j = i+2;
        }
    };
}

template <typename T>
void printWords(const vector<T> &allWords)
{
    cout << "{ ";
    for (auto j = allWords.begin(); j != allWords.end(); ++j) {
        if ((j+1) != allWords.end())
            cout << *j << ", ";
        else
            cout << *j << " }" << endl;
    }
}

void searchWords(const vector<string> &allWords, const vector<string> &allTexts, map<string,vector<int>> &invertedIndexDictionary)
{
    size_t num;
    for (auto word = allWords.begin(); word != allWords.end(); ++word) {
        num = 1;
        for (auto text = allTexts.begin(); text != allTexts.end(); ++text) {
            if ((*text).find(*word) != string::npos) {
                invertedIndexDictionary[*word].push_back(num);
            }
            ++num;
        }
    }
}

void printDictionary(const map<string,vector<int>> &invertedIndexDictionary)
{
    for (const auto [key, value] : invertedIndexDictionary) {
        cout << key << " : ";
        printWords(value);
    }
}
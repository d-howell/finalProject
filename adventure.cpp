//Dalton Howell
//IN200 Final Project
//Adventure

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR, STOREROOM,
    POOL, GARDEN, POND, PUMPROOM};
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};

enum en_NOUNS {STORE_DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD};


const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 11;
const int VERBS = 8;

const int NOUNS = 6;

//change struct to class
//FINISHED
class Word
{
public:
    //Had to give these default values, as Noun was giving errors, any way i can avoid that?
    Word(string givenWord = "", int givenCode = 0):
        mWord(givenWord),
        mCode(givenCode)
        {}
    string GetWord() const {return mWord;}
    int GetCode() const {return mCode;}
    void SetWord(string givenWord) {mWord = givenWord;}
    void SetCode(int givenCode) {mCode = givenCode;}
private:
    string mWord;
    int mCode;
};

struct room
{
    string description;
    int exits_to_room[DIRS];
};

class Noun : public Word //set noun as a derived class to save myself some work
{
public:
    Noun(string givenWord, int givenCode, string description, int location, bool canCarry):
        mDescription(description), mLocation(location), mCanCarry(canCarry)
        {
            SetWord(givenWord);
            SetCode(givenCode);
        }
        string GetDesc() const {return mDescription;}
        int GetLoc() const {return mLocation;}
        bool GetCarry() const {return mCanCarry;}
        void SetDesc(string desc) {mDescription = desc;}
        void SetLoc(int loc) {mLocation = loc;}
        void SetCarry(bool carry) {mCanCarry = carry;}
private:
    string mDescription;
    int mLocation;
    bool mCanCarry;

};

void set_rooms(room *rms)
{
    rms[SPORTSHOP].description.assign("sports shop");
    rms[SPORTSHOP].exits_to_room[NORTH] = NONE;
    rms[SPORTSHOP].exits_to_room[EAST] = NONE;
    rms[SPORTSHOP].exits_to_room[SOUTH] = CARPARK;
    rms[SPORTSHOP].exits_to_room[NORTH] = NONE;
    
    rms[CASINO].description.assign("bustling casino");
    rms[CASINO].exits_to_room[NORTH] = NONE;
    rms[CASINO].exits_to_room[EAST] = NONE;
    rms[CASINO].exits_to_room[SOUTH] = LOBBY;
    rms[CASINO].exits_to_room[WEST] = NONE;

    rms[CARPARK].description.assign("car park");
    rms[CARPARK].exits_to_room[NORTH] = SPORTSHOP;
    rms[CARPARK].exits_to_room[EAST] = LOBBY;
    rms[CARPARK].exits_to_room[SOUTH] = NONE;
    rms[CARPARK].exits_to_room[WEST] = NONE;

    rms[LOBBY].description.assign("hotel lobby");
    rms[LOBBY].exits_to_room[NORTH] = NONE;
    rms[LOBBY].exits_to_room[EAST] = NONE;
    rms[LOBBY].exits_to_room[SOUTH] = CARPARK;
    rms[LOBBY].exits_to_room[WEST] = NONE;

    rms[RESTAURANT].description.assign("restaurant");
    rms[RESTAURANT].exits_to_room[NORTH] = NONE;
    rms[RESTAURANT].exits_to_room[EAST] = NONE;
    rms[RESTAURANT].exits_to_room[SOUTH] = CARPARK;
    rms[RESTAURANT].exits_to_room[WEST] = NONE;

    rms[CORRIDOR].description.assign("corridor");
    rms[CORRIDOR].exits_to_room[NORTH] = NONE;
    rms[CORRIDOR].exits_to_room[EAST] = NONE;
    rms[CORRIDOR].exits_to_room[SOUTH] = CARPARK;
    rms[CORRIDOR].exits_to_room[WEST] = NONE;

    rms[STOREROOM].description.assign("store room");
    rms[STOREROOM].exits_to_room[NORTH] = NONE;
    rms[STOREROOM].exits_to_room[EAST] = NONE;
    rms[STOREROOM].exits_to_room[SOUTH] = CARPARK;
    rms[STOREROOM].exits_to_room[WEST] = NONE;

    rms[POOL].description.assign("swimming pool area");
    rms[POOL].exits_to_room[NORTH] = NONE;
    rms[POOL].exits_to_room[EAST] = NONE;
    rms[POOL].exits_to_room[SOUTH] = CARPARK;
    rms[POOL].exits_to_room[WEST] = NONE;

    rms[GARDEN].description.assign("tranquil garden");
    rms[GARDEN].exits_to_room[NORTH] = NONE;
    rms[GARDEN].exits_to_room[EAST] = NONE;
    rms[GARDEN].exits_to_room[SOUTH] = CARPARK;
    rms[GARDEN].exits_to_room[WEST] = NONE;

    rms[POND].description.assign("patio with a fish pond");
    rms[POND].exits_to_room[NORTH] = NONE;
    rms[POND].exits_to_room[EAST] = NONE;
    rms[POND].exits_to_room[SOUTH] = CARPARK;
    rms[POND].exits_to_room[WEST] = NONE;

    rms[PUMPROOM].description.assign("damp pump room");
    rms[PUMPROOM].exits_to_room[NORTH] = NONE;
    rms[PUMPROOM].exits_to_room[EAST] = NONE;
    rms[PUMPROOM].exits_to_room[SOUTH] = CARPARK;
    rms[PUMPROOM].exits_to_room[WEST] = NONE;

}

//Change to match new class type Word
//FINISHED
void set_directions(vector<Word>  &dir)
{
    vector<Word>::iterator iter = dir.begin();
    //Used an iterator and insert() so each element is at exact position
    dir.insert(iter+NORTH,Word("NORTH", NORTH));
    dir.insert(iter+EAST,Word("EAST", EAST));
    dir.insert(iter+SOUTH,Word("SOUTH", SOUTH));
    dir.insert(iter+WEST,Word("WEST", WEST));
}
//Change to match new class type Word
//FINISHED
void set_verbs(vector<Word> &vbs)
{
    vector<Word>::iterator iter = vbs.begin();
    //Used an iterator and insert() so each element is at exact position
    vbs.insert(iter+GET,Word("GET", GET));
    vbs.insert(iter+DROP,Word("DROP", DROP));
    vbs.insert(iter+USE,Word("USE", USE));
    vbs.insert(iter+OPEN,Word("OPEN", OPEN));
    vbs.insert(iter+CLOSE,Word("CLOSE", CLOSE));
    vbs.insert(iter+EXAMINE,Word("EXAMINE", EXAMINE));
    vbs.insert(iter+INVENTORY,Word("INVENTORY", INVENTORY));
    vbs.insert(iter+LOOK,Word("LOOK", LOOK));
}
//Change to match class noun
//FINISHED
void set_nouns(vector<Noun> &nns)
{
    vector<Noun>::iterator iter = nns.begin();
    //use iter along with insert to match position to enum value
    nns.insert(iter+STORE_DOOR,Noun("DOOR",STORE_DOOR,"a closed store room door", CORRIDOR, false));
    nns.insert(iter+MAGNET,Noun("MAGNET",MAGNET,"a magnet",NONE,true));
    nns.insert(iter+METER,Noun("METER",METER,"a parking meter",CARPARK,false));
    nns.insert(iter+ROULETTE,Noun("ROULETTE",ROULETTE,"a roulette wheel",CASINO,false));
    nns.insert(iter+MONEY,Noun("MONEY",MONEY,"some money",NONE,true));
    nns.insert(iter+FISHROD,Noun("ROD",FISHROD,"a fishing rod",SPORTSHOP,false));
}
 
void section_command(string Cmd, string &wd1, string &wd2){
    string sub_str;
    vector<string> words;
    char search = ' ';
    size_t i, j;
    cout<<"1";
    for(i=0; i < Cmd.size(); i++)
    {
        if(Cmd.at(i) != search)
        {
            sub_str.insert(sub_str.end(), Cmd.at(i));
        }
        if(i == Cmd.size()-1)
        {
            words.push_back(sub_str);
            sub_str.clear();
        }
        if(Cmd.at(i) == search)
        {
            words.push_back(sub_str);
            sub_str.clear();
        }
    }
    cout<<"2";
    for(i = words.size() - 1; i > 0; i--)
    {
        if(words.at(i) == "")
        {
            words.erase(words.begin() + i);
        }
    }
    cout<<"3";
    for(i = 0; i < words.size(); i++)
    {
        for(j = 0; j < words.at(i).size(); j++)
        {
            if(islower(words.at(i).at(j)))
            {
                words.at(i).at(j) = toupper(words.at(i).at(j));
            }
        }
    }
    cout<<"4";
    if(words.size() == 0)
    {
        cout << "No command given" << endl;
    }
    if(words.size() == 1)
    {
        wd1 = words.at(0);
    }
    if(words.size() == 2)
    {
        wd1 = words.at(0);
        wd2 = words.at(1);
    }
    if(words.size() > 2)
    {
        cout << "Command too long. Only one type or two words (direction or verb and noun)" << endl;
    }
}

void look_around(int loc, room *rms, vector<Word> &dir, vector<Noun> &nns)
{
    int i;
    cout << "I am in a " << rms[loc].description << "." << endl;

    vector<Word>::iterator iter = dir.begin();
    for(i = 0; i < DIRS; i++)
    {
        if(rms[loc].exits_to_room[i] != NONE)
        {
            cout << "There is an exit " << dir[i].GetWord() << " to a " << 
                rms[rms[loc].exits_to_room[i]].description << "." << endl;
        }
    }

    for(i = 0; i < NOUNS; i++)
    {
        if(nns[i].GetLoc() == loc)
        {
            cout << "I see " << nns[i].GetDesc() << "." << endl;
        }
    }
}

bool parser(int &loc, string wd1, string wd2, vector<Word> &dir, vector<Word> &vbs, room *rms, vector<Noun> &nns)
{
    static bool door_state = false;

    int i;
    for(i = 0; i < DIRS; i++)
    {
        if(wd1 == dir[i].GetWord())
        {
            if(rms[loc].exits_to_room[dir[i].GetCode()] != NONE)
            {
                loc = rms[loc].exits_to_room[dir[i].GetCode()];
                cout << "I am now in a " << rms[loc].description << "." << endl;

                if(loc == STOREROOM || loc == CORRIDOR)
                {
                    nns[STORE_DOOR].SetLoc(loc);
                }

                return true;
            }
            else
            {
                cout << "No exit that way." << endl;
                return true;
            }
        }
    }

    int NOUN_MATCH = NONE;
    int VERB_ACTION = NONE;

    for(i = 0; i < VERBS; i++)
    {
        if(wd1 == vbs[i].GetWord())
        {
            VERB_ACTION = vbs[i].GetCode();
            break;
        }
    }

    if(wd2 != "")
    {
        for(i = 0; i < NOUNS; i++)
        {
            if(wd2 == nns[i].GetWord())
            {
                NOUN_MATCH = nns[i].GetCode();
                break;
            }
        }
    }

    if(VERB_ACTION == NONE)
    {
        cout << "No valid command entered." << endl;
        return true;
    }

    if(VERB_ACTION == LOOK)
    {
        look_around(loc, rms, dir, nns);
        return true;
    }

    if(VERB_ACTION == OPEN)
    {
        if(NOUN_MATCH == STORE_DOOR)
        {
            if(loc == CORRIDOR || loc == STOREROOM)
            {
                if(door_state == false)
                {
                    door_state = true;
                    rms[CORRIDOR].exits_to_room[EAST] = STOREROOM;
                    rms[STOREROOM].exits_to_room[WEST] = CORRIDOR;
                    nns[STORE_DOOR].SetDesc("an open store room door");
                    cout << "I have opened the door." << endl;
                    return true;
                }
                else if(door_state == true)
                {
                    cout << "The door is already open." << endl;
                    return true;
                }
            }
            else
            {
                cout << "There is no door to open here." << endl;
                return true;
            }
        }
        else
        {
            cout << "Opening that is not possible." << endl;
            return true;
        }
    }

    return false;
}

int main()
{
    
    string command;
    string word_1;
    string word_2;

    room rooms[ROOMS];
    set_rooms(rooms);
    
    
    vector<Word> directions;
    directions.reserve(DIRS);
    set_directions(directions);

    vector<Word> verbs;
    verbs.reserve(VERBS);
    set_verbs(verbs);

    vector<Noun> nouns;
    nouns.reserve(NOUNS);
    set_nouns(nouns);

    int location = CARPARK;

    while(word_1 != "QUIT")
    {
        command.clear();
        cout << "What shall I do? ";
        getline(cin, command);

        word_1.clear();
        word_2.clear();
        cout<< "test";
        section_command(command, word_1, word_2);
        cout<<"test";
        if(word_1 != "QUIT")
        {
            parser(location, word_1, word_2, directions, verbs, rooms, nouns);
        }

    }

    return 0;
}


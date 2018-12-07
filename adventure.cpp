//Dalton Howell
//IN200 Final Project
//Adventure

/* x = finished
Total ~400 Pts/850 Pts
1. 25 Pts - [x] - Change "struct words" to class
2. 50 Pts - [x] - Change “struct room” to a class
3. 25 Pts - [x] - Change “struct noun” to a class
4. 25 Pts - [x] - Create constructors and destructors for each class.
5. 25 Pts - [] - Create overloaded constructor functions
6. 25 Pts - [x] - Class public/private members
7. 50 Pts - [x] - Use “setters/getters” for private data members
8. 25 Pts - [] - Use a static data member to limit number of objects
9. 50 Pts - [x] - Use constructors to create the objects
10. 25 Pts - [x] - Change rooms array into vectors
11. 25 Pts - [x] - Change directions array into vectors
12. 25 Pts - [x] - Change verbs array into vectors
13. 25 Pts - [x] - Change nouns array into vectors
14. 50 Pts - [] - Re-theme the game
15. 50 Pts - [] - Expand the number of nouns
16. 25 Pts - [] - Expand the number of rooms
17. 25 Pts - [] - Add additional verbs
18. 50 Pts - [x] - Use inheritance with your classes/objects
19. 150 Pts - [] - Enable other action verbs
REQUIRED

20. 50 Pts - [X] - Code Indentation
21. 50 Pts - [x] - Map
*/
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

enum en_DIRS {NORTH, EAST, SOUTH, WEST};
enum en_ROOMS {SPORTSHOP, CASINO, CARPARK, LOBBY, RESTAURANT, CORRIDOR, STOREROOM,
    POOL, GARDEN, POND, PUMPROOM};
enum en_VERBS {GET, DROP, USE, OPEN, CLOSE, EXAMINE, INVENTORY, LOOK};

enum en_NOUNS {DOOR, MAGNET, METER, ROULETTE, MONEY, FISHROD};


const int NONE = -1;
const int DIRS = 4;
const int ROOMS = 11;
const int VERBS = 8;

const int NOUNS = 6;

//change struct word to class
//FINISHED
class Word
{
public:
    //Had to give these default values, as Noun was giving errors, any way i can avoid that?
    Word(string givenWord = "", int givenCode = 0):
        mWord(givenWord),
        mCode(givenCode)
        {}
    ~Word() {}
    string GetWord() const {return mWord;}
    int GetCode() const {return mCode;}
    void SetWord(string givenWord) {mWord = givenWord;}
    void SetCode(int givenCode) {mCode = givenCode;}
private:
    string mWord;
    int mCode;
};
//change struct room to class
//FINISHED
class Room
{
public:
    Room(vector<int> exits,string desc = "an empty room")://multiple constructors in case they want to be constructed different ways
        mDescription(desc),
        mExits(exits)
        {}
    Room(string desc = "an empty room"):
        mDescription(desc)
        {
            mExits.reserve(DIRS);
        }
    Room(string desc = "an empty room", int north = NONE, int east = NONE, int south = NONE, int west = NONE): //will most likely use this one
        mDescription(desc)
        {
            mExits.reserve(DIRS);
            SetExitVec(north, east, south, west);
        }
    ~Room() {}
    string GetDesc() {return mDescription;}
    vector<int> GetExitVec() {return mExits;}
    int GetExit(int dir) {return mExits[dir];}
    void SetDesc(string desc) {mDescription = desc;}
    void SetExit(int dir, int loc)
    {
        mExits.at(dir) = loc;
    }
    void SetExitVec(vector<int> exits)
    {
        mExits = exits;
    }
    void SetExitVec(int north, int east, int south, int west)
    {
        
        vector<int>::iterator iter = mExits.begin();
        mExits.clear();        
        mExits.insert(iter+NORTH,north);
        mExits.insert(iter+EAST,east);
        mExits.insert(iter+SOUTH,south);
        mExits.insert(iter+WEST,west);
    }
private:
    string mDescription;
    vector<int> mExits;
};

//change struct noun to class
//FINISH
class Noun : public Word //set noun as a derived class to save myself some work
{
public:
    Noun(string givenWord, int givenCode, string description, int location, bool canCarry):
        mDescription(description), mLocation(location), mCanCarry(canCarry)
        {
            SetWord(givenWord);
            SetCode(givenCode);
        }
    ~Noun() {}
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
//Change to match new class type Room
//FINISHED
void set_rooms(vector<Room> &rms)
{
    vector<Room>::iterator iter = rms.begin();
    
    rms.insert(iter+SPORTSHOP,Room("sports shop",NONE,NONE,CARPARK,NONE));
    rms.insert(iter+CASINO,Room("bustling casino",NONE,NONE,LOBBY,NONE));
    rms.insert(iter+CARPARK,Room("car park",SPORTSHOP,LOBBY,NONE,NONE));
    rms.insert(iter+LOBBY,Room("hotel lobby",CASINO,RESTAURANT,CORRIDOR,CARPARK));
    rms.insert(iter+RESTAURANT,Room("restaurant",NONE,NONE,NONE,LOBBY));
    rms.insert(iter+CORRIDOR,Room("corridor",LOBBY,NONE,GARDEN,NONE));
    rms.insert(iter+STOREROOM,Room("store room",NONE,NONE,NONE,NONE));
    rms.insert(iter+POOL,Room("swimming pool area",NONE,GARDEN,PUMPROOM,NONE));
    rms.insert(iter+GARDEN,Room("tranquil garden",CORRIDOR,POND,NONE,POOL));
    rms.insert(iter+POND,Room("patio with a fish pond",NONE,NONE,NONE,GARDEN));
    rms.insert(iter+PUMPROOM,Room("damp pump room",POOL,NONE,NONE,NONE));
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
    nns.insert(iter+DOOR,Noun("DOOR",DOOR,"a closed store room door", CORRIDOR, false));
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
    for(i = words.size() - 1; i > 0; i--)
    {
        if(words.at(i) == "")
        {
            words.erase(words.begin() + i);
        }
    }
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

void look_around(int loc, vector<Room> &rms, vector<Word> &dir, vector<Noun> &nns)
{
    int i;
    cout << "I am in a " << rms[loc].GetDesc() << "." << endl;

    vector<Word>::iterator iter = dir.begin();
    for(i = 0; i < DIRS; i++)
    {
        if(rms[loc].GetExit(i) != NONE)
        {
            cout << "There is an exit " << dir[i].GetWord() << " to a " << 
                rms[rms[loc].GetExit(i)].GetDesc() << "." << endl;
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

bool parser(int &loc, string wd1, string wd2, vector<Word> &dir, vector<Word> &vbs, vector<Room> rms, vector<Noun> &nns)
{
    static bool door_state = false;

    int i;
    for(i = 0; i < DIRS; i++)
    {
        if(wd1 == dir[i].GetWord())
        {
            if(rms[loc].GetExit(dir[i].GetCode()) != NONE)
            {
                loc = rms[loc].GetExit(dir[i].GetCode());
                cout << "I am now in a " << rms[loc].GetDesc() << "." << endl;

                if(loc == STOREROOM || loc == CORRIDOR)
                {
                    nns[DOOR].SetLoc(loc);
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
        if(NOUN_MATCH == DOOR)
        {
            if(loc == CORRIDOR || loc == STOREROOM)
            {
                if(door_state == false)
                {
                    door_state = true;
                    rms[CORRIDOR].SetExit(EAST,STOREROOM);
                    rms[STOREROOM].SetExit(WEST,CORRIDOR);
                    nns[DOOR].SetDesc("an open store room door");
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

    vector<Room> rooms;
    rooms.reserve(ROOMS);
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

        section_command(command, word_1, word_2);

        if(word_1 != "QUIT")
        {
            parser(location, word_1, word_2, directions, verbs, rooms, nouns);
        }

    }

    return 0;
}


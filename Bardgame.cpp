
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <ctime> 

#define ARRAY_COUNT(x) (sizeof(*x)/sizeof((*x)[0]))


//Current tasks
//check if a note present in players dictionary return its level
// use in damage function 
//Battle order, chord recognition, card info, 
//instruments implementation, creating characters, implement sound with chuck

enum class BardPower //Powers can be attached to specific chords, if a card includes notes of a specific chord it will provide a power
    // major chord notes can be linked to CONFIDENCEBACK
{
    CONFIDENCEBACK,
    INCREASECHARISMA,
    INCREASEAGILITY,
    INCREASEINTELLECT,
    INCREASELUCK
};

enum class InstrumentEnum
{
    GUITAR,
    LUTE,
    FLUTE,
    DRUM,
    TRUMPLET
};


//Scale enum for using scale in card generation
enum class ScalesEnum {
    MAJOR,
    MINOR_NATURAL,
    MINOR_PENTATONICS
};


struct Chords {

    std::map<std::string, std::vector<int>> major{ {"MAJOR",{1,5,8}} ,
                                                    {"MINOR", { 1,4,8 }}
    };


};

struct NotesHelder {

    std::vector< std::map<std::string, int> > playersNotes;

};



struct Scales {

    std::vector<int> major = { 1,3,5,6,8,10,12 };

public: Scales() {}

      int GetRandomScaleStep(ScalesEnum scale) {

          std::mt19937 mt{};
          switch (scale) {

          case ScalesEnum::MAJOR:
              mt.seed(std::random_device{}());
              return major[mt() % major.size()];
              break;

          }
          return 0;
      }
};

struct Note {
    int position = 1;
    int step = 1;
    int length = 1;
    int level = 1;

public: Note(int positionx = 1, int stepx = 1, int lengthx = 1, int levelx = 1)
{
    position = positionx;
    step = stepx;
    length = lengthx;
    level = levelx;
}
};

struct Card {
    std::vector<Note> notes;
    int baseDamage;

public: Card(std::vector<Note> notesx, int baseDamagex) {

    baseDamage = baseDamagex;
    notes = notesx;
}

      int AverageNoteLevelInCard() {
          int level = 0;
          for (Note n : notes) {
              level += n.level;
          }
          level / notes.size();
      }
};


class Player
{
public:
    std::string name = "Nobody";
    bool isPlayer = true;
    int charisma = 4;
    int agility = 4;
    int intellect = 4;
    int luck = 4;
    int confidence = 100;
    int stamina = 100;
    int ignore = 0;
    int level = 1;
    std::map<std::string, int> notes;
    std::vector<Card> cards;
    BardPower activePowers[10];
    enum InstrumentEnum ins = InstrumentEnum::LUTE;

public: Player(std::string namex, bool isPlayerx, int charismax, int agilityx, int intellectx, int luckx) {
    name = namex;
    isPlayer = isPlayerx;
    charisma = charismax;
    agility = agilityx;
    intellect = intellectx;
    luck = luckx;

    confidence = (charisma + level) * 100;
    stamina = (agility + level) * 100;
    notes = {};
}

      int* ReturnAttrubutes(int sigil[]) {

          int att[4] = { 0,0,0,0 };

          //for (int i = 0; i < sizeof(activePowers); i++)
          //{
          //    switch (activePowers[i]) {
          //    case BardPower::INCREASECHARISMA:
          //        att[0] += 1;
          //        break;
          //    case BardPower::INCREASEAGILITY:
          //        att[1] += 1;
          //        break;
          //    case BardPower::INCREASEINTELLECT:
          //        att[2] += 1;
          //        break;
          //    case BardPower::INCREASELUCK:
          //        att[3] += 1;
          //        break;
          //    default:
          //        break;  
          //    }
          //}

          switch (ins) {
          case InstrumentEnum::GUITAR:
              att[0] += 1;
              break;
          case InstrumentEnum::FLUTE:
              break;
          case InstrumentEnum::DRUM:
              break;
          case InstrumentEnum::TRUMPLET:
              break;
          case InstrumentEnum::LUTE:
              break;
          }

          att[0] = att[0] + charisma + sigil[0];
          att[1] = att[1] + agility + sigil[1];
          att[2] = att[2] + intellect + sigil[2];
          att[3] = att[3] + luck + sigil[3];

          return att;
      }

      int DamageConfidence(float amount) {
          confidence -= amount;
          if (confidence < 0) {
              confidence = 0;
              HandleDeath();
          }
          return confidence;
      }

      int HealConfidence(float amount, int sigils[]) {

          confidence -= amount;
          if (confidence > ReturnAttrubutes(sigils)[0]) {
              confidence = ReturnAttrubutes(sigils)[0];
          }
          return confidence;
      }

      void HandleDeath() {

      }

      int DamageStamina(float amount) {
          stamina -= amount;
          if (stamina < 0) {
              stamina = 0;
          }
          return stamina;
      }

      void LevelUp(Note note) {
          std::string nameNote = std::to_string(note.position) + std::to_string(note.step) + std::to_string(note.length);

          notes[nameNote] = notes[nameNote] + 1;
          std::cout << " player's notes size " << notes.size() << std::endl;
          std::cout << nameNote << " - " << " note int " << notes[nameNote] << std::endl;
      }

      int NoteLevel(Note note) {

          std::string nameNote = std::to_string(note.position) + std::to_string(note.step) + std::to_string(note.length);
          if (notes.find(nameNote) != notes.end()) {
              return notes.find(nameNote)->second;
          }
          else {
              return 1; // if note isn't found
          }
      }
};

class Party {

public: int sigils[4] = { 0,0,0,0 };
public: std::vector<Player> players;

public: Party() {}


      std::vector<Player> BardOrder(Player enemy) {

          std::vector<Player> battleorder;
          /*  int count = 0;
            std::vector<Player> allBattleMembers;
            //allBattleMembers.emplace_back(players);
            allBattleMembers.emplace_back(enemy);
            std::cout << " all members " << allBattleMembers.size();
            */

          return battleorder;
      }
};

int DiceBasedOnLuck(int luck) {
    if (luck < 1)
    {
        std::cout << "luck can't be less than 1" << std::endl;
        luck = 4;
    }
    int dice = 0;
    if (luck > 0 && luck < 10)
    {
        dice = 20;
        return dice;
    }

    if (luck > 9 && luck < 15)
    {
        dice = 12;
        return dice;
    }

    if (luck > 14 && luck < 20)
    {
        dice = 10;
        return dice;
    }

    if (luck > 19 && luck < 25)
    {
        dice = 8;
        return dice;
    }

    if (luck > 24)
    {
        dice = 6;
        return dice;
    }

}

void LevelUp(Note note, std::map<std::string, int> noteLevel) {
    std::string nameNote = std::to_string(note.position) + std::to_string(note.step) + std::to_string(note.length);

    if (noteLevel.contains(nameNote)) {
        noteLevel[std::string(nameNote)] = noteLevel.find(nameNote)->second + 1;
        std::cout << " level up note  " << std::endl;
    }
    else {
        noteLevel[std::string(nameNote)] = 2;
        std::cout << " add new notes  " << std::endl;
    }
    std::cout << " player's notes  " << noteLevel.size() << std::endl;
}

int NoteLevel(Note note, std::map<std::string, int> noteLevel) {

    std::string nameNote = std::to_string(note.position) + std::to_string(note.step) + std::to_string(note.length);
    if (noteLevel.find(nameNote) != noteLevel.end()) {
        return noteLevel.find(nameNote)->second;
    }
    else {
        return 1; // if note isn't found
    }
}
// Core function 
int CalculateLuck(int luck)
{
    int returnLuck = 0;

    returnLuck = (std::rand() % DiceBasedOnLuck(luck)) + 1;
    // std::cout << returnLuck << std::endl;

    return returnLuck;
}

void NoteLevelUp(Player player, Note note) {
    player.LevelUp(note);
    std::cout << player.name << "'s" << " note " << note.position << "-" << note.step << "-" << note.length << "- is leveled up by level " << player.NoteLevel(note) << std::endl;
}

std::vector<Note> FindAChord(std::vector<Note> notes) {
    Chords chord = Chords();
    std::vector<Note> c;

    for (Note n : notes) {
        n.step;
    }
    return c;
}


float DamageCalculation(Player player, int cardBaseDamage, Note note, int sigils[])
{
    float damage = 0;
    int noteDamageRounded = (cardBaseDamage / note.length) * player.NoteLevel(note);
    if (player.stamina > 0) {
        int luckResult = CalculateLuck(player.ReturnAttrubutes(sigils)[3]);
        int dice = DiceBasedOnLuck(player.ReturnAttrubutes(sigils)[3]);
        float damageDiceDivision = (1.0 / (float)dice) * noteDamageRounded;
        float damageLuckResult = damageDiceDivision * luckResult;
        damage = (float)damageLuckResult + ((player.ReturnAttrubutes(sigils)[0]) * 0.3);
        if (luckResult < 3 && player.isPlayer) {

            player.LevelUp(note);
            
        }
        std::cout << player.name << "'s luck result - " << luckResult << std::endl;
    }
    else
    {
        damage = (float)noteDamageRounded * 0.5;
    }
    player.DamageStamina(damage);

    return damage;
}


Card cardMaker(std::vector<Note> notesMap, int baseDamage, int min, int max, ScalesEnum scale) {
    std::vector<Note> notes;
    std::mt19937 mt{};

    int barRange = 0;
    Scales scale_source = Scales();

    while (barRange < 32) {

        if (!notes.empty()) {
            mt.seed(std::random_device{}());
            int r = mt();
            Note n = notesMap[r % notesMap.size()];
            n.step = scale_source.GetRandomScaleStep(scale);
            if (n.length >= min && n.length <= max) {
                if (n.position == barRange && 32 / n.length <= (32 - barRange)) notes.push_back(n);
            }

        }

        if (notes.empty()) {
            mt.seed(std::random_device{}());
            int r = mt();
            Note n = notesMap[r % notesMap.size()];
            n.step = scale_source.GetRandomScaleStep(scale);
            if (n.length >= min && n.length <= max) {
                if (n.position == 1) notes.push_back(n);
            }
        }
        if (!notes.empty()) {
            barRange = 0;
            for (Note n : notes) {
                barRange += (32 / n.length);
            }
        }

    }
    //std::cout << "Notes bar: " << barRange;
    Card card = Card(notes, baseDamage);
    return card;
}




int main(int argc, char const* argv[])
{
    // Card initialization

        //Generate notes up to 8th, make map <int, Note> where int is notes position, tone, length added together as a char converting back to int
    std::mt19937 mt{};
    std::vector<Note> notes;

    for (int pos = 1; pos < 33; pos++) {
        for (int length = 1; length < 16; length++) {
            if (length == 1 || length == 2 || length == 4 || length == 8 || length == 16) {
                if ((32 / length) <= 32 - pos) {
                    Note note = Note(pos, 1, length, 1);
                    notes.push_back(note);
                }
            }
        }
    }

    // Add notes to cards and cards to cards array


    //Initializing players
    Player Player1 = Player("Garry", true, 6, 5, 5, 6);
    for (int i = 0; i < 2; i++) {
        Player1.cards.push_back(cardMaker(notes, 8, 1, 4, ScalesEnum::MAJOR));
    }

    std::map<std::string, int> noteLevelPLayer1;

    Player Player2 = Player("Ami", true, 10, 4, 5, 4);
    for (int i = 0; i < 2; i++) {
        Player2.cards.push_back(cardMaker(notes, 8, 1, 4, ScalesEnum::MAJOR));
    }
    std::map<std::string, int> noteLevelPLayer2;

    std::vector<Player> players;
    players.emplace_back(Player1);
    players.emplace_back(Player2);


    Player enemy = Player("Enemy", false, 8, 4, 6, 7);
    for (int i = 0; i < 4; i++) {
        enemy.cards.push_back(cardMaker(notes, 8, 1, 4, ScalesEnum::MAJOR));
    }
    players.emplace_back(enemy);
    std::map<std::string, int> noteLevelEnemy;

    NotesHelder notesHolder;
    notesHolder.playersNotes = { noteLevelPLayer1, noteLevelPLayer2, noteLevelEnemy };


    int sigils[4] = { 1,0,0,0 };

    //std::cout << " player's notes  " << players[0].notes.size() << std::endl;
    //players[0].LevelUp(Note(1, 1, 1, 1));
    //players[0].LevelUp(Note(2, 2, 2, 2));
    //players[0].LevelUp(Note(2, 2, 2, 2));
    //for (auto n : players[0].notes) {
    //    std::cout << " loop through notes" << n.second << std::endl;
    //}


    while (true)
    {
        int n = 0, c = 0;
        for (int i = 1; i <= players.size(); i++) {
            std::cout << i << ". " << players[i - 1].name << " // ";
        }
        std::cout << "Choose player ";
        std::cin >> n;
        n -= 1;
        if (players[n].isPlayer) {
            std::cout << "Player has " << players[n].cards.size() << " cards \n";
            std::cout << "Choose card ";
            std::cin >> c;
            float damage = 0;
            for (Note note : players[n].cards[c].notes) {
                damage += DamageCalculation(players[n], players[n].cards[c].baseDamage, note, sigils);
                enemy.DamageConfidence(damage);
                players[n].DamageStamina(damage * 0.5);
                std::cout << "Note position: " << note.position << " length: " << note.length << " step: " << note.step << std::endl;
                std::cout << players[n].name << " damages " << enemy.name << " on " << damage << " amount " << ", stamina left " << players[n].stamina << std::endl;
                std::cout << "Opponent confidence is " << enemy.confidence << std::endl;
                //std::cout << "check stamina is change" << players[n].stamina << std::endl;
                //std::system("pause");
            }
        }
        else {
            //auto attack of a enemy
            mt.seed(std::random_device{}());
            int r = mt();
            int ran = r % players[n].cards.size();

            mt.seed(std::random_device{}());
            int rndPlayer = mt() % players[n].cards.size();


            float damage = 0;
            for (Note note : players[n].cards[ran].notes) {
                damage += DamageCalculation(players[n], players[n].cards[ran].baseDamage, note, sigils);
                players[rndPlayer].DamageConfidence(damage);
                players[n].DamageStamina(damage * 0.5);
                std::cout << "Note position: " << note.position << " length: " << note.length << " step: " << note.step << std::endl;
                std::cout << players[n].name << " damages " << enemy.name << " on " << damage << " amount " << ", stamina left " << players[n].stamina << std::endl;
                std::cout << "Opponent confidence is " << enemy.confidence << std::endl;
                //std::cout << "check stamina is change" << players[n].stamina << std::endl;
                //std::system("pause");
            }
        }
    }
    return 0;
}

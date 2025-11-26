#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

void die(string s = "INVALID INPUT!") {
	cout << s << endl;
	exit(EXIT_FAILURE);
}

//Holds info for a single species of Pokemon, such as Pikachu
class Pokemon {
	/*private:
	string name;
	string type1;
	string type2;
	int index;
	int generation;
	int hp;
	int def;
	int attk;
	int spdf;
	int spAttk;
	int speed;
	bool legendary*/
  public:
	//YOU: Add member variable ints for each of the following:
	//index - what index it is in the pokedex
	//name (this is a string not an int)
	//hp - how much damage it takes before dying fainting
	//attack - this number gets multiplied by the move's power to determine damage
	//defense - incoming damage gets divided by this number
	//special attack - like attack but for special moves
	//special defense - like defense but for special moves
	//speed - whichever pokemon has the highest speed attacks first, flip a coin on a tie
	//generation - when the pokemon was released
	//legendary - if it is a legendary or not
	//YOU: Add member variables of type string for type1 and type2
	string name;
	string type1;
	string type2;
	int index;
	int generation;
	int total;
	int hp;
	int def;
	int attk;
	int spdf;
	int spAttk;
	int speed;
	bool legendary;
	Pokemon() {
		index = -1;
		name = "none";
		type1 = "none";
		type2 = "";
		hp = -1;
		attk = -1;
		def = -1;
		spdf = -1;
		spAttk = -1;
		speed = -1;
		legendary = false;
		generation = -1;
	}
	/*Pokemon(int pEntry, string pokemonName, string type, int HP, int attack, int defense, int spDefense, int spAttack, int spd, int gen, bool isL) {
		index = pEntry;
		name = pokemonName;
		type1 = type;
		hp = HP;
		def = defense;
		spdf = spDefense;
		spAttk = spAttack;
		speed = spd;
		legendary = isL;
		generation = gen;
	}
	Pokemon(int pEntry, string pokemonName, string fstType, string sndType, int HP, int attack, int defense, int spDefense, int spAttack, int spd, int gen, bool isL) {
		index = pEntry;
		name = pokemonName;
		type1 = fstType;
		type2 = sndType;
		hp = HP;
		attk = attack;
		def = defense;
		spdf = spDefense;
		spAttk = spAttack;
		speed = spd;
		legendary = isL;
		generation = gen;
	}*/
	void printTest() {
		cout << index << name << type1;
		if (type2 != "none") {
			cout << type2;
		}
		cout << hp << attk << def << spdf << spAttk << speed << legendary << generation << endl;
	}
	/*Pokemon(int pEntry, string firstName, string lastName, string fstType, string sndType, int HP, int attack, int defense, int spDefense, int spAttack, int spd, int gen, bool isL) {
	    temp = firstName;
		temp.append(" ");
		temp.append(lastName);
		index = pEntry;
	    name =;
	    type1 = fstType;
	    type2 = sndType;
	    hp = HP;
	    def = defense;
	    spdf = spDefense;
	    spAttk = spAttack;
	    speed = spd;
	    legendary = isL;
	    generation = gen;
		}*/
};

//This class holds a record for each move in the game
class Move {
  public:
	//YOU: Add member variable for each of these:
	//int index, string name, string type, string category, int PP, int power, int accuracy
	int index;
	string name;
	string type;
	string category;
	int PP;
	int power;
	int accuracy;
	Move() {
		index = -1;
		name = "none";
		type = "none";
		category = "none";
		PP = -1;
		power = -1;
		accuracy = -1;
	}
};

bool isType(string temp) {
	if (temp == "Normal" || temp == "Steel" || temp == "Fire" || temp == "Water" || temp == "Grass" || temp == "Fairy" || temp == "Electric" || temp == "Rock" || temp == "Ground" || temp == "Flying" || temp == "Dragon" || temp == "Ice" || temp == "Dark" || temp == "Ghost" || temp == "Psychic" || temp == "Fighting" || temp == "Bug" || temp == "Poison") {
		return true;
	} else {
		return false;
	}
}
vector <Pokemon> pokeList(string fileName) {
	string line;
	string temp;
	istringstream item;
	ifstream file(fileName);
	getline(file, line);
	vector <Pokemon> tempVec;
	while (getline(file, line)) {
		Pokemon pokemon;
		item.str(line);
		//item >> temp;
		getline(item, temp, ',');
		pokemon.index = stoi(temp);
		getline(item, temp, ',');
		pokemon.name = temp;
		getline(item, temp, ',');
		while (!isType(temp)) {
			temp.insert(0, " ");
			pokemon.name.append(temp);
			getline(item, temp, ',');
		}
		pokemon.type1 = temp;
		getline(item, temp, ',');
		if (temp == "—") {
			pokemon.type2 = "";
		} else {
			pokemon.type2 = temp;
		}
		getline(item, temp, ',');
		pokemon.total = stoi(temp);
		getline(item, temp, ',');
		pokemon.hp = stoi(temp);
		getline(item, temp, ',');
		pokemon.attk = stoi(temp);
		getline(item, temp, ',');
		pokemon.def = stoi(temp);
		getline(item, temp, ',');
		pokemon.spAttk = stoi(temp);
		getline(item, temp, ',');
		pokemon.spdf = stoi(temp);
		getline(item, temp, ',');
		pokemon.speed = stoi(temp);
		getline(item, temp, ',');
		pokemon.generation = stoi(temp);
		getline(item, temp, ',');
		if (temp == "True") {
			pokemon.legendary = true;
		} else {
			pokemon.legendary = false;
		}
		tempVec.push_back(pokemon);
		item.clear();
	}
	return tempVec;
}

vector <Move> moveList(string fileName) {
	string line;
	string temp;
	istringstream item;
	ifstream file(fileName);
	vector <Move> customMove;
	while (getline(file, line)) {
		Move move;
		item.str(line);
		item >> temp;
		move.index = stoi(temp);
		item >> temp;
		move.name = temp;
		item >> temp;
		while (!isType(temp)) {
			temp.insert(0, " ");
			move.name.append(temp);
			item >> temp;
		}
		move.type = temp;
		item >> temp;
		move.category = temp;
		item >> temp;
		move.PP = stoi(temp);
		item >> temp;
		if (temp != "—") {
			move.power = stoi(temp);
		}
		item >> temp;
		if (temp != "—") {
			temp.replace(temp.find("%"), 1, "");
			move.accuracy = stoi(temp);
		}
		customMove.push_back(move);
		item.clear();
	}
	return customMove;
}

int main() {
	string temp;
	string move;
	string currentLine;
	istringstream curr;
	bool last;
	int prevIndex = -10;
	ifstream pokedex("/public/pokemon.csv");
	ifstream moves("/public/moves.txt");
	//system("figlet POKEMON");
	//system("figlet ++ and \\#");
	//cout << "Do you want to use the default files? (Type \"NO\" for no, anything else for yes.)\n";

	//YOU: Load files for all pokemon and moves, and put them into these vectors:
	vector<Pokemon> pokemon_db; //Holds all pokemon known
	vector<Move> move_db; //Holds all the moves we know
	getline(pokedex, temp);//grabs first useless line
	//getline(moves, move);
	//cout << move << endl;
	//moves >> move;
	//cout << move << endl;

	while (getline(moves, move)) {
		Move currentMove;
		curr.str(move);
		curr >> temp;
		currentMove.index = stoi(temp);
		//cout << temp << endl;//here
		curr >> temp;
		currentMove.name = temp;
		curr >> temp;
		if (isType(temp)) {
			//cout << temp << endl;
			currentMove.type = temp;
			curr >> temp;
			currentMove.category = temp;
			curr >> temp;
			currentMove.PP = stoi(temp);
			//cout << temp << endl;//here
			curr >> temp;
			//cout << temp << endl;
			if (temp != "—") {
				currentMove.power = stoi(temp);
			}
			curr >> temp;
			if (temp != "—") {
				temp.replace(temp.find("%"), 1, "");
				currentMove.accuracy = stoi(temp);
				//cout << temp << endl;
			}
		} else {
			temp.insert(0, " ");
			currentMove.name.append(temp);
			curr >> temp;
			if (isType(temp)) {
				currentMove.type = temp;
			} else {
				temp.insert(0, " ");
				currentMove.name.append(temp);
				curr >> temp;
				currentMove.type = temp;
			}
			curr >> temp;
			currentMove.category = temp;
			curr >> temp;
			currentMove.PP = stoi(temp);
			//cout << temp << endl;//here
			curr >> temp;
			//cout << temp << endl;
			if (temp != "—") {
				currentMove.power = stoi(temp);
			}
			curr >> temp;
			if (temp != "—") {
				temp.replace(temp.find("%"), 1, "");
				currentMove.accuracy = stoi(temp);
				//cout << temp << endl;
			}

		}
		move_db.push_back(currentMove);
		curr.clear();
	}

	for (int i = 0; i < 721; i++) {
		Pokemon pokemon;
		getline(pokedex, currentLine);
		while (currentLine.find(" ") != string::npos) {
			currentLine.replace(currentLine.find(" "), 1, "");
		}
		curr.str(currentLine);
		getline(curr, temp, ',');
		pokemon.index = stoi(temp);
		if (prevIndex == stoi(temp)) {
			i = i - 1;
			continue;
		}
		prevIndex = stoi(temp);
		getline(curr, temp, ',');
		pokemon.name = temp;
		getline(curr, temp, ',');
		pokemon.type1 = temp;
		getline(curr, temp, ',');
		if (!temp.empty()) {
			pokemon.type2 = temp;
			getline(curr, temp, ',');
			pokemon.total = stoi(temp);
			getline(curr, temp, ',');
			pokemon.hp = stoi(temp);
			getline(curr, temp, ',');
			pokemon.attk = stoi(temp);
			getline(curr, temp, ',');
			pokemon.def = stoi(temp);
			getline(curr, temp, ',');
			pokemon.spAttk = stoi(temp);
			getline(curr, temp, ',');
			pokemon.spdf = stoi(temp);
			getline(curr, temp, ',');
			pokemon.speed = stoi(temp);
			getline(curr, temp, ',');
			pokemon.generation = stoi(temp);
			getline(curr, temp, ',');
			if (temp == "True") {
				pokemon.legendary = true;
			} else {
				pokemon.legendary = false;
			}
		} else {
			getline(curr, temp, ',');
			pokemon.total = stoi(temp);
			getline(curr, temp, ',');
			pokemon.hp = stoi(temp);
			getline(curr, temp, ',');
			pokemon.attk = stoi(temp);
			getline(curr, temp, ',');
			pokemon.def = stoi(temp);
			getline(curr, temp, ',');
			pokemon.spAttk = stoi(temp);
			getline(curr, temp, ',');
			pokemon.spdf = stoi(temp);
			getline(curr, temp, ',');
			pokemon.speed = stoi(temp);
			getline(curr, temp, ',');
			pokemon.generation = stoi(temp);
			getline(curr, temp, ',');
			if (temp == "True") {
				pokemon.legendary = true;
			} else {
				pokemon.legendary = false;
			}
		}
		pokemon_db.push_back(pokemon);
		curr.clear();
		//pokemon_db.at(i).printTest();
	}
	int userInput = 0;
	string input;
	//YOU: Ask the user if they want to look up a Pokemon or a Move
	//cout << "Do you want to look up a Pokemon or a Move?" << endl;
	vector <string> titleCard = {
		R"( ____   ___  _  _______ __  __  ___  _   _ )",
		R"(|  _ \ / _ \| |/ / ____|  \/  |/ _ \| \ | |)",
		R"(| |_) | | | | ' /|  _| | |\/| | | | |  \| |)",
		R"(|  __/| |_| | . \| |___| |  | | |_| | |\  |)",
		R"(|_|    \___/|_|\_\_____|_|  |_|\___/|_| \_|)",
		R"(                                           )",
		R"(                               _     _  _   )",
		R"(   _     _      __ _ _ __   __| |  _| || |_ )",
		R"( _| |_ _| |_   / _` | '_ \ / _` | |_  ..  _|)",
		R"(|_   _|_   _| | (_| | | | | (_| | |_      _|)",
		R"(  |_|   |_|    \__,_|_| |_|\__,_|   |_||_|  )",
		"                                            "
	};
	for (int i = 0; i < titleCard.size(); i++) {
		cout << titleCard.at(i) << endl;
	}
	cout << R"(Do you want to use the default files? (Type "NO" for no, anything else for yes.))" << endl;
	getline(cin, input);
	if (input == "NO" || input == "no") {
		cout << "Please enter the file containing the Pokémon CSV file:" << endl;
		cin >> input;
		vector <Pokemon> custom = pokeList(input);
		cout << "Please enter the file containing the moves for your Pokémon." << endl;
		cin >> input;
		vector <Move> customMove = moveList(input);
		cout << "Do you want to" << endl;
		cout << "1) Print Pokémon Data?" << endl;
		cout << "2) Print Move Data?" << endl;
		cout << "3) Pokemon Battle (1v1)" << endl;
		cout << "4) Explore the World?" << endl;
		cin >> userInput;
		if (userInput == 1) {
			cout << "Please enter the Pokedex number of the Pokémon whose data you want to print:" << endl;
			cin >> userInput;
			for (int i = 0; i < custom.size(); i++) {
				if (userInput == custom.at(i).index) {
					cout << "Name: " <<  custom.at(i).name << endl;
					cout << "Index: " << custom.at(i).index << endl;
					cout << "HP: " << custom.at(i).hp << endl;
					cout << "Attack: " << custom.at(i).attk << endl;
					cout << "Defense: " << custom.at(i).def << endl;
					cout << "Speed: " << custom.at(i).speed << endl;
					cout << "Special Attack: " << custom.at(i).spAttk << endl;
					cout << "Special Defense: " << custom.at(i).spdf << endl;
					cout << "Type1: " << custom.at(i).type1 << endl;
					cout << "Type2: " << custom.at(i).type2 << endl;
					cout << "Gen: " << custom.at(i).generation << endl;
					if (custom.at(i).legendary) {
						cout << "Legendary: true" << endl;
					} else {
						cout << "Legendary: false" << endl;
					}
					return 0;
				}
			}
			die();
		} else if (userInput == 2) {
			cout << "Please enter the move number of the move whose data you want to print:" << endl;
			cin >> userInput;
			for (int i = 0; i < customMove.size(); i++) {
				if (userInput == customMove.at(i).index) {
					cout << "Move Index " << customMove.at(i).index << ": " << customMove.at(i).name << "  type: ";
					cout << customMove.at(i).type << " category: " << customMove.at(i).category << " PP: ";
					cout << customMove.at(i).PP << " power: ";
					if (customMove.at(i).power == -1) {
						cout << "—";
					} else {
						cout << customMove.at(i).power;
					}
					cout << " accuracy: ";
					if (customMove.at(i).accuracy == -1) {
						cout << "—";
					} else {
						cout << customMove.at(i).accuracy << "%" << endl;
					}
					return 0;
				}
			}
			die();
		}

	} else {
		cout << "Do you want to" << endl;
		cout << "1) Print Pokémon Data?" << endl;
		cout << "2) Print Move Data?" << endl;
		cout << "3) Pokemon Battle (1v1)" << endl;
		cout << "4) Explore the World?" << endl;
		cin >> userInput;
		if (userInput == 1) {
			cout << "Please enter the Pokedex number of the Pokémon whose data you want to print:" << endl;
			cin >> userInput;
			for (int i = 0; i < pokemon_db.size(); i++) {
				if (userInput == pokemon_db.at(i).index) {
					if (pokemon_db.at(i).name == "Mr.Mime") {
						pokemon_db.at(i).name.insert((pokemon_db.at(i).name.find(".") + 1), " ");
					}
					cout << "Name: " <<  pokemon_db.at(i).name << endl;
					cout << "Index: " <<  pokemon_db.at(i).index << endl;
					cout << "HP: " <<  pokemon_db.at(i).hp << endl;
					cout << "Attack: " <<  pokemon_db.at(i).attk << endl;
					cout << "Defense: " <<  pokemon_db.at(i).def << endl;
					cout << "Speed: " << pokemon_db.at(i).speed << endl;
					cout << "Special Attack: " << pokemon_db.at(i).spAttk << endl;
					cout << "Special Defense: " << pokemon_db.at(i).spdf << endl;
					cout << "Type1: " << pokemon_db.at(i).type1 << endl;
					cout << "Type2: " << pokemon_db.at(i).type2 << endl;
					cout << "Gen: " << pokemon_db.at(i).generation << endl;
					if (pokemon_db.at(i).legendary) {
						cout << "Legendary: true" << endl;
					} else {
						cout << "Legendary: false" << endl;
					}
					return 0;
				}
			}
			die();
		} else if (userInput == 2) {
			cout << "Please enter the move number of the move whose data you want to print:" << endl;
			cin >> userInput;
			for (int i = 0; i < move_db.size(); i++) {
				if (userInput == move_db.at(i).index) {
					cout << "Move Index " << move_db.at(i).index << ": " << move_db.at(i).name << "  type: ";
					cout << move_db.at(i).type << " category: " << move_db.at(i).category << " PP: ";
					cout << move_db.at(i).PP << " power: ";
					if (move_db.at(i).power == -1) {
						cout << "—";
					} else {
						cout << move_db.at(i).power;
					}
					cout << " accuracy: ";
					if (move_db.at(i).accuracy == -1) {
						cout << "—";
					} else {
						cout << move_db.at(i).accuracy << "%" << endl;
					}
					return 0;
				}
			}
			die();
		}
	}
	//YOU: Print the info on the chosen Pokemon or Move
}

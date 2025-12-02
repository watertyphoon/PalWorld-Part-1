#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

void die(string s = "INVALID INPUT!") {
	cout << s << endl;
	exit(EXIT_FAILURE);
}

//Holds info for a single species of Pokemon, such as Pikachu
class Pokemon {
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
	void printTest() {
		cout << index << name << type1;
		if (type2 != "none") {
			cout << type2;
		}
		cout << hp << attk << def << spdf << spAttk << speed << legendary << generation << endl;
	}
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

int damage_step(Pokemon& aPokemon, Pokemon& dPokemon, Move& move) {
	int damage;
	double temp;
	vector<vector<double>> type_chart = {
		{1, 1, 1, 1, 1, 0.5, 1, 0, 0.5, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{2, 1, 0.5, 0.5, 1, 2, 0.5, 0, 2, 1, 1, 1, 1, 0.5, 2, 1, 2, 0.5},
		{1, 2, 1, 1, 1, 0.5, 2, 1, 0.5, 1, 1, 2, 0.5, 1, 1, 1, 1, 1},
		{1, 1, 1, 0.5, 0.5, 0.5, 1, 0.5, 0, 1, 1, 2, 1, 1, 1, 1, 1, 2},
		{1, 1, 0, 2, 1, 2, 0.5, 1, 2, 2, 1, 0.5, 2, 1, 1, 1, 1, 1},
		{1, 0.5, 2, 1, 0.5, 1, 2, 1, 0.5, 2, 1, 1, 1, 1, 2, 1, 1, 1},
		{1, 0.5, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 0.5, 1, 2, 1, 2, 1, 1, 2, 0.5},
		{0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 0.5, 1},
		{1, 1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 0.5, 1, 0.5, 1, 2, 1, 1, 2},
		{1, 1, 1, 1, 1, 0.5, 2, 1, 2, 0.5, 0.5, 2, 1, 1, 2, 0.5, 1, 1},
		{1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 1, 0.5, 1, 1},
		{1, 1, 0.5, 0.5, 2, 2, 0.5, 1, 0.5, 0.5, 2, 0.5, 1, 1, 1, 0.5, 1, 1},
		{1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 2, 0.5, 0.5, 1, 1, 0.5, 1, 1},
		{1, 2, 1, 2, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 0.5, 1, 1, 0, 1},
		{1, 1, 2, 1, 2, 1, 1, 1, 0.5, 0.5, 0.5, 2, 1, 1, 0.5, 2, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 1, 1, 1, 2, 1, 0},
		{1, 0.5, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 0.5, 0.5},
		{1, 2, 1, 0.5, 1, 1, 1, 1, 0.5, 0.5, 1, 1, 1, 1, 1, 2, 2, 1}
	};
	map<string, int> m;
	m["Normal"] = 0;
	m["Fighting"] = 1;
	m["Flying"] = 2;
	m["Poison"] = 3;
	m["Ground"] = 4;
	m["Rock"] = 5;
	m["Bug"] = 6;
	m["Ghost"] = 7;
	m["Steel"] = 8;
	m["Fire"] = 9;
	m["Water"] = 10;
	m["Grass"] = 11;
	m["Electric"] = 12;
	m["Psychic"] = 13;
	m["Ice"] = 14;
	m["Dragon"] = 15;
	m["Dark"] = 16;
	m["Fairy"] = 17;
	if (dPokemon.def == 0) {
		return 9999;
	}
	if (move.category == "Special") {
		temp = double(move.power * aPokemon.spAttk) / dPokemon.spdf;
		if (dPokemon.type2 == "none") {
			temp = temp * type_chart.at(m[move.type]).at(m[dPokemon.type1]);
		} else {
			temp = temp * (type_chart.at(m[move.type]).at(m[dPokemon.type1]) * type_chart.at(m[move.type]).at(m[dPokemon.type2]));
		}
	} else {
		temp = double(move.power * aPokemon.attk) / dPokemon.def;
		if (dPokemon.type2 == "none") {
			temp = temp * type_chart.at(m[move.type]).at(m[dPokemon.type1]);
		} else {
			temp = temp * (type_chart.at(m[move.type]).at(m[dPokemon.type1]) * type_chart.at(m[move.type]).at(m[dPokemon.type2]));
		}
	}
	if (move.type == aPokemon.type1 || move.type == aPokemon.type2) {
		temp = temp * 1.5;
	}
	damage = round(temp);
	return damage;
}

int main() {
	string temp;
	string move;
	string currentLine;
	string pokemon1;
	string pokemon2;
	string attack;
	int index1 = -1;
	int index2 = -1;
	int mindex = -1;
	int damage = 0;
	bool found = false;
	//istringstream curr;
	//bool last;
	//int prevIndex = -10;
	//system("figlet POKEMON");
	//system("figlet ++ and \\#");
	//cout << "Do you want to use the default files? (Type \"NO\" for no, anything else for yes.)\n";

	vector<Pokemon> pokemon_db; //Holds all pokemon known
	vector<Move> move_db; //Holds all the moves we know
	map<string, int> m;
	m["Normal"] = 0;
	m["Fighting"] = 1;
	m["Flying"] = 2;
	m["Poison"] = 3;
	m["Ground"] = 4;
	m["Rock"] = 5;
	m["Bug"] = 6;
	m["Ghost"] = 7;
	m["Steel"] = 8;
	m["Fire"] = 9;
	m["Water"] = 10;
	m["Grass"] = 11;
	m["Electric"] = 12;
	m["Psychic"] = 13;
	m["Ice"] = 14;
	m["Dragon"] = 15;
	m["Dark"] = 16;
	m["Fairy"] = 17;

	int userInput = 0;
	string input;
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
		pokemon_db = pokeList(input);
		cout << "Please enter the file containing the moves for your Pokémon." << endl;
		cin >> input;
		move_db = moveList(input);
	} else {
		pokemon_db = pokeList("/public/pokemon.csv");
		move_db = moveList("/public/moves.txt");
	}
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
	} else if (userInput == 3) {
		cout << "Please enter the name or ID of Pokemon 1:" << endl;
		cin >> pokemon1;
		if (isdigit(pokemon1.at(0))) {
			index1 = stoi(pokemon1);
			for (int i = 0; i < pokemon_db.size(); i++) {
				if (index1 == pokemon_db.at(i).index) {
					index1 = i;
					found = true;
					break;
				}
			}
		} else {
			for (int i = 0; i < pokemon_db.size(); i++) {
				if (pokemon1 == pokemon_db.at(i).name) {
					index1 = i;
					found = true;
					break;
				}
			}
		}
		if (!found) {
			die();
		}
		cout << "Please enter the name or ID of Pokemon 2:" << endl;
		found = false;
		cin >> pokemon2;
		if (isdigit(pokemon2.at(0))) {
			index2 = stoi(pokemon2);
			for (int i = 0; i < pokemon_db.size(); i++) {
				if (index2 == pokemon_db.at(i).index) {
					index2 = i;
					found = true;
					break;
				}
			}
		} else {
			for (int i = 0; i < pokemon_db.size(); i++) {
				if (pokemon2 == pokemon_db.at(i).name) {
					index2 = i;
					found = true;
					break;
				}
			}
		}
		if (!found) {
			die();
		}
		cout << "Please enter the name or ID of the move to use:" << endl;
		found = false;
		cin >> attack;
		if (isdigit(attack.at(0))) {
			mindex = stoi(attack);
			for (int i = 0; i < move_db.size(); i++) {
				if (mindex == move_db.at(i).index) {
					mindex = i;
					found = true;
					break;
				}
			}
		} else {
			for (int i = 0; i < move_db.size(); i++) {
				if (attack == move_db.at(i).name) {
					mindex = i;
					found = true;
					break;
				}
			}
		}
		if (!found) {
			die();
		}
		if (pokemon_db.at(index1).speed >= pokemon_db.at(index2).speed) {
			damage = damage_step(pokemon_db.at(index1), pokemon_db.at(index2), move_db.at(mindex));
			cout << pokemon_db.at(index1).name << " used " << move_db.at(mindex).name << " and dealt ";
			cout << damage << " to " << pokemon_db.at(index2).name << endl;
		} else {
			damage = damage_step(pokemon_db.at(index2), pokemon_db.at(index1), move_db.at(mindex));
			cout << pokemon_db.at(index2).name << " used " << move_db.at(mindex).name << " and dealt ";
			cout << damage << " to " << pokemon_db.at(index1).name << endl;
		}
	}
//YOU: Print the info on the chosen Pokemon or Move
}

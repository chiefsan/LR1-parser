#include <bits/stdc++.h>
using namespace std;

class Production {
private:
        string lhs;
        string rhs;
public:
        Production (string lhs, string rhs) {
                this->lhs = lhs;
                this->rhs = rhs;
        }
	string get_lhs(){
		return lhs;
	}
	string get_rhs(){
		return rhs;
	}
};

class Grammar {
private:
	int n=0;
        vector <Production> productions;
        vector <string> terminals;
        vector <string> nonTerminals;
public:
        Grammar() {
		n=0;
        }
	int get_no_of_productions(){
		return n;
	}
	Production get_productions(int i){
		return productions[i];
	}
        bool insertProduction (Production p) {
                this->productions.push_back(p);
		n+=1;
        }
        bool setTerminals (vector < string > terminals) {
                this->terminals = terminals;
        }
        bool setNonTerminals (vector < string > nonTerminals) {
                this->nonTerminals = nonTerminals;
        }
};

int main () {
        Grammar G;
        string line;
        ifstream pFile;
        pFile.open("productions.txt", ios::in);
        if (pFile.is_open()) {
                while (getline(pFile, line)) {
                        cout << line << '\n';
                        int pos = line.find("->");
                        if (pos!=1) {
                                cout << "Error";
                                exit(0);
                        }
                        string lhs = line.substr(0, pos-1);
                        string rhs = line.substr(pos+1, line.length());
                        G.insertProduction(Production(lhs, rhs));
                }
                pFile.close();
        }
        else {
                cout << "Unable to read productions file\n";
        }

        ifstream tFile;
        tFile.open("terminals.txt", ios::in);
        vector < string > terminals;
        if (tFile.is_open()) {
                while (getline(tFile, line)) {
                        cout << line << '\n';
                        string t = line.substr(0, 0);
                        terminals.push_back(t)
                }
                tFile.close();
        }
        else {
                cout << "Unable to read terminals file\n";
        }

        ifstream nFile;
        nFile.open("nonterminals.txt", ios::in);
        vector < string > nonTerminals;
        if (tFile.is_open()) {
                while (getline(nFile, line)) {
                        cout << line << '\n';
                        string t = line.substr(0, 0);
                        nonTerminals.push_back(t)
                }
                nFile.close();
        }
        else {
                cout << "Unable to read nonTerminals file\n";
        }
        return 0;
}

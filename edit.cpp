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
        string str() {
            string temp = "=";
            return lhs+temp+rhs;
        }
};

class Grammar {
private:
        unsigned int noOfProductions;
        vector <Production> productions;
        vector <string> terminals;
        vector <string> nonTerminals;

        int count, n;
        char calc_first[10][100];
        char calc_follow[10][100];
        int m;
        char production[10][10];
        char f[10], first[10];
        int k;
        char ck;
        int e;
public:
        Grammar() {
                noOfProductions = 0;
                m = 0;
                n = 0;
        }
        int get_no_of_productions(){
                return this->noOfProductions;
        }
        Production get_productions(int i){
                return productions[i];
        }
        bool insertProduction (Production p) {
                this->productions.push_back(p);
                this->noOfProductions+=1;
        }
        bool setTerminals (vector < string > terminals) {
                this->terminals.swap(terminals);
        }
        bool setNonTerminals (vector < string > nonTerminals) {
                this->nonTerminals.swap(nonTerminals);
        }
        void preprocess () {
                int jm = 0;
                int km = 0;
                int i, choice;
                string c, ch;
                count = this->get_no_of_productions();
                int kay;
                char done[count];
                int ptr = -1;
                for(k = 0; k < count; k++) {
                        for(kay = 0; kay < 100; kay++) {
                                calc_first[k][kay] = '!';
                        }
                }
                for (i=0; i< count; ++i) {
                        string temp = this->productions[i].str();
                        strncpy(production[i], temp.c_str(), sizeof(temp)-1);
                        production[i][sizeof(temp)-1] = '\0';
                }
                int point1 = 0, point2, xxx;
                for(k = 0; k < count; k++)  {
                        char ch = this->get_productions(k).get_lhs()[0];
                        point2 = 0;
                        xxx = 0;
                        for(kay = 0; kay <= ptr; kay++)
                                if(ch == done[kay])
                                        xxx = 1;
                        if (xxx == 1)
                                continue;
                        findfirst(ch, 0, 0);
                        ptr += 1;
                        done[ptr] = ch;
                        printf("\n First(%c) = { ", ch);
                        calc_first[point1][point2++] = ch;
                        for(i = 0 + jm; i < n; i++) {
                                int lark = 0, chk = 0;
                                for(lark = 0; lark < point2; lark++) {
                                        if (first[i] == calc_first[point1][lark]) {
                                                chk = 1;
                                                break;
                                        }
                                }
                                if(chk == 0) {
                                        printf("%c, ", first[i]);
                                        calc_first[point1][point2++] = first[i];
                                }
                        }
                        printf("}\n");
                        jm = n;
                        point1++;
                }
                printf("\n");
                printf("-----------------------------------------------\n\n");
                char donee[count];
                ptr = -1;
                for(k = 0; k < count; k++) {
                        for(kay = 0; kay < 100; kay++) {
                                calc_follow[k][kay] = '!';
                        }
                }
                point1 = 0;
                int land = 0;
                for(e = 0; e < count; e++) {
                        ck = production[e][0];
                        point2 = 0;
                        xxx = 0;
                        for(kay = 0; kay <= ptr; kay++)
                                if(ck == donee[kay])
                                        xxx = 1;
                        if (xxx == 1)
                                continue;
                        land += 1;
                        follow(ck);
                        ptr += 1;
                        donee[ptr] = ck;
                        printf(" Follow(%c) = { ", ck);
                        calc_follow[point1][point2++] = ck;
                        for(i = 0 + km; i < m; i++) {
                                int lark = 0, chk = 0;
                                for(lark = 0; lark < point2; lark++) {
                                        if (f[i] == calc_follow[point1][lark]) {
                                                chk = 1;
                                                break;
                                        }
                                }
                                if(chk == 0) {
                                        printf("%c, ", f[i]);
                                        calc_follow[point1][point2++] = f[i];
                                }
                        }
                        printf(" }\n\n");
                        km = m;
                        point1++;
                }
        }

        void follow(char c) {
                int i, j;
                if(production[0][0] == c) {
                        f[m++] = '$';
                }
                for(i = 0; i < 10; i++) {
                        for(j = 2;j < 10; j++) {
                                if(production[i][j] == c) {
                                        if(production[i][j+1] != '\0') {
                                                followfirst(production[i][j+1], i, (j+2));
                                                }
                                        if(production[i][j+1]=='\0' && c!=production[i][0]) {
                                                follow(production[i][0]);
                                        }
                                }
                        }
                }
        }
        void findfirst(char c, int q1, int q2) {
                int j;
                if(!(isupper(c))) {
                        first[n++] = c;
                }
                for(j = 0; j < count; j++) {
                        if(production[j][0] == c) {
                                if(production[j][2] == '#') {
                                        if(production[q1][q2] == '\0')
                                                first[n++] = '#';
                                        else if(production[q1][q2] != '\0'
                                                        && (q1 != 0 || q2 != 0)) {
                                                findfirst(production[q1][q2], q1, (q2+1));
                                        }
                                        else
                                                first[n++] = '#';
                                }
                                else if(!isupper(production[j][2])) {
                                        first[n++] = production[j][2];
                                }
                                else {
                                        findfirst(production[j][2], j, 3);
                                }
                        }
                }
        }

        void followfirst(char c, int c1, int c2) {
                int k;
                if(!(isupper(c)))
                        f[m++] = c;
                else {
                        int i = 0, j = 1;
                        for(i = 0; i < count; i++) {
                                if(calc_first[i][0] == c)
                                        break;
                        }
                        while(calc_first[i][j] != '!') {
                                if(calc_first[i][j] != '#') {
                                        f[m++] = calc_first[i][j];
                                }
                                else {
                                        if(production[c1][c2] == '\0') {
                                                follow(production[c1][0]);
                                        }
                                        else {
                                                followfirst(production[c1][c2], c1, c2+1);
                                        }
                                }
                                j++;
                        }
                }
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
                        int pos = line.find("=");
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
                        terminals.push_back(t);
                }
                tFile.close();
        }
        else {
                cout << "Unable to read terminals file\n";
        }

        ifstream nFile;
        nFile.open("nonterminals.txt", ios::in);
        vector < string > nonTerminals;
        if (nFile.is_open()) {
                while (getline(nFile, line)) {
                        cout << line << '\n';
                        string t = line.substr(0, 0);
                        nonTerminals.push_back(t);
                }
                nFile.close();
        }
        else {
                cout << "Unable to read nonTerminals file\n";
        }

        cout << "\nLOL\n\n";
        G.preprocess();
        return 0;
}

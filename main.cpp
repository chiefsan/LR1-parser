#include <bits/stdc++.h>

using namespace std;

class Production {
    public:
        string lhs;
    string rhs;

    Production(string lhs, string rhs) {
        this->lhs = lhs;
        this->rhs = rhs;
    }
    string get_lhs() {
        return lhs;
    }
    string get_rhs() {
        return rhs;
    }
    string str() {
        string temp = "=";
        return lhs + temp + rhs;
    }
};

class Item {
    public:
        vector < string > lhs;
    vector < string > rhs;
    vector < set < char > > lookahead;
    int noOfRules;
    vector < bool > expanded;

    bool isEqual(Item it) {
        for (int i = 0; i < noOfRules; ++i) {
            if (it.lhs[i].compare(this->lhs[i]) != 0 || it.rhs[i].compare(this->rhs[i]) != 0 || it.lookahead[i] != this->lookahead[i])
                return false;
        }
        return true;
    }
};

ostream & operator << (ostream & out, Item temp) {
    cout << "ITEM : ";
    for (int i = 0; i < temp.noOfRules; ++i) {
        cout << temp.lhs[i] << " -> " << temp.rhs[i] << " | ";
        for (char c: temp.lookahead[i]) {
            cout << c << " ";
        }
        cout << "\t";
    }
    cout << '\n';
    return out;
}

class Grammar {
    private:
        unsigned int noOfProductions;
    vector < Production > productions;
    vector < string > terminals;
    vector < string > nonTerminals;
    vector < Item > items;
    unsigned int noOfItems;
    // string table[50][500];
    map < char, set < char > > fi;
    map < char, set < char > > fo;

    set < pair < char, char > > equal;
    int count, n;
    char calc_first[10][100];
    char calc_follow[10][100];
    int m;
    char production[10][10];
    char f[10], first[10];
    int k;
    char ck;
    int e;
    bool called[300];
    public:
        string table[50][500];
    Grammar() {
        noOfProductions = 0;
        m = 0;
        n = 0;
    }
    int get_no_of_productions() {
        return this->noOfProductions;
    }
    Production get_productions(int i) {
        return productions[i];
    }
    bool insertProduction(Production p) {
        this->productions.push_back(p);
        this->noOfProductions += 1;
        return true;
    }
    bool insertTerminal(string c) {
        this->terminals.push_back(c);
        return true;
    }
    bool setTerminals(vector < string > terminals) {
        // this->terminals.swap(terminals);
        for (string c: terminals)
            this->terminals.push_back(c);
        return true;
    }
    bool setNonTerminals(vector < string > nonTerminals) {
        // this->nonTerminals.swap(nonTerminals);
        for (string c: nonTerminals)
            this->nonTerminals.push_back(c);
        return true;
    }
    void preprocess() {
        int jm = 0;
        int km = 0;
        int i, choice;
        string c, ch;
        count = this->get_no_of_productions();
        int kay;
        char done[count];
        int ptr = -1;
        for (k = 0; k < count; k++) {
            for (kay = 0; kay < 100; kay++) {
                calc_first[k][kay] = '!';
            }
        }
        for (i = 0; i < count; ++i) {
            string temp = this->productions[i].str();
            strncpy(production[i], temp.c_str(), sizeof(temp) - 1);
            production[i][sizeof(temp) - 1] = '\0';
            cout << production[i] << '\n';
        }
        int point1 = 0, point2, xxx;
        for (k = 0; k < count; k++) {
            char ch = this->get_productions(k).get_lhs()[0];
            point2 = 0;
            xxx = 0;
            for (kay = 0; kay <= ptr; kay++)
                if (ch == done[kay])
                    xxx = 1;
            if (xxx == 1)
                continue;
            findfirst(ch, 0, 0);
            ptr += 1;
            done[ptr] = ch;
            // printf("\n First(%c) = { ", ch);
            if (fi.find(ch) == fi.end())
                fi[ch] = set < char > ();
            calc_first[point1][point2++] = ch;
            for (i = 0 + jm; i < n; i++) {
                int lark = 0, chk = 0;
                for (lark = 0; lark < point2; lark++) {
                    if (first[i] == calc_first[point1][lark]) {
                        chk = 1;
                        break;
                    }
                }
                if (chk == 0) {
                    // printf("%c, ", first[i]);
                    calc_first[point1][point2++] = first[i];
                    fi[ch].insert(first[i]);
                }
            }
            // printf("}\n");
            jm = n;
            point1++;
        }
        // printf("\n");
        char donee[count];
        // printf("-----------------------------------------------\n\n");
        ptr = -1;
        for (k = 0; k < count; k++) {
            for (kay = 0; kay < 100; kay++) {
                calc_follow[k][kay] = '!';
            }
        }
        point1 = 0;
        int land = 0;

        for (e = 0; e < count; e++) {
            ck = production[e][0];
            point2 = 0;
            xxx = 0;
            for (kay = 0; kay <= ptr; kay++)
                if (ck == donee[kay])
                    xxx = 1;
            if (xxx == 1)
                continue;
            land += 1;
            follow(ck);
            ptr += 1;
            donee[ptr] = ck;
            // printf(" Follow(%c) = { ", ck);
            if (fo.find(ck) == fo.end())
                fo[ck] = set < char > ();
            calc_follow[point1][point2++] = ck;
            for (i = 0 + km; i < m; i++) {
                int lark = 0, chk = 0;
                for (lark = 0; lark < point2; lark++) {
                    if (f[i] == calc_follow[point1][lark]) {
                        chk = 1;
                        break;
                    }
                }
                if (chk == 0) {
                    // printf("%c, ", f[i]);
                    calc_follow[point1][point2++] = f[i];
                    fo[ck].insert(f[i]);
                }
            }
            // printf(" }\n\n");
            km = m;
            point1++;
        }

        for (set < pair < char, char > > ::iterator i = equal.begin(); i != equal.end(); ++i) {
            char c1 = ( * i).first;
            char c2 = ( * i).second;
            fo[c1].insert(fo[c2].begin(), fo[c2].end());
        }

        for (map < char, set < char > > ::iterator i = fi.begin(); i != fi.end(); ++i) {
            cout << ( * i).first << " : ";
            for (set < char > ::iterator j = ( * i).second.begin(); j != ( * i).second.end(); ++j) {
                cout << ( * j) << ' ';
            }
            cout << '\n';
        }

        for (map < char, set < char > > ::iterator i = fo.begin(); i != fo.end(); ++i) {
            cout << ( * i).first << " : ";
            for (set < char > ::iterator j = ( * i).second.begin(); j != ( * i).second.end(); ++j) {
                cout << ( * j) << ' ';
            }
            cout << '\n';
        }
    }

    void follow(char c) {
        called[c] = true;
        int i, j;
        if (production[0][0] == c) {
            f[m++] = '$';
        }
        for (i = 0; i < 10; i++) {
            for (j = 2; j < 10; j++) {
                if (production[i][j] == c) {
                    if (production[i][j + 1] != '\0') {
                        followfirst(production[i][j + 1], i, (j + 2));
                    }
                    if (production[i][j + 1] == '\0' && c != production[i][0]) {
                        //                                              cout << "I : " << i << ' ' << production[i] << '\n';
                        if (!called[production[i][0]])
                            follow(production[i][0]);
                        else
                            equal.insert(make_pair(c, production[i][0]));
                    }
                }
            }
        }
    }
    void findfirst(char c, int q1, int q2) {
        int j;
        if (!(isupper(c))) {
            first[n++] = c;
        }
        for (j = 0; j < count; j++) {
            if (production[j][0] == c) {
                if (production[j][2] == '#') {
                    if (production[q1][q2] == '\0')
                        first[n++] = '#';
                    else if (production[q1][q2] != '\0' &&
                        (q1 != 0 || q2 != 0)) {
                        findfirst(production[q1][q2], q1, (q2 + 1));
                    } else
                        first[n++] = '#';
                } else if (!isupper(production[j][2])) {
                    first[n++] = production[j][2];
                } else {
                    findfirst(production[j][2], j, 3);
                }
            }
        }
    }

    void followfirst(char c, int c1, int c2) {
        int k;
        if (!(isupper(c)))
            f[m++] = c;
        else {
            int i = 0, j = 1;
            for (i = 0; i < count; i++) {
                if (calc_first[i][0] == c)
                    break;
            }
            while (calc_first[i][j] != '!') {
                if (calc_first[i][j] != '#') {
                    f[m++] = calc_first[i][j];
                } else {
                    if (production[c1][c2] == '\0') {
                        follow(production[c1][0]);
                    } else {
                        followfirst(production[c1][c2], c1, c2 + 1);
                    }
                }
                j++;
            }
        }
    }

    Item closure(Item item) {
        for (int i = 0; i < item.noOfRules; ++i) {
            if (item.expanded[i] == false)
                item.expanded[i] = true;
            else
                return item;
            int posDot = item.rhs[i].find(".");
            int rhslen = item.rhs[i].length();
            if (rhslen - 1 == posDot)
                continue;
            if (item.rhs[i][posDot + 1] >= 'A' && item.rhs[i][posDot + 1] <= 'Z') {
                char newlhs = item.rhs[i][posDot + 1];
                for (Production p: this->productions) {
                    if (p.lhs[0] == newlhs) {
                        string temp = "." + p.rhs;
                        item.lhs.push_back(p.lhs);
                        item.rhs.push_back(temp);
                        item.expanded.push_back(false);
                        item.noOfRules += 1;
                        set < char > lookahead;
                        if (posDot + 2 == rhslen) {
                            for (char c: item.lookahead[i]) {
                                lookahead.insert(c);
                            }
                        } else if (item.rhs[i][posDot + 2] >= 'a' && item.rhs[i][posDot + 2] <= 'z') {
                            lookahead.insert(item.rhs[i][posDot + 2]);
                        } else {
                            for (char c: fi[item.rhs[i][posDot + 2]]) {
                                lookahead.insert(c);
                            }
                        }
                        item.lookahead.push_back(lookahead);
                    }
                }
            }
        }
        return item;
    }

    void constructItems() {
        Item temp = Item();
        temp.lhs.push_back("Z");
        temp.rhs.push_back(".S");
        set < char > lookahead;
        lookahead.insert('$');
        temp.lookahead.push_back(lookahead);
        temp.noOfRules = 1;
        temp.expanded.push_back(false);
        temp = closure(temp);
        items.push_back(temp);
        int oldSize = 0;
        int curItem = -1;
        vector < bool > terminalType;
        while (curItem != items.size() - 1) {
            curItem += 1;
            Item item = items[curItem];
            item = closure(item);
            oldSize = items.size();
            cout << item;
            vector < Item > toBeInserted;
            for (int i = 0; i < item.noOfRules; ++i) {
                int posDot = item.rhs[i].find(".");
                int rhslen = item.rhs[i].length();
                if (rhslen - 1 == posDot) {
                    int index = -1;
                    string s = item.lhs[i] + item.rhs[i].substr(0, posDot);
                    for (int i = 0; i < noOfProductions; ++i) {
                        string t = productions[i].lhs + productions[i].rhs;
                        if (t == s) {
                            index = i;
                        }
                    }
                    for (char c: item.lookahead[i]) {
                        table[curItem][c] = 'r' + to_string(index);
                    }
                }
            }
            vector < string > nextSym;
            for (string c: this->terminals) {
                Item temp = Item();
                for (int i = 0; i < item.noOfRules; ++i) {
                    int posDot = item.rhs[i].find(".");
                    int rhslen = item.rhs[i].length();
                    if (c == item.rhs[i].substr(posDot + 1, posDot + 1)) {
                        string newrhs = item.rhs[i].substr(0, posDot) + c + "." + item.rhs[i].substr(posDot + 2, rhslen);
                        string newlhs = item.lhs[i];
                        set < char > newlookahead;
                        for (char l: item.lookahead[i])
                            newlookahead.insert(l);
                        temp.lhs.push_back(newlhs);
                        temp.rhs.push_back(newrhs);
                        temp.lookahead.push_back(newlookahead);
                        temp.expanded.push_back(false);
                        temp.noOfRules += 1;
                    }
                }
                if (temp.noOfRules) {
                    // items.push_back(temp);
                    toBeInserted.push_back(temp);
                    terminalType.push_back(true);
                    nextSym.push_back(c);
                }
            }
            for (string c: this->nonTerminals) {
                Item temp = Item();
                for (int i = 0; i < item.noOfRules; ++i) {
                    int posDot = item.rhs[i].find(".");
                    int rhslen = item.rhs[i].length();
                    if (c == item.rhs[i].substr(posDot + 1, posDot + 1)) {
                        string newrhs = item.rhs[i].substr(0, posDot) + c + "." + item.rhs[i].substr(posDot + 2, rhslen);
                        string newlhs = item.lhs[i];
                        set < char > newlookahead;
                        for (char l: item.lookahead[i])
                            newlookahead.insert(l);
                        temp.lhs.push_back(newlhs);
                        temp.rhs.push_back(newrhs);
                        temp.lookahead.push_back(newlookahead);
                        temp.expanded.push_back(false);
                        temp.noOfRules += 1;
                    }
                }
                if (temp.noOfRules) {
                    toBeInserted.push_back(temp);
                    terminalType.push_back(false);
                    nextSym.push_back(c);
                }
            }
            oldSize = items.size();
            int toBeInsertedIndex = -1;
            for (Item item1: toBeInserted) {
                toBeInsertedIndex += 1;
                vector < string > toBeInsertedString;
                for (int i = 0; i < item1.noOfRules; ++i) {
                    string s;
                    s = item1.lhs[i] + item1.rhs[i];
                    for (char c: item1.lookahead[i]) {
                        s += c;
                    }
                    toBeInsertedString.push_back(s);
                }
                sort(toBeInsertedString.begin(), toBeInsertedString.end());
                bool present = false;
                int index = -1;
                for (Item item2: items) {
                    index += 1;
                    vector < string > item2String;
                    for (int i = 0; i < item2.noOfRules; ++i) {
                        string s;
                        s = item2.lhs[i] + item2.rhs[i];
                        for (char c: item2.lookahead[i]) {
                            s += c;
                        }
                        item2String.push_back(s);
                    }
                    int ne = 0;
                    sort(item2String.begin(), item2String.end());
                    if (item2String.size() == toBeInsertedString.size()) {
                        for (int i = item2String.size() - 1; i >= 0; --i) {
                            if (item2String[i] != toBeInsertedString[i]) {
                                // cout << item2String[i] << ' ' << toBeInsertedString[i] << '\n';
                                ne += 1;
                            } else {
                                // cout << item2String[i] << ' ' << toBeInsertedString[i] << '\n';
                                1;
                            }
                        }
                        if (ne == 0) {
                            present = true;
                            table[curItem][nextSym[toBeInsertedIndex][0]] = 's' + to_string(index);
                        }
                    }
                }
                if (present == false) {
                    table[curItem][nextSym[toBeInsertedIndex][0]] = 's' + to_string(items.size());
                    items.push_back(item1);
                }
            }
        }
    }

    bool parse_string(string input) {
        input = input + '$';
        stack < string > s;
        stack < char > symbol;
        string action;
        s.push("0");
        char x;
        int ii = 0;
        while (!(symbol.top() == 'S' && input == "$")) {
            x = input[ii];
            input = input.erase(0, 1);
            action = table[stoi(s.top())][x];
            if (action[0] == 's') {
                symbol.push(x);
                s.push(action.substr(1, action.length()));
            } else {
                if (stoi(action.substr(1, action.length())) == -1 && input == "$") {
                    return true;
                }
                L1:
                    string rhs = productions[stoi(action.substr(1, action.length()))].rhs;
                string lhs = productions[stoi(action.substr(1, action.length()))].lhs;
                cout << lhs << "->" << rhs << '\n';
                for (int i = 0; i < rhs.size(); i++) {
                    symbol.pop();
                    s.pop();
                }

                symbol.push(lhs[0]);

                string xx = table[stoi(s.top())][symbol.top()];
                if (xx[0] == 's') {
                    s.push(xx.substr(1, xx.length()));
                } else {
                    action = xx;
                    goto L1;
                }
                input = x + input;
            }
        }
        cout << "Accepted\n";
        return true;
    }

    void print_table() {
        terminals.push_back("$");
        cout << "   ";
        for (int j = 0; j < nonTerminals.size(); j++)
            cout << nonTerminals[j] << '\t';
        for (int j = 0; j < terminals.size(); j++)
            cout << terminals[j] << '\t';

        cout << '\n';
        for (int i = 0; i < items.size(); i++) {
            cout << i << ' ';
            for (int j = 0; j < nonTerminals.size(); j++) {
                cout << table[i][nonTerminals[j][0]] << '\t';
            }
            for (int j = 0; j < terminals.size(); j++) {
                cout << table[i][terminals[j][0]] << '\t';
            }
            cout << "\n";
        }

    }
};

int main() {
    Grammar G;
    string line;
    ifstream pFile;
    pFile.open("input.txt", ios:: in );
    if (pFile.is_open()) {
        while (getline(pFile, line)) {
            // cout << line << '\n';
            int pos = line.find("=");
            if (pos != 1) {
                cout << "Error";
                exit(0);
            }
            string lhs = line.substr(0, pos);
            string rhs = line.substr(pos + 1, line.length());
            G.insertProduction(Production(lhs, rhs));
        }
        pFile.close();

    } else {
        cout << "Unable to read productions file\n";
    }

    ifstream tFile;
    tFile.open("terminals.txt", ios:: in );
    vector < string > terminals;
    if (tFile.is_open()) {
        while (getline(tFile, line)) {
            // cout << line << '\n';
            string t = line.substr(0, 1);
            G.insertTerminal(t);
            terminals.push_back(t);
        }
        // G.setTerminals(terminals);
        tFile.close();
    } else {
        cout << "Unable to read terminals file\n";
    }

    ifstream nFile;
    nFile.open("nonterminals.txt", ios:: in );
    vector < string > nonTerminals;
    if (nFile.is_open()) {
        while (getline(nFile, line)) {
            // cout << line << '\n';
            string t = line.substr(0, 1);
            nonTerminals.push_back(t);
        }
        G.setNonTerminals(nonTerminals);
        nFile.close();
    } else {
        cout << "Unable to read nonTerminals file\n";
    }

    G.preprocess();
    G.constructItems();
    G.print_table();
    G.parse_string("aabb");

    return 0;
}

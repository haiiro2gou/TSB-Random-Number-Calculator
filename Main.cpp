#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

int N, P;
int A, B;
typedef pair<int, int> pairInt;
vector<pairInt> V;
int Base, Carry;
long long rBase, rCarry;
vector<pairInt> res;

void Random() {
    Base *= 31743;
    Base += Carry;
    Carry = Base;
    Carry /= 65536;
    Base %= 65536;
}

bool solve(int x, int y) {
    if (Base % y == x) return true;
    return false;
}

void recoverRandom(long long rb, long long rc) {
    rBase = rb + rc * 65536;
    rCarry = rBase;
    rBase /= 31743;
    rCarry %= 31743;
}

string suffix[] = {"th", "st", "nd", "rd"};

string addSuffix(int value) {
    string str;
    str += to_string(value);
    if ((((value / 10) % 10) == 1) || (((value % 10) & 0b1100) != 0)) {
        str += suffix[0];
    } else {
        str += suffix[value % 10];
    }
    return str;
}

int main() {
    cout << "TSB Random Inverter" << endl;
    cout << "Input Number of Random Calculation." << endl;
    cout << "N> ";
    cin >> N;
    cout << "Input Number of Queues." << endl;
    cout << "Q> ";
    cin >> P;
    cout << "Input Queues." << endl;
    cout << "Format> A B" << endl;
    cout << "(A: Index of the Array, B: Size of the Array)" << endl;
    for (int i = 0; i < P; i++) {
        printf("Input %s Queue.\n", addSuffix(i + 1).c_str());
        cout << "A B> ";
        cin >> A >> B;
        V.push_back(pairInt(A, B));
    }

    cout << "Calculating..." << endl;
    bool suc = false;
    const int MAX_LOOP = 65535;
    for (int i = 0; i <= MAX_LOOP; ++i) {
        for (int j = 0; j <= MAX_LOOP; ++j) {
            Base = i;
            Carry = j;

            bool b;
            for (int n = 0; n < P; n++) {
                Random();
                auto np = V.at(n);
                b = solve(np.first, np.second);
                if (!b) break;
            }

            if (b) {
                suc = true;
                rBase = i;
                rCarry = j;
                for (int k = 0; k < N; k++) recoverRandom(rBase, rCarry);
                res.push_back(pairInt(rBase, rCarry));
                break;
            }
        }
        if (i == 0) printf("0%\n");
        if (i == MAX_LOOP / 4) printf("25%\n");
        if (i == MAX_LOOP / 2) printf("50%\n");
        if (i == MAX_LOOP * 3 / 4) printf("75%\n");
        if (i == MAX_LOOP) printf("100%\n");
    }

    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    printf("Calculation Finished!");
    for (int i = 0; i < min((long long) res.size(), 10ll); i++) printf("%2d> Base: %5d  Carry: %5d\n", i + 1, res.at(i).first, res.at(i).second);
    if (!suc) printf("Failed to find answer.\n");
    else if (res.size() < 10) printf("Total: %d\n", res.size());
    else printf("The first 10 are shown. (Total: %lld)\n", res.size());
    return 0;
}
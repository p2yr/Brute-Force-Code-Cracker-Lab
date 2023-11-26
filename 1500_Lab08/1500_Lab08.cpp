#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

//abcdefghijklmnopqrstuvwxyz         ABCDEFGHIJKLMNOPQRSTUVWXYZ
//65                       90        97                       122

string shift(string cipher, int amount) {
	while (amount < 0) { //handle overflow and underflow
		amount += 26;
	}
	while (amount > 26) {
		amount -= 26;
	}

	string shifted = "";
	vector<int> shiftedInt;
	for (int i = 0; i < cipher.length(); ++i) {
		shiftedInt.push_back(int(cipher[i]));
	}
	for (int i = 0; i < cipher.length(); ++i) {

		if (shiftedInt[i] == 32) { //spaces stay the same
			shiftedInt[i] = shiftedInt[i];
		}
		else if (shiftedInt[i] >= 97) { //if lowercase
			if (shiftedInt[i] + amount > 122) {
				shiftedInt[i] = shiftedInt[i] + amount - 26;
			}
			else {
				shiftedInt[i] += amount;
			}
		}
		else { //if capital
			if (shiftedInt[i] + amount > 90) {
				shiftedInt[i] = shiftedInt[i] + amount - 26;
			}else{
				shiftedInt[i] += amount;
			}
		}
	}
	for (int i = 0; i < cipher.length(); ++i) {
		shifted += char(shiftedInt[i]);
	}
	return shifted;
}

void fill(string &cipher, vector<string> &shifts) { //make vector with all 26 iterations 
	for (int i = 0; i < 26; ++i) {
		shifts.push_back(shift(cipher, i));
	}
}

void cutPairs(vector<string>& shifts) { //search for and cut pairs that don't show up in English language
	vector<string> nonpairs = { "bx", "cj", "cv", "dx", "fq", "fx", "gq", "gx", "hx", "jc", "jf", "jg", "jq", "js", "jv", "jw", "jx", "jz",
	"kq," "kx", "mx", "px", "pz", "qb", "qc", "qd", "qf", "qg", "qh", "qj", "qk", "ql", "qm", "qn", "qp", "qs", "qt", "qv", "qw", "qx", "qy",
	"qz", "sx", "vb", "vf", "vh", "vj", "vm", "vp", "vq", "vt", "vw", "vx", "xj", "xx", "zj", "zq", "zx" };

	bool badIndex[26] = { false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, };

	for (int i = 0; i < shifts.size(); i++) {
		for (int j = 0; j < nonpairs.size(); j++) {
			if (shifts.at(i).find(nonpairs.at(j)) != string::npos) {
				badIndex[i] = true;
			}
		}
	}
	for (int i = shifts.size() - 1; i >= 0; --i) {
		if (badIndex[i] == true) {
			shifts.erase(shifts.begin() + i);
		}
	}
}

void cutKeyWords(vector<string> &shifts) {
	vector<string> keywords = { " in ", " the ", " and ", " is ", " are ", " not ", " of ", " too ", " but ", " you ", " that ", " with ", " this ", " say ", " they " };
	vector<bool> badIndex;
	badIndex.resize(shifts.size(), false);

	for (unsigned int i = 0; i < shifts.size(); ++i) {
		for (int j = 0; j < keywords.size(); ++j) {
			if (shifts.at(i).find(keywords.at(j)) != string::npos) {
				badIndex.at(i) = true;
			}
		}
	}

	for (int i = shifts.size() - 1; i >= 0; --i) {
		if (badIndex[i] == false) {
			shifts.erase(shifts.begin() + i);
		}
	}
}

void print(vector<string>& cipher) {
	for (int i = 0; i < cipher.size(); ++i) {
		cout << cipher.at(i) << endl;
	}
}

void output(vector<string> &shift, vector<string> &cut) {
	if (cut.size() > 0) {
		cout << "Your message is: ";
		print(cut);
	}
	else {
		cout << "Is one of these your message? " << endl;
		print(shift);
	}
}

int main() {
	string cipher1 = "Wkh qljkw lv orqj dqg zh doo suhwhqg wr vohhs";
	string cipher2 = "F xrfqq hnyd mfx gjjs inxhtajwji zsijw ymj gtbqnsl fqqjd";
	string cipher3 = "Yx Drebcnki dro vslbkbi gsvv lo exuxygklvo";
	string cipher4 = "Epht bsf opu bmmpxfe jo uif eph qbsl";
	string cipher5 = "Jrypbzr gb Avtug Inyr";

	vector<string> shift1; //create vector of all ciphers
	vector<string> shift2;
	vector<string> shift3;
	vector<string> shift4;
	vector<string> shift5;

	fill(cipher1, shift1); //fill vectors with all possibilities
	fill(cipher2, shift2);
	fill(cipher3, shift3);
	fill(cipher4, shift4);
	fill(cipher5, shift5);

	cutPairs(shift1);
	cutPairs(shift2);
	cutPairs(shift3);
	cutPairs(shift4);
	cutPairs(shift5);

	vector<string> cut1 = shift1;
	vector<string> cut2 = shift2;
	vector<string> cut3 = shift3;
	vector<string> cut4 = shift4;
	vector<string> cut5 = shift5;

	cutKeyWords(cut1);
	cutKeyWords(cut2);
	cutKeyWords(cut3);
	cutKeyWords(cut4);
	cutKeyWords(cut5);

	//THE MANUAL ALGORITHM\\
	//cout << shift(cipher1, 23) << endl;
	//cout << shift(cipher2, 21) << endl;
	//cout << shift(cipher3, 16) << endl;
	//cout << shift(cipher4, 25) << endl;
	//cout << shift(cipher5, 13) << endl;

	output(shift1, cut1);
	output(shift2, cut2);
	output(shift3, cut3);
	output(shift4, cut4);
	output(shift5, cut5);

	//fill vectors with strings where amountshifted is the index

	//shuffle strings. first put strings through keyword search to see if they're valid.
	//then cut through our existing strings and get rid of the ones that have letter combinations that don't occur naturally
	//if they're not valid then spit out a list of all 26 and ask which one is valid

}

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <map>
#include <queue>
#include <tuple>

using namespace std;

class Expense {
public:
    string category;
    double amount;
    string date;

    Expense() {}

    Expense(string c, double a, string d) {
        category = c;
        amount = a;
        date = d;
    }
};

/* -------------------- TRIE  -------------------- */
class TrieNode {
public:
    map<char, TrieNode*> children;
    bool isEnd;

    TrieNode() {
        isEnd = false;
    }
};

class Trie {
private:
    TrieNode* root;

    void suggestionsHelper(TrieNode* node, string prefix) {
        if (node->isEnd)
            cout << prefix << endl;

        for (auto &child : node->children) {
            suggestionsHelper(child.second, prefix + child.first);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;

        for (char c : word) {
            if (!node->children[c])
                node->children[c] = new TrieNode();

            node = node->children[c];
        }

        node->isEnd = true;
    }

    void suggestions(string prefix) {
        TrieNode* node = root;

        for (char c : prefix) {
            if (!node->children[c]) {
                cout << "No category found.\n";
                return;
            }
            node = node->children[c];
        }

        suggestionsHelper(node, prefix);
    }
};


class ExpenseTracker {

    multimap<string, Expense> expenses;     // Red-Black Tree
    unordered_map<string, double> categoryTotals; 
    Trie categoryTrie;                      
    string filename = "expenses.txt";

   
    void loadFromFile() {

        expenses.clear();
        categoryTotals.clear();

        ifstream file(filename);
        string line;

        while (getline(file, line)) {

            stringstream ss(line);
            string cat, amtStr, dt;

            getline(ss, cat, ',');
            getline(ss, amtStr, ',');
            getline(ss, dt);

            if (!cat.empty() && !amtStr.empty() && !dt.empty()) {

                double amt = stod(amtStr);

                expenses.insert({dt, Expense(cat, amt, dt)});
                categoryTotals[cat] += amt;

                categoryTrie.insert(cat);
            }
        }

        file.close();
    }

   
    void saveToFile() {

        ofstream file(filename);

        for (auto &pair : expenses) {

            file << pair.second.category << ","
                 << pair.second.amount << ","
                 << pair.second.date << endl;
        }

        file.close();
    }

public:

    ExpenseTracker() {
        loadFromFile();
    }

   
    void addExpense() {

        string cat, dt;
        double amt;

        cout << "Enter category: ";
        cin >> ws;
        getline(cin, cat);

        cout << "Enter amount: ";
        cin >> amt;

        cout << "Enter date (YYYY-MM-DD): ";
        cin >> dt;

        expenses.insert({dt, Expense(cat, amt, dt)});

        categoryTotals[cat] += amt;

        categoryTrie.insert(cat);

        saveToFile();

        cout << "Expense added successfully.\n";
    }

    /* ---------- View All Expenses ---------- */
    void viewExpenses() {

        if (expenses.empty()) {
            cout << "No expenses recorded.\n";
            return;
        }

        cout << left << setw(12) << "Date"
             << setw(20) << "Category"
             << setw(10) << "Amount" << endl;

        for (auto &pair : expenses) {

            cout << left << setw(12) << pair.second.date
                 << setw(20) << pair.second.category
                 << setw(10) << pair.second.amount << endl;
        }
    }

   
    void totalExpenses() {

        double total = 0;

        for (auto &pair : expenses)
            total += pair.second.amount;

        cout << "Total Expense: " << total << endl;
    }

   
    void filterByCategory() {

        string cat;

        cout << "Enter category: ";
        cin >> ws;
        getline(cin, cat);

        bool found = false;

        cout << left << setw(12) << "Date"
             << setw(20) << "Category"
             << setw(10) << "Amount" << endl;

        for (auto &pair : expenses) {

            if (pair.second.category == cat) {

                cout << left << setw(12) << pair.second.date
                     << setw(20) << pair.second.category
                     << setw(10) << pair.second.amount << endl;

                found = true;
            }
        }

        if (!found)
            cout << "No expenses found in this category.\n";
    }

   
    void showCategorySummary() {

        for (auto &pair : categoryTotals)
            cout << pair.first << " : " << pair.second << endl;
    }

   
    void viewExpensesSorted() {

        if (expenses.empty()) {
            cout << "No expenses.\n";
            return;
        }

        vector<Expense> sorted;

        for (auto const &pair : expenses)
            sorted.push_back(pair.second);

        int choice;

        cout << "1. Sort High to Low\n";
        cout << "2. Sort Low to High\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
            sort(sorted.begin(), sorted.end(),
                [](Expense a, Expense b){ return a.amount > b.amount; });

        else if (choice == 2)
            sort(sorted.begin(), sorted.end(),
                [](Expense a, Expense b){ return a.amount < b.amount; });

        cout << left << setw(12) << "Date"
             << setw(20) << "Category"
             << setw(10) << "Amount" << endl;

        for (auto &exp : sorted) {

            cout << left << setw(12) << exp.date
                 << setw(20) << exp.category
                 << setw(10) << exp.amount << endl;
        }
    }

   
    void showTopExpenses() {

        priority_queue<tuple<double,string,string>> pq;

        for (auto &pair : expenses) {

            pq.push(make_tuple(
                pair.second.amount,
                pair.second.category,
                pair.second.date
            ));
        }

        cout << "Top 5 Highest Expenses:\n";

        int count = 5;

        while (!pq.empty() && count--) {

            auto t = pq.top();
            pq.pop();

            cout << get<2>(t) << " | "
                 << get<1>(t) << " | "
                 << get<0>(t) << endl;
        }
    }

    
    void searchCategoryPrefix() {

        string prefix;

        cout << "Enter category prefix: ";
        cin >> prefix;

        cout << "Matching categories:\n";

        categoryTrie.suggestions(prefix);
    }

    
    void run() {

        int ch;

        do {

            cout << "\n------ Daily Expense Tracker ------\n";

            cout << "1. Add Expense\n";
            cout << "2. View All Expenses\n";
            cout << "3. Show Total Expenses\n";
            cout << "4. Filter by Category\n";
            cout << "5. Show Category Totals\n";
            cout << "6. Sort Expenses by Amount\n";
            cout << "7. Show Top Expenses (Heap)\n";
            cout << "8. Search Category Prefix (Trie)\n";
            cout << "9. Exit\n";

            cout << "Enter choice: ";
            cin >> ch;

            switch (ch) {

                case 1: addExpense(); break;
                case 2: viewExpenses(); break;
                case 3: totalExpenses(); break;
                case 4: filterByCategory(); break;
                case 5: showCategorySummary(); break;
                case 6: viewExpensesSorted(); break;
                case 7: showTopExpenses(); break;
                case 8: searchCategoryPrefix(); break;
                case 9: cout << "Exiting...\n"; break;

                default: cout << "Invalid choice.\n";
            }

        } while (ch != 9);
    }
};


int main() {

    ExpenseTracker tracker;

    tracker.run();

    return 0;
}

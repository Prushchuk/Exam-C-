#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

// ��������� ��� ������
struct Expense {
    string category;
    double amount;
    string date;
};

// ��������� ��� ��������
struct Wallet {
    string name;
    double balance;

    // ����������� ��� ����������� ������� � ��'�� �� ���������� ��������
    Wallet(string walletName, double initialBalance) : name(walletName), balance(initialBalance) {}
};

// ���� ��� ��������� ���������
class FinanceManager {
private:
    vector<Wallet> wallets; // ������� �� �� �������
    vector<Expense> expenses; // ������ ������

public:
    // ������ ��������
    void addWallet(string walletName) {
        wallets.push_back(Wallet(walletName, 0.0));
    }

    // ��������� ��������
    void deposit(string walletName, double amount) {
        for (size_t i = 0; i < wallets.size(); ++i) {
            if (wallets[i].name == walletName) {
                wallets[i].balance += amount;
                break;
            }
        }
    }

    // ������ �������
    void addExpense(string category, double amount, string date) {
        expenses.push_back(Expense{ category, amount, date });
    }

    // �������� ��� �� ����
    void generateDailyReport(string date) {
        double totalExpenses = 0.0;
        cout << "Daily Report for " << date << ":" << endl;
        size_t expensesSize = expenses.size();
        for (size_t i = 0; i < expensesSize; ++i) {
            if (expenses[i].date == date) {
                totalExpenses += expenses[i].amount;
                cout << "Category: " << expenses[i].category << ", Amount: " << expenses[i].amount << endl;
            }
        }
        cout << "Total Expenses: " << totalExpenses << endl;
    }

    // �������� ��� �� �������
    void generateWeeklyReport(string startDate, string endDate) {
        double totalExpenses = 0.0;
        cout << "Weekly Report from " << startDate << " to " << endDate << ":" << endl;
        size_t expensesSize = expenses.size();
        for (size_t i = 0; i < expensesSize; ++i) {
            if (expenses[i].date >= startDate && expenses[i].date <= endDate) {
                totalExpenses += expenses[i].amount;
                cout << "Category: " << expenses[i].category << ", Amount: " << expenses[i].amount << endl;
            }
        }
        cout << "Total Expenses: " << totalExpenses << endl;
    }

    // �������� ��� �� �����
    void generateMonthlyReport(string month) {
        double totalExpenses = 0.0;
        cout << "Monthly Report for " << month << ":" << endl;
        size_t expensesSize = expenses.size();
        for (size_t i = 0; i < expensesSize; ++i) {
            if (expenses[i].date.substr(0, 7) == month) {
                totalExpenses += expenses[i].amount;
                cout << "Category: " << expenses[i].category << ", Amount: " << expenses[i].amount << endl;
            }
        }
        cout << "Total Expenses: " << totalExpenses << endl;
    }

    // ���������� ���-3 ������ �� ������ ����� (������� ��� �����)
    void generateTopExpenses(string periodStart, string periodEnd) {
        unordered_map<string, double> categorySums; // ������� ��� ��� ����� �������
        size_t expensesSize = expenses.size();
        for (size_t i = 0; i < expensesSize; ++i) {
            const Expense& expense = expenses[i];
            if (expense.date >= periodStart && expense.date <= periodEnd) {
                categorySums[expense.category] += expense.amount;
            }
        }

        // ��������� ������� ��� <��������, ����> � ��������
        vector<pair<string, double>> categorySumsVec;
        categorySumsVec.reserve(categorySums.size());
        for (auto it = categorySums.begin(); it != categorySums.end(); ++it) {
            categorySumsVec.push_back(make_pair(it->first, it->second));
        }

        // ���������� ������� �� ��������� ���
        sort(categorySumsVec.begin(), categorySumsVec.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
            return a.second > b.second;
            });

        // ��������� ���-3 ������
        cout << "TOP-3 Expenses for the period " << periodStart << " to " << periodEnd << ":" << endl;
        size_t limit = min(static_cast<size_t>(3), categorySumsVec.size());
        for (size_t i = 0; i < limit; ++i) {
            cout << i + 1 << ". Category: " << categorySumsVec[i].first << ", Total amount: " << categorySumsVec[i].second << endl;
        }
    }

    // �������� ��� �� �������� � ����
    void saveToFile(string filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "Expenses:" << endl;
            size_t expensesSize = expenses.size();
            for (size_t i = 0; i < expensesSize; ++i) {
                outFile << "Category: " << expenses[i].category << ", Amount: " << expenses[i].amount << ", Date: " << expenses[i].date << endl;
            }
            outFile << "Wallets:" << endl;
            size_t walletsSize = wallets.size();
            for (size_t i = 0; i < walletsSize; ++i) {
                outFile << "Name: " << wallets[i].name << ", Balance: " << wallets[i].balance << endl;
            }
            outFile.close();
            cout << "Data saved to file: " << filename << endl;
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }
};

int main() {
    FinanceManager manager;
    manager.addWallet("Wallet1");
    manager.addWallet("Wallet2");

    manager.deposit("Wallet1", 100.0);
    manager.deposit("Wallet2", 200.0);

    manager.addExpense("Food", 50.0, "2024-04-01");
    manager.addExpense("Transport", 30.0, "2024-04-02");

    manager.generateTopExpenses("2024-04-01", "2024-04-07");

    manager.saveToFile("finance_data.txt");
}
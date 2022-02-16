#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

using namespace std;

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false, string iban = " ", int limit = 0, int account_balace = 0, int money_withdrawal = 0, int money_deposit = 0, int transfer_amount = 0);

    void print () const;
    // More methods

    void set_credit_limit(int limit);

    void save_money(int account_balance);

    void take_money(int money_deposit);

    void transfer_to(Account& owner, int transfer_amount);
private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    std::string owner;
    std::string owner_;
    bool has_credit_;
    int limit_;
    int account_balance_ = 0;
    int money_withdrawal_;
    string iban;
    string iban_;
    int money_deposit;
    int money_deposit_;

//    const string m_owner;
//    const string m_owner_;

    std::string account_number;
    int account_balance = 0;

    int transfer_amount = 0;
    int transfer_amount_ = 0;

    // More attributes/methods
};

#endif // ACCOUNT_HH

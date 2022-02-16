#include "account.hh"
#include <iostream>
#include <string>

using namespace std;

Account::Account(const std::string& owner, bool has_credit, string iban, int limit, int account_balance, int money_withdrawal, int money_deposit, int transfer_amount):
    owner_(owner),
    has_credit_(has_credit),
    limit_(limit),
    account_balance_(account_balance),
    money_withdrawal_(money_withdrawal),
    iban_(iban),
    money_deposit_(money_deposit),
    transfer_amount_(transfer_amount)

{
    generate_iban();
}

void Account::print() const
{
    std::cout << owner_ << " : " <<  iban_ << " : " << account_balance_ << " euros " <<  std::endl;
}

void Account::set_credit_limit(int limit)

{

    if (has_credit_ == false) {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;

    }

    else {
        limit_ = limit;
    }

}

void Account::save_money(int money_deposit_)
{
    account_balance_ = account_balance_ + money_deposit_;
}

void Account::take_money(int money_withdrawal_)
{

    if (has_credit_ == false && (account_balance_ - money_withdrawal_ < 0)) {
        std::cout << "Cannot take money: balance underflow" << std::endl;
    }

    else if (has_credit_ == false && (account_balance_ - money_withdrawal_ > 0)) {
        account_balance_ = account_balance_ - money_withdrawal_;
        std::cout << money_withdrawal_ << " euros taken: new balance of FI00 1234 01 is 50" << std::endl;
    }

    else if (has_credit_ == true && account_balance_ - money_withdrawal_ > (account_balance_ * (-1))) {
        account_balance_ = account_balance_ - money_withdrawal_;
        std::cout << money_withdrawal_ << " euros taken: new balance of FI00 1234 03 is -10 euros" << std::endl;

    }

    else if (has_credit_ == true && account_balance_ - money_withdrawal_ < account_balance_ * (-1)) {
        std::cout << "Cannot take money: credit limit overflow" << std::endl;

    }

}

void Account::transfer_to(Account &owner, int transfer_amount)

{
    if (account_balance >= transfer_amount && has_credit_ == false) {
        account_balance = account_balance - transfer_amount;
        cout << transfer_amount <<  " euros taken: new balance of " << iban << " is " << account_balance << endl;
    }

    else if (has_credit_ == true && (transfer_amount > account_balance)) {
        account_balance = account_balance - transfer_amount;
        cout << transfer_amount <<  " euros taken: new balance of " << iban << " is " << account_balance << endl;
    }

    else if (has_credit_ == false && transfer_amount > account_balance) {
        cout << "Cannot take money: balance underflow" << "\n" << "Transfer from " << iban_ << " failed" << endl;
    }

    else if (transfer_amount < account_balance && has_credit_ == false ) {
        account_balance = account_balance - transfer_amount;
        cout << transfer_amount <<  " euros taken: new balance of " << iban << " is " << account_balance << endl;
    }

    else if (transfer_amount <= account_balance && has_credit_ == true) {
        account_balance = account_balance - transfer_amount;
        cout << transfer_amount <<  " euros taken: new balance of " << iban << " is " << account_balance << endl;
    }

}



// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

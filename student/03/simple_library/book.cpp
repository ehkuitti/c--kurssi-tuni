#include "book.hh"
#include <iostream>

Book::Book(const std::string& author, const std::string& title) :
    author_(author),
    title_(title),
    loan_date_(),
    expiry_date_(),
    is_loaned_(false)
{
}

void Book::print() const
{
    std::cout << author_ << " : " << title_ << "\n";
    if (!is_loaned_)
    {
        std::cout << "- available\n";
    }
    else
    {
        std::cout << "- loaned: ";
        loan_date_.print();
        std::cout << "- to be returned: ";
        expiry_date_.print();
    }
}

void Book::loan(const Date& loan_date)
{
    if(is_loaned_)
    {
        std::cout << "Already loaned: cannot be loaned\n";
        return;
    }

    loan_date_ = loan_date;
    expiry_date_ = loan_date;
    expiry_date_.advance(28);
    is_loaned_ = true;
}

void Book::renew()
{
    if (!is_loaned_)
    {
        std::cout << "Not loaned: cannot be renewed\n";
        return;
    }

    expiry_date_.advance(28);
}

void Book::give_back()
{
    is_loaned_ = false;
}

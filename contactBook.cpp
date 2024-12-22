// contactBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>
#include <sstream>
#include <optional>
#include <string>

class ContactBook
{
public:
    struct Contact{
        std::string name;
        std::string phoneNumber;
        std::string emailAddress;
        std::string toString() const;
    };

    std::vector<Contact> contactList{};
    void addNewContact(ContactBook::Contact& contact);
    std::optional<ContactBook::Contact> searchContact(std::string& phoneNumber) const;
    bool deleteContact(std::string& phoneNumber);
    void displayContacts();

};

int main()
{
    std::cout << "Enter 1 -> Add contact" << std::endl;
    std::cout << "Enter 2 -> Search contact" << std::endl;
    std::cout << "Enter 3 -> Delete contact" << std::endl;
    std::cout << "Enter 4 -> Display contact" << std::endl;
    std::cout << "Enter 5 -> Exit" << std::endl;
    int choice;
    ContactBook book;
    while (1)
    {
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            ContactBook::Contact contact;
            std::cout << "Enter name" << std::endl;
            std::cin >> contact.name;
            std::cout << "Enter phoneNumber" << std::endl;
            std::cin >> contact.phoneNumber;
            std::cout << "Enter emailAddress" << std::endl;
            std::cin >> contact.emailAddress;
            book.addNewContact(contact);
            std::cout << "Contact added" << std::endl;
        }
        break;
        case 2:
        {
            ContactBook::Contact contact;
            std::string phoneNumber;
            std::cout << "Enter phoneNumber" << std::endl;
            std::cin >> phoneNumber;
            auto ret = book.searchContact(phoneNumber);
            if (ret)
                std::cout << "Contact found" << ret->toString() << std::endl;
            else 
                std::cout << "Contact notfound" << std::endl;
        }
        break;
        case 3:
        {
            ContactBook::Contact contact;
            std::string phoneNumber;
            std::cout << "Enter phoneNumber" << std::endl;
            std::cin >> phoneNumber;
            bool ret = book.deleteContact(phoneNumber);
            std::cout << "Contact delete:" << (ret == true? "done" : "notfound") << std::endl;
        }
        break;
        case 4:
            book.displayContacts();
            break;
        case 5:
        {
            std::cout << "Exit" << std::endl;
            return 0;
        }
        default:
            std::cout << "invalid option" << std::endl;
        }
    }
    return 0;
}

void ContactBook::addNewContact(ContactBook::Contact& contact)
{
    contactList.push_back({ contact.name,contact.phoneNumber, contact.emailAddress});
}

std::optional<ContactBook::Contact> ContactBook::searchContact(std::string& phoneNumber) const
{
    auto it = std::find_if(contactList.begin(), contactList.end(), [=](const Contact& contact) {
        return(contact.phoneNumber == phoneNumber);
        });

    if (it == contactList.end())
    {
        return *it;
    }
    else
        return std::nullopt;
}

bool ContactBook::deleteContact(std::string& phoneNumber)
{
    auto it = std::remove_if(contactList.begin(), contactList.end(), [&](const Contact& contact) {
        return(contact.phoneNumber == phoneNumber);
        });

    if (it == contactList.end())
    {
        return false;
    }
    else
    {
        contactList.erase(it, contactList.end());
        return true;
    }
}

void ContactBook::displayContacts()
{
    for (auto item : contactList)
        std::cout << item.toString() << std::endl;
}

std::string ContactBook::Contact::toString() const
{
    std::ostringstream s;
    s << "Name: " << this->name;
    s << " Phone: " << this->phoneNumber;
    s << " e-mail: " << this->emailAddress;

    return s.str();
}
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>


// User Class
class User
{
    static int idCounter; // Static counter for unique IDs
    int id;
    std::string name;
    std::string password;
    double balance;

public:
    // Constructor
    User(const std::string &userName) : name(userName), balance(0)
    {
        id = ++idCounter; // Assign a unique ID
    }

    void setPassword(const std::string &pass)
    {
        password = pass;
        std::cout << "Account created for: " << name << " (Account No. " << id << ")" << std::endl;
    }

    bool verifyPassword(const std::string &pass) const
    {
        return password == pass;
    }

    std::string getName() const
    {
        return name;
    }

    void setBalance(double amount)
    {
        if (amount >= 0)
        {
            balance = amount;
            std::cout << amount << " has been credited to Account No. " << id << std::endl;
        }
        else
        {
            std::cout << "Invalid initial balance." << std::endl;
        }
    }

    void depositAmount(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            std::cout << amount << " has been credited to Account No. " << id << ". Total Balance: " << balance << std::endl;
        }
        else
        {
            std::cout << "Please enter a valid deposit amount." << std::endl;
        }
    }

    void withdrawAmount(double amount)
    {
        if (amount > 0 && balance >= amount)
        {
            balance -= amount;
            std::cout << amount << " has been debited from Account No. " << id << ". Total Balance: " << balance << std::endl;
        }
        else
        {
            std::cout << "Insufficient funds or invalid amount. Please try again." << std::endl;
        }
    }

    void displayDetails() const
    {
        std::cout << "User: " << name << " (Account No. " << id << "), Balance: " << balance << std::endl;
    }
};

// Initialize static counter
int User::idCounter = 0;

// Global user storage
std::vector<User> users;

// Function to create a new user
void createUser()
{
    std::cout << "Enter your username: ";
    std::string username;
    std::cin >> username;

    User newUser(username);

    std::cout << "Set your password: ";
    std::string password;
    std::cin >> password;
    newUser.setPassword(password);

    std::cout << "Set your Initial Amount: ";
    double balance;
    std::cin >> balance;
    newUser.setBalance(balance);

    users.push_back(newUser); // Add user to the global list
}

// Function to log in a user
User *loginUser()
{
    std::cout << "Enter your username: ";
    std::string username;
    std::cin >> username;

    std::cout << "Enter your password: ";
    std::string password;
    std::cin >> password;

    for (auto &user : users)
    {
        if (user.getName() == username && user.verifyPassword(password))
        {
            std::cout << "Login successful!" << std::endl;
            return &user;
        }
    }

    std::cout << "Invalid credentials!" << std::endl;
    return nullptr;
}

// Main Menu
void menu(User &user)
{
    while (true)
    {
        std::cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Logout\nEnter your choice: ";
        int choice;
        std::cin >> choice;

        // If input is invalid, clear the error and input buffer
        if (std::cin.fail())
        {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid choice. Please Choose a Valid Option." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        switch (choice)
        {
        case 1:
            user.displayDetails();
            break;
        case 2:
        {
            std::cout << "Enter deposit amount: ";
            double deposit;
            std::cin >> deposit;
            if (std::cin.fail() || deposit <= 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid amount. Please enter a valid number." << std::endl;
            }
            user.depositAmount(deposit);
            break;
        }
        case 3:
        {
            std::cout << "Enter withdrawal amount: ";
            double withdraw;
            std::cin >> withdraw;
            if (std::cin.fail() || withdraw <= 0)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid amount. Please enter a valid number." << std::endl;
            }
            user.withdrawAmount(withdraw);
            break;
        }
        case 4:
            std::cout << "Logging out..." << std::endl;
            return;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            break;
        }
    }
}

// Main Function
int main()
{
    std::cout << "Welcome to Classic Banking System" << std::endl;

    while (true)
    {
        std::cout << "1. Create Account\n2. Login\n3. Exit\nEnter your choice: ";
        int choice;
        std::cin >> choice;

        // If input is invalid, clear the error and input buffer
        if (std::cin.fail())
        {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
            std::cout << "Invalid choice. Please Choose a Valid Option." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        switch (choice)
        {
        case 1:
            createUser();
            break;
        case 2:
        {
            User *loggedInUser = loginUser();
            if (loggedInUser)
            {
                menu(*loggedInUser);
            }
            break;
        }
        case 3:
            std::cout << "Thank you for using Classic Banking System. Goodbye!" << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Try again." << std::endl;
            break;
        }
    }
}

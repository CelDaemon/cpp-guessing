#include <iostream>
#include <random>
#include <sstream>
#include <thread>

using namespace std;

random_device random_device;
default_random_engine generator(::random_device());
uniform_int_distribution distribution(1, 100);

optional<int> parse_number(const string& input) {
    size_t size;
    int result;
    try {
        result = stoi(input, &size);
        if(size != input.size()) return {};
    } catch (exception&) {
        return {};
    }
    return {result};
}

int main() {
    cout << "Guess the number between 1 and 100, you have 6 tries." << endl;
    const auto num = distribution(generator);
    auto guesses = 0;
    auto lost = false;
    while(true) {
        cout << "What is your guess?: ";
        string guess_string;
        getline(cin, guess_string);
        const auto guess = parse_number(guess_string);
        if(!guess || guess < 1 || guess > 100) {
            cout << "That was not a valid guess, please guess a number between 1 and 100" << endl;
            continue;
        }
        if(guess == num) {
            cout << "You guess correctly!" << endl;
            break;
        }
        if(guess < num) {
            cout << "Your guess was too low" << endl;
        } else if(guess > num) {
            cout << "Your guess was too high" << endl;
        }
        if(++guesses >= 6) {
            lost = true;
            cout << "You are out of guesses, you lost!" << endl;
            break;
        }
    }
    if(lost) {
        cout << "The correct number was: " << num << endl;
    }
    cout << "Press any key to continue: ";
    cin.ignore();
    cin.get();
}

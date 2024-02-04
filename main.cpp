#include <iostream> //input/output stream functionality
#include <string> //representing strings as objects
#include <fstream> //file handling
#include <map> //implements an ordered map/dictionary data structure
#include <cstdlib> //random function for random generating - rand()
#include <ctime> //for getting current date/time and converting between date formats
#include <algorithm> //algorithms like sorting, searching, copying etc that work on a range of data structures
#include <vector> // for vectors - vectors are dynamic so better than array and provides flexibility
#include <random> //tools for generating pseudo-random numbers with different distributions
#include <chrono> //timing utilities for measuring code

const int MAX_MOVIES = 100; // Maximum number of movies
const int MAX_RECOMMENDATIONS = 10; // Maximum number of recommendations

using namespace std;

//class movie used stores data on movies which has constructor
class Movie {
public:
    string title;
    string genre;
    Movie* next;

    Movie(const string& _title, const string& _genre) {
        title = _title;
        genre = _genre;
        next = nullptr;
    }
};

//used to manage movies list linked list is used for this
class MovieList {
public:
    Movie* head;

    //constructor which intialises head to be null
    MovieList() {
        head = nullptr;
    }

    //function to add new movie ie insert node at beginning
    void addMovie(const string& title, const string& genre) {
        Movie* newMovie = new Movie(title, genre);
        newMovie->next = head;
        head = newMovie;
    }

    //userGenre: The genre for which the user wants movie recommendations, recommendedMovies:
    //A vector of strings where the recommended movie titles will be stored.
    //maxRecommendations: The maximum number of recommendations the method should generate.

    void recommendMovies(const string& userGenre, vector<string>& recommendedMovies, int maxRecommendations) {
        Movie* current = head;

        vector<string> genreMovies;
        while (current != nullptr) {
            if (current->genre == userGenre) {
                genreMovies.push_back(current->title);
            }
            current = current->next;
        }

        //creates random seed using epoch function for unique time stamp

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        //used for shuffling movies in the list
        shuffle(genreMovies.begin(), genreMovies.end(), std::default_random_engine(seed));

        for (int i = 0; i < maxRecommendations && i < genreMovies.size(); i++) {
            recommendedMovies.push_back(genreMovies[i]);
        }
    }
};

int main() {
    MovieList movieList;
    MovieList genreLists[MAX_MOVIES];

    ifstream file("movies.txt");
    if (file.is_open()) {
       // string variable 'line' to store each line from the file
        string line;
        while (getline(file, line)) {
            //finds position of the dash separating the movie title from genre
            size_t dashPos = line.find(" - ");
            if (dashPos != string::npos) {
                string title = line.substr(0, dashPos);
                string genre = line.substr(dashPos + 3);
                movieList.addMovie(title, genre);

                bool genreExists = false;
                for (int i = 0; i < MAX_MOVIES; i++) {
                    if (genreLists[i].head && genreLists[i].head->genre == genre) {
                        genreExists = true;
                        break;
                    }
                }
                if (!genreExists) {
                    for (int i = 0; i < MAX_MOVIES; i++) {
                        if (genreLists[i].head == nullptr) {
                            genreLists[i].addMovie(title, genre);
                            break;
                        }
                    }
                }
            }
        }
        file.close();
    } else {
        cerr << "Failed to open the file.\n";
        return 1;
    }

    string name;
    int id;
    int age;

    cout << "\t\t\tMOVIE RECOMMENDATION SYSTEM\t\t\t\t\n\n";

    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your id: ";
    cin >> id;
    cout << "Enter your age: ";
    cin >> age;

    if (age < 18) {
        cout << "Movies recommended by this system should not be watched without adult supervision.\nPROGRAM IS SHUTTING DOWN\n";
        return 0;
    }

    string favoriteActor, favoriteGenre;

    cout << "Enter your favorite actor: ";
    cin.ignore();
    getline(cin, favoriteActor);
    cout << "Enter your favorite genre: ";
    getline(cin, favoriteGenre);

    map<string, int> genreFrequency;
    vector<string> otherGenres;
    int otherGenreCount = 0;

    for (int i = 0; i < 5; i++) {
        cout << "Enter your favorite movie title #" << i + 1 << ": ";
        string title;
        cin.ignore();
        getline(cin, title);
        cout << "Enter the genre of the movie: ";
        string genre;
        getline(cin, genre);
        if (genre == favoriteGenre) {
            genreFrequency[genre]++;
        } else {
            otherGenres.push_back(genre);
        }
    }
ofstream userFile("user_inputs.txt", ios::app);

if (userFile.is_open()) {
    userFile << "Hello, " << name << "!\n";
    userFile << "Your ID is: " << id << "\n";
    userFile << "Your age is: " << age << "\n";
    userFile << "Your preferred genre is: " << favoriteGenre << "\n";
    userFile << "Your favorite actor is: " << favoriteActor << "\n";
    // You can also save other user inputs (favorite movies, genres) here.
    userFile.close();
}
else {
    cerr << "Failed to open the user inputs file.\n";
}

    vector<string> recommendedMovies;

    // Recommend movies based on the user's favorite genre
    int preferredGenreRecommendations = MAX_RECOMMENDATIONS / 2;
    int otherGenreRecommendations = MAX_RECOMMENDATIONS - preferredGenreRecommendations;

    movieList.recommendMovies(favoriteGenre, recommendedMovies, preferredGenreRecommendations);

    // Shuffle the otherGenres list to make recommendations random
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(otherGenres.begin(), otherGenres.end(), std::default_random_engine(seed));

    for (int i = 0; i < otherGenreRecommendations && i < otherGenres.size(); i++) {
        movieList.recommendMovies(otherGenres[i], recommendedMovies, 1);
    }

  cout << "\n\nHello " << name << " to the movie recommendation system\n";
cout << "Your ID is " << id << "\n";
cout << "Your age is " << age;
if (age >= 18) {
    cout << " so you are not underage to use this system\n";
}
else {
    cout << " so you are underage to use this system\n";
}

cout << "Your preferred genre is " << favoriteGenre << " and your favorite actor is " << favoriteActor << "\n";
cout << "So, these are the movie recommendations for you:\n\n";

// Loop to display recommended movies
for (const string& movieTitle : recommendedMovies) {
    Movie* current = movieList.head;
    while (current != nullptr) {
        if (current->title == movieTitle) {
            cout << current->genre << ": " << movieTitle << "\n";
            break;
        }
        current = current->next;
    }
}

    return 0;
}

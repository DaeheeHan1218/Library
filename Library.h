#ifndef LIBRARY_H
#define LIBRARY_H

#include "Record.h"
#include "TemplatedDLList.h"
#include <cctype>
#include <vector>

class Library {
    public:
        //Searches for a title in the database and returns vector of matching records
        std::vector<Record> search(std::string title);

        //Imports records from a file.  Does not import duplicates.
        // Return the number of records added to the database
        int import_database(std::string filename);

        //Exports the current database to a file
        //Return the number of records exported
        int export_database(std::string filename);

        void print_database();

        //add record to database, avoid complete duplicates
        bool add_record(Record book);

        //Deletes a record from the database
        void remove_record(Record book);

        //Prompts user for yes or no and returns choice Y or N
        char prompt_yes_no();

        //Given a vector of menu options returns index of choice
        int prompt_menu(std::vector<std::string>);

        //Prompts user for a new record
        Record prompt_record();

        //Prompt for a valid title
        std::string prompt_title();

        // Prompt for a valid string
        std::string prompt_string(std::string prompt);
    private:
        std::vector<DLList<Record>> book_db = vector<DLList<Record>>(26);
};

#endif
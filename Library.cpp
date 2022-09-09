#include <fstream>
#include <limits>
#include "Library.h"
#include "TemplatedDLList.h"

std::vector<Record> Library::search(std::string title){
	std::vector<Record> found;
	char first_letter = title.at(0);
	first_letter = toupper(first_letter);
	int index = first_letter - 65;
	DLListNode<Record>* temp = book_db[index].first_node();
	while(temp != book_db[index].after_last_node()){
		if(temp->obj.get_title() == title){
			found.push_back(temp->obj);
		}
		temp = temp->next;
	}
	return found;
}

int Library::import_database(std::string filename){
	Record tempRec;
	int count = 0;
	char first_letter;
	int index;
	DLListNode<Record>* tempNode;
	std::ifstream ifs(filename);
    while(ifs >> tempRec){
		first_letter = tempRec.get_title().at(0);
		first_letter = toupper(first_letter);
		index = first_letter - 65;
		tempNode = book_db[index].first_node();
		if(tempNode == book_db[index].after_last_node()){
			book_db[index].insert_first(tempRec);
			count++;
		}
		else{
			while(tempNode != book_db[index].after_last_node()){
				if(tempNode->obj == tempRec){
					break;
				}
				if(tempNode->obj.get_title().compare(tempRec.get_title()) < 0){
					book_db[index].insert_before(*tempNode, tempRec);
					count++;
					break;
				}
				else if(tempNode->obj.get_title().compare(tempRec.get_title()) == 0){
					if(tempNode->obj.get_author().compare(tempRec.get_author()) < 0){
						book_db[index].insert_before(*tempNode, tempRec);
						count++;
						break;
					}
					else if(tempNode->obj.get_author().compare(tempRec.get_author()) == 0){
						if(tempNode->obj.get_edition().compare(tempRec.get_edition()) < 0){
							book_db[index].insert_before(*tempNode, tempRec);
							count++;
							break;
						}
					}
				}
				tempNode = tempNode->next;
				if(tempNode == book_db[index].after_last_node()){
					book_db[index].insert_last(tempRec);
					count++;
					break;
				}
				
			}
		}
    }
	ifs.close();
	return count;
}

int Library::export_database(std::string filename){
	std::ofstream ofs(filename);
	DLListNode<Record>* tempNode;
	int count = 0;
	ofs << "\n";
	for(int i = 0; i < book_db.size(); i++){
		tempNode = book_db[i].first_node();
		while(tempNode != book_db[i].after_last_node()){
			ofs << tempNode->obj << "\n";
			count++;
			tempNode = tempNode->next;
		}
	}
	ofs << "     ";
	ofs.close();
	return count;
}

void Library::print_database(){
	DLListNode<Record>* tempNode;
	for(int i = 0; i < book_db.size(); i++){
		tempNode = book_db[i].first_node();
		while(tempNode != book_db[i].after_last_node()){
			std::cout << tempNode->obj << "\n";
			tempNode = tempNode->next;
		}
	}
}

bool Library::add_record(Record book){
	char first_letter = book.get_title().at(0);
	first_letter = toupper(first_letter);
	int index = first_letter - 65;
	DLListNode<Record>* tempNode = book_db[index].first_node();
	bool added = false;
	if(tempNode == book_db[index].after_last_node()){
		book_db[index].insert_first(book);
		added = true;
	}
	else{
		while(tempNode != book_db[index].after_last_node()){
			if(tempNode->obj == book){
				break;
			}
			if(tempNode->obj.get_title().compare(book.get_title()) < 0){
				book_db[index].insert_before(*tempNode, book);
				added = true;
				break;
			}
			else if(tempNode->obj.get_title().compare(book.get_title()) == 0){
				if(tempNode->obj.get_author().compare(book.get_author()) < 0){
					book_db[index].insert_before(*tempNode, book);
					added = true;
					break;
				}
				else if(tempNode->obj.get_author().compare(book.get_author()) == 0){
					if(tempNode->obj.get_edition().compare(book.get_edition()) < 0){
						book_db[index].insert_before(*tempNode, book);
						added = true;
						break;
					}
					else if(tempNode->obj.get_edition().compare(book.get_edition()) == 0){
						break;
					}
				}
			}
			tempNode = tempNode->next;
			if(tempNode == book_db[index].after_last_node()){
				book_db[index].insert_last(book);
				added = true;
				break;
			}
		}
	}
	return added;
}

void Library::remove_record(Record book){
	char first_letter = book.get_title().at(0);
	first_letter = toupper(first_letter);
	int index = first_letter - 65;
	DLListNode<Record>* tempNode = book_db[index].first_node();
	while(tempNode != book_db[index].after_last_node()){
		if(tempNode->obj == book){
			tempNode = tempNode->next;
			book_db[index].remove_before(*tempNode);
			break;
		}
		tempNode = tempNode->next;
	}
}

char Library::prompt_yes_no(){
	char answer;
	while(answer != 'Y' && answer != 'N'){
		std::cout << "Please Enter Y/N\n";
		std::cin >> answer;
		std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return answer;
}

int Library::prompt_menu(std::vector<std::string> vec){
	int answer;
	std::cout << "Please select an option\n";
	for(int i = 0; i < vec.size(); i++){
		std::cout << (i + 1) << ". " << vec[i] << "\n";
	}
	std::cin >> answer;
	std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
	answer --;
	return answer;
}

Record Library::prompt_record(){
	std::string t, a, i, y, e;
	Record rec;
	std::cout << "Please enter a title\n";
	getline(std::cin, t);
	std::cout << "Please enter a author\n";
	getline(std::cin, a);
	std::cout << "Please enter a ISBN\n";
	getline(std::cin, i);
	std::cout << "Please enter a year\n";
	getline(std::cin, y);
	std::cout << "Please enter a edition\n";
	getline(std::cin, e);
	rec.set_title(t);
	rec.set_author(a);
	rec.set_ISBN(i);
	rec.set_year(y);
	rec.set_edition(e);
	return rec;
}

std::string Library::prompt_title(){
	std::string t;
	std::cout << "Please enter a title\n";
	getline(std::cin, t);
	return t;
}

std::string Library::prompt_string(std::string prompt){
	std::string t;
	std::cout << prompt << "\n";
	getline(std::cin, t);
	return t;
}
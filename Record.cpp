//implementation of record class

#include "Record.h"

std::string Record::get_title() const{
	return title;
}

std::string Record::get_author()const{
	return author;
}

std::string Record::get_ISBN()const{
	return ISBN;
}

std::string Record::get_year()const{
	return year;
}

std::string Record::get_edition()const{
	return edition;
}

void Record::set_title(std::string t){
	title = t;
}

void Record::set_author(std::string a){
	author = a;
}

void Record::set_ISBN(std::string i){
	ISBN = i;
}

void Record::set_year(std::string y){
	year = y;
}

void Record::set_edition(std::string e){
	edition = e;
}

std::istream& operator>>(std::istream& is, Record& rec){
	std::string t, a, i, y, e;
	getline(is, t);
	getline(is, t);
	getline(is, a);
	getline(is, i);
	getline(is, y);
	getline(is, e);
	rec.set_title(t);
	rec.set_author(a);
	rec.set_ISBN(i);
	rec.set_year(y);
	rec.set_edition(e);
	return is;
}

std::ostream& operator<<(std::ostream& os, Record& rec){
	os << rec.get_title() << "\n" << rec.get_author() << "\n" << rec.get_ISBN() << "\n" << rec.get_year() << "\n" << rec.get_edition() << "\n";
	return os;
}

bool operator==(const Record& r1, const Record& r2){
	Record temp1, temp2;
	temp1 = r1;
	temp2 = r2;
	if(temp1.get_title() != temp2.get_title()){
		return false;
	}
	else if(temp1.get_author() != temp2.get_author()){
		return false;
	}
	else if(temp1.get_ISBN() != temp2.get_ISBN()){
		return false;
	}
	return true;
}
//This file contains the implementation of database class. 

#include <iostream>
#include <string>
#include "record.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;




class Database {

private: 

	int capacity = 10;
	int size = 0;
	Stock* arr;

public:

	//constructor
	Database()
	: capacity(10), size(0), arr(new Stock[capacity])
	{
		
		ifstream fin("database.txt");
		if (fin.is_open()){
			string line;
			while(getline(fin, line)){
				stringstream ss(line);

				string company_name;
				string market; 
				string current_price;
				string intrinsic_value;
				string rating;
				Stock s;
			
				getline(ss, company_name, ',');
				s.set_company_name(company_name);
				getline(ss, market, ',');
				s.set_market(market);
				getline(ss, current_price, ',');
				s.set_current_price(stod(current_price));
				getline(ss, intrinsic_value, ',');
				s.set_intrinsic_value(stod(intrinsic_value));
				getline(ss, rating, ',');
				s.set_rating(rating);

				add(s);
			}
		}

		fin.close();

	}

	//method to get size of the array
	int get_size(){
		return size;
	}


	//method to add a new record
	void add(Stock s){
		if (size < capacity){
			arr[size] = s;
			size++;
		} else {
			Stock* data = new Stock[capacity*2];
			for (int i = 0; i < size; i++){
				data[i] = arr[i];
			}
			data[size] = s;
			size++;
			capacity = capacity*2;
			delete[] arr;
			arr = data;
			data = nullptr;
		}

	}

	//method to check if a record already exist in the database
	int stock_exists(Stock s){
		for (int i = 0; i < size; i++){
			if (s.same_stock(arr[i]) == 1){
				cout << "\nError: Based on your entered values, we found an exactly same stock";
				cout << " existing in the database. Adding Stock unsuccessful.\n";
				return 1;
			}	
		}

		return 0;
	}

	//method to check if an input string exactly matches with the company name of any stock.
	void company_name_match_find(string input){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if (lower_case(arr[i].get_company_name()) == lower_case(input)){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " << arr[i].get_market() 
				<< ", " << arr[i].get_current_price() << ", " << arr[i].get_intrinsic_value() 
				<< ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "\nSorry! There is no Stock with company name same as your input.\n";
		}

	}


	//method to check if a string is contained in company name
	void company_name_contains_find(string input){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if ((lower_case(arr[i].get_company_name())).find(lower_case(input)) != std::string::npos){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "\nSorry! couldn't find any stock which has company name that contains you entered input.\n";
		}

	}

	//method to check if a string exactly matches with the market segment of a stock
	void market_segment_match_find(string input) {
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if (lower_case(arr[i].get_market()) == lower_case(input)){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;

			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has market segment exactly same as what you typed.\n";

		}

	}

	//method to check if a string is conained in a stock's market segment
	void market_segment_contains_find(string input){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if ((lower_case(arr[i].get_market())).find(lower_case(input)) != std::string::npos){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}	
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has market segment which contains your typed input.\n";
		}

		
	}

	//method to list all the stocks that has current price exactly equal to entered price
	void current_price_match_find(double input){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_current_price() == input){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;					
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has current price exactly equal to what you have entered.\n";

		}

	}

	//method to list all the stocks whose current price lies within a given range
	void current_price_range_find(double lower_limit, double upper_limit){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_current_price() >= lower_limit && arr[i].get_current_price() <= upper_limit){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock which has current price within your entered price range.\n";

		}

		
	}


	//method to list all the stocks that has intrinsic value exactly equal to entered price
	void intrinsic_value_match_find(double input){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_intrinsic_value() == input){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has fair value exactly equal to what you have entered.\n";

		}

	
	}


	//method to list all the stocks that has intrinsic value within an entered range by the user
	void intrinsic_value_range_find(double lower_limit, double upper_limit){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_intrinsic_value() >= lower_limit && arr[i].get_intrinsic_value() <= upper_limit){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count  == 0){
			cout << "Sorry! couldn't find any stock that has fair value within your entered range.\n";
		}

		
	}


	//method to list all the stocks that has rating exact as the input in the method
	void rating_match_find(string input){
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if (lower_case(arr[i].get_rating()) == lower_case(input)){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock with matching rating.\n";
		}

	
	}


	//method to list all the stocks that has rating that contains user input as a substring
	void rating_contains_find(string input){
		
		
		int count = 0;
		for (int i = 0; i < size; i++){
			if ((lower_case(arr[i].get_rating())).find(lower_case(input)) != std::string::npos){
				
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has rating which contains your entered letters/words in it.\n";
		}

		
	}

	//method to check if an input string exactly matches with the company name of any stock.
	int* company_name_match_delete(string input){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if (lower_case(arr[i].get_company_name()) == lower_case(input)){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "\nSorry! There is no Stock with company name same as your input.\n";
		}

		return searched_index;
	}


	//method to check if a string is contained in company name
	int* company_name_contains_delete(string input){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if ((lower_case(arr[i].get_company_name())).find(lower_case(input)) != std::string::npos){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "\nSorry! couldn't find any stock which has company name that contains you entered input.\n";
		}

		return searched_index;
	}

	//method to check if a string exactly matches with the market segment of a stock
	int* market_segment_match_delete(string input) {
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if (lower_case(arr[i].get_market()) == lower_case(input)){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;

			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has market segment exactly same as what you typed.\n";

		}
		return searched_index;
	}

	//method to check if a string is conained in a stock's market segment
	int* market_segment_contains_delete(string input){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if ((lower_case(arr[i].get_market())).find(lower_case(input)) != std::string::npos){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}	
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has market segment which contains your typed input.\n";
		}

		return searched_index;
	}

	//method to list all the stocks that has current price exactly equal to entered price
	int* current_price_match_delete(double input){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_current_price() == input){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;					
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has current price exactly equal to what you have entered.\n";

		}

		return searched_index;
	}

	//method to list all the stocks whose current price lies within a given range
	int* current_price_range_delete(double lower_limit, double upper_limit){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_current_price() >= lower_limit && arr[i].get_current_price() <= upper_limit){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock which has current price within your entered price range.\n";

		}

		return searched_index;
	}


	//method to list all the stocks that has intrinsic value exactly equal to entered price
	int* intrinsic_value_match_delete(double input){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_intrinsic_value() == input){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has fair value exactly equal to what you have entered.\n";

		}

		return searched_index;
	}


	//method to list all the stocks that has intrinsic value within an entered range by the user
	int* intrinsic_value_range_delete(double lower_limit, double upper_limit){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if (arr[i].get_intrinsic_value() >= lower_limit && arr[i].get_intrinsic_value() <= upper_limit){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count  == 0){
			cout << "Sorry! couldn't find any stock that has fair value within your entered range.\n";
		}

		return searched_index;
	}


	//method to list all the stocks that has rating exact as the input in the method
	int* rating_match_delete(string input){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if (lower_case(arr[i].get_rating()) == lower_case(input)){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock with matching rating.\n";
		}

		return searched_index;
	}


	//method to list all the stocks that has rating that contains user input as a substring
	int* rating_contains_delete(string input){
		int* searched_index = new int[size];
		for (int i = 0; i < size; i++){
			searched_index[i] = 10000000;
		}
		int index = 0;
		int count = 0;
		for (int i = 0; i < size; i++){
			if ((lower_case(arr[i].get_rating())).find(lower_case(input)) != std::string::npos){
				searched_index[index] = i;
				index++;
				cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
				<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
				<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				count++;
			}
		}

		if (count == 0){
			cout << "Sorry! couldn't find any stock that has rating which contains your entered letters/words in it.\n";
		}

		return searched_index;
	}


	//method to delete a particular stock from the array at a particular index
	void delete_stock_record(int i){
		arr[i] = arr[size - 1];
		arr[size - 1].set_company_name("");
		arr[size - 1].set_market("");
		arr[size - 1].set_current_price(0.01);
		arr[size - 1].set_intrinsic_value(0.01);
		arr[size - 1].set_rating("");
		size--;
	}



	//method to sort the records in alphabetical order based on their company names
	//reference for function below is from course notes
	void sort_company_name(){
		
		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while(j >= 0 && lower_case(arr[j].get_company_name()) > lower_case(key.get_company_name())){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;


		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}


	}

	//method to sort the records based on company name in reverse alphabetical order
	void reverse_sort_company_name(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while (j >= 0 && lower_case(arr[j].get_company_name()) < lower_case(key.get_company_name())){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;
		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " << arr[i].get_intrinsic_value() 
			<< ", " << arr[i].get_rating() << ".\n";
				
		}

	}


	//method to sort the records based on market segment in alphabetical order 
	void sort_market(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while(j >= 0 && lower_case(arr[j].get_market()) > lower_case(key.get_market())){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;


		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}


	//method to sort the records based on market segment in reverse alphabetical order
	void reverse_sort_market(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while (j >= 0 && lower_case(arr[j].get_market()) < lower_case(key.get_market())){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;
		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}


	//method to sort the records based on current price in ascending order
	void sort_current_price(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while(j >= 0 && arr[j].get_current_price() > key.get_current_price()){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;


		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}

	//method to sort the records based on current price in descending order
	void reverse_sort_current_price(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while (j >= 0 && arr[j].get_current_price() < key.get_current_price()){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;
		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}

	//method to sort the records based on fair price in ascending order
	void sort_intrinsic_value() {

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while(j >= 0 && arr[j].get_intrinsic_value() > key.get_intrinsic_value()){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;


		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}

	//method to sort the records based on fair price in descending order
	void reverse_sort_intrinsic_value(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while (j >= 0 && arr[j].get_intrinsic_value() < key.get_intrinsic_value()){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;
		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}

	//method to sort the record based on rating in alphabetical order
	void sort_rating(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while(j >= 0 && lower_case(arr[j].get_rating()) > lower_case(key.get_rating())){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;


		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}

	//method to sort the records based on rating in the reverse alphabetical order
	void reverse_sort_rating(){

		for (int i = 1; i < size; i++){

			Stock key = arr[i];
			int j = i - 1;

			while (j >= 0 && lower_case(arr[j].get_rating()) < lower_case(key.get_rating())){
				arr[j+1] = arr[j];
				j--;
			}

			arr[j+1] = key;
		}

		for (int i = 0; i < size; i++){
			cout << "(" << i + 1 << ") " << arr[i].get_company_name() << ", " 
			<< arr[i].get_market() << ", " << arr[i].get_current_price() << ", " 
			<< arr[i].get_intrinsic_value() << ", " << arr[i].get_rating() << ".\n";
				
		}

	}


	//destructor
	~Database()
	{
		//saving the changes to file database.txt
		ofstream fout("database.txt");
		if (fout.is_open()){
			for (int i = 0; i < size; i++){
				fout << arr[i].get_company_name() << "," << arr[i].get_market() 
				<< "," << arr[i].get_current_price() << "," << arr[i].get_intrinsic_value() 
				<< "," << arr[i].get_rating() << "\n";
			}
		}
		fout.close();


		delete[] arr;
		arr = nullptr;
	}
}; //Database class

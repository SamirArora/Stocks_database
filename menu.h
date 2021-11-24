//This file contains the implementation of menu class

#include <iostream>
#include <string>
#include "database.h"
#include <algorithm>



//creating a different version of getline because every input from user contains "\n" character, 
//which will cause problem when we call multiple getline()
//reference for this function is taken from: 
//https://stackoverflow.com/questions/35242971/getline-function-is-skipping-inputs
string my_getline()
{
    string result;

    while (!getline(cin, result) || result.empty());

    
    return result;
}



int is_double(string input){
	try {
		stod(input);
	} catch(...) {
		return 0;
	}
	return 1;
	
}

int is_int(string input){
	try {
		stoi(input);
	} catch(...) {
		return 0;
	}
	return 1;
}

double limit_eval(string limit){

	while (is_double(limit) != 1){
		cout << "Invalid input. Make sure you are entering a number. Please try again.\n";
		limit = my_getline();
		
	}
	double value = stod(limit);
	return value;
}

//creating a function to evaluate the market segment input of user
string market_seg_eval(){
	string m = my_getline();
	if (lower_case(m) == "small-cap" || lower_case(m) == "medium-cap" || lower_case(m) == "large-cap" || lower_case(m) == "mega-cap"){
		//accept it and do nothing;
	} else {
		cout << "Invalid input for market segment. Make sure your input is same as one of the";
		cout << " applicable entries given below:\n";
		cout << "Applicable entries: 'small-cap', 'medium-cap', 'large-cap', and 'mega-cap'.\n";
		m = market_seg_eval();
	}

	return m;
}

//creating a function to evaluate current price input from the user
double current_price_eval(string curr_string){
	while (is_double(curr_string) != 1){
		cout << "Invalid input. Current price must be a number. Please try again.\n";
		curr_string = my_getline();
	}
	double c = stod(curr_string);
	if (c > 0){
		//accept it and do nothing
	} else {
		cout << "Invalid input for price, share price can never be 0 or negative. Please try again.\n";
		curr_string = my_getline();
		current_price_eval(curr_string);
	}

	return c;
}

//creating a function to evaluate fair price input from the user
double fair_price_eval(string fair_string){
	while (is_double(fair_string) != 1){
		cout << "Invalid input. Fair value must be a number. Please try again.\n";
		fair_string = my_getline();
		
	}
	double i = stod(fair_string);
	if (i > 0){
		//accept it and do nothing
	} else {
		cout << "Invalid input for fair price of the stock, stock price can never be 0 or negative. Please try again.\n";
		fair_string = my_getline();
		fair_price_eval(fair_string);
	}

	return i;
}

//creating a function to evaluate rating input from the user
string rating_eval(double c, double i){
	string r = my_getline();
	//if current price is greater than fair price: only applicable ratings are 'hold' and 'sell'
	if (c > i){
		if (lower_case(r) == "hold" || lower_case(r) == "sell"){
			//do nothing;
		} else {
			cout << "Based on the current price and fair price entries, your rating input is invalid. Applicable entries are either 'hold', or 'sell'. Please enter a valid rating:\n";
			r = rating_eval(c, i);
		}
	} else {
		if (lower_case(r) == "hold" || lower_case(r) == "buy"){
			//do nothing
		} else {
			cout << "Based on your current price and fair price entries, your rating input is invalid. Applicable entries are either 'buy' or 'hold'. Please enter a valid rating:\n";
			r = rating_eval(c, i);
		}
	}

	return r;
}

//creating a function to check if the user chooses from one of the given choices
int choice_eval(int begin, int end){
	string choice;
	choice = my_getline();
	while (is_int(choice) != 1){
		cout << "Invalid input. Please try again.\n";
		choice = my_getline();
	}
	int choice_int = stoi(choice);
	if (choice_int >= begin && choice_int <= end){
		//accept it do nothing
	} else {
		cout << "\nError: Make sure your input is between " << begin << " and " << end << " . Please enter again:\n";
		choice_int = choice_eval(begin, end);
	}

	return choice_int;
}


class Menu {

private:

	string option;
	Database data;


public:

	//constructor
	Menu()
	{ }

	//method to evaluate the option entered by user
	void option_eval(string option){
		while (is_int(option) != 1){
			cout << "Invalid input. Make sure you are entering a number.\n";
			option = my_getline();
		}
		int opt = stoi(option);
		if (opt >= 1 && opt <= 5){
			if (opt == 1){
				Add_stock();
			} else if (opt == 2){
				Find_stock();
			} else if (opt == 3){
				Delete_stock();
			} else if (opt == 4){
				List_stock();
			} else if (opt == 5){
				Quit();
			}
		} else {
			cout << "Sorry, the number you have entered, does not match with any of the option. Make sure you adding number between 1 to 5; try again:)\n\n";
			option = my_getline();
			option_eval(option);
		}
	}

	//method to call the main menu
	void main_menu(){
		cout << "\n\nWelcome to the Stocks Database.\n\n";
		cout << "...............................\n\n\n\n";
		cout << "Please choose from one of the following option by typing their respective numbers:\n\n";
		cout << "(1) Add a Stock.\n";
		cout << "(2) Find a Stock.\n";
		cout << "(3) Delete a Stock.\n";
		cout << "(4) List Stocks.\n";
		cout << "(5) Quit.\n\n";
		option = my_getline();
		option_eval(option);
	}

	//method if user choose to add a stock
	void Add_stock(){
		cout << "\nAdd Stock\n";
		cout << "\n..........\n";
		//collecting information from the user
		string n = "";
		string m = "";
		double c = 0;
		double i = 0;
		string r = "";

		cout << "To add a Stock, please answer the following questions.\n";
		cout << "What is the name of the company?\n";
		n = my_getline();

		cout << "What is the market segment of the company?\n";
		cout << "Acceptable entries are: 'small-cap', 'medium-cap', 'large-cap', 'mega-cap'.\n";
		m = market_seg_eval();

		cout << "Please enter the current price of the stock in dollars.\n";
		string curr_string;
		curr_string = my_getline();
		c = current_price_eval(curr_string);//this function will check if you enter a string or enter 0, or negative share price
		

		cout << "Please enter the intrinsic value or fair price of the stock in dollars.\n";
		string fair_string;
		fair_string = my_getline();
		i = fair_price_eval(fair_string);//this function will check if you enter a string or 0 or  negative fair price for the share	

		cout << "Please enter the 'buy', 'hold', or 'sell' rating of the stock.\n";
		r = rating_eval(c, i);//this function will check that your input is valid for rating based on what you entered for current price and fair price

		//creating the stock
		Stock s(n, m, c, i, r);

		//checking if stock already exist in the database
		if (data.stock_exists(s) == 1){
			main_menu();
			return;
		} else {

		}

		//adding the stock in the database
		data.add(s);
		cout << "\nYour Stock has been successfully added to the database.\n";
		cout << "\n.......................................................\n";

		//go back to the main menu
		main_menu();
	}



	//method if user chooses to find a stock
	void Find_stock(){

		

		int choice = 0;

		cout << "\n\nFind a Stock\n\n";
		cout << "............\n\n\n\n";
		cout << "You can search by:\n\n\n\n";
		cout << "(1) Company name of the stock.\n";
		cout << "(2) Market segment of the stock (small-cap, medium-cap, large-cap, medium-cap).\n";
		cout << "(3) Current price of the stock.\n";
		cout << "(4) Fair price of the stock.\n";
		cout << "(5) Rating of the stock.\n\n";
		cout << "(6) Return to the main menu.\n";

		choice = choice_eval(1, 6);

		//if user chooses to search using company name
		if (choice == 1){
			int search_choice;
			cout << "\n\nYou can search using one of the given methods (Please enter 1 or 2):\n";
			cout << "(1) Do you know the exact name of the company. If yes, then you should enter 1,";
			cout << " as this search method will present those stocks which has company name exactly";
			cout << " same as what you enter.\n";
			cout << "(2) If you are not sure about the companu name and only know few alphabets or words,";
			cout << " choose option 2, as this option will present all the stocks which has company name that";
			cout << " contains your input words.\n\n";
			search_choice = choice_eval(1, 2);

			//if user wants to find stock with company name exactly same as what he/she enters.
			if (search_choice == 1){
				string input;
				cout << "\nPlease enter the company name of the stock you are looking for.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.company_name_match_find(input);
				main_menu();
			}

			//if user wants to find stocks with company name containing the string he/she enters.
			if (search_choice == 2){
				string input;
				cout << "\nPlease enter the words you think are present in company name.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.company_name_contains_find(input);
				main_menu();
			}

			
		}


		//if user chooses to find stocks using market segment
		if (choice == 2){
			int search_choice;
			cout << "\n\nYou can search using one of the given methods (Please enter 1 or 2):\n";
			cout << "(1) If you know the exact name of the market segment, choose option 1.";
			cout << " This search method will look for stocks with market segment exactly same as what you enter.\n";
			cout << "(2) If you don't know the exact market segment and know few words or";
			cout << " letters from it, choose option 2. This search method will list all the stocks which has";
			cout << " market segment name that contains your input.\n\n";
			search_choice = choice_eval(1, 2);

			//if user chooses to look for exact market segment he/she types
			if (search_choice == 1){
				string input;
				cout << "\nPlease enter the exact market segment you want to search for.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.market_segment_match_find(input);
				main_menu();
			}

			//if user doesn't know the exact market segment
			if (search_choice == 2){
				string input;
				cout << "\nPlease enter the words you think are present in the market segment.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.market_segment_contains_find(input);
				main_menu();
			}

			
		}


		//if user chooses to find the stock using current price of the stock
		if  (choice  == 3){
			int search_choice;
			cout << "\n\nYou can search using one of the given methods (please choose 1 or 2):\n";
			cout << "(1) You want to find a stock that has current price exactly equal to what you enter.\n";
			cout << "(2) You want to find a stock that has current price within your entered range.\n\n";
			search_choice = choice_eval(1, 2);


			//if user chooses to use an exact price
			if (search_choice == 1){
				
				cout << "\nPlease enter the exact current price you want to search for.\n";
				string input = my_getline();
				double price_input = limit_eval(input);
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.current_price_match_find(price_input);
				main_menu();
			}

			//if user chooses to use a range of prices
			if (search_choice == 2){
				double lower_limit;
				double upper_limit;
				cout << "\nPlease enter the lower limit of your current price range.\n";
				string llimit = my_getline();
				lower_limit = limit_eval(llimit);
				cout << "\nPlease enter the upper limit of your current price range.\n";
				string ulimit = my_getline();
				upper_limit = limit_eval(ulimit);

				//if user accidentally enetered reversed input, i.e., lower_limit is greater than upper_limit
				if (lower_limit > upper_limit){
					cout << "\nThe input receieved for lower limit is greater than upper limit.";
					cout <<" I will interchange lower limit and upper limit.\n";
					double temp = lower_limit;
					lower_limit = upper_limit;
					upper_limit = temp;
				}
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.current_price_range_find(lower_limit, upper_limit);
				main_menu();
			}

			
		}



		//if user chooses to find the stock using intrinsic value
		if (choice == 4){
			int search_choice;
			cout << "\n\nYou can search using one of the given method (Please enter 1 or 2):\n";
			cout << "(1) You want to find a stock which has fair value exactly equal to what you enter.\n";
			cout << "(2) You want to find all the stocks that has fair value within your entered range.\n\n";
			search_choice = choice_eval(1, 2);

			//if user wants to list all the stock that has intrinsic value exactly equal to what he/she enters
			if (search_choice == 1){
				
				cout << "\nPlease enter the exact fair value you want to search for.\n";
				string input = my_getline();
				double price_input = limit_eval(input);
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.intrinsic_value_match_find(price_input);
				main_menu();
			}

			//if user wants to search using a range of fair values
			if (search_choice == 2){
				double lower_limit;
				double upper_limit;
				cout << "\nPlease enter the lower limit of your fair value range.\n";
				string llimit = my_getline();
				lower_limit = limit_eval(llimit);
				cout << "\nPlease enter the upper limit of your fair value range.\n";
				string ulimit = my_getline();
				upper_limit = limit_eval(ulimit);

				//if user accidentally enetered reversed input, i.e., lower_limit is greater than upper_limit
				if (lower_limit > upper_limit){
					cout << "\nThe input receieved for lower limit is greater than upper limit.";
					cout << " I will interchange lower limit and upper limit.\n";
					double temp = lower_limit;
					lower_limit = upper_limit;
					upper_limit = temp;
				}
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.intrinsic_value_range_find(lower_limit, upper_limit);
				main_menu();
			}


			
		}



		//if user chooses to find stocks using rating
		if (choice == 5){
			int search_choice;
			cout << "\n\nYou can choose from one of the following search methods (please choose 1 or 2):\n";
			cout << "(1) If you know the exact word for the rating that stock has, then choose 1.\n";
			cout << "(2) If you know few letters from the rating that stock has, then choose 2.\n\n";
			search_choice = choice_eval(1, 2);

			//if user chooses the search method in which he/she knows the exact word for the rating
			if (search_choice == 1){
				string input;
				cout << "\nPlease enter the exact rating that you are looking for in Stocks.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.rating_match_find(input);
				main_menu();
			}

			//if user chooses to search method in which he/she knows few letters from the rating of the stock
			if (search_choice == 2){
				string input;
				cout << "\nPlease enter the letters of words you know from the desired stock rating.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				data.rating_contains_find(input);
				main_menu();
			}

			
		}


		//if user chooses to return to the main menu
		if (choice == 6){
			main_menu();
		}

		

		
	}//Find_stock method


	//method to delete stock
	void Delete_stock(){

		if (data.get_size() == 0){
			cout << "Sorry! this function is not available as database is already empty.\n";
			main_menu();
		}

		cout << "\nDelete Stock\n";
		cout << ".\n.................\n";
		string response;
		int* searched_index;

		int choice = 0;
		cout << "\n\nTo find the stock(s) you want to delete, please choose one of the following";
		cout << " option by choosing their respective number:\n";
		cout << "\n(1) Company name.\n";
		cout << "\n(2) Market Segment.\n";
		cout << "\n(3) Current price.\n";
		cout << "\n(4) Fair value.\n";
		cout << "\n(5) Rating.\n\n";
		choice = choice_eval(1, 5);

		if (choice == 1){
			cout << "\n\nTo find the stocks to delete using company name, you have further two options.";
			cout << " Please choose the option by typing their respective number.\n";
			cout << "\n(1) If you know the exact name of the company, choose this option.\n";
			cout << "\n(2) If you know few words or letters from the conmpany name, choose this option.\n";
			int search_choice;
			search_choice = choice_eval(1, 2);

			if (search_choice == 1){
				string input;
				cout << "\nPlease enter the exact company name you are looking for.\n";
				input = my_getline();
				cout << "\nHere are the result based on your search.\n";
				cout << "\n.........................................\n";
				searched_index = data.company_name_match_delete(input);
			}

			if (search_choice == 2){
				string input;
				cout << "\nPlease enter the words you think are present in company name.\n";
				input = my_getline();
				cout << "\nHere are the results based on your input.\n";
				cout << "\n.........................................\n";
				searched_index = data.company_name_contains_delete(input);
			}
		}

		if (choice == 2){
			cout << "\n\nTo find the stocks to delete using market segment, you have further two options.";
			cout << " Please choose the option by typing their respective number.\n";
			cout << "\n(1) If you know the market segment exactly, choose this option.\n";
			cout << "\n(2) If you know few words or letters from the conmpany market segment, choose this option.\n";
			int search_choice;
			search_choice = choice_eval(1, 2);

			if (search_choice == 1){
				string input;
				cout << "\nPlease enter the exact market segment you are looking for.\n";
				input = my_getline();
				cout << "\nHere are the result based on your search.\n";
				cout << "\n.........................................\n";
				searched_index = data.market_segment_match_delete(input);
			}

			if (search_choice == 2){
				string input;
				cout << "\nPlease enter the words or letters present in the market segment you are looking for.\n";
				input = my_getline();
				cout << "\nHere are the result based on your search.\n";
				cout << "\n.........................................\n";
				searched_index = data.market_segment_contains_delete(input);
			}

		}

		if (choice == 3){
			cout << "\n\nTo find the stocks to delete using current price of the stock, you have further two options.";
			cout << " Please choose the option by typing their respective number.\n";
			cout << "\n(1) If you know the current price exactly, choose this option.\n";
			cout << "\n(2) If you know the range for current price, choose this option.\n";
			int search_choice;
			search_choice = choice_eval(1, 2);

			if (search_choice == 1){
				
				cout << "\nPlease enter the exact current price you want to search for.\n";
				string input = my_getline();
				double price_input = limit_eval(input);
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				searched_index =  data.current_price_match_delete(price_input);
			}

			if (search_choice == 2){
				double lower_limit;
				double upper_limit;
				cout << "\nPlease enter the lower limit of your current price range.\n";
				string llimit = my_getline();
				lower_limit = limit_eval(llimit);
				cout << "\nPlease enter the upper limit of your current price range.\n";
				string ulimit = my_getline();
				upper_limit = limit_eval(ulimit);

				//if user accidentally enetered reversed input, i.e., lower_limit is greater than upper_limit
				if (lower_limit > upper_limit){
					cout << "\nThe input receieved for lower limit is greater than upper limit.";
					cout << " I will interchange lower limit and upper limit.\n";
					double temp = lower_limit;
					lower_limit = upper_limit;
					upper_limit = temp;
				}
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				searched_index = data.current_price_range_delete(lower_limit, upper_limit);
			}


		}

		if (choice == 4){
			int search_choice;
			cout << "\n\nYou can search using one of the given method (Please enter 1 or 2):\n";
			cout << "(1) You want to find a stock which has fair value exactly equal to what you enter.\n";
			cout << "(2) You want to find all the stocks that has fair value within your entered range.\n\n";
			search_choice = choice_eval(1, 2);

			//if user wants to list all the stock that has intrinsic value exactly equal to what he/she enters
			if (search_choice == 1){
				
				cout << "\nPlease enter the exact fair value you want to search for.\n";
				string input = my_getline();
				double price_input = limit_eval(input);
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				searched_index = data.intrinsic_value_match_delete(price_input);
			}

			//if user wants to search using a range of fair values
			if (search_choice == 2){
				double lower_limit;
				double upper_limit;
				cout << "\nPlease enter the lower limit of your fair value range.\n";
				string llimit = my_getline();
				lower_limit = limit_eval(llimit);
				cout << "\nPlease enter the upper limit of your fair value range.\n";
				string ulimit = my_getline();
				upper_limit = limit_eval(ulimit);

				//if user accidentally enetered reversed input, i.e., lower_limit is greater than upper_limit
				if (lower_limit > upper_limit){
					cout << "\nThe input receieved for lower limit is greater than upper limit. I will";
					cout << " interchange lower limit and upper limit.\n";
					double temp = lower_limit;
					lower_limit = upper_limit;
					upper_limit = temp;
				}
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				searched_index = data.intrinsic_value_range_delete(lower_limit, upper_limit);
			}


			
		}

		if (choice == 5){
			int search_choice;
			cout << "\n\nYou can choose from one of the following search methods (please choose 1 or 2):\n";
			cout << "(1) If you know the exact word for the rating that stock has, then choose 1.\n";
			cout << "(2) If you know few letters from the rating that stock has, then choose 2.\n\n";
			search_choice = choice_eval(1, 2);

			//if user chooses the search method in which he/she knows the exact word for the rating
			if (search_choice == 1){
				string input;
				cout << "\nPlease enter the exact rating that you are looking for in Stocks.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				searched_index = data.rating_match_delete(input);
			}

			//if user chooses to search method in which he/she knows few letters from the rating of the stock
			if (search_choice == 2){
				string input;
				cout << "\nPlease enter the letters of words you know from the desired stock rating.\n";
				input = my_getline();
				cout << "\nHere are the results based on your search.\n";
				cout << "\n..........................................\n";
				searched_index = data.rating_contains_delete(input);
			}

			
		}


		if (searched_index[0] != 10000000){
			cout << "\nAre you sure you want to delete these listed stocks? Please reply by typing yes or no?\n";
			response = my_getline();
			if (lower_case(response) == "yes"){
				for (int i = 0; i < data.get_size(); i++){
					if (searched_index[i] != 10000000){
						data.delete_stock_record(searched_index[i]);
					}
				}
				cout << "\nStocks successfully deleted from the database.\n";
			} else if (lower_case(response) == "no"){
				cout << "\nOkay!, listed stocks will not be deleted from the database.\n";
			}
		}

		cout << "\n......................................................................\n";


		//deleting the array of indicies
		delete[] searched_index;
		searched_index = nullptr;

		//going back to the main menu
		main_menu();
	}


	void List_stock(){
		cout << "\nList Stock\n";
		cout << "\n...........\n";

		int choice = 0;
		cout << "\n\nYou can list stocks based on one of the following criteria (Please enter the";
		cout << " number associated with your desired option):\n";
		cout << "\n(1) Based on company name.\n";
		cout << "\n(2) Based on market segment.\n";
		cout << "\n(3) Based on current price.\n";
		cout << "\n(4) Based on fair price.\n";
		cout << "\n(5) Based on rating.\n\n";
		choice = choice_eval(1, 5);

		if (choice == 1){
			int order_choice = 0;
			cout << "\n\nTo list stocks based on company name, two options are available";
			cout << " (please choose the number associated with desired option):\n";
			cout << "\n(1) In alphabetical order.\n";
			cout << "\n(2) In reverse alphabetical order.\n";
			order_choice = choice_eval(1, 2);

			if (order_choice == 1){
				cout << "\nHere is a list of all the stocks in database based on company name in alphabetical order:\n";
				cout << "\n.........................................................................................\n";
				data.sort_company_name();
				cout << "\n.......................................................................................\n";
			}

			if (order_choice == 2){
				cout << "\nHere is a list of all the stocks in database based on company name in";
				cout << " reverse alphabetical order.\n";
				cout << "\n....................................................................................\n";
				data.reverse_sort_company_name();
				cout << "\n.......................................................................................\n";
			}

		}

		if (choice == 2){
			int order_choice = 0;
			cout << "\n\nTo list stocks based on market segment, two options are available";
			cout << " (please choose the number associated with desired option):\n";
			cout << "\n(1) In alphabetical order.\n";
			cout << "\n(2) In reverse alphabetical order.\n";
			order_choice = choice_eval(1, 2);

			if (order_choice == 1){
				cout << "\nHere is a list of all the stocks in database based on market segment in alphabetical order:\n";
				cout << "\n...........................................................................................\n";
				data.sort_market();
				cout << "\n.......................................................................................\n";
			}

			if (order_choice == 2){
				cout << "\nHere is a list of all the stocks in database based on market segment in reverse";
				cout << " alphabetical order:\n";
				cout << "\n...............................................................................\n";
				data.reverse_sort_market();
				cout << "\n.......................................................................................\n";
			}
		}

		if (choice == 3){

			int order_choice = 0;
			cout << "\n\nTo list stocks based on current price, two options are available";
			cout << " (please choose the number associated with desired option):\n";
			cout << "\n(1) In ascending order.\n";
			cout << "\n(2) In descending order.\n";
			order_choice = choice_eval(1, 2);

			if (order_choice == 1){
				cout << "\nHere is a list of all the stocks in database based on current price in ascending order:\n";
				cout << "\n.......................................................................................\n";
				data.sort_current_price();
				cout << "\n.......................................................................................\n";
			}

			if (order_choice == 2){
				cout << "\nHere is a list of all the stocks in database based on current price in descending order:\n";
				cout << "\n........................................................................................\n";
				data.reverse_sort_current_price();
				cout << "\n.......................................................................................\n";
			}
		}

		if (choice == 4){

			int order_choice = 0;
			cout << "\n\nTo list stocks based on fair price, two options are available (please choose";
			cout << " the number associated with desired option):\n";
			cout << "\n(1) In ascending order.\n";
			cout << "\n(2) In descending order.\n";
			order_choice = choice_eval(1, 2);

			if (order_choice == 1){
				cout << "\nHere is a list of all the stocks in database based on fair price in ascending order:\n";
				cout << "\n.......................................................................................\n";
				data.sort_intrinsic_value();
				cout << "\n.......................................................................................\n";
			}

			if (order_choice == 2){
				cout << "\nHere is a list of all the stocks in database based on fair price in descending order:\n";
				cout << "\n...............................................................................\n";
				data.reverse_sort_intrinsic_value();
				cout << "\n.......................................................................................\n";
			}
		}

		if (choice == 5){
			int order_choice = 0;
			cout << "\n\nTo list stocks based on rating, two options are available (please choose the number";
			cout << " associated with desired option):\n";
			cout << "\n(1) In alphabetical order.\n";
			cout << "\n(2) In reverse alphabetical order.\n";
			order_choice = choice_eval(1, 2);

			if (order_choice == 1){
				cout << "\nHere is a list of all the stocks in database based on rating in alphabetical order:\n";
				cout << "\n.......................................................................................\n";
				data.sort_rating();
				cout << "\n.......................................................................................\n";
			}

			if (order_choice == 2){
				cout << "\nHere is a list of all the stocks in database based on rating in reverse alphabetical order:\n";
				cout << "\n.......................................................................................\n";
				data.reverse_sort_rating();
				cout << "\n.......................................................................................\n";
			}
		}

		//going back to the main menu
		main_menu();
	}


	int Quit(){
		return 0;
	}
	



}; //Menu class

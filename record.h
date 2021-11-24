//This file contains implementation of "record" class
//The data I am recording here is on Stocks, particularly, company name, current price, intrinsic value, buy/sell/hold rating

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string lower_case(string result){
	//For it to be convenient, I am allowing user to put any uppercase or lower case letter. 
    //This code will convert all uppercase to lowercase
    //here is a reference for this code:https://stackoverflow.com/questions/11502523/how-to-use-lambda-in-for-each
    for_each(result.begin(), result.end(), [](char & c){
		c = tolower(c);
	});

	return result;
}

class Stock {

private:

	string company_name;
	string market;
	double current_price;
	double intrinsic_value;
	string rating;

public:

	//default constructor
	Stock()
	{
	company_name = "";
	market = "";
	current_price = 0.01; //because stock price cannot be negative or 0
	intrinsic_value = 0.01; //because stock price cannot be negative or 0
	rating = "";	
	}

	//constructor
	Stock(string n, string m, double c, double i, string r)
	: company_name(n), market(m), current_price(c), intrinsic_value(i), rating(r) //initializer list
	{ }


	//method to get the company name
	string get_company_name(){
		return company_name;
	}

	//method to get the market segment of the stock
	string get_market(){
		return market;
	}

	//method to get the current price of the stock
	double get_current_price(){
		return current_price;
	}

	//method to get the intrinsic value of the stock
	double get_intrinsic_value(){
		return intrinsic_value;
	}

	//method to get the rating of the stock
	string get_rating(){
		return rating;
	}

	//method to set company name
	void set_company_name(string input){
		company_name = input;
	}

	//method to set market segment
	void set_market(string input) {
		market = input;
	}

	//method to set current price
	void set_current_price(double input){
		current_price = input;
	}

	//method to set intrinsic_value
	void set_intrinsic_value(double input){
		intrinsic_value = input;
	}

	//method to set rating
	void set_rating(string input){
		rating = input;
	}
	//method to check if two Stocks are same
	int same_stock(Stock j){
		if (lower_case(company_name) == lower_case(j.get_company_name()) &&
			lower_case(market) == lower_case(j.get_market()) &&
			current_price == j.get_current_price() &&
			intrinsic_value == j.get_intrinsic_value() &&
			lower_case(rating) == lower_case(j.get_rating())){
			return 1;
		} else {
			return 0;
		}
	}


	

	//destructor
	~Stock()
	{ }

}; //class Stock

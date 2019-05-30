#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

class customer
{
private:
	string customerId;
	string name;
	string emailAdress;
	int age;
	int gender;
public:
	string RtnCustomerId     (void) const { return customerId; };
	string RtnName	         (void) const { return name; };
	string RtnEmailAdress    (void) const { return emailAdress; };
	int    RtnAge            (void) const { return age; };
	int    RtnGender         (void) const { return gender; };
	void   SetCustomerInfo   (string CustId, string Name, string EmailAdress, int Age, int Gender);

};

class product
{
private:
	string sku;
	string name;
	string brand;
	double price;
	string currency;
public:
	string RtnSku            (void) const { return sku; };
	string RtnName           (void)const { return name; };
	string RtnBrand          (void)const { return brand; };
	double RtnPrice          (void)const { return price; };
	string RtnCurrency       (void)const { return currency; };
	void   SetProductInfo    (string Sku, string Name, string Brand, double Price, string Currency);
};


class orderLine
{
private:
	int lineNumber;
	string productName;
	double price;
	int quantity;
public:
	int RtnLineNumber(void)const { return lineNumber; };
	string RtnProductName(void)const { return productName; };
	double RtnPrice(void)const { return price; };
	int RtnQuantity(void)const { return quantity; };
	void SetOrderLineInfo(int LineNumber, string ProductName, double Price, int Quantity);

};


class order
{
private:
	string orderId;
	int numOfLineItems;
	double orderSubTotal;
	double orderTax;
	double orderTotal;
	string customerId;
public:
	vector<orderLine> Or;
	string RtnOrderId       (void) const { return orderId; };
	int RtnNumOfLineItems   (void) const { return numOfLineItems; };
	double RtnOrderSubTotal (void) const { return orderSubTotal; };
	double RtnOrderTax      (void) const { return orderTax; };
	double RtnOrderTotal    (void) const { return orderTotal; };
	string RtnCustomerId    (void) const { return customerId; };
	void   SetOrderInfo(string OrderId,int NumOfLineItems, double OrderSubTotal, double OrderTax, double OrderTotal, string CustomerId);
};





void getData(ifstream& inFile, vector<customer>& custObj, vector<product>& prodObj, vector<order>& ordObj);
void parseData(string line, vector<customer>& custObj, vector<product>& prodObj, vector<order>& ordObj);
std::vector<std::string> split(const std::string& s, char delimiter);
void removeCharsFromString(string &str, char* charsToRemove);
void creatingXmlFile(vector<customer>& test);
void creatingCsvFile(vector<product>& tes);
void creatingJsonFile(vector<order>& te);
string putComma(int first, int second);
string giveGender(int gen);
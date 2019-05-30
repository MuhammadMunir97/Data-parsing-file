#include "Class.h"

using namespace std;



// the three vectors are custObj, prodObj and ordObj
// they will be passed by reference and be used throughout the program
void getData(ifstream& inFile, vector<customer>& custObj, vector<product>& prodObj, vector<order>& ordObj)
{
	string            line;
		
	const bool      EOF_ENCOUNTERED = false,
				   	MORE_DATA_TO_READ = true;

	while (getline(inFile, line) ? MORE_DATA_TO_READ : EOF_ENCOUNTERED) 
	{
		parseData(line, custObj, prodObj, ordObj);
	};//while
	
};

void parseData(string line, vector<customer>& custObj, vector<product>& prodObj, vector<order>& ordObj)
{
//            ADDING RELEVANT ZERO                   //
//===================================================//
	if (line[line.length() -1] == ',')
		line = line + '0';


	for (int i = 1; i < line.length(); i++)
	{
		if ((line[i - 1] == ',') && (line[i] == ','))
		{
			line = line + '0';
			for (int j = line.length(); j >= i; j--)
			{
				line[j] = line[j - 1];
				if (j == i)
					line[j] = '0';
			}
		}
		
	}
// the code above is written to avoid error after the 
// string gets partitioned and the data is missing for
// person
//==================================================//

	
	removeCharsFromString(line, "\"" );
	

	std::vector<std::string> vec;
	vec = split(line, ',');

	int l = 0;
	if (vec[0] == "customer")
	{
			customer temp;
			temp.SetCustomerInfo(vec[1], vec[2], vec[3], std::stoi(vec[4]), std::stoi(vec[5]));
			custObj.push_back(temp);
	}
	if (vec[0] == "product")
	{
		if (vec[5] == "0")
		{
			vec[5] = "USD";
		}
		product temp;
        temp.SetProductInfo(vec[1], vec[2], vec[3], std::stod(vec[4]), vec[5]);
		prodObj.push_back(temp);
	}

	if ((vec[0] == "order")|| (vec[0] == "order-line"))
	{
		if (vec[0] == "order")
		{
			order temp;
			temp.SetOrderInfo(vec[1], std::stoi(vec[2]), std::stod(vec[3]), std::stod(vec[4]), std::stod(vec[5]), vec[6]);
			ordObj.push_back(temp);
		}
		else
		{
			orderLine temp;
			temp.SetOrderLineInfo(std::stoi(vec[1]), vec[2], std::stod(vec[3]), std::stoi(vec[4]));
			ordObj.back().Or.push_back(temp);
		}
	}
	
	
}


void customer::SetCustomerInfo(string CustId, string Name, string EmailAdress, int Age, int Gender)
{

	customerId = CustId;
	name = Name;
	emailAdress = EmailAdress;
	age = Age;
	gender = Gender;
}
// the custObj file is filled with errors and to counter them
// create a error detecting funtionion
// whenever their is a missing info it is two commas together
//	age = std::stoi(vec[5]);
	//	gender = std::stoi(vec[6]);

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void removeCharsFromString(string &str, char* charsToRemove) 
{
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
		str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
	}
}

void product::SetProductInfo(string Sku, string Name, string Brand, double Price, string Currency)
{
	 sku = Sku;
	 name = Name;
	 brand = Brand;
	 price = Price;
	 currency= Currency;
}

void order::SetOrderInfo(string OrderId,int NumOfLineItems, double OrderSubTotal, double OrderTax, double OrderTotal, string CustomerId)
{
	orderId = OrderId;
	numOfLineItems = NumOfLineItems;
	orderSubTotal = OrderSubTotal;
	orderTax = OrderTax;
	orderTotal = OrderTotal;
	customerId = CustomerId;
}

void orderLine::SetOrderLineInfo(int LineNumber, string ProductName, double Price, int Quantity)
{
	lineNumber = LineNumber;
	productName = ProductName;
	price = Price;
	quantity = Quantity;

}

void creatingXmlFile(vector<customer>& custObj)
{
	ofstream xmlFile;
	xmlFile.open("output_files\\customer.xml");
	if (!xmlFile)
	{
		cout << "Cannot open the output file. Program terminates!"
			<< endl;
		return ;
	}
	xmlFile << "<?xml version= \"1.0\"?>" << endl << endl;
	xmlFile << "<customers>" << endl;
	for (int i = 0; i < custObj.size(); i++)
	{
		xmlFile << "	<customer>" << endl ;
		xmlFile << "		<id> " << custObj[i].RtnCustomerId() << " </id>" << endl;
		xmlFile << "		<name> " << custObj[i].RtnName() << " </name>" << endl;
		xmlFile << "		<email> " << custObj[i].RtnEmailAdress() << " </email>" << endl;
		xmlFile << "		<age> " << custObj[i].RtnAge() << " </age>" << endl;
		xmlFile << "		<gender> " << giveGender(custObj[i].RtnGender()) << " </gender>" << endl;
		xmlFile << "	</customer>" << endl;
	}
	xmlFile << "</customers>" << endl;

	xmlFile.close();

}

string giveGender(int gen)
{
	if (gen == 1)
	{
		return "male";
	}
	else if (gen == 2)
	{
		return "female";
	}
	else
		return "INV";
}

void creatingCsvFile(vector<product>& prodObj)
{
	ofstream csvFile;
	csvFile.open("output_files\\products.csv");
	if (!csvFile)
	{
		cout << "Cannot open the output file. Program terminated!"
			<< endl;
		return;
	}
	csvFile << "sku" << "," << "name" << "," << "brand" << "," << "price" << ","
		<< "currency" << endl;

	for (int i = 0; i < prodObj.size(); i++)
	{
		csvFile << prodObj[i].RtnSku() << ","
			<< prodObj[i].RtnName() << ","
			<< prodObj[i].RtnBrand() << ","
			<< prodObj[i].RtnPrice() << ","
			<< prodObj[i].RtnCurrency() << "," << endl;

	}
	csvFile.close();
}

void creatingJsonFile(vector<order>& ordObj)
{
	ofstream jsonFile;
	jsonFile.open("output_files\\order.json");
	if (!jsonFile)
	{
		cout << "Cannot open the output file. Program terminates!"
			<< endl;
		return;
	}
	jsonFile << "{"<<endl
		<< "	\"orders\":[" << endl;
	for (int i = 0; i < ordObj.size(); i++)
	{
		jsonFile << "{" << endl
			<< "		\"id\": \"" << ordObj[i].RtnOrderId() << "\"," << endl
			<< "		\"head\":{" << endl
			<< "			\"sub_total\": \"" << ordObj[i].RtnOrderSubTotal() << "\"," << endl
			<< "			\"tax\": \"" << ordObj[i].RtnOrderTax() << "\"," << endl
			<< "			\"total\": \"" << ordObj[i].RtnOrderTotal() << "\"," << endl
			<< "			\"customer\": \"" << ordObj[i].RtnCustomerId() << "\"" << endl
			<< "		}," << endl
			<< "		\"lines\":[" ;
		for (int j = 0; j < ordObj[i].Or.size(); j++)
		{
			jsonFile << "{" << endl
				<< "			\"position\": \"" << ordObj[i].Or[j].RtnLineNumber() << "\"," << endl
				<< "			\"name\": \"" << ordObj[i].Or[j].RtnProductName() << "\"," << endl
				<< "			\"price\": \"" << ordObj[i].Or[j].RtnPrice() << "\"," << endl
				<< "			\"quantity\": \"" << ordObj[i].Or[j].RtnQuantity() << "\"," << endl
				<< "			\"row_total\": \"" << (ordObj[i].Or[j].RtnPrice() * ordObj[i].Or[j].RtnQuantity()) << "\"" << endl
				<< "			 }" << putComma(j, ordObj[i].Or.size() )<< endl;
		}
		jsonFile << "		]" << endl
			<< "	}"<< putComma(i, ordObj.size()) << endl;

	}
	jsonFile << "	]" << endl
		<< "}" << endl;


	jsonFile.close();
}

string putComma(int first, int second)
{
	if (first == (second - 1))
	{
		return "";
	}
	else
		return ",";
}
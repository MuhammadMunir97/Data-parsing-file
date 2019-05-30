//Create a class that holds the matrice
//read the matrice from a .txt file


#include "Class.h"



using namespace std;


int main()
{
	ifstream inData;
	ofstream outData;

	vector<customer> customerObj;
	vector<product> productObj;
	vector<order> orderObj;



	inData.open("test-file.txt");
	if (!inData)
	{
		cout << "The input file does not exist. Program terminates!"
			<< endl;
		return 1;
	}
	//==============================================================//
	// the following function will input all the data from the file
	// line by line and then send the data to the function
	// parseData() where the vector objects will be filled
	//==============================================================//
	getData(inData, customerObj, productObj, orderObj);

	//==============================================================//
	// this will use the vector customerObj to create the xml file
	creatingXmlFile(customerObj);

	//==============================================================//
	// this will use the vector productObj to create the csv file
	creatingCsvFile(productObj);

	//==============================================================//
	// this will use the vector orderObj to create the json file
	creatingJsonFile(orderObj);
	
	cout << "The output files have been created successfully please check the corresponding folder" << endl;

	return 0;
};
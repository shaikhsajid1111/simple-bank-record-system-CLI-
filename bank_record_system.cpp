#include<iostream>		/*default library*/
#include<fstream>		
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<sstream>
using namespace std;

/*class for all related bank functions*/
class Bank_account{
	/*private variables*/
	string f_name,l_name;
	string account_number;
	string account_type;
	string balance;
public:
	/*function prototype declaration*/
	bool account_exist(string search);	/*Whether account number exists in data*/
	void enter_data();						/*for entering data in txt file*/
	void search_account_number();				/*for searching account number in data.txt file*/
	void display_record();				/*to display all records in data file*/
	void update_data();				/*to update content of data.txt file*/
	void delete_record();		/*to delete record from file*/

};
/*function prototype declaration*/
string replace_str(string s, string oldVal, const string newVal); /*function for replacing strings*/

/*main function*/
int main(int argc, char const *argv[])
{
	Bank_account customer;		/*Bank account object*/

	/*prompting for options*/
	cout << "Enter 1 for Enter Data\nEnter 2 for Search your account Number\n";
	cout << "Enter 3 for display all records: \nEnter 4 for update your records\nEnter 5 for delete \n";
	
	/*label for jumping again*/
	PROMPT:
	
	int response;			/*takes response in integer*/
	cout << "Enter Number what you wanna do: \n";
	cin >> response;
	/*exception handling*/
	/*if user enters char values or user enters value that is out of commands*/
	if(cin.fail() || response > 5){
		cout << "Invalid Input\n";
		cin.clear();
		cin.ignore(100,'\n');
		goto PROMPT;
	}
	
	switch(response){
		/*cases*/
		case 1:
		customer.enter_data();
		break;
			
		case 2:	
		customer.search_account_number();
		break;
			
		case 3:
		customer.display_record();
		break;
			
		case 4:
		customer.update_data();
		break;

		case 5:
		customer.delete_record();
		break;

	}
	/*asking, whether code has to be run again*/
	int answer;
	/*exception handling*/
	if(cin.fail()){
		cin.clear();
		cin.ignore(100,'\n');
		cout << "Exiting";
		exit(1);
	}
	/*asking after operation is complete*/
	cout << "\nEnter 1 to repeat the procedure or enter any key to exit!\n";
	cin >> answer;
	/*if user wants to execute code again, code jumps to 'PROMPT'*/
	if(answer == 1){	
		goto PROMPT;  
	}
	system("pause");
	return 0;
}
string replace_str(string s, string oldVal, const string newVal) 
/* replace oldVal with newVal in s*/
{
	if (!s.empty() && !oldVal.empty()) {
		auto sbeg = s.begin(), OVbeg = oldVal.begin();
		unsigned cnt = 0;

		while (sbeg != s.end()) {
			while (sbeg != s.end() && OVbeg != oldVal.end() && *sbeg == *OVbeg) {
				++cnt;
				++sbeg;
				++OVbeg;
			}
			if (cnt == oldVal.size()) {
				sbeg = s.erase(sbeg - oldVal.size(), sbeg);
				for (decltype(newVal.size()) ind = 0; ind != newVal.size(); ++ind) {
					sbeg = s.insert(sbeg, newVal[ind]);
					++sbeg;
				}
			}
			cnt = 0; // This?
			OVbeg = oldVal.begin();

			if (sbeg != s.end())
				++sbeg;
		}
	}
	return s;
}


/************************outside function above************************/
/*check whether the string exist in the data*/
bool Bank_account::account_exist(string search){

    int offset; 
    string line;
    ifstream Myfile;			/*file open*/
    Myfile.open ("data.txt");

    if(Myfile.is_open())
    {
        while(!Myfile.eof())		/*while reading cursor does not reaches end of file*/
        {
            getline(Myfile,line);
            if ((offset = line.find(search, 0)) != string::npos) 
            {
             /*cout << "found '" << search << " \n\n"<< line  <<endl;*/
             return true;
            }
        }
        Myfile.close();
    }
    else
    cout<<"Data file is not created yet!\n"<<endl;
    return false;

}
void Bank_account::enter_data(){
		
		/*string f_name,l_name;*/	     
		/*first name and last name input*/
		/*starts label*/
		START:
		cout << "Enter Account Holder's First Name : "<< endl;
		cin >> l_name;
		/*exception handling*/
		if(cin.fail()){
			cout << "Invalid Input\n";
		}
		/*prompts for first name*/
		cout << "Enter Account Holder's Last Name: "<<endl;
		cin >> f_name;
		/*exception handling*/
		if(cin.fail()){
			cout << "Invalid Input\n";
		}
		
		/*account number variable*/ 
		/*string account_number;*/	

		ACCOUNT:			/*jump statement GOTO*/
		cout << "Enter Account Number for " << f_name + " " + l_name << endl;
		cin >> account_number;
		/*exception handling*/
		if(cin.fail()){
			cout << "Invalid Input\n";		/*showing error*/
			cin.clear();						/*clearing cin*/
			cin.ignore(100,'\n');			
			goto ACCOUNT;
		}
		/*checking whether the input is number or not*/
		try{
			stod(account_number);
		}
		/*if input is not number*/
		catch(invalid_argument &ex){
			cout << "Enter numbers only!";
			goto ACCOUNT;
		}
		/*if account number already exist, it'll clear all previous inputs*/
		if(account_exist(account_number)){
			cout << "Account already exist!\nHence your entered data will be cleared!";
			cout << "Enter data \n";
			goto START;	
		}
		
		int length_of_account_number = strlen(account_number.c_str()); /*checking length of account number */
		/*if account number is shorter than 8 or greater than 10*/
		if(length_of_account_number < 8 || length_of_account_number > 10){
			cout << "Account Number Cannot be Shorter than 8 digits or greater than 10! \n";
			goto ACCOUNT;
		}
		/*account type*/
		//string account_type;

		ACCOUNT_TYPE:
		cout << "Account type : ('s' for saving and 'c' for current) : \n";
		/*account type*/
		cin >> account_type;
	
		if(cin.fail()){
			cout << "Enter Character!\n";
			goto ACCOUNT_TYPE;
		}
		if(account_type == "s"){
			account_type = "saving";
		}
		else if(account_type == "c"){
			account_type = "current";
		}
		else{
			cout << "Invalid Input!\n";
			goto ACCOUNT_TYPE;
		}
		/*balance*/
		/*string balance;*/
		BALANCE:
		cout << "Enter Balance: \n";
		cin >> balance;
		if(cin.fail()){
			cout << "Invalid Input!\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto BALANCE;
		}
		/*trying to convert balance to number*/
		try{
			stod(balance);
		}
		/*if balance is not a number*/
		catch(invalid_argument &ex){
			cout << "Enter numbers only! \n";
			goto BALANCE;
		}
		/*opening data.txt as data_file*/
		fstream data_file;
		data_file.open("data.txt", std::ios_base::app); /*open data file in append mode*/
		data_file << f_name << "|" << l_name << "|" << account_number << "|" << account_type << "|" << balance << endl;
		data_file.close();				/*file close*/
		cout << "Data saved successfully!";			/*if data is entered, prompt*/

}
void Bank_account::search_account_number(){
	
		string account_number;
		ACCOUNT_NUMBER:
		cout << "Enter Account Number to search: " << endl;
		cin >> account_number;
		if(cin.fail()){
			cout << "Invalid Input!" << endl;
			cin.clear();
			cin.ignore(100,'\n');
			goto ACCOUNT_NUMBER;
		}
		int length_of_account_number = strlen(account_number.c_str());
		if(length_of_account_number < 8 || length_of_account_number > 10){
			cout << "Account number cannot be of " << length_of_account_number << " digits!" <<endl;
			goto ACCOUNT_NUMBER;
		}
		
		if(account_exist(account_number)){
			cout << "Account Number : " << account_number << "Exist!\n";
		}
		if(!account_exist(account_number)){
			cout << "Does not exist!";
		}
	}
void Bank_account::display_record(){
		/*opening file*/
		ifstream data_file;
		data_file.open("data.txt");
		string line;        	/*line for iteration over tha data lines*/
		int counter = 0;
		if(data_file.is_open()){
				/*while data file does not reach end of file*/
			while(!data_file.eof()){
				counter++;
				getline(data_file,line);
				if(line == ""){				
					break;
				}
				cout <<counter << ")" << line << endl;
				
			}
		}
		/*if file is not there*/
		else if(data_file.fail()){
			cout << "Data File does not exists!\n";
		}
}

void Bank_account::update_data(){
	fstream data_file;
	data_file.open("data.txt");
	if(data_file.fail()){
		cout << "Error While opening file";

	}
	stringstream file_content;
	file_content << data_file.rdbuf();
	string data = file_content.str();
	data_file.close();
	
	/*account number inpus and exception handling*/
	ACCOUNT_SEARCH:
	string account_number_search;
	cout << "Enter Account Number to search : \n";
	cin >> account_number_search;
	if(cin.fail()){
		cout << "Error Occured!\n";
		cin.clear();
		cin.ignore(100,'\n');
		goto ACCOUNT_SEARCH;
	}
	int length_of_account_number = strlen(account_number_search.c_str());
	if(length_of_account_number < 8 || length_of_account_number > 10){
			cout << "Account number cannot be of " << length_of_account_number << endl;
			goto ACCOUNT_SEARCH;
		}
	
	
		/*account number inpus and exception handling*/
		if(account_exist(account_number_search)){
			cout << "Account number exist!";
		}

		int offset;
		string line,new_line;

		data_file.open("data.txt");
		if(data_file.is_open()){
			while(!data_file.eof()){
				getline(data_file,line);
				 if((offset = line.find(account_number_search, 0)) != string::npos){
				 	cout << line << endl;

					cout << "Enter new Data\n";
					data_file.close();
					/*update operation*/

		//string f_name,l_name;
		START:
		cout << "Enter Account Holder's First Name : "<< endl;
		cin >> f_name;
		if(cin.fail()){
			cout << "Invalid Input\n";
		}

		cout << "Enter Account Holder's Last Name: "<<endl;
		cin >> l_name;
		if(cin.fail()){
			cout << "Invalid Input\n";
		}

		/*account type*/
		//string account_type;

		ACCOUNT_TYPE:
		cout << "Account type : ('s' for saving and 'c' for current) : \n";
		cin >> account_type;
		if(cin.fail()){
			cout << "Enter Character!\n";
			goto ACCOUNT_TYPE;
		}
		if(account_type == "s"){
			account_type = "saving";
		}
		else if(account_type == "c"){
			account_type = "current";
		}
		else{
			cout << "Invalid Input!\n";
			goto ACCOUNT_TYPE;
		}
		/*balance*/
		//string balance;
		BALANCE:
		cout << "Enter Balance: \n";
		cin >> balance;
		if(cin.fail()){
			cout << "Invalid Input!\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto BALANCE;
		}
		try{
			stod(balance);
		}
		catch(invalid_argument &ex){
			cout << "Enter numbers only! \n";
			goto BALANCE;
		}
		/*changes to the file*/
	 new_line = f_name + "|" + l_name + "|" + account_number_search + "|" + account_type + "|" + balance;
	 string new_data = replace_str(data,line,new_line);
	 cout << new_data;
	 data_file.open("data.txt", ios::out | ios::trunc);
	 if(data_file.fail()){
	 	cout << "Failed to open data file!\n";
	 }
	 data_file << new_data;
		/*updation of file ends*/
				 }				
			}
	}	
}
void Bank_account::delete_record(){
	/*decalring variable for opening file */
	fstream data_file;
	data_file.open("data.txt");

	/*if file does not exist*/
	if(data_file.fail()){
		cout << "Error While opening file";

	}
	stringstream file_content;
	file_content << data_file.rdbuf();
	string data = file_content.str();
	data_file.close();
	
	string account_search;
	ACCOUNT:
		cout << "Enter Account Number: "<< endl;
		cin >> account_search;
		
		if(cin.fail()){
			cout << "Invalid Input\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto ACCOUNT;
		}
		try{
			stod(account_search);
		}
		catch(invalid_argument &ex){
			cout << "Enter numbers only!\n";
			goto ACCOUNT;
		}
	int length_of_account_number = strlen(account_search.c_str());
		if(length_of_account_number < 8 || length_of_account_number > 10){
			cout << "Account Number Cannot be Shorter than 8 digits or greater than 10! \n";
			goto ACCOUNT;
		}
	if(account_exist(account_search)){
		cout << "Account exists!\n";
	}
	int offset;
	string line,new_data;
	
	data_file.open("data.txt");
	while(!data_file.eof()){
				getline(data_file,line);
				 if((offset = line.find(account_search, 0)) != string::npos){
				 	
				 	int end = strlen(line.c_str()) + 1;			/*last index of content to be find*/
				 	int start = data.find(line);			/*start index of content to be find*/
				 	data_file.close();					/*closing the file*/
				 	
				 	data.erase(start,end);				/*erasing data from start to end*/
					data_file.open("data.txt", ios::out | ios::trunc);
	 				if(data_file.fail()){
	 					cout << "Failed to open data file!\n";
	 }

	 				data_file << data;				/*again rewriting the content in data.txt file*/
	 				cout << "Account Deleted Successfully!\n";
	 				data_file.close();				
	 				//data_file << data;
	 				//cout << "Account Deleted Successfully!\n";
				 }		 
				}
			}
/*author : shaikh sajid*/

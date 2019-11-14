#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<sstream>
using namespace std;

class Bank_account{
public:
	bool account_exist(string search);
	void enter_data();
	void search_account_number();	
	void display_record();
	void edit_rec();
	void update_data();
	void delete_record();

};
int length_function(int number);
string replace_str(string s, string oldVal, const string newVal);
/*main function*/
int main(int argc, char const *argv[])
{
	Bank_account customer;
	//customer.display_record();
	//customer.enter_data();
	//customer.search_account_number();
	//customer.update_data();
	customer.delete_record();
	system("pause");
	return 0;
}
/******************length function **********************************************/
int length_function(int number){
	int counter = 0;
	while(number){
		number = number / 10;
		counter++;
	}
	return (counter);
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
bool Bank_account::account_exist(string search){

	int offset; 
    string line;
    ifstream Myfile;
    Myfile.open ("data.txt");

    if(Myfile.is_open())
    {
        while(!Myfile.eof())
        {
            getline(Myfile,line);
            if ((offset = line.find(search, 0)) != string::npos) 
            {
            //* cout << "found '" << search << " \n\n"<< line  <<endl;*/
             return true;
            }
        }
        Myfile.close();
    }
    else
    cout<<"Unable to open this file."<<endl;
    return false;

}
void Bank_account::enter_data(){
	
	while (true){
		string f_name,l_name;
		START:
		cout << "Enter Account Holder's First Name : "<< endl;
		cin >> l_name;
		if(cin.fail()){
			cout << "Invalid Input\n";
		}

		cout << "Enter Account Holder's Last Name: "<<endl;
		cin >> f_name;
		if(cin.fail()){
			cout << "Invalid Input\n";
		}
		
		//*account number cannot be negative*/ 
		string account_number,temp_account;	

		ACCOUNT:
		cout << "Enter Account Number for " << f_name + " " + l_name << endl;
		cin >> temp_account;
		
		if(cin.fail()){
			cout << "Invalid Input\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto ACCOUNT;
		}
		try{
			stod(temp_account);
		}
		catch(invalid_argument &ex){
			cout << "Enter numbers only!";
			goto ACCOUNT;
		}
		
		//*char search[10];*/
		//*itoa(temp_account,search,10);*/
		if(account_exist(temp_account)){
			cout << "Account already exist!\nHence your entered data will be cleared!";
			cout << "Enter data \n";
			goto START;
		}
		
		int length_of_account_number = strlen(temp_account.c_str());
		if(length_of_account_number >= 8 && length_of_account_number <= 10){
			account_number = temp_account;
		}
		else{
			cout << "Account Number Cannot be Shorter than 8 digits or greater than 10! \n";
			goto ACCOUNT;
		}
		/*account type*/
		string account_type,temp_type;

		ACCOUNT_TYPE:
		cout << "Account type : ('s' for saving and 'c' for current) : \n";
		cin >> temp_type;
		if(cin.fail()){
			cout << "Enter Character!\n";
			goto ACCOUNT_TYPE;
		}
		if(temp_type == "s"){
			account_type = "saving";
		}
		else if(temp_type == "c"){
			account_type = "current";
		}
		else{
			cout << "Invalid Input!\n";
			goto ACCOUNT_TYPE;
		}
		/*balance*/
		string balance,temp_balance;
		BALANCE:
		cout << "Enter Balance: \n";
		cin >> temp_balance;
		if(cin.fail()){
			cout << "Invalid Input!\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto BALANCE;
		}
		try{
			stod(temp_balance);
		}
		catch(invalid_argument &ex){
			cout << "Enter numbers only! \n";
			goto BALANCE;
		}
		balance = temp_balance;
		fstream data_file;
		data_file.open("data.txt", std::ios_base::app);
		data_file << f_name << "|" << l_name << "|" << account_number << "|" << account_type << "|" << balance << endl;
		data_file.close();
		cout << "Data saved successfully!";

}
}
void Bank_account::search_account_number(){
	
		unsigned long int account_number,temp;
		ACCOUNT_NUMBER:
		cout << "Enter account number: " << endl;
		cin >> temp;
		if(cin.fail()){
			cout << "Invalid Input!" << endl;
			cin.clear();
			cin.ignore(100,'\n');
			goto ACCOUNT_NUMBER;
		}
		int length_of_account_number = length_function(temp);
		if(length_of_account_number >= 8 && length_of_account_number <= 10){
			account_number = temp;
		}
		else{
			cout << "Account number cannot be of " << length_of_account_number << " digits!" <<endl;
			goto ACCOUNT_NUMBER;
		}
		/*searching*/
		int offset;
		string line;
		ifstream data_file;
		char search[10];
		
		itoa(account_number,search,10);
		
		data_file.open("data.txt");
		if(data_file.is_open()){
			while(!data_file.eof()){
				getline(data_file,line);
				 if((offset = line.find(search, 0)) != string::npos){
				 	cout << "found!\n";
				 	cout << line << endl;
				 }
				 data_file.close();
			}
		}
		else{
			cout << "Could not open file!";
			
		}

	}
void Bank_account::display_record(){
		ifstream data_file;
		data_file.open("data.txt");
		string line;
		int counter = 0;
		if(data_file.is_open()){

			while(!data_file.eof()){
				counter++;
				getline(data_file,line);
				if(line == ""){
					break;
				}
				cout <<counter << ")" << line << endl;
				
			}
		}
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
	//*data_file.open("data.txt", ios::out | ios::trunc);*/
	/*account number inpus and exception handling*/
	ACCOUNT_SEARCH:
	unsigned long int account_number_search;
	cout << "Enter Account Number to search : \n";
	cin >> account_number_search;
	if(cin.fail()){
		cout << "Error Occured!\n";
		cin.clear();
		cin.ignore(100,'\n');
		goto ACCOUNT_SEARCH;
	}
	int length_of_account_number = length_function(account_number_search);
	if(length_of_account_number < 8 || length_of_account_number > 10){
			cout << "Account number cannot be of " << length_of_account_number << endl;
			goto ACCOUNT_SEARCH;
		}
	
	char search[10];
	itoa(account_number_search,search,10);
		/*account number inpus and exception handling*/
		if(account_exist(search)){
			cout << "Account number exist!";
		}



		int offset;
		string line,new_line;
		//ifstream ;

		data_file.open("data.txt");
		if(data_file.is_open()){
			while(!data_file.eof()){
				getline(data_file,line);
				 if((offset = line.find(search, 0)) != string::npos){
				 	cout << line << endl;

					cout << "Enter new Data\n";
					data_file.close();
					/**/

		string f_name,l_name;
		START:
		cout << "Enter Account Holder's First Name : "<< endl;
		cin >> l_name;
		if(cin.fail()){
			cout << "Invalid Input\n";
		}

		cout << "Enter Account Holder's Last Name: "<<endl;
		cin >> f_name;
		if(cin.fail()){
			cout << "Invalid Input\n";
		}
		
		//account number cannot be negative 
		string account_number,temp_account;	

		ACCOUNT:
		cout << "Enter Account Number for " << f_name + " " + l_name << endl;
		cin >> temp_account;
		
		if(cin.fail()){
			cout << "Invalid Input\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto ACCOUNT;
		}
		try{
			stod(temp_account);
		}
		catch(invalid_argument &ex){
			cout << "Enter numbers only!";
			goto ACCOUNT;
		}
		
		//char search[10];
		//itoa(temp_account,search,10);
		if(account_exist(temp_account)){
			cout << "Account already exist!\nHence your entered data will be cleared!";
			cout << "Enter data \n";
			goto START;
		}
		
		int length_of_account_number = strlen(temp_account.c_str());
		if(length_of_account_number >= 8 && length_of_account_number <= 10){
			account_number = temp_account;
		}
		else{
			cout << "Account Number Cannot be Shorter than 8 digits or greater than 10! \n";
			goto ACCOUNT;
		}
		/*account type*/
		string account_type,temp_type;

		ACCOUNT_TYPE:
		cout << "Account type : ('s' for saving and 'c' for current) : \n";
		cin >> temp_type;
		if(cin.fail()){
			cout << "Enter Character!\n";
			goto ACCOUNT_TYPE;
		}
		if(temp_type == "s"){
			account_type = "saving";
		}
		else if(temp_type == "c"){
			account_type = "current";
		}
		else{
			cout << "Invalid Input!\n";
			goto ACCOUNT_TYPE;
		}
		/*balance*/
		string balance,temp_balance;
		BALANCE:
		cout << "Enter Balance: \n";
		cin >> temp_balance;
		if(cin.fail()){
			cout << "Invalid Input!\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto BALANCE;
		}
		try{
			stod(temp_balance);
		}
		catch(invalid_argument &ex){
			cout << "Enter numbers only! \n";
			goto BALANCE;
		}
		balance = temp_balance;
		/*changes to the file*/
	 new_line = f_name + "|" + l_name + "|" + account_number + "|" + account_type + "|" + balance;
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
	fstream data_file;
	
	data_file.open("data.txt");
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
			cout << "Enter numbers only!";
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
				 	//cout << line << endl;
				 	int end = strlen(line.c_str()) + 1;
				 	int start = data.find(line);
				 	data_file.close();
				 	//cout << data << endl;
				 	data.erase(start,end);
					data_file.open("data.txt", ios::out | ios::trunc);
	 				if(data_file.fail()){
	 					cout << "Failed to open data file!\n";
	 }
	 				data_file << data;
	 				cout << "Account Deleted Successfully!";
				 }		 
				}
			}

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cctype>
using namespace std;

class Bank_account{
public:
	bool account_exist(char *search);
	void enter_data();
	void search_account_number();	

};
int length_function(int number);

/*main function*/
int main(int argc, char const *argv[])
{
	Bank_account customer;
	customer.enter_data();
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
/************************outside function above************************/
bool Bank_account::account_exist(char *search){

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
            // cout << "found '" << search << " \n\n"<< line  <<endl;
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
		
		//account number cannot be negative 
		unsigned long int account_number,temp_account;	

		ACCOUNT:
		cout << "Enter Account Number for " << f_name + " " + l_name << endl;
		cin >> temp_account;
		
		if(cin.fail()){
			cout << "Invalid Input\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto ACCOUNT;
		}
		
		char search[10];
		itoa(temp_account,search,10);
		if(account_exist(search)){
			cout << "Account already exist!\nHence your entered data will be cleared!";
			cout << "Enter data \n";
			goto START;
		}
		
		int length_of_account_number = length_function(temp_account);
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
		double balance,temp_balance;
		BALANCE:
		cout << "Enter Balance: \n";
		cin >> temp_balance;
		if(cin.fail()){
			cout << "Invalid Input!\n";
			cin.clear();
			cin.ignore(100,'\n');
			goto BALANCE;
		}
		else{
			balance = temp_balance;
		}
		fstream data_file;
		data_file.open("data.txt", std::ios_base::app);
		data_file << "Name : " << f_name +"\t"+ l_name << "\t" << "account number : " << account_number << "\t" << "Account type : " << account_type << "\t" << "Balance :" << balance <<"\t" <<endl;
		data_file.close();
		cout << "Data saved successfully!";

}
}
void Bank_account::search_account_number(){
	while(true){
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
}

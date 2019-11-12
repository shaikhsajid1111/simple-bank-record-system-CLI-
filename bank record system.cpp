#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<cctype>
using namespace std;

class Bank_account{
public:
	void enter_data();	
};
int length_function(int number);
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

void Bank_account::enter_data(){
	
	while (true){
		string f_name,l_name;

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

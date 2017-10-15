#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <stdio.h>
#include <sstream>
//keith Nakamatsu

using namespace std;

		//this class will have information about currency such as the description, UDS dollar armount (using a golden standard), blah blah 

class Currency
{
   friend ostream &operator<<(ostream &, const Currency &);

   public:
      string CountryCode;
      string Description;
      float USD_DollarAmount;

      Currency();
      Currency(string x, string y, float z);
      Currency(const Currency &);
      ~Currency(){};
      Currency &operator=(const Currency &rhs);
      int operator==(const Currency &rhs) const;
      int operator<(const Currency &rhs) const;
     
};

Currency::Currency()   // Constructor
{
   CountryCode = "NaN";
   USD_DollarAmount = 0.0f;
   Description = "NaN";
   
}

Currency::Currency(string x , string y, float z)
{
	CountryCode = x;
	Description = y;
	USD_DollarAmount = z;
}

Currency::Currency(const Currency &copyin)   // Copy constructor to handle pass by value.
{                             
   CountryCode = copyin.CountryCode;
   Description = copyin.Description;
   USD_DollarAmount = copyin.USD_DollarAmount;
}

ostream &operator<<(ostream &output, const Currency &CurrencyObj)
{
   output << CurrencyObj.CountryCode << ' ' << CurrencyObj.USD_DollarAmount << ' ' << CurrencyObj.Description << endl;
   return output;
}

Currency& Currency::operator=(const Currency &rhs)
{
   this->CountryCode = rhs.CountryCode;
   this->Description = rhs.Description;
   this->USD_DollarAmount = rhs.USD_DollarAmount;
   return *this;
}

int Currency::operator==(const Currency &rhs) const
{
   if( this->CountryCode != rhs.CountryCode) return 0;
   if( this->Description != rhs.Description) return 0;
   if( this->USD_DollarAmount != rhs.USD_DollarAmount) return 0;
   return 1;
}

int Currency::operator<(const Currency &rhs) const
{
   if( this->CountryCode == rhs.CountryCode && this->Description == rhs.Description && this->USD_DollarAmount < rhs.USD_DollarAmount) return 1;
   if( this->CountryCode == rhs.CountryCode && this->Description < rhs.Description) return 1;
   if( this->CountryCode < rhs.CountryCode ) return 1;
   return 0;
}




	// this class will keep track and house all of the currency objects 
	class Currency_Collection{


		public:
			map<string, Currency> Map;

			Currency Obj;
			
			string string1, string2;
			Currency_Collection &operator=(const Currency &rhs);
			Currency_Collection()
			{
				//cout << "Currency constructor" << endl;

				ifstream file( "con.txt", ios::in );
				    string part1;
				    float num1;
				    
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				   cout << "Available Currencies and rate:\n";
				    while( file >> part1 >> num1  )
				    {
				    	
				        
				        Obj.CountryCode = part1;
				        Obj.USD_DollarAmount = num1;
				        
				        Map[part1] = Obj;
				        cout << part1 << " " << num1 << endl;
				       
					
				      
				    }

				   

				    file.close();
				  

			}
			bool Exist(string search)
			{
				map<string, Currency>::iterator ii;
				
				 if(Map.find(search) == Map.end())
				{
					return false;
				}
				else
				{
				
				return true;

			 	}
				
			}
			

			float Load(string search) // locate a currency and return that value
			{
				map<string, Currency>::iterator ii;
				if(Map.find(search) == Map.end())
				{
					return 123456789.987654321; //i actually dont needs this any more
				}
				else
				{
				ii= Map.find(search);

				//cout << "loading value: "<<(*ii).second.USD_DollarAmount << endl;

				return (*ii).second.USD_DollarAmount;

			 	}

			}






			void Save() // save things to the map this will be used import a large file with all the different curriences , change so that it can individuall add things via the interface
			{



			
				ifstream file( "con.txt", ios::in );
				    string part1;
				    float num1;
				    
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				    int i = 0;
				    while( file >> part1 >> num1  )
				    {
				        
				        Obj.CountryCode = part1;
				        Obj.USD_DollarAmount = num1;
				        Map[part1] = Obj;
				       // i++;

				     //   cout<< "i: "<<i << endl;
				    }

				   // cout << "Part1: "<<part1 << "\n" << endl;
				    //cout << "Num1: "<<num1 << "\n" << endl;

				    file.close();




			}
		
			// checks if currency exist if not return false
			
			void Dump()
			{


				for( map<string, Currency>::iterator ii=Map.begin(); ii!=Map.end(); ++ii)
				   {
				       cout << (*ii).first << ": " << (*ii).second << endl;
				       
				   }
			
		/*		
			cout << "dumping" << endl;
				//cout << Map.size() << endl;
				 for(int j =0; j< Map.size();j++)
				  {
				  	cout << Map[j] << endl;

				  	//cout << j << "\n" << endl;
				  }

				 */ 
/*
				  cout << Map[0] << endl;
				  cout << Map[1] << endl;
				//cout << Map.size();
*/

				
			} // print a list of all the curriencies 
		
			

	};
	




	// this class will have everything dealing with the users account, banking functions
	class Money{


		
			


		public:



			float value;
			string CurrentCountry;
			string CurrentC;
			Currency_Collection Denomination;
			// constructor
			// default constructor

			Money()
			{
				value = 100;
				CurrentC = "USD";
				CurrentCountry = "USD";

			}
			Money(float valuez, string cc)
			{
				value = valuez;
				CurrentC = cc;
				CurrentCountry = cc;
			}

			void ADD(float amount){
				value = value + amount;
			}
			void SUB(float amount){
				value = value - amount;
			}
			void View()
			{
				//cout << "This is the curriencies avaliable for conversion" << endl;
				//Denomination.Dump();

				cout << "Account balance: " << CurrentCountry << " "<< value << endl;
			}
			void DumpCurrencyList()
			{
				Denomination.Dump();
			}
			void ConvertTo(string z)
			{	
				float temp=0;
					// this function was working but now its not working

				 temp = Denomination.Load(z);
			
			// assuming no errors  need to check for errors later 
			if (Denomination.Exist(z)== true)
			{

				 if(CurrentCountry == "USD")
				 {
				 	value = value*temp;
				 	CurrentCountry = z;
				 //	CurrentC = z;
					cout << "Conversion complete:\n";
				 	//cout << CurrentCode << endl;

				 }
				 else 
				 {
				 	cout << "Converting: "<< CurrentCountry << " to: " << z << endl;

				 	float temp2;
				 	temp2 = (value/Denomination.Load(CurrentCountry))*Denomination.Load(z);
				 	//cout << CurrentC << " " << value<< " -------------> " << z<<" "<< temp2 << endl;
				 
				 	value = temp2;
				 	CurrentC = z;
				 	CurrentCountry = z;
				 	//cout << value << endl;

				 }
				
				
			}
			else 
			{
				cout << " invalid country code please try again \n";
			}
			}

	};







	//  this class will have informtion about different users, such as Name, (maybe password implementaiton later so only a ceratin person can access his or her acocunt)
	class User{


		public:
			
			Money Balance; // each user will have a Money object called balance
			
			string UserName;
			string PassWord; // will implement later but for now just leave as a reminder if security is needed

			int operator<(const User &rhs) const;
			
			User ()
			{
				/*
				UserName = "Keith";
				Balance.value = 100;
				Balance.CurrentCountry = "USD";
				*/
				
				ifstream file( "UserCollection.txt", ios::in );
				    string userName;
				    float cash;
				    string currencycode;
				    
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				    int i = 0;
				    while( file >> userName >> cash >> currencycode )
				    {
				        
				        UserName = userName;
				        Balance.value = cash;
				        Balance.CurrentCountry = currencycode;
				       // i++;

				     //   cout<< "i: "<<i << endl;
				    }

				   // cout << "Part1: "<<part1 << "\n" << endl;
				    //cout << "Num1: "<<num1 << "\n" << endl;

				    file.close();
			}
			// upon program termination this will save and overwrite user data with current data. 
			void SaveUser ()
			{
				ofstream file("UserCollection.txt");
				if(!file)
				{
					cerr << "Cant open" << endl;
					
				}
				else
				{
					file << UserName << " "<< Balance.value <<" " <<Balance.CurrentCountry;
				}
			}
			
			User &operator=(const User &rhs);
		/* // Could not set up a User_Collection class
			void SetupUser(string name, float balance, string countrycode )
			{
				//cout << "made it here to setupuser"<< endl; 
				UserName = name;
				
				Balance.value = balance;
				
				Balance.CurrentCountry = countrycode;
				Balance.CurrentC = countrycode;
			//	cout << name << " " << balance << " " << countrycode<< "\n\n" << endl;
			//	cout << "exiting setupuser end of \n"<< endl; 

			}
			*/

			void Display()
			{
				cout << "Account: " << UserName << endl;
				Balance.View();

			}
			void add(float a)
			{
				Balance.ADD(a);
			}
			void sub(float b)
			{
				Balance.SUB(b);
			}
			
			void ConvertingTime(string countrycode)
			{
				Balance.ConvertTo(countrycode);
			}
			void DumpList()
			{
				Balance.DumpCurrencyList();
			}


		


	};


User& User::operator=(const User &rhs)
{
   this->UserName = rhs.UserName;
   this->Balance.value = rhs.Balance.value;
   this->Balance.CurrentCountry = rhs.Balance.CurrentCountry;
   return *this;
}
int User::operator<(const User &rhs) const
{
   if( this->UserName == rhs.UserName && this->Balance.value == rhs.Balance.value && this->Balance.CurrentCountry < rhs.Balance.CurrentCountry) return 1;
   if( this->UserName == rhs.UserName && this->Balance.value < rhs.Balance.value) return 1;
   if( this->UserName < rhs.UserName ) return 1;
   return 0;
}









int main()
{


/*
	Currency_Collection A;

	A.Save();
	A.Dump();
	cout << A.Load("GPB");

	*/
/*
	Money big;

	big.View();
	big.ConvertTo("GPB");
	big.View();
	big.ConvertTo("AUS");
	
	big.View();
	big.ConvertTo("USD");
	big.View();
//	big.DumpCurrencyList();
*/
/*
	User Keith;
	
	Keith.Display();
	Keith.ConvertingTime("GPB");
	Keith.Display();
	*/
	

User Keith;

	int choice;
	string denom;
bool gameOn = true;
while (gameOn != false)
{
cout << "*******************************\n";
cout << " 1 - View accounts.\n";
cout << " 2 - Add Money.\n";
cout << " 3 - Sub Money.\n";
cout << " 4 - Convert to another currency \n";
cout << " 5 - Exit.\n";
cout << " Enter your choice and press return: ";

cin >> choice;

switch (choice)
{
case 1:
cout << "*******************************\n";
Keith.Display();
// rest of code here
break;
case 2:
cout << "*******************************\n";
cout << "NOTE: You can only add money that matches accounts Country Code \n";
cout << "Enter amount of money to add:";
int m;
cin >> m;
Keith.add(m);



// rest of code here
break;
case 3:
cout << "*******************************\n";
cout << "NOTE: You can only sub money that matches accounts Country Code \n";

//Keith.DumpList();

cout << "Enter amount of money to sub:";

cin >> m;
Keith.sub(m);

// rest of code here
break;
case 4:
cout << "*******************************\n";

cout << "Enter Country Code of the currency you want:";

cin >> denom;
Keith.ConvertingTime(denom);

cout << "Conversion complete!\n";
Keith.Display();

break;

case 5:
cout << "End of Program.\n";
Keith.SaveUser();
gameOn = false;
break;

default:
cout << "Not a Valid Choice. \n";
cout << "Choose again.\n";
cin >> choice;
break;
}

}
return 0;
	

	//Bank.Dump();

//	int i;
 // cout << "Please enter an integer value to select a account: ";
  //cin >> i;
/*
	int i = 1;
  Bank.FindAccount(i);
  Bank.view();
  Bank.AddMoney(150);
  Bank.ConvertMoneyTo("AUS");
  Bank.view();
  Bank.ConvertMoneyTo("GPB");
  Bank.view();


*/





}
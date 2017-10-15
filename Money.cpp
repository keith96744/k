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

			Currency_Collection(){
				//cout << "Currency constructor" << endl;

				ifstream file( "con.txt", ios::in );
				    string part1;
				    float num1;
				    
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				   
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
			

			float Load(string search) // locate a currency and return that value
			{
				map<string, Currency>::iterator ii;
				if(Map.find(search) == Map.end())
				{
					return 123456789.987654321;
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


/*
				Obj.CountryCode = "GBP";
				//Obj.Description = "European Dollar";
				Obj.USD_DollarAmount = 0.75;

				Map[1] = Obj;

				Obj.CountryCode = "USD";
				//Obj.Description = " American Dollars";
				Obj.USD_DollarAmount = 1;

				Map[0] = Obj;
				*/
			
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


				
/*
				while (infile >> key >> value)
				{
				    Map[key] = value;
				}
*/


			}
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
				//value = 100;
				//CurrentC = "USD";

			}
			Money(float valuez, string cc)
			{
				value = valuez;
				CurrentC = cc;
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
			void ConvertTo(string z)
			{	
				float temp=0;
					// this function was working but now its not working

				 temp = Denomination.Load(z);
			
			// assuming no errors  need to check for errors later 
				 if(z != "USD" || "AUS" || "GPB")
				 {
				 		// error checking implement this
				 }

				 if(CurrentCountry == "USD")
				 {
				 	value = value*temp;
				 	CurrentCountry = z;

				 	//cout << CurrentCode << endl;

				 }
				 else 
				 {
				 	cout << "Converting: "<< CurrentC << " to: " << z << endl;

				 	float temp2;
				 	temp2 = (value/Denomination.Load(CurrentC))*Denomination.Load(z);
				 	//cout << CurrentC << " " << value<< " -------------> " << z<<" "<< temp2 << endl;
				 	value = temp2;
				 	//cout << value << endl;

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
			/*
			User ()
			{
				UserName = "Keith";
				Balance.value = 100;
				Balance.CurrentCountry = "USD";
			}
			*/
			User &operator=(const User &rhs);

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


	// this class will house and keep track of all the users
	class User_Collection
	{
		public:

			map<int, User> UMap;

			User Uobject;

			User_Collection()
			{
				//cout << "User_Collection constructor" << endl;

				ifstream file( "UserCollection.txt", ios::in );
				    string getName;
				    float getBalance;
				    string getCountryCode;
				   //cout << "made it here 1"<< endl; 
				    if( !file )
				    {
				        cerr << "Cant open " << endl;
				    }
				   int i = 0;
				   //cout << "made it here 2"<< endl; 
				    while( file >> getName >> getBalance >> getCountryCode  )
				    {
				       // cout << "made it here in the loop"<< endl; 

				        Uobject.SetupUser(getName,getBalance,getCountryCode);
				       // cout << "trying to save map"<< endl; 

				        UMap[i] = Uobject;

						//cout << getName << " " << getBalance << " " << getCountryCode << "\n\n" << endl;
				       i++;


				       
				    }
				    
				   // cout << "made it here 3"<< endl; 

				   // cout << "Part1: "<<part1 << "\n" << endl;
				    //cout << "Num1: "<<num1 << "\n" << endl;

				    file.close();

			}
			void Dump()// total dump of all users and account information 
			{
				cout << "Displaying all user accounts \n\n";
				for(int x=0; x < UMap.size(); x++)
				{
					Uobject = UMap[x];
					cout << x +1<< ". ";
					Uobject.Display();
				}
			
			}
			void view ()
			{
				Uobject.Display();
			}
			void ConvertMoneyTo(string c)
			{
				Uobject.ConvertingTime(c);
			}
			void FindAccount(int x)
			{				
				Uobject = UMap[x-1]; 
			}
			void AddMoney(int v)
			{
				Uobject.add(v);
			}

	};

void ShowMenu() {
cout << "What would you like to do?\n";
		cout << "1 - Swing Sword\n";
		cout << "2 - Stab with Sword\n";
		cout << "3 - Dodge enemy attack\n";
		cout << "4 - Kick enemy\n";
        cout << "5 - Quit\n\n";
		cout << "Your move: " << endl; //flush buffer with endl occasionally

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
	big.ConvertTo("AUS");
	big.View();
*/
/*
	User Keith;
	
	Keith.Display();
	Keith.ConvertingTime("GPB");
	Keith.Display();
	*/

User_Collection Bank;

	int choice;
bool gameOn = true;
while (gameOn != false)
{
cout << "*******************************\n";
cout << " 1 - View account.\n";
cout << " 2 - Story.\n";
cout << " 3 - Help.\n";
cout << " 4 - Exit.\n";
cout << " Enter your choice and press return: ";

cin >> choice;

switch (1)
{
case 1:
Bank.Dump();
// rest of code here
break;
case 2:
cout << "Story so far....\n";
// rest of code here
break;
case 3:
cout << "Ahahah, you really think I will help you?\n";
// rest of code here
break;
case 4:
cout << "End of Program.\n";
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
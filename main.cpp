#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct district{
  string name;//: a string that holds the name of the district (note that names can consist of multiple words!)
  string type;//: a string that holds the type of the district, there are three types: "RESIDENTIAL", "COMMERCIAL",     and "HOSPITAL". Note that district type is always in all caps.
  int num_resident;// : a number for how many residents are in that district.
  double power;//: how much power the district is currently consuming from the power grid.
  bool has_power;//: a boolean that indicates if the district is currently supplied with power or not.
  int num_technician;// : a number for how many residents are in that district.
  string technicians[100];//: a string array holding the names of all the technicians assigned to that district
};
void load(string fname, district districts[], int &num, int &power){
  ifstream fin(fname);
  // if(!input.is_open())
  //   cout << 
  fin >> power;
  fin >> num;
  fin.ignore();
  for(int i = 0; i<num;i++){
     getline(fin, districts[i].name);
     fin >> districts[i].type;
     fin >> districts[i].num_resident;
     fin >> districts[i].power;
     fin >> districts[i].has_power;
     fin >> districts[i].num_technician;
     // cin.ignore is used if getline comes after cin
     fin.ignore();
     if(districts[i].num_technician > 0){
        for(int j = 0; j<districts[i].num_technician; j++)
          getline(fin, districts[i].technicians[j]);
     }
  }
  
  int i, j;
  district temp;
  for(j=0; j< num-1; j++)
   {
      for(i = 0; i < num-1; i++)
      {
         if(districts[i].num_resident > districts[i+1].num_resident)
         {
            temp = districts[i];
            districts[i] = districts[i+1];
            districts[i+1] = temp;
         }
      }
   }
  fin.close();
}

void save(string fname, district districts[], int num, int power){
  ofstream fout(fname);
  fout << power << endl;
  fout << num << endl;
  for(int i = 0; i < num; i++){
    fout << districts[i].name << endl;
    fout << districts[i].type << endl;
    fout << districts[i].num_resident << endl;
    fout << districts[i].power << endl;
    fout << districts[i].has_power << endl;
    fout << districts[i].num_technician<< endl;
    if(districts[i].num_technician > 0){
        for(int j = 0; j<districts[i].num_technician; j++)
          fout << districts[i].technicians[j] << endl;
    }
  }
  fout.close();
}

void print_all(district districts[], int num, int power){
  cout << "The current power supply is " << power << "MW." << endl;
  for(int i = 0; i < num; i++){
    cout << districts[i].name << endl;
    cout << "District type: " << districts[i].type << endl;
    cout << "Number of residents: " << districts[i].num_resident << endl;
    if(districts[i].has_power == false){
      cout << "Power use: 0MW" <<endl;
    }
    else{
      cout << "Power use: " << districts[i].power << "MW" <<endl;
      }
    cout << "Has power: " << districts[i].has_power << endl;
    if(districts[i].num_technician != 0){
      cout << "Technicians: ";
      for(int j = 0; j < districts[i].num_technician - 1; j++){
        cout << districts[i].technicians[j] << ", ";
      }
      cout << districts[i].technicians[districts[i].num_technician - 1] << endl;
    }
    cout << "---" << endl;
  }
  int total_demand = 0;
      for(int i = 0; i < num; i++){
        if(districts[i].has_power == true)
          total_demand += districts[i].power;
        }
    if(total_demand > power){
        cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply "; 
        cout <<total_demand << "MW of power demand. Please shut off one or more districts." << endl;
        cout << "---" << endl;
      }
      
}

void assign_technician(string tech_name, string district_name, district districts[], int num_district){
  int c = -1;  
  for(int i = 0; i < num_district; i++){
      if(districts[i].name == district_name){
        {
          int count = districts[i].num_technician;
          districts[i].technicians[count] = tech_name;
          districts[i].num_technician++;
          cout << "Technician assigned!" << endl;
          c++;
        }
      }
    }
  if(c == -1){
    cout << "Error! The district with that name doesn't exist." << endl;
  }
}

void cut_power(string name_dis, district districts[], int arrSize){
  int c = -1;
  for(int i = 0; i < arrSize; i++){
    if(districts[i].name == name_dis)
      {
        districts[i].has_power = 0;
        cout << "The district's power has been successfully turned off." << endl;
        c++;
      }
  }
  if(c == -1){
    cout << "Error! The district with that name doesn't exist." << endl;
  }
}

void restore_power(string name_dis, district districts[], int arrSize){
  int c = -1;
  for(int i = 0; i < arrSize; i++){
    if(districts[i].name == name_dis)
      {
        districts[i].has_power = 1;
        cout << "The district's power has been successfully turned back on." << endl;
        c++;
      }
  }
  if(c == -1){
    cout << "Error! The district with that name doesn't exist." << endl;
  }
}

int main() {
  string fname;
  cout << "Please enter the name of the file to load:" << endl;
  cin >> fname;
  int num, power;
  district districts[100];
  load(fname, districts, num, power);
  print_all(districts, num, power);
  int option;
  cout << "Main Menu" << endl;
  cout << "1- Status" << endl;
  cout << "2- Set Power Supply" << endl;
  cout << "3- Shutoff Power" << endl;
  cout << "4- Restore Power" << endl;
  cout << "5- Assign Technician" << endl;
  cout << "6- Save" << endl;
  cout << "7- Load" << endl;
  cout << "8- Exit" << endl;
  cout << "Please enter your choice:" << endl;
  cin >> option;
  while(option >=1 and option <= 8){
    if(option == 1){
      print_all(districts, num, power);
      
      }
      
    
    else if(option == 2){
      cout << "Enter the updated power supply in megawatts:" << endl;
      cin >> power;
      
    }
    else if(option == 3){
      string name_dis;
      cout << "Enter the name of the district:" << endl;
      cin.ignore();
      getline(cin, name_dis);
      cut_power(name_dis, districts, num);
    }
    else if(option == 4){
      string name_dis;
      cout << "Enter the name of the district:" << endl;
      cin.ignore();
      getline(cin, name_dis);
      restore_power(name_dis, districts, num);
    }
    else if(option == 5){
      string name_tech,name_dis;
      cin.ignore();
      cout << "Enter the name of the technician:" << endl;
      getline(cin, name_tech);
      cout << "Enter the name of the district to assign them to:" << endl;
      getline(cin, name_dis);
      assign_technician(name_tech, name_dis, districts, num);
    }
    else if(option == 6){
      string name_f;
      cout << "Enter the file name to save to:" << endl;
      cin >> name_f;
      save(name_f, districts, num ,power);
    }
    else if(option == 7){
      string name_f;
      cout << "Enter the file name to load from:" << endl;
      cin >> name_f;
      load(name_f, districts, num ,power);
    }
    else{
      exit(1);
    }
    cout << "Main Menu" << endl;
    cout << "1- Status" << endl;
    cout << "2- Set Power Supply" << endl;
    cout << "3- Shutoff Power" << endl;
    cout << "4- Restore Power" << endl;
    cout << "5- Assign Technician" << endl;
    cout << "6- Save" << endl;
    cout << "7- Load" << endl;
    cout << "8- Exit" << endl;
    cout << "Please enter your choice:" << endl;
    cin >> option;
  }
  if(option < 1 || option > 8){
    cout << "Invalid option!" << endl;
  }
}
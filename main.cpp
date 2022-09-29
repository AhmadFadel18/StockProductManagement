#include <iostream>
#include <iomanip>
using namespace std;

    //Global variables
    //receipt[max number][menu item]
    int receipt[1000][4];
    
    //catalogued items
    struct item{
      string name;
      int stock;
      float price;
      float cost;
    };

    item dataM[]={
      {"Water", 500, 5,  3}, {"Rice", 500, 5, 3.5},
      {"Chicken", 500, 10, 7.25},  {"Beef", 500, 20, 12.5},
    };

int SelectMenu() {
    int select;
    cout << "Please choose an operation. \n"
        << "1. Input receipts \n"
        << "2. Calculate sales and profits \n"
        << "3. Sort products by units sold \n"
        << "4. Inventory Tracker \n"
        << "5. Exit\n";
    cout << "Your choice: ";
    cin >> select;
    cout << endl;
      //change 5 with number of choices
    if (select > 0 && select <= 5) {
        return select;
    }
    else {
        cout << "Invalid Input\n\n";
        return 0;
    }
}

int SelectOption(int sel){
    int select;
    switch(sel){
        case 1:{
            //option to choose sales & profit per receipt or total sales & profits
            cout << "Please select an option: \n"
                << "1. Sales & profit per receipt \n"
                << "2. Total sales & profits \n"
                << "3. Exit\n";
            cout << "Your choice: ";
            cin >> select;
            cout << endl;

            if (select > 0 && select <= 3) {
                return select;
            }else{
                cout << "Invalid Input\n\n";
                return 0;
            }
            break;
        }case 2:{
            return 0;
            break;
        }
    }
    return 0;
}

void Calculate(int sel, int receiptNum, int menulen){
  float sales[2][receiptNum];
  for (int i = 0; i < receiptNum; i++) // ...initialize it
  {
      sales[0][i] = 0;     //array for sales
      sales[1][i] = 0;     //array for profits 
  }
  
  //option to choose sales & profit per receipt
    for(int i = 0; i < receiptNum; i++){
      for(int j = 0; j < menulen; j++){
        //calc sales
        sales[0][i] += receipt[i][j]*dataM[j].price;
        //calc profits
        sales[1][i] += receipt[i][j]*(dataM[j].price - dataM[j].cost);
      }
    }

  //option to choose total sales & profit
    float tot_sales = 0;
    float tot_profs = 0;

    for(int i = 0; i < receiptNum; i++){
      tot_sales += sales[0][i];
      tot_profs += sales[1][i];
    }

  //print sales & profits
    //if sel= 1 -> per receipt 
    if (sel == 1){
      for(int i = 0; i < receiptNum; i++){
        cout << "\nSales from receipt " << i + 1 << "\t: " << sales[0][i] << " $";
        cout << "\nProfits from receipt " << i + 1 << "\t: " << sales[1][i] << " $\n";
      }
      cout << endl;
    }
    else if (sel == 2){
      cout << "Total sales  : " << tot_sales << " $\n";
      cout << "Total profits: " << tot_profs << " $\n";
      cout << endl;
    }
    else {
      cout << "Invalid Input";
    }
}

void Sort(int n, int menu) {
    int temp, tempind;
    int index[menu], sales[menu];
    for (int i = 0; i < menu; i++) // ...initialize it
    {
        sales[i] = 0;
    }
    for (int i = 0; i < menu; i++) // ...initialize it
    {
        index[i] = i;
    }
    
    //calc units sold
        //loop for receipts
    for(int i=0; i<n;  i++){
        //loop for menu items
        for(int j=0; j<menu; j++){
          sales[j] += receipt[i][j];
        }
    }
    //Insertion Sort
    for (int j = 1; j < menu; j++) {
        int i;
        i = j - 1;
        temp = sales[j];
        tempind = index[j];
        while (sales[i] < temp && i >= 0) { 
            sales[i + 1] = sales[i]; 
            index[i + 1] = index[i]; 
            i--; 
        }
        sales[i + 1] = temp;
        index[i + 1] = tempind;
    }

    int ind;
    for(int i=0; i<menu; i++){
        ind = index[i];
        cout<<dataM[ind].name << ": " << sales[i] << endl;
    }
    cout << endl;
}

int main() {
  int userSelection=0, optionSelection=0;
  bool isOn = true;
  //receipt
  int receiptNum;
  int menuLength = 4;

  //User selection
  while (userSelection == 0) {
      userSelection = SelectMenu();
  }
  
  //while the program is active
  while(isOn){
      optionSelection = 0;
      
    switch (userSelection){
      case 1:{ //input receipts one by one
        cout << "Enter amount of receipts: ";
        cin >> receiptNum;
        cout << endl;

        //loop for receipts
        for(int i = 0; i < receiptNum;  i++){
          //loop for menu items
          cout << "Receipt #" << i + 1 << endl;
          for(int j = 0; j < 4; j++) {
            cout << "Enter amount of " << dataM[j].name << ": ";
            cin >> receipt[i][j];
          }
          cout << endl;
        }
        userSelection = SelectMenu(); break;
      }
      case 2:{ 
          // calculate
          while (optionSelection == 0) {
              optionSelection = SelectOption(1);
          }
          Calculate(optionSelection, receiptNum, menuLength);
        userSelection = SelectMenu(); break;          
      }
      case 3:{ //sort
        Sort(receiptNum, menuLength);
        userSelection = SelectMenu(); break;          
      }
      case 4:{ 
        int receiptNum, stock;
        int item_left[4];
        cout << "Enter amount of receipts: ";
        cin >> receiptNum;
        cout << endl;

        //loop for receipts
        for(int i = 0; i < receiptNum;  i++){
          cout << "Receipt #" <<  i+1 << endl;
          //loop for menu items
          for(int j=0; j<4; j++){
            cout << "Enter amount of " << dataM[j].name << ": ";
            cin >> receipt[i][j];
            
            item_left[j] = dataM[j].stock-receipt[i][j];
            dataM[j].stock = item_left[j];
          }            
          cout <<"No\tItems\tLeft" << endl; 
          for (int j=0;j<4;j++){
            cout<<j+1<<setw(6)<<dataM[j].name<<setw(6)<<item_left[j]<<endl;
          }
          cout<<endl;
        }
        userSelection = SelectMenu(); break;
      }
      case 5:{ //exit program
        isOn = false; break;          
      }
      default: userSelection = SelectMenu(); break;
    }
  }
return 0;
}
//members: Sarah Alhethily 2230040060 , Noura AlSaeed 2220002127 ,Fawziah Alshehri 2220002886 


#include <iostream>
#include <string>
#include <fstream>
#include "discount.h"
using namespace std;

// Order structure contains customer name, array of selected services, array of selected location

const int NUM_SERVICES = 6;

struct Service
{
    string name; //name of service
    int price; //price of service
};

struct Order
{
    string customerName;
    int *serviceChoices = new int[NUM_SERVICES]; //dynamic array 
    int location = 0; //home or shop
};

// printServices function prints all the services
void printServices(Service *services) // pointer so we can acsses to the services
{
    cout << "Services:" << endl;
    for (int i = 0; i < NUM_SERVICES; i++)
    {
        cout << i + 1 << ". " << services[i].name << " - SAR" << services[i].price << endl; 
    }
}

void printReceipt(string customerName, Service services[], int serviceChoices[], int serviceChoicesLength, int location, bool &disc)
{
    double total = 0;
    cout << "------ Receipt ------" << endl;
    cout << "Customer Name: " << customerName << endl;
    cout << "Services: " << endl;
    for (int i = 0; i < serviceChoicesLength; i++) // to print only the services that has been selected
    {
        if (serviceChoices[i] != -1) 
        {
           
            cout << services[serviceChoices[i]].name << " - SAR" << services[serviceChoices[i]].price << endl;
            total += services[serviceChoices[i]].price;
        }
    }
    cout << "Location: ";
    if (location == 1)
    {
        cout << "Home Service" << endl;
    }
    else
    {
        cout << "Shop Service" << endl;
    }
    if(!disc){
        total = applyDiscount(total);
    }
    cout << "------ Total ------" << endl;
    cout << "Total Cost: SAR" << total << endl;
}

//The `printServicesReceipt` function prints the services chosen by the customer
// and writes the output to a file stream.
void printServicesReceipt(Service *services, int *serviceChoices, int serviceChoicesLength, ofstream &receiptFile)
{
    receiptFile << "--- Services ---" << endl;
    for (int i = 0; i < serviceChoicesLength; i++)
    {
        if (serviceChoices[i] != -1)
        {
            receiptFile << services[serviceChoices[i]].name << " - SAR" << services[serviceChoices[i]].price << endl;
        }
    }
}

//The `saveReceiptToFile` function saves the receipt of the customer's order
//   to a file with the name `customerName-Receipt.txt`.
void saveReceiptToFile(string customerName, Service *services, int *serviceChoices, int serviceChoicesLength, int location, bool &disc)
{
    ofstream receiptFile;
    double total = 0;
    string rfilename= customerName + "-Receipt.txt";
    receiptFile.open("-Receipt.txt");
    receiptFile << "------ Receipt ------" << endl;
    receiptFile << "Customer Name: " << customerName << endl;
    printServicesReceipt(services, serviceChoices, serviceChoicesLength, receiptFile);
    receiptFile << "Location: ";
    if (location == 1)
    {
        receiptFile << "Home Service" << endl;
    }
    else
    {
        receiptFile << "Shop Service" << endl;
    }

    for (int i = 0; i < serviceChoicesLength; i++)
    {
        if (serviceChoices[i] != -1)
        {
            total += services[serviceChoices[i]].price;
        }
    }
    if(!disc){
        total = applyDiscount(total);
    }
    receiptFile << "------ Total ------" << endl;
    receiptFile << "Total Cost: SAR" << total << endl;
    receiptFile.close();
}
// function to swap two elements in the array
void swapServices(Service &a, Service &b)
{
    Service temp = a;
    a = b;
    b = temp;
}

// function to sort services array
void sortServices(Service services[], int size)
{
    int minIndex;
    for (int i = 0; i < size - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (services[j].price < services[minIndex].price)
            {
                minIndex = j;
            }
        }
        swapServices(services[minIndex], services[i]);
    }
}

void makeOrder(Service services[], Order &order) // the main function that 
{
    cout << "Please enter your name: ";
    getline(cin, order.customerName);
    int SnumChoices = 0;
    bool flag = true;
    bool disc = false;
    while (flag)
    {
        cout << "Please choose from the following options:" << endl;
        cout << "1. View Services" << endl;
        cout << "2. Sort Services by price" << endl;
        cout << "3. Order Services" << endl;
        cout << "4. View Receipt" << endl;
        cout << "5. Save Receipt to a file" << endl;
        cout << "0. Exit" << endl;
        
        int choice;
        cout << "Please Enter your choice: ";
        cin >> choice;
        
        switch (choice)
        {
            case 1:
                printServices(services);
                system("pause");// to display "any key to continue" fo the user in the out put
                break;
            case 2:
                sortServices(services, NUM_SERVICES);
                printServices(services);
                system("pause");
                break;
            case 3:
                if (order.location == 0) // if the user didnt choose a location yet
                {
                    cout << "Please select the location of the service:" << endl;
                    cout << "1. Home Service" << endl;
                    cout << "2. Shop Service" << endl;
                    cin >> order.location;
                }
                cout << "Please select the services you would like to order by entering their corresponding numbers:" << endl;
                printServices(services);
                
                while (true)
                {
                    int serviceNum;
                    cout << "Please Enter your choice or 0 to continue: ";
                    cin >> serviceNum;
                    if (serviceNum == 0)
                    {
                        break;
                    }
                    // check if location has been selected before
                    if (order.location == 0)
                    {
                        cout << "Please select the location of the service:" << endl;
                        cout << "1. Home Service" << endl;
                        cout << "2. Shop Service" << endl;
                        cin >> order.location;
                    }
                    order.serviceChoices[SnumChoices] = serviceNum - 1;
                    SnumChoices++;
                }
                    break;
                case 4:
                    printReceipt(order.customerName, services, order.serviceChoices, SnumChoices, order.location, disc);
                    system("pause"); //call function 
                    
                    break;
                case 5:
                    saveReceiptToFile(order.customerName, services, order.serviceChoices, SnumChoices, order.location, disc);
                    system("pause");  //call function 
                    break;
                case 0:
                    cout << "Thank you for choosing our Barber Shop! Have a good day." << endl;
                    flag = false;
                    break;
                default:
                    cout << "Invalid input." << endl;
                }
        }
    }
    
    int main()
    {
        // initialize services
        Service services[NUM_SERVICES] = {
            {"Hair Cut", 30},
            {"Beard Trim", 20},
            {"Shampoo", 15},
            {"Hair Coloring", 50},
            {"Hair Styling", 25},
            {"Hair Treatment", 40}};
        
        Order order;
        
        makeOrder(services, order);  //call function 
        
        return 0;
    }


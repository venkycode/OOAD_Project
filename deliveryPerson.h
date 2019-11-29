#include "ShopKeeper.h"

class deliverPerson : public User{
    public:
    int assignedOrderId;// -1 if none is assigned

    // A class constructor
    deliverPerson(profile Profile, int choice){
        assignUserProfile(Profile);
        if(choice == 2){ // Sign up case
            systemAdmin.insert_unassigned_deliveryPerson(userID); /* Adds the delivery person to the database of 
                                                                    available delivery persons */
            assignedOrderId = -1;
            systemAdmin.assignUnassignedOrders();  // Assigns orders in waiting, if any to the delivery person
        }
        else assignedOrderId = systemAdmin.AssignedOrderId(Profile.id);
    }

    // Checks if the delivery person is available
    bool isAvailable(){
        return assignedOrderId == -1;
    }

    // A function for delivery person to check if any order is assigned to him/her
    void checkIfOrderIsAssigned(){
        printHeader();
        if(assignedOrderId==-1){
            cout<<fgred<<printtabs(9)<<"No order is assigned" << "\n";
        }
        else {
            cout<<fggreen<<printtabs(9)<< "You have been assigned an order" << endl;  
            cout<<fggreen<<printtabs(9)<<"Order ID : "<<assignedOrderId<<endl;   
            order currentOrder=systemAdmin.extactOrderInfo(to_string(assignedOrderId));
            cout<<fggreen<<printtabs(9)<<currentOrder.order_<<endl;
            cout<<fggreen<<printtabs(9)<<"Customer address : "<<systemAdmin.addressFromId(currentOrder.customerID)<<"\n";
            cout<<fggreen<<printtabs(9)<<currentOrder.other_details<<endl;
        }
        cout<<fggreen<<printtabs(9)<< "Press enter to go back" << endl <<printtabs(9);
        string choice;
        getline(cin, choice);
        getline(cin, choice);
    }

    // A function for delivery person to get the required information about product from its product ID
    void getProductInfoFromId(){
        printHeader();
        int productID;
        cout<< fggreen<<printtabs(9)<<"Enter product ID"<< endl ;
        printInputField();
        cin>>productID;
        if(systemAdmin.productId_to_product.find(productID)==systemAdmin.productId_to_product.end()){
            cout<< fgred<<printtabs(9)<<"Product not present in the inventory" <<endl;
        }
        else {
            product currentProduct=systemAdmin.productId_to_product[productID];
            cout<<fggreen<<printtabs(9)<<"Product Name :"<<currentProduct.product_name<<endl;
            cout<<fggreen<<printtabs(9)<<"Shop name :"<<systemAdmin.nameFromId(currentProduct.shopkeeper_id)<<endl;
            cout<<fggreen<<printtabs(9)<<"Shop address :"<<systemAdmin.addressFromId(currentProduct.shopkeeper_id)<<endl;
        }
        cout<<printtabs(9)<<fggreen<<"Do you want to search more products(Y/n): ";
        char choice;
        cin>>choice;
        if(choice == 'Y' || choice == 'y')getProductInfoFromId();
    }

    // A function for delivery person to update the status(expected time left) of the order he/she is delivering
    void updateStatus(){
        printHeader();
        if(assignedOrderId != -1){
            cout<<fggreen<<printtabs(9)<<"Enter the expected time left in dd:hh:mm format" << endl;
            printInputField();
            string timeLeft;cin>>timeLeft;
            systemAdmin.updateTime(to_string(assignedOrderId),timeLeft);
            if(timeLeft=="00:00:00"){ // i.e. the order is delivered
                systemAdmin.finish_order(userID);
                assignedOrderId = -1;
                systemAdmin.insert_unassigned_deliveryPerson(userID);  /* Adds the delivery person to the database of 
                                                                    available delivery persons */
            }
        }
        else cout<<fgred<<printtabs(9)<<"No order is assigned"<<endl;
        cout<<fggreen<<printtabs(9)<< "Press enter to go back" << endl <<printtabs(9);
        string choice;
        getline(cin, choice);
        getline(cin, choice);
    }

    void assignOrder(int orderId){
        assignedOrderId = orderId;
        systemAdmin.assign_order(userID, orderId);
    }

};
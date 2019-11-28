#include "ShopKeeper.h"

class deliverPerson : public User{
    public:
    int assignedOrderId;// -1 if none is assigned
    deliverPerson(profile Profile, int choice){
        assignUserProfile(Profile);
        if(choice == 2){
            systemAdmin.insert_unassigned_deliveryPerson(userID);
            assignedOrderId = -1;
            systemAdmin.assignUnassignedOrders();
        }
        else assignedOrderId = systemAdmin.AssignedOrderId(Profile.id);
    }

    bool isAvailable(){
        return assignedOrderId == -1;
    }

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

    void updateStatus(){
        printHeader();
        if(assignedOrderId != -1){
            cout<<fggreen<<printtabs(9)<<"Enter the expected time left in dd:hh:mm format" << endl;
            printInputField();
            string timeLeft;cin>>timeLeft;
            systemAdmin.updateTime(to_string(assignedOrderId),timeLeft);
            if(timeLeft=="00:00:00"){
                systemAdmin.finish_order(userID);
                assignedOrderId = -1;
                systemAdmin.insert_unassigned_deliveryPerson(userID);
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
#include "User.h"

class deliverPerson : public User{
    public:
    int assignedOrderId;// -1 if none is assigned
    deliverPerson(profile Profile){
        assignUserProfile(Profile);
        assignedOrderId = systemAdmin.AssignedOrderId(Profile.id);
    }
    deliverPerson(){
        signUp();
        systemAdmin.insert_unassigned_deliveryPerson(userID);
        assignedOrderId = -1;
    }

    bool isAvailable(){
        return assignedOrderId == -1;
    }

    void checkIfOrderIsAssigned(){
        if(assignedOrderId==-1){
            cout<<"No order is assigned" << "\n";
            return;
        }
        cout<<"You have been assigned an order";     //INCOMPLETE
        
    }

    void updateStatus(){
        /*cout<<"Enter the expected time left" << "\n";
        
        if(timeRemaining.days == 0 && timeRemaining.hours == 0 && timeRemaining.minutes == 0){
            systemAdmin.finish_order(userID);
            assignedOrderId = -1;
            systemAdmin.insert_unassigned_deliveryPerson(userID);
        }*/
    }

    void assignOrder(int orderId){
        assignedOrderId = orderId;
        systemAdmin.assign_order(userID, orderId);
    }

};
#include "User.h"

class deliverPerson : public User{
    public:
    int assignedOrderId;// -1 if none is assigned
    deliverPerson(profile Profile){
        assignUserProfile(Profile);
        assignedOrderId = systemAdmin.AssignedOrderId(Profile.id);
    }
    deliverPerson(){
        //signUp();
        login();  ///TEMPORARY CHANGE
        assignedOrderId = -1;
    }

    bool isAvailable(){
        return assignedOrderId == -1;
    }

    void updateStatus(order &Order, timeStamp timeRemaining){
        Order.remainingTime = timeRemaining;
        if(timeRemaining.days == 0 && timeRemaining.hours == 0 && timeRemaining.minutes == 0){
            systemAdmin.finish_order(userID);
            assignedOrderId = -1;
        }
    }

    void assignOrder(int orderId){
        assignedOrderId = orderId;
        systemAdmin.assign_order(userID, orderId);
    }

};
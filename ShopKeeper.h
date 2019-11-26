#include "Customer.h"

class shopKeeper:public User{
    public:
    shopKeeper(profile Profile){
        assignUserProfile(Profile);
    }
    shopKeeper(){
        //signUp();
        login();        //TEMPORARY CHANGE
    }
    void addToInventory(){
        product productToAdd;
        productToAdd.shopkeeper_id[0]='S';
        productToAdd.shopkeeper_id[1]=userID[1];
        cout<<fggreen<<printtabs(9)<<"Enter the name of product you want to add" << "\n" ;
        char productName[10];cin>>productName;
        strcpy(productToAdd.product_name,productName);
        cout<<fggreen<<printtabs(9)<<"Enter the count of products you possess" << "\n";
        int productCount;cin>>productCount;
        productToAdd.count=productCount;            //product type pending
        productToAdd.deliveryCharge=0;
        cout<<fggreen<<printtabs(9)<<"Enter the price of this product" << "\n" ;
        int productPrice;cin>>productPrice;
        productToAdd.price=productPrice;
        productToAdd.rating=0;
        productToAdd.product_id=state.productCount++;
        systemAdmin.addToInventory(productToAdd);
    }

    void displayInventory(){
        for(auto y : systemAdmin.personal_inventory[userID]){
            product currentProduct=systemAdmin.productId_to_product[y];
            if(currentProduct.count==0)continue;
            cout<<fggreen<<printtabs(9)<<"Product name : "<<fgred << currentProduct.product_name << "\n";
            cout<<fggreen<<printtabs(9)<<"Product ID : "<<fgred << currentProduct.product_id << "\n";
            cout<<fggreen<<printtabs(9)<<"Available quantity : "<<fgred << currentProduct.count << "\n";
            cout<<fggreen<<printtabs(9) << "Price :"<<fgred << currentProduct.price << "\n";
        }
        //cout<<systemAdmin.personal_inventory[userID].size()<<endl;
    }

    void changeCount(){
        cout<<fggreen<<printtabs(9)<<"Enter the ID of product whose count needs to be updated" << "\n";
        int productID;cin>>productID;
        cout<<fggreen<<printtabs(9)<<"Enter the changed count" << "\n";
        int changedCount;cin>>changedCount;
        systemAdmin.changeProductCount(productID, changedCount);
    }

    void changePrice(){
        cout<<fggreen<<printtabs(9)<<"Enter the ID of product whose price needs to be updated" << "\n";
        int productID;cin>>productID;
        cout<<fggreen<<printtabs(9)<<"Enter the changed price" << "\n";
        int changedPrice;cin>>changedPrice;
        systemAdmin.changeProductPrice(productID, changedPrice);
    }

    void removeFromInventory(){
        cout<<fggreen<<printtabs(9)<<"Enter the ID of product you want to remove" << "\n";
        int productID;cin>>productID;
        systemAdmin.changeProductCount(productID, 0);
    }
};
#include "Customer.h"

class shopKeeper:public User{
    public:
    shopKeeper(profile Profile){
        assignUserProfile(Profile);
    }
    shopKeeper(){
        signUp();
    }
    void addToInventory(){
        printHeader();
        product productToAdd;
        productToAdd.shopkeeper_id[0]='S';
        productToAdd.shopkeeper_id[1]=userID[1];
        cout<<fggreen<<printtabs(9)<<"Enter the name of product you want to add" << "\n" ;
        cout<<printtabs(9)<<fgblue<<">>";
        char productName[10];cin>>productName;
        strcpy(productToAdd.product_name,productName);
        cout<<fggreen<<printtabs(9)<<"Choose the product type"<<endl;
        while(1){
            printOption(9,0,"Stationery",1);
            printOption(9,0,"Electronics",2);
            printOption(9,0,"Food",3);
            printOption(9,0,"Groceries",4);
            cout<<printtabs(9)<<fgblue<<">>";
            int response;cin>>response;
            switch (response)
            {
            case 1:
                productToAdd.product_type=stationery;
                break;
            case 2:
                productToAdd.product_type=electronics;
                break;
            case 3:
                productToAdd.product_type=food;
                break;
            case 4:
                productToAdd.product_type=groceries;
                break;
            default:
                cout<<fgred<<printtabs(9)<<"Invalid choice"<<endl;
            }
            if(response==1||response==2||response==3||response==4)break;
        }
        cout<<fggreen<<printtabs(9)<<"Enter the count of products you possess" << "\n";
        cout<<printtabs(9)<<fgblue<<">>";
        int productCount;cin>>productCount;
        productToAdd.count=productCount;           
        productToAdd.deliveryCharge=0;
        cout<<fggreen<<printtabs(9)<<"Enter the price of this product" << "\n" ;
        cout<<printtabs(9)<<fgblue<<">>";
        int productPrice;cin>>productPrice;
        productToAdd.price=productPrice;
        productToAdd.rating=0;
        productToAdd.product_id=state.productCount++;
        systemAdmin.addToInventory(productToAdd);
        cout<<fggreen<<printtabs(9)<<"Press enter to go back to dashboard"<<endl;
        cout<<fgblue<<printtabs(9)<<">>";
        string st;getline(cin,st);getline(cin,st);
    }

    void displayInventory(){
        printHeader();
        if(systemAdmin.personal_inventory[userID].size()==0){
            cout<<fgred<<printtabs(9)<<"Your inventory is empty"<<endl;
        }
        else{
            for(auto y : systemAdmin.personal_inventory[userID]){
                product currentProduct=systemAdmin.productId_to_product[y];
                if(currentProduct.count==0)continue;
                cout<<fggreen<<printtabs(9)<<"Product name : "<<fgred << currentProduct.product_name << "\n";
                cout<<fggreen<<printtabs(9)<<"Product ID : "<<fgred << currentProduct.product_id << "\n";
                cout<<fggreen<<printtabs(9)<<"Available quantity : "<<fgred << currentProduct.count << "\n";
                cout<<fggreen<<printtabs(9) << "Price :"<<fgred << currentProduct.price << "\n";
                cout<<"\n";
            }
        }
        cout<<fggreen<<printtabs(9)<<"Press enter to go back to dashboard"<<endl;
        cout<<printtabs(9)<<fgblue<<">>";
        string st;getline(cin,st);getline(cin,st);
    }

    void changeCount(){
        printHeader();
        cout<<fggreen<<printtabs(9)<<"Enter the ID of product whose count needs to be updated" << "\n";
        cout<<printtabs(9)<<fgblue<<">>";
        int productID;cin>>productID;
        if(systemAdmin.personal_inventory[userID].count(productID)){
            cout<<fggreen<<printtabs(9)<<"Enter the changed count" << "\n";
            cout<<printtabs(9)<<fgblue<<">>";
            int changedCount;cin>>changedCount;
            systemAdmin.changeProductCount(productID, changedCount);
        }
        else{
            cout<<fgred<<printtabs(9)<<"This product does not belong to your inventory"<<endl;
        }
        cout<<fggreen<<printtabs(9)<<"Press enter to go back to dashboard"<<endl;
        cout<<printtabs(9)<<fgblue<<">>";
        string st;getline(cin,st);getline(cin,st);
    }

    void changePrice(){
        printHeader();
        cout<<fggreen<<printtabs(9)<<"Enter the ID of product whose price needs to be updated" << "\n";
        cout<<printtabs(9)<<fgblue<<">>";
        int productID;cin>>productID;
        if(systemAdmin.personal_inventory[userID].count(productID)){
            cout<<fggreen<<printtabs(9)<<"Enter the changed price" << "\n";
            cout<<printtabs(9)<<fgblue<<">>";
            int changedPrice;cin>>changedPrice;
            systemAdmin.changeProductPrice(productID, changedPrice);
        }
        else{
            cout<<fgred<<printtabs(9)<<"This product does not belong to your inventory"<<endl;
        }
        cout<<fggreen<<printtabs(9)<<"Press enter to go back to dashboard"<<endl;
        cout<<printtabs(9)<<fgblue<<">>";
        string st;getline(cin,st);getline(cin,st);
    }

    void removeFromInventory(){
        printHeader();
        cout<<fggreen<<printtabs(9)<<"Enter the ID of product you want to remove" << "\n";
        cout<<printtabs(9)<<fgblue<<">>";
        int productID;cin>>productID;
        if(systemAdmin.personal_inventory[userID].count(productID)){
            systemAdmin.changeProductCount(productID, 0);
        }
        else{
            cout<<fgred<<printtabs(9)<<"This product does not belong to your inventory"<<endl;
        }
        cout<<fggreen<<printtabs(9)<<"Press enter to go back to dashboard"<<endl;
        cout<<printtabs(9)<<fgblue<<">>";
        string st;getline(cin,st);getline(cin,st);
    }
};
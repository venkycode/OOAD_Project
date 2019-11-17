#include "User.h"
#include "stringMatching.h"

class customer:public User{
    public:
    bool sortByRating(product product1, product product2){
        return product1.rating > product2.rating ;
    }

    bool sortByIncreasingPrice(product product1, product product2){
        return product1.price < product2.price ;
    }

    bool sortByDecreasingPrice(product product1, product product2){
        return product1.price > product2.price ;
    }

    void search(){
        cout<<"Enter the product you want to look-up" << "\n" ;
        string toBeSearched;
        cin>> toBeSearched;
        cout<<"Do you want a filter for your search results? Y/n" << "\n";
        char response;cin>>response;
        int input;
        if(response=='y'||response=='Y'){
            cout<<"Choose your filter of products" << "\n";
            cout<<"Press 1 for decreasing order of rating" << "\n" ;
            cout << "Press 2 for increasing order of price" << "\n";
            cout<<"Press 3 for decreasing order of price" << "\n" ;
            cin>>input;
        }
        vector<product> matches;
        for(auto currentProduct:systemAdmin.global_inventory){
           bool doesMatch=isMatch(currentProduct.first,toBeSearched);
           if(doesMatch){
               for(auto ids:currentProduct.second){
                   if(systemAdmin.productId_to_product[ids].count) matches.push_back(systemAdmin.productId_to_product[ids]);
               }
           }
        }
        if(response=='n'||response=='N');
        else if(input==1)sort(matches.begin(),matches.end(),sortByRating);
        else if(input==2)sort(matches.begin(),matches.end(),sortByIncreasingPrice);
        else sort(matches.begin(),matches.end(),sortByDecreasingPrice);
        for(auto currentProduct:matches){
            cout<< "Shopkeeper : " << systemAdmin.ShopKeeperid_to_name[currentProduct.shopkeeper_id] << "\n" ;
            cout << "Rating : " << currentProduct.rating << "\n" ;
            cout << "Quantity : " << currentProduct.count << "\n" ;
            cout << "Price : " << currentProduct.price << "\n" ;
            cout << "Delivery Charges : " << currentProduct.deliveryCharge << "\n" ; 
            cout << "\n" ;
        }
    }
    
    
    
};
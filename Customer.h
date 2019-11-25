#include "User.h"
#include "stringMatching.h"

//isblacklisted to be updated in admin.h

class customer:public User{
    public:
    static bool sortByRating(product product1, product product2){
        return (product1.rating > product2.rating) ;
    }

    static bool sortByIncreasingPrice(product product1, product product2){
        return (product1.price < product2.price) ;
    }

    static bool sortByDecreasingPrice(product product1, product product2){
        return (product1.price > product2.price) ;
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
        bool isFullMatchPossible=0;
        for(auto currentProduct: systemAdmin.global_inven_map){
            if(toBeSearched==currentProduct.first) {
                isFullMatchPossible=1;break;
            }
        }
        for(auto currentProduct:systemAdmin.global_inven_map){
           bool toAdd=0;
           if(isFullMatchPossible){
               if(toBeSearched==currentProduct.first) toAdd=1;
           } 
           else toAdd=isMatch(currentProduct.first,toBeSearched);
           if(toAdd){
               for(auto ids:currentProduct.second){
                   if(systemAdmin.productId_to_product[ids].count) matches.push_back(systemAdmin.productId_to_product[ids]);
               }
           }
        }
        if(response!='y'&& response!='Y');
        else if(input==1)sort(matches.begin(),matches.end(),sortByRating);
        else if(input==2)sort(matches.begin(),matches.end(),sortByIncreasingPrice);
        else sort(matches.begin(),matches.end(),sortByDecreasingPrice);
        for(auto currentProduct:matches){
            cout << "Product name : " << string(currentProduct.product_name) << "\n" ;
            cout<< "Shopkeeper : " << systemAdmin.nameFromId(currentProduct.shopkeeper_id) << "\n" ;
            cout << "Rating : " << currentProduct.rating << "\n" ;
            cout << "Quantity : " << currentProduct.count << "\n" ;
            cout << "Price : " << currentProduct.price << "\n" ;
            cout << "Delivery Charges : " << currentProduct.deliveryCharge << "\n" ; 
            cout << "\n" ;
        }
    }
};
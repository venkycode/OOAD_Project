//#include "Customer.h"
//#include "deliveryPerson.h"
#include "ShopKeeper.h"
//#include "Customer.h"

/*
int product_id;
    int product_type;
    char product_name[10];
    int deliveryCharge;
    int rating;                   //rating of the product
    char shopkeeper_id[10];
    int count,price;
*/

int main(){
    systemAdmin.loadDatabase();
    //deliverPerson d;
    //d.checkIfOrderIsAssigned();
    //d.getProductInfoFromId(2);
    //d.updateStatus();
    //cout<<d.userID<<endl;
    //return 0;
    //customer c;
    //c.checkStatus();
    shopKeeper s;
    s.addToInventory();
    s.addToInventory();
    s.displayInventory();
    s.changeCount();
    s.changePrice();
    s.displayInventory();
    s.removeFromInventory();
    s.displayInventory();
    //deliverPerson d; 
    //d.assignOrder(5);
    /*product p,q,r,s;
    char *t="aaaa", *u="aaav", *v="aaap", *w="aaao", *x="S0";
    p.product_id=0;
    strcpy(p.product_name,t);
    p.deliveryCharge=0;
    p.rating=12;
    p.count=14;
    p.price=27;
    strcpy(p.shopkeeper_id,x);
    p.product_type=0;
    q.product_id=1;
    strcpy(q.product_name,u);
    q.deliveryCharge=0;
    q.rating=22;
    q.count=14;
    q.price=20;
    strcpy(q.shopkeeper_id,x);
    q.product_type=0;
    r.product_id=2;
    strcpy(r.product_name,v);
    r.deliveryCharge=0;
    r.rating=27;
    r.count=14;
    r.price=25;
    strcpy(r.shopkeeper_id,x);
    r.product_type=0;
    s.product_id=3;
    strcpy(s.product_name,w);
    s.deliveryCharge=0;
    s.rating=2;
    s.count=14;
    s.price=34;
    strcpy(s.shopkeeper_id,x);
    s.product_type=0;
    /*systemAdmin.global_inven_map[p.product_name].insert(0);
    systemAdmin.global_inven_map[q.product_name].insert(1);
    systemAdmin.global_inven_map[r.product_name].insert(2);
    systemAdmin.global_inven_map[s.product_name].insert(3);*/
    /*systemAdmin.productId_to_product[0]=p;
    systemAdmin.productId_to_product[1]=q;
    systemAdmin.productId_to_product[2]=r;
    systemAdmin.productId_to_product[3]=s;
    //c.search();
    c.addToCart();
    c.addToCart();
    c.addToCart();
    //c.displayCart();
    //c.removeFromCart();
    //c.displayCart();
    c.cashInTheCart();
    /*c.addToWishlist();
    c.addToWishlist();
    c.addToWishlist();
    c.displayWishlist();
    c.removeFromWishlist();
    c.displayWishlist();
    c.removeFromWishlist();
    c.displayWishlist();
    c.removeFromWishlist();
    c.displayWishlist();*/

}
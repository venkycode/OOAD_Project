#include "User.h"
#include "stringMatching.h"

//isblacklisted to be updated in admin.h

class customer : public User
{
public:
    vector<pair<product, int>> cart;
    customer(profile userProfile)
    {
        name = userProfile.name;
        surname = userProfile.surname;
        emailID = userProfile.email;
        contact = userProfile.contact;
        username = userProfile.username;
        password = userProfile.password;
        userID = userProfile.id;
        address = userProfile.address;
        userType = Customer;
    }

    static bool sortByRating(product product1, product product2)
    {
        return (product1.rating > product2.rating);
    }

    static bool sortByIncreasingPrice(product product1, product product2)
    {
        return (product1.price < product2.price);
    }

    static bool sortByDecreasingPrice(product product1, product product2)
    {
        return (product1.price > product2.price);
    }

    void search()
    {
        printHeader();
        cout << endl;
        cout << printtabs(8);
        cout << fggreen;
        cout << "Enter the product you want to look-up";
        PRINTBLUE;
        cout << " ";
        cout << fggreen;
        string toBeSearched;
        cin >> toBeSearched;
        cout << endl;
        cout << fggreen << printtabs(8) << "     ";
        cout << "Do you want a filter for your search results? Y/n"
             << endl;
        printInputField();
        char response;
        cin >> response;
        int input;
        if (response == 'y' || response == 'Y')
        {
            cout << fgblue << printtabs(8) << "    ";
            cout << "Choose your filter of products"
                 << endl;
            cout << endl;
            printOption(8, 0, "Decreasing order of rating", 1);
            printOption(8, 0, "Increasing order of Price ", 2);
            printOption(8, 0, "Decrasing order of Price ", 3);
            printInputField();
            cin >> input;
        }
        vector<product> matches;
        bool isFullMatchPossible = 0;
        for (auto currentProduct : systemAdmin.global_inven_map)
        {
            if (toBeSearched == currentProduct.first)
            {
                isFullMatchPossible = 1;
                break;
            }
        }
        for (auto currentProduct : systemAdmin.global_inven_map)
        {
            bool toAdd = 0;
            if (isFullMatchPossible)
            {
                if (toBeSearched == currentProduct.first)
                    toAdd = 1;
            }
            else
                toAdd = isMatch(currentProduct.first, toBeSearched);
            if (toAdd)
            {
                for (auto ids : currentProduct.second)
                {
                    if (systemAdmin.productId_to_product[ids].count)
                        matches.push_back(systemAdmin.productId_to_product[ids]);
                }
            }
        }
        if (response != 'y' && response != 'Y')
            ;
        else if (input == 1)
            sort(matches.begin(), matches.end(), sortByRating);
        else if (input == 2)
            sort(matches.begin(), matches.end(), sortByIncreasingPrice);
        else
            sort(matches.begin(), matches.end(), sortByDecreasingPrice);

        int productMatchCounter = 1;
        printHeader();
        cout << printtabs(8);
        printLine(40);
        for (auto currentProduct : matches)
        {
            cout << fggreen << printtabs(8) << "PRODUCT NUMBER :" << fgred << productMatchCounter++;
            cout << endl;
            cout << fggreen << printtabs(8) << "Product name : " << fgblue << string(currentProduct.product_name) << "\n";
            cout << fggreen << printtabs(8) << "Product ID : " << fgblue << currentProduct.product_id << "\n";
            cout << fggreen << printtabs(8) << "Shopkeeper : " << fgblue << systemAdmin.nameFromId(currentProduct.shopkeeper_id) << "\n";
            cout << fggreen << printtabs(8) << "Rating : " << currentProduct.rating << "\n";
            cout << fggreen << printtabs(8) << "Quantity : " << currentProduct.count << "\n";
            cout << fggreen << printtabs(8) << "Price : " << currentProduct.price << "\n";
            cout << fggreen << printtabs(8) << "Delivery Charges : " << currentProduct.deliveryCharge << "\n";
            cout << fggreen << printtabs(8);
            cout << fgred;
            printLine(40);
        }
        if (matches.size())
        {
            int optionselected = -1;
            while (optionselected != 3)
            {

                printOption(8, 0, "Add to Cart", 1);
                printOption(8, 0, "Add to Wishlist", 2);
                printOption(8, 0, "Go back to Dashboard", 3);
                printInputField();

                cin >> optionselected;
                if (optionselected == 1)
                    addToCart();
                else if (optionselected == 2)
                    addToWishlist();
                else if (optionselected = 3)
                    ;
            }
        }
        else
        {
            delayBy(1);
            cout << endl;
            cout << endl;
            cout << endl;
            cout << printtabs(8) << fgred;
            cout << "NO PRODUCTS FOUND !!!" << endl;
            delayBy(2);
        }
    }

    void displayTopRatedProducts()
    {
        vector<pair<int, int>> ratings;
        for (auto y : systemAdmin.productId_to_product)
            ratings.push_back({y.second.rating, y.first});
        sort(ratings.begin(), ratings.end());
        reverse(ratings.begin(), ratings.end());
        int cnt = 0;
        printHeader();
        printLine(40);
        for (auto y : ratings)
        {
            product currentProduct = systemAdmin.productId_to_product[y.second];
            if (currentProduct.count == 0)
                continue;
            cnt++;
            cout << fggreen << printtabs(8) << "PRODUCT NUMBER :" << fgred << cnt;
            cout << endl;
            cout << fggreen << printtabs(8) << "Product name : " << fgblue << string(currentProduct.product_name) << "\n";
            cout << fggreen << printtabs(8) << "Product ID : " << fgblue << currentProduct.product_id << "\n";
            cout << fggreen << printtabs(8) << "Shopkeeper : " << fgblue << systemAdmin.nameFromId(currentProduct.shopkeeper_id) << "\n";
            cout << fggreen << printtabs(8) << "Rating : " << currentProduct.rating << "\n";
            cout << fggreen << printtabs(8) << "Quantity : " << currentProduct.count << "\n";
            cout << fggreen << printtabs(8) << "Price : " << currentProduct.price << "\n";
            cout << fggreen << printtabs(8) << "Delivery Charges : " << currentProduct.deliveryCharge << "\n";
            cout << fggreen << printtabs(8);
            cout << fgred;
            printLine(40);
            if (cnt == 5)
                break;
        }
        if (ratings.size())
        {
            int optionselected = -1;
            while (optionselected != 3)
            {

                printOption(8, 0, "Add to Cart", 1);
                printOption(8, 0, "Add to Wishlist", 2);
                printOption(8, 0, "Go back to Dashboard", 3);
                printInputField();

                cin >> optionselected;
                if (optionselected == 1)
                    addToCart();
                else if (optionselected == 2)
                    addToWishlist();
                else if (optionselected = 3)
                    ;
            }
        }
        else
        {
            delayBy(1);
            cout << endl;
            cout << endl;
            cout << endl;
            cout << printtabs(8) << fgred;
            cout << "NO PRODUCTS FOUND !!!" << endl;
            delayBy(2);
        }
    }

    void addToCart()
    {
        cout << printtabs(8) << fggreen << "Enter Product ID "
             << fgblue << " >> ";
        int productID;
        cin >> productID;
        cout << printtabs(8) << fggreen << "Enter Quantity"
             << fgblue << " >> ";
        int quantity;
        cin >> quantity;
        cart.push_back({systemAdmin.productId_to_product[productID], quantity});
        delayBy(1);
        deleteUnwanted(1, 9);
        delayBy(2);
        cout << fggreen << printtabs(8) << to_string(quantity) << " " << systemAdmin.productId_to_product[productID].product_name << " added to the cart !" << endl;
    }

    void removeFromCart()
    {
        cout << "Enter the ID of product you want to remove from cart"
             << "\n";
        int productID;
        cin >> productID;
        for (int i = 0; i < cart.size() - 1; ++i)
        {
            if (cart[i].first.product_id == productID)
                swap(cart[i], cart.back());
        }
        cart.pop_back();
    }

    void displayCart()
    {
        if (cart.empty())
        {
            cout << "Your cart is empty"
                 << "\n";
            return;
        }
        for (auto y : cart)
        {
            cout << "Product name : " << y.first.product_name << "\n";
            cout << "Product ID : " << y.first.product_id << "\n";
            cout << "Price : " << y.first.price << "\n";
            cout << "Delivery Charges : " << y.first.deliveryCharge << "\n";
            cout << "Quantity you have added to cart : " << y.second << "\n";
            cout << "\n";
        }
    }

    void cashInTheCart()
    {
        cout << "Choose your payment mode"
             << "\n";
        cout << "Press 1 for cash on delivery, 2 for online banking, 3 for paytm, 4 for gpay"
             << "\n";
        int response;
        cin >> response;
        enum mode paymentMode;
        if (response == 1)
            paymentMode = cashOnDelivery;
        else if (response == 2)
            paymentMode = onlineBanking;
        else if (response == 3)
            paymentMode = Paytm;
        else if (response == 4)
            paymentMode = GooglePay;
        else
            cout << "Invalid banking option" << endl;
        set<int> toBeRemoved;
        for (int i = 0; i < cart.size(); ++i)
        {
            auto y = cart[i];
            int availableQuantity = systemAdmin.productId_to_product[y.first.product_id].count;
            if (y.second > availableQuantity)
            {
                cout << "Only " << availableQuantity << "are available"
                     << "\n";
                cout << "Product Name : " << y.first.product_name << "\n";
                cout << "Product ID : " << y.first.product_id << "\n";
                cout << "Press 1 if you want to remove this from cart"
                     << "\n";
                cout << "Press 2 if you want to order the available quantity"
                     << "\n";
                int response;
                cin >> response;
                if (response == 1)
                    toBeRemoved.insert(y.first.product_id);
                else
                    cart[i].second = availableQuantity;
            }
        }
        for (int i = 0; i < cart.size(); ++i)
        {
            auto y = cart[i];
            if (toBeRemoved.find(y.first.product_id) == toBeRemoved.end())
                continue;
            swap(cart[i], cart.back());
            cart.pop_back();
        }

        systemAdmin.payment(cart, paymentMode, contact, userID);
        cart.clear();
    }

    void addToWishlist()
    {
        cout << fggreen << printtabs(8) << "Name of product:"
             << fgblue << " >> ";
        string productName;
        cin >> productName;
        if (systemAdmin.global_inven_map.find(productName) == systemAdmin.global_inven_map.end())
        {
            deleteUnwanted(1, 8);
            delayBy(1);
            cout << printtabs(8) << fgred << "This product is not available!!!"
                 << endl;
            return;
        }
        deleteUnwanted(1, 8);
        delayBy(1.5);
        cout << printtabs(8) << fgred << " " << productName << " added to wishlist!!" << endl;
        systemAdmin.addToWishList(userID, productName);
    }

    void displayWishlist()
    {
        set<string> tempWishlist = systemAdmin.returnWishlist(userID);
        if (tempWishlist.empty())
        {
            cout << "Your wishlist is empty"
                 << "\n";
            return;
        }
        for (auto y : tempWishlist)
            cout << y << " ";
        cout << endl;
    }

    void removeFromWishlist()
    {
        cout << "Enter the name of product you want to remove from wishlist"
             << "\n";
        string toRemove;
        cin >> toRemove;
        set<string> tempWishlist = systemAdmin.returnWishlist(userID);
        if (tempWishlist.find(toRemove) == tempWishlist.end())
        {
            cout << "This item does not belong to your wishlist"
                 << "\n";
            return;
        }
        tempWishlist.erase(tempWishlist.find(toRemove));
        systemAdmin.changeWishList(userID, tempWishlist);
    }

    void displayYourOrders()
    {
        vector<int> orders = systemAdmin.orderIdsofCustomer(userID);
        for (auto order_id : orders)
        {
            order currentOrder = systemAdmin.extactOrderInfo(to_string(order_id));
            if (currentOrder.remainingTime == "00:00:00")
                continue;
            cout << "Order ID :" << order_id << "\n";
            cout << currentOrder.order_ << "\n";
            cout << currentOrder.remainingTime << "\n";
            cout << currentOrder.other_details << "\n";
        }
    }

    void checkStatus()
    {
        cout << "Enter the ID of order you want to check for status"
             << "\n";
        int orderID;
        cin >> orderID;
        cout << "time left : " << systemAdmin.get_orderStatus(to_string(orderID));
    }
};
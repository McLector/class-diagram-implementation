#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

class Shopping
{
public:
    string productName[3], productID[3];
    int total = 0, qty[3] = {0};

    void displayCart()
    {
        if (total == 0) {
            cout << "Your cart is empty.\n";
            return;
        }
        cout << "\nProduct ID" << setw(15) << "Name" << setw(15) << "Price" << setw(15) << "Qty" << endl;
        for (int i = 0; i < 3; i++) {
            if (qty[i] > 0) {
                cout << "  " << productID[i] << setw(15) << productName[i] << setw(15) << (total / qty[i]) << setw(15) << qty[i] << endl; 
            }
        }
    }
};

class Order {
public:
    static int orderCount;
    int orderID;
    int totalAmount;
    vector<pair<string, pair<int, int>>> orderDetails;  // To store Product ID, Price, and Quantity

    Order(int total, vector<pair<string, pair<int, int>>> details)
    {
        orderID = ++orderCount;
        totalAmount = total;
        orderDetails = details;
    }

    void displayOrder() {
        cout << "Order ID: " << orderID << "\nTotal Amount: " << totalAmount << "\nOrder Details:\n";
        cout << "Product ID" << setw(15) << "Price" << setw(15) << "Qty" << endl;
        for (auto& detail : orderDetails) {
            cout << "  " << detail.first << setw(15) << detail.second.first << setw(15) << detail.second.second << endl;
        }
        cout << endl;
    }
};

int Order::orderCount = 0;  // Initialize static order counter

Shopping cart;
vector<Order> orders;  // List of all orders

class Product
{
private:
    char choice;

public:
    string productName[3], productDetails[3], productStatus[3], productID[3];
    int price[3], qty[3] = {0};

    void shopDisplay()
    {
        cout << "                     Canmore Online Potion Shop                        "
            << "\nWelcome dear customer!" << endl;
        cout << "1 - View Product List" << endl
            << "2 - View Shopping Cart" << endl
            << "3 - View Orders" << endl
            << "4 - Exit" << endl;
    };

    void addProduct()
    {
        string ID;

        while (true)
        {
            cout << "\nEnter ID to add product to cart: ";
            cin >> ID;

            if (ID == "109688")
            {
                cout << "\n     -Product Details-"
                    << "\nProduct Name: " << productName[0]
                    << "\nDetails: " << productDetails[0]
                    << "\nProduct ID: " << productID[0]
                    << "\nPrice: " << price[0] << endl;

                cout << "\nEnter quantity: ";
                cin >> qty[0];

                cart.productName[0] = productName[0];
                cart.productID[0] = productID[0];
                cart.qty[0] += qty[0];
                cart.total += price[0] * qty[0];

                cout << "\nProduct added successfully!" << endl;
                break;
            }
            else if (ID == "109689")
            {
                cout << "\n     -Product Details-"
                    << "\nProduct Name: " << productName[1]
                    << "\nDetails: " << productDetails[1]
                    << "\nProduct ID: " << productID[1]
                    << "\nPrice: " << price[1] << endl;

                cout << "\nThis product is out of stock. Please come back another time." << endl;
                break;
            }
            else if (ID == "109690")
            {
                cout << "\n     -Product Details-"
                    << "\nProduct Name: " << productName[2]
                    << "\nDetails: " << productDetails[2]
                    << "\nProduct ID: " << productID[2]
                    << "\nPrice: " << price[2] << endl;

                cout << "\nEnter quantity: ";
                cin >> qty[2];

                cart.productName[2] = productName[2];
                cart.productID[2] = productID[2];
                cart.qty[2] += qty[2];
                cart.total += price[2] * qty[2];

                cout << "\nProduct added successfully!" << endl;
                break;
            }
            else
            {
                cout << "\nPlease enter a valid product ID from the list." << endl;
                continue;
            }
        };
    }
};

int main()
{
    int navigate;
    char choice;
    int l = 0;

    // Shop Contents
    Product canmore;
    canmore.productName[0] = "Poison Potion";
    canmore.productDetails[0] = "Poisons whoever drinks or thrown this on.";
    canmore.productStatus[0] = "Available";
    canmore.price[0] = 500;
    canmore.productID[0] = "109688";

    canmore.productName[1] = "Healing Potion";
    canmore.productDetails[1] = "Heals and eliminates pain in wound.";
    canmore.productStatus[1] = "Out of Stock";
    canmore.price[1] = 800;
    canmore.productID[1] = "109689";

    canmore.productName[2] = "Energy Potion";
    canmore.productDetails[2] = "Puts you in adrenaline state.";
    canmore.productStatus[2] = "Available";
    canmore.price[2] = 700;
    canmore.productID[2] = "109690";

    do
    {
        canmore.shopDisplay();
        cout << "Enter Option: ";
        cin >> navigate;

        switch (navigate)
        {
        case 1:
            system("cls");
            cout << "\nProduct ID" << setw(15) << "Name" << setw(15) << "Price" << setw(15) << "Status" << endl;

            for (int i = 0; i < 3; i++)
            {
                cout << "  " << canmore.productID[i] << setw(23) << canmore.productName[i] << setw(8) << canmore.price[i]
                    << setw(17) << canmore.productStatus[i] << endl;
            }

            while (true)
            {
                canmore.addProduct();

                cout << "\nAdd more products? [Y/N]: ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y')
                {
                    continue;
                }
                else if (choice == 'N' || choice == 'n')
                {
                    system("cls");
                    break;
                }
                else
                {
                    cout << "\nInvalid input. Please enter a valid choice.";
                    continue;
                }
            }
            break;

        case 2:
            cart.displayCart();  // Display the shopping cart with proper qty and price
            cout << "Checkout? [Y/N]: ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                if (cart.total > 0) {
                    // Create an order and add to order list
                    vector<pair<string, pair<int, int>>> orderDetails;
                    for (int i = 0; i < 3; i++) {
                        if (cart.qty[i] > 0) {
                            orderDetails.push_back(make_pair(cart.productID[i], make_pair((cart.total / cart.qty[i]), cart.qty[i])));  // Correct price and qty
                        }
                    }
                    orders.push_back(Order(cart.total, orderDetails));

                    cout << "\nTotal Amount: " << cart.total;
                    cout << "\nYou have successfully checked out the products!" << endl;

                    // Clear the cart after checkout
                    cart.total = 0;
                    for (int i = 0; i < 3; i++) {
                        cart.qty[i] = 0;
                    }

                    // Simulate delay
                    for (int i = 5; i > 0; --i)
                    {
                        cout << i << " seconds remaining...\n";
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                    system("cls");
                } else {
                    cout << "Cart is empty, nothing to checkout.\n";
                }
            }
            else if (choice == 'N' || choice == 'n')
            {
                system("cls");
                break;
            }
            else
            {
                cout << "\nInvalid input. Please enter a valid choice.";
                continue;
            }
            break;

        case 3:
            if (orders.empty()) {
                cout << "No orders placed yet.\n";
            } else {
                for (Order& order : orders) {
                    order.displayOrder();
                }
            }
            break;

        case 4:
            exit(0);

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    } while (l < 1);

    return 0;
}

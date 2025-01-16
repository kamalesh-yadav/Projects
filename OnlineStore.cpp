#include <iostream>
#include<bits/stdc++.h>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <ctime>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Product
{
    int ProductId;
    string name;
    string category;
};

struct Order
{
    int OrderId;
    int ProductId;
    int quantity;
    string customerID;
    time_t orderDate;
};
int main()
{
    vector<Product> products = {
        {101, "Laptop", "Electronic"},
        {102, "Smartphone", "Electronic"},
        {103, "Coffe Maker", "Kitchen"},
        {104, "Blender", "Kitchen"},
        {105, "Desk lamp", "Home"},

    };

    deque<string> recentCustomers = {"C001", "C002", "C003"};
    recentCustomers.push_back("C004");
    recentCustomers.push_front("C005");

    list<Order> Orderhistory;
    Orderhistory.push_back({1, 101, 1, "C001", time(0)});
    Orderhistory.push_back({2, 102, 2, "C002", time(0)});
    Orderhistory.push_back({3, 103, 1, "C003", time(0)});

    set<string> catagories;
    for (const auto &Product : products)
    {
        catagories.insert(Product.category);
    }

    map<int, int> ProductStock = {
        {101, 10},
        {102, 18},
        {103, 15},
        {104, 16},
        {105, 7},
    };

    multimap<string, Order> CustomerOrders;
    for (const auto &Order : Orderhistory)
    {
        CustomerOrders.insert({Order.customerID, Order});
    }

    unordered_map<string, string> customerData = {
        {"C001", "SWATI"},
        {"C002", "MEGHLA"},
        {"C003", "VIPIN"},
        {"C004", "MAX"},
        {"C004", "HARRY"},
    };

    unordered_set<int> uniqueProductIDs;
    for (const auto &Product : products)
    {
        uniqueProductIDs.insert(Product.ProductId);
    }
    // print all data
    cout << "products" << endl;
    for (const auto &Product : products)
    {
        cout << Product.ProductId << " - " << Product.name << " - " << Product.category<<"-";
    }
    cout << endl
         << "customer " << endl;
    for (const auto &customer : recentCustomers)
    {
        cout << customer << endl;
    }

    cout << "Order History " << endl;
    for (const auto &Order : Orderhistory)
    {
        cout << "Order ID " << Order.OrderId << ",ProductId " << Order.ProductId
             << ",Quantity " << Order.quantity << ",Customer ID " << Order.customerID
             << ", Time " << Order.orderDate << endl;
    }

    cout<<"Catagories "<<endl;
    for(const auto &catagory:catagories)
    {
        cout<<catagory<<endl;
    }
    cout<<"Product stock "<<endl;
    for(const auto &Order:ProductStock)
    {
        cout<<"Product ID "<<Order.first<<endl;
        cout<<" stock "<<Order.second<<endl;

    }
    cout<<endl<<"customer orders "<<endl;
    for(const auto& Order:CustomerOrders)
    {
        cout << "CustomerID "<< Order.first<<endl;
    }

    cout<<"customer data "<<endl;
    for(const auto &data:customerData)
    {
        cout<<data.first<<"-"<<data.second<<endl;

    }
    cout<<"unique product ids "<<endl;
    for(const auto &id:uniqueProductIDs)
    {
        cout<<id<<" ";
    }

    return 0;
}
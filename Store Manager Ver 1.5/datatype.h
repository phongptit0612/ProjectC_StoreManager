//khai bao struct + import thu vien
#include <stdbool.h>
#include <string.h>

//struct Date{
//	int month, day, year;
//};
struct Category{
	char CategoryId[10];
	char CategoryName[20];
};
struct Product{
	char productId[10];
	char productName[20];
	int quantity;
	int price;
};
//struct Order{
//	char orderId[10];
//	char customerId[20];
//	struct Date date;
//	struct Product product;
//};


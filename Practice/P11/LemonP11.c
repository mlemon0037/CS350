#include <stdio.h>

typedef struct
{
	char* ing_name;
	double amount;
	char* measure_type;
} ingredient;

typedef struct 
{
	char* recipe_name;
	ingredient* cart;
} recipe;

int main(){
	

	ingredient beans = { "Beans", 1, "Pounds" };
	ingredient beef = { "Beef", 2, "Oz." };
	ingredient tomatoes = { "Tomatoes", 5, "Grams" };

	recipe chili = {"Chili"};
	ingredient temp_cart[3] = {beans, beef, tomatoes};
	chili.cart = temp_cart;


	printf(chili.recipe_name);
	puts(": \n");
	for (int i = 0; i < 3; i++){
		ingredient item = chili.cart[i];
		printf("%.1f %s of %s\n", item.amount, item.measure_type, item.ing_name);
	}

}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

struct Dictionary
{
	int key;
	int val;
	struct Dictionary* next;
	struct Dictionary* prev;
};
struct Dictionary* Head = NULL;
struct Dictionary* Tail = NULL;

//Insert values into the dictionary: key and val
void add(int key, int val)
{
	struct Dictionary* currentItem;
	currentItem = (struct Dictionary*)malloc(sizeof(struct Dictionary));
	if (currentItem == NULL)
	{
		printf("ERROR - Not enough memory");
		return;
	}
	else
	{
		//If you enter the same key it will change its value to the new value you entered
		struct Dictionary* changeKey = Head;
		while (changeKey != NULL)
		{
			if (changeKey->key == key)
			{
				changeKey->val = val;
				return;
			}

			changeKey = changeKey->next;
		}


		currentItem->key = key;
		currentItem->val = val;

		if (Head == NULL)
		{
			Head = currentItem;
			Tail = currentItem;
			currentItem->next = NULL;
			currentItem->prev = NULL;
		}
		else
		{
			currentItem->prev = Tail;
			currentItem->next = NULL;
			Tail->next = currentItem;
			Tail = currentItem;
		}
	}
}

//Search a key in the dictionary
struct Dictionary* search(int key)
{
	struct Dictionary* currentItem = Head;
	struct Dictionary* ret = NULL;

	while (currentItem != NULL)
	{
		if (currentItem->key == key)
		{
			ret = currentItem;
			return ret;
		}

		currentItem = currentItem->next;
	}

	//If there is no such key in the dictionary return NULL 
	printf("There is no such key in the dictionary\n");
	return NULL;
}

//Remove item from the dictionary
void removeFromDictionary(int key)
{
	struct Dictionary* currentItem = search(key);

	if (!currentItem) //If there is no such key->cuurentItem==NULL and return
	{
		currentItem = NULL;
		return;
	}
	else if (currentItem == Head && currentItem == Tail)
	{
		free(currentItem);
		Head = NULL;
		Tail = NULL;
		return;
	}
	else if (currentItem == Tail)
	{
		Tail->prev->next = NULL;
		Tail = Tail->prev;
		free(currentItem);
		return;
	}
	else if (currentItem == Head)
	{
		Head->next->prev = NULL;
		Head = Head->next;
		free(currentItem);
		return;
	}
	else
	{
		currentItem->prev->next = currentItem->next;
		currentItem->next->prev = currentItem->prev;
		free(currentItem);
		return;
	}
}

//Print the dictionary linked list
void printList()
{
	struct Dictionary* currentItem = Head;

	printf("The list of the dictionary:\n");
	while (currentItem != NULL)
	{
		printf("Key: %d Value: %d\n", currentItem->key, currentItem->val);
		currentItem = currentItem->next;
	}
}

//Free the list 
void freeList()
{
	struct Dictionary* currentItem = Head;
	struct Dictionary* releaseItem;

	while (currentItem != NULL)
	{
		releaseItem = currentItem;
		currentItem = currentItem->next;
		free(releaseItem);
	}
}


int main()
{
	int num1, num2, num3;
	struct Dictionary* valueFound;

	char userResponse = NULL;
	while (userResponse != 'E')
	{
		printf("\nPlease choose one of the following options:\n1-Insert a new value into the dictionary: key and value\n2-Search a key\n3-Print the values you entered in the dictionary\n4-Remove from dictionary\n'E'-Exit the program\n");
		userResponse = getch();
		switch (userResponse)
		{
		case '1': //Insert items to the dictionary linked list
			printf("Please enter key and value: ");
			scanf("%d %d", &num1, &num2);
			add(num1, num2);
			break;
		case '2': //Search a key and return value
			printf("Please enter the key you are looking for: ");
			scanf("%d", &num3);
			valueFound = search(num3);

			if (valueFound == NULL) //If there is no such key in the dictionary break
			{
				break;
			}

			printf("The value of this key is: %d\n", valueFound->val);
			break;
		case '3':
			printList(); //Print the dictionary linked list
			break;
		case '4': //Remove a key from the dictionary
			printf("Please enter the key you want to remove: ");
			scanf("%d", &num3);
			removeFromDictionary(num3);
			break;
		case 'E': //Exit the program
			printf("Thank you for using our program.\n");
			break;

		default:
			printf("Wrong selection, please try again\n");
			break;
		}
	}


	freeList(); //Free the dictionary linked list
	
	return 0;
}
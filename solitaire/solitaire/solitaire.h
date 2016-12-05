#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class topnode {													// doubly list
	char color[6];
	char suit[6];
	char symbol[6];
	char turned[6];
	topnode *next;
	topnode *prev;
	topnode *bottom;
	topnode *headtop;
	topnode() { *headtop = NULL; }										//global headtop

	void addtopnode(char *color, char *tip, char *value, char *down);

};
class boardnode {												//multilist
	char color[6];
	char suit[6];
	char symbol[6];
	char turned[6];
	char list[6];
	int listnumber;
	boardnode *next;
	boardnode *bottom;
	boardnode *headboard = NULL;								//global headboard
};
class foundationnode {											//multilist
	char color[6];
	char suit[6];
	char symbol[6];
	char turned[6];
	char suits[10];
	foundationnode *next;
	foundationnode *bottom;
	foundationnode *headfoundation = NULL;						//global headfoundation
};
int countfoundation = 0;												//global counter(number of cards at foundationlist)

void addboardnode(char *color, char *tip, char *value, char *down, int order);
void addheaderboardnode(int i);
void addheaderfoundationnode(char *tip);
void listtopnode();
void listboardnode();
void listfoundationnode();
void fromFile();
bool topToFoundation(char *, char *, char *);
bool addfoundationnode(topnode *add);
bool addboardnode2(topnode *add, int d);
bool topToBoard(char *a, char *b, char *c, int d);
bool boardToBoard(char *a, char *b, char *c, int d, int e);
bool addboardtoboard(boardnode *add, int e);
bool boardToFoundation(int d);
void deleteall();

int main()
{
	char club=5,meong=3;
	cout<<club<<meong<<club<<endl;
	fromFile();
	char a[2], b[2], c[2];
	int column, column2;
	char choice;
	do{
		cout << endl << "Choose an operation:" << endl;
		cout << "	1.Select from Top List to Foundation Lists" << endl;
		cout << "	2.Select from Top List to Board Lists" << endl;
		cout << "	3.Move on the Board List" << endl;
		cout << "	4.Move from Board List to Foundation List" << endl;
		cout << "	Please enter your choice(1, 2, 3, or 4):"; cin >> choice;
		switch (choice)
		{
		case '1':
			cout << "	Select a card from top list :"; scanf("%s %s %s", &a, &b, &c);
			if (topToFoundation(a, b, c) == false)
			{
				cout << "	wrong movement" << endl;
				cout << "**********************************" << endl;
				listtopnode();
				listboardnode();
				listfoundationnode();

				break;
			}
			listtopnode();
			listboardnode();
			listfoundationnode();

			break;
		case '2':
			cout << "	Select a card from top list :"; scanf("%s %s %s", &a, &b, &c);
			cout << "	Select the number of Destination Board List :"; cin >> column;
			if (topToBoard(a, b, c, column) == false)
			{
				cout << "	wrong movement" << endl;
				cout << "**********************************" << endl;
				listtopnode();
				listboardnode();
				listfoundationnode();

				break;
			}
			listtopnode();
			listboardnode();
			listfoundationnode();

			break;
		case '3':
			cout << "	Select the number of source Board List :"; cin >> column;
			cout << "	Select the number of destination Board List :"; cin >> column2;
			cout << "	Select a card from source Board List :"; scanf("%s %s %s", &a, &b, &c);

			if (boardToBoard(a, b, c, column, column2) == false)
			{
				cout << "	wrong movement" << endl;
				cout << "**********************************" << endl;
				listtopnode();
				listboardnode();
				listfoundationnode();

				break;
			}
			listtopnode();
			listboardnode();
			listfoundationnode();
			//meongg
			break;
		case '4':
			cout << "	Select the number of source Board List :"; cin >> column;
			if (boardToFoundation(column) == false)
			{
				cout << "	wrong movement" << endl;
				cout << "**********************************" << endl;
				listtopnode();
				listboardnode();
				listfoundationnode();

				break;
		default:
			cout << "Choose beetween 1-4!" << endl;
			}
			listtopnode();
			listboardnode();
			listfoundationnode();

			break;

		}
	} while (countfoundation != 52);								//congrats when foundation node has 52 cards

	cout << "     .-~~-." << endl;
	cout << "    {      }" << endl;
	cout << " .-~-.    .-~-." << endl;
	cout << "{              }" << endl;
	cout << " `.__.'||`.__.'" << endl;
	cout << "       ||" << endl;
	cout << "      '--`" << endl;
    cout << "CONGRATS YOU WON!" << endl;
	cin >> column;
	deleteall();								// deallocate memory
	return 0;


}

void addtopnode(char *color, char *tip, char *value, char *down)			//add function to doubly list
{
	topnode *temp = new topnode;
	strcpy(temp->color, color);
	strcpy(temp->suit, tip);
	strcpy(temp->symbol, value);
	strcpy(temp->turned, down);
	temp->next = NULL;
	temp->prev = NULL;
	temp->bottom = NULL;
	if (headtop == NULL)
	{
		headtop = temp;
		return;
	}
	topnode *traverse = headtop;
	while (traverse->next != NULL)
		traverse = traverse->next;
	traverse->next = temp;
	temp->prev = traverse;
}

bool addfoundationnode(topnode *add)				// top to foundation add
{
	char value[6];
	int say = 1;
	if (strcmp(add->symbol, "A") == 0)					// converts sysbols to number in order to easy check
		strcpy(value, "1");
	else if (strcmp(add->symbol, "J") == 0)
		strcpy(value, "11");
	else if (strcmp(add->symbol, "Q") == 0)
		strcpy(value, "12");
	else if (strcmp(add->symbol, "K") == 0)
		strcpy(value, "13");
	else
		strcpy(value, add->symbol);
	int below = atoi(value);
	int sagailerle;

	if (strcmp(add->suit, "S") == 0)
		sagailerle = 1;
	else if (strcmp(add->suit, "H") == 0)
		sagailerle = 2;
	else if (strcmp(add->suit, "D") == 0)
		sagailerle = 3;
	else if (strcmp(add->suit, "C") == 0)
		sagailerle = 4;

	foundationnode *traverse = headfoundation;							//finds list

	for (int i = 1; i < sagailerle; i++)
		traverse = traverse->next;

	foundationnode *traversedown = traverse;

	while (traversedown->bottom != NULL)
	{
		traversedown = traversedown->bottom;
		say++;
	}
	if (say != below) return false;								//if card number isnt equal with row order return false

	foundationnode *temp = new foundationnode;							//add last node
	strcpy(temp->suit, add->suit);
	strcpy(temp->color, add->color);
	strcpy(temp->symbol, add->symbol);
	temp->next = NULL;
	temp->bottom = NULL;
	traversedown->bottom = temp;
	return true;
}
bool addfoundationnode2(boardnode *add)				// BOARD to foundation add
{
	char value[6];
	int say = 1;
	if (strcmp(add->symbol, "A") == 0)					// converts sysbols to number in order to easy check
		strcpy(value, "1");
	else if (strcmp(add->symbol, "J") == 0)
		strcpy(value, "11");
	else if (strcmp(add->symbol, "Q") == 0)
		strcpy(value, "12");
	else if (strcmp(add->symbol, "K") == 0)
		strcpy(value, "13");
	else
		strcpy(value, add->symbol);
	int below = atoi(value);
	int sagailerle;

	if (strcmp(add->suit, "S") == 0)							//in order to track list
		sagailerle = 1;
	else if (strcmp(add->suit, "H") == 0)
		sagailerle = 2;
	else if (strcmp(add->suit, "D") == 0)
		sagailerle = 3;
	else if (strcmp(add->suit, "C") == 0)
		sagailerle = 4;

	foundationnode *traverse = headfoundation;

	for (int i = 1; i < sagailerle; i++)						//find list
		traverse = traverse->next;

	foundationnode *traversedown = traverse;

	while (traversedown->bottom != NULL)
	{
		traversedown = traversedown->bottom;
		say++;
	}
	if (say != below) return false;						//if card number isnt equal with row order return false

	foundationnode *temp = new foundationnode;					//add last node
	strcpy(temp->suit, add->suit);
	strcpy(temp->color, add->color);
	strcpy(temp->symbol, add->symbol);
	temp->next = NULL;
	temp->bottom = NULL;
	traversedown->bottom = temp;
	return true;
}
bool addboardnode2(topnode *add, int d)            // top to board add
{
	char value[6];
	char value2[6];
	int say = 1;
	if (strcmp(add->symbol, "A") == 0)
		strcpy(value, "1");
	else if (strcmp(add->symbol, "J") == 0)
		strcpy(value, "11");
	else if (strcmp(add->symbol, "Q") == 0)
		strcpy(value, "12");
	else if (strcmp(add->symbol, "K") == 0)
		strcpy(value, "13");
	else
		strcpy(value, add->symbol);
	int addvaluei = atoi(value);

	boardnode *traverse = headboard;

	for (int i = 1; i < d; i++)										//find list
		traverse = traverse->next;

	boardnode *traversedown = traverse;
	while (traversedown->bottom != NULL)							//find last node
		traversedown = traversedown->bottom;
	if (strcmp(traversedown->symbol, "A") == 0)
		strcpy(value2, "1");
	else if (strcmp(traversedown->symbol, "J") == 0)
		strcpy(value2, "11");
	else if (strcmp(traversedown->symbol, "Q") == 0)
		strcpy(value2, "12");
	else if (strcmp(traversedown->symbol, "K") == 0)
		strcpy(value2, "13");
	else
		strcpy(value2, traversedown->symbol);
	int kartvaluei = atoi(value2);

	if (traverse->bottom == NULL && addvaluei == 13)
	{
		boardnode *temp = new boardnode;
		strcpy(temp->suit, add->suit);
		strcpy(temp->color, add->color);
		strcpy(temp->symbol, add->symbol);
		strcpy(temp->turned, "Up");
		temp->next = NULL;
		temp->bottom = NULL;
		traverse->bottom = temp;
		return true;
	}
	else if (traverse->bottom == NULL && addvaluei != 13)		
		return false;
	

	if (!(kartvaluei == addvaluei + 1))								//card must 1 less from upper card and different color
		return false;
	
	if (!(strcmp(add->color,traversedown->color)!=0))
	{
		return false;
	}

	boardnode *temp = new boardnode;
	strcpy(temp->suit, add->suit);
	strcpy(temp->color, add->color);
	strcpy(temp->symbol, add->symbol);
	strcpy(temp->turned, "Up");
	temp->next = NULL;
	temp->bottom = NULL;
	traversedown->bottom = temp;
	return true;


}
bool addboardtoboard(boardnode *add, int e)
{
	char value[6];
	char value2[6];
	int say = 1;
	if (strcmp(add->symbol, "A") == 0)							// converts sysbols to number in order to easy check
		strcpy(value, "1");
	else if (strcmp(add->symbol, "J") == 0)
		strcpy(value, "11");
	else if (strcmp(add->symbol, "Q") == 0)
		strcpy(value, "12");
	else if (strcmp(add->symbol, "K") == 0)
		strcpy(value, "13");
	else
		strcpy(value, add->symbol);
	int addvaluei = atoi(value);

	boardnode *traverse = headboard;

	for (int i = 1; i < e; i++)										//finds the list
		traverse = traverse->next;

	boardnode *traversedown = traverse;
	while (traversedown->bottom != NULL)							//finds the card
		traversedown = traversedown->bottom;

	if (traverse->bottom == NULL && addvaluei == 13)			//if list is empty you can add King
	{
		boardnode *temp = new boardnode;
		strcpy(temp->suit, add->suit);
		strcpy(temp->color, add->color);
		strcpy(temp->symbol, add->symbol);
		strcpy(temp->turned, "Up");
		temp->next = NULL;
		temp->bottom = add->bottom;
		traversedown->bottom = temp;
		return true;
	}
	else if (traverse->bottom == NULL && addvaluei != 13)			//yeni addndi.  if list is empty you cannot add other than king 
		return false;

	if (strcmp(traversedown->symbol, "A") == 0)							// converts sysbols to number in order to easy check
		strcpy(value2, "1");
	else if (strcmp(traversedown->symbol, "J") == 0)
		strcpy(value2, "11");
	else if (strcmp(traversedown->symbol, "Q") == 0)
		strcpy(value2, "12");
	else if (strcmp(traversedown->symbol, "K") == 0)
		strcpy(value2, "13");
	else
		strcpy(value2, traversedown->symbol);						
	int kartvaluei = atoi(value2);

	if (!(kartvaluei == addvaluei + 1))								//card must 1 less from upper card and different color
		return false;

	if (!(strcmp(add->color, traversedown->color) != 0))
	{
		return false;
	}

	boardnode *temp = new boardnode;						//add last node
	strcpy(temp->suit, add->suit);
	strcpy(temp->color, add->color);
	strcpy(temp->symbol, add->symbol);
	strcpy(temp->turned, "Up");
	temp->next = NULL;
	temp->bottom = add->bottom;
	traversedown->bottom = temp;
	return true;


}

void addboardnode(char *color, char *tip, char *value, char *down, int order)	 //file to board multilist
{
	boardnode *temp = new boardnode;
	strcpy(temp->color, color);
	strcpy(temp->suit, tip);
	strcpy(temp->symbol, value);
	strcpy(temp->turned, down);
	temp->next = NULL;
	temp->bottom = NULL;
	int goforward;
	boardnode *traverseforward = headboard;
	for (goforward = 1; goforward < order; goforward++)
		traverseforward = traverseforward->next;
	boardnode *traversedown = traverseforward;
	while (traversedown->bottom != NULL)
		traversedown = traversedown->bottom;
	traversedown->bottom = temp;
}
void addheaderboardnode(int i)
{
	boardnode *temp = new boardnode;
	temp->listnumber = i;
	strcpy(temp->list, ". list");
	temp->next = NULL;
	temp->bottom = NULL;
	if (headboard == NULL)
	{
		headboard = temp;
		return;
	}
	boardnode *traverse = headboard;
	while (traverse->next != NULL)
		traverse = traverse->next;
	traverse->next = temp;
}
void addheaderfoundationnode(char *tip)
{
	foundationnode *temp = new foundationnode;
	strcpy(temp->suits, tip);
	temp->next = NULL;
	temp->bottom = NULL;
	if (headfoundation == NULL)
	{
		headfoundation = temp;
		return;
	}
	foundationnode *traverse = headfoundation;
	while (traverse->next != NULL)
		traverse = traverse->next;
	traverse->next = temp;
}
void listtopnode()									// list top node
{
	topnode *traverse = headtop->next;
	cout << endl << "Top List" << endl;
	while (traverse->next != NULL)
	{

		cout << traverse->color << "," << traverse->suit << "," << traverse->symbol << "|";
		traverse = traverse->next;
	}
	cout << endl;
}
void listboardnode()
{
	boardnode *traverse[7];						//7 traverse pointers for 7 lists
	boardnode *assign = headboard;
	int i = 0;
	while (assign != NULL)
	{
		traverse[i] = assign->bottom;
		assign = assign->next;
		i++;
	}
	cout << endl << "Board Lists" << endl;
	cout << "1.list   2.list   3.list   4.list   5.list   6.list   7.list" << endl;
	for (int i = 1; i < 14; i++)
	{
		if (traverse[0] == NULL &&traverse[1] == NULL &&traverse[2] == NULL &&traverse[3] == NULL &&traverse[4] == NULL &&traverse[5] == NULL &&traverse[6] == NULL)
			break;
		if (traverse[0] != NULL)
		{
			if (strcmp(traverse[0]->turned, "Up") == 0)
				cout << traverse[0]->color << "," << traverse[0]->suit << "," << traverse[0]->symbol << "    ";
			else cout << "X         ";
			traverse[0] = traverse[0]->bottom;

		}
		else{ cout << "         "; }
		if (traverse[1] != NULL)
		{
			if (strcmp(traverse[1]->turned, "Up") == 0)
				cout << traverse[1]->color << "," << traverse[1]->suit << "," << traverse[1]->symbol << "    ";
			else cout << "X        ";
			traverse[1] = traverse[1]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[2] != NULL)
		{
			if (strcmp(traverse[2]->turned, "Up") == 0)
				cout << traverse[2]->color << "," << traverse[2]->suit << "," << traverse[2]->symbol << "    ";
			else cout << "X        ";
			traverse[2] = traverse[2]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[3] != NULL)
		{
			if (strcmp(traverse[3]->turned, "Up") == 0)
				cout << traverse[3]->color << "," << traverse[3]->suit << "," << traverse[3]->symbol << "    ";
			else cout << "X        ";
			traverse[3] = traverse[3]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[4] != NULL)
		{
			if (strcmp(traverse[4]->turned, "Up") == 0)
				cout << traverse[4]->color << "," << traverse[4]->suit << "," << traverse[4]->symbol << "    ";
			else cout << "X        ";
			traverse[4] = traverse[4]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[5] != NULL)
		{
			if (strcmp(traverse[5]->turned, "Up") == 0)
				cout << traverse[5]->color << "," << traverse[5]->suit << "," << traverse[5]->symbol << "    ";
			else cout << "X        ";
			traverse[5] = traverse[5]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[6] != NULL)
		{
			if (strcmp(traverse[6]->turned, "Up") == 0)
				cout << traverse[6]->color << "," << traverse[6]->suit << "," << traverse[6]->symbol;
			else cout << "X        ";
			traverse[6] = traverse[6]->bottom;
		}
		else{ cout << "         "; }
		cout << endl;

	}

}

void listfoundationnode()
{
	foundationnode *traverse[4];					//4 traverse pointers for 4 list
	foundationnode *assign = headfoundation;
	int i = 0;
	while (assign != NULL)
	{
		traverse[i] = assign->bottom;
		assign = assign->next;
		i++;
	}
	cout << endl << "Foundation Lists" << endl;
	cout << "Spades   Hearts   Diamonds  Clubs" << endl;
	for (int i = 1; i < 14; i++)
	{
		if (traverse[0] == NULL &&traverse[1] == NULL &&traverse[2] == NULL &&traverse[3] == NULL)
			break;

		if (traverse[0] != NULL)
		{
			cout << traverse[0]->color << "," << traverse[0]->suit << "," << traverse[0]->symbol << "    ";
			traverse[0] = traverse[0]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[1] != NULL)
		{
			cout << traverse[1]->color << "," << traverse[1]->suit << "," << traverse[1]->symbol << "    ";
			traverse[1] = traverse[1]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[2] != NULL)
		{
			cout << traverse[2]->color << "," << traverse[2]->suit << "," << traverse[2]->symbol << "    ";
			traverse[2] = traverse[2]->bottom;
		}
		else{ cout << "         "; }
		if (traverse[3] != NULL)
		{
			cout << traverse[3]->color << "," << traverse[3]->suit << "," << traverse[3]->symbol;
			traverse[3] = traverse[3]->bottom;
		}
		else{ cout << "         "; }
		cout << endl;
	}

}
void fromFile()
{
	char a[6], b[6], c[6], d[6], star[10];								// ex: D S A Down ****

	FILE *fptr;
	fptr = fopen("solitaire.txt", "r");
	addtopnode("A", "A", "A", "A");										//topnode head starts with A A A A but never shown in console
	for (int i = 0; i < 24; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);
		addtopnode(a, b, c, d);											//add from file to top list
	}
	addtopnode("Z", "Z", "rZ", "Z");
	fscanf(fptr, "%s", star);											//skip stars

	addheaderboardnode(1);												//boardlist starts with numbers but never shown in console
	for (int i = 0; i < 1; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//1. list from file to top list
		addboardnode(a, b, c, d, 1);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(2);
	for (int i = 0; i < 2; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//2. list from file to top list
		addboardnode(a, b, c, d, 2);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(3);
	for (int i = 0; i < 3; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//3. list from file to top list
		addboardnode(a, b, c, d, 3);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(4);
	for (int i = 0; i < 4; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//4. list from file to top list
		addboardnode(a, b, c, d, 4);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(5);
	for (int i = 0; i < 5; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//5. list from file to top list
		addboardnode(a, b, c, d, 5);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(6);
	for (int i = 0; i < 6; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//6. list from file to top list
		addboardnode(a, b, c, d, 6);
	}
	fscanf(fptr, "%s", star);

	addheaderboardnode(7);
	for (int i = 0; i < 7; i++)
	{
		fscanf(fptr, "%s %s %s %s", a, b, c, d);						//7. list from file to top list
		addboardnode(a, b, c, d, 7);
	}
	addheaderfoundationnode("Spades");									//foundations node starts with Symbols never shown in console
	addheaderfoundationnode("Hearts");
	addheaderfoundationnode("Diamonds");
	addheaderfoundationnode("Clubs");

	fclose(fptr);
	listtopnode();
	listboardnode();
	listfoundationnode();
}
bool topToFoundation(char *a, char *b, char *c)
{
	bool gonder = false;
	topnode *traverse = headtop;
	while (traverse != NULL)								//checks the card
	{
		if (strcmp(traverse->color, a) == 0 && strcmp(traverse->suit, b) == 0 && strcmp(traverse->symbol, c) == 0)
		{
			gonder = true;
			break;
		}
		traverse = traverse->next;
	}
	if (gonder == true)										// if card on the top list send
	{
		if (addfoundationnode(traverse) == false)			//if not appropriate card return false
			return false;
		traverse->prev->next = traverse->next;				//break nodes
		traverse->next->prev = traverse->prev;
		cout << "Movement Succesful !" << endl;
		cout << "***************************" << endl;
		countfoundation++;

	}
	else                                                    //if card not on the top list return false
		return false;
	return true;
}
bool topToBoard(char *a, char *b, char *c, int d)
{
	bool gonder = false;
	topnode *traverse = headtop;
	while (traverse != NULL)
	{
		if (strcmp(traverse->color, a) == 0 && strcmp(traverse->suit, b) == 0 && strcmp(traverse->symbol, c) == 0)
		{
			gonder = true;
			break;
		}
		traverse = traverse->next;
	}
	if (gonder == true)
	{
		if (addboardnode2(traverse, d) == false)
			return false;
		traverse->prev->next = traverse->next;
		traverse->next->prev = traverse->prev;
		cout << "Movement Succesful !" << endl;
		cout << "***************************" << endl;

	}
	else
		return false;
	return true;
}
bool boardToBoard(char *a, char *b, char *c, int d, int e)
{
	bool gonder = false;
	boardnode *traverse = headboard;
	boardnode *traverse2 = headboard;					//never used
	boardnode *traversebottom;
	boardnode *traversebottom2;							//never used
	boardnode *tut = headboard;
	for (int i = 1; i < d; i++)							//finds the list
		traverse = traverse->next;
	for (int i = 1; i < e; i++)
		traverse2 = traverse2->next;

	traversebottom = traverse->bottom;
	tut = traverse;							// traversin öncesini tutar
	while (traversebottom != NULL)			//finds the card and checks
	{
		if (strcmp(traversebottom->color, a) == 0 && strcmp(traversebottom->suit, b) == 0 && strcmp(traversebottom->symbol, c) == 0)
		{
			gonder = true;
			break;
		}
		traversebottom = traversebottom->bottom;
		tut = tut->bottom;
	}
	if (gonder == true)
	{
		if (addboardtoboard(traversebottom, e) == false)	//checks if appropriate card if true breaks node
			return false;
		tut->bottom = NULL;									// prev node =NULL
		strcpy(tut->turned, "Up");							// prev node =Up
		cout << "Movement Succesful !" << endl;
		cout << "***************************" << endl;
	}
	else
		return false;
	return true;
}
bool boardToFoundation(int d)
{
	bool gonder = false;
	boardnode *traverse = headboard;
	for (int i = 1; i < d; i++)						//finds column
		traverse = traverse->next;
	boardnode *traversebottom;
	traversebottom = traverse->bottom;
	boardnode *tut = traverse;
	if (traversebottom == NULL)						//if list is empty return false
		return false;
	while (traversebottom->bottom != NULL)			//finds the last card
	{
		traversebottom = traversebottom->bottom;
		tut = tut->bottom;
	}

	gonder = true;
	if (gonder == true)
	{
		if (addfoundationnode2(traversebottom) == false)	// check if appropriate card and breaks node
			return false;
		tut->bottom = NULL;									//prev node->bottom NULL
		strcpy(tut->turned, "Up");							//prev node = Up
		cout << "Movement Succesful !" << endl;
		countfoundation++;
		cout << "***************************" << endl;
	}
	else
		return false;
	return true;
}


void deleteall()
{
		foundationnode *traverse[4],*sil[4];					//4 traverse pointers for 4 list
		foundationnode *assign = headfoundation;
		int i = 0;
		while (assign != NULL)
		{
			traverse[i] = assign->bottom;
			assign = assign->next;
			i++;
		}
		for (int i = 1; i < 14; i++)
		{
			if (traverse[0] == NULL &&traverse[1] == NULL &&traverse[2] == NULL &&traverse[3] == NULL)
				break;

			if (traverse[0] != NULL)
			{
				sil[0] = traverse[0];
				traverse[0] = traverse[0]->bottom;
				delete sil[0];
			}
			if (traverse[1] != NULL)
			{
				sil[1] = traverse[1];
				traverse[1] = traverse[1]->bottom;
				delete sil[1];
			}
			if (traverse[2] != NULL)
			{
				sil[2] = traverse[2];
				traverse[2] = traverse[2]->bottom;
				delete sil[2];
			}
			if (traverse[3] != NULL)
			{
				sil[3] = traverse[3];
				traverse[3] = traverse[3]->bottom;
				delete sil[3];
			}
		}

}


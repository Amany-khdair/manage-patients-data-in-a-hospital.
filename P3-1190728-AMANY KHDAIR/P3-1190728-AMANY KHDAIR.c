//1190728-Amany khdair
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define MAX 40

typedef struct AVLtree *AVLTree;
typedef struct Hashing HashTable;
typedef struct AVLtree A_V_L;

int loadedTable = 0;//initial value for the loaded table

//for the AVL TREE functions
AVLTree RF(AVLTree);//THE METHOD THAT WILL READ FROM FILE
void LSI(AVLTree);//THE METHOD THAT WILL LIST THE SAME ILLNESS BETWEEN ALL PATIENTS
void pInorderIll(char *strL, AVLTree);//THE METHOD THAT WILL PRINT THE PATIENT ILLNESS IN ORDER
void toLower(char *strL);//THE METHOD THAT WILL MAKE ALL LETTER IN LOWER CASE  (A become a)
void InsertNewPatient(AVLTree);//THE METHOD THAT WILL LET THE USER INSERT ANOTHER PATEINT
void FindThenUpdatePatient(AVLTree);//THE METHOD THAT WILL LET THE USER UPDATE THE DATA OR THE INFORMATION ON ANY PATIENT
void SaveInfoToHashFile(AVLTree);//THE METHOD THAT WILL SAVE ALL THE DATA FROM PATIENTS.TXT TO THE HASH FILE
void POF(AVLTree, FILE*);//THE METHOD THAT WILL PRINT THE DATA ON THE FILE

//for the HASH functions
void PHF(HashTable);//THE METHOD THAT WILL PRINT THE DATA TO THE HASH FUNCTION
void PrintSizeOfTable(HashTable);//THE METHOD THAT WILL PRINT THE NUMBER OF PATIENTS OR THE SIZE OF THE TABLE
void PT(HashTable);//THE METHOD THAT WILL PRINT THE HASH TABLE
void WriteToTheFile (HashTable);//THE METHOD THAT WILL WRITE THE TABLE PRINT IT TO THE FILE
void ReadFromTheFile(HashTable *);//THE METHOD THAT WILL READ THE TABLE FROM THE FILE
int FR(HashTable table, char[]);
void DFT(HashTable);//THE METHOD THAT WILL DELETE FROM TABLE WHAT THE USER WANT
void InsertTo(HashTable *, A_V_L);//THE METHOD THAT WILL LET THE USER INSERT ANOTHER PATEINT
void rehash(HashTable *);//THE METHOD THAT WILL UPDATE TABLE SIZE
int square(HashTable, char[]);//THE METHOD THAT WILL ALSO UPDATE THE TABLE SIZE
int Hash(HashTable, char []); //THE METHOD THAT WILL get the index that will put the world OR LETTER in it,refresh the table and initialize it
int RequiredSize(int);//THE METHOD THAT WILL REQUIRED TABLE SIZE FOR THE HASH TABLE
int isPrime(int);
void InsertNewPatientToTheHash(HashTable);//this method will insert new patient information to the hash table
void SearchARecord(HashTable);//this method will search for the record via patient name

struct Hashing //every node will consist from these information
{
    int TableSize;//table size
    int NumberOfRecording;//number of records
    AVLTree R;//pointer on records
};

struct AVLtree//every node will consist from these information
{
    char name[MAX];//patient name
    char gender;//patient gender
    char DateOfAdmission[MAX];//patient admission date
    char DateOfBirth[MAX];//patient birth date
    char Illness[MAX];//patient illness
    char Address[MAX];//patient address
    char BloodType[5];//patient blood type
    AVLTree Left;//pointer on the left
    AVLTree Right;//pointer on the right
    int Height; //its a Balance information
    int Statuse;//typedef
};
//first things first we defined (make empty) for the AVL node
AVLTree MakeEmpty( AVLTree TRe )//THE METHOD THAT WILL MAKE THE AVL TREE EMPTY
{
    if( TRe != NULL )//IF THE TREE WAS NOT EMPTY THEN FREE THE MEMORY FOR ALL THE FUNCTIONS
    {
        MakeEmpty( TRe->Left );//TO LET THE LEFT SIDE OF THE TREE EMPTY(this function find out if the left side of the tree empty or not if not then send it to function make empty)
        MakeEmpty( TRe->Right );//TO LET THE RIGHT SIDE OF THE TREE EMPTY(this function find out if the right side of the tree empty or not if not then send it to function make empty)
        free( TRe );//FREE THE MEMORY
    }
    return NULL;//RETURN NULL IF THE TREE WAS NOT EMPTY
}

AVLTree FindMaximum( AVLTree TRe )//SEND THE TREE THAT WE WANT TO SEE THE MAXIMUM IN IT
{
    //WE KNOW THAT IF WE WANT TO FIND THE MAXIMUM THEN WE SHOULD SEARCH ON THE RIGHT SIDE
    if( TRe != NULL )//FIRST OF ALL THE TREE SHOULD NOT BE EMPTY SO..
        while( TRe->Right != NULL )//CHECK AGAIN IF THE RIGHT SIDE = NULL OR NUT IF NOT ..
            TRe = TRe->Right;//SEND IT TO THE FIND MAXIMUM

    return TRe;//RETURN THE LAST ROOT ENTERED
}

AVLTree FindMinimum( AVLTree TRe )//SEND THE TREE THAT WE WANT TO SEE THE MINIMUM IN IT
{
    //WE KNOW THAT IF WE WANT TO FIND THE MINIMUM THEN WE SHOULD SEARCH ON THE LEFT SIDE
    if( TRe == NULL )//IF THE TREE WAS EMPTY THEN RETURN NULL
        return NULL;
    else if( TRe->Left == NULL )//IF THE LEFT SIDE OF THE TREE IS EMPTY THEN RETURN THE LAST ROOT ENTERED
        return TRe;
    else//AND LAST THING IF IT HAD A CHILDREN ON THE LEFT SIDE THEN FIND THE MINIMUM
        return FindMinimum( TRe->Left );
}

AVLTree Find(char name[MAX], AVLTree TRe )//WE PUT HERE WHAT ARE THE INFORMATION THAT WE WOULD SEARCH IT AND HERE ALL THE INFORMATION ARE IN THE AVL TREE
{
    if( TRe == NULL )//THIS MEAN THAT IF THE COMPILER REACHES TO THE BOTTOM OF THE TREE THEN IT MEANS EMPTY AND RETURN NULL
        return NULL;
//THIS METHOD COMPARE THE VALUE THAT BEEN SEARCHED WITH THE VALUE THAT THE FUNCTION AT ITS PLACE
    if(strcmp(name, TRe->name) < 0)//IF THE ONE SEARCHED LESS THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN IT GOES TO SEARCH IN THE LEFT SIDE
        return Find( name, TRe->Left );//SEARCH IN THE LEFT SIDE
    else if(strcmp(name, TRe->name) > 0)//ELSE IF NOT OR IN OTHER WORLD IF THE ONE SEARCHED LESS THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN IT GOES TO SEARCH IN THE RIGHT SIDE
        return Find( name, TRe->Right );//SEARCH IN THE RIGHT SIDE
    else//AND IF NOT OF THE ABOVE RETURN THE CALLER
        return TRe;
}

int Height( AVLTree height )//ITS AN EXTRA INFORMATION
{
    if( height == NULL )//IF THE NEW POINTER P WAS EMPTY THEN RETURN -1
        return -1;
    else//IF P WAS NOT EMPTY THEN RETURN THE CALLER
        return height->Height;
}

int MAximum( int Le, int Ri )//THIS METHOD RETURN THE BIGGER NUMBER
{
    return Le > Ri ? Le : Ri;//IF LEFT BIGGER THAN RIGHT RETURN LEFT IF NOT RETURN RIGHT
}

AVLTree SingleRightRotate( AVLTree SR1 )//THIS METHOD WILL WORK IF SR1 HAS RIGHT SIDE THEN ROTATE THE NODE SR1 AND ITS RIGHT SIDE AND THE LAST THING UPDATE THE HEIGHTS BEFORE RETURNING THE presentTime ROOT
{
    AVLTree SR2;

    SR2 = SR1->Right;//IT WILL SEARCH IF THERE ANY RIGHT SIDE
    SR1->Right = SR2->Left;//THIS LINE AND THE NEXT LINE MEANS ROTATE THE NODE AND ITS RIGHT SIDE
    SR2->Left = SR1;
//THE NEXT LINES UPDATE THE HEIGHTS BEFORE RETURNING THE presentTime ROOT
    SR1->Height = MAximum( Height( SR1->Left ), Height( SR1->Right ) ) + 1;
    SR2->Height = MAximum( Height( SR2->Right ), SR1->Height ) + 1;

    return SR2;//AND THE LAST THING RETURN THE NEW ROOT
}

AVLTree SingleLeftRotate( AVLTree SR2 )//THIS METHOD WILL WORK IF SR2 HAS LEFT SIDE THEN ROTATE THE NODE SR2 AND ITS LEFT SIDE AND THE LAST THING UPDATE THE HEIGHTS BEFORE RETURNING THE presentTime ROOT
{
    AVLTree  SR1;

    SR1 = SR2->Left;//IT WILL SEARCH IF THERE ANY LEFT SIDE
    SR2->Left = SR1->Right;//THIS LINE AND THE NEXT LINE MEANS ROTATE THE NODE AND ITS LEFT SIDE
    SR1->Right = SR2;
//THE NEXT LINES UPDATE THE HEIGHTS BEFORE RETURNING THE presentTime ROOT
    SR2->Height = MAximum( Height( SR2->Left ), Height( SR2->Right ) ) + 1;
    SR1->Height = MAximum( Height( SR1->Left ), SR2->Height ) + 1;

    return SR1;//AND THE LAST THING RETURN THE NEW ROOT
}

AVLTree DoubleRightRotate( AVLTree SR1 )//THIS METHOD WILL WORK ONLY IF SR1 HAS A RIGHT, THE RIGHT SIDE OF SR1 HAS A LEFT SIDE THEN DO A DOUBLE ROTATION FROM RIGHT TO LEFT THEN UPDATE THE HEIGHTS BEFORE RETURNING THE presentTime ROOT
{
    // IF SR1 HAS A RIGHT SIDE ROTATE BETWEEN SR3 AND SR2
    SR1->Right = SingleLeftRotate( SR1->Right );

    //THIS FUNCTION WILL ROTATE BETWEEN SR1 AND SR2
    return SingleRightRotate( SR1 );
}
AVLTree DoubleLeftRotate( AVLTree SR3 )//THIS METHOD WILL WORK ONLY IF SR3 HAS A LEFT, THE LEFT SIDE OF SR3 HAS A RIGHT SIDE THEN DO A DOUBLE ROTATION FROM LEFT TO RIGHT THEN UPDATE THE HEIGHTS BEFORE RETURNING THE presentTime ROOT
{
    // IF SR3 HAS A LEFT SIDE ROTATE BETWEEN SR1 AND SR2
    SR3->Left = SingleRightRotate( SR3->Left );

    //THIS FUNCTION WILL ROTATE BETWEEN SR3 AND SR2
    return SingleLeftRotate( SR3 );
}

//THIS METHOD WILL INSERT THE PATIENT INFORMATION IN THE TREE
AVLTree Insert(char name[MAX], char gender, char dateOfAdmission[MAX], char dateOfBirth[MAX], char illnes[MAX], char address[MAX], char BLOOD[3], AVLTree TRe )
{
    if( TRe == NULL )
    {
        //THE FOLLOWING FUNCTION WILL CREATE AND THEN RETURN SINGLE NODE TREE
        TRe = malloc( sizeof( struct AVLtree ) );
        if( TRe == NULL )//IF IT WAS EMPTY THEN PRINT THE FOLLOWING
            printf( "sorry, not enough memory :( " );
        else
        {
            // THIS FUNCTION COPIES THE STRING POINTED BY NAME(SOURCE) TO THE (DESTINATION)
            strcpy(TRe->name, name);
            // THIS FUNCTION COPIES THE STRING POINTED BY ADMISSION DATE(SOURCE) TO THE (DESTINATION)
            strcpy(TRe->DateOfAdmission, dateOfAdmission);
            // THIS FUNCTION COPIES THE STRING POINTED BY BIRTH DATE(SOURCE) TO THE (DESTINATION)
            strcpy(TRe->DateOfBirth, dateOfBirth);
            // THIS FUNCTION COPIES THE STRING POINTED BY BLOOD TYPE(SOURCE) TO THE (DESTINATION)
            strcpy(TRe->BloodType, BLOOD);
            // THIS FUNCTION COPIES THE STRING POINTED BY ILLNESS(SOURCE) TO THE (DESTINATION)
            strcpy(TRe->Illness, illnes);
            // THIS FUNCTION COPIES THE STRING POINTED BY ADDRESS(SOURCE) TO THE (DESTINATION)
            strcpy(TRe->Address, address);
            TRe->gender = gender;
            //SET HEIGHT TO ZERO (0)
            TRe->Height = 0;
            //LET THE LEFT EQUAL THE RIGHT EQUAL NULL(EMPTY) [LEFT AND RIGHT FOR THE NEW NODE EQUAL NULL]
            TRe->Left = TRe->Right = NULL;
        }
    }
    //ELSE IF THE ONE SEARCHED LESS THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN INSERT TO THE LEFT SIDE ALL THE PATIENT INFORMATIONS
    else if( strcmp(name, TRe->name) < 0 )
    {
        //THE FOLLOWING LINE WILL LET THE PROGRAM INSERT THE INFORMATION
        TRe->Left = Insert( name, gender, dateOfAdmission, dateOfBirth, illnes, address, BLOOD, TRe->Left );
        //THE FOLLOWING FUNCTIONS WILL CHECK THE BALANCED OF THE TREE IF IT WAS EQUAL 2 AND WE KNOW THAT WRONG THEN WE MUST DO THE FOLLOWING TO SOLVE THIS PROBLEM
        if( Height( TRe->Left ) - Height( TRe->Right ) == 2 )
        {
            //IF THE ONE SEARCHED LESS THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN DO A SINGLE ROTATION WITH THE LEFT
            if( strcmp(name, TRe->name) < 0 )
                TRe = SingleLeftRotate( TRe );
            //IF THE ONE SEARCHED LESS THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN DO A DOUBLE ROTATION WITH THE LEFT
            else
                TRe = DoubleLeftRotate( TRe );
        }
    }
    //ELSE IF THE ONE SEARCHED BIGGER THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN INSERT TO THE RIGHT SIDE ALL THE PATIENT INFORMATIONS
    else if( strcmp(name, TRe->name) > 0 )
    {
//THE FOLLOWING LINE WILL LET THE PROGRAM INSERT THE INFORMATION
        TRe->Right = Insert( name, gender, dateOfAdmission, dateOfBirth, illnes, address, BLOOD, TRe->Right );
//THE FOLLOWING FUNCTIONS WILL CHECK THE BALANCED OF THE TREE IF IT WAS EQUAL 2 AND WE KNOW THAT WRONG THEN WE MUST DO THE FOLLOWING TO SOLVE THIS PROBLEM
        if( Height( TRe->Right ) - Height( TRe->Left ) == 2 )
        {
//IF THE ONE SEARCHED BIGGER THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN DO A SINGLE ROTATION WITH THE RIGHT
            if( strcmp(name, TRe->name) > 0 )
                TRe = SingleRightRotate( TRe );
//IF THE ONE SEARCHED BIGGER THAN THE ONE THAT THE COMPILER IN ITS PLACE THEN DO A DOUBLE ROTATION WITH THE RIGHT
            else
                TRe = DoubleRightRotate( TRe );
        }
    }
    //IF THE THING WE SEARCH IS ALREADY IN THE TREE THEN DONT DO ANYTHING
    TRe->Height = MAximum( Height( TRe->Left ), Height( TRe->Right ) ) + 1;
    return TRe;
}

//THIS METHOD WILL FIND THE MINIMUM LEFT MOST ROOT
AVLTree MinValue(AVLTree val)
{
    AVLTree presentTime = val;
    //THE FOLLOWING WHILE LOOP FIND THE LEFT MOST ROOT
    while (presentTime->Left != NULL)//THE CONDITION IS IF THE NODE ON THE LEFT SIDE DOES NOT EQUAL NULL OR EMPTY THEN LET IT POINT TO THE LEFT
        presentTime = presentTime->Left;

    return presentTime;
}

//THE FOLLOWINF FUNCTION IS TO GET THE HEIGHT OF THE TREE
int height(AVLTree tree)
{
    //IF IT WAS EMPTY RETURN ZERO IF NOT RETURN THE HEIGHT OF THE TREE
    if (tree == NULL)
        return 0;
    return tree->Height;
}
//WE USED HERE THE IN ORDER METHOD (THE PUBLIC METHOD)TO REORDER THE INFORMATION TO SEE THE ELEMENT
void PrintInOrder( AVLTree ORDER)
{
    //IF IT WAS NOT EMPTY THEN REORDER THE INFORMATION
    if(ORDER != NULL)
    {
        //AS THE ROLE OF THE INORDER FUNCTION ITS START SEARCHING FROM THE LEFT FOLLOWED BY THE MIDDLE OR THE ROOT THEN THE RIGHT
        //PRINT THE EXITING INFORMATIONS IN THE LEFT
        PrintInOrder( ORDER->Left );
        printf("patient: %s, %c, %s, %s, %s, %s, %s \n", ORDER->name, ORDER->gender, ORDER->DateOfAdmission, ORDER->DateOfBirth, ORDER->Address, ORDER->Illness, ORDER->BloodType);
        //PRINT THE EXITING INFORMATIONS IN THE RIGHT
        PrintInOrder( ORDER->Right );
    }
}

int maxmum(int v, int w)//THIS METHOD RETURN THE BIGGER NUMBER
{
    return (v > w)? v : w;//IF THE FIRST BIGGER THAN THE SECOND RETURN FIRST IF NOT RETURN SECOND
}

// Get Balance factor of node N
//THIS METHOD IS TO GET THE BALANCE
int isBalance(AVLTree tree)
{
    //IF THE TREE WAS EMPTY THEN RETURN NULL IF NOT RETURN THE HEIGH
    if (tree == NULL)
        return 0;
    //RETURN THE HEIGH FROM SUBTRACTION BETWEEN BOTH LEFT AND RIGHT OF THE TREE
    return height(tree->Left) - height(tree->Right);
}

// THIS METHOD DELETES A NODE WITH A GIVEN KEY FROM A SUBTREE WITH A
//GIVEN ROOT USING A RECURSIVE ALGORITHM AND FINALLY IT RETURNS THE MODIFIED SUBTREE'S ROOT.
AVLTree DeleteIt(AVLTree r, char *k)
{
    //FIRST THINGS FIRST WE PERFOMED THE BINARY SEARCH TREE (BST) DELETE FUNCTION
    if (r == NULL)
        return r;

    //THE FOLLOWING FUNCTION COMPARE THE KEY AND THE ROOTS KEY IF THE ONE TO BE DELETED IS SMALLER THAN THE OTHER THEN IT WILL BE IN THE LEFT SIDE OF THE TREE
    if ( strcmp(k, r->name) < 0)
        r->Left = DeleteIt(r->Left, k);

    //THE FOLLOWING FUNCTION COMPARE THE KEY AND THE ROOTS KEY IF THE ONE TO BE DELETED IS BIGGER THAN THE OTHER THEN IT WILL BE IN THE RIGHT SIDE OF THE TREE
    else if( strcmp(k, r->name) > 0 )
        r->Right = DeleteIt(r->Right, k);

    //IF NOT ANY OF THE ABOVE THAT MEANS THE KEY AND THE ROOTS KEY ARE BOTH EQUALS AND ITS THE NODE THAT WILL BE DELETED
    else
    {
        //IF THE NODE HAVE JUST ONE SIDE(CHILD) OR DONT HAVE ANY SIDE
        if( (r->Left == NULL) || (r->Right == NULL) )
        {
            //THE FOLLOWING LINE CHECK IF THE NODE HAVE A LEFT, IF YES THEN IT HAVE A LEFT IF NO THEN IT HAVE A RIGHT
            AVLTree TEMP = r->Left ? r->Left :r->Right;
            //THE FOLLOWING CONDITION IS ABOUT IF IT DONT HAVE ANY SIDE OR IN OTHER WORLD CHILD
            if (TEMP == NULL)
            {
                TEMP = r;
                r = NULL;
            }
            //THE FOLLOWING CONDITION IS ABOUT IF IT HAVE JUST ONE SIDE (LEFT OR RIGHT)
            else
                //THE FOLLOWING COPY THE CONTENT SIDE OF THE TREE THAT ISN'T EMPTY.
                *r = *TEMP;
            free(TEMP);//FREE MEMORY
        }
        else
        {
            //THE FOLLOWING CODE WILL WORK IF THE NODE HAVE 2 CHILDREN OR 2 SIDES
            //NOW FOR THE FOLLOWING LINE GET THE INORDER METHOD
            AVLTree TEMP = MinValue(r->Right);
            //FOR THE FOLLOWING LINE COPY THE INORDER METHOD TO THIS NODE
            strcpy(r->name, TEMP->name);
            //FOR THE LAST FOLLOWING LINE DELETE THE INORDER METHOD
            r->Right = DeleteIt(r->Right, TEMP->name);
        }
    }

    //AND IF THE TREE HAVE JUST ONE SIDE OR CHILD THEN RETURN THE root
    if (r == NULL)
        return r;

    //THE NEXT THING THAT WE SHOULD DO IS TO UBDATE THE LAST HEIGHT WE REACH OR THE HEIGHT OF THE presentTime NODE
    r->Height = 1 + maxmum(height(r->Left),
                           height(r->Right));

    //AFTER UBDATE THE HEIGHT OF THE presentTime NODE WE SHOULD NOW CHECK IF THE NODE BALANCED OR UNBALANCED
    int balance = isBalance(r);
//LET WE SUPPOSED THAT THE NODE IS UNBALANCED THEN WE SHOULD KNOW THAT THERE ARE 4 CASES AS LEFT LEFT, LEFT RIGHT, RIGHT RIGHT, RIGHT LEFT CASES
    //1) LEFT LEFT
    if (balance > 1 && isBalance(r->Left) >= 0)
        return SingleRightRotate(r);

    //2) LEFT RIGHT
    if (balance > 1 && isBalance(r->Left) < 0)
    {
        r->Left =  SingleLeftRotate(r->Left);
        return SingleRightRotate(r);
    }

    //3) RIGHT RIGHT
    if (balance < -1 && isBalance(r->Right) <= 0)
        return SingleLeftRotate(r);

    //4) RIGHT LEFT
    if (balance < -1 && isBalance(r->Right) > 0)
    {
        r->Right = SingleRightRotate(r->Right);
        return SingleLeftRotate(r);
    }
//IF NOT ANY OF THE ABOVE THEN RETURN THE root
    return r;
}

int main()
{
    system("color b1");//THIS STATEMENT ISNT USEFUL AT ALL ITS JUST FOR THE DESIGN :)
//LET THE AVL TREE EMPTY
    AVLTree avltree =  NULL;
    avltree = MakeEmpty( avltree );
    HashTable table = {0, 0, NULL};
    int op;
    char theNameToDelete[MAX];

    do
    {
        printf("1190728\t\t\t\t\tDr.Ahmad AbuSnaina\t\t\t\tAmany khdair\n");
        printf("_______________________________**************************************_____________________________________ \n");
        printf("\n                                     Welcome to our program                  \n \nTo answer your questions please choose one of the following :) \n");
        printf("\nto make sure that every thing is right, please click number 1 first so that the data can load \n");
        printf("For the AVL tree function\n");
        printf("1-  Read from the file and load the data\n");
        printf("2-  INSERT a new patient with all its data \n");
        printf("3-  Find a patient and let me update the information of that patient if found .\n");
        printf("4-  List all patients in order with their information .\n");
        printf("5-  List all patients that have the same illness .\n");
        printf("6-  Delete a patient from the system .\n");
        printf("For the hash function \n");
        printf("7-  Save all words in file (patients_hash.data) .\n");
        printf("8-  Print hashed table (print the entire table to the screen including empty spots) .\n");
        printf("9-  Print out table size .\n");
        printf("10- Print out the used hash function .\n");
        printf("11- Insert a new record into the hash table .\n");
        printf("12- Search for a specific patient .\n");
        printf("13- Delete a specific record .\n");
        printf("14- Save hash table back to file .\n");
        printf("15- Exit .\n");
        printf("_______________________________**************************************_____________________________________ \n");
        scanf("%d", &op);
        system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
        switch(op)
        {
        case 1:
            //to get the information loaded to the screen we want to read it from the read file
            avltree = RF(avltree);
            PrintInOrder(avltree);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 2:
            //this case will insert a new patient from method insert
            InsertNewPatient(avltree);
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 3:
            //this case will find a patient and update it from method findUpdate
            FindThenUpdatePatient(avltree);
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 4:
            //this case will List all patients in order with their information from method print in order
            PrintInOrder(avltree);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 5:
            //this case will List all patients that have the same illness
            LSI(avltree);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 6:
            //this case will Delete a patient from the system
            printf("Hello :)\ncould you please choose the patient full name you want to delete: ");
            fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
            gets(theNameToDelete);//reads a line from stdin and stores it into the string pointed to by str
            fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
            if(Find(theNameToDelete, avltree))
            {
                avltree = DeleteIt(avltree, theNameToDelete);//to delete the node
                printf("\n________________\nDone successfully \n________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            }
            else
            {
                //if the user insert patient name that did not Existing in the file then print the following
                printf("\nSorry but, are you sure about that name? there is no patient with this name:(\n______________________________________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            }
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 7:
            //this case will Save all words in file “patients_hash.data
            SaveInfoToHashFile(avltree);//this method that will help to save the information to the hash file
            ReadFromTheFile(&table);//this method will help to read the table from file
            printf("\nHello Again :)\nThe Hash Table was loaded successfully\n__________________________________________________________\n");
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 8:
            //this case will Print hashed table (print the entire table to the screen including empty spots)
            if(table.TableSize == 0)//if the user did not save the information from the AVL table then the size table for the hash is zero
            {
                printf("\nSorry, you should have save the information to the hash file first because there is no records available currently:(\n___________________________________________________________________________________________________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            }
            else
            {
                //else if the user save the information to the hash file then print the table required
                PT(table);
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            }
            break;
        case 9:
            //this case will Print out table size
            PrintSizeOfTable(table);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 10:
            //this case will Print out the used hash function
            PHF(table);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 11:
            //this case will Insert a new record into the hash table
            InsertNewPatientToTheHash(table);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 12:
            //this case will Search for a specific patient
            SearchARecord(table);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 13:
            //this case will Delete a specific record
            DFT(table);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        case 14:
            //this case will Save hash table back to file
            WriteToTheFile(table);
            getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
            system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
            break;//The break statement ends the loop immediately when it is encountered.
        default:
            printf("\nThanks for using our program :)\n hope you have a nice day\n_________________________________\n");
            break;//The break statement ends the loop immediately when it is encountered.
        }
    }
    while(op != 15); //if the user entered an option that did not match with any of the above then return zero
    return 0;
}
//the following method will allow the user to insert a new patient to the tree
void InsertNewPatient(AVLTree avltree)
{
    //first things first we created the data and give it a special size
    char name[MAX];
    char gender;
    char dateofAdmission[MAX];
    char dateOfBirth[MAX];
    char sick[MAX];
    char address[MAX];
    char BLOOD[5];

    printf("\n______________________________________\nTo insert a new patient please enter his/her information: \n______________________________________\n");
    printf("Patient Name: ");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(name);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Gender: ");
    scanf("%c",&gender);//to let the user write the answer
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Date of admission ^_^\n ");
    int hday, hmonth, hyear;
    printf("The Day: ");
    scanf("%d",&hday);//to let the user write the answer
    printf("The Month: ");
    scanf("%d",&hmonth);//to let the user write the answer
    printf("The Year: ");
    scanf("%d",&hyear);//to let the user write the answer
    printf("Date of birth ^_^\n ");
    int lday, lmonth, lyear;//
    printf("The Day: ");
    scanf("%d",&lday);//to let the user write the answer
    printf("The Month: ");
    scanf("%d",&lmonth);//to let the user write the answer
    printf("The Year: ");
    scanf("%d",&lyear);//to let the user write the answer
    printf("Illness: ");
    scanf("%s", sick);//to let the user write the answer
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Address (city): ");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(address);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Blood Type: ");
    scanf("%s", BLOOD);//to let the user write the answer
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    sprintf(dateofAdmission, "%02d/%02d/%d", hday, hmonth, hyear);//Return a formatted string
    sprintf(dateOfBirth, "%02d/%02d/%d", lday, lmonth, lyear);//Return a formatted string
//now search in the presentTime tree if the patient name inserted by the user is in the tree or not
    AVLTree presentTime = Find(name,avltree);
    if(presentTime)//if the entered name was in the tree then print the following
    {
        printf("\n______________________________________\nmmm helo its me again,the patient you tried to enter is already in the tree and you can't add it again :)\nmake sure to enter another name that not in the tree\n______________________________________\n ");
        getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
        return;//return to main menu
    }
    else//if the entered name was not in the tree then do and print the following
        //the next line will insert the data entered by user
    avltree = Insert(name, gender, dateofAdmission, dateOfBirth, sick, address, BLOOD, avltree);
    printf("\n________________\nDone successfully \n________________\n");
    getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
}

//this method will help for reading the information from the file
AVLTree RF(AVLTree avltree)
{
    //the following operation is a basic base to read from a file
    FILE *input = fopen("patients.txt", "r");
    //if the file was empty then do the following
    if(input == NULL)
    {
        perror("");//this function prints a descriptive error message to stderr
        getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
        return NULL;
    }
    else//if there was an information in the file then do the following
    {
        //first things first we create the data and give it a special size
        char puffers[900];
        char name[MAX];
        char gender;
        char dateofAdmission[MAX];
        char dateOfBirth[MAX];
        char sick[MAX];
        char address[MAX];
        char BLOOD[5];
        //the following operation will divide the information from the file according to this sign #
        while(fgets(puffers, 900, input))
        {
            char *token = strtok(puffers, "#");
            strcpy(name, token);//copy the data or in other world store it
            token = strtok(NULL, "#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
            gender = token[0];//store the data

            token = strtok(NULL, "#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
            strcpy(dateofAdmission, token);//copy the data or in other world store it

            token = strtok(NULL, "#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
            strcpy(dateOfBirth, token);//copy the data or in other world store it

            token = strtok(NULL, "#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
            strcpy(sick, token);//copy the data or in other world store it

            token = strtok(NULL, "#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
            strcpy(address, token);//copy the data or in other world store it

            token = strtok(NULL, "\n");//this statement will cut what seen after seen a space and return null when the string has been fully tokenized.
            strcpy(BLOOD, token);//copy the data or in other world store it
            char dateAdmission[MAX] = {dateofAdmission[0], dateofAdmission[1], '/', dateofAdmission[2], dateofAdmission[3], '/', dateofAdmission[4], dateofAdmission[5], dateofAdmission[6], dateofAdmission[7], '\0'};
            char birthDate[MAX] = {dateOfBirth[0], dateOfBirth[1], '/', dateOfBirth[2], dateOfBirth[3], '/', dateOfBirth[4],  dateOfBirth[5], dateOfBirth[6], dateOfBirth[7], '\0'};
            avltree = Insert(name, gender, dateAdmission, birthDate, sick, address, BLOOD, avltree);
        }
        fclose(input);//close the file
        printf("______________________________________\nThe data has been read successfully\n______________________________________\n");
        return avltree;
    }
}

//the next method will allow the user to find the patient that want to update his/her information
void FindThenUpdatePatient(AVLTree avltree)
{
    //first of all we start by order from user to enter the name
    char name[MAX];
    printf("\nHello :)\ncould you please choose the patient full name that you want to look for:");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(name);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("\n%s\n", name);
//this statement allow to find the name of the wanted one
    AVLTree presentTime = Find(name, avltree);
//if the compiler found the wanted name then it will start do the following
    if(presentTime)
    {
        printf("\n________________\nPatient found successfully\n________________\n");
        printf("Patient Name: %s, Gender: %c, Date of admission: %s, Date of birth ^_^: %s, Illness: %s, Address: %s,  Blood type: %s\n",presentTime->name, presentTime->gender, presentTime->DateOfAdmission, presentTime->DateOfBirth, presentTime->Illness, presentTime->Address, presentTime->BloodType);
        char op;
        printf("\n_____________________________________________\nHello :), if you want to update the information for this patient please print y for yes. if you don't just click on any thing to get to the main menu \n");
        op = getch();
        if(op == 'y' || op == 'Y')
        {
            printf("could you please Choose what you want to update:(just click the number) \n");
            printf("\n________________\n(1) Gender\n(2) Date of admission\n(3) Date of birth\n(4) Address\n(5) Illness\n(6) Blood type\n(7) Don't want to update this patient, Back to the main menu\n");
            int choice;
            scanf("%d", &choice);//to let the user write the answers
            while(choice < 1 || choice > 8)//this condition will work only if the choices were less than 1 or greater than 8
            {
                printf("sorry but No such CHOISE! I already told you to Enter one of the choices that appear in front of you :(, chose again please\n\n");
                scanf("%d", &choice);//to let the user write the answers
            }
            //if the user insert 1 then get the gender information
            if(choice == 1)
            {
                if(presentTime->gender == 'MASCULINE')
                    presentTime->gender = 'FEMININE';
                else if(presentTime->gender == 'masculine')
                    presentTime->gender = 'FEMININE';
                else
                    presentTime->gender = 'MASCULINE';
                printf("\n________________\nThe Gender has been changed automatically :)\n________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                return;//return to main menu
            }
            //if the user insert 2 then
            else if(choice == 2)
            {
                printf("Date of admission \n");
                int hday, hmonth, hyear;
                printf("The Day: ");
                scanf("%d",&hday);//to let the user write the answer
                printf("The Month: ");
                scanf("%d",&hmonth);//to let the user write the answer
                printf("The Year: ");
                scanf("%d",&hyear);//to let the user write the answer
                char strL[11];
                sprintf(strL, "%02d/%02d/%d", hday, hmonth, hyear);//Return a formatted string
                strcpy(presentTime->DateOfAdmission, strL);//copy the data or in other world store it
                printf("\n________________\nCongratulations its Changed successfully\n________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                return;//return to main menu

            }
            //if the user insert 3 then
            else if(choice == 3)
            {
                printf("Birth date\n ");
                int lday, lmonth, lyear;
                printf("Day: ");
                scanf("%d",&lday);//to let the user write the answer
                printf("Month: ");
                scanf("%d",&lmonth);//to let the user write the answer
                printf("Year: ");
                scanf("%d",&lyear);//to let the user write the answer
                char strL1[MAX];
                sprintf(strL1, "%02d/%02d/%d", lday, lmonth, lyear);//Return a formatted string
                strcpy(presentTime->DateOfBirth, strL1);//copy the data or in other world store it
                printf("\n________________\nCongratulations its Changed successfully\n________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                return;//return to main menu
            }
            //if the user insert 4 then
            else if(choice == 4)
            {
                char address[MAX];
                printf("Address: ");
                scanf("%s", address);//to let the user write the answer
                fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
                strcpy(presentTime->Address, address);//copy the data or in other world store it
                printf("\n________________\nCongratulations its Changed successfully\n________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                return;//return to main menu
            }
            //if the user insert 5 then
            else if(choice == 5)
            {
                char sick[MAX];
                printf("new Illness: ");
                scanf("%s", sick);//to let the user write the answer
                fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
                strcpy(presentTime->Illness, sick);//copy the data or in other world store it
                printf("\n________________\nCongratulations its Changed successfully\n________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                return;//return to main menu
            }
            //if the user insert 6 then
            else if(choice == 6)
            {
                char BLOOD[5];
                printf("new Blood type: ");
                scanf("%s", BLOOD);//to let the user write the answer
                fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
                strcpy(presentTime->BloodType, BLOOD);//copy the data or in other world store it
                printf("\n________________\nCongratulations its Changed successfully\n________________\n");
                getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
                return;//return to main menu
            }
            //if the user insert 7 then
            else if(choice == 7)
                return;//return to main menu
        }
    }
    else
    {
        printf("\n________________\nSorry, we cant find the name you entered in the tree. try to check out the patients list\n________________\n");
        getch();//getch means pauses the Output Console until a key is pressed and The entered character does not show up on the console.
        return;//return to main menu
    }
}
//this method will print to the screen all the patient whose have the same illness
void LSI(AVLTree avltree)
{
    char illnes[MAX];

    printf("\n________________\nCould you please print the Illness you want to search for: ");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(illnes);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    toLower(illnes);//this function takes an upper case alphabet and convert it to a lower case character.
    pInorderIll(illnes, avltree);
}

//the following method print all patient illness but in order as required
void pInorderIll(char *strL, AVLTree avltree)
{
    //of the tree was not empty then
    if( avltree != NULL)
    {
        //AS THE ROLE OF THE INORDER FUNCTION ITS START SEARCHING FROM THE LEFT FOLLOWED BY THE MIDDLE OR THE ROOT THEN THE RIGHT
        //PRINT THE EXITING INFORMATIONS IN THE LEFT
        pInorderIll(strL, avltree->Left );
        char strL1[MAX];
        strcpy(strL1, avltree->Illness);//copy the data or in other world store it
        toLower(strL1);//this function takes an upper case alphabet and convert it to a lower case character.
        if(strcmp(strL, strL1) == 0)//this will let the program compare between the first and the second If the condition is met then it will print the informations
            printf("%s, %c, %s, %s, %s, %s, %s \n", avltree->name, avltree->gender, avltree->DateOfAdmission, avltree->DateOfBirth, avltree->Address, avltree->Illness, avltree->BloodType);
        //PRINT THE EXITING INFORMATIONS IN THE RIGHT
        pInorderIll(strL, avltree->Right );
    }
}

void toLower(char *strL)//this method will convert the worlds from upper to lower case
{
    //if it wasn't null then
    for (int X = 0; strL[X]!='\0'; X++)
    {
        //convert all the world with capital letter to small letter
        if(strL[X] >= 'A' && strL[X] <= 'Z')
        {
            strL[X] = strL[X] + 32;//let me explain this statement with example: ‘A‘ has a ASCII value 65 and ‘a‘ has a ASCII value 97 (65+32).
        }
    }

}

void POF(AVLTree avltree, FILE* output)
{
    //if the avltree was not empty then print the output
    if(avltree != NULL)
    {
        //we used here the in order operation to print them in order in the file
        //PRINT THE EXITING INFORMATIONS IN THE LEFT
        POF(avltree->Left, output);
        fprintf(output, "%s#%c#%s#%s#%s#%s#%s\n", avltree->name, avltree->gender, avltree->DateOfAdmission, avltree->DateOfBirth, avltree->Illness, avltree->Address, avltree->BloodType);
        //PRINT THE EXITING INFORMATIONS IN THE RIGHT
        POF(avltree->Right, output);
    }
}

//this method is the key to let all the hash functions work, so the user should choose this choice first so he can get a value for the other hash functions
void SaveInfoToHashFile(AVLTree avltree)
{
    //create a file to save or get the information inside it
    FILE *output = fopen("Patients_Hash.data", "w");
    //if there is no data in the file then
    if(output == NULL)
    {
        perror("\n________________\nSorry but this file can't be created \t|\t\n________________\n");//this function prints a descriptive error message to stderr
        return;//return to main menu
    }
    else//if there was data in the file then print them
    {
        POF(avltree, output);
        fclose(output);//close file
        printf("\n________________\nDone successfully \n________________\n");
    }
    return;//return to main menu
}

//this method will check if its prime or not
int isPrime(int NUMBER)
{
    int X;
    //the following operation here will ceck it is prime or not
    for(X = 2 ; X <= NUMBER/2 ; X++)
        if (NUMBER % X == 0)//if the mod equal zero then return zero
            return 0;

    return 1;//else return one
}

int Hash(HashTable table, char name[MAX])//get the index that will put the world in it,refresh the table and initialize it
{
//return the mode
    return strlen(name) % table.TableSize;
}

//we done with the first section now move to the hash functions
int RequiredSize(int n)//REQUIRED TABLE SIZE FOR THE HASH TABLE
{
    //we initialized an equation to calculate the table size
    int RequiredSize = 2*n + 1;
    RequiredSize++;
    while(!isPrime(RequiredSize))
        RequiredSize++;

    return RequiredSize;//return the required table size
}

//this method will rehash the table and update its size
void rehash(HashTable *table)
{
    //this will get a new size for the hash table
    int oldestSize = (*table).TableSize;
    int newestSize = RequiredSize(oldestSize);
    (*table).TableSize = newestSize;
//this will let insert another values
    A_V_L *TEMP = (*table).R;
    (*table).R = (A_V_L *) calloc(newestSize, sizeof(A_V_L) );//to book a place for the placement or in other word the position in the memory to let it add to the node

    int X;

    for (X = 0 ; X < oldestSize ; X++)
        if( TEMP[X].Statuse == 1)
            InsertTo(table, TEMP[X]);

    free(TEMP);//free memory
}

//the following method is to update the table size
int square(HashTable table, char name[MAX])
{
    int X = 1;
    int NuMbers = Hash(table, name);
    int squarnum = NuMbers;
//this loop will help to update and calculate the table size
    while(table.R[squarnum].Statuse == 1)
    {
//the equation that will help with the update
        squarnum = (NuMbers + X*X) % table.TableSize;
        X++;
    }
    return squarnum;
}

//THIS METHOD WILL INSERT THE PATIENT INFORMATION IN THE HASH avltree
void InsertTo(HashTable *table, A_V_L rec)
{

    (*table).NumberOfRecording++;
    if ( (*table).TableSize < RequiredSize( (*table).NumberOfRecording ) )
        rehash(table);
    rec.Statuse = 1;
    int NuMbers = square(*table, rec.name);
    (*table).R[NuMbers] = rec;
}
// THIS METHOD DELETES A NODE WITH A GIVEN KEY FROM A SUBTREE WITH A
//GIVEN ROOT USING A RECURSIVE ALGORITHM AND FINALLY IT RETURNS THE MODIFIED SUBTREE'S ROOT.
void DFT(HashTable table)
{
    //IF THE TABLE SIZE WAS EMPTY THEN PRINT
    if(table.TableSize == 0)
    {
        printf("\n________________\nSorry, you should have save the information to the hash file first because there is no records available currently:(\n________________\n");
        return;//return to main menu
    }
    char name[MAX];
    printf("\n________________\nName of patient to look for: \n");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(name);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
//THIS STATEMENT WILL HELP TO FIND THE RECORD WE WANT TO DELETE
    int NuMbers = FR(table, name);
    if (NuMbers != -1)
    {
        table.R[NuMbers].Statuse = 2;
        printf("\n________________\nDone successfully!\n________________\n\n");
    }
    else
    {
        printf("\n________________\nSorry, we cant find the name you entered in the tree. try to check out the patients list\n________________\n");
    }
}

//this method get the name from user and search in the table and return a value from user to insert the name
int FR(HashTable table, char name[MAX])
{

    int X = 1;

    int NuMbers = Hash(table, name);
    int squarnum = NuMbers;
//while it's not empty do the following
    while(table.R[squarnum].Statuse != 0)
    {
//if the status was not equal two and the compare function was equal zero then return the Required
        if (table.R[squarnum].Statuse != 2 &&  strcmp(table.R[squarnum].name,name) == 0)
        {
            return squarnum;
        }
//else if not any of the above Verified then calculate the following equation
        else
        {
            squarnum = (NuMbers + X*X) % table.TableSize;
            X++;
        }
    }
    return -1;//if return -1 means that it did not end very well
}
//this method will read the table from the hash file
void ReadFromTheFile(HashTable *table)
{
    //open the hash file
    FILE *input = fopen("Patients_Hash.data","r");
    //if the file was empty then
    if(input == NULL)
    {
        system("cls");//THIS FUNCTION IS JUST TO CLEAR THE OUTPUT SCREEN.
        perror("");//this function prints a descriptive error message to stderr
        return;//return to main menu
    }
    char lineation[900];
    int numOfLineation = 1;
//each line will be read line by line and It is given a specific size
    while (fgets(lineation,900,input) != NULL)// reading the file line by line using the fgets if it was not empty
        ++numOfLineation;

    (*table).TableSize = RequiredSize(numOfLineation);
    (*table).R = (A_V_L *) calloc( (*table).TableSize, sizeof(A_V_L) ); //to book a place for the placement or in other word the position in the memory to let it add to the node
    rewind(input);

    while (fgets(lineation,500,input) != NULL)// reading the file line by line using the fgets if it was not empty
    {

        char *name = strtok(lineation,"#");//this statement will cut what seen after this sign #
        char *gender = strtok(NULL,"#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
        char *addmissionDate = strtok(NULL,"#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
        char *dateOfBirth = strtok(NULL,"#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
        char *sick = strtok(NULL, "#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
        char *address = strtok(NULL, "#");//this statement will cut what seen after this sign # and return null when the string has been fully tokenized.
        char *bloodType = strtok(NULL,"\n");//this statement will cut what seen after seen a space and return null when the string has been fully tokenized.
        A_V_L rec;//call the AVL
        strcpy(rec.name, name);//copy the data or in other world store it
        rec.gender = gender[0];
        strcpy(rec.DateOfAdmission, addmissionDate);//copy the data or in other world store it
        strcpy(rec.DateOfBirth, dateOfBirth);//copy the data or in other world store it
        strcpy(rec.Illness, sick);//copy the data or in other world store it
        strcpy(rec.Address, address);//copy the data or in other world store it
        strcpy(rec.BloodType, bloodType);//copy the data or in other world store it
        InsertTo(table,rec); //call the function
    }
    fclose(input);//close the file
}

//this method search for a record in the table via patient name
void SearchARecord(HashTable table)
{
    //IF THE TABLE SIZE WAS EMPTY THEN PRINT
    if(table.TableSize == 0)
    {
        printf("\n________________\nSorry, you should have save the information to the hash file first because there is no records available currently:(\n________________\n");
        return;//return to main menu
    }
    char name[MAX];
    printf("\nHello :)\ncould you please choose the patient full name that you want to look for: \n");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(name);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    if(FR(table,name) != -1)
    {
        //THIS METHOD WILL FIND THE THE RECUIRED RECORD
        int X = FR(table,name);
        printf("\n________________\nFound successfully!\n________________\n\nindex:[%d]%s, %c, %s, %s, %s, %s, %s\n", X, table.R[X].name, table.R[X].gender, table.R[X].DateOfAdmission, table.R[X].DateOfBirth, table.R[X].Illness, table.R[X].Address, table.R[X].BloodType);
    }
    else
    {
        printf("\n________________\nSorry, we cant find the name you entered in the tree. try to check out the patients list\n________________\n");
    }
}

//this method will insert new patient information to the hash table
void InsertNewPatientToTheHash(HashTable table)
{
    //first things first we created the data and give it a special size
    A_V_L rec;
    char name[MAX];
    char gender;
    char dateofAdmission[MAX];
    char dateOfBirth[MAX];
    char sick[MAX];
    char address[MAX];
    char bloodType[5];

    printf("\n______________________________________\nTo insert a new patient please enter his/her information: \n______________________________________\n");
    printf("Patient Name: ");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(name);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Gender: ");
    scanf("%c",&gender);//to let the user write the answer
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Date of admission ^_^\n ");
    int hday, hmonth, hyear;
    printf("The Day: ");
    scanf("%d",&hday);//to let the user write the answer
    printf("The Month: ");
    scanf("%d",&hmonth);//to let the user write the answer
    printf("The Year: ");
    scanf("%d",&hyear);//to let the user write the answer
    printf("Date of birth ^_^\n ");
    int lday, lmonth, lyear;
    printf("The Day: ");
    scanf("%d",&lday);//to let the user write the answer
    printf("The Month: ");
    scanf("%d",&lmonth);//to let the user write the answer
    printf("The Year: ");
    scanf("%d",&lyear);//to let the user write the answer
    printf("Illness: ");
    scanf("%s", sick);//to let the user write the answer
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Address: ");
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(address);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    printf("Blood Type: ");
    scanf("%s", bloodType);//to let the user write the answer
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.


    sprintf(dateofAdmission, "%02d/%02d/%d", hday, hmonth, hyear);//Return a formatted string
    sprintf(dateOfBirth, "%02d/%02d/%d", lday, lmonth, lyear);//Return a formatted string
    strcpy(rec.name, name);//copy the data or in other world store it
    rec.gender = gender;
    strcpy(rec.DateOfAdmission, dateofAdmission);//copy the data or in other world store it
    strcpy(rec.DateOfBirth, dateOfBirth);//copy the data or in other world store it
    strcpy(rec.Illness, sick);//copy the data or in other world store it
    strcpy(rec.Address, address);//copy the data or in other world store it
    strcpy(rec.BloodType, bloodType);//copy the data or in other world store it
    InsertTo(&table, rec);//call the function
    printf("\n________________\nDone successfully \n________________\n");

}
void WriteToTheFile (HashTable table)
{
    //if the hash avltree was empty or in other world the information was not saved then print the following
    if(table.TableSize == 0)
    {
        printf("\n________________\nSorry, you should have save the information to the hash file first because there is no records available currently:(\n________________\n");
        return;//return to main menu
    }
    char path[200];

    printf("\n________________\nThe File path is: \n________________\n");

    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
    gets(path);//this statement reads a line from stdin and stores it into the string pointed to by str.
    fflush(stdin);//is used to flush the output buffer of the stream. It returns 0, if successful otherwise, returns EOF and feof error indicator is set.
//the following sentence is to let the compiler write this time not read
    FILE *output = fopen(path, "w");
//if the file was empty then print
    while (output == NULL)
    {
        perror("\n________________\nSorry but this file can't be created \t|\t\n________________\n");//this function prints a descriptive error message to stderr
        return;//return to main menu
    }

    int X;
//otherwise if there was a table size then do the following
    for(X = 0 ; X < table.TableSize ; X++)
        if(table.R[X].Statuse == 1)//if the status was equal one then print the information from the table records
            fprintf(output, "%s#%c#%s#%s#%s#%s#%s\n", table.R[X].name,table.R[X].gender, table.R[X].DateOfAdmission, table.R[X].DateOfBirth,table.R[X].Illness, table.R[X].Address, table.R[X].BloodType);
    printf("\n________________\nDone successfully \n________________\n");
    //close the file
    fclose(output);

}

//this method will print the table size
void PrintSizeOfTable(HashTable table)
{
    printf("The table size according your file is: %d\n",table.TableSize);
}

//this method print what hash function were used
void PHF(HashTable table)
{

    printf("the functions were used for hashing:\n");
    printf("g(x) = x %% %d\n\n",table.TableSize);//calculate it using the table size

    printf("the functions were used for quadratic probing:\n");
    printf("f(x) = (g(x) + X*X) %% %d = (x %% %d + X*X) %% %d\n",table.TableSize, table.TableSize, table.TableSize);//calculate it using the table size
}


//this method print the table and all inside it
void PT(HashTable table)
{

    int X;
    printf("Hi there :)\nyou should know that the hashed table it could be includes empty spots so do not panic. that was required in the project :)\nkeep going please\n__________________________________________________________\n");
    for(X = 0 ; X < table.TableSize ; X++)
    {
        if (table.R[X].Statuse != 0)//if it was not empty then print all the information
            printf("[%d]:  %s, %c, %s, %s, %s, %s, %s,  Status: %d\n",X, table.R[X].name,table.R[X].gender, table.R[X].DateOfAdmission, table.R[X].DateOfBirth,table.R[X].Illness, table.R[X].Address, table.R[X].BloodType, table.R[X].Statuse);

        else//otherwise print the value
            printf("[%d]:\n", X);
    }
}
//this is the end of project 3 X hope every thing was correct. thanks for your time our great doctor

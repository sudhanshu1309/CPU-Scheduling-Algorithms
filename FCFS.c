#include <stdio.h>
#include <stdlib.h>

struct node
{
    int PID, AT, BT, CT, TAT, WT;
    struct node *next;
};
struct node *head;

void sortList();
void Solve();
void Print()
{
    if (head == NULL)
    {
        printf("\nEmpty List!!!");
        return;
    }
    printf("\nPID \t AT \t BT \t CT \t TAT \t WT");
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("\n%d \t %d \t %d \t %d \t %d \t %d", temp->PID, temp->AT, temp->BT, temp->CT, temp->TAT, temp->WT);
        temp = temp->next;
    }
    printf("\n");
}

void Insert(int PID, int AT, int BT)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->PID = PID;
    temp->AT = AT;
    temp->BT = BT;
    temp->next = NULL;

    if (head == NULL)
    {
        head = temp;
        return;
    }

    struct node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = temp;
}

int cummulativect;

int main()
{
    int contexttime;
    printf("Enter the context switching time: ");
    scanf("%d", &contexttime);
    head = NULL;
    int n;
    printf("Enter the total number of processes: ");
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
    {
        int pid, at, bt;
        printf("Enter the PID: ");
        scanf("%d", &pid);
        printf("Enter the Arrival time: ");
        scanf("%d", &at);
        printf("Enter the Burst time: ");
        scanf("%d", &bt);
        Insert(pid, at, bt);
    }

    printf("\nOriginal processes list:\n");
    Print();

    sortList();
    printf("\nSorted processes list:\n");
    Print();
    
    Solve();
    printf("\nSolved process list!!!");
    Print();

    return 0;
}

//sortList() will sort nodes of the list in ascending order
void sortList()
{
    //Node current will point to head
    struct node *current = head, *index = NULL;
    int pid, at, bt;

    if (head == NULL)
    {
        return;
    }
    else
    {
        while (current != NULL)
        {
            //Node index will point to node next to current
            index = current->next;

            while (index != NULL)
            {
                //If current node's data is greater than index's node data, swap the data between them
                if (current->AT > index->AT)
                {
                    pid = current->PID;
                    at = current->AT;
                    bt = current->BT;
                    current->PID = index->PID;
                    current->AT = index->AT;
                    current->BT = index->BT;
                    index->PID = pid;
                    index->AT = at;
                    index->BT = bt;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

void Solve()
{
    if (head == NULL)
    {
        return;
    }
    struct node *temp = head;
    while (temp != NULL)
    {

        temp->CT = cummulativect + temp->BT;
        temp->TAT = temp->CT - temp->AT;
        temp->WT = temp->TAT - temp->BT;
        cummulativect = cummulativect + temp->BT;
        temp = temp->next;
    }
}
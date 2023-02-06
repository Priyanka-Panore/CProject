
//Mini project on player
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//1. Concept of typedef and structure define
typedef struct player
{
	int id; //jersey no
	char pname[30];  //player name
	int matches;	//no of matches played
	int runs;
	int wickets;
}player;
void store(player*,int,int);
int valid_jersey(player*,int);
void display_player_data(player*,int,int);
void insert_new_players(player*,int*);
player* delete_player(player*,int*);
void update_player_data(player*,int);
void search_player(player*,int);
void search_by_jersey_no(player*,int);
void search_by_name(player*,int);
void sort_players(player*,int);
void max_min(player*,int);
void main()
{
	player* player_data;
	int no_of_players,flag;
	int choice,inner_choice,max_choice;
	player* temp;
	
	printf("\nEnter no. of players you want to insert data for: ");
	scanf("%d",&no_of_players);
	
	//2. concept of dynamic memory allocation -- malloc
	player_data = (player*)malloc(sizeof(player)*no_of_players);
	
	//3. concept of function process
	store(player_data,0,no_of_players);
	
	do
	{
		printf("\n============================================================================\n");
		printf("\nFollowing operations can be performed on player data,");
		printf("\nEnter 1 - Display data");
		printf("\nEnter 2 - Insert a new player data");
		printf("\nEnter 3 - Update a player data");
		printf("\nEnter 4 - Delete a player");
		printf("\nEnter 5 - For more options..");
		printf("\nEnter 0 - To EXIT");
		
		printf("\n\nEnter the value associated with operation you wish to perform: ");
		scanf("%d",&choice);
		
		if(choice==1)
		{
			display_player_data(player_data,0,no_of_players);
		}
		else if(choice==2)
		{
			insert_new_players(player_data,&no_of_players);
		}
		else if(choice==3)
		{
			update_player_data(player_data,no_of_players);
		}
		else if(choice==4)
		{
			temp = player_data;
			player_data = delete_player(player_data,&no_of_players);
			printf("\nPlayer data in main: %u",player_data);
			free(temp);
		}
		else if(choice==5)
		{
//			search_player(player_data,no_of_players);
			printf("\n============================================================================\n");
			printf("\nEnter 6 - Search Player");
			printf("\nEnter 7 - Sort Player Data Based on Runs");
			printf("\nEnter 8 - Maximum and Minimum Runs");
			printf("\n\nEnter the value associated with operation you wish to perform: ");
			scanf("%d",&inner_choice);
			
			if(inner_choice==6)
			{
				search_player(player_data,no_of_players);
			}
			
			else if(inner_choice==7)
			{
				sort_players(player_data,no_of_players);
			}
			
			else if(inner_choice==8)
			{
				max_min(player_data,no_of_players);

			}
			
		}
	}while(choice != 0);
	
	free(player_data);
}

void store(player* p,int initial, int size)
{
	int pos,flag;
	
	printf("\n=================Enter player details=================\n");
	
	for(pos=initial;pos<size;pos++)
	{
		
		//jersey number
		printf("\ni=%d",pos);
		printf("\nEnter jersey no: ");
		scanf("%d",&p[pos].id);
		
		flag = valid_jersey(p,pos);
		if(flag==1)
		{
			printf("\nYou cannot repeat jersey number!");
			printf("..Enter a new jersey number.");
			pos = pos-1;
		}
		
		else
		{
			fflush(stdin);
			printf("\nEnter name: ");
			gets(p[pos].pname);
		
			printf("\nEnter matches played: ");
			scanf("%d",&p[pos].matches);
		
			printf("\nEnter runs scored: ");
			scanf("%d",&p[pos].runs);
		
			printf("\nEnter wickets took: ");
			scanf("%d",&p[pos].wickets);
		}
		
		
		printf("\n----------------------------------------------------\n");
	}
	
	printf("\nPlayer data stored Successfully!\n");
}

//validation of jersey number
int valid_jersey(player* p,int pos)
{
	int flag=0;
	int prev;
	
	prev = pos-1;
	
	while(prev>=0)
	{
		if(p[pos].id==p[prev].id)
		{
			flag=1;
			break;
		}
		else
		{
			flag=0;
			prev--;
		}
	}
	
	return flag;
}

void insert_new_players(player* p,int* size)
{
	int new_size,pos,old_size,flag;
	
	old_size = *size;
	printf("\nHow many new player data you want to enter: ");
	scanf("%d",&new_size);
	
	*size = *size + new_size;
	
	new_size = *size;
	
	p = (player*)realloc(p,*size*sizeof(player));
	
	store(p,old_size,new_size);
}

player* delete_player(player* p,int* size)
{
	player* temp;
	int player_id,pos=0,temp_pos,temp_size;
	
	temp_size = *size - 1;
	*size = temp_size;
	temp = (player*)malloc(sizeof(player)*temp_size);
	
	printf("\nEnter player id you want to delete the data for: ");
	scanf("%d",&player_id);
	
	for(temp_pos=0;temp_pos<temp_size;temp_pos++)
	{
		if(p[pos].id==player_id)
		{
			pos=pos+1;
		}
			temp[temp_pos].id = p[pos].id;
			strcpy(temp[temp_pos].pname,p[pos].pname);
			temp[temp_pos].matches = p[pos].matches;
			temp[temp_pos].runs = p[pos].runs;
			temp[temp_pos].wickets = p[pos].wickets;
		pos++;
	}
	printf("\n----------------------------------------------------\n");
	printf("\nPlayer deleted Successfully!\n");
	return temp;
}

void update_player_data(player* p,int size)
{
	int player_id,pos,player_pos,choice;
	
	printf("\nEnter jersey no. of the player you want to update data for: ");
	scanf("%d",&player_id);
	
	for(pos=0;pos<size;pos++)
	{
		if(p[pos].id == player_id)
		{
			player_pos = pos;
			printf("\n\n\nYou entered the data for pos : %d",player_pos);
			break;
		}
	}
	
	do
	{
	
		printf("\nEnter 1 to update PLAYER NAME");
		printf("\nEnter 2 to update PLAYER MATCHES PLAYED COUNT");
		printf("\nEnter 3 to update PLAYER RUNS SCORED COUNT");
		printf("\nEnter 4 to update PLAYER WICKETS TOOK COUNT");
		printf("\nEnter 0 to EXIT");
		
		printf("\n\nWhat data you want to update: ");
		scanf("%d",&choice);
		
		if(choice==1)
		{
			printf("\nOld name: %s",p[player_pos].pname);
			fflush(stdin);
			printf("\nEnter new name: ");
			gets(p[player_pos].pname);
		}
		
		else if(choice==2)
		{
			printf("\nYou want to update player matches\n");
			printf("\nOld count: %d",p[player_pos].matches);
			printf("\nEnter matches played: ");
			scanf("%d",&p[player_pos].matches);
		}
		
		else if(choice==3)
		{
			printf("\nYou want to update player runs\n");
			printf("\nOld count: %d",p[player_pos].runs);
			printf("\nEnter runs scored: ");
			scanf("%d",&p[player_pos].runs);
		}
		
		else if(choice==4)
		{
			printf("\nYou want to update player wickets\n");
			printf("\nOld count: %d",p[player_pos].wickets);
			printf("\nEnter wickets took: ");
			scanf("%d",&p[player_pos].wickets);
		}	
		
		else
		{
			printf("\nPlease enter valid choice!\n");
		}
	}while(choice!=0);
	
	printf("\n----------------------------------------------------\n");
	printf("\nPlayer data updated Successfully!\n");
}

void search_by_jersey_no(player* p,int size)
{
	int search_id;
	int pos,flag,pos_p,len,space;
	printf("\n----------------------------------------------------\n");
	printf("\nEnter jersey no. you want to search: ");
	scanf("%d",&search_id);
	
	for(pos=0;pos<size;pos++)
	{
		if(p[pos].id==search_id)
		{
			pos_p = pos;
			flag = 1;
			break;
		}
	}
	if(flag==1)
	{
	printf("\n========================Player details by Jersey No=============================\n");
	printf("|  Name\t\t | JerseyNo.\t | Total Matches | Total Runs \t | Total Wickets");
	len = strlen(p[pos_p].pname);
		space = 10 - len;
		printf("\n");
		printf("| %s",p[pos_p].pname);
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf("\t");
		
		printf(" |   %d",p[pos_p].id);
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf(" |   %d",p[pos_p].matches);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].runs);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].wickets);
	}
	else
	{
		printf("\nYou entered INVALID jersey number!");
	}
}

void search_by_name(player* p,int size)
{
	char search_name[30];
	int pos,pos_p,flag=0,space,plen,s;
	char* len;
	
	fflush(stdin);
	printf("\nEnter the name you want to search : ");
	gets(search_name);
	
	for(pos=0;pos<size;pos++)
	{
		len = (strstr(p[pos].pname,search_name));
		s = strlen(len);
		printf("\ns:%d",s);
		if(strlen(len)==0)
		{
			printf("\nString not found!");
		}
		else
		{
//			printf("\n Len : %d ",strlen(len));
			pos_p = pos;
			flag=1;
			break;
		}
		flag=0;
	}
	
	if(flag==1)
	{
		printf("\n========================Player details by Name=============================\n");
		printf("|  Name\t\t | JerseyNo.\t | Total Matches | Total Runs \t | Total Wickets");
		plen = strlen(p[pos_p].pname);
		space = 10 - plen;
		printf("\n");
		printf("| %s",p[pos_p].pname);
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf("\t");
		
		printf(" |   %d",p[pos_p].id);
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf(" |   %d",p[pos_p].matches);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].runs);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].wickets);
	}
}


void sort_players(player* p,int size)
{
	int* temp;
	int i,j,r;
	int choice,plen,space;
	printf("\nEnter 1 to sort Player data based on Lowest runs to Highest runs");  //Ascending order
	printf("\nEnter 2 to sort Player data based on Highest runs to Lowest runs"); //Descending order
	printf("\nHow you want to sort data? : ");
	scanf("%d",&choice);
	
	if(choice==1)
	{
		//Ascending order
		temp = (int*)malloc(sizeof(int)*size);
		//temp contains only runs
		//copying runs from player structure
		for(i=0;i<size;i++)
		{
			temp[i] = p[i].runs;
		}

		//Sorting runs in ascending order in temp array
		for(i=0;i<size;i++)
		{
			for(j=i+1;j<size;j++)
			{
				if(temp[i]>temp[j])
				{
					r = temp[i]; //r temporary variable
					temp[i] = temp[j];
					temp[j] = r;
				}
			}
		}
		printf("\n===========================Player Data Lowest to Highest====================\n");
			printf("|  Name\t\t | JerseyNo.\t | Total Matches | Total Runs \t | Total Wickets");
		for(i=0;i<size;i++)
		{
			for(j=0;j<size;j++)
			{
				if(temp[i]!=p[j].runs)
					continue;
				else
				{
					plen = strlen(p[j].pname);
				space = 10 - plen;
				printf("\n");
				printf("| %s",p[j].pname);
				while(space>0)
				{
					printf(" ");
					space--;
				}
		
				printf("\t");
		
				printf(" |   %d",p[j].id);
				space = 8;
				while(space>0)
				{
					printf(" ");
					space--;
				}
		
				printf(" |   %d",p[j].matches);
		
				space = 8;
				while(space>0)
				{
					printf(" ");
					space--;
				}
				printf(" |   %d",p[j].runs);
		
				space = 8;
				while(space>0)
				{
					printf(" ");
					space--;
				}
				printf(" |   %d",p[j].wickets);
				}
			}
		}
	
	}
	else if(choice==2)
	{
		printf("\nYou choose to sort in Descending order!");
		temp = (int*)malloc(sizeof(int)*size);
		
		for(i=0;i<size;i++)
		{
			temp[i] = p[i].runs;
		}
		//Sorting runs in descending order in temp array
		for(i=0;i<size;i++)
		{
			for(j=i+1;j<size;j++)
			{
				if(temp[i]<temp[j])
				{
					r = temp[i]; //r temporary variable
					temp[i] = temp[j];
					temp[j] = r;
				}
			}
		}
		
		printf("\nRuns in descending order!\n");
		printf("\n===========================Player Data Highest to Lowest==================\n");
		printf("|  Name\t\t | JerseyNo.\t | Total Matches | Total Runs \t | Total Wickets");
		for(i=0;i<size;i++)
		{
			for(j=0;j<size;j++)
			{
				if(temp[i]!=p[j].runs)
					continue;
				else
				{
					
				plen = strlen(p[j].pname);
				space = 10 - plen;
				printf("\n");
				printf("| %s",p[j].pname);
				while(space>0)
				{
					printf(" ");
					space--;
				}
		
				printf("\t");
		
				printf(" |   %d",p[j].id);
				space = 8;
				while(space>0)
				{
					printf(" ");
					space--;
				}
		
				printf(" |   %d",p[j].matches);
		
				space = 8;
				while(space>0)
				{
					printf(" ");
					space--;
				}
				printf(" |   %d",p[j].runs);
		
				space = 8;
				while(space>0)
				{
					printf(" ");
					space--;
				}
				printf(" |   %d",p[j].wickets);
				}
			}
		}
	
	}
	else
	{
		printf("\nYou entered wrong choice!");
	}
	
	free(temp);
}

void search_player(player* p,int size)
{
	int choice;
	printf("\nEnter 1 to Search Player by Jersey Number");
	printf("\nEnter 2 to Search Player by Name"); 
	printf("\nHow you want to search : ");
	scanf("%d",&choice);
	
	if(choice==1)
	{
		printf("\nSearch by jersey no.");
		search_by_jersey_no(p,size);
	}
	
	else if(choice==2)
	{
		printf("\nSearch by player name");
		search_by_name(p,size);
	}
	
	else
	{
		printf("\nYou entered INVALID choice!");
	}
}

void max_min(player* p,int size)
{
	int choice;
	
	int max,pos,pos_p,min,space,len;
	printf("\nEnter 1 to see details of Player who scored maximum runs");
	printf("\nEnter 2 to see details of Player who scored minimum runs"); 
	printf("\nWhich data you want : ");
	scanf("%d",&choice);
	
	if(choice==1)
	{
		max = p[0].runs;
		
		for(pos=0;pos<size;pos++)
		{
			if(max<p[pos].runs)
			{
				max = p[pos].runs;
				pos_p = pos;
			}
		}
		printf("\n========================Maximum Run scoring Player=============================\n");
	printf("|  Name\t\t | JerseyNo.\t | Total Matches | Total Runs \t | Total Wickets");
	len = strlen(p[pos_p].pname);
		space = 10 - len;
		printf("\n");
		printf("| %s",p[pos_p].pname);
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf("\t");
		
		printf(" |   %d",p[pos_p].id);
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf(" |   %d",p[pos_p].matches);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].runs);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].wickets);
		
	}
	
	else if(choice==2)
	{
		min = p[0].runs;
		
		for(pos=0;pos<size;pos++)
		{
			if(min>p[pos].runs)
			{
				min = p[pos].runs;
				pos_p = pos;
			}
		}
	printf("\n========================Minimum Scored by Player=============================\n");
	printf("|  Name\t\t | JerseyNo.\t | Total Matches | Total Runs \t | Total Wickets");
	len = strlen(p[pos_p].pname);
		space = 10 - len;
		printf("\n");
		printf("| %s",p[pos_p].pname);
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf("\t");
		
		printf(" |   %d",p[pos_p].id);
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf(" |   %d",p[pos_p].matches);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].runs);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos_p].wickets);
	}
	
	else
	{
		printf("\nYou entered INVALID choice!");
	}
}

void display_player_data(player* p,int initial,int size)
{
	int pos;
	int len,space;
	printf("\nP data in main: %u",p);
	printf("\nInitial : %d",initial);
	printf("\nsize : %d",size);
//	|Name - 2space+4+1+|\t = 10
//	\t
//	|Jerseyno. - 2space+9+1+| = 11-3 = 8
//	\t
//	|Total Matches - 2space+13+| = 15
//	\t
//	Total Runs - 2space + 10 =12 + 1extra space
//	\t
//	Total Wickets - 2space + 13 = 15
	printf("\n=============================Player details=============================\n");
	printf("|  Name\t\t | JerseyNo.\t | Total Matches | Total Runs \t | Total Wickets");
    printf("\n-----------------------------------------------------------------------------------   ");
	for(pos=initial;pos<size;pos++)
	{
		len = strlen(p[pos].pname);
		space = 10 - len;
		printf("\n");
		printf("| %s",p[pos].pname);
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf("\t");
		
		printf(" |   %d",p[pos].id);
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		
		printf(" |   %d",p[pos].matches);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos].runs);
		
		space = 8;
		while(space>0)
		{
			printf(" ");
			space--;
		}
		printf(" |   %d",p[pos].wickets);
	}
	printf("\n");
	printf("\nPlayer data displayed Successfully!\n");
}


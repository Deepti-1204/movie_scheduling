#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#define ROWS 5
#define COLS 5
#define MAX 50
#define DOW 7

typedef enum{Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday
}days;

int total_screen,total_capacity;
//function  to check if current date from system is equal to release date
int release_date(int date,int month,int year)
{
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    if (stime.wDay==date && stime.wMonth==month && stime.wYear==year)
        return 1;
    else
        return 0;
}
//function to check if date entered is of valid format
int valid_date(int day, int mon, int year)
{
    int is_valid = 1, is_leap = 0;

    if (year >= 2022 && year <= 9999)
    {

        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            is_leap = 1;
        }
        if(mon >= 1 && mon <= 12)
        {
            if (mon == 2)
            {
                if (is_leap && day == 29)
                {
                    is_valid = 1;
                }
                else if(day > 28)
                {
                    is_valid = 0;
                }
            }
            else if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            else if(day > 31)
            {
                is_valid = 0;
            }
        }

        else
        {
            is_valid = 0;
        }

    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}
//to calculate the difference between two dates to check if the diff%7!=0 then demand_score is calculated
//otherwise if diff%7==0 then it is the next week so initial_demand is considered
int date_diff(int day1,int mon1,int year1,int day2,int mon2,int year2)
{

    int day_diff, mon_diff, year_diff;

    if(!valid_date(day1, mon1, year1))
    {
        printf("Date is invalid.\n");
        exit(0);
    }

    if(!valid_date(day2, mon2, year2))
    {
        printf("Date is invalid.\n");
        exit(0);
    }

    if(day2 < day1)
    {
        if (mon2 == 3)
        {
            if ((year2 % 4 == 0 && year2 % 100 != 0) || (year2 % 400 == 0))
            {
                day2 += 29;
            }

            else
            {
                day2 += 28;
            }
        }
        else if (mon2 == 5 || mon2 == 7 || mon2 == 10 || mon2 == 12)
        {
           day2 += 30;
        }

        else
        {
           day2 += 31;
        }

        mon2 = mon2 - 1;
    }

    if (mon2 < mon1)
    {
        mon2 += 12;
        year2 -= 1;
    }

    day_diff = day2 - day1;
    mon_diff = mon2 - mon1;
    year_diff = year2 - year1;
    return day_diff;
}

//to find the number of screens based on demand
int screen_calc(int dem,int temp_screen,int movie_no)
{
    //printf("temp_screen : %d",(0.8*temp_screen));
    int screen_run;
    if(movie_no<total_screen)
    {
        if (dem<=100 && dem>90)
        {
            screen_run=0.5*temp_screen;
            if (screen_run==1 && temp_screen>1)
                screen_run=(0.5*temp_screen)+1;
        }
        //else if(temp_screen==1)
            //screen_run=temp_screen;
        else if (dem<=90 && dem>70)
        {
            screen_run=0.4*temp_screen;
            if (screen_run==1 && temp_screen>1)
                screen_run=(0.4*temp_screen)+1;
        }
        else if(dem<=50 && dem>30)
           {
            screen_run=0.3*temp_screen;
            if (screen_run==1 && temp_screen>1)
                screen_run=(0.3*temp_screen)+1;
        }
        else
            screen_run=0;
        //printf("\nscreen_run in func %d",screen_run);
    }
    else
    {
        if (dem<=100 && dem>60){
            screen_run=0.5*temp_screen;
            if ((screen_run==0 && temp_screen>0)/*||(screen_run==1 && temp_screen>1)*/)
                screen_run=(0.5*temp_screen)+1;
        }
        else if(dem<=60 && dem>30)
            {
            screen_run=0.3*temp_screen;
            if ((screen_run==0 && temp_screen>0)/*||(screen_run==1 && temp_screen>1)*/)
                screen_run=(0.3*temp_screen)+1;
        }
        else
            screen_run=0;

    }
    return screen_run;
}
//to calculate the initial_demand and demand_score
int demand_calc(int d,int m,int y,int screen_showed)
{
    int initial_demand,tickets_booked,demand_arr[50],i;
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    initial_demand=100;
    if (release_date(d,m,y)==1)
    {
        initial_demand=100;
        i=0;
    }
    else
    {
        if(date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)>=7 && date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)<14)
        {
            initial_demand-=20;
        }
        else if (date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)>=14 && date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)<21)
        {
            initial_demand-=20;
        }
        else if (date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)>=21 && date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)<28)
        {
            initial_demand-=20;
        }
        else if(date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)>=28 &&date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)<49)
        {
            initial_demand-=20;

        }
        else if(date_diff(d,m,y,stime.wDay,stime.wMonth,stime.wYear)>=49)
        {
            initial_demand-=20;
        }
        i++;
    }
    //printf("%d",initial_demand);
    return initial_demand;
}
int screen_show(int initial_demand,int temp_screen,int movie_no)
{
    int d,m,y,screen_showed,tickets_booked,demand_arr[MAX],i;
    screen_showed=screen_calc(initial_demand,temp_screen,movie_no);
    //printf("screen_showed %d",screen_showed);
    //printf("if conditions %d %d %d",(release_date(d,m,y)==1),(release_date(d,m,y)!=1)&&(screen_showed>0),screen_showed==0);
    if (screen_showed==0)
    {
        printf("\nMovie is removed from screening in the multiplex");
    }

    return screen_showed;
}
int popularity(){
 int pop_score,pop_lang=0,mov_rate;
 int lang;
 printf("\n\tEnter the movie rating based on reliable source : ");
 scanf("%d",&mov_rate);


printf("\n\tEnter the language[1-Tamil;2-English;3-Other regional languages] : ");
scanf("%d",&lang);
 if(lang==1){
  pop_lang=10;
}
 else if(lang==2){
  pop_lang=7;
}
 else{
  pop_lang=5;
}
pop_score=pop_lang + mov_rate;
return pop_score;
}
void slot_generation(int dow,float slot_arr[5][3],int temp_screen)
{
    int i=1,j=0;
    if (dow==0 || dow==5 || dow==6)
    {
         for(i=1;i<(total_screen-temp_screen)+1;i++)
         {
             //printf("\n SLOTS FOR SCREEN %d",i);
             float arr[5][3]={{(9+(i-1)*0.05),(12+(i-1)*0.05),5},
                    {(12+(i-1)*0.05),(3+(i-1)*0.05),4},
                    {(3+(i-1)*0.5),(6+(i-1)*0.05),1},
                    {(6+(i-1)*0.05),(9+(i-1)*0.05),2},
                    {(9+(i-1)*0.05),(12+(i-1)*0.05),3}};
            for (j=0;j<5;j++)
            {
                slot_arr[j][0]=arr[j][0];
                slot_arr[j][1]=arr[j][1];
                slot_arr[j][2]=arr[j][2];
                //printf("\n %0.2f - %0.2f    \t\t   %0.0f ",arr[j][0],arr[j][1],arr[j][2]);
            }
         }
    }
    else if(dow<=4 && dow>=1)
    {
        for(i=1;i<(total_screen-temp_screen)+1;i++)
         {
            //printf("\n SLOTS FOR SCREEN %d",i);
            float  arr[5][3]={{(9+((i-1)*0.05)),(12+((i-1)*0.05)),5},
                {(12+(i-1)*0.05),(3+(i-1)*0.05),3},
                {(3+(i-1)*0.05),(6+(i-1)*0.05),2},
                {(6+(i-1)*0.05),(9+(i-1)*0.05),1},
                {(9+(i-1)*0.05),(12+(i-1)*0.05),4}};
            for (j=0;j<5;j++)
            {
                slot_arr[j][0]=arr[j][0];
                slot_arr[j][1]=arr[j][1];
                slot_arr[j][2]=arr[j][2];
                //printf("\n %0.2f - %0.2f    \t\t   %0.0f ",arr[j][0],arr[j][1],arr[j][2]);
            }
         }
    }
}
int runtime(int comb_score[50],int run_time[],int movie_no,int dow)
{ int i;
    int dayscore,final_score;
    if (dow==0 || dow==5 || dow==6)
        dayscore=100;
    else if(dow<=4 && dow>=1)
        dayscore=10;
    for( i=0;i<movie_no;i++)
    {
        final_score=(comb_score[i]+dayscore)*0.5;
        if ((final_score>90) && (final_score<=100))
                run_time[i]=5;
        else if ((final_score>70) && (final_score<=90))
                run_time[i]=4;
        else if((final_score>50) && (final_score<=70))
                run_time[i]=3;
        else if ((final_score>30) && (final_score<=50))
                run_time[i]=2;
        else
                run_time[i]=1;
    }
}
void list2rank(int arr[MAX],int n,int newarr[MAX])
{int i,j;
   for ( i = 0; i < n; i++)
    {
        int curRank = 0;

        for ( j = 0; j < i; j++)
        {
            if (arr[i] < arr[j])
            {
                curRank++;
            }
            else
            {
                newarr[j]++;
            }
        }

        newarr[i] = curRank;
    }
}
void bin_scheduler(int aggval[MAX][MAX],int binarr[MAX][MAX],int mapint[MAX],int comb_score[MAX],int movie_no,int dow,int temp_screen)
{int i,j;
    int temp[MAX],output[MAX],ind,val,run_time[MAX];
    for( i=0;i<(total_screen-temp_screen);i++)
    {
        ind=mapint[i];
        runtime(comb_score,run_time,movie_no,dow);
        val=run_time[ind];
        //printf("val %d",val);
        for( j=0;j<ROWS;j++)
        {
            temp[j]=aggval[i][j];
        }
        /*printf("\n");
        for(int j=0;j<ROWS;j++)
        {
            printf("t %d",temp[j]);
        }*/
        list2rank(temp,5,output);
        printf("\n");
        /*for(int j=0;j<ROWS;j++)
        {
            printf("o %d",output[j]);
        }*/
        for (j=0;j<(total_screen-temp_screen);j++)
        {
            binarr[i][j]=0;
        }
        for ( j=0;j<val;j++)
        {
            int indc=output[j];
            binarr[i][indc]=1;
        }
    }
    printf("\n");
    for (i=0;i<(total_screen-temp_screen);i++)
    {
        for(j=0;j<COLS;j++)
        {
            printf("\t%d",binarr[i][j]);
        }
        printf("\n");
    }
}

//display the schedule in a text file

void display_file(int binarr[MAX][MAX],float slot[ROWS][3],int mapint[MAX], char name_arr[MAX][MAX],int temp_screen,int movie_no,char new_movie_arr[MAX][MAX],int count,int k)
{
    days day;
    char *dayn[]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	FILE *fp;
	fp = fopen("movie_schedule.txt","a");

    int temp,i,j;
    //fprintf(fp,"file displaying!!");
    //fprintf(fp,"A WEEK'S SCHEDULE FOR THE MULTIPLEX\n\n'");
    fprintf(fp,"\n");

    fprintf(fp,"\n%s\n",dayn[k]);
    for(i=0;i<(total_screen-temp_screen);i++)
    {

        fprintf(fp,"\n SCREEN %d",i+1);
        temp=mapint[i];

        fprintf(fp,"\t%s",name_arr[temp]);
        fprintf(fp,"\n");
        float  arr[5][3]={{(9+((i)*0.05)),(12+((i)*0.05)),5},
                {(12+(i)*0.05),(3+(i)*0.05),3},
                {(3+(i)*0.05),(6+(i)*0.05),2},
                {(6+(i)*0.05),(9+(i)*0.05),1},
                {(9+(i)*0.05),(12+(i)*0.05),4}};
        for( j=0;j<COLS;j++)
        {
            if (binarr[i][j]==1)
            {

                fprintf(fp,"\t %0.2f - %0.2f.pm ",arr[j][0],arr[j][1]);
                fprintf(fp,"\n");
            }
            else if(binarr[i][j]==0 && movie_no>total_screen && temp_screen<1 && count<movie_no)
            {


                fprintf(fp,"%s \t %0.2f - %0.2f.pm",new_movie_arr[count],arr[j][0],arr[j][1]);
			}

        }
        count++;
    }
    fprintf(fp,"*********************");
    fclose(fp);
}








void display(int binarr[MAX][MAX],float slot[ROWS][3],int mapint[MAX], char name_arr[MAX][MAX],int temp_screen,int movie_no,char new_movie_arr[MAX][MAX],int count)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //printf("%d",count);
    int temp,i,j;
    printf("\n");
    for( i=0;i<(total_screen-temp_screen);i++)
    {SetConsoleTextAttribute(hConsole,14+(0*30));
	
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_INTENSITY);
     //SetConsoleTextAttribute(hConsole,FOREGROUND_YELLOW|BACKGROUND_BLACK);
        printf("\n SCREEN %d",i+1);
        printf("\n");
        temp=mapint[i];
        if(movie_no<total_screen)
        {
            printf("\t%s",name_arr[temp]);
            printf("\n");
        }
        float  arr[5][3]={{(9+((i)*0.05)),(12+((i)*0.05)),5},
                {(12+(i)*0.05),(3+(i)*0.05),3},
                {(3+(i)*0.05),(6+(i)*0.05),2},
                {(6+(i)*0.05),(9+(i)*0.05),1},
                {(9+(i)*0.05),(12+(i)*0.05),4}};
        for( j=0;j<COLS;j++)
        if(j==0){
        	
		 if (binarr[i][j]==1)
            {
                if(movie_no<total_screen)
                {
                    printf("\t %0.2f.am - %0.2f.pm ",arr[j][0],arr[j][1]);
                    printf("\n");
                }
                if(movie_no>=total_screen)
                {
                    printf("%s \t %0.2f.am - %0.2f.pm ",name_arr[temp],arr[j][0],arr[j][1]);
                    printf("\n");
                }
            }
            if(binarr[i][j]==0 && movie_no>total_screen && count<=movie_no)
            {
                printf("%s \t %0.2f.am - %0.2f.pm",new_movie_arr[count],arr[j][0],arr[j][1]);
                printf("\n");
            }
       	
		}
		else{
		 
        {
            if (binarr[i][j]==1)
            {
                if(movie_no<total_screen)
                {
                    printf("\t %0.2f - %0.2f.pm ",arr[j][0],arr[j][1]);
                    printf("\n");
                }
                if(movie_no>=total_screen)
                {
                    printf("%s \t %0.2f - %0.2f.pm ",name_arr[temp],arr[j][0],arr[j][1]);
                    printf("\n");
                }
            }
            if(binarr[i][j]==0 && movie_no>total_screen && count<=movie_no)
            {
                printf("%s \t %0.2f - %0.2f.pm",new_movie_arr[count],arr[j][0],arr[j][1]);
                printf("\n");
            }
        }
        }
        count++;
    }
}
void occupancy_calc(int combscore[50],float slot[5][3],int aggval[50][5],int mapint[50],int temp_screen)
{
    int dow,i,j,k;
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    dow=stime.wDayOfWeek;
    int moviefactor,slot_scores;
    //printf("%d",total_screen);
    for(i=0;i<(total_screen-temp_screen);i++)
    {
        j=mapint[i];
        //printf("\n %d",i);
        moviefactor=combscore[j];
        //printf("\n \t j%d",j);
        //printf("\n mf %d",moviefactor);
        for( k=0;k<5;k++)
        {
            //printf("\n hi %d\n",k);
            slot_scores=(6-((slot[k][3])))*10;
            if (1<=dow<=4)
                slot_scores+=1;
            else if(dow==5 || dow==6 || dow==0)
                slot_scores+=10;
            aggval[i][k]=(moviefactor+slot_scores)*0.625;
            //printf("c2 %d",i);
            //printf("\t o%d",aggval[i][k]);
        }
    }
    printf("\n");
    for( i=0;i<(total_screen-temp_screen);i++)
    {
        for( j=0;j<5;j++)
        {
            printf("\t%d",aggval[i][j]);
        }
        printf("\n");
    }
}
void mapping(int total_screen,int movienum,char movie_lst[50][50],int movie_screen[50],int mapint[50])
{
    int i=0,j=0,k;
    int count=movie_screen[j];
    while(j<movienum)
    {
        while(i<count)
        {
            //strcpy(maparr[i],movie_lst[j]);
            //printf("\n%d",j);
            mapint[i]=j;
            i++;
            //printf("\t m%d",mapint[i]);
        }
        j++;
        count=count+movie_screen[j];
    }

    /*for(k=0;k<total_screen;k++)
        printf("m%d",mapint[k]);*/
}
void sort(char m_name[MAX][MAX],int score[MAX],int N,char nm_name[MAX][MAX])
{
  int i, j, temp1,temp2,rank_movies[MAX];
  list2rank(score,N,rank_movies);
  for( i=0;i<N;i++)
  {
      temp2=rank_movies[i];
      strcpy(nm_name[i],m_name[temp2]);
  }
  for (i = 0; i < N-1; ++i)
  {
    for (j = i + 1; j < N; ++j)
    {
        if (score[i] < score[j])
        {
        temp1 = score[i];
        score[i] = score[j];
        score[j] = temp1;
        }
    }
  }
    return;
}
void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,12+(0*16));
	
	
	
    int date_rel,month_rel,year_rel,demand,map_int[MAX],aggval[MAX][COLS],dow,schedule_arr[MAX][MAX],rankcombarr[MAX];
    char movie_arr[MAX][MAX],map_arr[MAX][MAX];
    int i,j,movie_to_screen[MAX],movie_no,screens,comb_arr[MAX];
    printf("\t\t\t\tMULTIPLEX MOVIES SCHEDULER\n\n\nDETAILS>>>\n\n");
    printf("\nAccomodation details of the multiplex>>>\n\n\n");
    printf("Enter number of screens in the multiplex : ");
    scanf("%d",&total_screen);
    printf("\nEnter capacity of each screen : ");
    scanf("%d",&total_capacity);
    printf("\nMovies details>>>\n");
    printf("\nEnter number of movies : ");
    scanf("%d",&movie_no);
    int temp_screen=total_screen;
    for(i=0;i<movie_no;i++)
    {
            printf("\nEnter movie name %d : ",i+1);
            scanf("%s",movie_arr[i]);
            printf("\n\tEnter release date (dd/mm/yy): ");
            scanf("%d/%d/%d", &date_rel,&month_rel,&year_rel);
            int popularity_score;
            popularity_score=popularity();
            printf("\n\tThe popularity score calculated based on movie rating is:%d",popularity_score);
            demand=demand_calc(date_rel,month_rel,year_rel,screens);
            comb_arr[i]=(demand+popularity_score)*0.83;
            printf("\n\n");

    }
    char new_movie_arr[MAX][MAX];
    sort(movie_arr,comb_arr,movie_no,new_movie_arr);
    //for(int i=0;i<movie_no;i++)
    //{
        //printf("combined scores %s",movie_arr[i]);
    //}
    int new_comb_arr[MAX];
    //list2rank(comb_arr,movie_no,)
    for( i=0;i<movie_no;i++)
    {
        movie_to_screen[i]=screen_show(demand,temp_screen,movie_no);
        //printf("\n%d",movie_to_screen[i]);
        temp_screen=temp_screen-movie_to_screen[i];
        //printf("\n%d",demand);
        //printf("\n%d",temp_screen);
        //printf("\n%d  %d",demand,popularity_score);
    }

    //for(int i=0;i<movie_no;i++)
    //{
        //printf("combined scores %d",comb_arr[i]);
    //}
    int count;
    for ( j=0;j<movie_no;j++)
    {
        printf("\n name of movie : %s   number of screens allotted : %d",new_movie_arr[j],movie_to_screen[j]);
        if (movie_to_screen[j]==0)
            count++;
    }
    mapping(total_screen-temp_screen,movie_no,new_movie_arr,movie_to_screen,map_int);
    float slot_timing[ROWS][3];
    //SYSTEMTIME stime;
    //GetSystemTime(&stime);
    //dow=stime.wDayOfWeek;
    for(dow=0;dow<DOW;dow++)
    {
        slot_generation(dow,slot_timing,temp_screen);
        occupancy_calc(comb_arr,slot_timing,aggval,map_int,temp_screen);
        bin_scheduler(aggval,schedule_arr,map_int,comb_arr,movie_no,dow,temp_screen);
        display(schedule_arr,slot_timing,map_int,new_movie_arr,temp_screen,movie_no,new_movie_arr,count);
    }
    
    //display_file(schedule_arr,slot_timing,map_int,new_movie_arr,temp_screen,movie_no,new_movie_arr,count);

    //}
    for( dow=0;dow<DOW;dow++){

    slot_generation(dow,slot_timing,temp_screen);
    occupancy_calc(comb_arr,slot_timing,aggval,map_int,temp_screen);
    bin_scheduler(aggval,schedule_arr,map_int,comb_arr,movie_no,dow,temp_screen);
    display_file(schedule_arr,slot_timing,map_int,new_movie_arr,temp_screen,movie_no,new_movie_arr,count,dow);
	}
}

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#define TEAM_SIZE 10
#define DRAFT_SIZE TEAM_SIZE*TEAM_SIZE
#define PARTA 1
#define PARTB 1
/**************** Your Code Goes Here ******************/

struct Player
{
    int offense;
    int defense;
    int number;
};

struct Team
{
    struct Player players[10];
    char name[80];
};

void initPlayers(struct Player players[], int size) {
    // seed the srand with time...
    srand(time(0));

    // remove garbage
    for (int i = 0; i < size; i++) {
        players[i].number = 0;
        players[i].defense = 0;
        players[i].offense = 0;
    }
    for (int i = 0; i < size; i++) {
        players[i].offense = rand();
        players[i].defense = rand();
        int done = 0;
        // loop until got new player
        while (!done) {
            // get random between 1-100
            int play_no = (rand() % (100)) + 1;   // rand 1 to 100
            // visit all players assign 
            for (int j = 0; j <= i; j++) {
                // if made it to end then okay to add
                if (i == j) {
                    players[i].number = play_no;
                    done = 1;
                    break;
                }
                // if found a duplcate try again with new random number
                if (players[j].number == play_no) {
                    // found duplicate, break but not done...
                    break;
                }
            }
        }
    }
}

struct Team draftTeam(char name[], struct Player draft[],int team_size) {
    struct Team league;
    for (int i = 0 ; i < team_size ; i++) {
        for (int j= 0 ; j < DRAFT_SIZE ; j++) {
            if (draft[j].number!=-1) {
                league.players[i].offense=draft[j].offense;
                league.players[i].defense=draft[j].defense;
                league.players[i].number=draft[j].number;
                draft[j].number=-1;
                break;
            }
        }
    }
    stpncpy(league.name,name,80);
    return league;
}


/**************** Do not touch anything after this comment *************/

int main(){
    srand(time(0));
#if PARTA
    ///////// PART A Tests /////////
    printf("\n\t======= Verifying Player Struct...\n\n");
    int player_num = 0;
    struct Player p1 = {rand()%TEAM_SIZE+1, rand()%TEAM_SIZE+1, player_num++};
    struct Player p2 = {rand()%TEAM_SIZE+1, rand()%TEAM_SIZE+1, player_num++};
    if(p1.offense > p2.defense){
        printf("\nPlayer%d wins with %d offense", p1.number, p1.offense);
        printf(" over Player%d's %d defense.\n", p2.number, p2.defense);
    }else if(p2.offense > p1.defense){
        printf("Player%d wins with %d offense", p2.number, p2.offense);
        printf(" over Player%d's %d defense.\n", p1.number, p1.defense);
    }else{
        printf("Player%d and Player%d tie the match.\n", p1.number, p2.number);
    }
    printf("\n\t...Passed =======\n\n");
    printf("\n\t======= Verifying Team Struct...");
    struct Team t1;
    for(int j = 0; j < 80; j++) t1.name[j] = '\0';
    for(int i = 0; i < TEAM_SIZE; i++){
        //this tests that you have player objects inside your team players array.
        //'total' is a nonsensical throwaway value.
        int total = t1.players[0].offense + t1.players[0].defense + t1.players[0].number;
    }
    printf("Passed =======\n\n");
#endif
#if PARTB
    ///////// PART B TESTS /////////
    printf("\n\t======= Single League Team Initialization...");

    struct Player draft[DRAFT_SIZE];
    initPlayers(draft, DRAFT_SIZE);
    struct Team league[TEAM_SIZE];
    league[0] = draftTeam("Prime", draft, TEAM_SIZE);
    int last_total = 0, counter = 0;
    for(int i = 0; i < TEAM_SIZE; i++){
        int total = league[0].players[i].offense + league[0].players[i].defense + league[0].players[i].number;
        if(total == last_total){
            counter++;
        }
        last_total = total;
    }

    printf("Passed =======\n\n");
    printf("\n\t======= Multiple League Team Initialization...");

    for(int i = 1; i < TEAM_SIZE; i++){
        league[i] = draftTeam("Prime", draft, TEAM_SIZE);
        int last_total = 0, counter = 0;
        for(int j = 0; j < TEAM_SIZE; j++){
            int total = league[i].players[j].offense + league[i].players[j].defense + league[i].players[j].number;
            if(total == last_total){
                counter++;
            }
            last_total = total;
        }
        assert(counter <= 3);
    }

    printf("Passed =======\n\n");
    printf("\n\t======= Verifying all players were drafted...");

        int t = -1;
        for(int j = 0; j < DRAFT_SIZE; j++){
            assert(draft[j].number == -1);
            if(j % 10 == 0) t++;
            assert(league[t].players[j%10].number != -1);
        }

    printf("Passed =======\n\n");
    printf("\n\tAll Tests Passed! \nMake sure to push to Github and submit your hash on MyCourses!\n\n");
#endif
}

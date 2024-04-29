#include <stdio.h>
#include <stdlib.h>

int get_vote(int);
int** incr_array(int**, int);
void print_histograms(int, int[7][3], int);

int main(int argc,char** argv){
    
    FILE* fp = fopen("votes.dat","r");
    
    unsigned short int tmp;

    // Is the binary 1111111000000000. For age we want to get only the first 7 digits
    unsigned short int age_mask = 0xfe00;

    // Is the binary 0000000110000000. For gender we want to get the 2 middle digits
    unsigned short int gender_mask = 0x180;

    // Is the binary 0000000001111111. For vote we want to get the last 7 digits
    unsigned short int vote_mask = 0x4f;

    int num_of_votes = 0;
    int** arr;
    int candidate_votes[7][3];
    int candidate_age_stats[7][4];
    for(int i=0; i<7; i++){
        candidate_votes[i][0] = 0; // Male
        candidate_votes[i][1] = 0; // Female
        candidate_votes[i][2] = 0; // Other
        candidate_age_stats[i][0] = 0; // Ages 18-29
        candidate_age_stats[i][1] = 0; // Ages 30-44
        candidate_age_stats[i][2] = 0; // Ages 45-59
        candidate_age_stats[i][3] = 0; // Ages 60 and above
    }

    // Data Input
    while(fscanf(fp,"%hx\n",&tmp) != EOF){
        // We shift the digits show we get the proper decimal number
        int age = (tmp & age_mask) >> 9;
        int gender = (tmp & gender_mask) >> 7;
        int vote = get_vote(tmp & vote_mask);
        // printf("Age: %d, Gender: %d, Voted: %d\n", age, gender, vote);

        // Saving Age Gender and Vote to voter's array after incrementing it by 1 row
        arr = incr_array(arr,num_of_votes);
        arr[num_of_votes][0] = age;
        arr[num_of_votes][1] = gender;
        arr[num_of_votes][2] = vote;
        num_of_votes++;

        // Counting candidate votes and age statistics
        if(vote >= 0 && vote <= 6)
            if(age >= 18 && age <= 100)
                if(gender != 0){
                    candidate_votes[vote][gender-1]++;
                    if(age >= 18 && age <= 29)
                        candidate_age_stats[vote][0]++;
                    else if(age >= 30 && age <= 44)
                        candidate_age_stats[vote][1]++;
                    else if(age >= 45 && age <= 59)
                        candidate_age_stats[vote][2]++;
                    else
                        candidate_age_stats[vote][3]++;
                }

    }

    int max_votes[4];
    max_votes[0] = 0; // Total
    max_votes[1] = 0; // Men
    max_votes[2] = 0; // Women
    max_votes[3] = 0; // Other
    
    int top_voted[4]; // Top voted person 0.Total 1.Men 2.Women 3.Other

    int ages[4]; // sum of ages
    ages[0] = 0; // 18-29
    ages[1] = 0; // 30-44
    ages[2] = 0; // 45-59
    ages[3] = 0; // 60-above

    int top_neolea = 0;
    int top_neolea_voted; // Speaks for its self
    int top_girea = 0;
    int top_girea_voted;

    // Counting Votes
    for(int i=0; i<7; i++){
        int total_votes = candidate_votes[i][0] + candidate_votes[i][1] + candidate_votes[i][2];
        int neolea_votes = candidate_age_stats[i][0] + candidate_age_stats[i][1];
        int girea_votes = candidate_age_stats[i][2] + candidate_age_stats[i][3];
        
        if(neolea_votes > top_neolea){
            top_neolea = neolea_votes;
            top_neolea_voted = i;
        }
        if(girea_votes > top_girea){
            top_girea = girea_votes;
            top_girea_voted = i;
        }
        
        
        if(total_votes > max_votes[0]){
            max_votes[0] = total_votes;
            top_voted[0] = i;
        }

        for(int j=0; j<4; j++){
            if(candidate_votes[i][j] > max_votes[j+1]){
                max_votes[j+1] = candidate_votes[i][j];
                top_voted[j+1] = i;
            }
        }
        
        // Counting total ages
        for(int j=0; j<4; j++)
            ages[j] += candidate_age_stats[i][j];

        // Histograms
        print_histograms(total_votes, candidate_votes, i);
        
    }


    // for(int i=0; i<7; i++){
    //     printf("Candidate %d got %d Male votes, %d Female votes, %d Other votes\n",i,candidate_votes[i][0],candidate_votes[i][1],candidate_votes[i][2]);
    // }
    printf("--------------------\n");
    printf("Candidate with most Votes is %d and has %d votes.\n",top_voted[0],max_votes[0]);
    printf("Candidate with most Male Votes is %d and has %d votes.\n",top_voted[1],max_votes[1]);
    printf("Candidate with most Female Votes is %d and has %d votes.\n",top_voted[2],max_votes[2]);
    printf("Candidate with most Other Votes is %d and has %d votes.\n",top_voted[3],max_votes[3]);
    printf("--------------------\n");

    printf("Voters with age 18-29: %d\n",ages[0]);
    printf("Voters with age 30-44: %d\n",ages[1]);
    printf("Voters with age 45-59: %d\n",ages[2]);
    printf("Voters with age 60 and above: %d\n",ages[3]);
    printf("--------------------\n");

    printf("Top candidate with most votes from neolea is %d with total votes %d\n",top_neolea_voted,top_neolea);
    printf("Top candidate with most votes from girea is %d with total votes %d\n",top_girea_voted,top_girea);
    printf("--------------------\n");


    free(*arr);
    free(arr);
    fclose(fp);
    return 
    0;
}

void print_histograms(int total_votes, int candidate_votes[7][3], int i){
    // Total Votes
    printf("Candidate %d: ",i);
    for(int j=0; j<total_votes; j++)
        printf("*");
    
    // Gender Votes
    printf("\nMale\t: ");
    for(int j=0; j<candidate_votes[i][0]; j++)
        printf("*");
    printf("\nFemale\t: ");
    for(int j=0; j<candidate_votes[i][1]; j++)
        printf("*");
    printf("\nOther\t: ");
    for(int j=0; j<candidate_votes[i][2]; j++)
        printf("*");
    printf("\n");
}

int** incr_array(int** arr, int voters){
    // Creating new array
    int** tmp = (int**)malloc((voters+1)*sizeof(int*));
    for(int i=0; i<voters+1; i++)
        tmp[i] = (int*)malloc(3*sizeof(int));
    
    // Saving data to new array
    for(int i=0; i<voters; i++)
        for(int j=0; j<3; j++)
            tmp[i][j] = arr[i][j];
    
    // On first call fo incr_array no votes have been made so arr hasn't been allocated
    if(voters > 0){
        for(int i=0; i<voters; i++)
            free(arr[i]);
        free(arr);
    }

    // Returning new array
    return tmp;
}

int get_vote(int vote){
    switch(vote){
        case 0:
            return -1; // Voted blank
        case 1:
            return 0;
        case 2:
            return 1;
        case 4:
            return 2;
        case 8:
            return 3;
        case 16:
            return 4;
        case 32:
            return 5;
        case 64:
            return 6;
        default:
            return 999; // Voted more than 1 candidate
    }
}  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define GRAY 'w'
#define YELLOW 'y'
#define GREEN 'g'


double best_entropy = 0;
char best_word[6];

struct word_struct{
    int no;
    char structure[7];
};


void display_Struct(struct word_struct *wd_str,int number_of_structures){
    int s = 0;
    // daca i e 0 arata ceva dubios
    for(int i=0;i< number_of_structures;i++){
        printf("%s -- %d\n",wd_str[i].structure,wd_str[i].no);
        s+= wd_str[i].no;
    }
    printf("Total struturi: %d\n",s);
    printf("\n\n");
}


void display_good_words(struct word_struct *wd_str){
    int s = 0;
    // daca i e 0 arata ceva dubios
    for(int i=1;i<= 11454;i++){
        if( wd_str[i].no == 1){
            printf("%s",wd_str[i].structure);
            s+= wd_str[i].no;

        }
    }
    printf("Total struturi: %d\n",s);
    printf("\n\n");
}

void increase(struct word_struct* wd_str,int* number_of_structures, char structure[6]){

    for(int i = 0;i <= *number_of_structures;i++){
        if (strcmp(wd_str[i].structure,structure)== 0){
            ++wd_str[i].no ;
            return;
        }
    }

    wd_str[++(*number_of_structures)].no = 1;
    strcpy(wd_str[(*number_of_structures)].structure,structure);
    return;

}

int letter_in(char *word,char letter){
    for(int i=0;i<5;i++){
        if(letter == word[i]){
            return 1;
        }
    }

    return 0;
}

void make_struct(char *base_word,char *given_word, char *result){
    for(int i=0;i<5;i++){
        if( base_word[i] == given_word[i]){
            result[i] = GREEN;
        }
        else {
                if( letter_in(base_word,given_word[i])){
            result[i] = YELLOW;
    }
            else{
                result[i] = GRAY;
            }
        }
    }
}

double Entropy(struct word_struct all_words[],int no_of_words, char* word){

//    FILE *f = fopen(filename,"r");

    struct word_struct structures[243];
    int number_of_structures = -1;


    char structure[6] = {GRAY,GRAY,GRAY,GRAY,GRAY};
    char word_read[7];


//    while(fgets(word_read,7,f)!= NULL){
    for(int i=0; i< no_of_words;i++){
//        make_struct(word_read,word,structure);
        make_struct(all_words[i].structure,word,structure);
//        printf("Citit: %s -- STructura: %s\n",word_read,structure);
        increase(structures,&number_of_structures,structure);
//        fgets(word_read,1,f);
    }
    double entropy = 0.0;
    for(int i=0; i< number_of_structures-1;i++){
        double probability = (double)structures[i].no/no_of_words;
//        printf("%d %d\n",structures[i].no,no_of_words);
        entropy += probability*log2l(probability);
    }

//    display_Struct(structures,number_of_structures);

//    fclose(f);
    return -entropy;

}

void read_words(const char* filename,struct word_struct *all_words){

    FILE *f = fopen(filename,"r");

    char word_read[7];
    int i=0;
    while(fgets(word_read,7,f)!= NULL){
        all_words[i].no = 1;
        strcpy(all_words[i].structure,word_read);
        i++;
    }

    fclose(f);
}

void find_best_world(struct word_struct *all_words,int no_of_words){
    best_entropy = 0;
    for(int i=0;i<no_of_words;i++){
        double current_entropy = Entropy(all_words,11454,all_words[i].structure);
        if(current_entropy>best_entropy && all_words[i].no == 1){
            best_entropy = current_entropy;
            strcpy(best_word,all_words[i].structure);
        }
    }
}


void check_letters(struct word_struct *all_words,int* no_of_words,char *structure){

    int copy = *no_of_words,good;

    for(int i =0;i< copy;i++){
        good = 1;
        for(int j=0;j<5;j++){
            if (structure[j] == GREEN && all_words[i].structure[j] != best_word[j]){

                all_words[i].no = 0;
                good = 0;
            }
            else{ if(structure[j] == YELLOW && !letter_in(all_words[i].structure,best_word[j]) && all_words[i].structure[j] != best_word[j]){
                all_words[i].no = 0;
                good = 0;
                }
                else {if( structure[j] == GRAY && letter_in(all_words[i].structure,best_word[j])){
                    all_words[i].no = 0;
                    good = 0;
                }
                    else{
//                        printf("%s\n",all_words[i].structure);
                    }
                }
            }

        }
        if (good == 0){
                --*no_of_words;
            }
    }
}

void clear_array(struct word_struct *all_words){

//    display_Struct(all_words,11454);
    int j=0;
    for(int i=0;i<11452;++i){
        if( all_words[i].no == 0){

            while( all_words[i].no == 0 && i<11454){i++;}
//            printf("%d\n",all_words[i].structure[0]);
            printf("%d\n",i);
            all_words[i].no = 0;
            j++;


        }
    }
    printf("%d\n",j);
}

int main()
{
    FILE *f = fopen("cuvinte.txt","r");

    struct word_struct all_words[11454];
    int no_of_words = 11454;
    read_words("cuvinte.txt",all_words);

    time_t start = time(NULL);


//    find_best_world(all_words,no_of_words);

    strcpy(best_word,"TAREI");
    char given_word[6],structure[6];
    strcpy(given_word,"TUREI");

//    for(int i=0;i<4;i++){
//
//        make_struct(given_word,best_word,structure);
//        check_letters(all_words,&no_of_words,structure);
//        //display_good_words(all_words);
//        find_best_world(all_words,11454);
//
//        printf("STRUCTURA: %s \n",structure);
//        printf("CUVANTUL ALES: %s -- BEST WORD: %s\n",given_word,best_word);
//        printf("No: %d\n",no_of_words);
//    }
    check_letters(all_words,&no_of_words,"gwggg");
    clear_array(all_words);
//    display_Struct(all_words,11454);

//    display_good_words(all_words);
    //display_Struct(all_words,11453);


//    display_Struct(all_words,11453);
//    Entropy(all_words,no_of_words,"TAREI");

//    printf("%s -- %Lf\n",best_word,best_entropy);
    printf("A durat sa ruleze: %d secunde\n",(time(NULL)-start));

    fclose(f);
    return 0;
}

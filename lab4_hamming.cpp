//
//  main.cpp
//  wireless_network
//
//  Created by 林憶萱 on 2019/10/3.
//  Copyright © 2019年 林憶萱. All rights reserved.
//

#include <iostream>
#include <vector>
#include <random>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <bitset>
#include <cstdlib> /* 亂數相關函數 */
#include <ctime>
#include <fstream>

using namespace std;

void random_data (vector<int> &original_code){
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0,1);
    
    for (int i=0; i<original_code.size(); ++i){
        original_code[i]=dis(gen);
    }
}//genetate 1K data - OK

void Dem_to_bin(int num,vector<int>&check){
    for (int i = check.size()-1; i>=0; i--) {
        check[i] = num%2;
        num = num/2;
    }
    /*cout<< "check bits  ： ";
    for (int i =0; i<check.size(); i++) {
        cout << check[i];
    }
    cout<<endl;*/
}

void hamming_encode(vector<int> orginal_code,vector<int>&encod_code,vector<int>&check_position,vector<int>&check_pre){
    
    vector<int> check_bit(encod_code.size()-orginal_code.size());
    
    //finding postion of redundant bits
    int j = 0, k =1 ;
    
    for(int i = 0; i<check_position.size();i++){
        if(i==pow(2,j)){
            check_position[i-1] = -1;//-1 is intital value of redundant bits//vect2 = hamming
            j++;
            //cout<< "j: "<<j << "    i " <<i<<endl;
        }
        else{
            check_position[i] = 0; // vect1 = data_1k
            k++;
        }
    }
    //encoded hamming code(no check bit)
    int x=0;
    for (int i = 0; i<encod_code.size(); i++) {
        if(check_position[i]==0){
            encod_code[i]=orginal_code[x];
            x++;
        }
    }
    //calculate check bit
    int y =0;
    for (int i =0; i<encod_code.size(); i++) {
        if(encod_code[i]==1){
            y = y^(i+1);
        }
    }
    
    Dem_to_bin(y,check_bit);
    //cout <<"y = "<<bitset<4>(y)<<endl;
    
    //final add check bit + data bit
    int z=0;
    for (int i =0; i<encod_code.size(); i++) {
        if(check_position[i]==-1){
            encod_code[i] = check_bit[z];
            z++;
        }
    }
    
    
}//origanal code+check bit = hamming code//check postion-1 put redundancy position

void ruin_data(vector<int> Hamming_code,vector<int>&Defect_code,int num_ruin){
   // srand( time(NULL) );
    /* 指定亂數範圍 */
    int min = 0;
    unsigned long int max = Hamming_code.size();
    
    for (int j =0; j< Hamming_code.size(); j++) {
        Defect_code[j] = Hamming_code[j];
    }
    
    for (int i=0; i<num_ruin; i++) {
        int x = rand() % (max - min + 1) + min;/* 產生 [min , max] 的整數亂數 */
        Defect_code[x] = (!Hamming_code[x]);
        //cout << "wrong bit : " <<11<<endl;
    }

}


void detect_hamming_correct(vector<int>&hdata,vector<int>&redundant_position,int NumofCheck){
    vector<int> data_bit(hdata.size()-NumofCheck);
    vector<int> check_bit(NumofCheck);
    
    //find check bit and data bit
    int a=0,b=0;
    for (int i =0; i<hdata.size(); i++) {
        if (redundant_position[i] == 0) {
            data_bit[a] = hdata[i];
            a++;
        }
        else if(redundant_position[i] == -1) {
            check_bit[b]=hdata[i];
            b++;
        }
    }
    
    //check
    /*cout<< "Data Bit :"<<endl;
    for (int i=0; i<data_bit.size(); ++i){
        cout<<data_bit[i]<< " ";
    }
    cout<<endl;
    
    cout<< "Check Bit :"<<endl;
    for (int i=0; i<check_bit.size(); ++i){
        cout<<check_bit[i]<< " ";
    }
    cout<<endl;*/
    
    //data bit XOR check bit
    int compare = 0;
    for (int i =0; i<hdata.size(); i++) {
        if (redundant_position[i]==0) {
            if (hdata[i]==1) {
                compare = compare^(i+1);
            }
        }
        
    }
    //cout << "data bit(XOR): "<<compare <<endl;
    
    //check bit + data bit(XOR)
    int C_num =0;
    //cout<<"C_num : ";
    for (int i=0;i<NumofCheck;i++) {
        if (check_bit[i]==1) {
            C_num = C_num+pow(2, NumofCheck- i-1);
            //cout<<pow(2, i);
        }
    }
    //cout<<endl;
    C_num = C_num^compare;
    
    //cout<<"check bit(XOR) : "<<C_num<<endl;
    
    if (C_num !=compare) {
        hdata[C_num-1]=(hdata[C_num-1]+1)%2;
    }
    /*check
    cout<< "fix Code :"<<endl;
    for (int i=0; i<hdata.size(); ++i){
        cout<<hdata[i]<< " ";
    }
    cout<<endl;*/

    
}

void decode(vector<int>Hamming,vector<int>redundant_position,vector<int>&Decode_data){
    int j=0;
    for (int i=0; i<Hamming.size(); i++) {
        if (redundant_position[i] == 0) {
            Decode_data[j]=Hamming[i];
            j++;
        }
    }
}//check ok

void compare_ori_decode(vector<int> origin,vector<int>&decode){
    int count=0;
    for (int i=0; i<origin.size(); i++) {
        if (origin[i]!=decode[i]) {
            count++;
        }
    }
    
    if (count == 0) {
        cout<<"Correct!"<<endl;
    }
    else
        cout<<"Not correct!"<<" "<<"number of bit(s) error detected: "<<count<<endl;
}

////////////////Main///////////////

int main(){
    // ofstream myfile;
   // myfile.open ("example.txt");
    
    vector<int> original_code (1024);
    int NumofCheckbit=0;
    while(pow (2,NumofCheckbit) < original_code.size() + NumofCheckbit + 1)
        NumofCheckbit++;
    //cout<<"No. of check bits= "<<NumofCheckbit<<endl;
    
    vector<int> encoded_code (original_code.size()+NumofCheckbit);
    vector<int> defected_code (encoded_code.size());
    vector<int> decoded_code (original_code.size());
    vector<int> checkbit_postion(encoded_code.size());
    vector<int> check_bit(encoded_code.size()-original_code.size());
    
    random_data(original_code);
    //check - OK
    cout<< "Original Code :"<<endl;
    for (int i=0; i<original_code.size(); ++i){
        cout<<original_code[i]<< " ";
    }
    cout<<endl;
    
    hamming_encode(original_code, encoded_code, checkbit_postion,check_bit);
    
    /*check - OK
    cout<< "redundant position(-1): ";
    for (int i =0; i<checkbit_postion.size(); i++) {
        cout<<  checkbit_postion[i] << " ";
    }
    cout <<endl;*/
    
    cout<< "Encoded Code :"<<endl;
    for (int i=0; i<encoded_code.size(); ++i){
        cout<<encoded_code[i]<< " ";
    }
    cout<<endl;
    
    ruin_data(encoded_code,defected_code, 1);
    
    //check
    cout<< "Defective Code :"<<endl;
    for (int i=0; i<defected_code.size(); ++i){
        cout<<defected_code[i]<< " ";
    }
    cout<<endl;
    
    
    detect_hamming_correct(defected_code, checkbit_postion, NumofCheckbit);
    
    decode(defected_code, checkbit_postion,decoded_code);
    
    //check
    cout<< "Decoded code :"<<endl;
    for (int i=0; i<decoded_code.size(); ++i){
        cout<<decoded_code[i]<< " ";
    }
    cout<<endl;
    
    compare_ori_decode(original_code,decoded_code);
    
    
    
}

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

using namespace std;

void random_data(vector<int> &vect){
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0,1);
    
    for (int i=0; i<vect.size(); ++i){
        vect[i]=dis(gen);
        //cout<< vect[i]<< " ";
    }
}//OK

void demtobin(int num,vector<int> &check){
    for (int i = check.size()-1; i>=0; i--) {
        check[i] = num%2;
        num = num/2;
    }
    cout<< "check bits  ： ";
    for (int i =0; i<check.size(); i++) {
        cout << check[i];
    }
    cout<<endl;
}


void hamming_code(vector<int> &vect1,vector<int> &vect2,vector<int>&hamming_bit){
    //finding postion of redundant bits
    int j = 0, k =1 ;
    //vector<int> hamming_bit(vect2.size());
    vector<int> check_bit(vect2.size()-vect1.size());
    
    for(int i = 0; i<hamming_bit.size();i++){
        if(i==pow(2,j)){
            hamming_bit[i-1] = -1;//-1 is intital value of redundant bits//vect2 = hamming
            j++;
            //cout<< "j: "<<j << "    i " <<i<<endl;
        }
        else{
            hamming_bit[i] = 0; // vect1 = data_1k
            k++;
        }
    }
    
    /*check
    cout<< "redundant position(-1): ";
    for (int i =0; i<hamming_bit.size(); i++) {
        cout<<  hamming_bit[i] << " ";
    }
    cout <<endl;
    */
    
    //
    int x=0;
    for (int i = 0; i<vect2.size(); i++) {
        if(hamming_bit[i]==0){
            vect2[i]=vect1[x];
            x++;
        }
    }
    
    int y =0;
    for (int i =0; i<vect2.size(); i++) {
        if(vect2[i]==1){
            y = y^(i+1);
        }
    }
    
    demtobin(y, check_bit);
    //cout <<"y = "<<bitset<4>(y)<<endl;
    
    // final add check bit + data bit
    int z=0;
    for (int i =0; i<vect2.size(); i++) {
        if(hamming_bit[i]==-1){
            vect2[i] = check_bit[z];
            z++;
        }
    }
    
    
    /*check
    cout<<"Hamming code is : ";
    for(int i =0;i<vect2.size();i++)
        cout<<vect2[i]<<" ";
    cout<<endl;
   */
}

void detect_hamming_code(vector<int> &hdata,vector<int> &check_pre,int numofckeck){ // hdata = hamming code ,check_pre= find redundant position
    int a=0,b=0;
    vector<int> check_bit(numofckeck);//find ckeck bit
    vector<int> hamming_bit(numofckeck);//XOR bit
    //find check bit
    for (int i =0; i<hdata.size(); i++) {
        if(check_pre[i]==-1){
            check_bit[a] = hdata[i];
            a++;
        }
        else if (check_pre[i]==0){
            if(hdata[i] == 1)
                b = b^(i+1);
        }
    }
    
    demtobin(b, hamming_bit);
    
    //compare check bit and xor data bit
    int fault = 0;
    for (int i = 0 ; i<numofckeck; i++) {
        if (check_bit[i]!=hamming_bit[i]) {
            fault = fault + pow(2, i);
        }
    }
    
    // justify correct or not
    if (fault == 0)
        cout << "correct!"<<endl;
    else{
        hdata[fault]= (hdata[fault]+1)%2;
    }
    cout << "fault "<<fault <<endl;
    
    //ckeck
    //cout <<"b = "<<bitset<4>(b)<<endl;
    
    cout<<"check_pro_bit is : ";
    for(int i =0;i<check_bit.size();i++)
        cout<<hamming_bit[i]<<" ";
    cout<<endl;
    //
    
}

void linear_block_code(vector<int> vect){
    
}

void cyclic_code(vector<int> vect){
    
}

void ruin_data(vector<int> &vect,int num_ruin){
    std::random_device rd;
    std::default_random_engine gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0,vect.size());
    
    for (int i=0; i<num_ruin; ++i){
        vect[dis(gen)] = (vect[dis(gen)]+1)%2;
    }
    
    
}

int main() {
    
    vector<int> data_1k(7);
    int r = 0;
    
    while(pow (2,r) < data_1k.size() + r + 1)
        r++;
    cout<<"No. of check bits= "<<r<<endl;
    
    
    vector<int> hamming_data(data_1k.size()+r);
    random_data(data_1k);// random binary data
    vector<int> hamming_bit(hamming_data.size());
    
    
    //check data
    cout<< "random_data: " ;
    for (int i =0; i<data_1k.size(); i++) {
        cout<< data_1k[i] << " ";
    }
    cout<<endl;
    

    hamming_code(data_1k,hamming_data,hamming_bit);
    cout<< "hamming_data: " ;
    for (int i =0; i<hamming_data.size(); i++) {
        cout<< hamming_data[i] << " ";
    }
    cout<<endl;
    
    
    
    ruin_data(hamming_data, 1);
    
    //check
    cout<< "ruin_data: " ;
    for (int i =0; i<hamming_data.size(); i++) {
        cout<< hamming_data[i] << " ";
    }
    cout<<endl;
    
    detect_hamming_code(hamming_data,hamming_bit,r);
    
    
    return 0;
}


#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h> /* ¶Ã¼Æ¬ÛÃö¨ç¼Æ */
#include <time.h>   /* ®É¶¡¬ÛÃö¨ç¼Æ */
#include <string>
using namespace std;
int checking(vector<int> data);
void generate_data( vector<int> &data){
    srand( time(NULL) );
    for(int i=0;i<data.size();i++){

        data[i] = rand()%2;
        //cout << data[i];

    }
    cout << endl;
}
void encode( vector<int> &ori_data,vector<int> &encode_data){
    for(int i=0;i< (ori_data.size()/4);i++){
        string s ="";
        string codeword;
        for(int j=0; j<4; j++){
            encode_data[i*7+j] = ori_data[i*4+j];

            if( ori_data[i*4+j]==0)
                s+="0";
            else
                s+="1";
        }

        if (s=="0000")
            codeword = "000";
        else if (s=="0001")
            codeword = "011";
        else if (s=="0010")
            codeword = "110";
        else if (s=="0011")
            codeword = "101";
        else if (s=="0100")
            codeword = "111";
        else if (s=="0101")
            codeword = "100";
        else if (s=="0110")
            codeword = "001";
        else if (s=="0111")
            codeword = "010";
        else if (s=="1000")
            codeword = "101";
        else if (s=="1001")
            codeword = "110";
        else if (s=="1010")
            codeword = "011";
        else if (s=="1011")
            codeword = "000";
        else if (s=="1100")
            codeword = "010";
        else if (s=="1101")
            codeword = "001";
        else if (s=="1110")
            codeword = "100";
        else if (s=="1111")
            codeword = "111";

        for(int j=4; j<7; j++){
            if(codeword[j-4] == '0')
                encode_data[i*7+j] = 0;
            else
                encode_data[i*7+j] = 1;
        }

    }
}
void ruin( vector<int> &data){
    for(int i=0;i<data.size()/7;i++){
        if(rand()%10 == 0){
            int x = rand()%7;
            if(data[i*7+x]==0)
                data[i*7+x] = 1;
            else
                data[i*7+x] = 0;
            //cout << i*7+x << " " << x<< " Has been ruined.\n";
        }
    }
}


void restore_data( vector<int> ruined_data, vector<int> &decoded_data){
    for(int i=0;i<ruined_data.size()/7;i++){
        vector<int> check(7);
        for(int j=0; j<7; j++){

            check[j] = ruined_data[i*7+j];
        }
        for(int j=0;j<4;j++)
            decoded_data[i*4+j] = ruined_data[i*7+j];
        int error = checking(check);
        if(error > 3){
            if(decoded_data[i*4+7-error]==0)
                decoded_data[i*4+7-error] =1;
            else
                decoded_data[i*4+7-error]=0;
        }

    }
}

int checking(vector<int> data){

    for(int i=0; i<4; i++){
        if(data[i]==1){
            data[i] =0;
            data[i+1] = abs((data[i+1]==1));
            data[i+2] = abs((data[i+2]==0));
            data[i+3] = abs((data[i+3]==0));
        }
    }

    if(data[4]==0){
        if(data[5]==0){
            if(data[6]==0)
                return 0;
            else
                return 1;
        }
        else{
            if(data[6]==0)
                return 2;
            else
                return 4;
        }
    }
    else{
        if(data[5]==0){
            if(data[6]==0)
                return 3;
            else
                return 7;
        }
        else{
            if(data[6]==0)
                return 5;
            else
                return 6;
        }
    }
}

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

int main(){
    int size = 1024;
    vector<int> rawdata(size);
    vector<int> encoded_code( size/4*7);
    vector<int> decoded_code( size);
    vector<int> ruindata;

    ruindata.assign(encoded_code.begin(),encoded_code.end());

    generate_data(rawdata);
    cout<< "Original Code :"<<endl;
    for (int i=0; i<rawdata.size(); ++i){
        cout<<rawdata[i]<< " ";
    }
    cout<<endl;


    encode(rawdata, encoded_code);
    cout<< "Encoded Code :"<<endl;
    for (int i=0; i<encoded_code.size(); ++i){
        cout<<encoded_code[i]<< " ";
    }
    cout<<endl;

    for(int i=0;i<encoded_code.size();i++)
        ruindata[i] = encoded_code[i];
    cout << endl;

    ruin(ruindata);
    cout<< "Defective Code :"<<endl;
    for (int i=0; i<ruindata.size(); ++i){
        cout<<ruindata[i]<< " ";
    }
    cout<<endl;


    restore_data(ruindata,decoded_code);

    cout<< "Decoded code :"<<endl;
    for (int i=0; i<decoded_code.size(); ++i){
        cout<<decoded_code[i]<< " ";
    }
    cout<<endl;

    compare_ori_decode(rawdata,decoded_code);

}

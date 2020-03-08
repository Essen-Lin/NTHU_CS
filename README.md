# NTHU_CS Ｗireless Network

Wireless Network Lab 4

Code file : lab4_hamming.cpp
Output file: Hamming_code.txt

說明：
function 一共有7個，分別是
1.	random_data : 產生Original Code，Randomly generate 1Kbits of binary data
2.	Dem_to_bin ：將十進位轉成二進位
3.	Hamming_encode : Have these data encoded with channel coding schemes above.(將1產生的1K bit利用hamming code 轉成新的code
4.	ruin_data : Randomly ruin the data (one or more bits depend on what kind of channel coding scheme you use)  num_ruin可以決定要隨機破壞幾個bit
5.	detect_hamming_correct : 找出是哪個bit壞掉
6.	decode：Decode the ruined data（和5一起完成此步驟）
7.	compare_ori_decode：Compare the original data and decoded data

---
Code file : lab4_linear_block_code.py
Output file: linear_block_code.txt

說明：因為需要使用到矩陣運算，在python上較好處理，因此在此不使用c++改使用python

將1024分成每4bit一個區塊處理，將每4bit encode成linear block code，因此若錯誤都分佈在不同的block之中，最多可以錯256個bit，但由於ruin data按照常理是在一次傳送的過程中，不會按照規律一次都只錯一個block，因此隨機分佈在不同block中，所以若只有1個bit都能保證正確。
 
function 一共有7個，分別是
1.	generate_data : 產生Original Code，Randomly generate 1Kbits of binary data
2.	handle_dot ：處理矩陣，呈現XOR的結果
3.	encoding_data : Have these data encoded with channel coding schemes above.(將1產生的1K bit利用linear block code 轉成新的code
4.	ruining_data : Randomly ruin the data (one or more bits depend on what kind of channel coding scheme you use)  num_ruin可以決定要隨機破壞幾個bit
5.	decoding_data: 找出是哪個bit壞掉
6.	final_data：Decode the ruined data（和5一起完成此步驟）
7.	compare_ori_decode：Compare the original data and decoded data

---
Code file : lab4_cyclic_code.cpp
Output file: cyclic_code.txt

說明：
將1024分成每4bit一個區塊處理，將每4bit encode成linear block code，因此若錯誤都分佈在不同的block之中，最多可以錯256個bit，但由於ruin data按照常理是在一次傳送的過程中，不會按照規律一次都只錯一個block，因此隨機分佈在不同block中，所以若只有1個bit都能保證正確。

function 一共有6個，分別是
1.	generate_data : 產生Original Code，Randomly generate 1Kbits of binary data
2.	encode : Have these data encoded with channel coding schemes above.(將1產生的1K bit利用cyclic code 轉成新的code
3.	ruin : Randomly ruin the data (one or more bits depend on what kind of channel coding scheme you use)  num_ruin可以決定要隨機破壞幾個bit
4.	checking : 找出是哪個bit壞掉
5.	restore_data：Decode the ruined data（和5一起完成此步驟）
6.	compare_ori_decode：Compare the original data and decoded data

---

#####Compare






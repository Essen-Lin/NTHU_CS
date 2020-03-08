#!/usr/bin/python
# -*- coding: UTF-8 -*-
 
import random
import numpy as np
# 生成第一个随机数




def generate_data(times,list =[]):
	for i in range(0,times):
		a = random.randint(0,1)
		list.append(a)

	return list

def encoding_data(oridata):
	encode_data = []
	G = np.array([[1,0,0,0,1,1,0]
		,[0,1,0,0,0,1,1]
		,[0,0,1,0,1,1,1]
		,[0,0,0,1,1,0,1]])

	for i in range(int(len(oridata)/4)):
		m = np.array([[oridata[i*4],origin_data[i*4+1],
						oridata[i*4+2],origin_data[i*4+3]]])
		c = handle_dot(np.dot(m,G))
		c = c.flat
		#print(list(c))
		for i in range(len(list(c))):
			encode_data.append(c[i])
		#encode_data.append(list(c))

	print(encode_data)
	return encode_data

def handle_dot(matrix):
	for i in range(matrix.size):
		if(matrix[0][i]%2 == 1 ):
			matrix[0][i] = 1
		else:
			matrix[0][i] = 0
	return matrix

def ruining_data(encode_data,num):
	error_data = encode_data.copy()
	for i in range(num):
		x = random.randint(0,len(encode_data)-1)
		error_data[x] = (error_data[x]+1)%2
	return error_data

def decoding_data(error_data):
	H = np.array([[1,1,0],[0,1,1],[1,1,1],[1,0,1]
					,[1,0,0],[0,1,0],[0,0,1]])

	decode_data = error_data.copy()
	s = 0
	error_bit =0
	for i in range(int(len(error_data)/7)):
		#print("iteration",i)
		x = np.array([error_data[i*7:i*7+7]])
		#print ("error_data:",x,"cH :",np.dot(x,H) )
		s = handle_dot(np.dot(x,H))
		s = list(s.flat)
		for j in range(len(list(H))):
			#print(" s : ",s," H :", list(list(H)[j]))
			if( s == list(list(H)[j])):
				error_bit = i*7+j
				#print("error_bit: ",error_bit)
				decode_data[error_bit] = (decode_data[error_bit]+1)%2

	#print("error_bit : ",error_bit)

	#decode_data[error_bit] = (decode_data[error_bit]+1)%2
	
	return decode_data


def final_data(decode_data):
	final_data = []
	for i in range(int(len(error_data))):
		if ((i%7)<4):
			final_data.append(decode_data[i])

	return final_data


def compare_ori_decode(origin_data,decode_data):
	s =0
	for i in range(len(origin_data)):
		if (origin_data[i]!=decode_data[i]):
			s+=1
			print(i,'is error')
	if (s != 0):
		print("number of bit(s) error detected : ",s)	
	else:
		print("correct !")

size = 1024
origin_data = generate_data(size,[])


print("Original Data : ")
print(origin_data) # generate 1K data



print("Encode Data : ")
encode_data = encoding_data(origin_data)

print("Defected Data : ")

error_data = ruining_data(encode_data,1)

print(error_data)

#compare_ori_decode(encode_data,error_data)

decode_data = decoding_data(error_data)

print("Decoded Data : ")

final_data = final_data(decode_data)
#print(decode_data)
#print("Final Data : ")
print(final_data)

compare_ori_decode(origin_data,final_data)

# Introduction
**Bucket sorting is a non-comparative and stable sort which trades space complexity for time complexity.**  
It's an inductive result of nest sorting which is a near-complete idea named **divide-and-conquer（分治）**.
# Bucket sorting algorithm roughly
The array is divided into a finite number of buckets and sort within each bucketand finally list the records in each bucket one by one to get an ordered sequence;   
It's possible to use other sorting algorithms, or recursively using bucket sorting in each bucket.

# Bucket sort algorithm concretely 
A set of data (dataset's size:N)to be sorted is evenly(均匀地) and independently distributed in a range [min,max].  

And the range is divided into several sub-ranges (the number of sub-ranges is M), and then based on some kind of mapping function f, Map the keyword K of each element to B[i], then k is the element of B[i] .   

B[i] is a set of sequences of size N/M, and each element in B[i] (non-empty bucket) is sorted internally(内部地) and then the data in the non-empty bucket is combined to get an ordered sequence.   
The mapping function is generally f=array[i]/k,k^2=n;   
Bucket sorting makes use of the mapping of functions, and **the key to efficiency lies in the determination of the mapping functions**.  
# In order to make the bucket sorting efficient, we need to do the following two things.
**1.In the case of sufficient(充足的) extra space, increase the number of buckets as much as possible.   
2.Using the mapping function, the input N data can be evenly distributed in M buckets.**   
Why do we need to do both?   
Bucket sorting needs to ensure that the elements are evenly distributed as much as possible, otherwise when all elements are concentrated in the same bucket, the bucket sorting fails.   
The smaller the bucket division(划分), the less data in each bucket, the time taken to sort will decrease, but the space consumption will increase; 
# The determination of the number of buckets 
Suppose to sort the array named "arr".  
|array's attributes|value|
|---|---|
|length|len|
|maximum|max|
|minimum|min|
|gap|(max-min)/len+1|
|bucket_num|(max-min)/gap+1|

The gap between elements in the same bucket is up to gap-1;  
The formula (arr[i]-min)/gap determines which bucket the array elements are placed in.

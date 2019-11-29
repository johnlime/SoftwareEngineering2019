# softwareEngineering2019
>This is for the class of softwareEngineering2019.  
>Codes for the quiz will be added here.  

## 10/18 B+tree(leaf split)
Step 1: Copy left leaf to temp.
Step 2: Insert new key and pointer to temp array.
Step 4: For left leaf, set pointer to NULL and key to -1. The nkey is also set to 0.
Step 5, 6: Copy first half of temp to right and second half of temp to left.

Example output:
```
Key: 2
[2]
Key: 3
[2 3]
Key: 1
[1 2 3]
Key: 5
[0x0]1[0x0]2[0x0]3[0x0]5[0x6665646362613938]
Left:  [1 2]
Right: [3 5]
[1 2]
```

## 11/29 B+tree(full implementation)
Example output: B+-Tree with 0~19
```
[0]
[0 1]
[0 1 2]
[[0 1]2[2 3]]
[[0 1]2[2 3 4]]
[[0 1]2[2 3]4[4 5]]
[[0 1]2[2 3]4[4 5 6]]
[[0 1]2[2 3]4[4 5]6[6 7]]
[[0 1]2[2 3]4[4 5]6[6 7 8]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9 10]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11 12]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]12[12 13]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]12[12 13 14]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]]12[[12 13]14[14 15]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]]12[[12 13]14[14 15 16]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]]12[[12 13]14[14 15]16[16 17]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]]12[[12 13]14[14 15]16[16 17 18]]]
[[[0 1]2[2 3]4[4 5]]6[[6 7]8[8 9]10[10 11]]12[[12 13]14[14 15]16[16 17]18[18 19]]]
```

## 11/22 Latch
Example output:
```
Counter: 100000000 (Ref. 100000000)
```

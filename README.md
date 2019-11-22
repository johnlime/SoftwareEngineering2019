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

## 10/22 B+tree(full implementation)
Segmentation Error が出ていて一ヶ月直せていないのでこのまま出します。`1018_bptree-leaf_split`に入っています。

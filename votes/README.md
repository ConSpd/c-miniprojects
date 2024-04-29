# Vote Calculator

The script reads a binary file consisting of 16 bit numbers on each line that represent gender, age and vote according to the following structure.

`0111010 10 0100000` splits into:

**Age:** `0111010`, it is the first seven digits.
- $18 \le \text{age} \le 100$
<br>

**Gender:** `10`, it is the middle two digits.
- `01` = Male
- `10` = Female
- `11` = Other
- `00` = Invalid
<br>

**Vote:** `0100000`, it is the final seven digits. Each of the digits represents a candidate. 
- `0000000` = Blank Vote
- `0000101` = Invalid Vote
- `0010000` = Valid Vote
<br>

According to the above rules the `0111010 10 0100000` represents:
- **Age** = `0111010` = 52
- **Gender** = `10` = Female
- **Vote** = `0100000` = 6th candidate
<br>

### Example of Running the Application
---
**Input Data**<br>
`0x4f04`<br>
`0x4881`<br>
`0x4f08`<br>
`0x4f01`<br>
`0x4940`<br>
`0x4ba2`<br>
`0x4884`<br>


<img width="513" alt="image" src="https://github.com/ConSpd/c-miniprojects/assets/74179715/1aa4931b-64f5-4aba-8a9e-1416746c7371">

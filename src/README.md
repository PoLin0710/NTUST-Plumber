#    Pipe
水管型態
```
直線水管 STRAIGHTPIPE = 0 
T字形水管 TPIPE = 1 
L字形水管 LPIPE = 2 
十字水管 CROSSPIPE = 3 
```
方向
```
上 UP = 0
下 DOWN = 1
左 LEFT = 2
右 RIGHT = 3
```
各種類方向配代號
1. STRAIGHTPIPE
```
UP #P# RIGHT ### DOWN #P# LEFT ###
   #P#       PPP      #P#      PPP
   #P#       ###      #P#      ###
```
2. TPIPE
```
UP #P# RIGHT #P# DOWN ### LEFT #P#
   PPP       #PP      PPP      PP#
   ###       #P#      #P#      #P#
```
3. LPIPE
```
UP #P# RIGHT ### DOWN ### LEFT #P#
   #PP       #PP      PP#      PP#
   ###       #P#      #P#      ###
```
4. CROSSPIPE
```
UP #P# RIGHT #P# DOWN #P# LEFT #P#
   PPP       PPP      PPP      PPP
   #P#       #P#      #P#      #P#
```
#    Pipe
���ޫ��A
```
���u���� STRAIGHTPIPE = 0 
T�r�Τ��� TPIPE = 1 
L�r�Τ��� LPIPE = 2 
�Q�r���� CROSSPIPE = 3 
```
��V
```
�W UP = 0
�U DOWN = 1
�� LEFT = 2
�k RIGHT = 3
```
�U������V�t�N��
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
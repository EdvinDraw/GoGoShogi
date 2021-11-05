@echo off
setlocal EnableDelayedExpansion

set "startTime=%time: =0%"

echo Started at: %startTime%

E:\GBDK\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yt01 -Wl-yo16 -Wm-ys -IhUGEDriver/hUGEDriver-master/include -o GoGoShogi.gb fade.c mastershogi.c boardcode.c playermovements.c main.c intro.c title.c menu.c colorsides.c tutorials.c ingame.c animations.c kill.c goodsfx.c titletheme.c fujitheme.c starttheme.c hUGEDriver.obj.o

echo Started at: %startTime%
set "endTime=%time: =0%"
echo Ended at: %endTime%
rem Get elapsed time:
set "end=!endTime:%time:~8,1%=%%100)*100+1!"  &  set "start=!startTime:%time:~8,1%=%%100)*100+1!"
set /A "elap=((((10!end:%time:~2,1%=%%100)*60+1!%%100)-((((10!start:%time:~2,1%=%%100)*60+1!%%100), elap-=(elap>>31)*24*60*60*100"

rem Convert elapsed time to HH:MM:SS:CC format:
set /A "cc=elap%%100+100,elap/=100,ss=elap%%60+100,elap/=60,mm=elap%%60+100,hh=elap/60+100"

echo Estimated time: %hh:~1%%time:~2,1%%mm:~1%%time:~2,1%%ss:~1%%time:~8,1%%cc:~1%
@echo off
set file=E:\MMX5_BGM.wav
( echo Set Chime = CreateObject("WMPlayer.OCX.7"^)
  echo Chime.URL = "%file%"
  echo Chime.Controls.play
  echo do while Chime.currentmedia.duration = 0
  echo wscript.sleep 100
  echo loop
  echo wscript.sleep (int(Chime.currentmedia.duration^)+1^)*1000) >chime.vbs
start /min chime.vbs
pause
start GoGoShogi.gb
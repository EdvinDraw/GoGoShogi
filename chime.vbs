Set Chime = CreateObject("WMPlayer.OCX.7")
Chime.URL = "E:\MMX5_BGM.wav"
Chime.Controls.play
do while Chime.currentmedia.duration = 0
wscript.sleep 100
loop
wscript.sleep (int(Chime.currentmedia.duration)+1)*1000

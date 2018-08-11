此程式為利用Python接收一段Udp字串指令之後將此字串透過Http Post到Google Sheet之上，而Google Sheet則有另外一段JaveScript做接收處理。

目前設定的Google Sheet為 https://docs.google.com/spreadsheets/d/1w0TWJwhMztvCEC5R1fbfshAZZ8VhjfkFMyhZM4AAiXs/edit#gid=1250688084

使用時請先用記事本打開此程式，之後於第五行的地方(address)，將IP改為本機IP，以及設定Port即可

接收的格式為

"write,WorkSheetName,Time,Lon, Lat,Tem1,Hum1,Vol1,Tem2,Hum2,Vol2,Tem3,Hum3,Vol3,Tem4,Hum4,Vol4,Weight,"

PS:沒資料的地方記得補上空格 否則程式不會處理
例如 
write,WorkSheetName, , , Lat,......
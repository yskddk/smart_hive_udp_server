var ss = SpreadsheetApp.getActiveSpreadsheet(),
    sheet1 = ss.getSheetByName("Test3");
function myFunction()
{
  //doGet(e);
  doPost(e);
}
function doGet(e) {
 return HtmlService.createHtmlOutput('<b>Hello, world!</b>');
}
function doPost(e) {
  if(e.parameter.method =="write")
  {
    write_data(e.parameter);
  }
    if(e.parameter.method =="Test")
  {
    // return HtmlService.createHtmlOutput('<b>Hello, world!</b>');
  }

}
var e = {
  parameter:{
    "method": "write",
    "WorkSheetName": "Sheet1",
    "Time":"0",
    "Lon":"0",
    "Lat":"0",
    "Tem1":"0",
    "Hum1":"0",
    "Vol1":"0",
     "Tem2":"0",
    "Hum2":"0",
    "Vol2":"0",
     "Tem3":"0",
    "Hum3":"0",
    "Vol3":"0",
     "Tem4":"0",
    "Hum4":"0",
    "Vol4":"0",
    "Weight":"0",
  }
}
function write_data(para) {
  var WorkSheetName=para.WorkSheetName,
      Time = para.Time,
      Lon = para.Lon,
      Lat = para.Lat,
      Hum1=para.Hum1,
      Vol1=para.Vol1,
      Tem2=para.Tem2,
      Hum2=para.Hum2,
      Vol2=para.Vol2,
      Tem3=para.Tem3,
      Hum3=para.Hum3,
      Vol3=para.Vol3,
      Tem4=para.Tem4,
      Hum4=para.Hum4,
      Vol4=para.Vol4,
      Weight=para.Weight,
      Tem1=para.Tem1;
  var nowSheet =ss.getSheetByName(WorkSheetName);
  if(nowSheet ==null)
  {
    nowSheet=ss.insertSheet(WorkSheetName);
    nowSheet.appendRow(["時鐘","經度","緯度","溫度1","濕度1","音量1","溫度2","濕度2","音量2","溫度3","濕度3","音量3","溫度4","濕度4","音量4","重量"]); 
    //nowSheet.setName(WorkSheetName);
  }
  nowSheet.appendRow([Time,Lon,Lat,Tem1,Hum1,Vol1,Tem2,Hum2,Vol2,Tem3,Hum3,Vol3,Tem4,Hum4,Vol4,Weight]); // 插入一列新的資料 
}
/*function onOpen() {
    var activeSpreadsheet = SpreadsheetApp.getActiveSpreadsheet();
    var yourNewSheet = activeSpreadsheet.getSheetByName("Name of your new sheet");

    if (yourNewSheet != null) {
        activeSpreadsheet.deleteSheet(yourNewSheet);
    }

    yourNewSheet = activeSpreadsheet.insertSheet();
    yourNewSheet.setName("Name of your new sheet");
}*/

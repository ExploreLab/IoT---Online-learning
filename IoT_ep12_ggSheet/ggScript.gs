// Created by Mr.Jukrapun Chitpong, 2018
// All Rights Reserved.
// Github: https://github.com/ExploreLab

// Read/Write to Google Sheets using REST API.
// Can be used with ESP32/ESP8266 & other embedded IoT devices.

// Use this file with the ESP32/ESP8266 library WiFiClientSecure
 
// doGet() and doPost() need the spreadsheet ID. Cannot use "active spreadsheet" here since

/* This Script for connect between ESP32/ESP8266 with Google Apps Script
   Jukrapun Chitpong - facebook.com/eeeg.ch
   */

var SS = SpreadsheetApp.openById('Your_SheetID');
var sheet = SS.getSheetByName('Sheet1');
var str = "";

function doGet(e){
  var FIELD1 = e.parameter.FIELD1; 
  var FIELD2 = e.parameter.FIELD2;
  
  if (FIELD1 !== undefined || FIELD2 !== undefined){
    var now = Utilities.formatDate(new Date(), "GMT+7", "yyyy-MM-dd'T'hh:mm a'Z'").slice(11,19);
    var count = (sheet.getRange('G2').getValue());
    if(count == '0'){
      sheet.getRange('E2').setValue(now);
      sheet.getRange('G2').setValue(1);
      
    }else{
      sheet.getRange('F2').setValue(now);
      sheet.getRange('G2').setValue(count+1);
    }

    addProduct(FIELD1, FIELD2); 
    
    str = "Sent: "+ now;
    return ContentService.createTextOutput(str);
  }
}

//https://developers.google.com/apps-script/reference/spreadsheet/sheet
function addProduct(FIELD1, FIELD2) {
  var sheet = SpreadsheetApp.getActiveSheet();
  var Time = new Date(); 
  sheet.appendRow([Time, FIELD1, FIELD2]);
  //sheet.deleteRows(6, 10);
  //Logger.log(values)
  
} 
